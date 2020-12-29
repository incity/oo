#ifndef _OO_VECTOR_H_
#define _OO_VECTOR_H_

#include "List.h"

/* - - - - - - - - - - - - - - - +---------------------------+ - - - - - - - - - - - - - - */
/*              \\\\\\\          |   Class ObjectVectorItr   |           ///////           */
/* - - - - - - - - - - - - - - - +---------------------------+ - - - - - - - - - - - - - - */
DECLARE_CLASS(forward)(ObjectVector, Object)

#define   private_class_ObjectVectorItrClass(T, SuperClss)         \
                     extends_class(Object)(T, SuperClss)           \
implements_generic_interface(ListIterator, T, Object*)             \
                       CONSTRUCTOR(public)(T, ObjectVector* vector, int index); \

#define private_class_ObjectVectorItr(T)       \
           extends(Object)(T)                  \
        implements(ObjectListIterator)         \
       ObjectVector* vector;                   \
                 int cursor;                   \
                 int lastRet;

DECLARE_CLASS(private)(ObjectVectorItr, Object)

/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */
/*              \\\\\\\            |    Class ObjectVector   |           ///////           */
/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */

#define public_class_ObjectVectorClass(T, SuperClss)                                      \
                 extends_class(Object)(T, SuperClss)                                      \
    implements_generic_interface(List, T, Object*, ObjectVectorIterator*)                 \
                   CONSTRUCTOR(public)(T, int initialCapacity, int capacityIncrement);    \
                   CONSTRUCTOR(public)(T, int initialCapacity);                           \
             void CLASS_METHOD(public)(T, trimToSize);                                    \
             void CLASS_METHOD(public)(T, ensureCapacity, int minCapacity);               \
             void CLASS_METHOD(public)(T, grow, int minCapacity);                         \
             void CLASS_METHOD(public)(T, setSize, int newSize);                          \
              int CLASS_METHOD(public)(T, indexOf, Object* o, int index);                 \
              int CLASS_METHOD(public)(T, lastIndexOf, Object* o, int index);             \
             void CLASS_METHOD(public)(T, removeElementAt, int index);                    \
             void CLASS_METHOD(public)(T, insertElementAt, Object* obj, int index);       \
             void CLASS_METHOD(public)(T, addElement, Object* obj);                       \
             bool CLASS_METHOD(public)(T, removeElement, Object* obj);                    \
             void CLASS_METHOD(public)(T, removeAllElements);                             \
              int CLASS_METHOD(public)(T, capacity);                                      \
          Object* CLASS_METHOD(public)(T, elementAt, int index);                          \
          Object* CLASS_METHOD(public)(T, firstElement);                                  \
          Object* CLASS_METHOD(public)(T, lastElement);                                   \
             void CLASS_METHOD(public)(T, setElementAt, Object* obj, int index);          \

#define public_class_ObjectVector(T)            \
                  extends(Object)(T)            \
                   implements(ObjectList)       \
                 Object** _mElementData;        \
                      int _mElementCount;       \
                      int _mCapacity;           \
                      int _mCapacityIncrement;

DECLARE_CLASS(public)(ObjectVector, Object)

#endif /* _OO_VECTOR_H_ */
