// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_CHANGE_SERVICES_DESCRIPTOR_H_
#define LIBSK_CHANGE_SERVICES_DESCRIPTOR_H_

#include <stddef.h>
#include <vector>

#include "descriptor.h"

namespace sk {

class Field;

// Describes the fields in a Change-Services log entry (see
// ChangeServicesEntry).
class ChangeServicesDescriptor : public Descriptor {
 public:
  // The type name for plaintext serialization.
  static const char* const kTypeName;

  // The type code for binary serialization.
  static const int kTypeId;

  // Indices of fields, used for fast accessors.
  enum {
    kName = 0,
    kSKSignature = 1,
    kSN = 2,
    kServices = 3,
    kSignature = 4,
    kTID = 5,
    kTimestamp = 6
  };

  explicit ChangeServicesDescriptor(int version);
  virtual ~ChangeServicesDescriptor();

  // Descriptor interface.
  virtual const char* GetTypeName() const OVERRIDE;
  virtual int GetTypeId() const OVERRIDE;
  virtual size_t GetNumFields() const OVERRIDE;
  virtual const Field& GetField(size_t index) const OVERRIDE;

  // Returns true iff this class supports |version|.
  static bool IsVersionSupported(int version);
};

}  // namespace sk

#endif  // LIBSK_CHANGE_SERVICES_DESCRIPTOR_H_
