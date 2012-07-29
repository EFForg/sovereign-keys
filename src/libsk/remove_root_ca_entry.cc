// Copyright 2012 the SK authors. All rights reserved.

#include "remove_root_ca_entry.h"

#include "remove_root_ca_descriptor.h"

namespace sk {

RemoveRootCAEntry::RemoveRootCAEntry(int version)
  : LogEntry(GetDescriptor(version)) {
}

RemoveRootCAEntry::~RemoveRootCAEntry() {
}

// static
const RemoveRootCADescriptor* RemoveRootCAEntry::GetDescriptor(int version) {
  static RemoveRootCADescriptor desc(1);
  if (version == 1)
    return &desc;
  return NULL;
}

}  // namespace sk
