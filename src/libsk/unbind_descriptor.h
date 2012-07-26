// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_UNBIND_DESCRIPTOR_H_
#define LIBSK_UNBIND_DESCRIPTOR_H_

#include <stddef.h>
#include <vector>

#include "descriptor.h"

namespace sk {

class Field;

// Describes the fields in an Unbind log entry (see UnbindEntry).
class UnbindDescriptor : public Descriptor {
 public:
  // The type name for plaintext serialization.
  static const char* const kTypeName;

  // The type code for binary serialization.
  static const int kTypeId;

  // Indices of fields, used for fast accessors.
  enum {
    kLastSecureTimestamp,
    kName,
    kSKSignature,
    kSN,
    kSignature,
    kTID,
    kTimestamp
  };

  explicit UnbindDescriptor(int version);
  virtual ~UnbindDescriptor();

  // Descriptor interface.
  virtual const char* GetTypeName() const OVERRIDE;
  virtual int GetTypeId() const OVERRIDE;
  virtual size_t GetNumFields() const OVERRIDE;
  virtual const Field& GetField(size_t index) const OVERRIDE;

  // Returns true iff this class supports |version|.
  static bool IsVersionSupported(int version);
};

}  // namespace sk

#endif  // LIBSK_UNBIND_DESCRIPTOR_H_
