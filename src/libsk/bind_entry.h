// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_BIND_ENTRY_H_
#define LIBSK_BIND_ENTRY_H_

#include "bind_descriptor.h"
#include "log_entry.h"
#include "slice.h"
#include "value_accessors.h"

namespace sk {

// Provides simplified accessors for Bind entries.
class BindEntry : public LogEntry {
 public:
  explicit BindEntry(int version);
  virtual ~BindEntry();

  static BindEntry* ParseText(Slice in) {
    return static_cast<BindEntry*>(LogEntry::ParseText(in));
  }

  static BindEntry* ParseBinary(Slice* in) {
    return static_cast<BindEntry*>(LogEntry::ParseBinary(in));
  }

  PROPERTY(, const std::string&, ca_cert_chain,
           Blob, BindDescriptor::kCACertChain, data);
  PROPERTY(, bool, includes_subdomains,
           Boolean, BindDescriptor::kIncludesSubdomains, value);
  PROPERTY(, const std::string&, key,
           Blob, BindDescriptor::kKey, data);
  PROPERTY(, KeyTypeValue::KeyType, key_type,
           KeyType, BindDescriptor::kKeyType, key_type);
  PROPERTY(, const std::string&, name,
           String, BindDescriptor::kName, text);
  PROPERTY(, const std::vector<std::string>&, rebinder_names,
           RebinderNames, BindDescriptor::kRebinderNames, rebinder_names);
  PROPERTY(, const std::string&, sk_signature,
           Blob, BindDescriptor::kSKSignature, data);
  PROPERTY(virtual, uint64_t, sn,
           Integer, BindDescriptor::kSN, value);
  PROPERTY(, const std::vector<Service>&, services,
           Services, BindDescriptor::kServices, services);
  PROPERTY(virtual, const std::string&, signature,
           Blob, BindDescriptor::kSignature, data);
  PROPERTY(virtual, uint64_t, tid,
           Integer, BindDescriptor::kTID, value);
  PROPERTY(virtual, uint32_t, timestamp,
           Timestamp, BindDescriptor::kTimestamp, timestamp);
};
}  // namespace sk

#endif  // LIBSK_BIND_ENTRY_H_
