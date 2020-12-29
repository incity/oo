//1. The .cc .cpp .cxx related header files
#include "Vector.h"
//2. C system include files.
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.
#include "AbstractList.h"

/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - - */
/*               \\\\\\\           |  Class ObjectVectorItr  |           ///////             */
/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - - */

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(ObjectVectorItr, ObjectVector* vector, int index)
{
    CONSTRUCTOR(super)(Object);
    self->vector = vector;
    self->cursor = index;
    self->lastRet = -1;
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(ObjectVectorItr)
{
    DESTRUCTOR(super)(Object);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
static bool CLASS_METHOD()(ObjectVectorItr, hasNext)
{
    return self->cursor != self->vector->_mElementCount;
}

static Object* CLASS_METHOD()(ObjectVectorItr, next)
{
    int i = self->cursor;
    assert(i < self->vector->_mElementCount);
    self->cursor = i + 1;
    self->lastRet = i;
    return self->vector->_mElementData[i];
}

static bool CLASS_METHOD()(ObjectVectorItr, hasPrevious)
{
    return self->cursor != 0;
}

static Object* CLASS_METHOD()(ObjectVectorItr, previous)
{
    int i = self->cursor - 1;
    assert(i >= 0);
    self->cursor = i;
    self->lastRet = i;
    return self->vector->_mElementData[i];
}

static int CLASS_METHOD()(ObjectVectorItr, nextIndex)
{
    return self->cursor;
}

static int CLASS_METHOD()(ObjectVectorItr, previousIndex)
{
    return self->cursor - 1;
}

static void CLASS_METHOD()(ObjectVectorItr, remove)
{
    assert(self->lastRet != -1);
    _M(self->vector, remove, self->lastRet);
    self->cursor = self->lastRet;
    self->lastRet = -1;
}

static void CLASS_METHOD()(ObjectVectorItr, set, Object* e)
{
    assert(self->lastRet != -1);
    _M(self->vector, set, self->lastRet, e);
}

static void CLASS_METHOD()(ObjectVectorItr, add, Object* e)
{
    int i = self->cursor;
    _M(self->vector, add, i, e);
    self->cursor = i + 1;
    self->lastRet = -1;
}

BEGIN_CLASS(ObjectVectorItr, Object)
    IMPLEMENTS(ObjectVectorItr, ObjectListIterator, ListIterator)
    CONSTRUCTOR(map)(ObjectVectorItr, ObjectLinkedList* list, int index)
     DESTRUCTOR(map)(ObjectVectorItr)
   CLASS_METHOD(map)(ObjectVectorItr, hasNext)
   CLASS_METHOD(map)(ObjectVectorItr, next)
   CLASS_METHOD(map)(ObjectVectorItr, hasPrevious)
   CLASS_METHOD(map)(ObjectVectorItr, previous)
   CLASS_METHOD(map)(ObjectVectorItr, nextIndex)
   CLASS_METHOD(map)(ObjectVectorItr, previousIndex)
   CLASS_METHOD(map)(ObjectVectorItr, remove)
   CLASS_METHOD(map)(ObjectVectorItr, set, Object* e)
   CLASS_METHOD(map)(ObjectVectorItr, add, Object* e)
END_CLASS

/* - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */
/*             \\\\\\\           |    Class ObjectVector   |           ///////           */
/* - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(ObjectVector, int initialCapacity, int capacityIncrement)
{
    CONSTRUCTOR(super)(Object);
    assert(initialCapacity > 0);
    self->_mElementData = (Object**)calloc(initialCapacity, sizeof(self->_mElementData));
    self->_mCapacity = initialCapacity;
    self->_mCapacityIncrement = capacityIncrement;
}

static CONSTRUCTOR()(ObjectVector, int initialCapacity)
{
    CONSTRUCTOR(super)(ObjectVector, initialCapacity, 0);
}

static CONSTRUCTOR()(ObjectVector)
{
    CONSTRUCTOR(super)(ObjectVector, 10);
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(ObjectVector)
{
    if (self->_mElementData)
        free(self->_mElementData);
    DESTRUCTOR(super)(Object);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++

/**
 * Trims the capacity of this vector to be the vector's current
 * size. If the capacity of this vector is larger than its current
 * size, then the capacity is changed to equal the size by replacing
 * its internal data array, kept in the field {@code elementData},
 * with a smaller one. An application can use this operation to
 * minimize the storage of a vector.
 */
static void CLASS_METHOD()(ObjectVector, trimToSize)
{
    if (self->_mElementCount < self->_mCapacity) {
        self->_mElementData = realloc(self->_mElementData, self->_mElementCount);
        self->_mCapacity = self->_mElementCount;
    }
}

static void CLASS_METHOD()(ObjectVector, ensureCapacity, int minCapacity)
{
    if (minCapacity > 0) {
        if (minCapacity - self->_mCapacity > 0)
            self(grow, minCapacity);
    }
}

static void CLASS_METHOD()(ObjectVector, grow, int minCapacity)
{
    int oldCapacity = self->_mCapacity;
    int newCapacity = oldCapacity + ((self->_mCapacityIncrement > 0) ?
                                     self->_mCapacityIncrement : oldCapacity);
    if (newCapacity - minCapacity < 0)
        newCapacity = minCapacity;
    self->_mElementData = realloc(self->_mElementData, newCapacity);
    self->_mCapacity = newCapacity;
}

/**
 * Returns the current capacity of this vector.
 *
 * @return  the current capacity (the length of its internal
 *          data array, kept in the field {@code elementData}
 *          of this vector)
 */
static int CLASS_METHOD()(ObjectVector, capacity)
{
    return self->_mCapacity;
}

/**
 * Returns the number of components in this vector.
 *
 * @return  the number of components in this vector
 */
static int CLASS_METHOD()(ObjectVector, size)
{
    return self->_mElementCount;
}

/**
 * Tests if this vector has no components.
 *
 * @return  {@code true} if and only if this vector has
 *          no components, that is, its size is zero;
 *          {@code false} otherwise.
 */
static bool CLASS_METHOD()(ObjectVector, isEmpty)
{
    return self->_mElementCount == 0;
}

/**
 * Returns {@code true} if this vector contains the specified element.
 * More formally, returns {@code true} if and only if this vector
 * contains at least one element {@code e} such that
 * <tt>(o==null&nbsp;?&nbsp;e==null&nbsp;:&nbsp;o.equals(e))</tt>.
 *
 * @param o element whose presence in this vector is to be tested
 * @return {@code true} if this vector contains the specified element
 */
static bool CLASS_METHOD()(ObjectVector, contains, Object* o)
{
    return self(indexOf, o, 0) >= 0;
}

/**
 * Returns the index of the first occurrence of the specified element
 * in this vector, or -1 if this vector does not contain the element.
 * More formally, returns the lowest index {@code i} such that
 * <tt>(o==null&nbsp;?&nbsp;get(i)==null&nbsp;:&nbsp;o.equals(get(i)))</tt>,
 * or -1 if there is no such index.
 *
 * @param o element to search for
 * @return the index of the first occurrence of the specified element in
 *         this vector, or -1 if this vector does not contain the element
 */
static int CLASS_METHOD()(ObjectVector, indexOf, Object* o)
{
    return self(indexOf, o, 0);
}

/**
 * Returns the index of the first occurrence of the specified element in
 * this vector, searching forwards from {@code index}, or returns -1 if
 * the element is not found.
 * More formally, returns the lowest index {@code i} such that
 * <tt>(i&nbsp;&gt;=&nbsp;index&nbsp;&amp;&amp;&nbsp;(o==null&nbsp;?&nbsp;get(i)==null&nbsp;:&nbsp;o.equals(get(i))))</tt>,
 * or -1 if there is no such index.
 *
 * @param o element to search for
 * @param index index to start searching from
 * @return the index of the first occurrence of the element in
 *         this vector at position {@code index} or later in the vector;
 *         {@code -1} if the element is not found.
 */
static int CLASS_METHOD()(ObjectVector, indexOf, Object* o, int index)
{
    int i;
    if (o == NULL) {
        for (i = index; i < self->_mElementCount; i++)
            if (self->_mElementData[i] == NULL)
                return i;
    } else {
        for (i = index; i < self->_mElementCount; i++)
            if (_M(o, equals, self->_mElementData[i]))
                return i;
    }
    return -1;
}

/**
 * Returns the index of the last occurrence of the specified element
 * in this vector, or -1 if this vector does not contain the element.
 * More formally, returns the highest index {@code i} such that
 * <tt>(o==null&nbsp;?&nbsp;get(i)==null&nbsp;:&nbsp;o.equals(get(i)))</tt>,
 * or -1 if there is no such index.
 *
 * @param o element to search for
 * @return the index of the last occurrence of the specified element in
 *         this vector, or -1 if this vector does not contain the element
 */
static int CLASS_METHOD()(ObjectVector, lastIndexOf, Object* o)
{
    return self(lastIndexOf, o, self->_mElementCount-1);
}

/**
 * Returns the index of the last occurrence of the specified element in
 * this vector, searching backwards from {@code index}, or returns -1 if
 * the element is not found.
 * More formally, returns the highest index {@code i} such that
 * <tt>(i&nbsp;&lt;=&nbsp;index&nbsp;&amp;&amp;&nbsp;(o==null&nbsp;?&nbsp;get(i)==null&nbsp;:&nbsp;o.equals(get(i))))</tt>,
 * or -1 if there is no such index.
 *
 * @param o element to search for
 * @param index index to start searching backwards from
 * @return the index of the last occurrence of the element at position
 *         less than or equal to {@code index} in this vector;
 *         -1 if the element is not found.
 */
static int CLASS_METHOD()(ObjectVector, lastIndexOf, Object* o, int index)
{
    assert(index < self->_mElementCount);
    int i;
    if (o == NULL) {
        for (i = index; i >= 0; i--)
            if (self->_mElementData[i] == NULL)
                return i;
    } else {
        for (i = index; i >= 0; i--)
            if (_M(o, equals, self->_mElementData[i]))
                return i;
    }
    return -1;
}

/**
 * Returns the component at the specified index.
 *
 * <p>This method is identical in functionality to the {@link #get(int)}
 * method (which is part of the {@link List} interface).
 *
 * @param      index   an index into this vector
 * @return     the component at the specified index
 */
static Object* CLASS_METHOD()(ObjectVector, elementAt, int index)
{
    assert(index < self->_mElementCount);
    return self->_mElementData[index];
}

/**
 * Returns the first component (the item at index {@code 0}) of
 * this vector.
 *
 * @return     the first component of this vector
 */
static Object* CLASS_METHOD()(ObjectVector, firstElement)
{
    if (self->_mElementCount == 0) {
        return NULL;
    }
    return self->_mElementData[0];
}

/**
 * Returns the last component of the vector.
 *
 * @return  the last component of the vector, i.e., the component at index
 *          <code>size()&nbsp;-&nbsp;1</code>.
 */
static Object* CLASS_METHOD()(ObjectVector, lastElement)
{
    if (self->_mElementCount == 0) {
        return NULL;
    }
    return self->_mElementData[0];
}

static void CLASS_METHOD()(ObjectVector, setElementAt, Object* obj, int index)
{
    assert(index < self->_mElementCount);
    DELETE(self->_mElementData[index]);
    self->_mElementData[index] = REFER(obj);
}

static void CLASS_METHOD()(ObjectVector, removeElementAt, int index)
{
    assert(index < self->_mElementCount && index >= 0);
    DELETE(self->_mElementData[index]);
    int numMoved = (self->_mElementCount-index-1)*sizeof(self->_mElementData);
    if (numMoved > 0)
        memmove(self->_mElementData+index, self->_mElementData+index+1, numMoved);
    self->_mElementCount--;
}

static void CLASS_METHOD()(ObjectVector, insertElementAt, Object* obj, int index)
{
    assert(index <= self->_mElementCount);
    self(ensureCapacity, self->_mElementCount + 1);
    memmove(self->_mElementData + index + 1, self->_mElementData + index, self->_mElementCount - index);
    self->_mElementData[index] = REFER(obj);
    self->_mElementCount++;
}

static void CLASS_METHOD()(ObjectVector, addElement, Object* obj)
{
    self(ensureCapacity, self->_mElementCount + 1);
    self->_mElementData[self->_mElementCount++] = REFER(obj);
}

static bool CLASS_METHOD()(ObjectVector, removeElement, Object* obj)
{
    int i = self(indexOf, obj);
    if (i >= 0) {
        self(removeElementAt, i);
        return true;
    }
    return false;
}

static void CLASS_METHOD()(ObjectVector, removeAllElements)
{
    for (int i = 0; i < self->_mElementCount; i++)
        DELETE(self->_mElementData[i]);
    self->_mElementCount = 0;
}

/**
 * Returns the element at the specified position in this Vector.
 *
 * @param index index of the element to return
 * @return object at the specified index
 */
static Object* CLASS_METHOD()(ObjectVector, get, int index)
{
    assert(index < self->_mElementCount);
    return self->_mElementData[index];
}

/**
 * Replaces the element at the specified position in this Vector with the
 * specified element.
 *
 * @param index index of the element to replace
 * @param element element to be stored at the specified position
 * @return the element previously at the specified position
 */
static Object* CLASS_METHOD()(ObjectVector, set, Object* obj, int index)
{
    assert(index < self->_mElementCount);
    Object* oldValue = self->_mElementData[index];
    self->_mElementData[index] = REFER(obj);
    return oldValue;
}

/**
 * Appends the specified element to the end of this Vector.
 *
 * @param e element to be appended to this Vector
 * @return {@code true} (as specified by {@link Collection#add})
 */
static bool CLASS_METHOD()(ObjectVector, add, Object* e)
{
    self(ensureCapacity, self->_mElementCount + 1);
    self->_mElementData[self->_mElementCount++] = e;
    return true;
}

/**
 * Removes the first occurrence of the specified element in this Vector
 * If the Vector does not contain the element, it is unchanged.  More
 * formally, removes the element with the lowest index i such that
 * {@code (o==null ? get(i)==null : o.equals(get(i)))} (if such
 * an element exists).
 *
 * @param o element to be removed from this Vector, if present
 * @return true if the Vector contained the specified element
 */
static bool CLASS_METHOD()(ObjectVector, removeObject, Object* o)
{
    return self(removeElement, o);
}

/**
 * Inserts the specified element at the specified position in this Vector.
 * Shifts the element currently at that position (if any) and any
 * subsequent elements to the right (adds one to their indices).
 *
 * @param index index at which the specified element is to be inserted
 * @param element element to be inserted
 */
static void CLASS_METHOD()(ObjectVector, add, int index, Object* element)
{
    self(insertElementAt, element, index);
}

/**
 * Removes the element at the specified position in this Vector.
 * Shifts any subsequent elements to the left (subtracts one from their
 * indices).  Returns the element that was removed from the Vector.
 *
 * @param index the index of the element to be removed
 * @return element that was removed
 */

static bool CLASS_METHOD()(ObjectVector, remove, int index)
{
    assert(index >= 0 && index < self->_mElementCount);
    Object* oldValue = self->_mElementData[index];

    int numMoved = (self->_mElementCount-index-1)*sizeof(self->_mElementData);
    if (numMoved > 0)
        memmove(self->_mElementData+index, self->_mElementData+index+1, numMoved);

    return oldValue;
}

/**
 * Removes all of the elements from this Vector.  The Vector will
 * be empty after this call returns (unless it throws an exception).
 */
static void CLASS_METHOD()(ObjectVector, clear)
{
    self(removeAllElements);
}

static ObjectVectorIterator* CLASS_METHOD()(ObjectVector, listIterator, int index)
{
    ObjectVectorItr* iterator = NEW(ObjectVectorItr, self, index);
    return INTERFACEOF(iterator, ObjectVectorIterator, ListIterator);
}

static ObjectVectorIterator* CLASS_METHOD()(ObjectVector, listIterator)
{
    return self(listIterator, 0);
}

//BEGIN_CLASS(ObjectVector, Object)
// A trick to inherit AbstractObjectCollection member function
 BEGIN_CLASS(ObjectVector, AbstractObjectList)
// IMPLEMENTS(ObjectVector, ObjectList, List)
    CONSTRUCTOR(map)(ObjectVector, int initialCapacity, int capacityIncrement)
    CONSTRUCTOR(map)(ObjectVector, int initialCapacity)
    CONSTRUCTOR(map)(ObjectVector)
     DESTRUCTOR(map)(ObjectVector)
   CLASS_METHOD(map)(ObjectVector, trimToSize)
   CLASS_METHOD(map)(ObjectVector, ensureCapacity, int minCapacity)
   CLASS_METHOD(map)(ObjectVector, grow, int minCapacity)
   CLASS_METHOD(map)(ObjectVector, capacity)
   CLASS_METHOD(map)(ObjectVector, size)
   CLASS_METHOD(map)(ObjectVector, isEmpty)
   CLASS_METHOD(map)(ObjectVector, contains, Object* o)
   CLASS_METHOD(map)(ObjectVector, indexOf, Object* o)
   CLASS_METHOD(map)(ObjectVector, indexOf, Object* o, int index)
   CLASS_METHOD(map)(ObjectVector, lastIndexOf, Object* o)
   CLASS_METHOD(map)(ObjectVector, lastIndexOf, Object* o, int index)
   CLASS_METHOD(map)(ObjectVector, elementAt, int index)
   CLASS_METHOD(map)(ObjectVector, firstElement)
   CLASS_METHOD(map)(ObjectVector, lastElement)
   CLASS_METHOD(map)(ObjectVector, setElementAt, Object* obj, int index)
   CLASS_METHOD(map)(ObjectVector, removeElementAt, int index)
   CLASS_METHOD(map)(ObjectVector, insertElementAt, Object* obj, int index)
   CLASS_METHOD(map)(ObjectVector, addElement, Object* obj)
   CLASS_METHOD(map)(ObjectVector, removeElement, Object* obj)
   CLASS_METHOD(map)(ObjectVector, removeAllElements)
   CLASS_METHOD(map)(ObjectVector, get, int index)
   CLASS_METHOD(map)(ObjectVector, set, Object* obj, int index)
   CLASS_METHOD(map)(ObjectVector, add, Object* e)
   CLASS_METHOD(map)(ObjectVector, removeObject, Object* o)
   CLASS_METHOD(map)(ObjectVector, remove, int index)
   CLASS_METHOD(map)(ObjectVector, add, int index, Object* element)
   CLASS_METHOD(map)(ObjectVector, listIterator)
   CLASS_METHOD(map)(ObjectVector, listIterator, int index)
END_CLASS

