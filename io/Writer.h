#ifndef _OO_WRITER_H_
#define _OO_WRITER_H_

#include "lang/String.h"
#include "Appendable.h"
#include "Closeable.h"
#include "Flushable.h"

#define public_abstract_class_WriterClass(T, SuperClss)                                      \
                    extends_class(Object)(T, SuperClss)                                      \
         implements_interface(Appendable, T)                                                 \
          implements_interface(Closeable, T)                                                 \
          implements_interface(Flushable, T)                                                 \
                      CONSTRUCTOR(public)(T, Object* lock);                                  \
                 int CLASS_METHOD(public)(T, write, int c);                                  \
                 int CLASS_METHOD(public)(T, write, const char* buf, int len);               \
        int CLASS_METHOD(public_abstract)(T, write, const char* buf, int off, int len);      \
                 int CLASS_METHOD(public)(T, writeString, String* str);                      \
                 int CLASS_METHOD(public)(T, writeString, String* str, int off, int len);    \

#define public_abstract_class_Writer(T)    \
                     extends(Object)(T)    \
                   implements(Appendable)  \
                   implements(Closeable)   \
                   implements(Flushable)   \
                     Object* _mLock;       \

DECLARE_CLASS(public_abstract)(Writer, Object)

#endif /* _OO_WRITER_H_ */
