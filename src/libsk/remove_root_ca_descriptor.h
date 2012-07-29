// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_REMOVE_ROOT_CA_DESCRIPTOR_H_
#define LIBSK_REMOVE_ROOT_CA_DESCRIPTOR_H_

#include <stddef.h>
#include <vector>

#include "descriptor.h"

namespace sk {

class Field;

// Describes the fields in a Remove-Root-CA log entry (see RemoveRootCAEntry).
class RemoveRootCADescriptor : public Descriptor {
 public:
  enum {
    kCACertHash = 0,
    kSN = 1,
    kSignature = 2,
    kTID = 3,
    kTimestamp = 4
  };

  static const char* const kTypeName;
  static const int kTypeId;

  explicit RemoveRootCADescriptor(int version);
  virtual ~RemoveRootCADescriptor();

  // Descriptor interface.
  virtual const char* GetTypeName() const OVERRIDE;
  virtual int GetTypeId() const OVERRIDE;
  virtual size_t GetNumFields() const OVERRIDE;
  virtual const Field& GetField(size_t index) const OVERRIDE;
};

}  // namespace sk

#endif  // LIBSK_REMOVE_ROOT_CA_DESCRIPTOR_H_
