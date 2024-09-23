/**
 * (C) Copyright 2016-2024 Intel Corporation.
 *
 * SPDX-License-Identifier: BSD-2-Clause-Patent
 */
/**
 * Object cache for VOS OI table.
 * Object index is in Persistent memory. This cache in DRAM
 * maintains an LRU which is accessible in the I/O path. The object
 * index API defined for PMEM are used here by the cache..
 *
 * LRU cache implementation:
 * Simple LRU based object cache for Object index table
 * Uses a hashtable and a doubly linked list to set and get
 * entries. The size of both hashtable and linked list are
 * fixed length.
 *
 * Author: Vishwanath Venkatesan <vishwanath.venkatesan@intel.com>
 */
#define D_LOGFAC	DD_FAC(vos)

#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include "vos_obj.h"
#include "vos_internal.h"
#include <daos_errno.h>

/**
 * Local type for VOS LRU key
 * VOS LRU key must consist of
 * Object ID and container UUID
 */
struct obj_lru_key {
	/* container the object belongs to */
	struct vos_container	*olk_cont;
	/* Object ID */
	daos_unit_oid_t		 olk_oid;
};

static inline void
init_object(struct vos_object *obj, daos_unit_oid_t oid, struct vos_container *cont)
{
	/**
	 * Saving a copy of oid to avoid looking up in vos_obj_df, which
	 * is a direct pointer to pmem data structure
	 */
	obj->obj_id	= oid;
	obj->obj_cont	= cont;
	vos_cont_addref(cont);
	vos_ilog_fetch_init(&obj->obj_ilog_info);
}

static int
obj_lop_alloc(void *key, unsigned int ksize, void *args,
	      struct daos_llink **llink_p)
{
	struct vos_object	*obj;
	struct obj_lru_key	*lkey;
	struct vos_container	*cont;
	struct vos_tls		*tls;
	int			 rc;

	cont = (struct vos_container *)args;
	D_ASSERT(cont != NULL);

	tls = vos_tls_get(cont->vc_pool->vp_sysdb);
	lkey = (struct obj_lru_key *)key;
	D_ASSERT(lkey != NULL);

	D_DEBUG(DB_TRACE, "cont="DF_UUID", obj="DF_UOID"\n",
		DP_UUID(cont->vc_id), DP_UOID(lkey->olk_oid));

	D_ALLOC_PTR(obj);
	if (!obj)
		D_GOTO(failed, rc = -DER_NOMEM);

	init_object(obj, lkey->olk_oid, cont);
	d_tm_inc_gauge(tls->vtl_obj_cnt, 1);
	*llink_p = &obj->obj_llink;
	rc = 0;
failed:
	return rc;
}

static bool
obj_lop_cmp_key(const void *key, unsigned int ksize, struct daos_llink *llink)
{
	struct vos_object	*obj;
	struct obj_lru_key	*lkey = (struct obj_lru_key *)key;

	D_ASSERT(ksize == sizeof(struct obj_lru_key));

	obj = container_of(llink, struct vos_object, obj_llink);
	return lkey->olk_cont == obj->obj_cont &&
	       !memcmp(&lkey->olk_oid, &obj->obj_id, sizeof(obj->obj_id));
}

static uint32_t
obj_lop_rec_hash(struct daos_llink *llink)
{
	struct obj_lru_key	 lkey;
	struct vos_object	*obj;

	obj = container_of(llink, struct vos_object, obj_llink);

	/* Create the key for obj cache */
	lkey.olk_cont = obj->obj_cont;
	lkey.olk_oid  = obj->obj_id;

	return d_hash_string_u32((const char *)&lkey, sizeof(lkey));
}

static inline void
clean_object(struct vos_object *obj)
{
	vos_ilog_fetch_finish(&obj->obj_ilog_info);
	if (obj->obj_cont != NULL)
		vos_cont_decref(obj->obj_cont);

	obj_tree_fini(obj);
}

static void
obj_lop_free(struct daos_llink *llink)
{
	struct vos_object	*obj;
	struct vos_tls		*tls;

	D_DEBUG(DB_TRACE, "lru free callback for vos_obj_cache\n");

	obj = container_of(llink, struct vos_object, obj_llink);
	tls = vos_tls_get(obj->obj_cont->vc_pool->vp_sysdb);
	d_tm_dec_gauge(tls->vtl_obj_cnt, 1);
	clean_object(obj);
	D_FREE(obj);
}

static void
obj_lop_print_key(void *key, unsigned int ksize)
{
	struct obj_lru_key	*lkey = (struct obj_lru_key *)key;
	struct vos_container	*cont = lkey->olk_cont;

	D_DEBUG(DB_TRACE, "pool="DF_UUID" cont="DF_UUID", obj="DF_UOID"\n",
		DP_UUID(cont->vc_pool->vp_id),
		DP_UUID(cont->vc_id), DP_UOID(lkey->olk_oid));
}

static struct daos_llink_ops obj_lru_ops = {
	.lop_free_ref	= obj_lop_free,
	.lop_alloc_ref	= obj_lop_alloc,
	.lop_cmp_keys	= obj_lop_cmp_key,
	.lop_rec_hash	= obj_lop_rec_hash,
	.lop_print_key	= obj_lop_print_key,
};

int
vos_obj_cache_create(int32_t cache_size, struct daos_lru_cache **occ)
{
	int	rc;

	D_DEBUG(DB_TRACE, "Creating an object cache %d\n", (1 << cache_size));
	rc = daos_lru_cache_create(cache_size, D_HASH_FT_NOLOCK,
				   &obj_lru_ops, occ);
	if (rc)
		D_ERROR("Error in creating lru cache: "DF_RC"\n", DP_RC(rc));
	return rc;
}

void
vos_obj_cache_destroy(struct daos_lru_cache *occ)
{
	D_ASSERT(occ != NULL);
	daos_lru_cache_destroy(occ);
}

static bool
obj_cache_evict_cond(struct daos_llink *llink, void *args)
{
	struct vos_container	*cont = (struct vos_container *)args;
	struct vos_object	*obj;

	if (cont == NULL)
		return true;

	obj = container_of(llink, struct vos_object, obj_llink);
	return obj->obj_cont == cont;
}

void
vos_obj_cache_evict(struct vos_container *cont)
{
	struct daos_lru_cache	*occ;

	occ = vos_obj_cache_get(cont->vc_pool->vp_sysdb);
	D_ASSERT(occ != NULL);

	daos_lru_cache_evict(occ, obj_cache_evict_cond, cont);
}

static __thread struct vos_object	 obj_local = {0};

static inline void
obj_put(struct daos_lru_cache *occ, struct vos_object *obj, bool evict)
{
	if (evict)
		daos_lru_ref_evict(occ, &obj->obj_llink);
	daos_lru_ref_release(occ, &obj->obj_llink);
}

static int
obj_get(struct daos_lru_cache *occ, struct vos_container *cont, daos_unit_oid_t oid,
	bool create, struct vos_object **obj_p)
{
	struct vos_object	*obj;
	struct daos_llink	*lret;
	struct obj_lru_key	 lkey;
	int			 rc;
	void			*create_flag;

	if (cont->vc_pool->vp_dying)
		D_GOTO(out, rc = -DER_SHUTDOWN);

	create_flag = create ? cont : NULL;
	lkey.olk_cont = cont;
	lkey.olk_oid = oid;

	rc = daos_lru_ref_hold(occ, &lkey, sizeof(lkey), create_flag, &lret);
	if (rc == 0) {
		obj = container_of(lret, struct vos_object, obj_llink);
		*obj_p = obj;
		return 0;
	}
out:
	if (rc == -DER_NONEXIST) {
		D_ASSERT(create_flag == NULL);
		D_DEBUG(DB_TRACE, DF_CONT": Object "DF_UOID" doesn't exist.\n",
			DP_CONT(cont->vc_pool->vp_id, cont->vc_id), DP_UOID(oid));
	} else if (rc) {
		DL_ERROR(rc, DF_CONT": Failed to find object "DF_UOID".",
			 DP_CONT(cont->vc_pool->vp_id, cont->vc_id), DP_UOID(oid));
	}

	return rc;
}

static inline void
obj_release(struct daos_lru_cache *occ, struct vos_object *obj, bool evict)
{

	D_ASSERT(obj != NULL);
	/* TODO: Unpin the object in md-on-ssd phase II */

	if (obj == &obj_local) {
		clean_object(obj);
		memset(obj, 0, sizeof(*obj));
		return;
	}

	obj_put(occ, obj, evict);
}

void
vos_obj_release(struct vos_object *obj, uint64_t flags, bool evict)
{
	struct daos_lru_cache	*occ;

	D_ASSERT(obj != &obj_local);

	occ = vos_obj_cache_get(obj->obj_cont->vc_pool->vp_sysdb);
	D_ASSERT(occ != NULL);

	if (flags & VOS_OBJ_AGGREGATE)
		obj->obj_aggregate = 0;
	else if (flags & VOS_OBJ_DISCARD)
		obj->obj_discard = 0;

	obj_release(occ, obj, evict);
}

/** Move local object to the lru cache */
static inline int
cache_object(struct daos_lru_cache *occ, struct vos_object **objp)
{
	struct vos_object	*obj_new;
	int			 rc;

	D_ASSERT(obj_local.obj_cont != NULL);
	rc = obj_get(occ, obj_local.obj_cont, obj_local.obj_id, true, &obj_new);
	if (rc != 0)
		return rc; /* Can't cache new object */

	/* This object should not be cached */
	D_ASSERT(obj_new != NULL);
	D_ASSERT(obj_new->obj_df == NULL);

	vos_ilog_fetch_move(&obj_new->obj_ilog_info, &obj_local.obj_ilog_info);
	obj_new->obj_toh = obj_local.obj_toh;
	obj_new->obj_ih = obj_local.obj_ih;
	obj_new->obj_sync_epoch = obj_local.obj_sync_epoch;
	obj_new->obj_df = obj_local.obj_df;
	obj_new->obj_zombie = obj_local.obj_zombie;
	obj_local.obj_toh = DAOS_HDL_INVAL;
	obj_local.obj_ih = DAOS_HDL_INVAL;

	clean_object(&obj_local);
	memset(&obj_local, 0, sizeof(obj_local));

	*objp = obj_new;

	return 0;
}

static bool
check_discard(struct vos_object *obj, uint64_t flags)
{
	bool discard = flags & VOS_OBJ_DISCARD;
	bool agg     = flags & VOS_OBJ_AGGREGATE;
	bool create  = flags & VOS_OBJ_CREATE;

	/* VOS aggregation is mutually exclusive with VOS discard.
	 * Object discard is mutually exclusive with VOS discard.
	 * EC aggregation is not mutually exclusive with anything.
	 * For simplicity, we do make all of them mutually exclusive on the same
	 * object.
	 */

	if (obj->obj_discard) {
		/** Mutually exclusive with create, discard and aggregation */
		if (create || discard || agg) {
			D_DEBUG(DB_EPC, "Conflict detected, discard already running on object\n");
			return true;
		}
	} else if (obj->obj_aggregate) {
		/** Mutually exclusive with discard */
		if (discard || agg) {
			D_DEBUG(DB_EPC,
				"Conflict detected, aggregation already running on object\n");
			return true;
		}
	}

	return false;
}

int
vos_obj_check_discard(struct vos_container *cont, daos_unit_oid_t oid, uint64_t flags)
{
	struct vos_object	*obj;
	struct daos_lru_cache	*occ;
	int			 rc;

	D_ASSERT(cont != NULL);
	D_ASSERT(cont->vc_pool);

	occ = vos_obj_cache_get(cont->vc_pool->vp_sysdb);
	D_ASSERT(occ != NULL);

	rc = obj_get(occ, cont, oid, false, &obj);
	if (rc == -DER_NONEXIST)
		return 0;
	if (rc)
		return rc;

	/* TODO: Pin object in memory */

	if (check_discard(obj, flags))
		/* Update request will retry with this error */
		rc = (flags & VOS_OBJ_CREATE) ? -DER_UPDATE_AGAIN : -DER_BUSY;

	obj_release(occ, obj, false);
	return rc;
}

int
vos_obj_incarnate(struct vos_object *obj, daos_epoch_range_t *epr, daos_epoch_t bound,
		  uint64_t flags, uint32_t intent, struct vos_ts_set *ts_set)
{
	struct vos_container	*cont = obj->obj_cont;
	uint32_t		 cond_mask = 0;
	int			 rc;

	D_ASSERT((flags & (VOS_OBJ_AGGREGATE | VOS_OBJ_DISCARD)) == 0);
	D_ASSERT(intent == DAOS_INTENT_PUNCH || intent == DAOS_INTENT_UPDATE);

	if (obj->obj_df == NULL) {
		rc = vos_oi_alloc(cont, obj->obj_id, epr->epr_hi, &obj->obj_df, ts_set);
		if (rc) {
			DL_ERROR(rc, DF_CONT": Failed to allocate OI "DF_UOID".",
				 DP_CONT(cont->vc_pool->vp_id, cont->vc_id),
				 DP_UOID(obj->obj_id));
			return rc;
		}
		D_ASSERT(obj->obj_df);
	} else {
		vos_ilog_ts_ignore(vos_obj2umm(obj), &obj->obj_df->vo_ilog);
	}

	/* Check again since it could yield since vos_obj_hold() */
	if (check_discard(obj, flags))
		return -DER_UPDATE_AGAIN;

	/* Check the sync epoch */
	if (epr->epr_hi <= obj->obj_sync_epoch &&
	    vos_dth_get(obj->obj_cont->vc_pool->vp_sysdb) != NULL) {
		/* If someone has synced the object against the
		 * obj->obj_sync_epoch, then we do not allow to modify the
		 * object with old epoch. Let's ask the caller to retry with
		 * newer epoch.
		 *
		 * For rebuild case, the @dth will be NULL.
		 */
		D_ASSERT(obj->obj_sync_epoch > 0);

		D_INFO("Refuse %s obj "DF_UOID" because of the epoch "DF_U64
		       " is not newer than the sync epoch "DF_U64"\n",
		       intent == DAOS_INTENT_PUNCH ? "punch" : "update",
		       DP_UOID(obj->obj_id), epr->epr_hi, obj->obj_sync_epoch);
		return -DER_TX_RESTART;
	}

	/* It's done for DAOS_INTENT_PUNCH case */
	if (intent == DAOS_INTENT_PUNCH)
		return 0;

	/** If it's a conditional update, we need to preserve the -DER_NONEXIST
	 *  for the caller.
	 */
	if (ts_set && ts_set->ts_flags & VOS_COND_UPDATE_OP_MASK)
		cond_mask = VOS_ILOG_COND_UPDATE;
	rc = vos_ilog_update(cont, &obj->obj_df->vo_ilog, epr, bound, NULL,
			     &obj->obj_ilog_info, cond_mask, ts_set);
	if (rc == -DER_NONEXIST && !cond_mask)
		rc = 0;

	if (rc != 0)
		VOS_TX_LOG_FAIL(rc, "Could not update object "DF_UOID" at "DF_U64": "DF_RC"\n",
				DP_UOID(obj->obj_id), epr->epr_hi, DP_RC(rc));
	return rc;
}

int
vos_obj_hold(struct vos_container *cont, daos_unit_oid_t oid, daos_epoch_range_t *epr,
	     daos_epoch_t bound, uint64_t flags, uint32_t intent, struct vos_object **obj_p,
	     struct vos_ts_set *ts_set)
{
	struct vos_object	*obj;
	struct daos_lru_cache	*occ;
	int			 rc, tmprc;
	bool			 create = false;

	D_ASSERT(cont != NULL);
	D_ASSERT(cont->vc_pool);
	D_ASSERT(obj_p != NULL);
	*obj_p = NULL;

	occ = vos_obj_cache_get(cont->vc_pool->vp_sysdb);
	D_ASSERT(occ != NULL);

	if (flags & VOS_OBJ_CREATE) {
		D_ASSERT(intent == DAOS_INTENT_UPDATE || intent == DAOS_INTENT_PUNCH);
		create = true;
	}

	D_DEBUG(DB_TRACE, "Try to hold cont="DF_UUID", obj="DF_UOID" "
		"layout=%u create=%d epr="DF_X64"-"DF_X64"\n", DP_UUID(cont->vc_id),
		DP_UOID(oid), oid.id_layout_ver, create, epr->epr_lo, epr->epr_hi);

	/* Lookup object cache */
	rc = obj_get(occ, cont, oid, create, &obj);
	if (rc == -DER_NONEXIST) {
		D_ASSERT(obj_local.obj_cont == NULL);
		obj = &obj_local;
		init_object(obj, oid, cont);
		rc = 0;
	} else if (rc) {
		D_GOTO(fail_log, rc);
	}

	if (obj->obj_zombie)
		D_GOTO(failed, rc = -DER_AGAIN);

	if (check_discard(obj, flags)) {
		/** Cleanup so unit test that triggers doesn't corrupt the state */
		obj_release(occ, obj, false);
		/* Update request will retry with this error */
		rc = create ? -DER_UPDATE_AGAIN : -DER_BUSY;
		goto fail_log;
	}

	/* Lookup OI table if the cached object is negative */
	if (obj->obj_df == NULL) {
		obj->obj_sync_epoch = 0;
		rc = vos_oi_find(cont, oid, &obj->obj_df, ts_set);
		if (rc == 0) {
			obj->obj_sync_epoch = obj->obj_df->vo_sync;
		} else if (rc == -DER_NONEXIST) {
			if (!create)
				goto failed;
			rc = 0;
		} else if (rc) {
			goto failed;
		}
	} else {
		tmprc = vos_ilog_ts_add(ts_set, &obj->obj_df->vo_ilog, &oid, sizeof(oid));
		D_ASSERT(tmprc == 0); /* Non-zero only valid for akey */
	}

	/* TODO: Pin the object in memory in md-on-ssd phase II. Revise the 'obj_local' implementation
	 * then, since this function could yield. */

	/* It's done for DAOS_INTENT_UPDATE or DAOS_INTENT_PUNCH or DAOS_INTENT_KILL */
	if (intent == DAOS_INTENT_UPDATE || intent == DAOS_INTENT_PUNCH ||
	    intent == DAOS_INTENT_KILL) {
		D_ASSERT((flags & (VOS_OBJ_AGGREGATE | VOS_OBJ_DISCARD)) == 0);
		if (obj == &obj_local) {
			D_ASSERT(create == false);
			rc = cache_object(occ, &obj);
			if (rc != 0)
				goto failed;
		}
		*obj_p = obj;
		return 0;
	}
	D_ASSERT(obj->obj_df != NULL);

	/* It's done for obj discard */
	if ((flags & VOS_OBJ_DISCARD))
		goto out;

	/* Object ilog check */
	rc = vos_ilog_fetch(vos_cont2umm(cont), vos_cont2hdl(cont), intent, &obj->obj_df->vo_ilog,
			    epr->epr_hi, bound, false, /* has_cond: no object level condition. */
			    NULL, NULL, &obj->obj_ilog_info);
	if (rc != 0) {
		if (vos_has_uncertainty(ts_set, &obj->obj_ilog_info, epr->epr_hi, bound))
			rc = -DER_TX_RESTART;
		D_DEBUG(DB_TRACE, "Object "DF_UOID" not found at " DF_U64"\n",
			DP_UOID(oid), epr->epr_hi);
		goto failed;
	}

	rc = vos_ilog_check(&obj->obj_ilog_info, epr, epr, flags & VOS_OBJ_VISIBLE);
	if (rc != 0) {
		D_DEBUG(DB_TRACE, "Object "DF_UOID" not visible at "DF_U64"-"DF_U64"\n",
			DP_UOID(oid), epr->epr_lo, epr->epr_hi);
		if (!vos_has_uncertainty(ts_set, &obj->obj_ilog_info, epr->epr_hi, bound))
			goto failed;

		/** If the creation is uncertain, go ahead and fall
		 *  through as if the object exists so we can do
		 *  actual uncertainty check.
		 */
	}
out:
	if (obj == &obj_local) {
		/** Ok, it's successful, go ahead and cache the object. */
		rc = cache_object(occ, &obj);
		if (rc != 0)
			goto failed;
	}
	*obj_p = obj;

	if (flags & VOS_OBJ_AGGREGATE)
		obj->obj_aggregate = 1;
	else if (flags & VOS_OBJ_DISCARD)
		obj->obj_discard = 1;

	return 0;

failed:
	obj_release(occ, obj, true);
fail_log:
	VOS_TX_LOG_FAIL(rc, "failed to hold object " DF_UOID ", rc=" DF_RC "\n", DP_UOID(oid),
			DP_RC(rc));

	return	rc;
}

void
vos_obj_evict(struct vos_object *obj)
{
	struct daos_lru_cache	*occ;

	D_ASSERT(obj != &obj_local);
	occ = vos_obj_cache_get(obj->obj_cont->vc_pool->vp_sysdb);
	D_ASSERT(occ != NULL);

	daos_lru_ref_evict(occ, &obj->obj_llink);
}

int
vos_obj_evict_by_oid(struct vos_container *cont, daos_unit_oid_t oid)
{
	struct daos_lru_cache	*occ;
	struct vos_object	*obj;
	int			 rc;

	occ = vos_obj_cache_get(cont->vc_pool->vp_sysdb);
	D_ASSERT(occ != NULL);

	rc = obj_get(occ, cont, oid, false, &obj);
	if (rc == 0) {
		obj_put(occ, obj, true);
		return 0;
	}

	return (rc == -DER_NONEXIST || rc == -DER_SHUTDOWN)? 0 : rc;
}
