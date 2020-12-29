//1. The .cc .cpp .cxx related header files
#include "Array.h"
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
static CONSTRUCTOR()(Array, void* array, int length)
{
    CONSTRUCTOR(super)(Object);
    self->_mArray= array;
    self->_mLength = length;
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
int CLASS_METHOD()(Array, getLength)
{
    return self->_mLength;
}

Object* CLASS_METHOD()(Array, get, int index)
{
    assert(index < self->_mLength);
    Object** objArr = (Object**)self->_mArray;
    return objArr[index];
}

bool CLASS_METHOD()(Array, getBool, int index)
{
    assert(index < self->_mLength);
    bool* boolArr = (bool*)self->_mArray;
    return boolArr[index];
}

char CLASS_METHOD()(Array, getChar, int index)
{
    assert(index < self->_mLength);
    char* charArr = (char*)self->_mArray;
    return charArr[index];
}

short CLASS_METHOD()(Array, getShort, int index)
{
    assert(index < self->_mLength);
    short* shortArr = (short*)self->_mArray;
    return shortArr[index];
}

int CLASS_METHOD()(Array, getInt, int index)
{
    assert(index < self->_mLength);
    int* intArr = (int*)self->_mArray;
    return intArr[index];
}

long CLASS_METHOD()(Array, getLong, int index)
{
    assert(index < self->_mLength);
    long* longArr = (long*)self->_mArray;
    return longArr[index];
}

float CLASS_METHOD()(Array, getFloat, int index)
{
    assert(index < self->_mLength);
    float* floatArr = (float*)self->_mArray;
    return floatArr[index];
}

double CLASS_METHOD()(Array, getDouble, int index)
{
    assert(index < self->_mLength);
    double* doubleArr = (double*)self->_mArray;
    return doubleArr[index];
}

String* CLASS_METHOD()(Array, getString, int index)
{
    assert(index < self->_mLength);
    String** stringArr = (String**)self->_mArray;
    return stringArr[index];
}

BEGIN_CLASS(Array, Object)
   CONSTRUCTOR(map)(Array, void* array, int length)
  CLASS_METHOD(map)(Array, getLength)
  CLASS_METHOD(map)(Array, get, int index)
  CLASS_METHOD(map)(Array, getBool, int index)
  CLASS_METHOD(map)(Array, getChar, int index)
  CLASS_METHOD(map)(Array, getShort, int index)
  CLASS_METHOD(map)(Array, getInt, int index)
  CLASS_METHOD(map)(Array, getLong, int index)
  CLASS_METHOD(map)(Array, getFloat, int index)
  CLASS_METHOD(map)(Array, getDouble, int index)
  CLASS_METHOD(map)(Array, getString, int index)
END_CLASS
