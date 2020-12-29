#ifndef _OO_STRING_BUFFER_H_
#define _OO_STRING_BUFFER_H_

#include "Object.h"
#include "String.h"

#define public_final_class_StringBufferClass(T, SuperClss)                                        \
                  extends_class(Object)(T, SuperClss)                                             \
                    CONSTRUCTOR(public)(T, int capacity);                                         \
               int CLASS_METHOD(public)(T, length);                                               \
               int CLASS_METHOD(public)(T, capacity);                                             \
       const char* CLASS_METHOD(public)(T, getCString);                                           \
              void CLASS_METHOD(public)(T, ensureCapacity, int minimumCapacity);                  \
              void CLASS_METHOD(public)(T, expandCapacity, int minimumCapacity);                  \
              char CLASS_METHOD(public)(T, charAt, int index);                                    \
              void CLASS_METHOD(public)(T, setCharAt, int index, char ch);                        \
     T* CLASS_METHOD(public)(T, appendCString, const char* str);                                  \
     T* CLASS_METHOD(public)(T, appendCString, const char* str, int offset, int len);             \
     T* CLASS_METHOD(public)(T, appendString, String* str);                                       \
     T* CLASS_METHOD(public)(T, appendString, String* str, int start, int end);                   \
     T* CLASS_METHOD(public)(T, appendChar, char c);                                              \
     T* CLASS_METHOD(public)(T, appendBool, bool b);                                              \
     T* CLASS_METHOD(public)(T, appendShort, short s);                                            \
     T* CLASS_METHOD(public)(T, appendInt, int i);                                                \
     T* CLASS_METHOD(public)(T, appendLong, long lng);                                            \
     T* CLASS_METHOD(public)(T, appendFloat, float f);                                            \
     T* CLASS_METHOD(public)(T, appendDouble, double d);                                          \
     T* CLASS_METHOD(public)(T, appendObject, Object* obj);                                       \
     T* CLASS_METHOD(public)(T, insertCString, int offset, const char* str);                      \
     T* CLASS_METHOD(public)(T, insertCString, int index, const char* str, int offset, int len);  \
     T* CLASS_METHOD(public)(T, insertString, int offset, String* str);                           \
     T* CLASS_METHOD(public)(T, insertChar, int offset, char c);                                  \
     T* CLASS_METHOD(public)(T, insertBool, int offset, bool b);                                  \
     T* CLASS_METHOD(public)(T, insertInt, int offset, int i);                                    \
     T* CLASS_METHOD(public)(T, insertLong, int offset, long lng);                                \
     T* CLASS_METHOD(public)(T, insertFloat, int offset, float f);                                \
     T* CLASS_METHOD(public)(T, insertDouble, int offset, double d);                              \
     T* CLASS_METHOD(public)(T, insertObject, int offset, Object obj);                            \

#define public_final_class_StringBuffer(T)  \
            extends(Object)(T)              \
            int _mCapacity;                 \
            int _mLength;                   \
            char* _mStr;

DECLARE_CLASS(public_final)(StringBuffer, Object)

#endif /* _OO_STRING_BUFFER_H_ */
