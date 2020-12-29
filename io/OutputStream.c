//1. The .cc .cpp .cxx related header files
#include "OutputStream.h"
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

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++

static int CLASS_METHOD()(OutputStream, write, const byte* b, int len)
{
    return self(write, b, 0, len);
}

static int CLASS_METHOD()(OutputStream, write, const byte* b, int off, int len)
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

static void CLASS_METHOD()(OutputStream, close)
{
}

static void CLASS_METHOD()(OutputStream, flush)
{
}

BEGIN_CLASS(OutputStream, Object)
 IMPLEMENTS(OutputStream, Closeable)
CLASS_METHOD(map)(OutputStream, write, const byte* b, int len)
CLASS_METHOD(map)(OutputStream, write, const byte* b, int off, int len)
CLASS_METHOD(map)(OutputStream, close)
CLASS_METHOD(map)(OutputStream, flush)
END_CLASS
