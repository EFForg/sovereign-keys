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
  enum {
    kCACertChain = 0,
    kIncludesSubdomains = 1,
    kKey = 2,
    kKeyType = 3,
    kName = 4,
    kRebinderNames = 5,
    kSKSignature = 6,
    kSN = 7,
    kServices = 8,
    kSignature = 9,
    kTID = 10,
    kTimestamp = 11
  };

  static const char* const kTypeName;
  static const int kTypeId;

  explicit BindDescriptor(int version);
  virtual ~BindDescriptor();

  // Descriptor interface.
  virtual const char* GetTypeName() const OVERRIDE;
  virtual int GetTypeId() const OVERRIDE;
  virtual size_t GetNumFields() const OVERRIDE;
  virtual const Field& GetField(size_t index) const OVERRIDE;
};

}  // namespace sk

#endif  // LIBSK_BIND_DESCRIPTOR_H_
