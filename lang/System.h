#ifndef _OO_SYSTEM_H_
#define _OO_SYSTEM_H_

#include "Object.h"
#include "String.h"
#include "io/InputStream.h"

#define public_final_class_SystemClass(T, SuperClss)                               \
                 extends_class(Object)(T, SuperClss)                               \
             long CLASS_METHOD(public_static)(currentTimeMillis);                  \
             long CLASS_METHOD(public_static)(nanoTime);                           \
      const char* CLASS_METHOD(public_static)(lineSeparator);                      \
          String* CLASS_METHOD(public_static)(getenv, const char* str);            \
          String* CLASS_METHOD(public_static)(getcwd);                             \
             void CLASS_METHOD(public_static)(exit, int status);                   \
            void* CLASS_METHOD(public_static)(loadLibrary, String* libname);       \
             void CLASS_METHOD(public_static)(unloadLibrary, void* handle);        \
                  InputStream* in;                                                 \
                  SET(public_static)(InputStream*, in, In);                        \
                  InputStream* out;                                                \
                  SET(public_static)(InputStream*, out, Out);                      \
                  InputStream* err;                                                \
                  SET(public_static)(InputStream*, err, Err);                      \

#define public_final_class_System(T)    \
                  extends(Object)(T)    \

DECLARE_CLASS(public_final)(System, Object)

#endif /* _OO_SYSTEM_H_ */
