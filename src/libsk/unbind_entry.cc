// Copyright 2012 the SK authors. All rights reserved.

#include "unbind_entry.h"

#include "unbind_descriptor.h"

namespace sk {

UnbindEntry::UnbindEntry(int version)
  : LogEntry(GetDescriptor(version)) {
}

UnbindEntry::~UnbindEntry() {
}

// static
const UnbindDescriptor* UnbindEntry::GetDescriptor(int version) {
  static UnbindDescriptor desc(1);
  if (version == 1)
    return &desc;
  return NULL;
}

}  // namespace sk
