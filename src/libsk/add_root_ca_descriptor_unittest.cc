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
  unique_ptr<AddRootCADescriptor> desc(new AddRootCADescriptor(1));
  ASSERT_TRUE(desc.get() != NULL);
  EXPECT_STREQ("Add-Root-CA", desc->GetTypeName());
  EXPECT_EQ(6, desc->GetTypeId());
  EXPECT_TRUE(testing::CheckDescriptorFields(desc.get()));
}

TEST(AddRootCADescriptorTest, Fields) {
  unique_ptr<AddRootCADescriptor> desc(new AddRootCADescriptor(1));
  ASSERT_TRUE(desc.get() != NULL);
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
