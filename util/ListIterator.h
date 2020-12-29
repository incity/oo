#ifndef _OO_LIST_ITERATOR_H_
#define _OO_LIST_ITERATOR_H_

#include "Iterator.h"

#define public_interface_ListIterator(Interface, ClassImpl, override...)    \
          extends_interface(override)(Iterator, Interface, ClassImpl)       \
            bool CLASS_METHOD(public)(ClassImpl, hasPrevious);              \
           void* CLASS_METHOD(public)(ClassImpl, previous);                 \
             int CLASS_METHOD(public)(ClassImpl, nextIndex);                \
             int CLASS_METHOD(public)(ClassImpl, previousIndex);            \
            void CLASS_METHOD(public)(ClassImpl, set, void* e);             \
            void CLASS_METHOD(public)(ClassImpl, add, void* e); 

DECLARE_INTERFACE(ListIterator)

#endif /* _OO_LIST_ITERATOR_H_ */
