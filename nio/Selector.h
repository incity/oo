#ifndef _OO_SELECTOR_H_
#define _OO_SELECTOR_H_

#include "SelectableChannel.h"

enum {
    OP_READ    = 1 << 0,
    OP_WRITE   = 1 << 1,
    OP_CONNECT = 1 << 2,
    OP_ACCEPT  = 1 << 3,
};

#define public_abstract_class_SelectorClass(T, SuperClss)                \
                      extends_class(Object)(T, SuperClss)                \
         bool CLASS_METHOD(public_abstract)(T, isOpen);                  \
          int CLASS_METHOD(public_abstract)(T, selectNow);               \
          int CLASS_METHOD(public_abstract)(T, select, long timeout);    \
          int CLASS_METHOD(public_abstract)(T, select);                  \
         void CLASS_METHOD(public_abstract)(T, close);                   \
     Selector * CLASS_METHOD(public_static)(open);                       \

#define public_abstract_class_Selector(T)  \
          extends(Object)(T)               \

DECLARE_CLASS(public_abstract)(Selector, Object)

#endif /* _OO_SELECTOR_H_ */
