//1. The .cc .cpp .cxx related header files
#include "SharedLibrary.h"
//2. C system include files.
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <sys/time.h>
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.
#include "lang/System.h"
#include "util/Vector.h"

// The paths searched for libraries
static String** usr_paths;
static String** sys_paths;

// All library names we've loaded.
static BUILD(global)(loadedLibraryNames, ObjectVector)

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(SharedLibrary, String* name)
{
    CONSTRUCTOR(super)(Object);
    self->_mName = REFER(name);
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(SharedLibrary)
{
    self(unload);
    DELETE(self->_mName);
    DESTRUCTOR(super)(Object);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
static void CLASS_METHOD()(SharedLibrary, load, String* name)
{
    self->_mHandle = _SM(System, loadLibrary, name);
    if (self->_mHandle != NULL) {
        _M(loadedLibraryNames, addElement, (Object*)name);
    }
}

static void CLASS_METHOD()(SharedLibrary, find, String* name)
{
    //TODO:
}

static void CLASS_METHOD()(SharedLibrary, unload)
{
    if(self->_mHandle) {
        _SM(System, unloadLibrary, self->_mHandle);
        int i;
        int size = _M(loadedLibraryNames, size);
        for (i = 0; i < size; i++) {
            Object* name = _M(loadedLibraryNames, elementAt, i);
            if (_M(self->_mName, equals, name)) {
                _M(loadedLibraryNames, removeElementAt, i);
                self(unload);
                break;
            }
        }
    }
}

BEGIN_CLASS(SharedLibrary, Object)
    CONSTRUCTOR(map)(SharedLibrary, String* name)
     DESTRUCTOR(map)(SharedLibrary)
   CLASS_METHOD(map)(SharedLibrary, unload)
   CLASS_METHOD(map)(SharedLibrary, load, String* libname)
   CLASS_METHOD(map)(SharedLibrary, find, void* handle)
END_CLASS
