// Copyright 2012 the SK authors. All rights reserved.

#include "rebind_entry.h"

#include "rebind_descriptor.h"

namespace sk {

RebindEntry::RebindEntry(int version)
  : LogEntry(GetDescriptor(version)) {
}

RebindEntry::~RebindEntry() {
}

// static
const RebindDescriptor* RebindEntry::GetDescriptor(int version) {
  static RebindDescriptor desc(1);
  if (version == 1)
    return &desc;
  return NULL;
}

}  // namespace sk
