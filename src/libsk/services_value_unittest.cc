// Copyright 2012 the SK authors. All rights reserved.

#include "services_value.h"

#include <string>
#include <memory>
#include <vector>

#include "gtest/gtest.h"
#include "slice.h"
#include "test_util.h"

using sk::testing::WithNul;

using std::string;
using std::unique_ptr;
using std::vector;

namespace sk {

TEST(ServicesValueTest, EncodeText) {
  string out;
  ServicesValue(vector<Service>()).AppendText(&out);
  EXPECT_EQ("all", out);
  out.clear();
  ServicesValue(vector<Service>({{"https", "", {}}})).AppendText(&out);
  EXPECT_EQ("https", out);
  out.clear();
  ServicesValue(vector<Service>({{"https", "", {}},
                                 {"imaps", "", {}}})).AppendText(&out);
  EXPECT_EQ("https,imaps", out);
  out.clear();
  ServicesValue(vector<Service>({{"https", "8080", {}}})).AppendText(&out);
  EXPECT_EQ("https:8080", out);
  out.clear();
  ServicesValue(vector<Service>({{"https", "8080", {}},
                                 {"imaps", "9000", {}}})).AppendText(&out);
  EXPECT_EQ("https:8080,imaps:9000", out);
  out.clear();
  ServicesValue(vector<Service>({{"https", "", {"a"}}})).AppendText(&out);
  EXPECT_EQ("https;a", out);
  out.clear();
  ServicesValue(vector<Service>({{"https", "8080", {"a"}}})).AppendText(&out);
  EXPECT_EQ("https:8080;a", out);
  out.clear();
  ServicesValue(vector<Service>({{"https", "8080", {"a", "b"}}}))
    .AppendText(&out);
  EXPECT_EQ("https:8080;a;b", out);
  out.clear();
  ServicesValue(vector<Service>({{"https", "8080", {"a"}},
                                 {"imaps", "9000", {"b"}}})).AppendText(&out);
  EXPECT_EQ("https:8080;a,imaps:9000;b", out);
}

TEST(ServicesValueTest, EncodeBinary) {
  string out;
  ServicesValue(vector<Service>()).AppendBinary(&out);
  EXPECT_EQ(string("all") + string(1, 0), out);
  out.clear();
  ServicesValue(vector<Service>({{"https", "", {}}})).AppendBinary(&out);
  EXPECT_EQ(string("https") + string(1, 0), out);
  out.clear();
  ServicesValue(vector<Service>({{"https", "", {}},
                                 {"imaps", "", {}}})).AppendBinary(&out);
  EXPECT_EQ(string("https,imaps") + string(1, 0), out);
  out.clear();
  ServicesValue(vector<Service>({{"https", "8080", {}}})).AppendBinary(&out);
  EXPECT_EQ(string("https:8080") + string(1, 0), out);
  out.clear();
  ServicesValue(vector<Service>({{"https", "8080", {}},
                                 {"imaps", "9000", {}}})).AppendBinary(&out);
  EXPECT_EQ(string("https:8080,imaps:9000") + string(1, 0), out);
  out.clear();
  ServicesValue(vector<Service>({{"https", "", {"a"}}})).AppendBinary(&out);
  EXPECT_EQ(string("https;a") + string(1, 0), out);
  out.clear();
  ServicesValue(vector<Service>({{"https", "8080", {"a"}}}))
    .AppendBinary(&out);
  EXPECT_EQ(string("https:8080;a") + string(1, 0), out);
  out.clear();
  ServicesValue(vector<Service>({{"https", "8080", {"a", "b"}}}))
    .AppendBinary(&out);
  EXPECT_EQ(string("https:8080;a;b") + string(1, 0), out);
  out.clear();
  ServicesValue(vector<Service>({{"https", "8080", {"a"}},
                                 {"imaps", "9000", {"b"}}}))
    .AppendBinary(&out);
  EXPECT_EQ(string("https:8080;a,imaps:9000;b") + string(1, 0), out);
}

TEST(ServicesValueTest, DecodeText) {
  unique_ptr<ServicesValue> services;
  services.reset(ServicesValue::ParseText("all"));
  ASSERT_TRUE(services.get() != NULL);
  EXPECT_EQ(0U, services->services().size());
  services.reset(ServicesValue::ParseText("https"));
  ASSERT_TRUE(services.get() != NULL);
  EXPECT_EQ(1U, services->services().size());
  EXPECT_EQ("https", services->services()[0].name);
  EXPECT_EQ("", services->services()[0].port);
  EXPECT_EQ(0U, services->services()[0].alternate_routes.size());
  services.reset(ServicesValue::ParseText("https,imaps"));
  ASSERT_TRUE(services.get() != NULL);
  EXPECT_EQ(2U, services->services().size());
  EXPECT_EQ("https", services->services()[0].name);
  EXPECT_EQ("", services->services()[0].port);
  EXPECT_EQ(0U, services->services()[0].alternate_routes.size());
  EXPECT_EQ("imaps", services->services()[1].name);
  EXPECT_EQ("", services->services()[1].port);
  EXPECT_EQ(0U, services->services()[1].alternate_routes.size());
  services.reset(ServicesValue::ParseText("https:8080"));
  ASSERT_TRUE(services.get() != NULL);
  EXPECT_EQ(1U, services->services().size());
  EXPECT_EQ("https", services->services()[0].name);
  EXPECT_EQ("8080", services->services()[0].port);
  EXPECT_EQ(0U, services->services()[0].alternate_routes.size());
  services.reset(ServicesValue::ParseText("https:8080,imaps:9000"));
  ASSERT_TRUE(services.get() != NULL);
  EXPECT_EQ(2U, services->services().size());
  EXPECT_EQ("https", services->services()[0].name);
  EXPECT_EQ("8080", services->services()[0].port);
  EXPECT_EQ(0U, services->services()[0].alternate_routes.size());
  EXPECT_EQ("imaps", services->services()[1].name);
  EXPECT_EQ("9000", services->services()[1].port);
  EXPECT_EQ(0U, services->services()[1].alternate_routes.size());
  services.reset(ServicesValue::ParseText("https;a"));
  ASSERT_TRUE(services.get() != NULL);
  EXPECT_EQ(1U, services->services().size());
  EXPECT_EQ("https", services->services()[0].name);
  EXPECT_EQ("", services->services()[0].port);
  EXPECT_EQ(1U, services->services()[0].alternate_routes.size());
  EXPECT_EQ("a", services->services()[0].alternate_routes[0]);
  services.reset(ServicesValue::ParseText("https:8080;a"));
  ASSERT_TRUE(services.get() != NULL);
  EXPECT_EQ(1U, services->services().size());
  EXPECT_EQ("https", services->services()[0].name);
  EXPECT_EQ("8080", services->services()[0].port);
  EXPECT_EQ(1U, services->services()[0].alternate_routes.size());
  EXPECT_EQ("a", services->services()[0].alternate_routes[0]);
  services.reset(ServicesValue::ParseText("https:8080;a;b"));
  ASSERT_TRUE(services.get() != NULL);
  EXPECT_EQ(1U, services->services().size());
  EXPECT_EQ("https", services->services()[0].name);
  EXPECT_EQ("8080", services->services()[0].port);
  EXPECT_EQ(2U, services->services()[0].alternate_routes.size());
  EXPECT_EQ("a", services->services()[0].alternate_routes[0]);
  EXPECT_EQ("b", services->services()[0].alternate_routes[1]);
  services.reset(ServicesValue::ParseText("https:8080;a,imaps:9000;b"));
  ASSERT_TRUE(services.get() != NULL);
  EXPECT_EQ(2U, services->services().size());
  EXPECT_EQ("https", services->services()[0].name);
  EXPECT_EQ("8080", services->services()[0].port);
  EXPECT_EQ(1U, services->services()[0].alternate_routes.size());
  EXPECT_EQ("a", services->services()[0].alternate_routes[0]);
  EXPECT_EQ("imaps", services->services()[1].name);
  EXPECT_EQ("9000", services->services()[1].port);
  EXPECT_EQ(1U, services->services()[1].alternate_routes.size());
  EXPECT_EQ("b", services->services()[1].alternate_routes[0]);
}

TEST(ServicesValueTest, DecodeBinary) {
  unique_ptr<ServicesValue> services;
  Slice in(WithNul("all"));
  Slice orig_in = in;
  services.reset(ServicesValue::ParseBinary(&in));
  ASSERT_TRUE(services.get() != NULL);
  EXPECT_EQ(0U, services->services().size());
  EXPECT_EQ(orig_in.data() + 4, in.data());
  in = WithNul("https");
  orig_in = in;
  services.reset(ServicesValue::ParseBinary(&in));
  ASSERT_TRUE(services.get() != NULL);
  EXPECT_EQ(1U, services->services().size());
  EXPECT_EQ("https", services->services()[0].name);
  EXPECT_EQ("", services->services()[0].port);
  EXPECT_EQ(0U, services->services()[0].alternate_routes.size());
  EXPECT_EQ(orig_in.data() + 6, in.data());
  in = WithNul("https,imaps");
  orig_in = in;
  services.reset(ServicesValue::ParseBinary(&in));
  ASSERT_TRUE(services.get() != NULL);
  EXPECT_EQ(2U, services->services().size());
  EXPECT_EQ("https", services->services()[0].name);
  EXPECT_EQ("", services->services()[0].port);
  EXPECT_EQ(0U, services->services()[0].alternate_routes.size());
  EXPECT_EQ("imaps", services->services()[1].name);
  EXPECT_EQ("", services->services()[1].port);
  EXPECT_EQ(0U, services->services()[1].alternate_routes.size());
  EXPECT_EQ(orig_in.data() + 12, in.data());
  in = WithNul("https:8080");
  orig_in = in;
  services.reset(ServicesValue::ParseBinary(&in));
  ASSERT_TRUE(services.get() != NULL);
  EXPECT_EQ(1U, services->services().size());
  EXPECT_EQ("https", services->services()[0].name);
  EXPECT_EQ("8080", services->services()[0].port);
  EXPECT_EQ(0U, services->services()[0].alternate_routes.size());
  EXPECT_EQ(orig_in.data() + 11, in.data());
  in = WithNul("https:8080,imaps:9000");
  orig_in = in;
  services.reset(ServicesValue::ParseBinary(&in));
  ASSERT_TRUE(services.get() != NULL);
  EXPECT_EQ(2U, services->services().size());
  EXPECT_EQ("https", services->services()[0].name);
  EXPECT_EQ("8080", services->services()[0].port);
  EXPECT_EQ(0U, services->services()[0].alternate_routes.size());
  EXPECT_EQ("imaps", services->services()[1].name);
  EXPECT_EQ("9000", services->services()[1].port);
  EXPECT_EQ(0U, services->services()[1].alternate_routes.size());
  EXPECT_EQ(orig_in.data() + 22, in.data());
  in = WithNul("https;a");
  orig_in = in;
  services.reset(ServicesValue::ParseBinary(&in));
  ASSERT_TRUE(services.get() != NULL);
  EXPECT_EQ(1U, services->services().size());
  EXPECT_EQ("https", services->services()[0].name);
  EXPECT_EQ("", services->services()[0].port);
  EXPECT_EQ(1U, services->services()[0].alternate_routes.size());
  EXPECT_EQ("a", services->services()[0].alternate_routes[0]);
  EXPECT_EQ(orig_in.data() + 8, in.data());
  in = WithNul("https:8080;a");
  orig_in = in;
  services.reset(ServicesValue::ParseBinary(&in));
  ASSERT_TRUE(services.get() != NULL);
  EXPECT_EQ(1U, services->services().size());
  EXPECT_EQ("https", services->services()[0].name);
  EXPECT_EQ("8080", services->services()[0].port);
  EXPECT_EQ(1U, services->services()[0].alternate_routes.size());
  EXPECT_EQ("a", services->services()[0].alternate_routes[0]);
  EXPECT_EQ(orig_in.data() + 13, in.data());
  in = WithNul("https:8080;a;b");
  orig_in = in;
  services.reset(ServicesValue::ParseBinary(&in));
  ASSERT_TRUE(services.get() != NULL);
  EXPECT_EQ(1U, services->services().size());
  EXPECT_EQ("https", services->services()[0].name);
  EXPECT_EQ("8080", services->services()[0].port);
  EXPECT_EQ(2U, services->services()[0].alternate_routes.size());
  EXPECT_EQ("a", services->services()[0].alternate_routes[0]);
  EXPECT_EQ("b", services->services()[0].alternate_routes[1]);
  EXPECT_EQ(orig_in.data() + 15, in.data());
  in = WithNul("https:8080;a,imaps:9000;b");
  orig_in = in;
  services.reset(ServicesValue::ParseBinary(&in));
  ASSERT_TRUE(services.get() != NULL);
  EXPECT_EQ(2U, services->services().size());
  EXPECT_EQ("https", services->services()[0].name);
  EXPECT_EQ("8080", services->services()[0].port);
  EXPECT_EQ(1U, services->services()[0].alternate_routes.size());
  EXPECT_EQ("a", services->services()[0].alternate_routes[0]);
  EXPECT_EQ("imaps", services->services()[1].name);
  EXPECT_EQ("9000", services->services()[1].port);
  EXPECT_EQ(1U, services->services()[1].alternate_routes.size());
  EXPECT_EQ("b", services->services()[1].alternate_routes[0]);
  EXPECT_EQ(orig_in.data() + 26, in.data());
}

TEST(ServicesValueTest, DecodeTextErrors) {
  unique_ptr<ServicesValue> services;
  services.reset(ServicesValue::ParseText(""));
  EXPECT_TRUE(services.get() == NULL);
  services.reset(ServicesValue::ParseText(","));
  EXPECT_TRUE(services.get() == NULL);
  services.reset(ServicesValue::ParseText(":"));
  EXPECT_TRUE(services.get() == NULL);
  services.reset(ServicesValue::ParseText(";"));
  EXPECT_TRUE(services.get() == NULL);
  services.reset(ServicesValue::ParseText("https,"));
  EXPECT_TRUE(services.get() == NULL);
  services.reset(ServicesValue::ParseText("https:"));
  EXPECT_TRUE(services.get() == NULL);
  services.reset(ServicesValue::ParseText("https;"));
  EXPECT_TRUE(services.get() == NULL);
  services.reset(ServicesValue::ParseText("https;,"));
  EXPECT_TRUE(services.get() == NULL);
  services.reset(ServicesValue::ParseText("https:;"));
  EXPECT_TRUE(services.get() == NULL);
  services.reset(ServicesValue::ParseText("https:,"));
  EXPECT_TRUE(services.get() == NULL);
  services.reset(ServicesValue::ParseText("https:8000;"));
  EXPECT_TRUE(services.get() == NULL);
  services.reset(ServicesValue::ParseText("https:8000;;"));
  EXPECT_TRUE(services.get() == NULL);
  services.reset(ServicesValue::ParseText("https:8000;,imaps"));
  EXPECT_TRUE(services.get() == NULL);
}

TEST(ServicesValueTest, DecodeBinaryErrors) {
  unique_ptr<ServicesValue> services;
  Slice in(string(1, 0));
  services.reset(ServicesValue::ParseBinary(&in));
  EXPECT_TRUE(services.get() == NULL);
  in = WithNul(",");
  services.reset(ServicesValue::ParseBinary(&in));
  EXPECT_TRUE(services.get() == NULL);
  in = WithNul(":");
  services.reset(ServicesValue::ParseBinary(&in));
  EXPECT_TRUE(services.get() == NULL);
  in = WithNul(";");
  services.reset(ServicesValue::ParseBinary(&in));
  EXPECT_TRUE(services.get() == NULL);
  in = WithNul("https,");
  services.reset(ServicesValue::ParseBinary(&in));
  EXPECT_TRUE(services.get() == NULL);
  in = WithNul("https:");
  services.reset(ServicesValue::ParseBinary(&in));
  EXPECT_TRUE(services.get() == NULL);
  in = WithNul("https;");
  services.reset(ServicesValue::ParseBinary(&in));
  EXPECT_TRUE(services.get() == NULL);
  in = WithNul("https;,");
  services.reset(ServicesValue::ParseBinary(&in));
  EXPECT_TRUE(services.get() == NULL);
  in = WithNul("https:;");
  services.reset(ServicesValue::ParseBinary(&in));
  EXPECT_TRUE(services.get() == NULL);
  in = WithNul("https:,");
  services.reset(ServicesValue::ParseBinary(&in));
  EXPECT_TRUE(services.get() == NULL);
  in = WithNul("https:8000;");
  services.reset(ServicesValue::ParseBinary(&in));
  EXPECT_TRUE(services.get() == NULL);
  in = WithNul("https:8000;;");
  services.reset(ServicesValue::ParseBinary(&in));
  EXPECT_TRUE(services.get() == NULL);
  in = WithNul("https:8000;,imaps");
  services.reset(ServicesValue::ParseBinary(&in));
  EXPECT_TRUE(services.get() == NULL);
}

}  // namespace sk
