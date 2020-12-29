#ifndef _OO_FILE_SYSTEM_H_
#define _OO_FILE_SYSTEM_H_

#include "lang/Object.h"
#include "File.h"

typedef enum {
    BA_EXISTS      = 0x01,
    BA_REGULAR     = 0x02,
    BA_DIRECTORY   = 0x04,
    BA_HIDDEN      = 0x08,
} FileSystemAttributesEnum;

typedef enum {
    ACCESS_EXECUTE = 0x01,
    ACCESS_WRITE   = 0x02,
    ACCESS_READ    = 0x04,
} FileSystemAccessEnum;

typedef enum {
    SPACE_TOTAL    = 0x01,
    SPACE_FREE     = 0x02,
    SPACE_USABLE   = 0x04,
} FileSystemSpaceEnum;

#define public_abstract_class_FileSystemClass(T, SuperClss)                                             \
                        extends_class(Object)(T, SuperClss)                                             \
             FileSystem* CLASS_METHOD(public_static)(getFileSystem);                                    \
                    /* -- Normalization and construction -- */                                          \
                    char CLASS_METHOD(public)(T, getSeparator);                                         \
                    char CLASS_METHOD(public)(T, getPathSeparator);                                     \
                 String* CLASS_METHOD(public)(T, normalize, String* pathname);                          \
                     int CLASS_METHOD(public)(T, prefixLength, String* path);                           \
           const String* CLASS_METHOD(public)(T, getDefaultParent);                                     \
                     /* -- Path operations -- */                                                        \
                    bool CLASS_METHOD(public)(T, isAbsolute, File* f);                                  \
                 String* CLASS_METHOD(public)(T, resolve, File* f);                                     \
                 String* CLASS_METHOD(public)(T, resolve, String* parent, String* child);               \
                     /* -- Attribute accessors -- */                                                    \
                     int CLASS_METHOD(public)(T, getBoolAttributes, File* f);                           \
                 String* CLASS_METHOD(public)(T, canonicalize, String* path);                           \
                    bool CLASS_METHOD(public)(T, checkAccess, File* f, int access);                     \
                    bool CLASS_METHOD(public)(T, setPermission, File* f, int access, bool enable, bool owneronly);    \
                    long CLASS_METHOD(public)(T, getLastModifiedTime, File* f);                         \
                    long CLASS_METHOD(public)(T, getLength, File* f);                                   \
                    /* -- File operations -- */                                                         \
                    bool CLASS_METHOD(public)(T, createFileExclusively, String* pathname);              \
                    bool CLASS_METHOD(public)(T, createDirectory, File* f);                             \
                    bool CLASS_METHOD(public)(T, delete, File* f);                                      \
                    bool CLASS_METHOD(public)(T, rename, File* f1, File* f2);                           \
                    bool CLASS_METHOD(public)(T, setLastModifiedTime, File* f, long time);              \
                    bool CLASS_METHOD(public)(T, setReadOnly, File* f);                                 \
                    /* -- Disk usage -- */                                                              \
                    long CLASS_METHOD(public)(T, getSpace, File* f, int t);                             \

#define public_abstract_class_FileSystem(T)    \
                         extends(Object)(T)    \

DECLARE_CLASS(public_abstract)(FileSystem, Object)

#endif /* _OO_FILE_SYSTEM_H_ */
