#ifndef _OO_STRING_H_
#define _OO_STRING_H_

#include "Object.h"
#include <stdarg.h>

#define public_final_class_StringClass(T, SuperClss)                                                        \
                 extends_class(Object)(T, SuperClss)                                                        \
                   CONSTRUCTOR(public)(T, const char* str);                                                 \
                   CONSTRUCTOR(public)(T, const char* str, int offset, int count);                          \
             CONST_CONSTRUCTOR(public)(T, const char* str);                                                 \
              int CLASS_METHOD(public)(T, length);                                                          \
       String* CLASS_METHOD(0)(public)(T, format, const char* format, ...);                                 \
          String* CLASS_METHOD(public)(T, format, const char* format, va_list ap);                          \
          String* CLASS_METHOD(public)(T, toLowerCase);                                                     \
          String* CLASS_METHOD(public)(T, toUpperCase);                                                     \
      const char* CLASS_METHOD(public)(T, getCString);                                                      \
      const char* CLASS_METHOD(public)(T, getCString, int off);                                             \
             void CLASS_METHOD(public)(T, getChars, char* dst, int dstBegin);                               \
             void CLASS_METHOD(public)(T, getChars, int srcBegin, int srcEnd, char* dst, int dstBegin);     \
             bool CLASS_METHOD(public)(T, equalsToCString, const char* str);                                \
             bool CLASS_METHOD(public)(T, equalsToCStringIgnoreCase, const char* str);                      \
             bool CLASS_METHOD(public)(T, equalsIgnoreCase, String* anotherString);                         \
              int CLASS_METHOD(public)(T, compareTo, String* anotherString);                                \
              int CLASS_METHOD(public)(T, compareToIgnoreCase, String* str);                                \
              int CLASS_METHOD(public)(T, compareToCString, const char* str);                               \
              int CLASS_METHOD(public)(T, compareToCStringIgnoreCase, const char* str);                     \
          String* CLASS_METHOD(public)(T, concat, String* str);                                             \
          String* CLASS_METHOD(public)(T, concatChar, char c);                                              \
          String* CLASS_METHOD(public)(T, concatCString, const char* str);                                  \
             char CLASS_METHOD(public)(T, charAt, int index);                                               \
              int CLASS_METHOD(public)(T, indexOf, String* str, int fromIndex);                             \
              int CLASS_METHOD(public)(T, indexOf, String* str);                                            \
              int CLASS_METHOD(public)(T, indexOfChar, int ch, int fromIndex);                              \
              int CLASS_METHOD(public)(T, indexOfChar, int ch);                                             \
              int CLASS_METHOD(public)(T, lastIndexOfChar, int ch, int fromIndex);                          \
              int CLASS_METHOD(public)(T, lastIndexOfChar, int ch);                                         \
              int CLASS_METHOD(public)(T, lastIndexOf, String* str, int fromIndex);                         \
              int CLASS_METHOD(public)(T, lastIndexOf, String* str);                                        \
          String* CLASS_METHOD(public)(T, substring, int beginIndex, int endIndex);                         \
          String* CLASS_METHOD(public)(T, substring, int beginIndex);                                       \

#define public_final_class_String(T) \
                  extends(Object)(T) \
                    int _mHash;      \
                    int _mLength;    \
                  char* _mStr;

DECLARE_CLASS(public_final)(String, Object)

#endif /* _OO_STRING_H_ */
