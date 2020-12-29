#ifndef _OO_BUFFERED_OUTPUT_STREAM_H_
#define _OO_BUFFERED_OUTPUT_STREAM_H_

#include "FilterOutputStream.h"

#define public_class_BufferedOutputStreamClass(T, SuperClss)           \
             extends_class(FilterOutputStream)(T, SuperClss)           \
                CONSTRUCTOR(public)(T, OutputStream* out, int size);   \
              void CLASS_METHOD(private)(T, flushBuffer);

#define public_class_BufferedOutputStream(T)    \
            extends(FilterOutputStream)(T)      \
              byte* _mBuf;                      \
              int   _mCount;                    \
              int   _mCapacity;

DECLARE_CLASS(public)(BufferedOutputStream, FilterOutputStream)

#endif /* _OO_BUFFERED_OUTPUT_STREAM_H_ */
