#ifndef _OO_BOOL_H_
#define _OO_BOOL_H_

#include "lang/Object.h"
#include "lang/String.h"
#include "lang/Comparable.h"

#define      public_final_class_BoolClass(T, SuperClss)             \
                    extends_class(Object)(T, SuperClss)             \
 implements_generic_interface(Comparable, T, Bool*)                 \
                      CONSTRUCTOR(public)(T, bool value);           \
                bool CLASS_METHOD(public)(T, boolValue);            \
         bool CLASS_METHOD(public_static)(parseBool, String* s);    \

#define public_final_class_Bool(T)     \
                extends(Object)(T)     \
               implements(Comparable)  \
                    bool _mValue;      \

DECLARE_CLASS(public_final)(Bool, Object)

DECLARE()(TRUE,  Bool)
DECLARE()(FALSE, Bool)

#endif /* _OO_BOOL_H_ */
