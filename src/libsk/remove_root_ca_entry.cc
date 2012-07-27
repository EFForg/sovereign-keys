// Copyright 2012 the SK authors. All rights reserved.

#include "remove_root_ca_entry.h"

#include "remove_root_ca_descriptor.h"

namespace sk {

RemoveRootCAEntry::RemoveRootCAEntry(int version)
  : LogEntry(new RemoveRootCADescriptor(version)) {
}

RemoveRootCAEntry::~RemoveRootCAEntry() {
}

}  // namespace sk
