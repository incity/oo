#ifndef _OO_ABSTRACT_LIST_H_
#define _OO_ABSTRACT_LIST_H_

#include "AbstractCollection.h"
#include "List.h"

#define public_class_AbstractObjectListClass(T, SuperClss)                      \
                       extends_class(Object)(T, SuperClss)                      \
          implements_generic_interface(List, T, Object*, ObjectListIterator*)   \

#define public_class_AbstractObjectList(T)   \
                        extends(Object)(T)   \
                     implements(ObjectList)

DECLARE_CLASS(public)(AbstractObjectList, Object)

#endif /* _OO_ABSTRACT_LIST_H_ */
