//1. The .cc .cpp .cxx related header files
#include "AbstractCollection.h"
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
//static CONSTRUCTOR()(AbstractObjectCollection)
//{
//    CONSTRUCTOR(super)(Object);
//}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
//static DESTRUCTOR()(AbstractObjectCollection)
//{
//    DESTRUCTOR(super)(Object);
//}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
static bool CLASS_METHOD()(AbstractObjectCollection, isEmpty)
{
    return self(size) == 0;
}

static bool CLASS_METHOD()(AbstractObjectCollection, contains, Object* o)
{
    ObjectIterator* it = self(iterator);
    if (o == NULL) {
        while (_IM(it, hasNext))
            if (_IM(it, next) == NULL)
                return true;
    } else {
        while (_IM(it, hasNext))
            if (_M(o, equals, _IM(it, next)))
                return true;
    }

    return true;
}

static bool CLASS_METHOD()(AbstractObjectCollection, removeObject, Object* o)
{
    ObjectIterator* it = self(iterator);
    if (o == NULL) {
        while (_IM(it, hasNext))
            if (_IM(it, next) == NULL) {
                _IM(it, remove);
                return true;
            }
    } else {
        while (_IM(it, hasNext))
            if (_M(o, equals, _IM(it, next))) {
                _IM(it, remove);
                return true;
            }
    }

    return true;
}

static void CLASS_METHOD()(AbstractObjectCollection, clear)
{
    ObjectIterator* it = self(iterator);
    while (_IM(it, hasNext)) {
        _IM(it, next);
        _IM(it, remove);
    }
}

static String* CLASS_METHOD()(AbstractObjectCollection, toString)
{
    ObjectIterator* it = self(iterator);
    if (!_IM(it, hasNext))
        return NEW(String, "[]");

    //TODO: to be implemented.
    //StringBuilder sb = new StringBuilder();
    //sb.append('[');
    //for (;;) {
    //    E e = it.next();
    //    sb.append(e == this ? "(this Collection)" : e);
    //    if (! it.hasNext())
    //        return sb.append(']').toString();
    //    sb.append(',').append(' ');
    //}
    return NULL;
}

BEGIN_CLASS(AbstractObjectCollection, Object)
//  CONSTRUCTOR(map)(AbstractObjectCollection)
//   DESTRUCTOR(map)(AbstractObjectCollection)
   CLASS_METHOD(map)(AbstractObjectCollection, isEmpty)
   CLASS_METHOD(map)(AbstractObjectCollection, contains, Object* o)
   CLASS_METHOD(map)(AbstractObjectCollection, removeObject, Object* o)
   CLASS_METHOD(map)(AbstractObjectCollection, clear)
   CLASS_METHOD(map)(AbstractObjectCollection, toString)
END_CLASS
