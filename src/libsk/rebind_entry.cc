// Copyright 2012 the SK authors. All rights reserved.

#include "rebind_entry.h"

#include "rebind_descriptor.h"

namespace sk {

RebindEntry::RebindEntry(int version)
  : LogEntry(new RebindDescriptor(version)) {
}

RebindEntry::~RebindEntry() {
}

}  // namespace sk
