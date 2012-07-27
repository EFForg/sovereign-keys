// Copyright 2012 the SK authors. All rights reserved.

#include "bind_entry.h"

#include "bind_descriptor.h"

namespace sk {

BindEntry::BindEntry(int version)
  : LogEntry(new BindDescriptor(version)) {
}

BindEntry::~BindEntry() {
}

}  // namespace sk
