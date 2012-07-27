// Copyright 2012 the SK authors. All rights reserved.

#include "change_services_entry.h"

#include "change_services_descriptor.h"

namespace sk {

ChangeServicesEntry::ChangeServicesEntry(int version)
  : LogEntry(new ChangeServicesDescriptor(version)) {
}

ChangeServicesEntry::~ChangeServicesEntry() {
}

}  // namespace sk
