#ifndef _OO_BYTE_H_
#define _OO_BYTE_H_

#include "Number.h"
#include "Comparable.h"

#define      public_final_class_ByteClass(T, SuperClss)                 \
          extends_class(Number, abstract)(T, SuperClss)                 \
 implements_generic_interface(Comparable, T, Byte*)                     \
                      CONSTRUCTOR(public)(T, long value);               \
      String* CLASS_METHOD(public_static)(toString, long l);            \
      String* CLASS_METHOD(public_static)(toString, long l, int radix);

#define public_final_class_Byte(T)     \
         extends(Number, abstract)(T)  \
               implements(Comparable)  \
                    long _mValue;      \

DECLARE_CLASS(public_final)(Byte, Number)

#endif /* _OO_BYTE_H_ */
