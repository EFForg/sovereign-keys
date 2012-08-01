%{
#include "message.h"
#include "slice.h"
#include "tfm_descriptor.h"
%}

%{
// To get the right polymorphic behavior for derived Messages we must
// compute and tell SWIG what type a Message instance has.
static swig_type_info* GetMessageType(sk::Message* msg) {
  if (!msg || !msg->descriptor())
    return SWIGTYPE_p_sk__Message;
  if (msg->descriptor()->GetTypeId() == sk::TFMDescriptor::kTypeId)
    return SWIGTYPE_p_sk__TFM;
  return SWIGTYPE_p_sk__Message;
}
%}

namespace sk {

%nodefaultctor Message;
%feature("docstring", "The parent class for serializable records.") Message;
class Message {
  // SWIG makes a mess of this, so define our own Pythonic wrappers below.
};

%extend Message {
  %feature("docstring",
           "Parses a Message from plaintext and returns it.\n\n"
           "Raises ValueError if text does not encode a Message.")
           parse_text;
  static PyObject* parse_text(PyObject* text) {
    char* buf;
    Py_ssize_t length;
    PyString_AsStringAndSize(text, &buf, &length);
    sk::Message* msg = sk::Message::ParseText(
        sk::Slice(reinterpret_cast<uint8_t*>(buf), length));
    if (msg == NULL) {
      SWIG_SetErrorMsg(PyExc_ValueError, "Message text does not parse.");
      return NULL;
    }
    PyObject* msg_obj = SWIG_NewPointerObj(SWIG_as_voidptr(msg),
        GetMessageType(msg), 0);
    return msg_obj;
  }

  %feature("docstring",
           "Parses a Message from binary data and returns (Message, size).\n\n"
           "Raises ValueError if data does not encode a Message.")
           parse_binary;
  static PyObject* parse_binary(PyObject* binary_message) {
    char* buf;
    Py_ssize_t length;
    PyString_AsStringAndSize(binary_message, &buf, &length);
    uint8_t* data = reinterpret_cast<uint8_t*>(buf);
    sk::Slice slice(data, length);
    sk::Message* msg = sk::Message::ParseBinary(&slice);
    if (msg == NULL) {
      SWIG_SetErrorMsg(PyExc_ValueError, "Message data does not parse.");
      return NULL;
    }
    PyObject* msg_obj = SWIG_NewPointerObj(SWIG_as_voidptr(msg),
        GetMessageType(msg), 0);
    return PyTuple_Pack(2, msg_obj, PyInt_FromSsize_t(slice.data() - data));
  }

  %feature("docstring", "Serializes message as plaintext.") write_text;
  PyObject* write_text() const {
    std::string out;
    self->AppendText(&out);
    return PyString_FromStringAndSize(out.c_str(), out.size());
  }

  %feature("docstring", "Serializes message as binary data.") write_binary;
  PyObject* write_binary() const {
    std::string out;
    self->AppendBinary(&out);
    return PyString_FromStringAndSize(out.c_str(), out.size());
  }
};

}  // namespace sk
