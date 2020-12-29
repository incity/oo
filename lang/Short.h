#ifndef _OO_SHORT_H_
#define _OO_SHORT_H_

#include "lang/Number.h"
#include "lang/Comparable.h"

#define     public_final_class_ShortClass(T, SuperClss)          \
          extends_class(Number, abstract)(T, SuperClss)          \
 implements_generic_interface(Comparable, T, Short*)             \
                      CONSTRUCTOR(public)(T, short value);       \
      String* CLASS_METHOD(public_static)(toString, short s);    \

#define public_final_class_Short(T)    \
         extends(Number, abstract)(T)  \
               implements(Comparable)  \
                    short _mValue;     \

DECLARE_CLASS(public_final)(Short, Number)

#endif /* _OO_SHORT_H_ */
