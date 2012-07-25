// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_BIND_ENTRY_H_
#define LIBSK_BIND_ENTRY_H_

#include "bind_descriptor.h"
#include "log_entry.h"
#include "slice.h"
#include "value_accessors.h"

namespace sk {

// Provides simplified accessors for version 1 Bind entries.
class BindV1Entry : public LogEntry {
 public:
  virtual ~BindV1Entry();

  static BindV1Entry* ParseText(Slice in) {
    return static_cast<BindV1Entry*>(LogEntry::ParseText(in));
  }

  static BindV1Entry* ParseBinary(Slice* in) {
    return static_cast<BindV1Entry*>(LogEntry::ParseBinary(in));
  }

  PROPERTY(const std::string&, ca_cert_chain,
      VALUE(Blob, BindDescriptor::kV1CACertChain), data);
  PROPERTY(bool, includes_subdomains,
      VALUE(Boolean, BindDescriptor::kV1IncludesSubdomains), value);
  PROPERTY(const std::string&, key,
      VALUE(Blob, BindDescriptor::kV1Key), data);
  PROPERTY(KeyTypeValue::KeyType, key_type,
      VALUE(KeyType, BindDescriptor::kV1KeyType), key_type);
  PROPERTY(const std::string&, name,
      VALUE(String, BindDescriptor::kV1Name), text);
  PROPERTY(const std::vector<std::string>&, rebinder_names,
      VALUE(RebinderNames, BindDescriptor::kV1RebinderNames), rebinder_names);
  PROPERTY(const std::string&, sk_signature,
      VALUE(Blob, BindDescriptor::kV1SKSignature), data);
  PROPERTY(uint64_t, sn,
      VALUE(Integer, BindDescriptor::kV1SN), value);
  PROPERTY(const std::vector<Service>&, services,
      VALUE(Services, BindDescriptor::kV1Services), services);
  PROPERTY(const std::string&, signature,
      VALUE(Blob, BindDescriptor::kV1Signature), data);
  PROPERTY(uint32_t, timestamp,
      VALUE(Timestamp, BindDescriptor::kV1Timestamp), timestamp);
};
}  // namespace sk

#endif  // LIBSK_BIND_ENTRY_H_
