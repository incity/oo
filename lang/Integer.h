#ifndef _OO_INTEGER_H_
#define _OO_INTEGER_H_

#include "Number.h"
#include "Comparable.h"

#define   public_final_class_IntegerClass(T, SuperClss)                 \
          extends_class(Number, abstract)(T, SuperClss)                 \
 implements_generic_interface(Comparable, T, Integer*)                  \
                      CONSTRUCTOR(public)(T, int value);                \
      String* CLASS_METHOD(public_static)(toString, int i);             \
      String* CLASS_METHOD(public_static)(toString, int i, int radix);

#define public_final_class_Integer(T)  \
         extends(Number, abstract)(T)  \
               implements(Comparable)  \
                     int _mValue;      \

DECLARE_CLASS(public_final)(Integer, Number)

#endif /* _OO_INTEGER_H_ */
