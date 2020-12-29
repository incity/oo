#ifndef _OO_ITERATOR_H_
#define _OO_ITERATOR_H_

#include "lang/Object.h"
#include "lang/Ibject.h"

#define public_generic_interface_Iterator(IF, T, E)         \
                extends_interface(Ibject)(IF, T)            \
                    bool CLASS_METHOD(public)(T, hasNext);  \
                       E CLASS_METHOD(public)(T, next);     \
                    void CLASS_METHOD(public)(T, remove);

DECLARE_INTERFACE(public_generic)(ObjectIterator, Iterator, Object*)

#define public_generic_interface_ListIterator(IF, T, E)                \
          extends_generic_interface(Iterator)(IF, T, E)                \
                        bool CLASS_METHOD(public)(T, hasPrevious);     \
                           E CLASS_METHOD(public)(T, previous);        \
                         int CLASS_METHOD(public)(T, nextIndex);       \
                         int CLASS_METHOD(public)(T, previousIndex);   \
                        void CLASS_METHOD(public)(T, set, E e);        \
                        void CLASS_METHOD(public)(T, add, E e);        \

DECLARE_INTERFACE(public_generic)(ObjectListIterator, ListIterator, Object*)
DECLARE_INTERFACE(public_generic)(ObjectVectorIterator, ListIterator, Object*)

#endif /* _OO_ITERATOR_H_ */
