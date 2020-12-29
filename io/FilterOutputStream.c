//1. The .cc .cpp .cxx related header files
#include "FilterOutputStream.h"
//2. C system include files.
#include <stdio.h>
#include <stdlib.h>
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(FilterOutputStream, OutputStream* out)
{
    CONSTRUCTOR(super)(OutputStream);
    self->_mOut = REFER(out);
}
// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(FilterOutputStream)
{
    DELETE(self->_mOut);
    DESTRUCTOR(super)(OutputStream);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++

static int CLASS_METHOD()(FilterOutputStream, write, byte b)
{
    return _M(self->_mOut, write, b);
}

static int CLASS_METHOD()(FilterOutputStream, write, const byte* b, int len)
{
    return self(write, b, 0, len);
}

static int CLASS_METHOD()(FilterOutputStream, write, const byte* b, int off, int len)
{
    assert(b != NULL);
    assert(off >= 0 && len > 0);
    int i;
    for (i = 0; i < len; i++) {
        if (self(write, b[off + i]) <= 0)
            break;
    }
    return i;
}

static void CLASS_METHOD()(FilterOutputStream, close)
{
    self(flush);
    _M(self->_mOut, close);
}

static void CLASS_METHOD()(FilterOutputStream, flush)
{
    _M(self->_mOut, flush);
}

BEGIN_CLASS(FilterOutputStream, OutputStream)
    CONSTRUCTOR(map)(FilterOutputStream, OutputStream* out)
     DESTRUCTOR(map)(FilterOutputStream)
   CLASS_METHOD(map)(FilterOutputStream, write, byte b)
   CLASS_METHOD(map)(FilterOutputStream, write, const byte* b, int len)
   CLASS_METHOD(map)(FilterOutputStream, write, const byte* b, int off, int len)
   CLASS_METHOD(map)(FilterOutputStream, close)
   CLASS_METHOD(map)(FilterOutputStream, flush)
END_CLASS
