//1. The .cc .cpp .cxx related header files
#include "Writer.h"
//2. C system include files.
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++
static CONSTRUCTOR()(Writer)
{
    CONSTRUCTOR(super)(Writer, (Object*)self);
}

static CONSTRUCTOR()(Writer, Object* lock)
{
    CONSTRUCTOR(super)(Object);
    assert(lock);
    self->_mLock = REFER(lock);
}

static DESTRUCTOR()(Writer)
{
    DELETE(self->_mLock);
    DESTRUCTOR(super)(Object);
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

static void CLASS_METHOD()(Writer, write, int c)
{
    _M(self->_mLock, lock);
    char buf = (int)c;
    self(write, &buf, 0, 1);
    _M(self->_mLock, unlock);
}

static void CLASS_METHOD()(Writer, write, const char* buf, int len)
{
    self(write, buf, 0, len);
}

// public abstract
// void CLASS_METHOD()(Writer, write, const char* buf, int off, int len)

static void CLASS_METHOD()(Writer, writeString, String* str)
{
    int len = _M(str, length);
    self(writeString, str, 0, len);
}

static void CLASS_METHOD()(Writer, writeString, String* str, int off, int len)
{
    _M(self->_mLock, lock);
    const char* buf = _M(str, getCString);
    self(write, buf, off, len);
    _M(self->_mLock, unlock);
}

static Writer* CLASS_METHOD()(Writer, append, char c)
{
    self(write, c);
    return self;
}

static Writer* CLASS_METHOD()(Writer, append, const char* buf, int len)
{
    self(write, buf, len);
    return self;
}

static Writer* CLASS_METHOD()(Writer, append, const char* buf, int start, int end)
{
    self(write, buf+start, end-start);
    return self;
}

BEGIN_CLASS(Writer, Object)
   IMPLEMENTS(Writer, Appendable)
   IMPLEMENTS(Writer, Closeable)
   IMPLEMENTS(Writer, Flushable)
    CONSTRUCTOR(map)(Writer)
    CONSTRUCTOR(map)(Writer, Object* lock)
     DESTRUCTOR(map)(Writer)
   CLASS_METHOD(map)(Writer, write, int c)
   CLASS_METHOD(map)(Writer, write, const char* buf, int len)
//    CLASS_METHOD(map)(Writer, write, const char* buf, int off, int len)
   CLASS_METHOD(map)(Writer, writeString, String* str)
   CLASS_METHOD(map)(Writer, writeString, String* str, int off, int len)
   CLASS_METHOD(map)(Writer, append, char c)
   CLASS_METHOD(map)(Writer, append, const char* buf, int len)
   CLASS_METHOD(map)(Writer, append, const char* buf, int start, int end)
END_CLASS
