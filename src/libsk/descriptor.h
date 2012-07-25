// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_DESCRIPTOR_H_
#define LIBSK_DESCRIPTOR_H_

#include "util.h"

namespace sk {

class Field;

// Interface for classes which expose details of each log entry type
// such as its name and fields.
class Descriptor {
 public:
  virtual ~Descriptor();

  // Returns the type name for canonical form serialization.
  virtual const char* GetTypeName() const = 0;

  // Returns the type id for binary serialization.
  virtual int GetTypeId() const = 0;

  // Returns the number of fields in the entry.
  virtual size_t GetNumFields() const = 0;

  // Returns the field at offset |index|.
  virtual const Field& GetField(size_t index) const = 0;

  // Returns the version of this entry.
  int GetVersion() const {
    return version_;
  }

 protected:
  explicit Descriptor(int version);

 private:
  DISALLOW_EVIL_CONSTRUCTORS(Descriptor);

  // Which version of the log entry this descriptor is for.
  int version_;
};

}  // namespace sk

#endif  // LIBSK_DESCRIPTOR_H_
