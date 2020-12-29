//1. The .cc .cpp .cxx related header files
#include "Integer.h"
//2. C system include files.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.
#include "String.h"

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(Integer, int value)
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
 * Returns the value of this {@code Integer} as a
 * {@code byte}.
 */
static byte CLASS_METHOD()(Integer, byteValue)
{
    return (byte)self->_mValue;
}

/**
 * Returns the value of this {@code Integer} as a
 * {@code short}.
 */
static short CLASS_METHOD()(Integer, shortValue)
{
    return (short)self->_mValue;
}

/**
 * Returns the value of this {@code Integer} as an
 * {@code int}.
 */
static int CLASS_METHOD()(Integer, intValue)
{
    return self->_mValue;
}

/**
 * Returns the value of this {@code Integer} as a
 * {@code long}.
 */
static long CLASS_METHOD()(Integer, longValue)
{
    return (long)self->_mValue;
}

/**
 * Returns the value of this {@code Integer} as a
 * {@code float}.
 */
static float CLASS_METHOD()(Integer, floatValue)
{
    return (float)self->_mValue;
}

/**
 * Returns the value of this {@code Integer} as a
 * {@code double}.
 */
static double CLASS_METHOD()(Integer, doubleValue)
{
    return (double)self->_mValue;
}

/**
 * All possible chars for representing a number as a Integer
 */
char digits[] = {
    '0' , '1' , '2' , '3' , '4' , '5' ,
    '6' , '7' , '8' , '9' , 'a' , 'b' ,
    'c' , 'd' , 'e' , 'f' , 'g' , 'h' ,
    'i' , 'j' , 'k' , 'l' , 'm' , 'n' ,
    'o' , 'p' , 'q' , 'r' , 's' , 't' ,
    'u' , 'v' , 'w' , 'x' , 'y' , 'z'
};

static String* STATIC_CLASS_METHOD()(Integer, toString, int i)
{
    String* str = NEW(String);
    _M0(str, format, "%d", i);
    return str;
}

static String* STATIC_CLASS_METHOD()(Integer, toString, int i, int radix)
{
    if (radix < 2 || radix > 36)
        radix = 10;

    /* Use the faster version */
    if (radix == 10) {
        return _SM(Integer, toString, i);
    }

    char buf[33];
    bool negative = (i < 0);
    int charPos = 32;

    if (!negative) {
        i = -i;
    }

    while (i <= -radix) {
        buf[charPos--] = digits[-(i % radix)];
        i = i / radix;
    }
    buf[charPos] = digits[-i];

    if (negative) {
        buf[--charPos] = '-';
    }

    return NEW(String, buf, charPos, (33 - charPos));
}

static String* CLASS_METHOD()(Integer, toString)
{
    String* rv = _SM(Integer, toString, self->_mValue);
    return rv;
}

static int CLASS_METHOD()(Integer, hashCode)
{
    return self->_mValue;
}

static bool CLASS_METHOD()(Integer, equals, Object* obj)
{
    if ((Object*)self == obj)
        return true;

    if (INSTANCEOF(obj, Integer)) {
        Integer* integer = (Integer*)obj;
        return self->_mValue == _M(integer, intValue);
    }
    return false;
}

static int compare(int x, int y)
{
    return (x < y) ? -1 : ((x == y) ? 0 : 1);
}

static int CLASS_METHOD()(Integer, compareTo, Integer* anotherInteger)
{
    return compare(self->_mValue, anotherInteger->_mValue);
}

BEGIN_CLASS(Integer, Number)
   IMPLEMENTS(Integer, Comparable)
   CONSTRUCTOR(map)(Integer, int value)
  CLASS_METHOD(map)(Integer, byteValue)
  CLASS_METHOD(map)(Integer, shortValue)
  CLASS_METHOD(map)(Integer, intValue)
  CLASS_METHOD(map)(Integer, longValue)
  CLASS_METHOD(map)(Integer, floatValue)
  CLASS_METHOD(map)(Integer, doubleValue)
  CLASS_METHOD(map)(Integer, toString)
  CLASS_METHOD(map)(Integer, compareTo, Integer* anotherInteger)
  CLASS_METHOD(map)(Integer, hashCode)
  CLASS_METHOD(map)(Integer, equals, Object* obj)
STATIC_CLASS_METHOD(map)(Integer, toString, int i)
STATIC_CLASS_METHOD(map)(Integer, toString, int i, int radix)
END_CLASS
