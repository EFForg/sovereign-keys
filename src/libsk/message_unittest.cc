// Copyright 2012 the SK authors. All rights reserved.

#include "message.h"

#include <memory>
#include <stdio.h>
#include <string>
#include <string.h>

#include "gtest/gtest.h"
#include "bind_descriptor.h"
#include "descriptor.h"
#include "integer_value.h"
#include "slice.h"
#include "test_util.h"
#include "util.h"

using sk::testing::Unhex;
using std::string;
using std::unique_ptr;

namespace sk {
namespace {
Slice* TmpSlice(string value) {
  static Slice in(value);
  in = value;
  return &in;
}
}  // namespace

TEST(MessageTest, ParseText) {
  unique_ptr<Message> msg(Message::ParseText(
    "Bind: 1\n"
    "CA-Cert-Chain: Li4u\n"
    "Includes-Subdomains: 0\n"
    "Key: Li4u\n"
    "Key-Type: ECC\n"
    "Name: foo.example.com\n"
    "Rebinder-Names: bar.example.com,baz.example.com\n"
    "SK-Signature: Li4u\n"
    "SN: 42\n"
    "Services: https\n"
    "Signature: Li4u\n"
    "TID: 0\n"
    "Timestamp: 1342885825\n"
    "\n"));
  ASSERT_TRUE(msg.get() != NULL);
  ASSERT_TRUE(msg->descriptor() != NULL);
  EXPECT_STREQ("Bind", msg->descriptor()->GetTypeName());
  EXPECT_EQ(1, msg->descriptor()->GetVersion());
  msg.reset(Message::ParseText(
    "TFM: 1\n"
    "Max-Published-SN: 42\n"
    "Max-Published-Timestamp: 1000\n"
    "Max-SN: 57\n"
    "Max-Timestamp: 1100\n"
    "Signature: Li4u\n"
    "TID: 0\n"
    "Timestamp: 2000\n"
    "\n"));
  ASSERT_TRUE(msg.get() != NULL);
  ASSERT_TRUE(msg->descriptor() != NULL);
  ASSERT_STREQ("TFM", msg->descriptor()->GetTypeName());
  ASSERT_EQ(1, msg->descriptor()->GetVersion());
  msg.reset(Message::ParseText(
    "Change-Services: 1\n"
    "Name: foo.example.com\n"
    "SK-Signature: Li4u\n"
    "SN: 42\n"
    "Services: https\n"
    "Signature: Li4u\n"
    "TID: 0\n"
    "Timestamp: 1342885825\n"
    "\n"));
  ASSERT_TRUE(msg.get() != NULL);
  ASSERT_TRUE(msg->descriptor() != NULL);
  ASSERT_STREQ("Change-Services", msg->descriptor()->GetTypeName());
  ASSERT_EQ(1, msg->descriptor()->GetVersion());
  msg.reset(Message::ParseText(
    "Unbind: 1\n"
    "Last-Secure-Timestamp: 1342885822\n"
    "Name: foo.example.com\n"
    "SK-Signature: Li4u\n"
    "SN: 42\n"
    "Signature: Li4u\n"
    "TID: 0\n"
    "Timestamp: 1342885825\n"
    "\n"));
  ASSERT_TRUE(msg.get() != NULL);
  ASSERT_TRUE(msg->descriptor() != NULL);
  EXPECT_STREQ("Unbind", msg->descriptor()->GetTypeName());
  EXPECT_EQ(1, msg->descriptor()->GetVersion());
  msg.reset(Message::ParseText(
    "Rebind: 1\n"
    "CA-Cert-Chain: Li4u\n"
    "Includes-Subdomains: 0\n"
    "Key: Li4u\n"
    "Key-Type: ECC\n"
    "Name: foo.example.com\n"
    "Rebinder-Name: bar.example.com\n"
    "Rebinder-Names: bar.example.com,baz.example.com\n"
    "Rebinder-Signature: Li4u\n"
    "SK-Signature: Li4u\n"
    "SN: 42\n"
    "Services: https\n"
    "Signature: Li4u\n"
    "TID: 0\n"
    "Timestamp: 1342885825\n"
    "\n"));
  ASSERT_TRUE(msg.get() != NULL);
  ASSERT_TRUE(msg->descriptor() != NULL);
  EXPECT_STREQ("Rebind", msg->descriptor()->GetTypeName());
  EXPECT_EQ(1, msg->descriptor()->GetVersion());
  msg.reset(Message::ParseText(
    "Add-Root-CA: 1\n"
    "CA-Cert: Li4u\n"
    "SN: 42\n"
    "Signature: Li4u\n"
    "TID: 0\n"
    "Timestamp: 1342885825\n"
    "\n"));
  ASSERT_TRUE(msg.get() != NULL);
  ASSERT_TRUE(msg->descriptor() != NULL);
  EXPECT_STREQ("Add-Root-CA", msg->descriptor()->GetTypeName());
  EXPECT_EQ(1, msg->descriptor()->GetVersion());
  msg.reset(Message::ParseText(
    "Remove-Root-CA: 1\n"
    "CA-Cert-Hash: Li4u\n"
    "SN: 42\n"
    "Signature: Li4u\n"
    "TID: 0\n"
    "Timestamp: 1342885825\n"
    "\n"));
  ASSERT_TRUE(msg.get() != NULL);
  ASSERT_TRUE(msg->descriptor() != NULL);
  EXPECT_STREQ("Remove-Root-CA", msg->descriptor()->GetTypeName());
  EXPECT_EQ(1, msg->descriptor()->GetVersion());
}

TEST(MessageTest, ParseBinary) {
  unique_ptr<Message> msg(Message::ParseBinary(TmpSlice(Unhex(
    "0101032e2e2e00032e2e2e01666f6f2e6578616d706c652e636f6d006261"
    "722e6578616d706c652e636f6d2c62617a2e6578616d706c652e636f6d00"
    "032e2e2e2a687474707300032e2e2e00c1cf0a50"))));
  ASSERT_TRUE(msg.get() != NULL);
  ASSERT_TRUE(msg->descriptor() != NULL);
  ASSERT_STREQ("Bind", msg->descriptor()->GetTypeName());
  ASSERT_EQ(1, msg->descriptor()->GetVersion());
  msg.reset(Message::ParseBinary(TmpSlice(Unhex(
    "00012ae80739cc08032e2e2e00d0070000"))));
  ASSERT_TRUE(msg.get() != NULL);
  ASSERT_TRUE(msg->descriptor() != NULL);
  ASSERT_STREQ("TFM", msg->descriptor()->GetTypeName());
  ASSERT_EQ(1, msg->descriptor()->GetVersion());
  msg.reset(Message::ParseBinary(TmpSlice(Unhex(
    "0401666f6f2e6578616d706c652e636f6d00032e2e2e2a68747470730003"
    "2e2e2e00c1cf0a50"))));
  ASSERT_TRUE(msg.get() != NULL);
  ASSERT_TRUE(msg->descriptor() != NULL);
  ASSERT_STREQ("Change-Services", msg->descriptor()->GetTypeName());
  ASSERT_EQ(1, msg->descriptor()->GetVersion());
  msg.reset(Message::ParseBinary(TmpSlice(Unhex(
    "0201be9fab8005666f6f2e6578616d706c652e636f6d00032e2e2e2a032e"
    "2e2e00c1cf0a50"))));
  ASSERT_TRUE(msg.get() != NULL);
  ASSERT_TRUE(msg->descriptor() != NULL);
  ASSERT_STREQ("Unbind", msg->descriptor()->GetTypeName());
  ASSERT_EQ(1, msg->descriptor()->GetVersion());
  msg.reset(Message::ParseBinary(TmpSlice(Unhex(
    "0301032e2e2e00032e2e2e01666f6f2e6578616d706c652e636f6d006261"
    "722e6578616d706c652e636f6d006261722e6578616d706c652e636f6d2c"
    "62617a2e6578616d706c652e636f6d00032e2e2e032e2e2e2a6874747073"
    "00032e2e2e00c1cf0a50"))));
  ASSERT_TRUE(msg.get() != NULL);
  ASSERT_TRUE(msg->descriptor() != NULL);
  ASSERT_STREQ("Rebind", msg->descriptor()->GetTypeName());
  ASSERT_EQ(1, msg->descriptor()->GetVersion());
  msg.reset(Message::ParseBinary(TmpSlice(Unhex(
    "0601032e2e2e2a032e2e2e00c1cf0a50"))));
  ASSERT_TRUE(msg.get() != NULL);
  ASSERT_TRUE(msg->descriptor() != NULL);
  ASSERT_STREQ("Add-Root-CA", msg->descriptor()->GetTypeName());
  ASSERT_EQ(1, msg->descriptor()->GetVersion());
  msg.reset(Message::ParseBinary(TmpSlice(Unhex(
    "0701032e2e2e2a032e2e2e00c1cf0a50"))));
  ASSERT_TRUE(msg.get() != NULL);
  ASSERT_TRUE(msg->descriptor() != NULL);
  ASSERT_STREQ("Remove-Root-CA", msg->descriptor()->GetTypeName());
  ASSERT_EQ(1, msg->descriptor()->GetVersion());
}

// These *Errors tests exercise each condition in message.cc where parsing
// message text should fail. Since later conditions will generally reject
// partial messages even if earlier conditions are defective, a debugger or
// coverage tool should be used to verify these tests reliably.
TEST(MessageTest, ParseTextErrors) {
  unique_ptr<Message> msg(Message::ParseText(""));
  ASSERT_TRUE(msg.get() == NULL);
  msg.reset(Message::ParseText("\n"));
  ASSERT_TRUE(msg.get() == NULL);
  msg.reset(Message::ParseText("Bind\n"));
  ASSERT_TRUE(msg.get() == NULL);
  msg.reset(Message::ParseText("Bind: 1"));
  ASSERT_TRUE(msg.get() == NULL);
  msg.reset(Message::ParseText(
    "Bind\n"
    "Value: hey\n"
    "\n"));
  ASSERT_TRUE(msg.get() == NULL);
  msg.reset(Message::ParseText(
    "Bind: 1\n"
    "\n"));
  ASSERT_TRUE(msg.get() == NULL);
  msg.reset(Message::ParseText(
    "Bind: 01\n"
    "\n"));
  ASSERT_TRUE(msg.get() == NULL);
  msg.reset(Message::ParseText(
    "Bind: 1024\n"
    "\n"));
  ASSERT_TRUE(msg.get() == NULL);
  msg.reset(Message::ParseText(
    "Not-A-Real-Message: 1\n"
    "\n"));
  ASSERT_TRUE(msg.get() == NULL);
  msg.reset(Message::ParseText(
    "Bind: 42\n"
    "\n"));
  ASSERT_TRUE(msg.get() == NULL);
  msg.reset(Message::ParseText(
    "Bind: 1\n"
    "CA-Cert-Chain: Li4u\n"
    "\n"));
  ASSERT_TRUE(msg.get() == NULL);
  msg.reset(Message::ParseText(
    "Bind: 1\n"
    "Includes-Subdomains: 0\n"
    "CA-Cert-Chain: Li4u\n"
    "Key: Li4u\n"
    "Key-Type: ECC\n"
    "Name: foo.example.com\n"
    "Rebinder-Names: bar.example.com,baz.example.com\n"
    "SK-Signature: Li4u\n"
    "SN: 42\n"
    "Services: https\n"
    "Signature: Li4u\n"
    "TID: 0\n"
    "Timestamp: 1342885825\n"
    "\n"));
  ASSERT_TRUE(msg.get() == NULL);
  msg.reset(Message::ParseText(
    "Bind: 1\n"
    "CA-Cert-Chain: Li4u\n"
    "Includes-Subdomains: 27\n"
    "Key: Li4u\n"
    "Key-Type: ECC\n"
    "Name: foo.example.com\n"
    "Rebinder-Names: bar.example.com,baz.example.com\n"
    "SK-Signature: Li4u\n"
    "SN: 42\n"
    "Services: https\n"
    "Signature: Li4u\n"
    "TID: 0\n"
    "Timestamp: 1342885825\n"
    "\n"));
  ASSERT_TRUE(msg.get() == NULL);
}

TEST(MessageTest, ParseBinaryErrors) {
  unique_ptr<Message> msg(Message::ParseBinary(TmpSlice("")));
  ASSERT_TRUE(msg.get() == NULL);
  msg.reset(Message::ParseBinary(TmpSlice(Unhex("ff01"))));
  ASSERT_TRUE(msg.get() == NULL);
  msg.reset(Message::ParseBinary(TmpSlice(Unhex("ff01"))));
  ASSERT_TRUE(msg.get() == NULL);
  // The following tests break this valid bind entry, so make sure it's
  // valid to begin with.
  const char* kBindEntry =
    "0101032e2e2e00032e2e2e01666f6f2e6578616d706c652e636f6d006261"
    "722e6578616d706c652e636f6d2c62617a2e6578616d706c652e636f6d00"
    "032e2e2e2a687474707300032e2e2e00c1cf0a50";
  msg.reset(Message::ParseBinary(TmpSlice(Unhex(kBindEntry))));
  ASSERT_TRUE(msg.get() != NULL);
  msg.reset(Message::ParseBinary(TmpSlice(
    Unhex(string(kBindEntry, strlen(kBindEntry) - 8)))));
  ASSERT_TRUE(msg.get() == NULL);
  msg.reset(Message::ParseBinary(TmpSlice(
    Unhex(string(kBindEntry, strlen(kBindEntry) - 2)))));
  ASSERT_TRUE(msg.get() == NULL);
}

TEST(MessageTest, AppendText) {
  unique_ptr<Message> msg(Message::ParseText(
    "TFM: 1\n"
    "Max-Published-SN: 42\n"
    "Max-Published-Timestamp: 1000\n"
    "Max-SN: 57\n"
    "Max-Timestamp: 1100\n"
    "Signature: Li4u\n"
    "TID: 0\n"
    "Timestamp: 2000\n"
    "\n"));
  ASSERT_TRUE(msg.get() != NULL);
  string out;
  msg->AppendText(&out);
  EXPECT_EQ(
    "TFM: 1\n"
    "Max-Published-SN: 42\n"
    "Max-Published-Timestamp: 1000\n"
    "Max-SN: 57\n"
    "Max-Timestamp: 1100\n"
    "Signature: Li4u\n"
    "TID: 0\n"
    "Timestamp: 2000\n"
    "\n", out);
}

TEST(MessageTest, AppendBinary) {
  unique_ptr<Message> msg(Message::ParseText(
    "TFM: 1\n"
    "Max-Published-SN: 42\n"
    "Max-Published-Timestamp: 1000\n"
    "Max-SN: 57\n"
    "Max-Timestamp: 1100\n"
    "Signature: Li4u\n"
    "TID: 0\n"
    "Timestamp: 2000\n"
    "\n"));
  ASSERT_TRUE(msg.get() != NULL);
  string out;
  msg->AppendBinary(&out);
  EXPECT_EQ(Unhex("00012ae80739cc08032e2e2e00d0070000"), out);
}

TEST(MessageTest, AcceptsNULLDescriptor) {
  unique_ptr<Message> msg(new Message(NULL));
  ASSERT_TRUE(msg.get() != NULL);
  ASSERT_TRUE(msg->descriptor() == NULL);
}

TEST(MessageTest, GenericAccessors) {
  unique_ptr<Message> msg(Message::ParseText(
    "Remove-Root-CA: 1\n"
    "CA-Cert-Hash: Li4u\n"
    "SN: 42\n"
    "Signature: Li4u\n"
    "TID: 0\n"
    "Timestamp: 1342885825\n"
    "\n"));
  ASSERT_TRUE(msg.get() != NULL);
  ASSERT_TRUE(msg->descriptor() != NULL);
  ASSERT_TRUE(msg->value(0) != NULL);
  ASSERT_TRUE(msg->value(4) != NULL);
  IntegerValue* tid = new IntegerValue(100);
  msg->set_value(3, static_cast<Value*>(tid));
  ASSERT_EQ(tid, msg->value(3));
}

}  // namespace sk
