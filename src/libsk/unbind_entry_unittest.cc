// Copyright 2012 the SK authors. All rights reserved.

#include "unbind_entry.h"

#include <string>
#include <memory>

#include "gtest/gtest.h"
#include "descriptor.h"
#include "slice.h"

using std::string;
using std::unique_ptr;

namespace sk {

TEST(UnbindEntryTest, Accessors) {
  unique_ptr<UnbindEntry> entry(UnbindEntry::ParseText(
    "Unbind: 1\n"
    "Last-Secure-Timestamp: 1342885822\n"
    "Name: foo.example.com\n"
    "SK-Signature: Li4u\n"
    "SN: 42\n"
    "Signature: Li4u\n"
    "TID: 0\n"
    "Timestamp: 1342885825\n"
    "\n"));
  ASSERT_TRUE(entry.get() != NULL);
  ASSERT_TRUE(entry->descriptor() != NULL);
  EXPECT_STREQ("Unbind", entry->descriptor()->GetTypeName());
  EXPECT_EQ(1, entry->descriptor()->GetVersion());
  EXPECT_EQ(1342885822U, entry->last_secure_timestamp());
  EXPECT_EQ("foo.example.com", entry->name());
  EXPECT_EQ("...", entry->sk_signature());
  EXPECT_EQ(42U, entry->sn());
  EXPECT_EQ("...", entry->signature());
  EXPECT_EQ(0U, entry->tid());
  EXPECT_EQ(1342885825U, entry->timestamp());
}

TEST(UnbindEntryTest, Setters) {
  unique_ptr<UnbindEntry> entry(new UnbindEntry(1));
  entry->set_last_secure_timestamp(1342885822);
  entry->set_name("foo.example.com");
  entry->set_sk_signature("...");
  entry->set_sn(42);
  entry->set_signature("...");
  entry->set_tid(0);
  entry->set_timestamp(1342885825);
  string out;
  entry->AppendText(&out);
  EXPECT_EQ(
    "Unbind: 1\n"
    "Last-Secure-Timestamp: 1342885822\n"
    "Name: foo.example.com\n"
    "SK-Signature: Li4u\n"
    "SN: 42\n"
    "Signature: Li4u\n"
    "TID: 0\n"
    "Timestamp: 1342885825\n"
    "\n",
    out);
}

}  // namespace sk
