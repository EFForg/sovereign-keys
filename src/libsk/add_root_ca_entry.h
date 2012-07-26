// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_ADD_ROOT_CA_ENTRY_H_
#define LIBSK_ADD_ROOT_CA_ENTRY_H_

#include "add_root_ca_descriptor.h"
#include "log_entry.h"
#include "slice.h"
#include "value_accessors.h"

namespace sk {

// Provides simplified accessors for AddRootCA entries.
class AddRootCAEntry : public LogEntry {
 public:
  virtual ~AddRootCAEntry();

  static AddRootCAEntry* ParseText(Slice in) {
    return static_cast<AddRootCAEntry*>(LogEntry::ParseText(in));
  }

  static AddRootCAEntry* ParseBinary(Slice* in) {
    return static_cast<AddRootCAEntry*>(LogEntry::ParseBinary(in));
  }

  PROPERTY(const std::string&, ca_cert,
      VALUE(Blob, AddRootCADescriptor::kCACert), data);
  PROPERTY(uint64_t, sn,
      VALUE(Integer, AddRootCADescriptor::kSN), value);
  PROPERTY(const std::string&, signature,
      VALUE(Blob, AddRootCADescriptor::kSignature), data);
  PROPERTY(uint64_t, tid,
      VALUE(Integer, AddRootCADescriptor::kTID), value);
  PROPERTY(uint32_t, timestamp,
      VALUE(Timestamp, AddRootCADescriptor::kTimestamp), timestamp);
};
}  // namespace sk

#endif  // LIBSK_ADD_ROOT_CA_ENTRY_H_
