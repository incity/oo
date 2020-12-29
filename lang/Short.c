//1. The .cc .cpp .cxx related header files
#include "Short.h"
//2. C system include files.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.
#include "String.h"
#include "Integer.h"

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(Short, short value)
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
 * Returns the value of this {@code Short} as a
 * {@code byte}.
 */
static byte CLASS_METHOD()(Short, byteValue)
{
    return (byte)self->_mValue;
}

/**
 * Returns the value of this {@code Short} as a
 * {@code short}.
 */
static short CLASS_METHOD()(Short, shortValue)
{
    return self->_mValue;
}

/**
 * Returns the value of this {@code Short} as an
 * {@code int}.
 */
static int CLASS_METHOD()(Short, intValue)
{
    return (int)self->_mValue;
}

/**
 * Returns the value of this {@code Short} as a
 * {@code long}.
 */
static long CLASS_METHOD()(Short, longValue)
{
    return (long)self->_mValue;
}

/**
 * Returns the value of this {@code Short} as a
 * {@code float}.
 */
static float CLASS_METHOD()(Short, floatValue)
{
    return (float)self->_mValue;
}

/**
 * Returns the value of this {@code Short} as a
 * {@code double}.
 */
static double CLASS_METHOD()(Short, doubleValue)
{
    return (double)self->_mValue;
}

static String* STATIC_CLASS_METHOD()(Short, toString, short s)
{
    String* str = _SM(Integer, toString, (int)s, 10);
    return str;
}

static String* CLASS_METHOD()(Short, toString)
{
    String* rv = _SM(Integer, toString, (int)self->_mValue);
    return rv;
}

static int CLASS_METHOD()(Short, hashCode)
{
    return (int)self->_mValue;
}

static bool CLASS_METHOD()(Short, equals, Object* obj)
{
    if ((Object*)self == obj)
        return true;

    if (INSTANCEOF(obj, Short)) {
        Short* s = (Short*)obj;
        return self->_mValue == _M(s, shortValue);
    }
    return false;
}

static int compare(int x, int y)
{
    return x - y;
}

static int CLASS_METHOD()(Short, compareTo, Short* anotherShort)
{
    return compare(self->_mValue, anotherShort->_mValue);
}

BEGIN_CLASS(Short, Number)
   IMPLEMENTS(Short, Comparable)
   CONSTRUCTOR(map)(Short, int value)
  CLASS_METHOD(map)(Short, byteValue)
  CLASS_METHOD(map)(Short, shortValue)
  CLASS_METHOD(map)(Short, intValue)
  CLASS_METHOD(map)(Short, longValue)
  CLASS_METHOD(map)(Short, floatValue)
  CLASS_METHOD(map)(Short, doubleValue)
  CLASS_METHOD(map)(Short, toString)
  CLASS_METHOD(map)(Short, compareTo, Short* anotherShort)
  CLASS_METHOD(map)(Short, hashCode)
  CLASS_METHOD(map)(Short, equals, Object* obj)
STATIC_CLASS_METHOD(map)(Short, toString, int i)
END_CLASS
