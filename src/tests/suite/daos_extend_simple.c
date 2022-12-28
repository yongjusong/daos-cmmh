/**
 * (C) Copyright 2016-2022 Intel Corporation.
 *
 * SPDX-License-Identifier: BSD-2-Clause-Patent
 */
/**
 * This file is for simple tests of extend, which does not need to kill the
 * rank, and only used to verify the consistency after different data model
 * extend.
 *
 * tests/suite/daos_extend_simple.c
 *
 *
 */
#define D_LOGFAC	DD_FAC(tests)

#include "daos_iotest.h"
#include "dfs_test.h"
#include <daos/pool.h>
#include <daos/mgmt.h>
#include <daos/container.h>

#define KEY_NR		10
#define OBJ_NR		10
#define EXTEND_SMALL_POOL_SIZE	(4ULL << 30)

static void
extend_dkeys(void **state)
{
	test_arg_t	*arg = *state;
	daos_obj_id_t	oids[OBJ_NR];
	struct ioreq	req;
	int		i;
	int		j;
	int		rc;

	if (!test_runable(arg, 3))
		return;

	for (i = 0; i < OBJ_NR; i++) {
		oids[i] = daos_test_oid_gen(arg->coh, OC_RP_3G1, 0, 0,
					    arg->myrank);
		ioreq_init(&req, arg->coh, oids[i], DAOS_IOD_ARRAY, arg);

		/** Insert 10 records */
		print_message("Insert %d kv record in object "DF_OID"\n",
			      KEY_NR, DP_OID(oids[i]));
		for (j = 0; j < KEY_NR; j++) {
			char	key[32] = {0};

			sprintf(key, "dkey_0_%d", j);
			insert_single(key, "a_key", 0, "data",
				      strlen("data") + 1,
				      DAOS_TX_NONE, &req);
		}
		ioreq_fini(&req);
	}

	extend_single_pool_rank(arg, 3);

	for (i = 0; i < OBJ_NR; i++) {
		rc = daos_obj_verify(arg->coh, oids[i], DAOS_EPOCH_MAX);
		assert_rc_equal(rc, 0);
	}
}

static void
extend_akeys(void **state)
{
	test_arg_t	*arg = *state;
	daos_obj_id_t	oids[OBJ_NR];
	struct ioreq	req;
	int		i;
	int		j;
	int		rc;

	if (!test_runable(arg, 3))
		return;

	for (i = 0; i < OBJ_NR; i++) {
		oids[i] = daos_test_oid_gen(arg->coh, OC_RP_3G1, 0, 0,
					    arg->myrank);
		ioreq_init(&req, arg->coh, oids[i], DAOS_IOD_ARRAY, arg);

		/** Insert 10 records */
		print_message("Insert %d kv record in object "DF_OID"\n",
			      KEY_NR, DP_OID(oids[i]));
		for (j = 0; j < KEY_NR; j++) {
			char	akey[16];

			sprintf(akey, "%d", j);
			insert_single("dkey_1_0", akey, 0, "data",
				      strlen("data") + 1,
				      DAOS_TX_NONE, &req);
		}
		ioreq_fini(&req);
	}

	extend_single_pool_rank(arg, 3);
	for (i = 0; i < OBJ_NR; i++) {
		rc = daos_obj_verify(arg->coh, oids[i], DAOS_EPOCH_MAX);
		assert_rc_equal(rc, 0);
	}
}

static void
extend_indexes(void **state)
{
	test_arg_t	*arg = *state;
	daos_obj_id_t	oids[OBJ_NR];
	struct ioreq	req;
	int		i;
	int		j;
	int		k;
	int		rc;

	if (!test_runable(arg, 3))
		return;

	for (i = 0; i < OBJ_NR; i++) {
		oids[i] = daos_test_oid_gen(arg->coh, OC_RP_3G1, 0, 0,
					    arg->myrank);
		ioreq_init(&req, arg->coh, oids[i], DAOS_IOD_ARRAY, arg);

		/** Insert 10 records */
		print_message("Insert %d kv record in object "DF_OID"\n",
			      KEY_NR, DP_OID(oids[i]));

		for (j = 0; j < KEY_NR; j++) {
			char	key[32] = {0};

			sprintf(key, "dkey_2_%d", j);
			for (k = 0; k < 20; k++)
				insert_single(key, "a_key", k, "data",
					      strlen("data") + 1, DAOS_TX_NONE,
					      &req);
		}
		ioreq_fini(&req);
	}

	extend_single_pool_rank(arg, 3);
	for (i = 0; i < OBJ_NR; i++) {
		rc = daos_obj_verify(arg->coh, oids[i], DAOS_EPOCH_MAX);
		assert_rc_equal(rc, 0);
	}
}

static void
extend_large_rec(void **state)
{
	test_arg_t	*arg = *state;
	daos_obj_id_t	oids[OBJ_NR];
	struct ioreq	req;
	char		buffer[5000];
	int		i;
	int		j;
	int		rc;

	if (!test_runable(arg, 3))
		return;

	memset(buffer, 'a', 5000);
	for (i = 0; i < OBJ_NR; i++) {
		oids[i] = daos_test_oid_gen(arg->coh, OC_RP_3G1, 0, 0,
					    arg->myrank);
		ioreq_init(&req, arg->coh, oids[i], DAOS_IOD_ARRAY, arg);

		/** Insert 10 records */
		print_message("Insert %d kv record in object "DF_OID"\n",
			      KEY_NR, DP_OID(oids[i]));
		for (j = 0; j < KEY_NR; j++) {
			char	key[32] = {0};

			sprintf(key, "dkey_3_%d", j);
			insert_single(key, "a_key", 0, buffer, 5000,
				      DAOS_TX_NONE, &req);
		}
		ioreq_fini(&req);
	}

	extend_single_pool_rank(arg, 3);
	for (i = 0; i < OBJ_NR; i++) {
		rc = daos_obj_verify(arg->coh, oids[i], DAOS_EPOCH_MAX);
		assert_rc_equal(rc, 0);
	}
}

static void
extend_objects(void **state)
{
	test_arg_t	*arg = *state;
	struct ioreq	req;
	daos_obj_id_t	oids[OBJ_NR];
	int		i;

	if (!test_runable(arg, 3))
		return;

	for (i = 0; i < OBJ_NR; i++) {
		oids[i] = daos_test_oid_gen(arg->coh, OC_S1, 0,
					    0, arg->myrank);
		ioreq_init(&req, arg->coh, oids[i], DAOS_IOD_ARRAY, arg);

		insert_single("dkey", "akey", 0, "data", strlen("data") + 1,
			      DAOS_TX_NONE, &req);
		ioreq_fini(&req);
	}

	extend_single_pool_rank(arg, 3);

	for (i = 0; i < OBJ_NR; i++) {
		char buffer[16];

		ioreq_init(&req, arg->coh, oids[i], DAOS_IOD_ARRAY, arg);
		memset(buffer, 0, 16);
		lookup_single("dkey", "akey", 0, buffer, 16,
			      DAOS_TX_NONE, &req);
		assert_string_equal(buffer, "data");
		ioreq_fini(&req);
	}
}

struct extend_cb_arg{
	daos_obj_id_t	*oids;
	dfs_t		*dfs_mt;
};

static int
extend_punch_cb(void *arg)
{
	test_arg_t		*test_arg = arg;
	struct extend_cb_arg	*cb_arg = test_arg->rebuild_cb_arg;
	dfs_t			*dfs_mt = cb_arg->dfs_mt;
	daos_obj_id_t		*oids = cb_arg->oids;
	int			rc;
	int			i;

	print_message("sleep 10 seconds to start extend\n");
	sleep(10);
	/* Remove 20 files during extend */
	for (i = 0; i < 20; i++) {
		char filename[32];

		sprintf(filename, "test_file%d", i);
		rc = dfs_remove(dfs_mt, NULL, filename, true, &oids[i]);
		assert_int_equal(rc, 0);
	}

	daos_debug_set_params(test_arg->group, -1, DMG_KEY_FAIL_LOC, 0, 0, NULL);
	return 0;
}

void
dfs_extend_punch(void **state)
{
	test_arg_t	*arg = *state;
	dfs_t		*dfs_mt;
	daos_handle_t	co_hdl;
	dfs_obj_t	*obj;
	uuid_t		co_uuid;
	int		i;
	char		str[37];
	daos_obj_id_t	oids[20];
	struct extend_cb_arg cb_arg;
	dfs_attr_t attr = {};
	int		rc;

	attr.da_props = daos_prop_alloc(1);
	assert_non_null(attr.da_props);
	attr.da_props->dpp_entries[0].dpe_type = DAOS_PROP_CO_REDUN_LVL;
	attr.da_props->dpp_entries[0].dpe_val = DAOS_PROP_CO_REDUN_RANK;
	rc = dfs_cont_create(arg->pool.poh, &co_uuid, &attr, &co_hdl, &dfs_mt);
	daos_prop_free(attr.da_props);
	assert_int_equal(rc, 0);

	print_message("Created DFS Container "DF_UUIDF"\n", DP_UUID(co_uuid));

	/* Create 20 files */
	for (i = 0; i < 20; i++) {
		char filename[32];

		sprintf(filename, "test_file%d", i);
		rc = dfs_open(dfs_mt, NULL, filename, S_IFREG | S_IWUSR | S_IRUSR,
			      O_RDWR | O_CREAT, OC_S1, 1048576, NULL, &obj);
		assert_int_equal(rc, 0);
		dfs_obj2id(obj, &oids[i]);
		rc = dfs_release(obj);
		assert_int_equal(rc, 0);
	}

	cb_arg.oids = oids;
	cb_arg.dfs_mt = dfs_mt;

	arg->rebuild_cb = extend_punch_cb;
	arg->rebuild_cb_arg = &cb_arg;

	/* HOLD rebuild ULT */
	daos_debug_set_params(arg->group, -1, DMG_KEY_FAIL_LOC,
			      DAOS_REBUILD_TGT_SCAN_HANG | DAOS_FAIL_ALWAYS, 0, NULL);

	extend_single_pool_rank(arg, 3);

	rc = dfs_umount(dfs_mt);
	assert_int_equal(rc, 0);

	rc = daos_cont_close(co_hdl, NULL);
	assert_rc_equal(rc, 0);

	uuid_unparse(co_uuid, str);
	rc = daos_cont_destroy(arg->pool.poh, str, 1, NULL);
	assert_rc_equal(rc, 0);
}

int
extend_small_sub_setup(void **state)
{
	int rc;

	save_group_state(state);
	rc = test_setup(state, SETUP_CONT_CONNECT, true,
			EXTEND_SMALL_POOL_SIZE, 3, NULL);
	if (rc) {
		print_message("It can not create the pool with 3 ranks"
			      " probably due to not enough ranks %d\n", rc);
		return 0;
	}

	return rc;
}

/** create a new pool/container for each test */
static const struct CMUnitTest extend_tests[] = {
	{"EXTEND1: extend small rec multiple dkeys",
	 extend_dkeys, extend_small_sub_setup, test_teardown},
	{"EXTEND2: extend small rec multiple akeys",
	 extend_akeys, extend_small_sub_setup, test_teardown},
	{"EXTEND3: extend small rec multiple indexes",
	 extend_indexes, extend_small_sub_setup, test_teardown},
	{"EXTEND4: extend large rec single index",
	 extend_large_rec, extend_small_sub_setup, test_teardown},
	{"EXTEND5: extend multiple objects",
	 extend_objects, extend_small_sub_setup, test_teardown},
	{"EXTEND6: punch object during extend",
	 dfs_extend_punch, extend_small_sub_setup, test_teardown},
};

int
run_daos_extend_simple_test(int rank, int size, int *sub_tests,
			    int sub_tests_size)
{
	int rc = 0;

	par_barrier(PAR_COMM_WORLD);
	if (sub_tests_size == 0) {
		sub_tests_size = ARRAY_SIZE(extend_tests);
		sub_tests = NULL;
	}

	run_daos_sub_tests_only("DAOS_Extend_Simple", extend_tests,
				ARRAY_SIZE(extend_tests), sub_tests,
				sub_tests_size);

	par_barrier(PAR_COMM_WORLD);

	return rc;
}
