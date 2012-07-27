// Copyright 2012 the SK authors. All rights reserved.

#include "unbind_entry.h"

#include "unbind_descriptor.h"

namespace sk {

UnbindEntry::UnbindEntry(int version)
  : LogEntry(new UnbindDescriptor(version)) {
}

UnbindEntry::~UnbindEntry() {
}

}  // namespace sk
