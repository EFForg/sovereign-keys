%define DOCSTRING
"sk wraps the native Sovereign Key library, libsk. It provides message
serialization and cryptographic primitives for higher level code."
%enddef

%module(docstring=DOCSTRING) sk 

%{
#include "message.h"
#include "slice.h"
%}

namespace sk {

%nodefaultctor Message;
%feature("docstring", "The parent class for serializable records.") Message;
class Message {
  // SWIG makes a mess of this, so define our own Pythonic wrappers below.
};

%extend Message {
  %feature("docstring", "Parses a Message from plaintext and returns it.")
           ParseText;
  static sk::Message* ParseText(PyObject* text) {
    char* buf;
    Py_ssize_t length;
    PyString_AsStringAndSize(text, &buf, &length);
    return sk::Message::ParseText(
        sk::Slice(reinterpret_cast<uint8_t*>(buf), length));
  }

  %feature("docstring",
           "Parses a Message from binary data and returns (Message, size).")
           ParseBinary;
  static PyObject* ParseBinary(PyObject* binary_message) {
    char* buf;
    Py_ssize_t length;
    PyString_AsStringAndSize(binary_message, &buf, &length);
    uint8_t* data = reinterpret_cast<uint8_t*>(buf);
    sk::Slice slice(data, length);
    sk::Message* msg = sk::Message::ParseBinary(&slice);
    PyObject* msg_obj = SWIG_NewPointerObj(SWIG_as_voidptr(msg),
        SWIGTYPE_p_sk__Message, 0 |  0);
    return PyTuple_Pack(2, msg_obj, PyInt_FromSsize_t(slice.data() - data));
  }

  %feature("docstring", "Serializes message as plaintext.") WriteText;
  PyObject* WriteText() const {
    std::string out;
    self->AppendText(&out);
    return PyString_FromStringAndSize(out.c_str(), out.size());
  }

  %feature("docstring", "Serializes message as binary data.") WriteBinary;
  PyObject* WriteBinary() const {
    std::string out;
    self->AppendBinary(&out);
    return PyString_FromStringAndSize(out.c_str(), out.size());
  }
};

}  // namespace sk
