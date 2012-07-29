// Copyright 2012 the SK authors. All rights reserved.

#include "descriptor.h"

#include "add_root_ca_descriptor.h"
#include "bind_descriptor.h"
#include "change_services_descriptor.h"
#include "rebind_descriptor.h"
#include "remove_root_ca_descriptor.h"
#include "slice.h"
#include "tfm_descriptor.h"
#include "unbind_descriptor.h"

namespace sk {

Descriptor::Descriptor(int version)
  : version_(version) {
}

Descriptor::~Descriptor() {
}

// static
const Descriptor* Descriptor::GetByName(Slice name, int version) {
#define BUILD(type) \
  if (name == type::kTypeName && type::IsVersionSupported(version)) \
    return new type(version);
  BUILD(BindDescriptor);
  BUILD(ChangeServicesDescriptor);
  BUILD(UnbindDescriptor);
  BUILD(RebindDescriptor);
  BUILD(AddRootCADescriptor);
  BUILD(RemoveRootCADescriptor);
  BUILD(TFMDescriptor);
  return NULL;
#undef BUILD
}

// static
const Descriptor* Descriptor::GetByType(int entry_type, int version) {
#define BUILD(type) \
  if (entry_type == type::kTypeId && type::IsVersionSupported(version)) \
    return new type(version);
  BUILD(BindDescriptor);
  BUILD(ChangeServicesDescriptor);
  BUILD(UnbindDescriptor);
  BUILD(RebindDescriptor);
  BUILD(AddRootCADescriptor);
  BUILD(RemoveRootCADescriptor);
  BUILD(TFMDescriptor);
  return NULL;
#undef BUILD
}
}  // namespace sk
