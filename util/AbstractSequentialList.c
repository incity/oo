//1. The .cc .cpp .cxx related header files
#include "AbstractSequentialList.h"
//2. C system include files.
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(AbstractSequentialList)
{
    CONSTRUCTOR(super)(Object);
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(AbstractSequentialList)
{
    DESTRUCTOR(super)(Object);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
static void* CLASS_METHOD()(AbstractSequentialList, get, int index)
{
    ListIterator* it = _M(self, listIterator, index);
    if (it)
        _IM(it, next);

    return NULL;
}

static void* CLASS_METHOD()(AbstractSequentialList, set, int index, void* element)
{
    ListIterator* it = _M(self, listIterator, index);
    if (!it)
        return NULL;
    void* oldVal = _IM(it, next);
    _IM(it, set, element);
    return oldVal;
}

static void CLASS_METHOD()(AbstractSequentialList, add, int index, void* element)
{
    ListIterator* it = _M(self, listIterator, index);
    if(!it)
        return;
    _IM(it, add, element);
}

static Iterator* CLASS_METHOD()(AbstractSequentialList, iterator)
{
    return (Iterator*)_M(self, listIterator);
}

BEGIN_CLASS(AbstractSequentialList, AbstractList)
    CONSTRUCTOR(map)(AbstractSequentialList)
     DESTRUCTOR(map)(AbstractSequentialList)
   CLASS_METHOD(map)(AbstractSequentialList, get, int index)
   CLASS_METHOD(map)(AbstractSequentialList, set, int index, void* element)
   CLASS_METHOD(map)(AbstractSequentialList, add, int index, void* element)
   CLASS_METHOD(map)(AbstractSequentialList, iterator)
END_CLASS
