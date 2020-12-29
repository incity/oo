#ifndef _OO_QUEUE_H_
#define _OO_QUEUE_H_

#include "Collection.h"

#define public_interface_Queue(Interface, ClassImpl, override...)         \
          extends_interface(override)(Collection, Interface, ClassImpl)   \
           void* CLASS_METHOD(public)(ClassImpl, peek);                   \
           void* CLASS_METHOD(public)(ClassImpl, poll);                   \
           void* CLASS_METHOD(public)(ClassImpl, remove);

DECLARE_INTERFACE(Queue)

#endif /* _OO_QUEUE_H_ */
