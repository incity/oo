#ifndef _OO_INPUT_STREAM_H_
#define _OO_INPUT_STREAM_H_

#include "lang/Object.h"
#include "Closeable.h"

#define MAX_SKIP_BUFFER_SIZE 4096

#define public_abstract_class_InputStreamClass(T, SuperClss)                    \
                         extends_class(Object)(T, SuperClss)                    \
               implements_interface(Closeable, T)                               \
                 int CLASS_METHOD(public)(T, read);                             \
                 int CLASS_METHOD(public)(T, read, byte* b, int len);           \
                 int CLASS_METHOD(public)(T, read, byte* b, int off, int len);  \
                long CLASS_METHOD(public)(T, skip, long n);                     \
                 int CLASS_METHOD(public)(T, available);                        \
                void CLASS_METHOD(public)(T, mark, int readlimit);              \
                void CLASS_METHOD(public)(T, reset);                            \
                bool CLASS_METHOD(public)(T, markSupported);

#define public_abstract_class_InputStream(T)     \
                           extends(Object)(T)    \
                        implements(Closeable)

DECLARE_CLASS(public_abstract)(InputStream, Object)

#endif /* _OO_INPUT_STREAM_H_ */
