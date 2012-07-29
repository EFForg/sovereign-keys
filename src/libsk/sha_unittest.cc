// Copyright 2012 the SK authors. All rights reserved.

#include "sha.h"

#include <string>
#include <string.h>

#include "gtest/gtest.h"
#include "slice.h"
#include "test_util.h"

using sk::ComputeSHA256;
using sk::Slice;
using sk::testing::Unhex;
using std::string;

TEST(SHATest, SHA256) {
  // Generated using a non-OpenSSL SHA-256 implementation.
  EXPECT_EQ(Unhex("cc6004bb7ab40e52a92928146ffdb32f"
                  "10d48c599d5fbf9a7eaa4e3623ec7d69"),
            ComputeSHA256("testing 123"));
}
