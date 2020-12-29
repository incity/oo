#ifndef _OO_SHARED_LIBRARY_H_
#define _OO_SHARED_LIBRARY_H_

#include "String.h"

#define public_class_SharedLibraryClass(T, SuperClss)              \
                  extends_class(Object)(T, SuperClss)              \
                    CONSTRUCTOR(public)(T, String* name);          \
              void CLASS_METHOD(public)(T, load, String* name);    \
              void CLASS_METHOD(public)(T, find, String* name);    \
              void CLASS_METHOD(public)(T, unload);                \


#define public_class_SharedLibrary(T)    \
                   extends(Object)(T)    \
                       void* _mHandle;   \
                     String* _mName;     \

DECLARE_CLASS(public)(SharedLibrary, Object)

#endif /* _OO_SHARED_LIBRARY_H_ */
