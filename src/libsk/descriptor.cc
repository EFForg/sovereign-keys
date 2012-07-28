// Copyright 2012 the SK authors. All rights reserved.

#include "descriptor.h"

#include "add_root_ca_descriptor.h"
#include "bind_descriptor.h"
#include "change_services_descriptor.h"
#include "rebind_descriptor.h"
#include "remove_root_ca_descriptor.h"
#include "slice.h"
#include "unbind_descriptor.h"

namespace sk {

Descriptor::Descriptor(int version)
  : version_(version) {
}

Descriptor::~Descriptor() {
}

// static
const Descriptor* Descriptor::GetByName(Slice name, int version) {
  if (name == BindDescriptor::kTypeName &&
      BindDescriptor::IsVersionSupported(version))
    return new BindDescriptor(version);
  else if (name == ChangeServicesDescriptor::kTypeName &&
      ChangeServicesDescriptor::IsVersionSupported(version))
    return new ChangeServicesDescriptor(version);
  else if (name == UnbindDescriptor::kTypeName &&
      UnbindDescriptor::IsVersionSupported(version))
    return new UnbindDescriptor(version);
  else if (name == RebindDescriptor::kTypeName &&
      RebindDescriptor::IsVersionSupported(version))
    return new RebindDescriptor(version);
  else if (name == AddRootCADescriptor::kTypeName &&
           AddRootCADescriptor::IsVersionSupported(version))
    return new AddRootCADescriptor(version);
  else if (name == RemoveRootCADescriptor::kTypeName &&
           RemoveRootCADescriptor::IsVersionSupported(version))
    return new RemoveRootCADescriptor(version);
  return NULL;
}

// static
const Descriptor* Descriptor::GetByType(int entry_type, int version) {
  if (entry_type == BindDescriptor::kTypeId &&
      BindDescriptor::IsVersionSupported(version))
    return new BindDescriptor(version);
  else if (entry_type == ChangeServicesDescriptor::kTypeId &&
      ChangeServicesDescriptor::IsVersionSupported(version))
    return new ChangeServicesDescriptor(version);
  else if (entry_type == UnbindDescriptor::kTypeId &&
      UnbindDescriptor::IsVersionSupported(version))
    return new UnbindDescriptor(version);
  else if (entry_type == RebindDescriptor::kTypeId &&
      RebindDescriptor::IsVersionSupported(version))
    return new RebindDescriptor(version);
  return NULL;
}
}  // namespace sk
