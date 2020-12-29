//1. The .cc .cpp .cxx related header files
#include "Double.h"
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
static CONSTRUCTOR()(Double, double value)
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
 * Returns the value of this {@code Double} as a
 * {@code byte}.
 */
static byte CLASS_METHOD()(Double, byteValue)
{
    return (byte)self->_mValue;
}

/**
 * Returns the value of this {@code Double} as a
 * {@code short}.
 */
static short CLASS_METHOD()(Double, shortValue)
{
    return (short)self->_mValue;
}

/**
 * Returns the value of this {@code Double} as an
 * {@code int}.
 */
static int CLASS_METHOD()(Double, intValue)
{
    return (int)self->_mValue;
}

/**
 * Returns the value of this {@code Double} as a
 * {@code long}.
 */
static long CLASS_METHOD()(Double, longValue)
{
    return (long)self->_mValue;
}

/**
 * Returns the value of this {@code Double} as a
 * {@code float}.
 */
static float CLASS_METHOD()(Double, floatValue)
{
    return (float)self->_mValue;
}

/**
 * Returns the value of this {@code Double} as a
 * {@code double}.
 */
static double CLASS_METHOD()(Double, doubleValue)
{
    return self->_mValue;
}

static String* STATIC_CLASS_METHOD()(Double, toString, double d)
{
    String* str = NEW(String);
    _M0(str, format, "%f", d);
    return str;
}

static String* CLASS_METHOD()(Double, toString)
{
    String* rv = _SM(Double, toString, self->_mValue);
    return rv;
}

/* Useful on machines where long and double have different endianness. */
#define long_to_double_bits(a)
#define double_to_long_bits(a)

/*
 * Find the double float corresponding to a given bit pattern
 */
static inline float longBitsToDouble(long v)
{
    union {
        long l;
        double d;
    } u;
    long_to_double_bits(&v);
    u.l = v;
    return u.d;
}

/*
 * Find the bit pattern corresponding to a given double float, NOT collapsing NaNs
 */
static inline long doubleToLongBits(double v)
{
    union {
        long l;
        double d;
    } u;
    double_to_long_bits(&v);
    u.d = (double)v;
    return u.d;
}

static bool CLASS_METHOD()(Double, equals, Object* obj)
{
    if ((Object*)self == obj)
        return true;

    if (INSTANCEOF(obj, Double)) {
        Double* d = (Double*)obj;
        return doubleToLongBits(self->_mValue) == doubleToLongBits(d->_mValue);
    }
    return false;
}

int STATIC_CLASS_METHOD()(Double, compare, double d1, double d2)
{
    if (d1 < d2)
        return -1;           // Neither val is NaN, thisVal is smaller
    if (d1 > d2)
        return 1;            // Neither val is NaN, thisVal is larger

    // Cannot use floatToRawIntBits because of possibility of NaNs.
    int thisBits    = doubleToLongBits(d1);
    int anotherBits = doubleToLongBits(d2);

    return (thisBits == anotherBits ?  0 : // Values are equal
            (thisBits < anotherBits ? -1 : // (-0.0, 0.0) or (!NaN, NaN)
             1));                          // (0.0, -0.0) or (NaN, !NaN)
}

static int CLASS_METHOD()(Double, compareTo, Double* anotherDouble)
{
    return _SM(Double, compare, self->_mValue, anotherDouble->_mValue);
}

static int CLASS_METHOD()(Double, hashCode)
{
    unsigned long bits = doubleToLongBits(self->_mValue);
    return (int)(bits ^ (bits >> 32));
}

static bool STATIC_CLASS_METHOD()(Double, isNaN, double v)
{
    return (v != v);
}

static bool STATIC_CLASS_METHOD()(Double, isInfinite, double v)
{
    return (v == POSITIVE_INFINITY) || (v == NEGATIVE_INFINITY);
}

static bool CLASS_METHOD()(Double, isNaN)
{
    return _SM(Double, isNaN, self->_mValue);
}

static bool CLASS_METHOD()(Double, isInfinite)
{
    return _SM(Double, isInfinite, self->_mValue);
}

BEGIN_CLASS(Double, Number)
   IMPLEMENTS(Double, Comparable)
   CONSTRUCTOR(map)(Double, int value)
  CLASS_METHOD(map)(Double, byteValue)
  CLASS_METHOD(map)(Double, shortValue)
  CLASS_METHOD(map)(Double, intValue)
  CLASS_METHOD(map)(Double, longValue)
  CLASS_METHOD(map)(Double, floatValue)
  CLASS_METHOD(map)(Double, doubleValue)
  CLASS_METHOD(map)(Double, toString)
  CLASS_METHOD(map)(Double, compareTo, Double* anotherDouble)
  CLASS_METHOD(map)(Double, hashCode)
  CLASS_METHOD(map)(Double, equals, Object* obj)
  CLASS_METHOD(map)(Double, isNaN)
  CLASS_METHOD(map)(Double, isInfinite)
STATIC_CLASS_METHOD(map)(Double, toString, float f)
STATIC_CLASS_METHOD(map)(Double, isNaN, float v)
STATIC_CLASS_METHOD(map)(Double, isInfinite, float v)
STATIC_CLASS_METHOD(map)(Double, compare, double d1, double d2)
END_CLASS
