// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_LOG_ENTRY_H_
#define LIBSK_LOG_ENTRY_H_

#include <algorithm>
#include <string>
#include <vector>

#include "util.h"

namespace sk {

class Descriptor;
class Slice;
class Value;

// LogEntry is the parent class for records in the SK distributed log.
// This class handles serialization and provides generic value accessors.
// Derived classes provide more efficient named accessors.
class LogEntry {
 public:
  typedef std::pair<Slice, Slice> KeyValuePair;
  virtual ~LogEntry();

  void AppendText(std::string* out) const;
  void AppendBinary(std::string* out) const;
  static LogEntry* ParseText(Slice in);
  static LogEntry* ParseBinary(Slice* in);

  const Descriptor* descriptor() const { return descriptor_; }

 protected:
  Value* value(size_t i) const { return values_[i]; }

 private:
  DISALLOW_EVIL_CONSTRUCTORS(LogEntry);

  // Takes ownership of descriptor.
  explicit LogEntry(const Descriptor* descriptor);

  static LogEntry* ParseTextFields(
      const Descriptor* descriptor,
      const std::vector<KeyValuePair>& fields);
  static LogEntry* ParseBinaryFields(
      const Descriptor* descriptor, Slice* in);

  // Description of this entry's name and fields.
  const Descriptor* descriptor_;

  // Values for each field in order.
  std::vector<Value*> values_;
};

}  // namespace sk

#endif  // LIBSK_LOG_ENTRY_H_
