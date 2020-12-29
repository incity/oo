#ifndef _OO_DOUBLE_H_
#define _OO_DOUBLE_H_

#include "Number.h"
#include "Comparable.h"

#define POSITIVE_INFINITY  1.0f / 0.0f
#define NEGATIVE_INFINITY -1.0f / 0.0f
#define NaN                0.0f / 0.0f

#define   public_final_class_DoubleClass(T, SuperClss)                      \
          extends_class(Number, abstract)(T, SuperClss)                    \
 implements_generic_interface(Comparable, T, Double*)                       \
                      CONSTRUCTOR(public)(T, double value);                \
                bool CLASS_METHOD(public)(T, isNaN);                       \
                bool CLASS_METHOD(public)(T, isInfinite);                  \
      String* CLASS_METHOD(public_static)(toString, double d);             \
         bool CLASS_METHOD(public_static)(isNaN, double d);                \
         bool CLASS_METHOD(public_static)(isInfinite, double d);           \
          int CLASS_METHOD(public_static)(compare, double d1, double d2);  \

#define public_final_class_Double(T)    \
         extends(Number, abstract)(T)  \
               implements(Comparable)  \
                   double _mValue;     \

DECLARE_CLASS(public_final)(Double, Number)

#endif /* _OO_DOUBLE_H_ */
