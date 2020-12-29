#ifndef _OO_APPLICATION_H_
#define _OO_APPLICATION_H_

#include "lang/Object.h"

#define public_interface_ActivityLifecycleCallbacks(IF, T)                         \
                          extends_interface(Ibject)(IF, T)                         \
        void CLASS_METHOD(public)(T, onActivityPreCreated,    Activity* activity); \
        void CLASS_METHOD(public)(T, onActivityCreated,       Activity* activity); \
        void CLASS_METHOD(public)(T, onActivityPostCreated,   Activity* activity); \
        void CLASS_METHOD(public)(T, onActivityPreStarted,    Activity* activity); \
        void CLASS_METHOD(public)(T, onActivityStarted,       Activity* activity); \
        void CLASS_METHOD(public)(T, onActivityPostStarted,   Activity* activity); \
        void CLASS_METHOD(public)(T, onActivityPreResumed,    Activity* activity); \
        void CLASS_METHOD(public)(T, onActivityResumed,       Activity* activity); \
        void CLASS_METHOD(public)(T, onActivityPostResumed,   Activity* activity); \
        void CLASS_METHOD(public)(T, onActivityPrePaused,     Activity* activity); \
        void CLASS_METHOD(public)(T, onActivityPaused,        Activity* activity); \
        void CLASS_METHOD(public)(T, onActivityPostPaused,    Activity* activity); \
        void CLASS_METHOD(public)(T, onActivityPreStopped,    Activity* activity); \
        void CLASS_METHOD(public)(T, onActivityStopped,       Activity* activity); \
        void CLASS_METHOD(public)(T, onActivityPostStopped,   Activity* activity); \
        void CLASS_METHOD(public)(T, onActivityPreDestroyed,  Activity* activity); \
        void CLASS_METHOD(public)(T, onActivityDestroyed,     Activity* activity); \
        void CLASS_METHOD(public)(T, onActivityPostDestroyed, Activity* activity); \

DECLARE_INTERFACE(public)(ActivityLifecycleCallbacks)

#define public_class_ApplicationClass(T, SuperClss)     \
                extends_class(Object)(T, SuperClss)     \
        void CLASS_METHOD(public)(T, onCreate);     \
        void CLASS_METHOD(public)(T, onTerminate);  \
        void CLASS_METHOD(public)(T, onLowMemory);  \
        void CLASS_METHOD(public)(T, onTrimMemory); \
        void CLASS_METHOD(public)(T, registerActivityLifecycleCallbacks, ActivityLifecycleCallbacks* callback);    \
        void CLASS_METHOD(public)(T, unregisterActivityLifecycleCallbacks, ActivityLifecycleCallbacks* callback);  \

#define public_class_Application(T)  \
              extends(Object)(T)  \


DECLARE_CLASS(public)(Application, Object)

#endif /* _OO_APPLICATION_H_ */
