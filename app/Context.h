#ifndef _OO_CONTEXT_H_
#define _OO_CONTEXT_H_

#include "lang/Object.h"

/**
 * Interface to global information about an application environment. This is
 * an abstract class whose implementation is provided by
 * the Android system.  It
 * allows access to application-specific resources and classes, as well as
 * up-calls for application-level operations such as launching activities,
 * broadcasting and receiving intents, etc.
 */
#define public_abstract_class_ContextClass(T, SuperClss)     \
                extends_class(Object)(T, SuperClss)     \
        void CLASS_METHOD(public)(T, onCreate);     \
        void CLASS_METHOD(public)(T, onTerminate);  \
        void CLASS_METHOD(public)(T, onLowMemory);  \
        void CLASS_METHOD(public)(T, onTrimMemory); \
        void CLASS_METHOD(public)(T, registerActivityLifecycleCallbacks, ActivityLifecycleCallbacks* callback);    \
        void CLASS_METHOD(public)(T, unregisterActivityLifecycleCallbacks, ActivityLifecycleCallbacks* callback);  \

#define public_abstract_class_Context(T)  \
              extends(Object)(T)  \

DECLARE_CLASS(public_abstract)(Context, Object)

#endif /* _OO_CONTEXT_H_ */
