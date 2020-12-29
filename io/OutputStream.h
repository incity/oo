#ifndef _OO_OUTPUT_STREAM_H_
#define _OO_OUTPUT_STREAM_H_

#include "lang/Object.h"
#include "Closeable.h"
#include "Flushable.h"

#define MAX_SKIP_BUFFER_SIZE 4096

#define public_abstract_class_OutputStreamClass(T, SuperClss)                                \
                          extends_class(Object)(T, SuperClss)                                \
                implements_interface(Closeable, T)                                           \
                implements_interface(Flushable, T)                                           \
              int CLASS_METHOD(public_abstract)(T, write, int b);                            \
                       int CLASS_METHOD(public)(T, write, const byte* b, int len);           \
                       int CLASS_METHOD(public)(T, write, const byte* b, int off, int len);  \

#define public_abstract_class_OutputStream(T)    \
                           extends(Object)(T)    \
                        implements(Closeable)    \
                        implements(Flushable)

DECLARE_CLASS(public_abstract)(OutputStream, Object)

#endif /* _OO_OUTPUT_STREAM_H_ */
