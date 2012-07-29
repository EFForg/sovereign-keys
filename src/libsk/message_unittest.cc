// Copyright 2012 the SK authors. All rights reserved.

#include "message.h"

#include <memory>
#include <stdio.h>
#include <string>
#include <string.h>

#include "gtest/gtest.h"
#include "bind_descriptor.h"
#include "descriptor.h"
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

TEST(MessageTest, AcceptsNULLDescriptor) {
  unique_ptr<Message> msg(new Message(NULL));
  ASSERT_TRUE(msg.get() != NULL);
  ASSERT_TRUE(msg->descriptor() == NULL);
}

}  // namespace sk
