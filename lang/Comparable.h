#ifndef _OO_COMPARABLE_H_
#define _OO_COMPARABLE_H_

#include "Ibject.h"

#define public_generic_interface_Comparable(IF, T, TO)               \
                  extends_interface(Ibject)(IF, T)                   \
                       int CLASS_METHOD(public)(T, compareTo, TO o);

DECLARE_INTERFACE(public_generic)(Comparable, Comparable, Object*)

#endif /* _OO_COMPARABLE_H_ */
