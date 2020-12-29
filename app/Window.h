#ifndef _OO_WINDOW_H_
#define _OO_WINDOW_H_

#include "lang/Object.h"

#define public_interface_WindowCallback(IF, T)                       \
              extends_interface(Ibject)(IF, T)                       \
            void CLASS_METHOD(public)(T, onWindowAttributesChanged); \
            void CLASS_METHOD(public)(T, onWindowFocusChanged);      \
            void CLASS_METHOD(public)(T, onAttachedToWindow);        \
            void CLASS_METHOD(public)(T, onDetachedFromWindow);      \

DECLARE_INTERFACE(public)(WindowCallback)

#define public_interface_OnWindowDismissedCallback(IF, T)            \
                         extends_interface(Ibject)(IF, T)            \
             void CLASS_METHOD(public)(T, onWindowDismissed, bool finishTask, bool suppressWindowTransition);

DECLARE_INTERFACE(public)(OnWindowDismissedCallback)

#define public_interface_OnWindowSwipeDismissedCallback(IF, T)       \
                         extends_interface(Ibject)(IF, T)            \
             void CLASS_METHOD(public)(T, onWindowSwipeDismissed);

DECLARE_INTERFACE(public)(OnWindowSwipeDismissedCallback)

#define public_class_WindowClass(T, SuperClss)     \
           extends_class(Object)(T, SuperClss)     \


#define public_class_Window(T)                                                  \
            extends(Object)(T)                                                  \
            OnWindowDismissedCallback* mOnWindowDismissedCallback;              \
            OnWindowSwipeDismissedCallback* mOnWindowSwipeDismissedCallback;    \

DECLARE_CLASS(public)(Activity, Object)

#endif /* _OO_WINDOW_H_ */
