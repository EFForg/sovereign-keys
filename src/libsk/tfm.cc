// Copyright 2012 the SK authors. All rights reserved.

#include "tfm.h"

#include "tfm_descriptor.h"

namespace sk {

TFM::TFM(int version)
  : Message(GetDescriptor(version)) {
}

TFM::~TFM() {
}

// static
const TFMDescriptor* TFM::GetDescriptor(int version) {
  static TFMDescriptor desc(1);
  if (version == 1)
    return &desc;
  return NULL;
}

}  // namespace sk
