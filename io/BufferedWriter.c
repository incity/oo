//1. The .cc .cpp .cxx related header files
#include "BufferedWriter.h"
//2. C system include files.
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.
#include "lang/math.h"

#define DEFAULT_BUFFER_SIZE 8192

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

static CONSTRUCTOR()(BufferedWriter, Writer* out, Object* lock)
{
   CONSTRUCTOR(super)(BufferedWriter, out, lock, DEFAULT_BUFFER_SIZE);
}

static CONSTRUCTOR()(BufferedWriter, Writer* out, Object* lock, int capacity)
{
    CONSTRUCTOR(super)(Writer, lock);
    assert(out);
    self->_mCapacity = capacity;
    self->_mBuffer = (byte*)malloc(capacity);
    self->_mOut = REFER(out);
}

static DESTRUCTOR()(BufferedWriter)
{
    self(close);
    DESTRUCTOR(super)(Writer);
}

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++

void CLASS_METHOD()(BufferedWriter, write, const char* buf, int off, int len)
{
    assert(off >= 0 && len > 0);
    _M(self->_mLock, lock);
    do {
        if (len > self->_mCapacity) {
            /* If the request length exceeds the size of the output buffer,
               flush the buffer and then write the data directly.  In this
               way buffered streams will cascade harmlessly. */
            self(flushBuffer);
            _M(self->_mOut, write, buf, off, len);
            break;
        }

        int b = off, t = off + len;
        while (b < t) {
            int d = min(self->_mCapacity - self->_mNextChar, t - b);
            memcpy(self->_mBuffer + self->_mNextChar, buf + b, d);
            b += d;
            self->_mNextChar += d;
            if (self->_mNextChar >= self->_mCapacity)
                self(flushBuffer);
        }
    } while(0);
   _M(self->_mLock, unlock);
}

void CLASS_METHOD()(BufferedWriter, flush)
{
    _M(self->_mLock, lock);
    self(flushBuffer);
    _M(self->_mOut, flush);
    _M(self->_mLock, unlock);
}

void CLASS_METHOD()(BufferedWriter, close)
{
   _M(self->_mLock, lock);
   do {
       if (self->_mOut)
           break;
        self(flushBuffer);
        _M(self->_mOut, close);
        DELETE(self->_mOut);
        self->_mOut = NULL;
        free(self->_mBuffer);
        self->_mBuffer = NULL;
   } while(0);
   _M(self->_mLock, unlock);
}

BEGIN_CLASS(BufferedWriter, Writer)
   CONSTRUCTOR(map)(BufferedWriter, Writer* writer, Object* lock)
   CONSTRUCTOR(map)(BufferedWriter, Writer* writer, Object* lock, int capacity)
    DESTRUCTOR(map)(BufferedWriter)
  CLASS_METHOD(map)(BufferedWriter, write, const char* buf, int off, int len)
  CLASS_METHOD(map)(BufferedWriter, flush)
  CLASS_METHOD(map)(BufferedWriter, close)
END_CLASS
