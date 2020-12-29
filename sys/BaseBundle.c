//1. The .cc .cpp .cxx related header files
#include "BaseBundle.h"
//2. C system include files.
#include <stdio.h>
#include <stdlib.h>
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.
#include "lang/Bool.h"
#include "lang/Byte.h"
#include "lang/Integer.h"
#include "lang/Short.h"
#include "lang/Long.h"
#include "lang/Float.h"
#include "lang/Double.h"
// #include "lang/Byte.h"
// #include "lang/Char.h"

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(BaseBundle)
{
    CONSTRUCTOR(super)(Object);
    self->_mMap = NEW(O2OHashMap);
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(BaseBundle)
{
    DELETE(self->_mMap);
    DESTRUCTOR(super)(Object);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
O2OHashMap* CLASS_METHOD()(BaseBundle, getMap)
{
    return self->_mMap;
}

int CLASS_METHOD()(BaseBundle, size)
{
    return _M(self->_mMap, size);
}

bool CLASS_METHOD()(BaseBundle, isEmpty)
{
    return _M(self->_mMap, isEmpty);
}

void CLASS_METHOD()(BaseBundle, clear)
{
    return _M(self->_mMap, clear);
}

bool CLASS_METHOD()(BaseBundle, containsKey, String* key)
{
    return _M(self->_mMap, containsKey, (Object*)key);
}

Object* CLASS_METHOD()(BaseBundle, get, String* key)
{
    return _M(self->_mMap, get, (Object*)key);
}

void CLASS_METHOD()(BaseBundle, remove, String* key)
{
    _M(self->_mMap, remove, (Object*)key);
}

void CLASS_METHOD()(BaseBundle, putBool, String* key, bool value)
{
    Bool* b = NEW(Bool, value);
    _M(self->_mMap, put, (Object*)key, (Object*)b);
    DELETE(b);
}

void CLASS_METHOD()(BaseBundle, putByte, String* key, byte value)
{
    Byte* b = NEW(Byte, value);
    _M(self->_mMap, put, (Object*)key, (Object*)b);
    DELETE(b);
}

void CLASS_METHOD()(BaseBundle, putChar, String* key, char value)
{
}

void CLASS_METHOD()(BaseBundle, putShort, String* key, short value)
{
    Short* s = NEW(Short, value);
    _M(self->_mMap, put, (Object*)key, (Object*)s);
    DELETE(s);
}

void CLASS_METHOD()(BaseBundle, putInt, String* key, int value)
{
    Integer* i = NEW(Integer, value);
    _M(self->_mMap, put, (Object*)key, (Object*)i);
    DELETE(i);
}

void CLASS_METHOD()(BaseBundle, putLong, String* key, long value)
{
    Long* l = NEW(Long, value);
    _M(self->_mMap, put, (Object*)key, (Object*)l);
    DELETE(l);
}

void CLASS_METHOD()(BaseBundle, putFloat, String* key, float value)
{
    Float* f = NEW(Float, value);
    _M(self->_mMap, put, (Object*)key, (Object*)f);
    DELETE(f);
}

void CLASS_METHOD()(BaseBundle, putDouble, String* key, double value)
{
    Double* d = NEW(Double, value);
    _M(self->_mMap, put, (Object*)key, (Object*)d);
    DELETE(d);
}

void CLASS_METHOD()(BaseBundle, putString, String* key, String* value)
{
    _M(self->_mMap, put, (Object*)key, (Object*)value);
}

void CLASS_METHOD()(BaseBundle, putCString, String* key, const char* value)
{
    String* s = NEW(String, value);
    _M(self->_mMap, put, (Object*)key, (Object*)s);
    DELETE(s);
}

bool CLASS_METHOD()(BaseBundle, getBool, String* key)
{
    return self(getBool, key, false);
}

bool CLASS_METHOD()(BaseBundle, getBool, String* key, bool defaultValue)
{
    Object* o = _M(self->_mMap, get, (Object*)key);
    if (o == NULL)
        return defaultValue;
    Bool* b = (Bool*)o;
    return _M(b, boolValue);
}

byte CLASS_METHOD()(BaseBundle, getByte, String* key)
{
    return self(getByte, 0);
}

byte CLASS_METHOD()(BaseBundle, getByte, String* key, byte defaultValue)
{
    Object* o = _M(self->_mMap, get, (Object*)key);
    if (o == NULL)
        return defaultValue;
    Byte* b = (Byte*)o;
    return _M(b, byteValue);
}

char CLASS_METHOD()(BaseBundle, getChar, String* key)
{
    return self(getByte, 0);
}

char CLASS_METHOD()(BaseBundle, getChar, String* key, char defaultValue)
{
    return 0;
}

short CLASS_METHOD()(BaseBundle, getShort, String* key)
{
    return self(getShort, key, 0);
}

short CLASS_METHOD()(BaseBundle, getShort, String* key, short defaultValue)
{
    Object* o = _M(self->_mMap, get, (Object*)key);
    if (o == NULL)
        return defaultValue;
    Short* s = (Short*)o;
    return _M(s, shortValue);
}

int CLASS_METHOD()(BaseBundle, getInt, String* key)
{
    return self(getInt, key, 0);
}

int CLASS_METHOD()(BaseBundle, getInt, String* key, int defaultValue)
{
    Object* o = _M(self->_mMap, get, (Object*)key);
    if (o == NULL)
        return defaultValue;
    Integer* i = (Integer*)o;
    return _M(i, intValue);
}

long CLASS_METHOD()(BaseBundle, getLong, String* key)
{
    return self(getLong, key, 0);
}

long CLASS_METHOD()(BaseBundle, getLong, String* key, long defaultValue)
{
    Object* o = _M(self->_mMap, get, (Object*)key);
    if (o == NULL)
        return defaultValue;
    Long* l = (Long*)o;
    return _M(l, longValue);
}

float CLASS_METHOD()(BaseBundle, getFloat, String* key)
{
    return self(getFloat, key, 0.0f);
}

float CLASS_METHOD()(BaseBundle, getFloat, String* key, float defaultValue)
{
    Object* o = _M(self->_mMap, get, (Object*)key);
    if (o == NULL)
        return defaultValue;
    Float* f = (Float*)o;
    return _M(f, floatValue);
}

double CLASS_METHOD()(BaseBundle, getDouble, String* key)
{
    return self(getDouble, key, 0.0);
}

double CLASS_METHOD()(BaseBundle, getDouble, String* key, double defaultValue)
{
    Object* o = _M(self->_mMap, get, (Object*)key);
    if (o == NULL)
        return defaultValue;
    Double* f = (Double*)o;
    return _M(f, doubleValue);
}

String* CLASS_METHOD()(BaseBundle, getString, String* key)
{
    return self(getString, key, NULL);
}

String* CLASS_METHOD()(BaseBundle, getString, String* key, String* defaultValue)
{
    Object* o = _M(self->_mMap, get, (Object*)key);
    if (o == NULL)
        return defaultValue;
    return (String*)o;
}

BEGIN_CLASS(BaseBundle, Object)
     CONSTRUCTOR(map)(BaseBundle)
      DESTRUCTOR(map)(BaseBundle)
    CLASS_METHOD(map)(BaseBundle, getMap)
    CLASS_METHOD(map)(BaseBundle, size)
    CLASS_METHOD(map)(BaseBundle, isEmpty)
    CLASS_METHOD(map)(BaseBundle, clear)
    CLASS_METHOD(map)(BaseBundle, containsKey, String* key)
    CLASS_METHOD(map)(BaseBundle, get, String* key)
    CLASS_METHOD(map)(BaseBundle, remove, String* key)
    CLASS_METHOD(map)(BaseBundle, putBool, String* key, bool value)
    CLASS_METHOD(map)(BaseBundle, putByte, String* key, byte value)
    CLASS_METHOD(map)(BaseBundle, putChar, String* key, char value)
    CLASS_METHOD(map)(BaseBundle, putShort, String* key, short value)
    CLASS_METHOD(map)(BaseBundle, putInt, String* key, int value)
    CLASS_METHOD(map)(BaseBundle, putLong, String* key, long value)
    CLASS_METHOD(map)(BaseBundle, putFloat, String* key, float value)
    CLASS_METHOD(map)(BaseBundle, putDouble, String* key, double value)
    CLASS_METHOD(map)(BaseBundle, putString, String* key, String* value)
    CLASS_METHOD(map)(BaseBundle, putCString, String* key, const char* value)
    CLASS_METHOD(map)(BaseBundle, getBool, String* key)
    CLASS_METHOD(map)(BaseBundle, getBool, String* key, bool defaultValue)
    CLASS_METHOD(map)(BaseBundle, getByte, String* key)
    CLASS_METHOD(map)(BaseBundle, getByte, String* key, byte defaultValue)
    CLASS_METHOD(map)(BaseBundle, getChar, String* key)
    CLASS_METHOD(map)(BaseBundle, getChar, String* key, char defaultValue)
    CLASS_METHOD(map)(BaseBundle, getShort, String* key)
    CLASS_METHOD(map)(BaseBundle, getShort, String* key, short defaultValue)
    CLASS_METHOD(map)(BaseBundle, getInt, String* key)
    CLASS_METHOD(map)(BaseBundle, getInt, String* key, int defaultValue)
    CLASS_METHOD(map)(BaseBundle, getLong, String* key)
    CLASS_METHOD(map)(BaseBundle, getLong, String* key, long defaultValue)
    CLASS_METHOD(map)(BaseBundle, getFloat, String* key)
    CLASS_METHOD(map)(BaseBundle, getFloat, String* key, float defaultValue)
    CLASS_METHOD(map)(BaseBundle, getDouble, String* key)
    CLASS_METHOD(map)(BaseBundle, getDouble, String* key, double defaultValue)
    CLASS_METHOD(map)(BaseBundle, getString, String* key)
    CLASS_METHOD(map)(BaseBundle, getString, String* key, String* defaultValue)
END_CLASS
