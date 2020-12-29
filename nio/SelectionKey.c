//1. The .cc .cpp .cxx related header files
#include "SelectionKey.h"
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

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++

static int CLASS_METHOD()(SelectionKey, isReadable)
{
    return (self(readyOps) & OP_READ) != 0;
}

static int CLASS_METHOD()(SelectionKey, isWritable)
{
    return (self(readyOps) & OP_WRITE) != 0;
}

static int CLASS_METHOD()(SelectionKey, isConnectable)
{
    return (self(readyOps) & OP_CONNECT) != 0;
}

static int CLASS_METHOD()(SelectionKey, isAcceptable)
{
    return (self(readyOps) & OP_ACCEPT) != 0;
}

BEGIN_CLASS(SelectionKey, Object)
    CLASS_METHOD(map)(SelectionKey, isReadable)
    CLASS_METHOD(map)(SelectionKey, isWritable)
    CLASS_METHOD(map)(SelectionKey, isConnectable)
    CLASS_METHOD(map)(SelectionKey, isAcceptable)
END_CLASS

