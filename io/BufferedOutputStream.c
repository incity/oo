//1. The .cc .cpp .cxx related header files
#include "BufferedOutputStream.h"
//2. C system include files.
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++

static CONSTRUCTOR()(BufferedOutputStream, OutputStream* out)
{
    CONSTRUCTOR(super)(BufferedOutputStream, out, 8192);
}

static CONSTRUCTOR()(BufferedOutputStream, OutputStream* out, int size)
{
    CONSTRUCTOR(super)(FilterOutputStream, out);
    assert(size > 0);
    self->_mBuf = (byte*)calloc(size, sizeof(byte));
    self->_mCapacity = size;
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++

static DESTRUCTOR()(BufferedOutputStream)
{
    free(self->_mBuf);
    DESTRUCTOR(super)(FilterOutputStream);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++

static void CLASS_METHOD()(BufferedOutputStream, flushBuffer)
{
    if (self->_mCount > 0) {
        _M(self->_mOut, write, self->_mBuf, 0, self->_mCount);
        self->_mCount = 0;
    }
}

static void CLASS_METHOD()(BufferedOutputStream, write, byte b)
{
    if (self->_mCount >= self->_mCapacity) {
        self(flushBuffer);
    }
    self->_mBuf[self->_mCount++] = (byte)b;
}

static void CLASS_METHOD()(BufferedOutputStream, write, const byte* b, int off, int len)
{
    if (len >= self->_mCapacity) {
        self(flushBuffer);
        _M(self->_mOut, write, b, off, len);
        return;
    }
    if (len > self->_mCapacity - self->_mCount)
        self(flushBuffer);
    memcpy(self->_mBuf + self->_mCount, b + off, len);
    self->_mCount += len;
}

static void CLASS_METHOD()(BufferedOutputStream, flush)
{
    self(flushBuffer);
    _M(self->_mOut, flush);
}

BEGIN_CLASS(BufferedOutputStream, FilterOutputStream)
    CONSTRUCTOR(map)(BufferedOutputStream, OutputStream* out)
    CONSTRUCTOR(map)(BufferedOutputStream, OutputStream* out, int size)
     DESTRUCTOR(map)(BufferedOutputStream)
   CLASS_METHOD(map)(BufferedOutputStream, write, byte b)
   CLASS_METHOD(map)(BufferedOutputStream, write, const byte* b, int off, int len)
   CLASS_METHOD(map)(BufferedOutputStream, flush)
   CLASS_METHOD(map)(BufferedOutputStream, flushBuffer)
END_CLASS
