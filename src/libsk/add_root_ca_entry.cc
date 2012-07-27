// Copyright 2012 the SK authors. All rights reserved.

#include "add_root_ca_entry.h"

#include "add_root_ca_descriptor.h"

namespace sk {

AddRootCAEntry::AddRootCAEntry(int version)
  : LogEntry(new AddRootCADescriptor(version)) {
}

AddRootCAEntry::~AddRootCAEntry() {
}

}  // namespace sk
