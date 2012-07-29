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

}  // namespace sk
