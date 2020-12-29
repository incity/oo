#ifndef _OO_MAP_H_
#define _OO_MAP_H_

#include "lang/Object.h"
#include "lang/Ibject.h"

#define public_generic_interface_Entry(IF, T, K, V)                   \
             extends_interface(Ibject)(IF, T)                         \
                    K CLASS_METHOD(public)(T, getKey);                \
                    V CLASS_METHOD(public)(T, getValue);              \
                    V CLASS_METHOD(public)(T, setValue, V value);

DECLARE_INTERFACE(public_generic)(Int2IntEntry, Entry, int, int)
DECLARE_INTERFACE(public_generic)(Int2ObjEntry, Entry, int, Object*)
DECLARE_INTERFACE(public_generic)(Obj2ObjEntry, Entry, Object*, Object*)

/* - - - - - - - - - - - - - - +-----------------------+ - - - - - - - - - - - - - - */
/*              \\\\\\\        |  Class SimpleO2OEntry |          ///////            */
/* - - - - - - - - - - - - - - +-----------------------+ - - - - - - - - - - - - - - */

/* forward declaration */
DECLARE_CLASS(forward)(O2OHashMap)

#define public_class_SimpleO2OEntryClass(T, SuperClss)                     \
                   extends_class(Object)(T, SuperClss)                     \
     implements_generic_interface(Entry, T, Object*, Object*)              \
                     CONSTRUCTOR(public)(T, int h, Object* k, Object* v, SimpleO2OEntry* n); \
               void CLASS_METHOD(public)(T, recordAccess, O2OHashMap* m);                    \
               void CLASS_METHOD(public)(T, recordRemoval, O2OHashMap* m);                   \

#define public_class_SimpleO2OEntry(T)        \
                    extends(Object)(T)        \
                 implements(Obj2ObjEntry)     \
                       Object* key;           \
                       Object* value;         \
                           int hash;          \
               SimpleO2OEntry* next;

DECLARE_CLASS(public)(SimpleO2OEntry, Object)

#define public_generic_interface_Map(IF, T, K, V)                      \
           extends_interface(Ibject)(IF, T)                            \
                int CLASS_METHOD(public)(T, size);                     \
               bool CLASS_METHOD(public)(T, isEmpty);                  \
               bool CLASS_METHOD(public)(T, containsKey, K key);       \
               bool CLASS_METHOD(public)(T, containsValue, V value);   \
                  K CLASS_METHOD(public)(T, get, K key);               \
                  V CLASS_METHOD(public)(T, put, K key, V value);      \
                  V CLASS_METHOD(public)(T, remove, V key);            \
               void CLASS_METHOD(public)(T, clear);                    \

DECLARE_INTERFACE(public_generic)(Int2IntMap, Map, int, int)
DECLARE_INTERFACE(public_generic)(Int2ObjMap, Map, int, Object*)
DECLARE_INTERFACE(public_generic)(Obj2ObjMap, Map, Object*, Object*)

#endif /* _OO_MAP_H_ */
