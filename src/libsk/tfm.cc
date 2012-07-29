// Copyright 2012 the SK authors. All rights reserved.

#include "tfm.h"

#include "tfm_descriptor.h"

namespace sk {

TFM::TFM(int version)
  : Message(new TFMDescriptor(version)) {
}

TFM::~TFM() {
}

}  // namespace sk
