// Copyright 2012 the SK authors. All rights reserved.

#include "add_root_ca_descriptor.h"

#include <memory>
#include <stddef.h>

#include "field.h"
#include "gtest/gtest.h"
#include "test_util.h"

using std::unique_ptr;

namespace sk {

TEST(AddRootCADescriptorTest, Sanity) {
  size_t prev_version_num_fields = 0;
  for (int version = 1; version < 255; version++) {
    if (AddRootCADescriptor::IsVersionSupported(version)) {
      unique_ptr<AddRootCADescriptor> desc(new AddRootCADescriptor(version));
      ASSERT_TRUE(desc.get() != NULL);
      EXPECT_STREQ("Add-Root-CA", desc->GetTypeName());
      EXPECT_EQ(5, desc->GetTypeId());
      EXPECT_LE(prev_version_num_fields, desc->GetNumFields());
      EXPECT_TRUE(testing::CheckDescriptorFields(desc.get()));
      prev_version_num_fields = desc->GetNumFields();
    }
  }
}

TEST(AddRootCADescriptorTest, Fields) {
  ASSERT_TRUE(AddRootCADescriptor::IsVersionSupported(1));
  unique_ptr<AddRootCADescriptor> desc(new AddRootCADescriptor(1));
  EXPECT_STREQ("CA-Cert",
      desc->GetField(AddRootCADescriptor::kCACert).name);
  EXPECT_STREQ("SN",
      desc->GetField(AddRootCADescriptor::kSN).name);
  EXPECT_STREQ("Signature",
      desc->GetField(AddRootCADescriptor::kSignature).name);
  EXPECT_STREQ("TID",
      desc->GetField(AddRootCADescriptor::kTID).name);
  EXPECT_STREQ("Timestamp",
      desc->GetField(AddRootCADescriptor::kTimestamp).name);
}

}  // namespace sk
