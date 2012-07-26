// Copyright 2012 the SK authors. All rights reserved.

#include "change_services_descriptor.h"

#include <memory>
#include <stddef.h>

#include "field.h"
#include "gtest/gtest.h"
#include "test_util.h"

using std::unique_ptr;

namespace sk {

TEST(ChangeServicesDescriptorTest, Sanity) {
  size_t prev_version_num_fields = 0;
  for (int version = 1; version < 255; version++) {
    if (ChangeServicesDescriptor::IsVersionSupported(version)) {
      unique_ptr<ChangeServicesDescriptor> desc(new ChangeServicesDescriptor(version));
      ASSERT_TRUE(desc.get() != NULL);
      EXPECT_STREQ("Change-Services", desc->GetTypeName());
      EXPECT_EQ(4, desc->GetTypeId());
      EXPECT_LE(prev_version_num_fields, desc->GetNumFields());
      EXPECT_TRUE(testing::CheckDescriptorFields(desc.get()));
      prev_version_num_fields = desc->GetNumFields();
    }
  }
}

TEST(ChangeServicesDescriptorTest, Fields) {
  ASSERT_TRUE(ChangeServicesDescriptor::IsVersionSupported(1));
  unique_ptr<ChangeServicesDescriptor> desc(new ChangeServicesDescriptor(1));
  EXPECT_STREQ("Name",
      desc->GetField(ChangeServicesDescriptor::kName).name);
  EXPECT_STREQ("SK-Signature",
      desc->GetField(ChangeServicesDescriptor::kSKSignature).name);
  EXPECT_STREQ("SN",
      desc->GetField(ChangeServicesDescriptor::kSN).name);
  EXPECT_STREQ("Services",
      desc->GetField(ChangeServicesDescriptor::kServices).name);
  EXPECT_STREQ("Signature",
      desc->GetField(ChangeServicesDescriptor::kSignature).name);
  EXPECT_STREQ("TID",
      desc->GetField(ChangeServicesDescriptor::kTID).name);
  EXPECT_STREQ("Timestamp",
      desc->GetField(ChangeServicesDescriptor::kTimestamp).name);
}

}  // namespace sk
