// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_LOG_ENTRY_H_
#define LIBSK_LOG_ENTRY_H_

#include <string>

#include "message.h"
#include "slice.h"
#include "util.h"
#include "value.h"

namespace sk {

class Descriptor;

// LogEntry is the parent class for messages logged on a timeline.
class LogEntry : public Message {
 public:
  virtual ~LogEntry();

  // Factory methods for constructing derived class instances.
  static LogEntry* ParseText(Slice in);
  static LogEntry* ParseBinary(Slice* in);

  // All log entries have the fields SN, Signature, TID and Timestamp, so
  // derived entry classes must implement these accessors.
  virtual uint64_t sn() = 0;
  virtual void set_sn(uint64_t value) = 0;
  virtual const std::string& signature() = 0;
  virtual void set_signature(const std::string& data) = 0;
  virtual uint64_t tid() = 0;
  virtual void set_tid(uint64_t value) = 0;
  virtual uint32_t timestamp() = 0;
  virtual void set_timestamp(uint32_t timestamp) = 0;

 protected:
  explicit LogEntry(const Descriptor* descriptor);

 private:
  DISALLOW_EVIL_CONSTRUCTORS(LogEntry);
};

}  // namespace sk

#endif  // LIBSK_LOG_ENTRY_H_
