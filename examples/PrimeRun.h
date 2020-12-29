#ifndef _OO_PRIME_RUN_H_
#define _OO_PRIME_RUN_H_

#include "lang/Object.h"
#include "lang/Runnable.h"

#define public_class_PrimeRunClass(T, SuperClss)   \
  	         extends_class(Object)(T, SuperClss)   \
    implements_interface(Runnable, T)

#define public_class_PrimeRun(T)   \
              extends(Object)(T)   \
         implements(Runnable)      \
         char* _mHelloWorld;

DECLARE_CLASS(public)(PrimeRun, Object)

#endif /* _OO_PRIME_RUN_H_ */
