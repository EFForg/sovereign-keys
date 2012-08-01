%{
#include <string>
#include "message.h"
#include "tfm.h"
%}

namespace sk {

%nodefaultctor TFM;
%feature("docstring",
         "Signed statements about the recency of information on a timeline.")
         TFM;

%rename(get_max_published_sn) TFM::max_published_sn();
%rename(get_max_published_timestamp) TFM::max_published_timestamp();
%rename(get_max_sn) TFM::max_sn();
%rename(get_max_timestamp) TFM::max_timestamp();
%rename(get_tid) TFM::tid();
%rename(get_timestamp) TFM::timestamp();

class TFM : public Message {
 public:
  TFM(int version);
  unsigned long long max_published_sn();
  void set_max_published_sn(unsigned long long);
  unsigned int max_published_timestamp();
  void set_max_published_timestamp(unsigned int);
  unsigned long long max_sn();
  void set_max_sn(unsigned long long);
  unsigned int max_timestamp();
  void set_max_timestamp(unsigned int);
  unsigned long long tid();
  void set_tid(unsigned long long);
  unsigned int timestamp();
  void set_timestamp(unsigned int);
};

%extend TFM {
  const char* get_signature() { return self->signature().c_str(); }
  void set_signature(const char* value) {
    self->set_signature(std::string(value));
  }
};

}  // namespace sk
