// Copyright 2012 the SK authors. All rights reserved.

#include "services_value.h"

#include <ctype.h>
#include <memory>
#include <string>

#include "slice.h"
#include "string_value.h"

namespace sk {
namespace {
// Special value meaning that all services should use the SK.
const char* const kAll = "all";

// Appends |services| to |out| in canonical text format.
void AppendServices(const std::vector<Service>& services, std::string* out) {
  if (services.empty()) {
    out->append(kAll);
    return;
  }
  for (size_t i = 0; i < services.size(); i++) {
    if (i != 0)
      out->append(",");
    out->append(services[i].name);
    if (!services[i].port.empty()) {
      out->append(":");
      out->append(services[i].port);
    }
    for (size_t j = 0; j < services[i].alternate_routes.size(); j++) {
      out->append(";");
      out->append(services[i].alternate_routes[j]);
    }
  }
}

// Parses a single service description from |in| and stores it to |service|.
// Returns true iff the service description parses correctly.
bool ReadOneService(Slice* in, Service* service) {
  size_t i;
  // Scan for service name.
  for (i = 0; i < in->length(); i++)
    if ((*in)[i] == ':' || (*in)[i] == ';' || (*in)[i] == ',')
      break;
  if (i == 0)
    // Service name cannot be empty.
    return false;
  service->name.assign(reinterpret_cast<const char*>(in->data()), i);
  in->Consume(i);
  // Scan for port number.
  if (in->length() != 0 && (*in)[0] == ':') {
    in->ConsumeFirst();
    for (i = 0; i < in->length(); i++)
      if ((*in)[i] == ';' || (*in)[i] == ',')
        break;
    if (i == 0)
      // Port number cannot be empty.
      return false;
    service->port.assign(reinterpret_cast<const char*>(in->data()), i);
    // Note this does not consume the delimiter (; or ,).
    in->Consume(i);
  }
  // Scan for alternate routes.
  while (in->length() != 0 && (*in)[0] == ';') {
    in->ConsumeFirst();
    for (i = 0; i < in->length(); i++)
      if ((*in)[i] == ';' || (*in)[i] == ',')
        break;
    if (i == 0)
      // Route cannot be empty.
      return false;
    service->alternate_routes.push_back(std::string(
          reinterpret_cast<const char*>(in->data()), i));
    // Note this does not consume the delimiter (; or ,).
    in->Consume(i);
  }
  return true;
}

// Reads services field from |in| and stores it to |services|.
// Returns true iff the field is properly encoded.
bool ReadServices(Slice in, std::vector<Service>* services) {
  if (in == kAll)
    return true;
  while (in.length() > 0) {
    Service service;
    if (!ReadOneService(&in, &service))
      return false;
    services->push_back(service);
    if (in.length() == 0)
      return true;
    if (in[0] != ',')
      return false;
    in.ConsumeFirst();
  }
  return false;
}

// Returns a new ServiceValue given a properly decoded StringValue |str|.
// Takes ownership of and deletes str.
ServicesValue* BuildFromStringValue(StringValue* str) {
  std::unique_ptr<StringValue> str_deleter(str);
  if (str == NULL)
    // Services must be a valid string.
    return NULL;
  std::vector<Service> services;
  const bool valid_services = ReadServices(str->text(), &services);
  if (!valid_services)
    // Services string did not parse correctly.
    return NULL;
  return new ServicesValue(services);
}
}  // namespace

ServicesValue::ServicesValue() {
}

ServicesValue::ServicesValue(const std::vector<Service>& services)
  : services_(services) {
}

ServicesValue::~ServicesValue() {
}

void ServicesValue::AppendText(std::string* out) const {
  AppendServices(services_, out);
}

void ServicesValue::AppendBinary(std::string* out) const {
  AppendServices(services_, out);
  out->append(1, '\0');
}

// static
ServicesValue* ServicesValue::ParseText(Slice in) {
  return BuildFromStringValue(StringValue::ParseText(in));
}

// static
ServicesValue* ServicesValue::ParseBinary(Slice* in) {
  return BuildFromStringValue(StringValue::ParseBinary(in));
}

}  // namespace sk
