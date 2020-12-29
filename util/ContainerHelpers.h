#ifndef _OO_CONTAINER_HELPER_H_
#define _OO_CONTAINER_HELPER_H_

#include "util/Map.h"

/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - - */
/*              \\\\\\\            |  Class ContainerHelpers |            ///////            */
/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - - */

#define public_class_ContainerHelpersClass(T, SuperClss)                                              \
          extends_class(Object)(T, SuperClss)                                                         \
            int CLASS_METHOD(public_static)(binarySearchInt, int array[], int size, int value);       \
            int CLASS_METHOD(public_static)(binarySearchLong, long array[], int size, long value);    \

#define public_class_ContainerHelpers(T)  \
          extends(Object)(T)              \

DECLARE_CLASS(public)(ContainerHelpers, Object)

#endif /* _OO_CONTAINER_HELPER_H_ */
