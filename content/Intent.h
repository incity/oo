#ifndef _OO_INTENT_H_
#define _OO_INTENT_H_

#include "lang/String.h"
#include "net/Uri.h"
#include "sys/Bundle.h"

DECLARE()(ACTION_MAIN,                    String)
DECLARE()(ACTION_VIEW,                    String)
DECLARE()(ACTION_APPLICATION_PREFERENCES, String)
DECLARE()(ACTION_SHOW_APP_INFO,           String)
DECLARE()(ACTION_SET_WALLPAPER,           String)
DECLARE()(ACTION_BUG_REPORT,              String)
DECLARE()(ACTION_FACTORY_TEST,            String)
DECLARE()(ACTION_POWER_USAGE_SUMMARY,     String)

enum {
   FLAG_ACTIVITY_NO_HISTORY = 0x40000000,
   FLAG_ACTIVITY_SINGLE_TOP = 0x20000000,
   FLAG_ACTIVITY_CLEAR_TOP = 0x04000000,
   FLAG_ACTIVITY_REORDER_TO_FRONT = 0X00020000,
   FLAG_ACTIVITY_NO_ANIMATION = 0X00010000,
};

#define public_class_IntentClass(T, SuperClss)                                           \
           extends_class(Object)(T, SuperClss)                                           \
             CONSTRUCTOR(public)(T, String* action);                                     \
             CONSTRUCTOR(public)(T, String* action, Uri* uri);                           \
    Intent* CLASS_METHOD(public)(T, setAction, String* action);                          \
    String* CLASS_METHOD(public)(T, getAction);                                          \
    Intent* CLASS_METHOD(public)(T, setData, Uri* data);                                 \
       Uri* CLASS_METHOD(public)(T, getData);                                            \
    String* CLASS_METHOD(public)(T, getDataString);                                      \
    String* CLASS_METHOD(public)(T, getScheme);                                          \
    String* CLASS_METHOD(public)(T, getType);                                            \
       bool CLASS_METHOD(public)(T, hasExtra, String* name);                             \
    Object* CLASS_METHOD(public)(T, getExtra, String* name);                             \
    Object* CLASS_METHOD(public)(T, getExtra, String* name, Object* defaultValue);       \
    Bundle* CLASS_METHOD(public)(T, getExtras);                                          \
       bool CLASS_METHOD(public)(T, getBoolExtra, String* name, bool defaultValue);      \
       byte CLASS_METHOD(public)(T, getByteExtra, String* name, byte defaultValue);      \
       char CLASS_METHOD(public)(T, getCharExtra, String* name, char defaultValue);      \
      short CLASS_METHOD(public)(T, getShortExtra, String* name, short defaultValue);    \
        int CLASS_METHOD(public)(T, getIntExtra, String* name, int defaultValue);        \
       long CLASS_METHOD(public)(T, getLongExtra, String* name, long defaultValue);      \
      float CLASS_METHOD(public)(T, getFloatExtra, String* name, float defaultValue);    \
       long CLASS_METHOD(public)(T, getDoubleExtra, String* name, double defaultValue);  \
    String* CLASS_METHOD(public)(T, getStringExtra, String* name, String* defaultValue); \
    Intent* CLASS_METHOD(public)(T, putBoolExtra, String* name, bool value);             \
    Intent* CLASS_METHOD(public)(T, putByteExtra, String* name, byte value);             \
    Intent* CLASS_METHOD(public)(T, putCharExtra, String* name, char value);             \
    Intent* CLASS_METHOD(public)(T, putShortExtra, String* name, short value);           \
    Intent* CLASS_METHOD(public)(T, putIntExtra, String* name, int value);               \
    Intent* CLASS_METHOD(public)(T, putLongExtra, String* name, long value);             \
    Intent* CLASS_METHOD(public)(T, putFloatExtra, String* name, float value);           \
    Intent* CLASS_METHOD(public)(T, putDoubleExtra, String* name, double value);         \
    Intent* CLASS_METHOD(public)(T, putStringExtra, String* name, String* value);        \
       void CLASS_METHOD(public)(T, removeExtra, String* name);                          \
    Intent* CLASS_METHOD(public)(T, setFlags, int flags);                                \
    Intent* CLASS_METHOD(public)(T, addFlags, int flags);                                \
       void CLASS_METHOD(public)(T, removeFlags, int flags);                             \


#define public_class_Intent(T)    \
            extends(Object)(T)    \
                 int   _mFlags;   \
              Bundle* _mExtras;   \
              String* _mAction;   \
                 Uri* _mData;     \

DECLARE_CLASS(public)(Intent, Object)

#endif /* _OO_INTENT_H_ */
