// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_SERVICES_VALUE_H_
#define LIBSK_SERVICES_VALUE_H_

#include <stdint.h>
#include <string>
#include <vector>

#include "value.h"
#include "util.h"

namespace sk {

class Slice;

// A Service is one entry in a Services field.
struct Service {
  // The common name of the service.
  std::string name;

  // A TCP/UDP port number or the empty string.
  std::string port;

  // Alternate routes to the service.
  std::vector<std::string> alternate_routes;
};

// A ServicesValue stores a list of service descriptions in a Bind entry.
class ServicesValue : public Value {
 public:
  explicit ServicesValue(const std::vector<Service>& services);
  virtual ~ServicesValue();

  const std::vector<Service>& services() const { return services_; }
  void set_services(const std::vector<Service>& services) {
    services_ = services;
  }

  // Value interface:
  virtual void AppendText(std::string* out) const OVERRIDE;
  virtual void AppendBinary(std::string* out) const OVERRIDE;
  static ServicesValue* ParseText(Slice in);
  static ServicesValue* ParseBinary(Slice* in);

 private:
  DISALLOW_EVIL_CONSTRUCTORS(ServicesValue);
  ServicesValue();

  // The list of service descriptions.
  std::vector<Service> services_;
};
}  // namespace sk

#endif  // LIBSK_SERVICES_VALUE_H_
