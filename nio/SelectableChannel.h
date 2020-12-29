#ifndef _OO_SELECTABLE_CHANNEL_H_
#define _OO_SELECTABLE_CHANNEL_H_

#include "lang/Object.h"

#define public_abstract_class_SelectableChannelClass(T, SuperClss)            \
                   extends_class(Object)(T, SuperClss)                        \
       int CLASS_METHOD(public_abstract)(T, validOps);                        \
      bool CLASS_METHOD(public_abstract)(T, isRegistered);                    \
      bool CLASS_METHOD(public_abstract)(T, isBlocking);                      \
        T* CLASS_METHOD(public_abstract)(T, configureBlocking, bool block);   \

#define public_abstract_class_SelectableChannel(T)    \
            extends(Object)(T)                        \
            int _mTotalChannels;                      \
           int* _mPollArray;                          \

DECLARE_CLASS(public_abstract)(SelectableChannel, Object)

#endif /* _OO_SELECTABLE_CHANNEL_H_ */
