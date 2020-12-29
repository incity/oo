#ifndef _OO_SELECTION_KEY_H_
#define _OO_SELECTION_KEY_H_

#include "SelectableChannel.h"

enum {
    OP_READ    = 1 << 0,
    OP_WRITE   = 1 << 1,
    OP_CONNECT = 1 << 2,
    OP_ACCEPT  = 1 << 3,
};

#define public_abstract_class_SelectionKeyClass(T, SuperClss)          \
          extends_class(Object)(T, SuperClss)                          \
       SelectableChannel* CLASS_METHOD(public_abstract)(T, channel);   \
      bool CLASS_METHOD(public_abstract)(T, isValid);                  \
      void CLASS_METHOD(public_abstract)(T, cancel);                   \
       int CLASS_METHOD(public_abstract)(T, interestOps);              \
        T* CLASS_METHOD(public_abstract)(T, interestOps,  int ops);    \
       int CLASS_METHOD(public_abstract)(T, readyOps);                 \
               bool CLASS_METHOD(public)(T, isReadable);               \
               bool CLASS_METHOD(public)(T, isWritable);               \
               bool CLASS_METHOD(public)(T, isConnectable);            \
               bool CLASS_METHOD(public)(T, isAcceptable);             \

#define public_abstract_class_SelectionKey(T)  \
          extends(Object)(T)                   \

DECLARE_CLASS(public_abstract)(SelectionKey, Object)

#endif /* _OO_SELECTION_KEY_H_ */
