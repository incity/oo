//1. The .cc .cpp .cxx related header files
#include "Byte.h"
//2. C system include files.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.
#include "Integer.h"
#include "String.h"

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(Byte, byte value)
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
 * Returns the value of this {@code Byte} as a
 * {@code byte}.
 */
static byte CLASS_METHOD()(Byte, byteValue)
{
    return self->_mValue;
}

/**
 * Returns the value of this {@code Byte} as a
 * {@code short}.
 */
static short CLASS_METHOD()(Byte, shortValue)
{
    return (short)self->_mValue;
}

/**
 * Returns the value of this {@code Byte} as an
 * {@code int}.
 */
static int CLASS_METHOD()(Byte, intValue)
{
    return (int)self->_mValue;
}

/**
 * Returns the value of this {@code Byte} as a
 * {@code byte}.
 */
static byte CLASS_METHOD()(Byte, longValue)
{
    return (long)self->_mValue;
}

/**
 * Returns the value of this {@code Byte} as a
 * {@code float}.
 */
static float CLASS_METHOD()(Byte, floatValue)
{
    return (float)self->_mValue;
}

/**
 * Returns the value of this {@code Byte} as a
 * {@code double}.
 */
static double CLASS_METHOD()(Byte, doubleValue)
{
    return (double)self->_mValue;
}

static String* STATIC_CLASS_METHOD()(Byte, toString, byte b)
{
    String* str = _SM(Integer, toString, (int)b, 10);
    return str;
}

static String* CLASS_METHOD()(Byte, toString)
{
    String* rv = _SM(Byte, toString, self->_mValue);
    return rv;
}

static int CLASS_METHOD()(Byte, hashCode)
{
    return (int)self->_mValue;
}

static bool CLASS_METHOD()(Byte, equals, Object* obj)
{
    if ((Object*)self == obj)
        return true;

    if (INSTANCEOF(obj, Byte)) {
        Byte* b = (Byte*)obj;
        return self->_mValue == _M(b, byteValue);
    }
    return false;
}

static int compare(byte x, byte y)
{
    return x - y;
}

static int CLASS_METHOD()(Byte, compareTo, Byte* anotherByte)
{
    return compare(self->_mValue, anotherByte->_mValue);
}

BEGIN_CLASS(Byte, Number)
   IMPLEMENTS(Byte, Comparable)
   CONSTRUCTOR(map)(Byte, byte value)
  CLASS_METHOD(map)(Byte, byteValue)
  CLASS_METHOD(map)(Byte, shortValue)
  CLASS_METHOD(map)(Byte, intValue)
  CLASS_METHOD(map)(Byte, longValue)
  CLASS_METHOD(map)(Byte, floatValue)
  CLASS_METHOD(map)(Byte, doubleValue)
  CLASS_METHOD(map)(Byte, toString)
  CLASS_METHOD(map)(Byte, compareTo, Byte* anotherByte)
  CLASS_METHOD(map)(Byte, hashCode)
  CLASS_METHOD(map)(Byte, equals, Object* obj)
STATIC_CLASS_METHOD(map)(Byte, toString, byte b)
END_CLASS
