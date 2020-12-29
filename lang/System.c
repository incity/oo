//1. The .cc .cpp .cxx related header files
#include "System.h"
//2. C system include files.
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <sys/time.h>
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(System)
{
    assert(0);
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(System)
{
    assert(0);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
static void STATIC_CLASS_METHOD()(System, setIn, InputStream* in)
{

}

static void STATIC_CLASS_METHOD()(System, setOut, InputStream* out)
{

}

static void STATIC_CLASS_METHOD()(System, setErr, InputStream* err)
{

}

/**
 * Returns the current time in milliseconds. Note that
 * while the unit of time of the return value is a millisecond,
 * the granularity of the value depends on the underlying
 * operating system and may be larger.  For example, many
 * operating systems measure time in units of tens of
 * milliseconds.
 *
 * <p> See the description of the class <code>Date</code> for
 * a discussion of slight discrepancies that may arise between
 * "computer time" and coordinated universal time (UTC).
 *
 * @return  the difference, measured in milliseconds, between
 *          the current time and midnight, January 1, 1970 UTC.
 */
static long STATIC_CLASS_METHOD()(System, currentTimeMillis)
{
    struct timeval tv;

    if (gettimeofday(&tv, (void *)0) != 0) {
        return (long)0; /* EOVERFLOW ? */
    }
    /*LINTED*/
    return ((long)tv.tv_sec * (long)1000) + (long)(tv.tv_usec / 1000);
}

static String* STATIC_CLASS_METHOD()(System, getenv, const char* str)
{
    return NULL;
}

static String* STATIC_CLASS_METHOD()(System, getcwd)
{
    char path[PATH_MAX + 1];
    if (!getcwd(path, sizeof(path)))
        return NULL;
    String* str = NEW(String, path);
    return str;
}

static void STATIC_CLASS_METHOD()(System, exit, int status)
{
    exit(status);
}

static void* STATIC_CLASS_METHOD()(System, loadLibrary, String* libname)
{
    void * result;

    result = dlopen(_M(libname, getCString), RTLD_LAZY);
    if (result == NULL) {
        //TODO: log dlerror();
    }
    return result;
}

static void STATIC_CLASS_METHOD()(System, unloadLibrary, void* handle)
{
    dlclose(handle);
}

BEGIN_CLASS(System, Object)
        CONSTRUCTOR(map)(System)
         DESTRUCTOR(map)(System)
STATIC_CLASS_METHOD(map)(System, setIn, InputStream* in)
STATIC_CLASS_METHOD(map)(System, setOut, InputStream* out)
STATIC_CLASS_METHOD(map)(System, setErr, InputStream* err)
STATIC_CLASS_METHOD(map)(System, currentTimeMillis)
STATIC_CLASS_METHOD(map)(System, getcwd)
STATIC_CLASS_METHOD(map)(System, exit, int status)
STATIC_CLASS_METHOD(map)(System, loadLibrary, String* libname)
STATIC_CLASS_METHOD(map)(System, unloadLibrary, void* handle)
END_CLASS
