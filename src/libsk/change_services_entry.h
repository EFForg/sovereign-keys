// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_CHANGE_SERVICES_ENTRY_H_
#define LIBSK_CHANGE_SERVICES_ENTRY_H_

#include "change_services_descriptor.h"
#include "log_entry.h"
#include "slice.h"
#include "value_accessors.h"

namespace sk {

// Provides simplified accessors for ChangeServices entries.
class ChangeServicesEntry : public LogEntry {
 public:
  virtual ~ChangeServicesEntry();

  static ChangeServicesEntry* ParseText(Slice in) {
    return static_cast<ChangeServicesEntry*>(LogEntry::ParseText(in));
  }

  static ChangeServicesEntry* ParseBinary(Slice* in) {
    return static_cast<ChangeServicesEntry*>(LogEntry::ParseBinary(in));
  }

  PROPERTY(const std::string&, name,
      VALUE(String, ChangeServicesDescriptor::kName), text);
  PROPERTY(const std::string&, sk_signature,
      VALUE(Blob, ChangeServicesDescriptor::kSKSignature), data);
  PROPERTY(uint64_t, sn,
      VALUE(Integer, ChangeServicesDescriptor::kSN), value);
  PROPERTY(const std::vector<Service>&, services,
      VALUE(Services, ChangeServicesDescriptor::kServices), services);
  PROPERTY(const std::string&, signature,
      VALUE(Blob, ChangeServicesDescriptor::kSignature), data);
  PROPERTY(uint64_t, tid,
      VALUE(Integer, ChangeServicesDescriptor::kTID), value);
  PROPERTY(uint32_t, timestamp,
      VALUE(Timestamp, ChangeServicesDescriptor::kTimestamp), timestamp);
};
}  // namespace sk

#endif  // LIBSK_CHANGE_SERVICES_ENTRY_H_
