#ifndef _OO_RUNNABLE_H_
#define _OO_RUNNABLE_H_

#include "Ibject.h"

#define public_interface_Runnable(IF, T)        \
        extends_interface(Ibject)(IF, T)        \
            void CLASS_METHOD(public)(T, run);

DECLARE_INTERFACE(public)(Runnable)

#endif /* _OO_RUNNABLE_H_ */
