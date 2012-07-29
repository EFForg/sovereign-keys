// Copyright 2012 the SK authors. All rights reserved.

#include "bind_entry.h"

#include "bind_descriptor.h"

namespace sk {

BindEntry::BindEntry(int version)
  : LogEntry(GetDescriptor(version)) {
}

BindEntry::~BindEntry() {
}

// static
const BindDescriptor* BindEntry::GetDescriptor(int version) {
  static BindDescriptor desc(1);
  if (version == 1)
    return &desc;
  return NULL;
}

}  // namespace sk
