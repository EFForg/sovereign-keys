// Copyright 2012 the SK authors. All rights reserved.

#include "bind_descriptor.h"

#include <memory>
#include <stddef.h>

#include "field.h"
#include "gtest/gtest.h"
#include "test_util.h"

using std::unique_ptr;

namespace sk {

TEST(BindDescriptorTest, Sanity) {
  unique_ptr<BindDescriptor> desc(new BindDescriptor(1));
  ASSERT_TRUE(desc.get() != NULL);
  EXPECT_STREQ("Bind", desc->GetTypeName());
  EXPECT_EQ(1, desc->GetTypeId());
  EXPECT_TRUE(testing::CheckDescriptorFields(desc.get()));
}

TEST(BindDescriptorTest, Fields) {
  unique_ptr<BindDescriptor> desc(new BindDescriptor(1));
  ASSERT_TRUE(desc.get() != NULL);
  EXPECT_STREQ("CA-Cert-Chain",
      desc->GetField(BindDescriptor::kCACertChain).name);
  EXPECT_STREQ("Includes-Subdomains",
      desc->GetField(BindDescriptor::kIncludesSubdomains).name);
  EXPECT_STREQ("Key",
      desc->GetField(BindDescriptor::kKey).name);
  EXPECT_STREQ("Key-Type",
      desc->GetField(BindDescriptor::kKeyType).name);
  EXPECT_STREQ("Name",
      desc->GetField(BindDescriptor::kName).name);
  EXPECT_STREQ("Rebinder-Names",
      desc->GetField(BindDescriptor::kRebinderNames).name);
  EXPECT_STREQ("SK-Signature",
      desc->GetField(BindDescriptor::kSKSignature).name);
  EXPECT_STREQ("SN",
      desc->GetField(BindDescriptor::kSN).name);
  EXPECT_STREQ("Services",
      desc->GetField(BindDescriptor::kServices).name);
  EXPECT_STREQ("Signature",
      desc->GetField(BindDescriptor::kSignature).name);
  EXPECT_STREQ("TID",
      desc->GetField(BindDescriptor::kTID).name);
  EXPECT_STREQ("Timestamp",
      desc->GetField(BindDescriptor::kTimestamp).name);
}

}  // namespace sk
