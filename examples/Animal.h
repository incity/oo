#ifndef _OO_ANIMAL_H_
#define _OO_ANIMAL_H_

#include "lang/Object.h"

#define public_class_AnimalClass(T, SuperClss)                  \
    	   extends_class(Object)(T, SuperClss)                  \
    	     CONSTRUCTOR(public)(T, int breed, int age);        \
       void CLASS_METHOD(public)(T, eat);                       \
       void CLASS_METHOD(public)(T, grow);                      \
                     GET(public)(T, bool, _mIsWild, IsWild);    \
                     SET(public)(T, bool, _mIsWild, IsWild);    \
                     GET(public)(T, int, _mAge, Age);           \
                     SET(public)(T, int, _mAge, Age);

#define public_class_Animal(T)  \
            extends(Object)(T)  \
            bool _mIsWild;      \
             int _mAge;

DECLARE_CLASS(public)(Animal, Object)

#endif /* _OO_ANIMAL_H_ */
