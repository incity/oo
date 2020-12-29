#ifndef _OO_HASH_MAP_H_
#define _OO_HASH_MAP_H_

#include "util/Map.h"

/* - - - - - - - - - - - - - - - - +-------------------+ - - - - - - - - - - - - - - - */
/*              \\\\\\\            |  Class O2OHashMap |            ///////            */
/* - - - - - - - - - - - - - - - - +-------------------+ - - - - - - - - - - - - - - - */

#define  public_class_O2OHashMapClass(T, SuperClss)                                                \
                extends_class(Object)(T, SuperClss)                                                \
    implements_generic_interface(Map, T, Object*, Object*)                                         \
                  CONSTRUCTOR(public)(T, int initialCapacity, float loadFactor);                   \
            void CLASS_METHOD(public)(T, resize, int newCapacity);                                 \
             int CLASS_METHOD(public)(T, capacity);                                                \
           float CLASS_METHOD(public)(T, loadFactor);                                              \
            void CLASS_METHOD(public)(T, addEntry, int hash, Object* key, Object* value, int bucketIndex); \
  SimpleO2OEntry* CLASS_METHOD(final)(T, removeEntryForKey, Object* key);                          \
  SimpleO2OEntry* CLASS_METHOD(final)(T, getEntry, Object* key);                                   \
         void CLASS_METHOD(protected)(T, transfer, SimpleO2OEntry** newTable, int newCapacity);    \

#define public_class_O2OHashMap(T)     \
                extends(Object)(T)     \
                 int _mCapacity;       \
               float _mLoadFactor;     \
                 int _mThreshold;      \
                 int _mSize;           \
    SimpleO2OEntry** _mTable;

DECLARE_CLASS(public)(O2OHashMap, Object)

/**
* The default initial capacity - MUST be a power of two.
*/
#define DEFAULT_INITIAL_CAPACITY 16

/**
 * The maximum capacity, used if a higher value is implicitly specified
 * by either of the constructors with arguments.
 * MUST be a power of two <= 1<<30.
 */
#define MAXIMUM_CAPACITY 1 << 30

/**
 * The load factor used when none specified in constructor.
 */
#define DEFAULT_LOAD_FACTOR 0.75f

#endif /* _OO_HASH_MAP_H_ */
