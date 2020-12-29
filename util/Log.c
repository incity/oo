//1. The .cc .cpp .cxx related header files
#include "Log.h"
//2. C system include files.
#include <string.h>
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.

enum {
    /**
     * Priority constant for the println method; use LOG.v.
     */
    VERBOSE = 2,

    /**
     * Priority constant for the println method; use LOG.d.
     */
    DEBUG   = 3,

    /**
     * Priority constant for the println method; use LOG.i.
     */
    INFO    = 4,

    /**
     * Priority constant for the println method; use LOG.w.
     */
    WARN    = 5,

    /**
     * Priority constant for the println method; use LOG.e.
     */
    ERROR   = 6,

    /**
     * Priority constant for the println method.
     */
    ASSERT  = 7,
};

enum {
    LOG_ID_MAIN   = 0,
    LOG_ID_EVENTS = 1,
    LOG_ID_SYSTEM = 2,
    LOG_ID_CRASH  = 3,
};

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(Log)
{
    assert(0);
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(Log)
{
    assert(0);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
static int STATIC_CLASS_METHOD(0)()(Log, v, String* tag, String* msg)
{
    return LOG.println2(LOG_ID_MAIN, VERBOSE, tag, msg);
}

static int STATIC_CLASS_METHOD(0)()(Log, d, String* tag, String* msg)
{
    return LOG.println2(LOG_ID_MAIN, DEBUG, tag, msg);
}

static int STATIC_CLASS_METHOD(0)()(Log, i, String* tag, String* msg)
{
    return LOG.println2(LOG_ID_MAIN, INFO, tag, msg);
}

static int STATIC_CLASS_METHOD(0)()(Log, w, String* tag, String* msg)
{
    return LOG.println2(LOG_ID_MAIN, WARN, tag, msg);
}

static int STATIC_CLASS_METHOD(0)()(Log, e, String* tag, String* msg)
{
    return LOG.println2(LOG_ID_MAIN, ERROR, tag, msg);
}

static int STATIC_CLASS_METHOD(0)()(Log, println, int priority, String* tag, String* msg)
{
    return LOG.println2(LOG_ID_MAIN, ASSERT, tag, msg);
}

void println(int priority, const char* tag, const char* msg)
{
    const char* levels[] = {0, 0, "verbose", "debug", "info", "warn", "error", "assert"};
    printf("%s(%s): %s\n", tag, levels[priority], msg);
}

/* print line to(2) bufID */
static int STATIC_CLASS_METHOD(0)()(Log, println2, int bufID, int priority, String* tag, String* msg)
{
    if (_c(msg) == &Class(String)) {
        if (_c(tag) == &Class(String)) {
            println(priority, _M(tag, getCString), _M(msg, getCString));
        } /*else if(INSTANCEOF(tag, Object)) {
            String* str = _M(tag, toString);
            println(priority, _M(str, getCString), _M(msg, getCString));
            DELETE(str);
        } */else {
            println(priority, (const char*)tag, _M(msg, getCString));
        }
    } else if(INSTANCEOF(msg, Object)) {
        String* str = _M(msg, toString);
        if (_c(tag) == &Class(String)) {
            println(priority, _M(tag, getCString), _M(str, getCString));
        } else {
            println(priority, (const char*)tag, _M(str, getCString));
        }
        DELETE(str);
    } else {
        if (_c(tag) == &Class(String)) {
            println(priority, _M(tag, getCString), (const char*)msg);
        } else {
            println(priority, (const char*)tag, (const char*)msg);
        }
    }

    return 0;
}

BEGIN_CLASS(Log, Object)
           CONSTRUCTOR(map)(Log)
            DESTRUCTOR(map)(Log)
STATIC_CLASS_METHOD(0)(map)(Log, v, String* tag, String* msg)
STATIC_CLASS_METHOD(0)(map)(Log, d, String* tag, String* msg)
STATIC_CLASS_METHOD(0)(map)(Log, i, String* tag, String* msg)
STATIC_CLASS_METHOD(0)(map)(Log, w, String* tag, String* msg)
STATIC_CLASS_METHOD(0)(map)(Log, e, String* tag, String* msg)
STATIC_CLASS_METHOD(0)(map)(Log, println, int priority, String* tag, String* msg)
STATIC_CLASS_METHOD(0)(map)(Log, println2, int bufID, int priority, String* tag, String* msg)
END_CLASS
