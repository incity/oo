#ifndef _OO_OBJECT_H_
#define _OO_OBJECT_H_

#include <string.h>
#include "Class.h"
#include <pthread.h>

#define BEGIN_CLASS(Clss, SuperClss) _BEGIN_CLASS(Clss, SuperClss)
#define END_CLASS _END_CLASS

/*
 * declare and build Object
 * selector:
 *     global
 *     global_const
 *     local
 */
#define DECLARE(selector)            DECLARE_##selector
#define BUILD(selector)              BUILD_##selector

#define NEW(Clss, ...)               NEWEX(Clss, malloc, 1, ##__VA_ARGS__)
#define ARRAY_NEW(Clss, n, ...)      NEWEX(Clss, malloc, n, ##__VA_ARGS__)

/*
#define LOCAL_NEW(Clss, ...)                             \
        NEWEX(Clss, alloca, 1, ##__VA_ARGS__)

#define LOCAL_ARRAY_NEW(Clss, n, ...)                    \
        NEWEX(Clss, alloca, n, ##__VA_ARGS__)
*/

#define REFER(obj)            ((TYPEOF(obj))_c(obj)->refer(obj))
#define CLONE(obj)            ((TYPEOF(obj))_c(obj)->clone(obj))
#define DELETE(obj)           __deleteObject((Object*)(obj), true)
#define DELETE_ARRAY(obj, n)  __deleteArray((Object*)(obj), n)
#define INSTANCEOF(obj, clss) __instanceOf((Object*)(obj), (ObjectClass*)(&Class(clss)))

//------------------------------------------------------------------
// Do not write code that depends on anything below this line.
typedef struct oo_ObjectClass ObjectClass;
typedef struct oo_Object Object;
typedef struct oo_String String;

typedef void AnyClass;
typedef void (*ClassLoader)(AnyClass*);

#define public_class_ObjectClass(T, SuperClss)                       \
             CONSTRUCTOR(public)(T);                                 \
              DESTRUCTOR(public)(T);                                 \
       CONST_CONSTRUCTOR(public)(T);                                 \
       long CLASS_METHOD(public)(T, hashCode);                       \
         T* CLASS_METHOD(public)(T, refer);                          \
    String* CLASS_METHOD(public)(T, toString);                       \
       bool CLASS_METHOD(public)(T, equals, Object* obj);            \
        int CLASS_METHOD(public)(T, lock);                           \
       void CLASS_METHOD(public)(T, unlock);                         \
        int CLASS_METHOD(public)(T, tryLock);                        \
       void CLASS_METHOD(public)(T, notify);                         \
       void CLASS_METHOD(public)(T, notifyAll);                      \
       void CLASS_METHOD(public)(T, wait);                           \
       void CLASS_METHOD(public)(T, wait, long millis);              \
       void CLASS_METHOD(public)(T, wait, long millis, int nanos);   \
 Object* CLASS_METHOD(protected)(T, clone);                          \
      ClassLoader loadClass;                                         \
      ClassType(SuperClss)* super; /* immediate superclass */        \
      const char* typeName;                                          \
      size_t objSize;                                                \
      size_t interfaceOffset;

enum {
    STACK_OBJECT,
    HEAP_OBJECT,
    CONST_OBJECT,
};

/* Object start with 0xFE
 * 字节FF和FE在UTF-8编码中永远不会出现
 */
#define public_class_Object(T)                  \
                   byte _mFirstByteMustBe0xFE;  \
          ClassType(T)* class;                  \
                   byte _mObjType;              \
                   int _mObjRefCount;           \
        pthread_cond_t _mCond;                  \
       pthread_mutex_t _mMutex;                 \

struct oo_ObjectClass {
    public_class_ObjectClass(Object, Object)
};

struct oo_Object {
    public_class_Object(Object)
};

#define _BEGIN_CLASS(Clss, SuperClss)                               \
        static void Clss##ClassLoader(ClassType(Clss)* _class);     \
        ClassType(Clss) Class(Clss) = {                             \
            .loadClass = (ClassLoader)Clss##ClassLoader             \
        };                                                          \
        AUTO_LOAD_CLASS(Clss)                                       \
        static void Clss##ClassLoader(ClassType(Clss)* _class)      \
        {                                                           \
            size_t * _pintfOffset = NULL;                           \
            Class(SuperClss).loadClass(_class);                     \
            _class->super = (SuperClss##Class*)&Class(SuperClss);   \
            _class->typeName = #Clss;                               \
            _class->objSize = sizeof(Clss);                         \
            _pintfOffset = &_class->interfaceOffset;

#define _END_CLASS                                                  \
        }

#define LOAD_CLASS(Clss) \
        Class(Clss).loadClass((ObjectClass*)(&(Class(Clss))))

#define AUTO_LOAD_CLASS(Clss)                                                   \
        static __attribute__((constructor(101))) void Clss##ClassAutoloader()   \
        {                                                                       \
            LOAD_CLASS(Clss);                                                   \
        }

#define NEWEX(Clss, allocator, n, ...)                   \
        ({                                               \
        Clss* o = (Clss*)allocator((n)*sizeof(Clss));    \
        if (o) {                                         \
            BUILDEX(o, Clss, (n), ##__VA_ARGS__);        \
            o->_mObjType = HEAP_OBJECT;                  \
        }                                                \
        o;})

#define BUILDEX(obj, Clss, n, ...)                                                 \
        do {                                                                       \
            int i = 0;                                                             \
            memset((obj), 0, sizeof(Clss)*n);                                      \
            do {                                                                   \
                __initObject((Object*)((obj) + i), (ObjectClass*)&Class(Clss));    \
                Class(Clss).CONSTRUCTOR(m)(Clss, ##__VA_ARGS__)                    \
                                    ((obj) + i, ##__VA_ARGS__);                    \
            } while(++i < (n));                                                    \
        } while(0)

#define BUILD_GLOBAL(obj, Clss, n, ...)                                            \
        Clss obj[n];                                                               \
        static __attribute__((destructor(201))) void __destroy_global_##obj()      \
        {                                                                          \
            DELETE(obj);                                                           \
        }                                                                          \
        static __attribute__((constructor(200))) void __build_global_##obj()       \
        {                                                                          \
            BUILDEX(obj, Clss, n, ##__VA_ARGS__);                                  \
        }

#define BUILD_CONST(obj, Clss, n, ...)                                        \
        Clss obj[n];                                                          \
        static __attribute__((constructor(201))) void __build_const_##obj()   \
        {                                                                     \
            int i = 0;                                                        \
            memset(obj, 0, sizeof(Clss)*n);                                   \
            obj->_mObjType = CONST_OBJECT;                                    \
            do {                                                              \
                __initObject((Object*)&obj[i], (ObjectClass*)&Class(Clss));   \
                Class(Clss).CONST_CONSTRUCTOR(m)(Clss, ##__VA_ARGS__)         \
                                            (&obj[i], ##__VA_ARGS__);         \
            } while(++i < (n));                                               \
        }

#define DECLARE_global_const(obj, Clss)    extern Clss obj[1];
#define DECLARE_global(obj, Clss)          extern Clss obj[1];
#define DECLARE_(obj, Clss)          extern Clss obj[1];

#define BUILD_global(obj, Clss, ...)       BUILD_GLOBAL(obj, Clss, 1, ##__VA_ARGS__)
#define BUILD_global_const(obj, Clss, ...) BUILD_CONST(obj, Clss, 1, ##__VA_ARGS__)
#define BUILD_local(obj, Clss, ...)

void __initObject(Object* pobj, ObjectClass* _class);
void __deleteObject(Object* obj, bool wouldFree);
void __deleteArray(Object* obj, int n);
bool __instanceOf(Object *obj, ObjectClass* clss);

extern ObjectClass Class(Object);

#endif /* _OO_OBJECT_H_ */
