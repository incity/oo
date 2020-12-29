#ifndef _OO_BASE_BUNDLE_H_
#define _OO_BASE_BUNDLE_H_

#include "lang/Object.h"
#include "util/HashMap.h"

/**
 * A mapping from String keys to values of various types. In most cases, you
 * should work directly with either the {@link Bundle} or
 * {@link PersistableBundle} subclass.
 */
#define public_class_BaseBundleClass(T, SuperClss)                                     \
               extends_class(Object)(T, SuperClss)                                     \
    O2OHashMap* CLASS_METHOD(public)(T, getMap);                                       \
            int CLASS_METHOD(public)(T, size);                                         \
           bool CLASS_METHOD(public)(T, isEmpty);                                      \
           void CLASS_METHOD(public)(T, clear);                                        \
           bool CLASS_METHOD(public)(T, containsKey, String* key);                     \
        Object* CLASS_METHOD(public)(T, get, String* key);                             \
           void CLASS_METHOD(public)(T, remove, String* key);                          \
           void CLASS_METHOD(public)(T, putBool, String* key, bool value);             \
           void CLASS_METHOD(public)(T, putByte, String* key, byte value);             \
           void CLASS_METHOD(public)(T, putChar, String* key, char value);             \
           void CLASS_METHOD(public)(T, putShort, String* key, short value);           \
           void CLASS_METHOD(public)(T, putInt, String* key, int value);               \
           void CLASS_METHOD(public)(T, putLong, String* key, long value);             \
           void CLASS_METHOD(public)(T, putFloat, String* key, float value);           \
           void CLASS_METHOD(public)(T, putDouble, String* key, double value);         \
           void CLASS_METHOD(public)(T, putString, String* key, String* value);        \
           void CLASS_METHOD(public)(T, putCString, String* key, const char* value);   \
           bool CLASS_METHOD(public)(T, getBool, String* key);                         \
           bool CLASS_METHOD(public)(T, getBool, String* key, bool defaultValue);      \
           byte CLASS_METHOD(public)(T, getByte, String* key);                         \
           byte CLASS_METHOD(public)(T, getByte, String* key, byte defaultValue);      \
           char CLASS_METHOD(public)(T, getChar, String* key);                         \
           char CLASS_METHOD(public)(T, getChar, String* key, char defaultValue);      \
          short CLASS_METHOD(public)(T, getShort, String* key);                        \
          short CLASS_METHOD(public)(T, getShort, String* key, short defaultValue);    \
            int CLASS_METHOD(public)(T, getInt, String* key);                          \
            int CLASS_METHOD(public)(T, getInt, String* key, int defaultValue);        \
           long CLASS_METHOD(public)(T, getLong, String* key);                         \
           long CLASS_METHOD(public)(T, getLong, String* key, long defaultValue);      \
          float CLASS_METHOD(public)(T, getFloat, String* key);                        \
          float CLASS_METHOD(public)(T, getFloat, String* key, float defaultValue);    \
         double CLASS_METHOD(public)(T, getDouble, String* key);                       \
         double CLASS_METHOD(public)(T, getDouble, String* key, double defaultValue);  \
        String* CLASS_METHOD(public)(T, getString, String* key);                       \
        String* CLASS_METHOD(public)(T, getString, String* key, String* defaultValue); \

#define public_class_BaseBundle(T)    \
                extends(Object)(T)    \
            O2OHashMap* _mMap;

DECLARE_CLASS(public)(BaseBundle, Object)

#endif /* _OO_BASE_BUNDLE_H_ */
