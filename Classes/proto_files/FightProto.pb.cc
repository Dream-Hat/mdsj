// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: FightProto.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "FightProto.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace com {
namespace tiange {
namespace mdsj {
namespace proto {

namespace {


}  // namespace


void protobuf_AssignDesc_FightProto_2eproto() {
  protobuf_AddDesc_FightProto_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "FightProto.proto");
  GOOGLE_CHECK(file != NULL);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_FightProto_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
}

}  // namespace

void protobuf_ShutdownFile_FightProto_2eproto() {
}

void protobuf_AddDesc_FightProto_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\020FightProto.proto\022\025com.tiange.mdsj.prot"
    "o", 41);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "FightProto.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_FightProto_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_FightProto_2eproto {
  StaticDescriptorInitializer_FightProto_2eproto() {
    protobuf_AddDesc_FightProto_2eproto();
  }
} static_descriptor_initializer_FightProto_2eproto_;

// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace mdsj
}  // namespace tiange
}  // namespace com

// @@protoc_insertion_point(global_scope)
