//1. The .cc .cpp .cxx related header files
#include "Object.h"
//2. C system include files.
#include <string.h>
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.
#include "Ibject.h"
#include "String.h"

static int totalObjects = 0;
static int constObjects = 0;

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(Object)
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&self->_mMutex, &attr);
    pthread_cond_init(&self->_mCond, NULL);
}

static CONST_CONSTRUCTOR()(Object)
{
    CONSTRUCTOR(super)(Object);
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(Object)
{
    pthread_cond_destroy(&self->_mCond);
    pthread_mutex_destroy(&self->_mMutex);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
String* CLASS_METHOD()(Object, toString)
{
    String* str = NEW(String);
    long hashCode = _M(self, hashCode);
    _M0(str, format, "%s@0x%x", _c(self)->typeName, hashCode);
    return str;
}

static Object* CLASS_METHOD()(Object, refer)
{
    self(lock);
    ++self->_mObjRefCount;
    self(unlock);
    return self;
}

static long CLASS_METHOD()(Object, hashCode)
{
    return (long)self;
}

static bool CLASS_METHOD()(Object, equals, Object* obj)
{
    return self == obj;
}

/**
 * Wakes up a single thread that is waiting on this object's monitor.
 * If any threads are waiting on this object, one of them is chosen to be awakened.
 * The choice is arbitrary and occurs at the discretion of the implementation.
 * A thread waits on an object's monitor by calling one of the wait methods.
 */
static void CLASS_METHOD()(Object, notify)
{
    pthread_cond_signal(&self->_mCond);
}

/**
 * Wakes up all threads that are waiting on this object's monitor.
 * A thread waits on an object's monitor by calling one of the wait methods.
 */
static void CLASS_METHOD()(Object, notifyAll)
{
    pthread_cond_broadcast(&self->_mCond);
}

static int CLASS_METHOD()(Object, lock)
{
    return -pthread_mutex_lock(&self->_mMutex);
}

static void CLASS_METHOD()(Object, unlock)
{
    pthread_mutex_unlock(&self->_mMutex);
}

static int CLASS_METHOD()(Object, tryLock)
{
    return -pthread_mutex_trylock(&self->_mMutex);
}

/**
 * Causes the current thread to wait until another thread invokes the notify() method
 * or the notifyAll() method for this object. In other words, this method behaves
 * exactly as if it simply performs the call wait(0).
 *
 * The awakened threads will not be able to proceed until the current thread relinquishes
 * the lock on this object.
 *
 * Waits should always occur in loops, like this one:
 *
 * _M(obj, lock);
 * while (<condition does not hold>)
 *     obj.wait(timeout);
 * ... // Perform action appropriate to condition
 * _M(obj, unlock);
 *
 */
static void CLASS_METHOD()(Object, wait)
{
    pthread_cond_wait(&self->_mCond, &self->_mMutex);
}

/**
 * Causes the current thread to wait until either another thread invokes the notify() method
 * or the notifyAll() method for this object, or a specified amount of time has elapsed.
 * @param millis the maximum time to wait in milliseconds.
 */
void CLASS_METHOD()(Object, wait, long millis)
{
    if (millis == 0) {
        self(wait);
        return;
    }

    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += millis/1000;
    ts.tv_nsec += (millis%1000)*1000000;
    if (ts.tv_nsec >= 1000000000) {
        ts.tv_nsec -= 1000000000;
        ts.tv_sec  += 1;
    }
    pthread_cond_timedwait(&self->_mCond, &self->_mMutex, &ts);
}

/**
 * Causes the current thread to wait until another thread invokes the notify() method
 * or the notifyAll() method for this object, or some other thread interrupts the
 * current thread, or a certain amount of real time has elapsed.
 * @param millis the maximum time to wait in milliseconds.
 * @param nanos additional time, in nanoseconds range 0-999999.
 */
static void CLASS_METHOD()(Object, wait, long millis, int nanos)
{
    //TODO: to be implemented.
}

static Object* CLASS_METHOD()(Object, clone)
{
    Object* obj = (Object*)calloc(1, _c(self)->objSize);
    memcpy(obj, self, _c(self)->objSize);
    obj->_mObjRefCount = 1;
    pthread_mutex_init(&obj->_mMutex, NULL);
    pthread_cond_init(&obj->_mCond, NULL);
    totalObjects++;
    return obj;
}

// +++++++++++++++++++++++++++++++++++++++++++++
// |   2. private members                      |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   2.8. private functions|
// +++++++++++++++++++++++++++

AUTO_LOAD_CLASS(Object)
static void ObjectClassLoader(ObjectClass* _class)
{
    _class->super = NULL;
    _class->typeName = "Object";
    _class->objSize = sizeof(Object);

      CONSTRUCTOR(map)(Object)
CONST_CONSTRUCTOR(map)(Object)
       DESTRUCTOR(map)(Object)
     CLASS_METHOD(map)(Object, hashCode)
     CLASS_METHOD(map)(Object, equals, Object* obj)
     CLASS_METHOD(map)(Object, toString)
     CLASS_METHOD(map)(Object, refer)
     CLASS_METHOD(map)(Object, lock)
     CLASS_METHOD(map)(Object, unlock)
     CLASS_METHOD(map)(Object, tryLock)
     CLASS_METHOD(map)(Object, notify)
     CLASS_METHOD(map)(Object, notifyAll)
     CLASS_METHOD(map)(Object, wait)
     CLASS_METHOD(map)(Object, wait, long millis)
     CLASS_METHOD(map)(Object, wait, long millis, int nanos)
     CLASS_METHOD(map)(Object, clone)
}

ObjectClass Class(Object) = {
    .loadClass = (ClassLoader)ObjectClassLoader
};

void __initObject(Object* obj, ObjectClass* _class)
{
    totalObjects++;
    if (obj->_mObjType == CONST_OBJECT) constObjects++;
    obj->_mFirstByteMustBe0xFE = 0xFE;
    obj->class = _class;
    obj->_mObjRefCount = 1;
    Ibject* ibj;
    IbjectVTable* _ivtable;

    size_t next_intf_offset = _class->interfaceOffset;
    while (next_intf_offset > 0) {
        _ivtable = (IbjectVTable*)((char*)_class + next_intf_offset);
        ibj = (Ibject*)((char*)obj + _ivtable->_obj_offset);
        ibj->_vtable = _ivtable;
        next_intf_offset = _ivtable->_next_offset;
    }
}

void __deleteObject(Object* obj, bool wouldFree)
{
    assert(obj->_mFirstByteMustBe0xFE == 0xFE);
    _M(obj, lock);
    do {
        if (obj == NULL || obj->class == NULL) break;
        if (--obj->_mObjRefCount > 0) break;
        _M(obj, unlock);
        _c(obj)->destroy(obj);
        obj->class = NULL;
        if (wouldFree && obj->_mObjType == HEAP_OBJECT) free(obj);
        totalObjects--;
        printf("totalObjects:%d constObject:%d\n", totalObjects, constObjects);
        return;
    } while(0);
    _M(obj, unlock);
}

void __deleteArray(Object* obj, int n)
{
    int objSize = _c(obj)->objSize;
    int arrSize = objSize * n;
    const char* o = (const char*)obj + arrSize;

    while (o != (const char*)obj) {
        o -= objSize;
        __deleteObject((Object*)o, o == (const char*)obj);
    }
}

bool __instanceOf(Object* obj, ObjectClass* clss)
{
    ObjectClass* objClss;
    if (obj == NULL || clss == NULL || obj->_mFirstByteMustBe0xFE != 0xFE)
        return false;

    objClss = _c(obj);
    while (objClss && clss != objClss) {
        objClss = objClss->super;
    }

    return objClss != NULL;
}

