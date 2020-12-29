#ifndef _OO_ITERABLE_H_
#define _OO_ITERABLE_H_

#include "Iterator.h"

#define public_generic_interface_Iterable(IF, T, Itr)           \
                 extends_interface(Ibject)(IF, T)               \
                    Itr CLASS_METHOD(public)(T, iterator);

DECLARE_INTERFACE(public_generic)(Iterable, Iterable, ObjectIterator*)

#endif /* _OO_ITERABLE_H_ */
