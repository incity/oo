//1. The .cc .cpp .cxx related header files
#include "Bundle.h"
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
static CONSTRUCTOR()(Bundle)
{
    CONSTRUCTOR(super)(BaseBundle);
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(Bundle)
{
    DESTRUCTOR(super)(BaseBundle);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++

void CLASS_METHOD()(Bundle, putSize, String* key, Size* value)
{
    _M(self->_mMap, put, (Object*)key, (Object*)value);
}

Size* CLASS_METHOD()(Bundle, getSize, String* key)
{
    Object* o = _M(self->_mMap, get, (Object*)key);
    return (Size*)o;
}

// SizeF* CLASS_METHOD()(Bundle, getSizeF, String* key)
// {
    // return self(getSizeF, key, NULL);
// }

BEGIN_CLASS(Bundle, BaseBundle)
     CONSTRUCTOR(map)(Bundle)
      DESTRUCTOR(map)(Bundle)
    CLASS_METHOD(map)(Bundle, putSize, String* key, Size* value)
    CLASS_METHOD(map)(Bundle, getSize, String* key)
END_CLASS
