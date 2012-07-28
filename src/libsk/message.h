// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_MESSAGE_H_
#define LIBSK_MESSAGE_H_

#include <algorithm>
#include <string>
#include <vector>

#include "slice.h"
#include "util.h"
#include "value.h"

namespace sk {

class Descriptor;

// Message is the parent class for serializable records in the SK system.
// This class handles serialization and provides generic value accessors.
// Derived classes provide more efficient named accessors.
class Message {
 public:
  typedef std::pair<Slice, Slice> KeyValuePair;
  virtual ~Message();

  // Takes ownership of descriptor.
  explicit Message(const Descriptor* descriptor);

  static Message* ParseText(Slice in);
  static Message* ParseBinary(Slice* in);

  void AppendText(std::string* out) const;
  void AppendBinary(std::string* out) const;

  const Descriptor* descriptor() const { return descriptor_; }

  // Retains ownership of returned pointer.
  Value* value(size_t i) const { return values_[i]; }

  // Takes ownership of value.
  void set_value(size_t i, Value* value) {
    delete values_[i];
    values_[i] = value;
  }

 private:
  DISALLOW_EVIL_CONSTRUCTORS(Message);

  static Message* ParseTextFields(
      const Descriptor* descriptor,
      const std::vector<KeyValuePair>& fields);
  static Message* ParseBinaryFields(
      const Descriptor* descriptor, Slice* in);

  // Description of this message's name and fields.
  const Descriptor* descriptor_;

  // Values for each field in order.
  std::vector<Value*> values_;
};

}  // namespace sk

#endif  // LIBSK_MESSAGE_H_
