/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: chainmaker_network.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "chainmaker_network.pb-c.h"
void   common__chainmaker_networks__init
                     (Common__ChainmakerNetworks         *message)
{
  static const Common__ChainmakerNetworks init_value = COMMON__CHAINMAKER_NETWORKS__INIT;
  *message = init_value;
}
size_t common__chainmaker_networks__get_packed_size
                     (const Common__ChainmakerNetworks *message)
{
  assert(message->base.descriptor == &common__chainmaker_networks__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t common__chainmaker_networks__pack
                     (const Common__ChainmakerNetworks *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &common__chainmaker_networks__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t common__chainmaker_networks__pack_to_buffer
                     (const Common__ChainmakerNetworks *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &common__chainmaker_networks__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Common__ChainmakerNetworks *
       common__chainmaker_networks__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Common__ChainmakerNetworks *)
     protobuf_c_message_unpack (&common__chainmaker_networks__descriptor,
                                allocator, len, data);
}
void   common__chainmaker_networks__free_unpacked
                     (Common__ChainmakerNetworks *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &common__chainmaker_networks__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   common__chainmaker_network_data__init
                     (Common__ChainmakerNetworkData         *message)
{
  static const Common__ChainmakerNetworkData init_value = COMMON__CHAINMAKER_NETWORK_DATA__INIT;
  *message = init_value;
}
size_t common__chainmaker_network_data__get_packed_size
                     (const Common__ChainmakerNetworkData *message)
{
  assert(message->base.descriptor == &common__chainmaker_network_data__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t common__chainmaker_network_data__pack
                     (const Common__ChainmakerNetworkData *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &common__chainmaker_network_data__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t common__chainmaker_network_data__pack_to_buffer
                     (const Common__ChainmakerNetworkData *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &common__chainmaker_network_data__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Common__ChainmakerNetworkData *
       common__chainmaker_network_data__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Common__ChainmakerNetworkData *)
     protobuf_c_message_unpack (&common__chainmaker_network_data__descriptor,
                                allocator, len, data);
}
void   common__chainmaker_network_data__free_unpacked
                     (Common__ChainmakerNetworkData *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &common__chainmaker_network_data__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor common__chainmaker_networks__field_descriptors[2] =
{
  {
    "networkNum",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(Common__ChainmakerNetworks, networknum),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "networks",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Common__ChainmakerNetworks, networks),
    &common__chainmaker_network_data__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned common__chainmaker_networks__field_indices_by_name[] = {
  0,   /* field[0] = networkNum */
  1,   /* field[1] = networks */
};
static const ProtobufCIntRange common__chainmaker_networks__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor common__chainmaker_networks__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "common.chainmakerNetworks",
  "ChainmakerNetworks",
  "Common__ChainmakerNetworks",
  "common",
  sizeof(Common__ChainmakerNetworks),
  2,
  common__chainmaker_networks__field_descriptors,
  common__chainmaker_networks__field_indices_by_name,
  1,  common__chainmaker_networks__number_ranges,
  (ProtobufCMessageInit) common__chainmaker_networks__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor common__chainmaker_network_data__field_descriptors[10] =
{
  {
    "index",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(Common__ChainmakerNetworkData, index),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "client_member_type",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(Common__ChainmakerNetworkData, client_member_type),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "client_sign_cert_content",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Common__ChainmakerNetworkData, client_sign_cert_content),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "node_url",
    4,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Common__ChainmakerNetworkData, node_url),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "host_name",
    5,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Common__ChainmakerNetworkData, host_name),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "chain_id",
    6,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Common__ChainmakerNetworkData, chain_id),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "org_id",
    7,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Common__ChainmakerNetworkData, org_id),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "ca_tls_cert_content",
    8,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Common__ChainmakerNetworkData, ca_tls_cert_content),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "client_tls_cert_content",
    9,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Common__ChainmakerNetworkData, client_tls_cert_content),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "client_tls_privkey_data",
    10,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Common__ChainmakerNetworkData, client_tls_privkey_data),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned common__chainmaker_network_data__field_indices_by_name[] = {
  7,   /* field[7] = ca_tls_cert_content */
  5,   /* field[5] = chain_id */
  1,   /* field[1] = client_member_type */
  2,   /* field[2] = client_sign_cert_content */
  8,   /* field[8] = client_tls_cert_content */
  9,   /* field[9] = client_tls_privkey_data */
  4,   /* field[4] = host_name */
  0,   /* field[0] = index */
  3,   /* field[3] = node_url */
  6,   /* field[6] = org_id */
};
static const ProtobufCIntRange common__chainmaker_network_data__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 10 }
};
const ProtobufCMessageDescriptor common__chainmaker_network_data__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "common.chainmakerNetworkData",
  "ChainmakerNetworkData",
  "Common__ChainmakerNetworkData",
  "common",
  sizeof(Common__ChainmakerNetworkData),
  10,
  common__chainmaker_network_data__field_descriptors,
  common__chainmaker_network_data__field_indices_by_name,
  1,  common__chainmaker_network_data__number_ranges,
  (ProtobufCMessageInit) common__chainmaker_network_data__init,
  NULL,NULL,NULL    /* reserved[123] */
};