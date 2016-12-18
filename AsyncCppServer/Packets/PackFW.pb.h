// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: PackFW.proto

#ifndef PROTOBUF_PackFW_2eproto__INCLUDED
#define PROTOBUF_PackFW_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3000000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace ProtobufPackets {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_PackFW_2eproto();
void protobuf_AssignDesc_PackFW_2eproto();
void protobuf_ShutdownFile_PackFW_2eproto();

class PackHeaderIn;
class PackHeaderOut;

// ===================================================================

class PackHeaderIn : public ::google::protobuf::Message {
 public:
  PackHeaderIn();
  virtual ~PackHeaderIn();

  PackHeaderIn(const PackHeaderIn& from);

  inline PackHeaderIn& operator=(const PackHeaderIn& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const PackHeaderIn& default_instance();

  void Swap(PackHeaderIn* other);

  // implements Message ----------------------------------------------

  inline PackHeaderIn* New() const { return New(NULL); }

  PackHeaderIn* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const PackHeaderIn& from);
  void MergeFrom(const PackHeaderIn& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(PackHeaderIn* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional bool serverRead = 1;
  void clear_serverread();
  static const int kServerReadFieldNumber = 1;
  bool serverread() const;
  void set_serverread(bool value);

  // optional string locKey = 2;
  void clear_lockey();
  static const int kLocKeyFieldNumber = 2;
  const ::std::string& lockey() const;
  void set_lockey(const ::std::string& value);
  void set_lockey(const char* value);
  void set_lockey(const char* value, size_t size);
  ::std::string* mutable_lockey();
  ::std::string* release_lockey();
  void set_allocated_lockey(::std::string* lockey);

  // repeated uint32 sendToIDs = 3;
  int sendtoids_size() const;
  void clear_sendtoids();
  static const int kSendToIDsFieldNumber = 3;
  ::google::protobuf::uint32 sendtoids(int index) const;
  void set_sendtoids(int index, ::google::protobuf::uint32 value);
  void add_sendtoids(::google::protobuf::uint32 value);
  const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      sendtoids() const;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_sendtoids();

  // optional uint32 dataSize = 4;
  void clear_datasize();
  static const int kDataSizeFieldNumber = 4;
  ::google::protobuf::uint32 datasize() const;
  void set_datasize(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:ProtobufPackets.PackHeaderIn)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::google::protobuf::internal::ArenaStringPtr lockey_;
  bool serverread_;
  ::google::protobuf::uint32 datasize_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > sendtoids_;
  mutable int _sendtoids_cached_byte_size_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_PackFW_2eproto();
  friend void protobuf_AssignDesc_PackFW_2eproto();
  friend void protobuf_ShutdownFile_PackFW_2eproto();

  void InitAsDefaultInstance();
  static PackHeaderIn* default_instance_;
};
// -------------------------------------------------------------------

class PackHeaderOut : public ::google::protobuf::Message {
 public:
  PackHeaderOut();
  virtual ~PackHeaderOut();

  PackHeaderOut(const PackHeaderOut& from);

  inline PackHeaderOut& operator=(const PackHeaderOut& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const PackHeaderOut& default_instance();

  void Swap(PackHeaderOut* other);

  // implements Message ----------------------------------------------

  inline PackHeaderOut* New() const { return New(NULL); }

  PackHeaderOut* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const PackHeaderOut& from);
  void MergeFrom(const PackHeaderOut& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(PackHeaderOut* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string locKey = 1;
  void clear_lockey();
  static const int kLocKeyFieldNumber = 1;
  const ::std::string& lockey() const;
  void set_lockey(const ::std::string& value);
  void set_lockey(const char* value);
  void set_lockey(const char* value, size_t size);
  ::std::string* mutable_lockey();
  ::std::string* release_lockey();
  void set_allocated_lockey(::std::string* lockey);

  // optional uint32 sentFromID = 2;
  void clear_sentfromid();
  static const int kSentFromIDFieldNumber = 2;
  ::google::protobuf::uint32 sentfromid() const;
  void set_sentfromid(::google::protobuf::uint32 value);

  // optional uint32 dataSize = 3;
  void clear_datasize();
  static const int kDataSizeFieldNumber = 3;
  ::google::protobuf::uint32 datasize() const;
  void set_datasize(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:ProtobufPackets.PackHeaderOut)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::google::protobuf::internal::ArenaStringPtr lockey_;
  ::google::protobuf::uint32 sentfromid_;
  ::google::protobuf::uint32 datasize_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_PackFW_2eproto();
  friend void protobuf_AssignDesc_PackFW_2eproto();
  friend void protobuf_ShutdownFile_PackFW_2eproto();

  void InitAsDefaultInstance();
  static PackHeaderOut* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// PackHeaderIn

// optional bool serverRead = 1;
inline void PackHeaderIn::clear_serverread() {
  serverread_ = false;
}
inline bool PackHeaderIn::serverread() const {
  // @@protoc_insertion_point(field_get:ProtobufPackets.PackHeaderIn.serverRead)
  return serverread_;
}
inline void PackHeaderIn::set_serverread(bool value) {
  
  serverread_ = value;
  // @@protoc_insertion_point(field_set:ProtobufPackets.PackHeaderIn.serverRead)
}

// optional string locKey = 2;
inline void PackHeaderIn::clear_lockey() {
  lockey_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& PackHeaderIn::lockey() const {
  // @@protoc_insertion_point(field_get:ProtobufPackets.PackHeaderIn.locKey)
  return lockey_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void PackHeaderIn::set_lockey(const ::std::string& value) {
  
  lockey_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:ProtobufPackets.PackHeaderIn.locKey)
}
inline void PackHeaderIn::set_lockey(const char* value) {
  
  lockey_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:ProtobufPackets.PackHeaderIn.locKey)
}
inline void PackHeaderIn::set_lockey(const char* value, size_t size) {
  
  lockey_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:ProtobufPackets.PackHeaderIn.locKey)
}
inline ::std::string* PackHeaderIn::mutable_lockey() {
  
  // @@protoc_insertion_point(field_mutable:ProtobufPackets.PackHeaderIn.locKey)
  return lockey_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* PackHeaderIn::release_lockey() {
  
  return lockey_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void PackHeaderIn::set_allocated_lockey(::std::string* lockey) {
  if (lockey != NULL) {
    
  } else {
    
  }
  lockey_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), lockey);
  // @@protoc_insertion_point(field_set_allocated:ProtobufPackets.PackHeaderIn.locKey)
}

// repeated uint32 sendToIDs = 3;
inline int PackHeaderIn::sendtoids_size() const {
  return sendtoids_.size();
}
inline void PackHeaderIn::clear_sendtoids() {
  sendtoids_.Clear();
}
inline ::google::protobuf::uint32 PackHeaderIn::sendtoids(int index) const {
  // @@protoc_insertion_point(field_get:ProtobufPackets.PackHeaderIn.sendToIDs)
  return sendtoids_.Get(index);
}
inline void PackHeaderIn::set_sendtoids(int index, ::google::protobuf::uint32 value) {
  sendtoids_.Set(index, value);
  // @@protoc_insertion_point(field_set:ProtobufPackets.PackHeaderIn.sendToIDs)
}
inline void PackHeaderIn::add_sendtoids(::google::protobuf::uint32 value) {
  sendtoids_.Add(value);
  // @@protoc_insertion_point(field_add:ProtobufPackets.PackHeaderIn.sendToIDs)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
PackHeaderIn::sendtoids() const {
  // @@protoc_insertion_point(field_list:ProtobufPackets.PackHeaderIn.sendToIDs)
  return sendtoids_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
PackHeaderIn::mutable_sendtoids() {
  // @@protoc_insertion_point(field_mutable_list:ProtobufPackets.PackHeaderIn.sendToIDs)
  return &sendtoids_;
}

// optional uint32 dataSize = 4;
inline void PackHeaderIn::clear_datasize() {
  datasize_ = 0u;
}
inline ::google::protobuf::uint32 PackHeaderIn::datasize() const {
  // @@protoc_insertion_point(field_get:ProtobufPackets.PackHeaderIn.dataSize)
  return datasize_;
}
inline void PackHeaderIn::set_datasize(::google::protobuf::uint32 value) {
  
  datasize_ = value;
  // @@protoc_insertion_point(field_set:ProtobufPackets.PackHeaderIn.dataSize)
}

// -------------------------------------------------------------------

// PackHeaderOut

// optional string locKey = 1;
inline void PackHeaderOut::clear_lockey() {
  lockey_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& PackHeaderOut::lockey() const {
  // @@protoc_insertion_point(field_get:ProtobufPackets.PackHeaderOut.locKey)
  return lockey_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void PackHeaderOut::set_lockey(const ::std::string& value) {
  
  lockey_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:ProtobufPackets.PackHeaderOut.locKey)
}
inline void PackHeaderOut::set_lockey(const char* value) {
  
  lockey_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:ProtobufPackets.PackHeaderOut.locKey)
}
inline void PackHeaderOut::set_lockey(const char* value, size_t size) {
  
  lockey_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:ProtobufPackets.PackHeaderOut.locKey)
}
inline ::std::string* PackHeaderOut::mutable_lockey() {
  
  // @@protoc_insertion_point(field_mutable:ProtobufPackets.PackHeaderOut.locKey)
  return lockey_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* PackHeaderOut::release_lockey() {
  
  return lockey_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void PackHeaderOut::set_allocated_lockey(::std::string* lockey) {
  if (lockey != NULL) {
    
  } else {
    
  }
  lockey_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), lockey);
  // @@protoc_insertion_point(field_set_allocated:ProtobufPackets.PackHeaderOut.locKey)
}

// optional uint32 sentFromID = 2;
inline void PackHeaderOut::clear_sentfromid() {
  sentfromid_ = 0u;
}
inline ::google::protobuf::uint32 PackHeaderOut::sentfromid() const {
  // @@protoc_insertion_point(field_get:ProtobufPackets.PackHeaderOut.sentFromID)
  return sentfromid_;
}
inline void PackHeaderOut::set_sentfromid(::google::protobuf::uint32 value) {
  
  sentfromid_ = value;
  // @@protoc_insertion_point(field_set:ProtobufPackets.PackHeaderOut.sentFromID)
}

// optional uint32 dataSize = 3;
inline void PackHeaderOut::clear_datasize() {
  datasize_ = 0u;
}
inline ::google::protobuf::uint32 PackHeaderOut::datasize() const {
  // @@protoc_insertion_point(field_get:ProtobufPackets.PackHeaderOut.dataSize)
  return datasize_;
}
inline void PackHeaderOut::set_datasize(::google::protobuf::uint32 value) {
  
  datasize_ = value;
  // @@protoc_insertion_point(field_set:ProtobufPackets.PackHeaderOut.dataSize)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace ProtobufPackets

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_PackFW_2eproto__INCLUDED
