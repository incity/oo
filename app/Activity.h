#ifndef _OO_ACTIVITY_H_
#define _OO_ACTIVITY_H_

#include "lang/Object.h"

#define public_class_ActivityClass(T, SuperClss)         \
             extends_class(Object)(T, SuperClss)         \
      void CLASS_METHOD(protected)(T, onCreate);         \
      void CLASS_METHOD(protected)(T, onStart);          \
      void CLASS_METHOD(protected)(T, onRestart);        \
      void CLASS_METHOD(protected)(T, onResume);         \
      void CLASS_METHOD(protected)(T, onPause);          \
      void CLASS_METHOD(protected)(T, onStop);           \
      void CLASS_METHOD(protected)(T, onDestroy);        \
      void CLASS_METHOD(protected)(T, startActivity);    \

#define public_class_Activity(T)  \
              extends(Object)(T)  \

DECLARE_CLASS(public)(Activity, Object)

#endif /* _OO_ACTIVITY_H_ */
