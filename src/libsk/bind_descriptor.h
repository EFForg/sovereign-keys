// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_BIND_DESCRIPTOR_H_
#define LIBSK_BIND_DESCRIPTOR_H_

#include <stddef.h>
#include <vector>

#include "descriptor.h"

namespace sk {

class Field;

// Describes the fields in a Bind log entry (see BindEntry).
class BindDescriptor : public Descriptor {
 public:
  // The type name for plaintext serialization.
  static const char* const kTypeName;

  // The type code for binary serialization.
  static const int kTypeId;

  // Indices of fields, used for fast accessors.
  enum {
    kV1CACertChain = 0,
    kV1IncludesSubdomains = 1,
    kV1Key = 2,
    kV1KeyType = 3,
    kV1Name = 4,
    kV1RebinderNames = 5,
    kV1SKSignature = 6,
    kV1SN = 7,
    kV1Services = 8,
    kV1Signature = 9,
    kV1TID = 10,
    kV1Timestamp = 11
  };

  explicit BindDescriptor(int version);
  virtual ~BindDescriptor();

  // Descriptor interface.
  virtual const char* GetTypeName() const OVERRIDE;
  virtual int GetTypeId() const OVERRIDE;
  virtual size_t GetNumFields() const OVERRIDE;
  virtual const Field& GetField(size_t index) const OVERRIDE;

  // Returns true iff this class supports |version|.
  static bool IsVersionSupported(int version);
};

}  // namespace sk

#endif  // LIBSK_BIND_DESCRIPTOR_H_
