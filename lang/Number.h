#ifndef _OO_NUMBER_H_
#define _OO_NUMBER_H_

#include "Object.h"

#define public_abstract_class_NumberClass(T, SuperClss)        \
                    extends_class(Object)(T, SuperClss)        \
                byte CLASS_METHOD(public)(T, byteValue);       \
               short CLASS_METHOD(public)(T, shortValue);      \
                 int CLASS_METHOD(public)(T, intValue);        \
                long CLASS_METHOD(public)(T, longValue);       \
               float CLASS_METHOD(public)(T, floatValue);      \
              double CLASS_METHOD(public)(T, doubleValue);     \

#define public_abstract_class_Number(T)    \
                     extends(Object)(T)    \

DECLARE_CLASS(public_abstract)(Number, Object)

#endif /* _OO_NUMBER_H_ */
