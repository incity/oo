#ifndef _OO_LOG_H_
#define _OO_LOG_H_

#include "lang/String.h"

#define public_final_class_LogClass(T, SuperClss)                                                 \
              extends_class(Object)(T, SuperClss)                                                 \
 int CLASS_METHOD(0)(public_static)(v, String* tag, String* msg);                                 \
 int CLASS_METHOD(0)(public_static)(d, String* tag, String* msg);                                 \
 int CLASS_METHOD(0)(public_static)(i, String* tag, String* msg);                                 \
 int CLASS_METHOD(0)(public_static)(w, String* tag, String* msg);                                 \
 int CLASS_METHOD(0)(public_static)(e, String* tag, String* msg);                                 \
 int CLASS_METHOD(0)(public_static)(println, int priority, String* tag, String* msg);             \
 int CLASS_METHOD(0)(public_static)(println2, int bufID, int priority, String* tag, String* msg); \

#define public_final_class_Log(T)  \
            extends(Object)(T)     \

DECLARE_CLASS(public_final)(Log, Object)

#define LOG Class(Log)

#endif /* _OO_LOG_H_ */
