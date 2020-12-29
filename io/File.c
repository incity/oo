//1. The .cc .cpp .cxx related header files
#include "File.h"
//2. C system include files.
#include <stdio.h>
#include <stdlib.h>
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.
#include "lang/System.h"
#include "FileSystem.h"

static FileSystem* fs;

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
CONSTRUCTOR()(File, String* pathname)
{
    CONSTRUCTOR(super)(Object);
    FileSystem* fs = Class(FileSystem).getFileSystem();
    self->_mPath = _M(fs, normalize, pathname);
    self->_mPrefixLength = _M(fs, prefixLength, self->_mPath);
}

CONSTRUCTOR()(File, String* pathname, int prefixLength)
{
    CONSTRUCTOR(super)(Object);
    FileSystem* fs = Class(FileSystem).getFileSystem();
    self->_mPath = REFER(pathname);
    self->_mPrefixLength = prefixLength;
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
DESTRUCTOR()(File)
{
    DELETE(self->_mPath);
    DESTRUCTOR(super)(Object);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++

static bool CLASS_METHOD()(File, exists)
{
    return _M(fs, getBoolAttributes, self) & BA_EXISTS;
}

static bool CLASS_METHOD()(File, isDirectory)
{
    return _M(fs, getBoolAttributes, self) & BA_DIRECTORY;
}

static bool CLASS_METHOD()(File, isFile)
{
    return _M(fs, getBoolAttributes, self) & BA_REGULAR;
}

static long CLASS_METHOD()(File, lastModified)
{
    return _M(fs, getLastModifiedTime, self);
}

static long CLASS_METHOD()(File, length)
{
    return _M(fs, getLength, self);
}

static bool CLASS_METHOD()(File, createNewFile)
{
    return _M(fs, createFileExclusively, self->_mPath);
}

static bool CLASS_METHOD()(File, delete)
{
    return _M(fs, delete, self);
}

static bool CLASS_METHOD()(File, mkdir)
{
    return _M(fs, createDirectory, self);
}

static bool CLASS_METHOD()(File, mkdirs)
{
    if (self(exists))
        return false;

    if (self(mkdir))
        return true;

    File* canonFile = self(getCanonicalFile);
    if (canonFile == NULL)
        return false;

    File* parent = _M(canonFile, getParentFile);
    bool rv = (parent != NULL && (_M(parent, mkdirs) || _M(parent, exists))
            && _M(canonFile, mkdir));
    DELETE(canonFile);
    if (parent) DELETE(parent);
    return rv;
}

static bool CLASS_METHOD()(File, renameTo, File* dest)
{
    return _M(fs, rename, self, dest);
}

static bool CLASS_METHOD()(File, setReadOnly)
{
    return _M(fs, setReadOnly, self);
}

static bool CLASS_METHOD()(File, setWritable, bool writable, bool ownerOnly)
{
    return _M(fs, setPermission, self, ACCESS_WRITE, writable, ownerOnly);
}

static bool CLASS_METHOD()(File, setWritable, bool writable)
{
    return self(setWritable, writable, true);
}

static bool CLASS_METHOD()(File, setReadable, bool readable, bool ownerOnly)
{
    return _M(fs, setPermission, self, ACCESS_READ, readable, ownerOnly);
}

static bool CLASS_METHOD()(File, setReadable, bool readable)
{
    return self(setReadable, readable, true);
}

static bool CLASS_METHOD()(File, setExecutable, bool executable, bool ownerOnly)
{
    return _M(fs, setPermission, self, ACCESS_EXECUTE, executable, ownerOnly);
}

static bool CLASS_METHOD()(File, setExecutable, bool executable)
{
    return self(setExecutable, executable, true);
}

static bool CLASS_METHOD()(File, canExecute)
{
    return _M(fs, checkAccess, self, ACCESS_EXECUTE);
}

static bool CLASS_METHOD()(File, getPrefixLength)
{
    return self->_mPrefixLength;
}

static String* CLASS_METHOD()(File, getPath)
{
    return self->_mPath;
}

static String* CLASS_METHOD()(File, getCanonicalPath)
{
    String* path = _M(fs, resolve, self);
    String* rv = _M(fs, canonicalize, path);
    DELETE(path);
    return rv;
}

static File* CLASS_METHOD()(File, getCanonicalFile)
{
    String* canonPath = self(getCanonicalPath);
    int len = _M(fs, prefixLength, canonPath);
    File* file = NEW(File, canonPath, len);
    DELETE(canonPath);
    return file;
}

static File* CLASS_METHOD()(File, getParentFile)
{
    String* p = self(getParent);
    if (p == NULL) return NULL;
    File* parentFile = NEW(File, p, self->_mPrefixLength);
    DELETE(p);
    return parentFile;
}

static String* CLASS_METHOD()(File, getParent)
{
    int separatorChar = _M(fs, getSeparator);
    int index = _M(self->_mPath, lastIndexOfChar, separatorChar);
    if (index < self->_mPrefixLength) {
        if (self->_mPrefixLength > 0 && _M(self->_mPath, length) > self->_mPrefixLength)
            return _M(self->_mPath, substring, 0, self->_mPrefixLength);
        return NULL;
    }
    return _M(self->_mPath, substring, 0, index);
}

BEGIN_CLASS(File, Object)
  IMPLEMENTS(File, Comparable)
     fs = Class(FileSystem).getFileSystem();
     CONSTRUCTOR(map)(File, String* pathname)
     CONSTRUCTOR(map)(File, String* pathname, int prefixLength)
      DESTRUCTOR(map)(File)
    CLASS_METHOD(map)(File, exists)
    CLASS_METHOD(map)(File, isDirectory)
    CLASS_METHOD(map)(File, isFile)
    CLASS_METHOD(map)(File, lastModified)
    CLASS_METHOD(map)(File, length)
    CLASS_METHOD(map)(File, createNewFile)
    CLASS_METHOD(map)(File, delete)
    CLASS_METHOD(map)(File, mkdir)
    CLASS_METHOD(map)(File, mkdirs)
    CLASS_METHOD(map)(File, renameTo, File* dest)
    CLASS_METHOD(map)(File, setReadOnly)
    CLASS_METHOD(map)(File, setWritable, bool writable, bool ownerOnly)
    CLASS_METHOD(map)(File, setWritable, bool writable)
    CLASS_METHOD(map)(File, setReadable, bool readable)
    CLASS_METHOD(map)(File, setReadable, bool readable, bool ownerOnly)
    CLASS_METHOD(map)(File, setExecutable, bool executable, bool ownerOnly)
    CLASS_METHOD(map)(File, setExecutable, bool executable)
    CLASS_METHOD(map)(File, canExecute)
    CLASS_METHOD(map)(File, getPrefixLength)
    CLASS_METHOD(map)(File, getPath)
    CLASS_METHOD(map)(File, getCanonicalPath)
    CLASS_METHOD(map)(File, getParentFile)
    CLASS_METHOD(map)(File, getCanonicalFile)
    CLASS_METHOD(map)(File, getParent)
END_CLASS
