#ifndef _OO_UNIX_FILE_SYSTEM_IMPL_H_
#define _OO_UNIX_FILE_SYSTEM_IMPL_H_

#include "lang/String.h"
#include "io/FileSystem.h"

#define public_class_UnixFileSystemClass(T, SuperClss)                                       \
     extends_class(FileSystem, abstract)(T, SuperClss)                                       \
           String* CLASS_METHOD(private)(T, normalize, String* pathname, int len, int off);  \

#define   public_class_UnixFileSystem(T)    \
        extends(FileSystem, abstract)(T)    \

DECLARE_CLASS(public)(UnixFileSystem, FileSystem)

#endif /* _OO_UNIX_FILE_SYSTEM_IMPL_H_ */
