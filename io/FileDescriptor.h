#ifndef _OO_FILE_DESCRIPTOR_
#define _OO_FILE_DESCRIPTOR_

#include "lang/Object.h"
#include "io/Closeable.h"

#define public_final_class_FileDescriptorClass(T, SuperClss)    \
          extends_class(Object)(T, SuperClss)                   \
            CONSTRUCTOR(public)(T, int fd);                     \
      void CLASS_METHOD(public)(T, attach, Closeable* c);       \

#define public_final_class_FileDescriptor(T)    \
          extends(Object)(T)                    \
          int fd;                               \

DECLARE_CLASS(public_final)(FileDescriptor, Object)

#endif /* _OO_FILE_DESCRIPTOR_ */
