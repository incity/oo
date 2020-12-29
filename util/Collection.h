#ifndef _OO_COLLECTION_H_
#define _OO_COLLECTION_H_

#include "Iterable.h"

/**
 * @param IF  interface name
 * @param T   this class, the class who implements this inteface
 * @param E   element type
 * @param Itr element iterator type
 */
#define public_generic_interface_Collection(IF, T, E, Itr)                    \
        extends_generic_interface(Iterable)(IF, T, Itr)                       \
                      bool CLASS_METHOD(public)(T, add, E e);                 \
                      bool CLASS_METHOD(public)(T, removeObject, Object* o);  \
                      void CLASS_METHOD(public)(T, clear);                    \
                      bool CLASS_METHOD(public)(T, contains, Object* o);      \
                      bool CLASS_METHOD(public)(T, isEmpty);                  \
                       int CLASS_METHOD(public)(T, size);                     \
                       int CLASS_METHOD(public)(T, toArray);                  \

DECLARE_INTERFACE(public_generic)(ObjectCollection, Collection, Object*, ObjectIterator*)

#endif /* _OO_COLLECTION_H_ */
