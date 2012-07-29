// Copyright 2012 the SK authors. All rights reserved.

#include "tfm.h"

#include <string>
#include <memory>
#include <vector>

#include "gtest/gtest.h"
#include "descriptor.h"
#include "slice.h"

using std::string;
using std::unique_ptr;

namespace sk {

TEST(TFMTest, Getters) {
  unique_ptr<TFM> tfm(TFM::ParseText(
    "TFM: 1\n"
    "Max-Published-SN: 42\n"
    "Max-Published-Timestamp: 1000\n"
    "Max-SN: 57\n"
    "Max-Timestamp: 1100\n"
    "Signature: Li4u\n"
    "TID: 0\n"
    "Timestamp: 2000\n"
    "\n"));
  ASSERT_TRUE(tfm.get() != NULL);
  ASSERT_TRUE(tfm->descriptor() != NULL);
  EXPECT_STREQ("TFM", tfm->descriptor()->GetTypeName());
  EXPECT_EQ(1, tfm->descriptor()->GetVersion());
  EXPECT_EQ(42U, tfm->max_published_sn());
  EXPECT_EQ(1000U, tfm->max_published_timestamp());
  EXPECT_EQ(57U, tfm->max_sn());
  EXPECT_EQ(1100U, tfm->max_timestamp());
  EXPECT_EQ("...", tfm->signature());
  EXPECT_EQ(0U, tfm->tid());
  EXPECT_EQ(2000U, tfm->timestamp());
}

TEST(TFMTest, Setters) {
  unique_ptr<TFM> tfm(new TFM(1));
  tfm->set_max_published_sn(42);
  tfm->set_max_published_timestamp(1000);
  tfm->set_max_sn(57);
  tfm->set_max_timestamp(1100);
  tfm->set_signature("...");
  tfm->set_tid(0);
  tfm->set_timestamp(2000);
  string out;
  tfm->AppendText(&out);
  EXPECT_EQ(
    "TFM: 1\n"
    "Max-Published-SN: 42\n"
    "Max-Published-Timestamp: 1000\n"
    "Max-SN: 57\n"
    "Max-Timestamp: 1100\n"
    "Signature: Li4u\n"
    "TID: 0\n"
    "Timestamp: 2000\n"
    "\n",
    out);
}

}  // namespace sk
