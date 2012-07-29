// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_ADD_ROOT_CA_DESCRIPTOR_H_
#define LIBSK_ADD_ROOT_CA_DESCRIPTOR_H_

#include <stddef.h>
#include <vector>

#include "descriptor.h"

namespace sk {

class Field;

// Describes the fields in a Add-Root-CA log entry (see AddRootCAEntry).
class AddRootCADescriptor : public Descriptor {
 public:
  enum {
    kCACert = 0,
    kSN = 1,
    kSignature = 2,
    kTID = 3,
    kTimestamp = 4
  };

  static const char* const kTypeName;
  static const int kTypeId;

  explicit AddRootCADescriptor(int version);
  virtual ~AddRootCADescriptor();

  // Descriptor interface.
  virtual const char* GetTypeName() const OVERRIDE;
  virtual int GetTypeId() const OVERRIDE;
  virtual size_t GetNumFields() const OVERRIDE;
  virtual const Field& GetField(size_t index) const OVERRIDE;
};

}  // namespace sk

#endif  // LIBSK_ADD_ROOT_CA_DESCRIPTOR_H_
