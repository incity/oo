//1. The .cc .cpp .cxx related header files
#include "Thread.h"
//2. C system include files.
#include <stdio.h>
#include <stdlib.h>
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.

// +++++++++++++++++++++++++++
// |   typedefs              |
// +++++++++++++++++++++++++++
typedef void* (*thread_func_t)(void*);

// +++++++++++++++++++++++++++
// |   static prototypes     |
// +++++++++++++++++++++++++++
static int createThreadEtc(thread_func_t entryFunction,
                                  void *userData,
                                  const char* threadName,
                                  int32_t threadPriority,
                                  size_t threadStackSize,
                                  pthread_t *threadId);

static void* threadRun(void* obj);

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(Thread)
{
    CONSTRUCTOR(super)(Object);
    self->_mName = NULL;
    self->_mRunning = false;
    self->_mThreadId = -1;
    self->_mTarget = NULL;
}

static CONSTRUCTOR()(Thread, Runnable* target)
{
    assert(target);
    CONSTRUCTOR(super)(Thread);
    self->_mTarget = target;
    REFER(OBJECTOF(target, Object));
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(Thread)
{
    if (self->_mName)
        DELETE(self->_mName);
    if (self->_mTarget)
        DELETE(OBJECTOF(self->_mTarget));
    DESTRUCTOR(super)(Object);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
/**
 * Causes this thread to begin execution.
 */
static void CLASS_METHOD()(Thread, start)
{
    self(lock);
    if (self->_mRunning) {
        // thread already started
        goto exit;
    }

    self->_mThreadId = -1;
    self->_mRunning = true;

    int ret = createThreadEtc(threadRun, self, NULL, 0, 0, &self->_mThreadId);
    if (ret == 0) {
        self->_mRunning = false;
        self->_mThreadId = 0;
    }

exit:
    self(unlock);
}

/**
 * Returns the identifier of this Thread.
 * @return this thread's ID.
 */
static long CLASS_METHOD()(Thread, getId)
{
    if (!self->_mRunning) {
        return -1;
    }

    return (long)self->_mThreadId;
}

/**
 * Tests if this thread is alive. A thread is alive if it has been started and has not yet died.
 * @return true if this thread is alive; false otherwise.
 */
static bool CLASS_METHOD()(Thread, isAlive)
{
    return self->_mRunning;
}

/**
 * Waits for this thread to die.
 */
static void CLASS_METHOD()(Thread, join)
{
    self(lock);
    if (self->_mThreadId == pthread_self()) {
        //db_error(
        //"Thread (self=%p): don't call join() from this "
        //"Thread object's thread. It's a guaranteed deadlock!",
        //self);
        self(unlock);
        return;
    }
    while (self->_mRunning) {
        self(wait);
    }
    self(unlock);
}

/**
 * Waits at most millis milliseconds for this thread to die. A timeout of 0 means to wait forever.
 * @param millis the time to wait in milliseconds
 */
static void CLASS_METHOD()(Thread, join, long millis)
{
    self(lock);
    if (self->_mThreadId == pthread_self()) {
        //db_error(
        //"Thread (self=%p): don't call join() from this "
        //"Thread object's thread. It's a guaranteed deadlock!",
        //self);

        return;
    }
    self(wait, millis);
    self(unlock);
}

/**
 * Waits at most millis milliseconds plus nanos nanoseconds for this thread to die.
 * @param millis the time to wait in milliseconds
 * @param nanos 0-999999 additional nanoseconds to wait
 */
static void CLASS_METHOD()(Thread, join, long millis, int nanos)
{
    self(lock);
    if (self->_mThreadId == pthread_self()) {
        //db_error(
        //"Thread (self=%p): don't call join() from this "
        //"Thread object's thread. It's a guaranteed deadlock!",
        //self);

        return;
    }
    //TODO: to be implemented.
    self(unlock);
}

// +++++++++++++++++++++++++++
// |   getters and setters   |
// +++++++++++++++++++++++++++
static GET()(Thread, String*, _mName, Name)

//static SET()(Thread, String*, _mName, Name)
static void CLASS_METHOD()(Thread, setName, String* name)
{
    assert(name);
    if (self->_mName)
        DELETE(self->_mName);
    self->_mName = REFER(name);
}

// +++++++++++++++++++++++++++
// |   static functions      |
// +++++++++++++++++++++++++++
static int createThreadEtc(thread_func_t entryFunction,
                                   void* userData,
                             const char* threadName,
                                 int32_t threadPriority,
                                  size_t threadStackSize,
                              pthread_t* threadId)
{
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    if (threadStackSize) {
        pthread_attr_setstacksize(&attr, threadStackSize);
    }

    pthread_t thread;
    int result = pthread_create(&thread, &attr, entryFunction, userData);
    pthread_attr_destroy(&attr);
    if (result != 0) {
        //ALOGE("androidCreateRawThreadEtc failed (entry=%p, res=%d, errno=%d)\n"
        //     "(android threadPriority=%d)",
        //    entryFunction, result, errno, threadPriority);
        return 0;
    }

    if (threadId != NULL) {
        *threadId = thread;
    }

    return 1;
}

static void* threadRun(void* obj)
{
    Thread* self = (Thread*)obj;

    if (self->_mTarget)
        _IM(self->_mTarget, run);
    else
        self(run);

    self(lock);
    self->_mRunning = false;
    self->_mThreadId = -1;
    self(notifyAll);
    self(unlock);
    return NULL;
}

BEGIN_CLASS(Thread, Object)
       IMPLEMENTS(Thread, Runnable)
 CONSTRUCTOR(map)(Thread)
 CONSTRUCTOR(map)(Thread, Runnable* target)
  DESTRUCTOR(map)(Thread)
CLASS_METHOD(map)(Thread, getId)
CLASS_METHOD(map)(Thread, isAlive)
CLASS_METHOD(map)(Thread, start)
CLASS_METHOD(map)(Thread, join)
CLASS_METHOD(map)(Thread, join, long millis)
CLASS_METHOD(map)(Thread, join, long millis, int nanos)
         GET(map)(Thread, int, _mName, Name)
         SET(map)(Thread, int, _mName, Name)
END_CLASS

