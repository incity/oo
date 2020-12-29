#ifndef _OO_LONG_H_
#define _OO_LONG_H_

#include "Number.h"
#include "Comparable.h"

#define   public_final_class_LongClass(T, SuperClss)                    \
          extends_class(Number, abstract)(T, SuperClss)                 \
 implements_generic_interface(Comparable, T, Long*)                     \
                      CONSTRUCTOR(public)(T, long value);               \
      String* CLASS_METHOD(public_static)(toString, long l);            \
      String* CLASS_METHOD(public_static)(toString, long l, int radix);

#define public_final_class_Long(T)     \
         extends(Number, abstract)(T)  \
               implements(Comparable)  \
                    long _mValue;      \

DECLARE_CLASS(public_final)(Long, Number)

#endif /* _OO_LONG_H_ */
