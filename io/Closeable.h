#ifndef _OO_CLOSEABLE_H_
#define _OO_CLOSEABLE_H_

#include "lang/Ibject.h"

#define public_interface_Closeable(IF, T)         \
         extends_interface(Ibject)(IF, T)         \
             void CLASS_METHOD(public)(T, close);

DECLARE_INTERFACE(public)(Closeable)

#endif /* _OO_CLOSEABLE_H_ */
