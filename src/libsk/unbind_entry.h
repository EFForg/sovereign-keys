// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_UNBIND_ENTRY_H_
#define LIBSK_UNBIND_ENTRY_H_

#include "unbind_descriptor.h"
#include "log_entry.h"
#include "slice.h"
#include "value_accessors.h"

namespace sk {

// Provides simplified accessors for Unbind entries.
class UnbindEntry : public LogEntry {
 public:
  virtual ~UnbindEntry();

  static UnbindEntry* ParseText(Slice in) {
    return static_cast<UnbindEntry*>(LogEntry::ParseText(in));
  }

  static UnbindEntry* ParseBinary(Slice* in) {
    return static_cast<UnbindEntry*>(LogEntry::ParseBinary(in));
  }

  PROPERTY(uint32_t, last_secure_timestamp,
      VALUE(Timestamp, UnbindDescriptor::kLastSecureTimestamp), timestamp);
  PROPERTY(const std::string&, name,
      VALUE(String, UnbindDescriptor::kName), text);
  PROPERTY(const std::string&, sk_signature,
      VALUE(Blob, UnbindDescriptor::kSKSignature), data);
  PROPERTY(uint64_t, sn,
      VALUE(Integer, UnbindDescriptor::kSN), value);
  PROPERTY(const std::string&, signature,
      VALUE(Blob, UnbindDescriptor::kSignature), data);
  PROPERTY(uint64_t, tid,
      VALUE(Integer, UnbindDescriptor::kTID), value);
  PROPERTY(uint32_t, timestamp,
      VALUE(Timestamp, UnbindDescriptor::kTimestamp), timestamp);
};
}  // namespace sk

#endif  // LIBSK_UNBIND_ENTRY_H_
