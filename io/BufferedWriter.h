#ifndef _OO_BUFFERED_WRITER_H_
#define _OO_BUFFERED_WRITER_H_

#include "Writer.h"

#define public_class_BufferedWriterClass(T, SuperClss)                         \
         extends_class(Writer, abstract)(T, SuperClss)                         \
             CONSTRUCTOR(public)(T, Writer* out, Object* lock);                \
             CONSTRUCTOR(public)(T, Writer* out, Object* lock, int capacity);  \
       void CLASS_METHOD(public)(T, flushBuffer);                              \

#define public_class_BufferedWriter(T)  \
          extends(Writer, abstract)(T)  \
            Writer* _mOut;              \
            byte* _mBuffer;             \
            int _mCapacity;             \
            int _mNextChar;             \

DECLARE_CLASS(public)(BufferedWriter, Writer)

#endif /* _OO_BUFFERED_WRITER_H_ */
