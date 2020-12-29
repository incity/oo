//1. The .cc .cpp .cxx related header files
#include "FileOutputStream.h"
//2. C system include files.
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++

static CONSTRUCTOR()(FileOutputStream, String* name)
{
    CONSTRUCTOR(super)(FileOutputStream, name, false);
}

static CONSTRUCTOR()(FileOutputStream, String* name, bool append)
{
    assert(name);
    self->_mAppend = append;
    const char* path = _M(name, getCString);
    int fd = open(path, O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC), 0666);
    self->_mFD = NEW(FileDescriptor, fd);
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(FileOutputStream)
{
    self(close);
    DESTRUCTOR(super)(OutputStream);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++

static void CLASS_METHOD()(FileOutputStream, close)
{
    DELETE(self->_mFD);
    self->_mFD = NULL;
}

static FileDescriptor* CLASS_METHOD()(FileOutputStream, getFD)
{
    return self->_mFD;
}

static void CLASS_METHOD()(FileOutputStream, setFD)
{
    self->_mFD = REFER(self->_mFD);
}

static int CLASS_METHOD()(FileOutputStream, write, int b)
{
    byte c = (byte)b;
    return self(write, &c, sizeof(char));
}

static int CLASS_METHOD()(FileOutputStream, write, const byte* b, int len)
{
    return self(write, b, 0, len);
}

static int CLASS_METHOD()(FileOutputStream, write, const byte* b, int off, int len)
{
    int n;
    int remain = len;
    while (remain > 0) {
        n = write(self->_mFD->fd, b, remain);
        if (n < 0) {
            if (errno == EINTR)
                continue;
            if (errno == EAGAIN || errno == EWOULDBLOCK)
                break;
            assert(0);
        }
        remain -= n;
        b += n;
    }
    return len - remain;
}

BEGIN_CLASS(FileOutputStream, OutputStream)
    CONSTRUCTOR(map)(FileOutputStream, String* name, bool append)
    CONSTRUCTOR(map)(FileOutputStream, String* name)
     DESTRUCTOR(map)(FileOutputStream)
   CLASS_METHOD(map)(FileOutputStream, write, int b)
   CLASS_METHOD(map)(FileOutputStream, write, const char* b, int len)
   CLASS_METHOD(map)(FileOutputStream, write, const char* b, int off, int len)
   CLASS_METHOD(map)(FileOutputStream, close)
   CLASS_METHOD(map)(FileOutputStream, setFD)
   CLASS_METHOD(map)(FileOutputStream, getFD)
END_CLASS
