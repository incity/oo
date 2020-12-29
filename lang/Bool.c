//1. The .cc .cpp .cxx related header files
#include "Bool.h"
//2. C system include files.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.
#include "String.h"

BUILD(global)(TRUE,  Bool, true)
BUILD(global)(FALSE, Bool, false)

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(Bool, bool value)
{
    CONSTRUCTOR(super)(Object);
    self->_mValue = value;
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++


// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++

/**
 * Returns the value of this {@code Bool} object as a boolean
 * primitive.
 *
 * @return  the primitive {@code bool} value of this object.
 */
static bool CLASS_METHOD()(Bool, boolValue)
{
    return self->_mValue;
}

static String* CLASS_METHOD()(Bool, toString)
{
    const char* strBools[] = {"true", "false"};
    return NEW(String, strBools[!!self->_mValue]);
}

static int CLASS_METHOD()(Bool, hashCode)
{
    return self->_mValue ? 1231 : 1237;
}

static bool CLASS_METHOD()(Bool, equals, Object* obj)
{
    if ((Object*)self == obj)
        return true;

    if (INSTANCEOF(obj, Bool)) {
        Bool* b = (Bool*)obj;
        return self->_mValue == _M(b, boolValue);
    }
    return false;
}

static int compare(bool x, bool y)
{
    return (x == y) ? 0 : (x ? 1 : -1);
}

static int CLASS_METHOD()(Bool, compareTo, Bool* b)
{
    return compare(self->_mValue, b->_mValue);
}

static bool toBool(String* name)
{
    return ((name != NULL) && _M(name, equalsToCStringIgnoreCase, "true"));
}

bool STATIC_CLASS_METHOD()(Bool, parseBool, String* s)
{
    return toBool(s);
}

BEGIN_CLASS(Bool, Object)
    IMPLEMENTS(Bool, Comparable)
   CONSTRUCTOR(map)(Bool, int value)
  CLASS_METHOD(map)(Bool, boolValue)
  CLASS_METHOD(map)(Bool, toString)
  CLASS_METHOD(map)(Bool, compareTo, Bool* b)
  CLASS_METHOD(map)(Bool, hashCode)
  CLASS_METHOD(map)(Bool, equals, Object* obj)
  STATIC_CLASS_METHOD(map)(Bool, parseBool, String* s)
END_CLASS
