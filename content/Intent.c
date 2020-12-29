//1. The .cc .cpp .cxx related header files
#include "Intent.h"
//2. C system include files.
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.

BUILD(global_const)(ACTION_MAIN,                    String, "intent.action.MAIN")
BUILD(global_const)(ACTION_VIEW,                    String, "intent.action.VIEW")
BUILD(global_const)(ACTION_APPLICATION_PREFERENCES, String, "intent.action.APPLICATION_PREFERENCES")
BUILD(global_const)(ACTION_SHOW_APP_INFO,           String, "intent.action.SHOW_APP_INFO")
BUILD(global_const)(ACTION_SET_WALLPAPER,           String, "intent.action.SET_WALLPAPER")
BUILD(global_const)(ACTION_BUG_REPORT,              String, "intent.action.ACTION_BUG_REPORT")
BUILD(global_const)(ACTION_FACTORY_TEST,            String, "intent.action.ACTION_FACTORY_TEST")
BUILD(global_const)(ACTION_POWER_USAGE_SUMMARY,     String, "intent.action.POWER_USAGE_SUMMARY")

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(Intent, String* action)
 {
    CONSTRUCTOR(super)(Object);
    self(setAction, action);
}

static CONSTRUCTOR()(Intent, String* action, Uri* uri)
{
    CONSTRUCTOR(super)(Object);
    self(setAction, action);
    self->_mData = REFER(uri);
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(Intent)
{
    DELETE(self->_mAction);
    DELETE(self->_mData);
    if (self->_mExtras)
        DELETE(self->_mExtras);
    DESTRUCTOR(super)(Object);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++

static Intent* CLASS_METHOD()(Intent, setAction, String* action)
{
    self->_mAction = action != NULL ? REFER(action) : NULL;
    return self;
}

static String* CLASS_METHOD()(Intent, getAction)
{
    return self->_mAction;
}

static Intent* CLASS_METHOD()(Intent, setData, Uri* data)
{
    self->_mData = REFER(data);
    return self;
}

static Uri* CLASS_METHOD()(Intent, getData)
{
    return self->_mData;
}

static String* CLASS_METHOD()(Intent, getDataString)
{
    return self->_mData != NULL ? _M(self->_mData, toString) : NULL;
}

static bool CLASS_METHOD()(Intent, hasExtra, String* name)
{
    if (self->_mExtras == NULL)
        return false;
    return _M(self->_mExtras, containsKey, name);
}

static Bundle* CLASS_METHOD()(Intent, getExtras)
{
    return self->_mExtras;
}

static Object* CLASS_METHOD()(Intent, getExtra, String* name, Object* defaultValue)
{
   Object* result = REFER(defaultValue);
   if (self->_mExtras != NULL) {
       Object* result2 = _M(self->_mExtras, get, name);
       if (result2 != NULL)
           result = result2;
   }
   return result;
}

static Object* CLASS_METHOD()(Intent, getExtra, String* name)
{
    Object* obj = self(getExtra, name, NULL);
    return obj;
}

static bool CLASS_METHOD()(Intent, getBoolExtra, String* name, bool defaultValue)
{
    if (self->_mExtras == NULL)
        return defaultValue;
    return _M(self->_mExtras, getBool, name, defaultValue);
}

static byte CLASS_METHOD()(Intent, getByteExtra, String* name, byte defaultValue)
{
    if (self->_mExtras == NULL)
        return defaultValue;
    return _M(self->_mExtras, getByte, name, defaultValue);
}

static short CLASS_METHOD()(Intent, getShortExtra, String* name, short defaultValue)
{
    if (self->_mExtras == NULL)
        return defaultValue;
    return _M(self->_mExtras, getShort, name, defaultValue);
}

static char CLASS_METHOD()(Intent, getCharExtra, String* name, char defaultValue)
{
    if (self->_mExtras == NULL)
        return defaultValue;
   return _M(self->_mExtras, getChar, name, defaultValue);
}

static int CLASS_METHOD()(Intent, getIntExtra, String* name, int defaultValue)
{
    if (self->_mExtras == NULL)
        return defaultValue;
   return _M(self->_mExtras, getInt, name, defaultValue);
}

static long CLASS_METHOD()(Intent, getLongExtra, String* name, long defaultValue)
{
    if (self->_mExtras == NULL)
        return defaultValue;
   return _M(self->_mExtras, getLong, name, defaultValue);
}

static float CLASS_METHOD()(Intent, getFloatExtra, String* name, float defaultValue)
{
    if (self->_mExtras == NULL)
        return defaultValue;
   return _M(self->_mExtras, getFloat, name, defaultValue);
}

static double CLASS_METHOD()(Intent, getDoubleExtra, String* name, double defaultValue)
{
    if (self->_mExtras == NULL)
        return defaultValue;
   return _M(self->_mExtras, getDouble, name, defaultValue);
}

static String* CLASS_METHOD()(Intent, getStringExtra, String* name, String* defaultValue)
{
    if (self->_mExtras == NULL)
        return defaultValue;
    return _M(self->_mExtras, getString, name, defaultValue);
}

static Intent* CLASS_METHOD()(Intent, putBoolExtra, String* name, bool value)
{
    if (self->_mExtras == NULL)
        self->_mExtras = NEW(Bundle);
    _M(self->_mExtras, putBool, name, value);
    return self;
}

static Intent* CLASS_METHOD()(Intent, putByteExtra, String* name, byte value)
{
    if (self->_mExtras == NULL)
        self->_mExtras = NEW(Bundle);
    _M(self->_mExtras, putByte, name, value);
    return self;
}

static Intent* CLASS_METHOD()(Intent, putCharExtra, String* name, char value)
{
    if (self->_mExtras == NULL)
        self->_mExtras = NEW(Bundle);
    _M(self->_mExtras, putChar, name, value);
    return self;
}

static Intent* CLASS_METHOD()(Intent, putIntExtra, String* name, int value)
{
    if (self->_mExtras == NULL)
        self->_mExtras = NEW(Bundle);
    _M(self->_mExtras, putInt, name, value);
    return self;
}

static Intent* CLASS_METHOD()(Intent, putLongExtra, String* name, long value)
{
    if (self->_mExtras == NULL)
        self->_mExtras = NEW(Bundle);
    _M(self->_mExtras, putLong, name, value);
    return self;
}

static Intent* CLASS_METHOD()(Intent, putFloatExtra, String* name, float value)
{
    if (self->_mExtras == NULL)
        self->_mExtras = NEW(Bundle);
    _M(self->_mExtras, putFloat, name, value);
    return self;
}

static Intent* CLASS_METHOD()(Intent, putDoubleExtra, String* name, double value)
{
    if (self->_mExtras == NULL)
        self->_mExtras = NEW(Bundle);
    _M(self->_mExtras, putDouble, name, value);
    return self;
}

static Intent* CLASS_METHOD()(Intent, putStringExtra, String* name, String* value)
{
    if (self->_mExtras == NULL)
        self->_mExtras = NEW(Bundle);
    _M(self->_mExtras, putString, name, value);
    return self;
}

void CLASS_METHOD()(Intent, removeExtra, String* name)
{
    if (self->_mExtras != NULL) {
        _M(self->_mExtras, remove, name);
        if (_M(self->_mExtras, size) == 0) {
            DELETE(self->_mExtras);
            self->_mExtras = NULL;
        }
    }
}

Intent* CLASS_METHOD()(Intent, setFlags, int flags)
{
    self->_mFlags = flags;
    return self;
}

void CLASS_METHOD()(Intent, removeFlags, int flags)
{
    self->_mFlags &= ~flags;
}

BEGIN_CLASS(Intent, Object)
     CONSTRUCTOR(map)(Intent, String* action)
     CONSTRUCTOR(map)(Intent, String* action, Uri* uri)
      DESTRUCTOR(map)(Intent)
    CLASS_METHOD(map)(Intent, setAction, String* action)
    CLASS_METHOD(map)(Intent, getAction)
    CLASS_METHOD(map)(Intent, setData, Uri* data)
    CLASS_METHOD(map)(Intent, getData)
    CLASS_METHOD(map)(Intent, getDataString)
    CLASS_METHOD(map)(Intent, getExtras)
    CLASS_METHOD(map)(Intent, getExtra, String* name, Object* defaultValue)
    CLASS_METHOD(map)(Intent, getExtra, String* name)
    CLASS_METHOD(map)(Intent, hasExtra, String* name)
    CLASS_METHOD(map)(Intent, getBoolExtra, String* name, bool defaultValue)
    CLASS_METHOD(map)(Intent, getByteExtra, String* name, byte defaultValue)
    CLASS_METHOD(map)(Intent, getShortExtra, String* name, short defaultValue)
    CLASS_METHOD(map)(Intent, getCharExtra, String* name, char defaultValue)
    CLASS_METHOD(map)(Intent, getIntExtra, String* name, int defaultValue)
    CLASS_METHOD(map)(Intent, getLongExtra, String* name, long defaultValue)
    CLASS_METHOD(map)(Intent, getFloatExtra, String* name, float defaultValue)
    CLASS_METHOD(map)(Intent, getDoubleExtra, String* name, double defaultValue)
    CLASS_METHOD(map)(Intent, getStringExtra, String* name, String* defaultValue)
    CLASS_METHOD(map)(Intent, putBoolExtra, String* name, bool value)
    CLASS_METHOD(map)(Intent, putByteExtra, String* name, byte value)
    CLASS_METHOD(map)(Intent, putCharExtra, String* name, char value)
    CLASS_METHOD(map)(Intent, putIntExtra, String* name, int value)
    CLASS_METHOD(map)(Intent, putLongExtra, String* name, long value)
    CLASS_METHOD(map)(Intent, putFloatExtra, String* name, float value)
    CLASS_METHOD(map)(Intent, putDoubleExtra, String* name, double value)
    CLASS_METHOD(map)(Intent, putStringExtra, String* name, String* value)
    CLASS_METHOD(map)(Intent, removeExtra, String* name)
    CLASS_METHOD(map)(Intent, setFlags, int flags)
    CLASS_METHOD(map)(Intent, removeFlags, int flags)
END_CLASS
