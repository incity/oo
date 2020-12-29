#ifndef _OO_FLOAT_H_
#define _OO_FLOAT_H_

#include "Number.h"
#include "Comparable.h"

#define POSITIVE_INFINITY  1.0f / 0.0f
#define NEGATIVE_INFINITY -1.0f / 0.0f
#define NaN                0.0f / 0.0f

#define   public_final_class_FloatClass(T, SuperClss)                      \
          extends_class(Number, abstract)(T, SuperClss)                    \
 implements_generic_interface(Comparable, T, Float*)                       \
                      CONSTRUCTOR(public)(T, float value);                 \
                bool CLASS_METHOD(public)(T, isNaN);                       \
                bool CLASS_METHOD(public)(T, isInfinite);                  \
      String* CLASS_METHOD(public_static)(toString, float f);              \
         bool CLASS_METHOD(public_static)(isNaN, float f);                 \
         bool CLASS_METHOD(public_static)(isInfinite, float f);            \
          int CLASS_METHOD(public_static)(compare, float f1, float f2);    \

#define public_final_class_Float(T)    \
         extends(Number, abstract)(T)  \
               implements(Comparable)  \
                   float _mValue;      \

DECLARE_CLASS(public_final)(Float, Number)

#endif /* _OO_FLOAT_H_ */
