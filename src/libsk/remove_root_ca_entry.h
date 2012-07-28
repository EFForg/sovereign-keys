// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_remove_ROOT_CA_ENTRY_H_
#define LIBSK_remove_ROOT_CA_ENTRY_H_

#include "remove_root_ca_descriptor.h"
#include "log_entry.h"
#include "slice.h"
#include "value_accessors.h"

namespace sk {

// Provides simplified accessors for RemoveRootCA entries.
class RemoveRootCAEntry : public LogEntry {
 public:
  explicit RemoveRootCAEntry(int version);
  virtual ~RemoveRootCAEntry();

  static RemoveRootCAEntry* ParseText(Slice in) {
    return static_cast<RemoveRootCAEntry*>(LogEntry::ParseText(in));
  }

  static RemoveRootCAEntry* ParseBinary(Slice* in) {
    return static_cast<RemoveRootCAEntry*>(LogEntry::ParseBinary(in));
  }

  PROPERTY(, const std::string&, ca_cert_hash,
           Blob, RemoveRootCADescriptor::kCACertHash, data);
  PROPERTY(virtual, uint64_t, sn,
           Integer, RemoveRootCADescriptor::kSN, value);
  PROPERTY(virtual, const std::string&, signature,
           Blob, RemoveRootCADescriptor::kSignature, data);
  PROPERTY(virtual, uint64_t, tid,
           Integer, RemoveRootCADescriptor::kTID, value);
  PROPERTY(virtual, uint32_t, timestamp,
           Timestamp, RemoveRootCADescriptor::kTimestamp, timestamp);
};
}  // namespace sk

#endif  // LIBSK_remove_ROOT_CA_ENTRY_H_
