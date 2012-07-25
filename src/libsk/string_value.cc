#include "string_value.h"

#include <ctype.h>
#include <string>

#include "slice.h"

namespace sk {
namespace {
// Returns true iff all characters from |in| are printable.
bool IsPrintable(Slice in) {
  for (size_t i = 0; i < in.length(); i++)
    if (!isprint(in[i]))
      return false;
  return true;
}
}  // namespace

StringValue::StringValue() {
}

StringValue::StringValue(std::string text)
  : text_(text) {
}

StringValue::~StringValue() {
}

void StringValue::AppendText(std::string* out) const {
  out->append(text_);
}

void StringValue::AppendBinary(std::string* out) const {
  out->append(text_);
  out->append(1, '\0');
}

// static
StringValue* StringValue::ParseText(Slice in) {
  if (in.length() == 0)
    // String values cannot be empty.
    return NULL;
  if (!IsPrintable(in))
    // String values must contain only printable characters.
    return NULL;
  const char* text = reinterpret_cast<const char*>(in.data());
  return new StringValue(std::string(text, in.length()));
}

// static
StringValue* StringValue::ParseBinary(Slice* in) {
  size_t nul_pos;
  for (nul_pos = 0; nul_pos < in->length(); nul_pos++)
    if ((*in)[nul_pos] == '\0')
      break;
  if (nul_pos == 0 || nul_pos == in->length())
    // Empty or non-terminated string.
    return NULL;
  if (!IsPrintable(Slice(in->data(), nul_pos)))
    // String values must contain only printable characters.
    return NULL;
  const char* text = reinterpret_cast<const char*>(in->data());
  in->Consume(nul_pos + 1);
  return new StringValue(std::string(text, nul_pos));
}

}  // namespace sk
