#ifndef _OO_DEQUE_H_
#define _OO_DEQUE_H_

#include "Queue.h"

#define public_generic_interface_Deque(IF, ClassImpl, override...)         \
              extends_interface(override)(Queue, Interface, ClassImpl)    \
                void CLASS_METHOD(public)(ClassImpl, addFirst, void* e);  \
                void CLASS_METHOD(public)(ClassImpl, addLast, void* e);   \
               void* CLASS_METHOD(public)(ClassImpl, getFirst);           \
               void* CLASS_METHOD(public)(ClassImpl, getLast);            \
               void* CLASS_METHOD(public)(ClassImpl, peekFirst);          \
               void* CLASS_METHOD(public)(ClassImpl, peekLast);           \
               void* CLASS_METHOD(public)(ClassImpl, pollFirst);          \
               void* CLASS_METHOD(public)(ClassImpl, pollLast);           \
               void* CLASS_METHOD(public)(ClassImpl, removeFirst);        \
               void* CLASS_METHOD(public)(ClassImpl, removeLast);         \
               void* CLASS_METHOD(public)(ClassImpl, pop);                \
                void CLASS_METHOD(public)(ClassImpl, push, void* e);

#define implements_Deque(override...)   \
            implements(override)(Queue)

DECLARE_INTERFACE(Deque)

#endif /* _OO_DEQUE_H_ */
