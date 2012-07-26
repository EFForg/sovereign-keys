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
  virtual ~RebindEntry();

  static RebindEntry* ParseText(Slice in) {
    return static_cast<RebindEntry*>(LogEntry::ParseText(in));
  }

  static RebindEntry* ParseBinary(Slice* in) {
    return static_cast<RebindEntry*>(LogEntry::ParseBinary(in));
  }

  PROPERTY(const std::string&, ca_cert_chain,
      VALUE(Blob, RebindDescriptor::kCACertChain), data);
  PROPERTY(bool, includes_subdomains,
      VALUE(Boolean, RebindDescriptor::kIncludesSubdomains), value);
  PROPERTY(const std::string&, key,
      VALUE(Blob, RebindDescriptor::kKey), data);
  PROPERTY(KeyTypeValue::KeyType, key_type,
      VALUE(KeyType, RebindDescriptor::kKeyType), key_type);
  PROPERTY(const std::string&, name,
      VALUE(String, RebindDescriptor::kName), text);
  PROPERTY(const std::string&, rebinder_name,
      VALUE(String, RebindDescriptor::kRebinderName), text);
  PROPERTY(const std::vector<std::string>&, rebinder_names,
      VALUE(RebinderNames, RebindDescriptor::kRebinderNames), rebinder_names);
  PROPERTY(const std::string&, rebinder_signature,
      VALUE(Blob, RebindDescriptor::kRebinderSignature), data);
  PROPERTY(const std::string&, sk_signature,
      VALUE(Blob, RebindDescriptor::kSKSignature), data);
  PROPERTY(uint64_t, sn,
      VALUE(Integer, RebindDescriptor::kSN), value);
  PROPERTY(const std::vector<Service>&, services,
      VALUE(Services, RebindDescriptor::kServices), services);
  PROPERTY(const std::string&, signature,
      VALUE(Blob, RebindDescriptor::kSignature), data);
  PROPERTY(uint64_t, tid,
      VALUE(Integer, RebindDescriptor::kTID), value);
  PROPERTY(uint32_t, timestamp,
      VALUE(Timestamp, RebindDescriptor::kTimestamp), timestamp);
};
}  // namespace sk

#endif  // LIBSK_REBIND_ENTRY_H_
