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
  static const char* const kTypeName;
  static const int kTypeId;
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
};

}  // namespace sk

#endif  // LIBSK_UNBIND_DESCRIPTOR_H_
