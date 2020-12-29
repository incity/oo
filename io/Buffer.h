#ifndef _OO_BUFFER_H_
#define _OO_BUFFER_H_

#include "lang/Object.h"

#define public_abstract_class_BufferClass(T, SuperClss)                               \
                    extends_class(Object)(T, SuperClss)                               \
                      CONSTRUCTOR(public)(T, int mark, int pos, int lim, int cap);    \
           int CLASS_METHOD(public_final)(T, capacity);                               \
           int CLASS_METHOD(public_final)(T, position);                               \
       Buffer* CLASS_METHOD(public_final)(T, position, int newPosition);              \
           int CLASS_METHOD(public_final)(T, limit);                                  \
       Buffer* CLASS_METHOD(public_final)(T, limit, int newLimit);                    \
       Buffer* CLASS_METHOD(public_final)(T, mark);                                   \
       Buffer* CLASS_METHOD(public_final)(T, reset);                                  \
       Buffer* CLASS_METHOD(public_final)(T, clear);                                  \
       Buffer* CLASS_METHOD(public_final)(T, flip);                                   \
       Buffer* CLASS_METHOD(public_final)(T, rewind);                                 \
           int CLASS_METHOD(public_final)(T, remaining);                              \
          bool CLASS_METHOD(public_final)(T, hasRemaining);                           \
          bool CLASS_METHOD(public_final)(T, isReadOnly);                             \
                  int CLASS_METHOD(final)(T, markValue);                              \
                 void CLASS_METHOD(final)(T, truncate);                               \
                 void CLASS_METHOD(final)(T, discardMark);                            \

#define public_abstract_class_Buffer(T)    \
                     extends(Object)(T)    \
                     int _mMark;           \
                     int _mPosition;       \
                     int _mLimit;          \
                     int _mCapacity;       \
                   char* _mBuffer;         \

DECLARE_CLASS(public_abstract)(Buffer, Object)

#endif /* _OO_BUFFER_H_ */
