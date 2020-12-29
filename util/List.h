#ifndef _OO_LIST_H_
#define _OO_LIST_H_

#include "Collection.h"
//#include "ListIterator.h"

#define public_generic_interface_List(IF, T, E, Itr)                        \
extends_generic_interface(Collection)(IF, T, E, Itr)                        \
                void CLASS_METHOD(public)(T, add, int index, E element);    \
                   E CLASS_METHOD(public)(T, get, int index);               \
                   E CLASS_METHOD(public)(T, set, int index, E element);    \
                   E CLASS_METHOD(public)(T, remove, int index);            \
                 int CLASS_METHOD(public)(T, indexOf, Object* o);           \
                 int CLASS_METHOD(public)(T, lastIndexOf, Object* o);       \
                 Itr CLASS_METHOD(public)(T, listIterator);                 \
                 Itr CLASS_METHOD(public)(T, listIterator, int index);      \

DECLARE_INTERFACE(public_generic)(ObjectList, List, Object*, ObjectIterator*)

#endif /* _OO_LIST_H_ */
