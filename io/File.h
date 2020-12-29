#ifndef _OO_FILE_H_
#define _OO_FILE_H_

#include "lang/Object.h"
#include "lang/Comparable.h"

#define public_class_FileClass(T, SuperClss)                                                   \
                     extends_class(Object)(T, SuperClss)                                       \
  implements_generic_interface(Comparable, T, File*)                                           \
                       CONSTRUCTOR(public)(T, String* pathname);                               \
                       CONSTRUCTOR(public)(T, String* pathname, int prefixLength);             \
                 bool CLASS_METHOD(public)(T, getPrefixLength);                                \
                 bool CLASS_METHOD(public)(T, exists);                                         \
                 bool CLASS_METHOD(public)(T, isDirectory);                                    \
                 bool CLASS_METHOD(public)(T, isFile);                                         \
                 long CLASS_METHOD(public)(T, lastModified);                                   \
                 long CLASS_METHOD(public)(T, length);                                         \
                 bool CLASS_METHOD(public)(T, createNewFile);                                  \
                 bool CLASS_METHOD(public)(T, delete);                                         \
                 bool CLASS_METHOD(public)(T, mkdir);                                          \
                 bool CLASS_METHOD(public)(T, mkdirs);                                         \
                 bool CLASS_METHOD(public)(T, renameTo, File* dest);                           \
                 bool CLASS_METHOD(public)(T, setReadOnly);                                    \
                 bool CLASS_METHOD(public)(T, setWritable, bool writable, bool ownerOnly);     \
                 bool CLASS_METHOD(public)(T, setWritable, bool writable);                     \
                 bool CLASS_METHOD(public)(T, setReadable, bool readable, bool ownerOnly);     \
                 bool CLASS_METHOD(public)(T, setReadable, bool readable);                     \
                 bool CLASS_METHOD(public)(T, setExecutable, bool executable, bool ownerOnly); \
                 bool CLASS_METHOD(public)(T, setExecutable, bool executable);                 \
                 bool CLASS_METHOD(public)(T, canExecute);                                     \
              String* CLASS_METHOD(public)(T, getPath);                                        \
              String* CLASS_METHOD(public)(T, getName);                                        \
              String* CLASS_METHOD(public)(T, getParent);                                      \
                File* CLASS_METHOD(public)(T, getParentFile);                                  \
              String* CLASS_METHOD(public)(T, getCanonicalPath);                               \
                File* CLASS_METHOD(public)(T, getCanonicalFile);                               \

#define public_class_File(T)     \
           extends(Object)(T)    \
       implements(Comparable)    \
           int _mPrefixLength;   \
       String* _mPath;           \

DECLARE_CLASS(public)(File, Object)

#endif /* _OO_FILE_H_ */
