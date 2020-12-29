//1. The .cc .cpp .cxx related header files
#include "Float.h"
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
static CONSTRUCTOR()(Float, float value)
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
 * Returns the value of this {@code Float} as a
 * {@code byte}.
 */
static byte CLASS_METHOD()(Float, byteValue)
{
    return (byte)self->_mValue;
}

/**
 * Returns the value of this {@code Float} as a
 * {@code short}.
 */
static short CLASS_METHOD()(Float, shortValue)
{
    return (short)self->_mValue;
}

/**
 * Returns the value of this {@code Float} as an
 * {@code int}.
 */
static int CLASS_METHOD()(Float, intValue)
{
    return (int)self->_mValue;
}

/**
 * Returns the value of this {@code Float} as a
 * {@code long}.
 */
static long CLASS_METHOD()(Float, longValue)
{
    return (long)self->_mValue;
}

/**
 * Returns the value of this {@code Float} as a
 * {@code float}.
 */
static float CLASS_METHOD()(Float, floatValue)
{
    return self->_mValue;
}

/**
 * Returns the value of this {@code Float} as a
 * {@code double}.
 */
static double CLASS_METHOD()(Float, doubleValue)
{
    return (double)self->_mValue;
}

static String* STATIC_CLASS_METHOD()(Float, toString, float f)
{
    String* str = NEW(String);
    _M0(str, format, "%f", f);
    return str;
}

static String* CLASS_METHOD()(Float, toString)
{
    String* rv = _SM(Float, toString, self->_mValue);
    return rv;
}

/*
 * Find the float corresponding to a given bit pattern
 */
static inline float intBitsToFloat(int i)
{
    union {
        int i;
        float f;
    } u;
    u.i = i;
    return u.f;
}

/*
 * Find the bit pattern corresponding to a given float, NOT collapsing NaNs
 */
static inline int floatToIntBits(float f)
{
    union {
        int i;
        float f;
    } u;
    u.f = f;
    return u.i;
}

static bool CLASS_METHOD()(Float, equals, Object* obj)
{
    if ((Object*)self == obj)
        return true;

    if (INSTANCEOF(obj, Float)) {
        Float* f = (Float*)obj;
        return floatToIntBits(self->_mValue) == floatToIntBits(f->_mValue);
    }
    return false;
}

int STATIC_CLASS_METHOD()(Float, compare, float f1, float f2)
{
    if (f1 < f2)
        return -1;           // Neither val is NaN, thisVal is smaller
    if (f1 > f2)
        return 1;            // Neither val is NaN, thisVal is larger

    // Cannot use floatToRawIntBits because of possibility of NaNs.
    int thisBits    = floatToIntBits(f1);
    int anotherBits = floatToIntBits(f2);

    return (thisBits == anotherBits ?  0 : // Values are equal
            (thisBits < anotherBits ? -1 : // (-0.0, 0.0) or (!NaN, NaN)
             1));                          // (0.0, -0.0) or (NaN, !NaN)
}

static int CLASS_METHOD()(Float, compareTo, Float* anotherFloat)
{
    return _SM(Float, compare, self->_mValue, anotherFloat->_mValue);
}

static int CLASS_METHOD()(Float, hashCode)
{
    return floatToIntBits(self->_mValue);
}

static bool STATIC_CLASS_METHOD()(Float, isNaN, float v)
{
    return (v != v);
}

static bool STATIC_CLASS_METHOD()(Float, isInfinite, float v)
{
    return (v == POSITIVE_INFINITY) || (v == NEGATIVE_INFINITY);
}

static bool CLASS_METHOD()(Float, isNaN)
{
    return _SM(Float, isNaN, self->_mValue);
}

static bool CLASS_METHOD()(Float, isInfinite)
{
    return _SM(Float, isInfinite, self->_mValue);
}

BEGIN_CLASS(Float, Number)
   IMPLEMENTS(Float, Comparable)
   CONSTRUCTOR(map)(Float, int value)
  CLASS_METHOD(map)(Float, byteValue)
  CLASS_METHOD(map)(Float, shortValue)
  CLASS_METHOD(map)(Float, intValue)
  CLASS_METHOD(map)(Float, longValue)
  CLASS_METHOD(map)(Float, floatValue)
  CLASS_METHOD(map)(Float, doubleValue)
  CLASS_METHOD(map)(Float, toString)
  CLASS_METHOD(map)(Float, compareTo, Float* anotherFloat)
  CLASS_METHOD(map)(Float, hashCode)
  CLASS_METHOD(map)(Float, equals, Object* obj)
  CLASS_METHOD(map)(Float, isNaN)
  CLASS_METHOD(map)(Float, isInfinite)
STATIC_CLASS_METHOD(map)(Float, toString, float f)
STATIC_CLASS_METHOD(map)(Float, isNaN, float v)
STATIC_CLASS_METHOD(map)(Float, isInfinite, float v)
STATIC_CLASS_METHOD(map)(Float, compare, float f1, float f2)
END_CLASS
