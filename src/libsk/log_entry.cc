// Copyright 2012 the SK authors. All rights reserved.

#include "log_entry.h"

#include "descriptor.h"

namespace sk {

LogEntry::LogEntry(const Descriptor* descriptor)
  : Message(descriptor) {
}

LogEntry::~LogEntry() {
}

// static
LogEntry* LogEntry::ParseText(Slice in) {
  return static_cast<LogEntry*>(Message::ParseText(in));
}

// static
LogEntry* LogEntry::ParseBinary(Slice* in) {
  return static_cast<LogEntry*>(Message::ParseBinary(in));
}

}  // namespace sk
