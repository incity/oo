#ifndef _OO_FILTER_OUTPUT_STREAM_H_
#define _OO_FILTER_OUTPUT_STREAM_H_

#include "OutputStream.h"

#define public_class_FilterOutputStreamClass(T, SuperClss)            \
       extends_class(OutputStream, abstract)(T, SuperClss)            \
                         CONSTRUCTOR(public)(T, OutputStream* out);   \

#define public_class_FilterOutputStream(T)    \
        extends(OutputStream, abstract)(T)    \
          OutputStream* _mOut;

DECLARE_CLASS(public)(FilterOutputStream, OutputStream)

#endif /* _OO_FILTER_OUTPUT_STREAM_H_ */
