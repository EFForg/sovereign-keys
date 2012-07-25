#include "log_entry.h"

#include <stdio.h>
#include <string>
#include <memory>

#include "gtest/gtest.h"
#include "bind_descriptor.h"
#include "descriptor.h"
#include "slice.h"
#include "util.h"

using std::string;
using std::unique_ptr;

namespace sk {

TEST(LogEntryTest, BindV1TextEncoding) {
  unique_ptr<LogEntry> entry(LogEntry::ParseText(
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
    "Timestamp: 1342885825\n"
    "\n"));
  ASSERT_TRUE(entry->descriptor() != NULL);
  EXPECT_STREQ("Bind", entry->descriptor()->GetTypeName());
  EXPECT_EQ(1, entry->descriptor()->GetVersion());
  string out;
  entry->AppendText(&out);
  EXPECT_EQ(
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
    "Timestamp: 1342885825\n"
    "\n", out);
}

TEST(LogEntryTest, BindV1BinaryEncoding) {
  const uint8_t kBindEntry[] = {
    0x00, 0x01, 0x03, 0x2e, 0x2e, 0x2e, 0x00, 0x03, 0x2e, 0x2e, 0x2e,
    0x01, 0x66, 0x6f, 0x6f, 0x2e, 0x65, 0x78, 0x61, 0x6d, 0x70, 0x6c,
    0x65, 0x2e, 0x63, 0x6f, 0x6d, 0x00, 0x62, 0x61, 0x72, 0x2e, 0x65,
    0x78, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x2e, 0x63, 0x6f, 0x6d, 0x2c,
    0x62, 0x61, 0x7a, 0x2e, 0x65, 0x78, 0x61, 0x6d, 0x70, 0x6c, 0x65,
    0x2e, 0x63, 0x6f, 0x6d, 0x00, 0x03, 0x2e, 0x2e, 0x2e, 0x2a, 0x68,
    0x74, 0x74, 0x70, 0x73, 0x00, 0x03, 0x2e, 0x2e, 0x2e, 0xc1, 0xcf,
    0x0a, 0x50
  };
  string data(reinterpret_cast<const char*>(kBindEntry),
      arraysize(kBindEntry));
  Slice in(data);
  Slice orig_in = in;
  unique_ptr<LogEntry> entry(LogEntry::ParseBinary(&in));
  ASSERT_TRUE(entry->descriptor() != NULL);
  EXPECT_STREQ("Bind", entry->descriptor()->GetTypeName());
  EXPECT_EQ(1, entry->descriptor()->GetVersion());
  EXPECT_EQ(orig_in.data() + arraysize(kBindEntry), in.data());
  string out;
  entry->AppendBinary(&out);
  EXPECT_EQ(data, out);
}

}  // namespace sk
