#ifndef _OO_ABSTRACT_COLLECTION_H_
#define _OO_ABSTRACT_COLLECTION_H_

#include "Collection.h"

#define public_class_AbstractObjectCollectionClass(T, SuperClss)                   \
                             extends_class(Object)(T, SuperClss)                   \
          implements_generic_interface(Collection, T, Object*, ObjectIterator*)    \

#define public_class_AbstractObjectCollection(T)         \
                              extends(Object)(T)         \
                          implements(ObjectCollection)

DECLARE_CLASS(public)(AbstractObjectCollection, Object)

#endif /* _OO_ABSTRACT_COLLECTION_H_ */
