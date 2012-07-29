// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_REBIND_ENTRY_H_
#define LIBSK_REBIND_ENTRY_H_

#include "rebind_descriptor.h"
#include "log_entry.h"
#include "slice.h"
#include "value_accessors.h"

namespace sk {

// Provides simplified accessors for Rebind entries.
class RebindEntry : public LogEntry {
 public:
  explicit RebindEntry(int version);
  virtual ~RebindEntry();

  // Gets a descriptor for this message type.
  static const RebindDescriptor* GetDescriptor(int version);

  static RebindEntry* ParseText(Slice in) {
    return static_cast<RebindEntry*>(LogEntry::ParseText(in));
  }

  static RebindEntry* ParseBinary(Slice* in) {
    return static_cast<RebindEntry*>(LogEntry::ParseBinary(in));
  }

  PROPERTY(, const std::string&, ca_cert_chain,
           Blob, RebindDescriptor::kCACertChain, data);
  PROPERTY(, bool, includes_subdomains,
           Boolean, RebindDescriptor::kIncludesSubdomains, value);
  PROPERTY(, const std::string&, key,
           Blob, RebindDescriptor::kKey, data);
  PROPERTY(, KeyTypeValue::KeyType, key_type,
           KeyType, RebindDescriptor::kKeyType, key_type);
  PROPERTY(, const std::string&, name,
           String, RebindDescriptor::kName, text);
  PROPERTY(, const std::string&, rebinder_name,
           String, RebindDescriptor::kRebinderName, text);
  PROPERTY(, const std::vector<std::string>&, rebinder_names,
           RebinderNames, RebindDescriptor::kRebinderNames, rebinder_names);
  PROPERTY(, const std::string&, rebinder_signature,
           Blob, RebindDescriptor::kRebinderSignature, data);
  PROPERTY(, const std::string&, sk_signature,
           Blob, RebindDescriptor::kSKSignature, data);
  PROPERTY(virtual, uint64_t, sn,
           Integer, RebindDescriptor::kSN, value);
  PROPERTY(, const std::vector<Service>&, services,
           Services, RebindDescriptor::kServices, services);
  PROPERTY(virtual, const std::string&, signature,
           Blob, RebindDescriptor::kSignature, data);
  PROPERTY(virtual, uint64_t, tid,
           Integer, RebindDescriptor::kTID, value);
  PROPERTY(virtual, uint32_t, timestamp,
           Timestamp, RebindDescriptor::kTimestamp, timestamp);
};
}  // namespace sk

#endif  // LIBSK_REBIND_ENTRY_H_
