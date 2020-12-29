#ifndef _OO_THREAD_H_
#define _OO_THREAD_H_

#include <pthread.h>

#include "Object.h"
#include "String.h"
#include "Runnable.h"

#define public_class_ThreadClass(T, SuperClss)                      \
  	       extends_class(Object)(T, SuperClss)                      \
  implements_interface(Runnable, T)                                 \
             CONSTRUCTOR(public)(T, Runnable* target);              \
       long CLASS_METHOD(public)(T, getId);                         \
       bool CLASS_METHOD(public)(T, isAlive);                       \
       void CLASS_METHOD(public)(T, join);                          \
       void CLASS_METHOD(public)(T, join, long millis);             \
       void CLASS_METHOD(public)(T, join, long millis, int nanos);  \
       void CLASS_METHOD(public)(T, start);                         \
                     GET(public)(T, String*, _mName, Name);         \
                     SET(public)(T, String*, _mName, Name);

#define public_class_Thread(T)   \
            extends(Object)(T)   \
         implements(Runnable)    \
          Runnable* _mTarget;    \
            String* _mName;      \
          pthread_t _mThreadId;  \
               bool _mRunning;

DECLARE_CLASS(public)(Thread, Object)

#endif /* _OO_THREAD_H_ */
