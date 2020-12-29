#ifndef _OO_SIZE_H_
#define _OO_SIZE_H_

#include "lang/String.h"

DECLARE_CLASS(forward)(Size, Object)

#define public_class_SizeClass(T, SuperClss)                 \
         extends_class(Object)(T, SuperClss)                 \
           CONSTRUCTOR(public)(T, int width, int height);    \
 Size* CLASS_METHOD(public_static)(parseSize, String* size); \
                   GET(public)(T, int, _mWidth, Width);      \
                   SET(public)(T, int, _mWidth, Width);      \
                   GET(public)(T, int, _mHeight, Height);    \
                   SET(public)(T, int, _mHeight, Height);    \

#define public_class_Size(T)   \
          extends(Object)(T)   \
            int _mWidth;       \
            int _mHeight;      \

DECLARE_CLASS(public)(Size, Object)

#endif /* _OO_SIZE_H_ */
