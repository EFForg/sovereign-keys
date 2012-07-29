// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_REBIND_DESCRIPTOR_H_
#define LIBSK_REBIND_DESCRIPTOR_H_

#include <stddef.h>
#include <vector>

#include "descriptor.h"

namespace sk {

class Field;

// Describes the fields in a Rebind log entry (see RebindEntry).
class RebindDescriptor : public Descriptor {
 public:
  enum {
    kCACertChain = 0,
    kIncludesSubdomains = 1,
    kKey = 2,
    kKeyType = 3,
    kName = 4,
    kRebinderName = 5,
    kRebinderNames = 6,
    kRebinderSignature = 7,
    kSKSignature = 8,
    kSN = 9,
    kServices = 10,
    kSignature = 11,
    kTID = 12,
    kTimestamp = 13
  };

  static const char* const kTypeName;
  static const int kTypeId;

  explicit RebindDescriptor(int version);
  virtual ~RebindDescriptor();

  // Descriptor interface.
  virtual const char* GetTypeName() const OVERRIDE;
  virtual int GetTypeId() const OVERRIDE;
  virtual size_t GetNumFields() const OVERRIDE;
  virtual const Field& GetField(size_t index) const OVERRIDE;
};

}  // namespace sk

#endif  // LIBSK_REBIND_DESCRIPTOR_H_
