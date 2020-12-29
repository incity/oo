//1. The .cc .cpp .cxx related header files
#include "Long.h"
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
static CONSTRUCTOR()(Long, long value)
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
 * Returns the value of this {@code Long} as a
 * {@code byte}.
 */
static byte CLASS_METHOD()(Long, byteValue)
{
    return (byte)self->_mValue;
}

/**
 * Returns the value of this {@code Long} as a
 * {@code short}.
 */
static short CLASS_METHOD()(Long, shortValue)
{
    return (short)self->_mValue;
}

/**
 * Returns the value of this {@code Long} as an
 * {@code int}.
 */
static int CLASS_METHOD()(Long, intValue)
{
    return (int)self->_mValue;
}

/**
 * Returns the value of this {@code Long} as a
 * {@code long}.
 */
static long CLASS_METHOD()(Long, longValue)
{
    return self->_mValue;
}

/**
 * Returns the value of this {@code Long} as a
 * {@code float}.
 */
static float CLASS_METHOD()(Long, floatValue)
{
    return (float)self->_mValue;
}

/**
 * Returns the value of this {@code Long} as a
 * {@code double}.
 */
static double CLASS_METHOD()(Long, doubleValue)
{
    return (double)self->_mValue;
}

static String* STATIC_CLASS_METHOD()(Long, toString, long l)
{
    String* str = NEW(String);
    _M0(str, format, "%ld", l);
    return str;
}
extern char digits[];
static String* STATIC_CLASS_METHOD()(Long, toString, long l, int radix)
{
    if (radix < 2 || radix > 36)
        radix = 10;
    if (radix == 10)
        return _SM(Long, toString, l);
    char buf[65];
    bool negative = (l < 0);
    int charPos = 64;

    if (!negative) {
        l = -l;
    }

    while (l <= -radix) {
        buf[charPos--] = digits[-(l % radix)];
        l = l / radix;
    }
    buf[charPos] = digits[-l];

    if (negative) {
        buf[--charPos] = '-';
    }

    return NEW(String, buf, charPos, (65 - charPos));
}

static String* CLASS_METHOD()(Long, toString)
{
    String* rv = _SM(Long, toString, self->_mValue);
    return rv;
}

static int CLASS_METHOD()(Long, hashCode)
{
    unsigned long value = self->_mValue;
    return (int)(value ^ (value >> 32));
}

static bool CLASS_METHOD()(Long, equals, Object* obj)
{
    if ((Object*)self == obj)
        return true;

    if (INSTANCEOF(obj, Long)) {
        Long* l = (Long*)obj;
        return self->_mValue == _M(l, longValue);
    }
    return false;
}

static int compare(long x, long y)
{
    return (x < y) ? -1 : ((x == y) ? 0 : 1);
}

static int CLASS_METHOD()(Long, compareTo, Long* anotherLong)
{
    return compare(self->_mValue, anotherLong->_mValue);
}

BEGIN_CLASS(Long, Number)
   IMPLEMENTS(Long, Comparable)
   CONSTRUCTOR(map)(Long, long value)
  CLASS_METHOD(map)(Long, byteValue)
  CLASS_METHOD(map)(Long, shortValue)
  CLASS_METHOD(map)(Long, intValue)
  CLASS_METHOD(map)(Long, longValue)
  CLASS_METHOD(map)(Long, floatValue)
  CLASS_METHOD(map)(Long, doubleValue)
  CLASS_METHOD(map)(Long, toString)
  CLASS_METHOD(map)(Long, compareTo, Long* anotherLong)
  CLASS_METHOD(map)(Long, hashCode)
  CLASS_METHOD(map)(Long, equals, Object* obj)
STATIC_CLASS_METHOD(map)(Long, toString, long l)
STATIC_CLASS_METHOD(map)(Long, toString, long l, int radix)
END_CLASS
