// Copyright 2012 the SK authors. All rights reserved.

#include "add_root_ca_entry.h"

#include "add_root_ca_descriptor.h"

namespace sk {

AddRootCAEntry::AddRootCAEntry(int version)
  : LogEntry(GetDescriptor(version)) {
}

AddRootCAEntry::~AddRootCAEntry() {
}

// static
const AddRootCADescriptor* AddRootCAEntry::GetDescriptor(int version) {
  static AddRootCADescriptor desc(1);
  if (version == 1)
    return &desc;
  return NULL;
}

}  // namespace sk
