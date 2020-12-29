//1. The .cc .cpp .cxx related header files
#include "FileDescriptor.h"
//2. C system include files.
#include <assert.h>
#include <unistd.h>
//4. Other libraries' .h files.
//5. Your project's .h files.

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
CONSTRUCTOR()(FileDescriptor)
{
    self->fd = -1;
}

CONSTRUCTOR()(FileDescriptor, int fd)
{
    self->fd = fd;
}

DESTRUCTOR()(FileDescriptor)
{
    close(self->fd);
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
BEGIN_CLASS(FileDescriptor, Object)
    CONSTRUCTOR(map)(FileDescriptor)
    CONSTRUCTOR(map)(FileDescriptor, int fd)
     DESTRUCTOR(map)(FileDescriptor)
END_CLASS
