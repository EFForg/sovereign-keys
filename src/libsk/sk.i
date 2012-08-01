%define DOCSTRING
"sk wraps the native Sovereign Key library, libsk. It provides message
serialization and cryptographic primitives for higher level code."
%enddef

%module(docstring=DOCSTRING) sk 

%include "message.i"
%include "tfm.i"
