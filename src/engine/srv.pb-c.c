/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: srv.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "srv.pb-c.h"
void   srv__notify_ready_req__init
                     (Srv__NotifyReadyReq         *message)
{
  static const Srv__NotifyReadyReq init_value = SRV__NOTIFY_READY_REQ__INIT;
  *message = init_value;
}
size_t srv__notify_ready_req__get_packed_size
                     (const Srv__NotifyReadyReq *message)
{
  assert(message->base.descriptor == &srv__notify_ready_req__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t srv__notify_ready_req__pack
                     (const Srv__NotifyReadyReq *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &srv__notify_ready_req__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t srv__notify_ready_req__pack_to_buffer
                     (const Srv__NotifyReadyReq *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &srv__notify_ready_req__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Srv__NotifyReadyReq *
       srv__notify_ready_req__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Srv__NotifyReadyReq *)
     protobuf_c_message_unpack (&srv__notify_ready_req__descriptor,
                                allocator, len, data);
}
void   srv__notify_ready_req__free_unpacked
                     (Srv__NotifyReadyReq *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &srv__notify_ready_req__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   srv__get_pool_svc_req__init
                     (Srv__GetPoolSvcReq         *message)
{
  static const Srv__GetPoolSvcReq init_value = SRV__GET_POOL_SVC_REQ__INIT;
  *message = init_value;
}
size_t srv__get_pool_svc_req__get_packed_size
                     (const Srv__GetPoolSvcReq *message)
{
  assert(message->base.descriptor == &srv__get_pool_svc_req__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t srv__get_pool_svc_req__pack
                     (const Srv__GetPoolSvcReq *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &srv__get_pool_svc_req__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t srv__get_pool_svc_req__pack_to_buffer
                     (const Srv__GetPoolSvcReq *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &srv__get_pool_svc_req__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Srv__GetPoolSvcReq *
       srv__get_pool_svc_req__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Srv__GetPoolSvcReq *)
     protobuf_c_message_unpack (&srv__get_pool_svc_req__descriptor,
                                allocator, len, data);
}
void   srv__get_pool_svc_req__free_unpacked
                     (Srv__GetPoolSvcReq *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &srv__get_pool_svc_req__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   srv__get_pool_svc_resp__init
                     (Srv__GetPoolSvcResp         *message)
{
  static const Srv__GetPoolSvcResp init_value = SRV__GET_POOL_SVC_RESP__INIT;
  *message = init_value;
}
size_t srv__get_pool_svc_resp__get_packed_size
                     (const Srv__GetPoolSvcResp *message)
{
  assert(message->base.descriptor == &srv__get_pool_svc_resp__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t srv__get_pool_svc_resp__pack
                     (const Srv__GetPoolSvcResp *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &srv__get_pool_svc_resp__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t srv__get_pool_svc_resp__pack_to_buffer
                     (const Srv__GetPoolSvcResp *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &srv__get_pool_svc_resp__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Srv__GetPoolSvcResp *
       srv__get_pool_svc_resp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Srv__GetPoolSvcResp *)
     protobuf_c_message_unpack (&srv__get_pool_svc_resp__descriptor,
                                allocator, len, data);
}
void   srv__get_pool_svc_resp__free_unpacked
                     (Srv__GetPoolSvcResp *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &srv__get_pool_svc_resp__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   srv__pool_find_by_label_req__init
                     (Srv__PoolFindByLabelReq         *message)
{
  static const Srv__PoolFindByLabelReq init_value = SRV__POOL_FIND_BY_LABEL_REQ__INIT;
  *message = init_value;
}
size_t srv__pool_find_by_label_req__get_packed_size
                     (const Srv__PoolFindByLabelReq *message)
{
  assert(message->base.descriptor == &srv__pool_find_by_label_req__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t srv__pool_find_by_label_req__pack
                     (const Srv__PoolFindByLabelReq *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &srv__pool_find_by_label_req__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t srv__pool_find_by_label_req__pack_to_buffer
                     (const Srv__PoolFindByLabelReq *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &srv__pool_find_by_label_req__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Srv__PoolFindByLabelReq *
       srv__pool_find_by_label_req__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Srv__PoolFindByLabelReq *)
     protobuf_c_message_unpack (&srv__pool_find_by_label_req__descriptor,
                                allocator, len, data);
}
void   srv__pool_find_by_label_req__free_unpacked
                     (Srv__PoolFindByLabelReq *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &srv__pool_find_by_label_req__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   srv__pool_find_by_label_resp__init
                     (Srv__PoolFindByLabelResp         *message)
{
  static const Srv__PoolFindByLabelResp init_value = SRV__POOL_FIND_BY_LABEL_RESP__INIT;
  *message = init_value;
}
size_t srv__pool_find_by_label_resp__get_packed_size
                     (const Srv__PoolFindByLabelResp *message)
{
  assert(message->base.descriptor == &srv__pool_find_by_label_resp__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t srv__pool_find_by_label_resp__pack
                     (const Srv__PoolFindByLabelResp *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &srv__pool_find_by_label_resp__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t srv__pool_find_by_label_resp__pack_to_buffer
                     (const Srv__PoolFindByLabelResp *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &srv__pool_find_by_label_resp__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Srv__PoolFindByLabelResp *
       srv__pool_find_by_label_resp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Srv__PoolFindByLabelResp *)
     protobuf_c_message_unpack (&srv__pool_find_by_label_resp__descriptor,
                                allocator, len, data);
}
void   srv__pool_find_by_label_resp__free_unpacked
                     (Srv__PoolFindByLabelResp *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &srv__pool_find_by_label_resp__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor srv__notify_ready_req__field_descriptors[8] =
{
  {
    "uri",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Srv__NotifyReadyReq, uri),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "nctxs",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(Srv__NotifyReadyReq, nctxs),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "drpcListenerSock",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Srv__NotifyReadyReq, drpclistenersock),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "instanceIdx",
    4,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(Srv__NotifyReadyReq, instanceidx),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "ntgts",
    5,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(Srv__NotifyReadyReq, ntgts),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "incarnation",
    6,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT64,
    0,   /* quantifier_offset */
    offsetof(Srv__NotifyReadyReq, incarnation),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "secondaryUris",
    7,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_STRING,
    offsetof(Srv__NotifyReadyReq, n_secondaryuris),
    offsetof(Srv__NotifyReadyReq, secondaryuris),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "secondaryNctxs",
    8,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_UINT32,
    offsetof(Srv__NotifyReadyReq, n_secondarynctxs),
    offsetof(Srv__NotifyReadyReq, secondarynctxs),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned srv__notify_ready_req__field_indices_by_name[] = {
  2,   /* field[2] = drpcListenerSock */
  5,   /* field[5] = incarnation */
  3,   /* field[3] = instanceIdx */
  1,   /* field[1] = nctxs */
  4,   /* field[4] = ntgts */
  7,   /* field[7] = secondaryNctxs */
  6,   /* field[6] = secondaryUris */
  0,   /* field[0] = uri */
};
static const ProtobufCIntRange srv__notify_ready_req__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 8 }
};
const ProtobufCMessageDescriptor srv__notify_ready_req__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "srv.NotifyReadyReq",
  "NotifyReadyReq",
  "Srv__NotifyReadyReq",
  "srv",
  sizeof(Srv__NotifyReadyReq),
  8,
  srv__notify_ready_req__field_descriptors,
  srv__notify_ready_req__field_indices_by_name,
  1,  srv__notify_ready_req__number_ranges,
  (ProtobufCMessageInit) srv__notify_ready_req__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor srv__get_pool_svc_req__field_descriptors[1] =
{
  {
    "uuid",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Srv__GetPoolSvcReq, uuid),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned srv__get_pool_svc_req__field_indices_by_name[] = {
  0,   /* field[0] = uuid */
};
static const ProtobufCIntRange srv__get_pool_svc_req__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor srv__get_pool_svc_req__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "srv.GetPoolSvcReq",
  "GetPoolSvcReq",
  "Srv__GetPoolSvcReq",
  "srv",
  sizeof(Srv__GetPoolSvcReq),
  1,
  srv__get_pool_svc_req__field_descriptors,
  srv__get_pool_svc_req__field_indices_by_name,
  1,  srv__get_pool_svc_req__number_ranges,
  (ProtobufCMessageInit) srv__get_pool_svc_req__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor srv__get_pool_svc_resp__field_descriptors[2] =
{
  {
    "status",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Srv__GetPoolSvcResp, status),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "svcreps",
    2,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_UINT32,
    offsetof(Srv__GetPoolSvcResp, n_svcreps),
    offsetof(Srv__GetPoolSvcResp, svcreps),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned srv__get_pool_svc_resp__field_indices_by_name[] = {
  0,   /* field[0] = status */
  1,   /* field[1] = svcreps */
};
static const ProtobufCIntRange srv__get_pool_svc_resp__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor srv__get_pool_svc_resp__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "srv.GetPoolSvcResp",
  "GetPoolSvcResp",
  "Srv__GetPoolSvcResp",
  "srv",
  sizeof(Srv__GetPoolSvcResp),
  2,
  srv__get_pool_svc_resp__field_descriptors,
  srv__get_pool_svc_resp__field_indices_by_name,
  1,  srv__get_pool_svc_resp__number_ranges,
  (ProtobufCMessageInit) srv__get_pool_svc_resp__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor srv__pool_find_by_label_req__field_descriptors[1] =
{
  {
    "label",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Srv__PoolFindByLabelReq, label),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned srv__pool_find_by_label_req__field_indices_by_name[] = {
  0,   /* field[0] = label */
};
static const ProtobufCIntRange srv__pool_find_by_label_req__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor srv__pool_find_by_label_req__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "srv.PoolFindByLabelReq",
  "PoolFindByLabelReq",
  "Srv__PoolFindByLabelReq",
  "srv",
  sizeof(Srv__PoolFindByLabelReq),
  1,
  srv__pool_find_by_label_req__field_descriptors,
  srv__pool_find_by_label_req__field_indices_by_name,
  1,  srv__pool_find_by_label_req__number_ranges,
  (ProtobufCMessageInit) srv__pool_find_by_label_req__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor srv__pool_find_by_label_resp__field_descriptors[3] =
{
  {
    "status",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Srv__PoolFindByLabelResp, status),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "uuid",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Srv__PoolFindByLabelResp, uuid),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "svcreps",
    3,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_UINT32,
    offsetof(Srv__PoolFindByLabelResp, n_svcreps),
    offsetof(Srv__PoolFindByLabelResp, svcreps),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned srv__pool_find_by_label_resp__field_indices_by_name[] = {
  0,   /* field[0] = status */
  2,   /* field[2] = svcreps */
  1,   /* field[1] = uuid */
};
static const ProtobufCIntRange srv__pool_find_by_label_resp__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor srv__pool_find_by_label_resp__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "srv.PoolFindByLabelResp",
  "PoolFindByLabelResp",
  "Srv__PoolFindByLabelResp",
  "srv",
  sizeof(Srv__PoolFindByLabelResp),
  3,
  srv__pool_find_by_label_resp__field_descriptors,
  srv__pool_find_by_label_resp__field_indices_by_name,
  1,  srv__pool_find_by_label_resp__number_ranges,
  (ProtobufCMessageInit) srv__pool_find_by_label_resp__init,
  NULL,NULL,NULL    /* reserved[123] */
};
