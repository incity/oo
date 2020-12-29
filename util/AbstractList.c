//1. The .cc .cpp .cxx related header files
#include "AbstractList.h"
//2. C system include files.
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.
#include "lang/String.h"

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(AbstractObjectList)
{
    CONSTRUCTOR(super)(Object);
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(AbstractObjectList)
{
    DESTRUCTOR(super)(Object);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
static bool CLASS_METHOD()(AbstractObjectList, add, void* e)
{
    int size = _M(self, size);
    self(add, size, e);
    return true;
}

static void CLASS_METHOD()(AbstractObjectList, add, int index, void* element)
{
    //Unsupported Operation
    assert(0);
}

static void CLASS_METHOD()(AbstractObjectList, remove, int index)
{
    //Unsupported Operation
    assert(0);
}

static int CLASS_METHOD()(AbstractObjectList, indexOf, Object* o)
{
    ObjectListIterator* it = self(listIterator);
    if (o == NULL) {
        while (_IM(it, hasNext))
            if (_IM(it, next) == NULL)
                return _IM(it, previousIndex);
    } else {
        while (_IM(it, hasNext))
            if (_M(o, equals, _IM(it, next)))
                return _IM(it, previousIndex);
    }

    return -1;
}

static int CLASS_METHOD()(AbstractObjectList, lastIndexOf, Object* o)
{
    int size = self(size);
    ObjectListIterator* it = self(listIterator, size);
    if (o == NULL) {
        while (_IM(it, hasPrevious))
            if (_IM(it, previous) == NULL)
                return _IM(it, nextIndex);
    } else {
        while (_IM(it, hasPrevious))
            if (_M(o, equals, _IM(it, previous)))
                return _IM(it, nextIndex);
    }

    return -1;
}

BEGIN_CLASS(AbstractObjectList, AbstractObjectCollection)
    IMPLEMENTS(AbstractObjectList, ObjectList, List)
    CONSTRUCTOR(map)(AbstractObjectList)
     DESTRUCTOR(map)(AbstractObjectList)
   CLASS_METHOD(map)(AbstractObjectList, add, void* e)
   CLASS_METHOD(map)(AbstractObjectList, add, int index, void* element)
   CLASS_METHOD(map)(AbstractObjectList, indexOf, Object* o)
   CLASS_METHOD(map)(AbstractObjectList, lastIndexOf, Object* o)
END_CLASS
