#ifndef _OO_ARRAY_H_
#define _OO_ARRAY_H_

#include "Object.h"

#define NEW_ARRAY(Type, n) NEW(Array, malloc(n*sizeof(Type)), n)

#define public_final_class_ArrayClass(T, SuperClss)                    \
                extends_class(Object)(T, SuperClss)                    \
                  CONSTRUCTOR(public)(T, void* array, int length);     \
             int CLASS_METHOD(public)(T, getLength);                   \
         Object* CLASS_METHOD(public)(T, get, int index);              \
            bool CLASS_METHOD(public)(T, getBool, int index);          \
            char CLASS_METHOD(public)(T, getChar, int index);          \
           short CLASS_METHOD(public)(T, getShort, int index);         \
             int CLASS_METHOD(public)(T, getInt, int index);           \
            long CLASS_METHOD(public)(T, getLong, int index);          \
           float CLASS_METHOD(public)(T, getFloat, int index);         \
          double CLASS_METHOD(public)(T, getDouble, int index);        \
         String* CLASS_METHOD(public)(T, getString, int index);

#define public_final_class_Array(T)    \
                 extends(Object)(T)    \
                 void* _mArray;        \
                   int _mLength;       \

DECLARE_CLASS(public_final)(Array, Object)

#endif /* _OO_ARRAY_H_ */
