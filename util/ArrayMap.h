#ifndef _OO_ARRAY_MAP_H_
#define _OO_ARRAY_MAP_H_

#include "util/Map.h"

/* - - - - - - - - - - - - - - - - +-------------------+ - - - - - - - - - - - - - - - */
/*              \\\\\\\            | Class O2OArrayMap |            ///////            */
/* - - - - - - - - - - - - - - - - +-------------------+ - - - - - - - - - - - - - - - */

#define  public_class_O2OArrayMapClass(T, SuperClss)                              \
                 extends_class(Object)(T, SuperClss)                              \
     implements_generic_interface(Map, T, Object*, Object*)                       \
                   CONSTRUCTOR(public)(T, int capacity);                          \
                   CONSTRUCTOR(public)(T, int capacity, bool identityHashCode);   \
             void CLASS_METHOD(public)(T, erase);                                 \
             void CLASS_METHOD(public)(T, ensureCapacity, int minimumCapacity);   \
             bool CLASS_METHOD(public)(T, containsKey, Object* key);              \
              int CLASS_METHOD(public)(T, indexOfKey, Object* key);               \
              int CLASS_METHOD(public)(T, indexOfValue, Object* value);           \
             bool CLASS_METHOD(public)(T, containsValue, Object* value);          \
          Object* CLASS_METHOD(public)(T, keyAt, int index);                      \
          Object* CLASS_METHOD(public)(T, valueAt, int index);                    \
          Object* CLASS_METHOD(public)(T, setValueAt, int index, Object* value);  \
             void CLASS_METHOD(public)(T, append, Object* key, Object* value);    \
          Object* CLASS_METHOD(public)(T, removeAt, int index);                   \
         Object* CLASS_METHOD(private)(T, allocArrays, int size);                 \

#define public_class_O2OArrayMap(T)         \
                extends(Object)(T)          \
                 int* _mHashes;             \
             Object** _mArray;              \
                  int _mSize;               \
                 bool _mIdentityHashCode;

DECLARE_CLASS(public)(O2OArrayMap, Object)

/**
 * The minimum amount by which the capacity of a O2OArrayMap will increase.
 * This is tuned to be relatively space-efficient.
 */
#define BASE_SIZE 4

#endif /* _OO_ARRAY_MAP_H_ */
