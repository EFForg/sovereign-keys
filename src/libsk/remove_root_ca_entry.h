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
  virtual ~RemoveRootCAEntry();

  static RemoveRootCAEntry* ParseText(Slice in) {
    return static_cast<RemoveRootCAEntry*>(LogEntry::ParseText(in));
  }

  static RemoveRootCAEntry* ParseBinary(Slice* in) {
    return static_cast<RemoveRootCAEntry*>(LogEntry::ParseBinary(in));
  }

  PROPERTY(const std::string&, ca_cert_hash,
      VALUE(Blob, RemoveRootCADescriptor::kCACertHash), data);
  PROPERTY(uint64_t, sn,
      VALUE(Integer, RemoveRootCADescriptor::kSN), value);
  PROPERTY(const std::string&, signature,
      VALUE(Blob, RemoveRootCADescriptor::kSignature), data);
  PROPERTY(uint64_t, tid,
      VALUE(Integer, RemoveRootCADescriptor::kTID), value);
  PROPERTY(uint32_t, timestamp,
      VALUE(Timestamp, RemoveRootCADescriptor::kTimestamp), timestamp);
};
}  // namespace sk

#endif  // LIBSK_remove_ROOT_CA_ENTRY_H_
