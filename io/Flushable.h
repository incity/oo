#ifndef _OO_FLUSHABLE_H_
#define _OO_FLUSHABLE_H_

#include "lang/Ibject.h"

#define public_interface_Flushable(IF, T)         \
         extends_interface(Ibject)(IF, T)         \
             void CLASS_METHOD(public)(T, flush);

DECLARE_INTERFACE(public)(Flushable)

#endif /* _OO_FLUSHABLE_H_ */
