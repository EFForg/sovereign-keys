// Copyright 2012 the SK authors. All rights reserved.

#include "change_services_entry.h"

#include "change_services_descriptor.h"

namespace sk {

ChangeServicesEntry::ChangeServicesEntry(int version)
  : LogEntry(GetDescriptor(version)) {
}

ChangeServicesEntry::~ChangeServicesEntry() {
}

// static
const ChangeServicesDescriptor* ChangeServicesEntry::GetDescriptor(int version) {
  static ChangeServicesDescriptor desc(1);
  if (version == 1)
    return &desc;
  return NULL;
}

}  // namespace sk
