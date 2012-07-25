#include "rebinder_names_value.h"

#include <ctype.h>
#include <string>
#include <memory>

#include "slice.h"
#include "string_value.h"

namespace sk {
namespace {
// A special value used to mean there are no rebinders.
const char* const kNone = "none";

// Appends |names| to |out| in canonical text format.
void AppendNames(const std::vector<std::string>& names, std::string* out) {
  if (names.empty()) {
    out->append(kNone);
    return;
  }
  for (size_t i = 0; i < names.size(); i++) {
    if (i != 0)
      out->append(",");
    out->append(names[i]);
  }
}

// Reads rebinder names field from |in| and stores it to |names|.
// Returns true iff the field is properly encoded.
bool ReadNames(Slice in, std::vector<std::string>* names) {
  if (in.length() == 0)
    return false;
  if (in == kNone) {
    names->clear();
    return true;
  }
  while (in.length() > 0) {
    size_t i;
    for (i = 0; i < in.length(); i++)
      if (in[i] == ',')
        break;
    if (i == 0)
      // Names cannot be empty.
      return false;
    const char* text = reinterpret_cast<const char*>(in.data());
    names->push_back(std::string(text, i));
    if (in[i] != ',')
      return true;
    in.Consume(i + 1);
  }
  return false;
}

// Returns a new RebinderNamesValue given a properly decoded StringValue |str|.
// Takes ownership of and deletes str.
RebinderNamesValue* BuildFromStringValue(StringValue* str) {
  std::unique_ptr<StringValue> str_deleter(str);
  if (str == NULL)
    // Rebinder names must be a valid string.
    return NULL;
  std::vector<std::string> names;
  const bool valid_names = ReadNames(str->text(), &names);
  if (!valid_names)
    // Rebinder names string did not parse correctly.
    return NULL;
  return new RebinderNamesValue(names);
}
}  // namespace

RebinderNamesValue::RebinderNamesValue() {
}

RebinderNamesValue::RebinderNamesValue(const std::vector<std::string>& names)
  : names_(names) {
}

RebinderNamesValue::~RebinderNamesValue() {
}

void RebinderNamesValue::AppendText(std::string* out) const {
  AppendNames(names_, out);
}

void RebinderNamesValue::AppendBinary(std::string* out) const {
  AppendNames(names_, out);
  out->append(1, '\0');
}

// static
RebinderNamesValue* RebinderNamesValue::ParseText(Slice in) {
  return BuildFromStringValue(StringValue::ParseText(in));
}

// static
RebinderNamesValue* RebinderNamesValue::ParseBinary(Slice* in) {
  return BuildFromStringValue(StringValue::ParseBinary(in));
}

}  // namespace sk
