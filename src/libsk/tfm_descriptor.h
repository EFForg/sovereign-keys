// Copyright 2012 the SK authors. All rights reserved.

#ifndef TFM_DESCRIPTOR_H_
#define TFM_DESCRIPTOR_H_

#include <stddef.h>
#include "descriptor.h"

namespace sk {

// Describes the fields in a Timeline Freshness Message (see TFM).
class TFMDescriptor : public Descriptor {
 public:
  // The type name for plaintext serialization.
  static const char* const kTypeName;

  // The type code for binary serialization.
  static const int kTypeId;

  // Indices of fields, used for fast accessors.
  enum {
    kMaxPublishedSN = 0,
    kMaxPublishedTimestamp = 1,
    kMaxSN = 2,
    kMaxTimestamp = 3,
    kSignature = 4,
    kTID = 5,
    kTimestamp = 6
  };

  explicit TFMDescriptor(int version);
  virtual ~TFMDescriptor();

  // Descriptor interface.
  virtual const char* GetTypeName() const OVERRIDE;
  virtual int GetTypeId() const OVERRIDE;
  virtual size_t GetNumFields() const OVERRIDE;
  virtual const Field& GetField(size_t index) const OVERRIDE;

  // Returns true iff this class supports |version|.
  static bool IsVersionSupported(int version);
};

}  // namespace sk

#endif  // TFM_DESCRIPTOR_H_
