#ifndef _OO_FILE_OUTPUT_STREAM_H_
#define _OO_FILE_OUTPUT_STREAM_H_

#include "lang/String.h"
#include "OutputStream.h"
#include "FileDescriptor.h"

#define public_class_FileOutputStreamClass(T, SuperClss)                    \
     extends_class(OutputStream, abstract)(T, SuperClss)                    \
                       CONSTRUCTOR(public)(T, String* name);                \
                       CONSTRUCTOR(public)(T, String* name, bool append);   \
                 void CLASS_METHOD(public)(T, setFD);                       \
      FileDescriptor* CLASS_METHOD(public)(T, getFD);                       \

#define public_class_FileOutputStream(T)    \
      extends(OutputStream, abstract)(T)    \
             FileDescriptor* _mFD;          \
                        bool _mAppend;      \

DECLARE_CLASS(public)(FileOutputStream, OutputStream)

#endif /* _OO_FILE_OUTPUT_STREAM_H_ */
