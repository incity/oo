//1. The .cc .cpp .cxx related header files
#include "LinkedList.h"
//2. C system include files.
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.
#include "AbstractList.h"

/* - - - - - - - - - - - - - - - - +--------------------+ - - - - - - - - - - - - - - */
/*              \\\\\\\            |  Class ObjectNode  |           ///////           */
/* - - - - - - - - - - - - - - - - +--------------------+ - - - - - - - - - - - - - - */

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(ObjectNode, ObjectNode* prev, Object* element, ObjectNode* next)
{
    CONSTRUCTOR(super)(Object);
    self->item = REFER(element);
    self->next = next;
    self->prev = prev;
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(ObjectNode)
{
    DELETE(self->item);
    DESTRUCTOR(super)(Object);
}

BEGIN_CLASS(ObjectNode, Object)
    CONSTRUCTOR(map)(ObjectNode, ObjectNode* prev, Object* element, ObjectNode* next)
     DESTRUCTOR(map)(ObjectNode)
END_CLASS

/* - - - - - - - - - - - - - - - +----------------------------+ - - - - - - - - - - - - - - */
/*              \\\\\\\          |  Class ObjectLinkedListItr |           ///////           */
/* - - - - - - - - - - - - - - - +----------------------------+ - - - - - - - - - - - - - - */

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(ObjectLinkedListItr, ObjectLinkedList* list, int index)
{
    CONSTRUCTOR(super)(Object);
    self->lastReturned = NULL;
    self->list = list;
    self->next = (index == list->_mSize) ? NULL : _M(list, node, index);
    self->nextIndex = index;
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(ObjectLinkedListItr)
{
    DESTRUCTOR(super)(Object);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
static bool CLASS_METHOD()(ObjectLinkedListItr, hasNext)
{
    return self->nextIndex < self->list->_mSize;
}

static Object* CLASS_METHOD()(ObjectLinkedListItr, next)
{
    if (!self(hasNext)) {
        return NULL;
    }
    self->lastReturned = self->next;
    self->next = self->next->next;
    self->nextIndex++;
    return self->lastReturned->item;
}

static bool CLASS_METHOD()(ObjectLinkedListItr, hasPrevious)
{
    return self->nextIndex > 0;
}

static Object* CLASS_METHOD()(ObjectLinkedListItr, previous)
{
    if (!self(hasPrevious)) {
        return NULL;
    }

    self->lastReturned = self->next = (self->next == NULL) ? self->list->_mLast : self->next->prev;
    self->nextIndex--;
    return self->lastReturned->item;
}

static int CLASS_METHOD()(ObjectLinkedListItr, nextIndex)
{
    return self->nextIndex;
}

static int CLASS_METHOD()(ObjectLinkedListItr, previousIndex)
{
    return self->nextIndex - 1;
}

static void CLASS_METHOD()(ObjectLinkedListItr, remove)
{
    if (self->lastReturned == NULL)
        return;

    ObjectNode* lastNext = self->lastReturned->next;
    _M(self->list, unlink, self->lastReturned);
    if (self->next == self->lastReturned)
        self->next = lastNext;
    else
        self->nextIndex--;
    self->lastReturned = NULL;
}

static void CLASS_METHOD()(ObjectLinkedListItr, set, Object* e)
{
    if (self->lastReturned == NULL)
        return;
    self->lastReturned->item = e;
}

static void CLASS_METHOD()(ObjectLinkedListItr, add, Object* e)
{
    self->lastReturned = NULL;
    if (self->next == NULL)
        _M(self->list, linkLast, e);
    else
        _M(self->list, linkBefore, e, self->next);
    self->nextIndex++;
}

BEGIN_CLASS(ObjectLinkedListItr, Object)
    IMPLEMENTS(ObjectLinkedListItr, ObjectListIterator, ListIterator)
    CONSTRUCTOR(map)(ObjectLinkedListItr, ObjectLinkedList* list, int index)
     DESTRUCTOR(map)(ObjectLinkedListItr)
   CLASS_METHOD(map)(ObjectLinkedListItr, hasNext)
   CLASS_METHOD(map)(ObjectLinkedListItr, next)
   CLASS_METHOD(map)(ObjectLinkedListItr, hasPrevious)
   CLASS_METHOD(map)(ObjectLinkedListItr, previous)
   CLASS_METHOD(map)(ObjectLinkedListItr, nextIndex)
   CLASS_METHOD(map)(ObjectLinkedListItr, previousIndex)
   CLASS_METHOD(map)(ObjectLinkedListItr, remove)
   CLASS_METHOD(map)(ObjectLinkedListItr, set, Object* e)
   CLASS_METHOD(map)(ObjectLinkedListItr, add, Object* e)
END_CLASS

/* - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */
/*             \\\\\\\           |  Class ObjectLinkedList |           ///////           */
/* - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(ObjectLinkedList)
{
    CONSTRUCTOR(super)(Object);
    self->_mFirst = NULL;
    self->_mLast = NULL;
    self->_mSize = 0;
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(ObjectLinkedList)
{
    self(clear);
    DESTRUCTOR(super)(Object);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
/**
 * Links e as first element.
 */
static void CLASS_METHOD()(ObjectLinkedList, linkFirst, Object* e)
{
    ObjectNode* f = self->_mFirst;
    ObjectNode* newNode = NEW(ObjectNode, NULL, e, f);
    self->_mFirst = newNode;
    if (f == NULL)
        self->_mLast = newNode;
    else
        f->prev = newNode;
}

/**
 * Links e as last element.
 */
static void CLASS_METHOD()(ObjectLinkedList, linkLast, Object* e)
{
    ObjectNode* l = self->_mLast;
    ObjectNode* newNode = NEW(ObjectNode, l, e, NULL);
    self->_mLast = newNode;
    if (l == NULL)
        self->_mFirst = newNode;
    else
        l->next = newNode;
    self->_mSize++;
}

/**
 * Inserts element e before non-null Node succ.
 */
static void CLASS_METHOD()(ObjectLinkedList, linkBefore, Object* e, ObjectNode* succ)
{
    ObjectNode* pred = succ->prev;
    ObjectNode* newNode = NEW(ObjectNode, pred, e, succ);
    succ->prev = newNode;
    if (pred == NULL)
        self->_mFirst = newNode;
    else
        pred->next = newNode;
    self->_mSize++;
}

/**
 * Unlinks non-null first node f.
 */
static Object* CLASS_METHOD()(ObjectLinkedList, unlinkFirst, ObjectNode* f)
{
    Object* element = f->item;
    ObjectNode* next = f->next;
    f->item = NULL;
    f->next = NULL;
    self->_mFirst = next;
    if (next == NULL)
        self->_mLast = NULL;
    else
        next->prev = NULL;
    self->_mSize--;
    return element;
}

/**
 * Unlinks non-null last node l.
 */
static Object* CLASS_METHOD()(ObjectLinkedList, unlinkLast, ObjectNode* l)
{
    Object* element = l->item;
    ObjectNode* prev = l->prev;
    l->item = NULL;
    l->prev = NULL; // help GC
    self->_mLast = prev;
    if (prev == NULL)
        self->_mFirst = NULL;
    else
        prev->next = NULL;
    self->_mSize--;
    return element;
}

/**
 * Unlinks non-null node x.
 */
static Object* CLASS_METHOD()(ObjectLinkedList, unlink, ObjectNode* x)
{
    Object* element = x->item;
    ObjectNode* next = x->next;
    ObjectNode* prev = x->prev;

    if (prev == NULL) {
        self->_mFirst = next;
    } else {
        prev->next = next;
        x->prev = NULL;
    }

    if (next == NULL) {
        self->_mLast = prev;
    } else {
        next->prev = prev;
        x->next = NULL;
    }

    x->item = NULL;
    self->_mSize--;
    return element;
}

/**
 * Returns the first element in this list.
 *
 * @return the first element in this list
 */
static Object* CLASS_METHOD()(ObjectLinkedList, getFirst)
{
    ObjectNode* f = self->_mFirst;
    if (f == NULL)
        return NULL;
    return f->item;
}

/**
 * Returns the last element in this list.
 *
 * @return the last element in this list
 */
static Object* CLASS_METHOD()(ObjectLinkedList, getLast)
{
    ObjectNode* l = self->_mLast;
    if (l == NULL)
        return NULL;
    return l->item;
}

/**
 * Removes and returns the first element from this list.
 *
 * @return the first element from this list
 */
static Object* CLASS_METHOD()(ObjectLinkedList, removeFirst)
{
    ObjectNode* f = self->_mFirst;
    if (f == NULL)
        return NULL;
    return f->item;
}

/**
 * Removes and returns the last element from this list.
 *
 * @return the last element from this list
 */
static Object* CLASS_METHOD()(ObjectLinkedList, removeLast)
{
    ObjectNode* l = self->_mLast;
    if (l == NULL)
        return NULL;
    return l->item;
}

/**
 * Inserts the specified element at the beginning of this list.
 *
 * @param e the element to add
 */
static void CLASS_METHOD()(ObjectLinkedList, addFirst, Object* e)
{
    self(linkFirst, e);
}

/**
 * Appends the specified element to the end of this list.
 *
 * <p>This method is equivalent to {@link #add}.
 *
 * @param e the element to add
 */
static void CLASS_METHOD()(ObjectLinkedList, addLast, Object* e)
{
    self(linkLast, e);
}

/**
 * Returns the index of the first occurrence of the specified element
 * in this list, or -1 if this list does not contain the element.
 * More formally, returns the lowest index {@code i} such that
 * <tt>(o==null&nbsp;?&nbsp;get(i)==null&nbsp;:&nbsp;o.equals(get(i)))</tt>,
 * or -1 if there is no such index.
 *
 * @param o element to search for
 * @return the index of the first occurrence of the specified element in
 *         this list, or -1 if this list does not contain the element
 */
static int CLASS_METHOD()(ObjectLinkedList, indexOf, Object* o)
{
    int index = 0;
    ObjectNode* x;
    if (o == NULL) {
        for (x = self->_mFirst; x != NULL; x = x->next) {
            if (x->item == NULL)
                return index;
            index++;
        }
    } else {
        for (x = self->_mFirst; x != NULL; x = x->next) {
            if (_M(o, equals, x->item))
                return index;
            index++;
        }
    }
    return -1;
}

/**
 * Returns the index of the last occurrence of the specified element
 * in this list, or -1 if this list does not contain the element.
 * More formally, returns the highest index {@code i} such that
 * <tt>(o==null&nbsp;?&nbsp;get(i)==null&nbsp;:&nbsp;o.equals(get(i)))</tt>,
 * or -1 if there is no such index.
 *
 * @param o element to search for
 * @return the index of the last occurrence of the specified element in
 *         this list, or -1 if this list does not contain the element
 */
static int CLASS_METHOD()(ObjectLinkedList, lastIndexOf, Object* o)
{
    int index = self->_mSize;
    ObjectNode* x;
    if (o == NULL) {
        for (x = self->_mLast; x != NULL; x = x->prev) {
            index--;
            if (x->item == NULL)
                return index;
        }
    } else {
        for (x = self->_mLast; x != NULL; x = x->prev) {
            index--;
            if (_M(o, equals, x->item))
                return index;
        }
    }
    return -1;
}

/**
 * Returns the number of elements in this list.
 *
 * @return the number of elements in this list
 */
static int CLASS_METHOD()(ObjectLinkedList, size)
{
    return self->_mSize;
}

/**
 * Returns {@code true} if this list contains the specified element.
 * More formally, returns {@code true} if and only if this list contains
 * at least one element {@code e} such that
 * <tt>(o==null&nbsp;?&nbsp;e==null&nbsp;:&nbsp;o.equals(e))</tt>.
 *
 * @param o element whose presence in this list is to be tested
 * @return {@code true} if this list contains the specified element
 */
static bool CLASS_METHOD()(ObjectLinkedList, contains, Object* o)
{
    return self(indexOf, o) != -1;
}

/**
 * Appends the specified element to the end of this list.
 *
 * <p>This method is equivalent to {@link #addLast}.
 *
 * @param e element to be appended to this list
 * @return {@code true} (as specified by {@link Collection#add})
 */
static bool CLASS_METHOD()(ObjectLinkedList, add, Object* e)
{
    self(linkLast, e);
    return true;
}

/**
 * Removes the first occurrence of the specified element from this list,
 * if it is present.  If this list does not contain the element, it is
 * unchanged.  More formally, removes the element with the lowest index
 * {@code i} such that
 * <tt>(o==null&nbsp;?&nbsp;get(i)==null&nbsp;:&nbsp;o.equals(get(i)))</tt>
 * (if such an element exists).  Returns {@code true} if this list
 * contained the specified element (or equivalently, if this list
 * changed as a result of the call).
 *
 * @param o element to be removed from this list, if present
 * @return {@code true} if this list contained the specified element
 */
static bool CLASS_METHOD()(ObjectLinkedList, removeObject, Object* o)
{
    ObjectNode* x;
    Object* element = NULL;
    if (o == NULL) {
        for (x = self->_mFirst; x != NULL; x = x->next) {
            if (x->item == NULL) {
                element = self(unlink, x);
            }
        }
    } else {
        for (x = self->_mFirst; x != NULL; x = x->next) {
            if (_M(o, equals, x->item)) {
                element = self(unlink, x);
            }
        }
    }
    return element;
}

/**
 * Returns the (non-null) Node at the specified element index.
 */
static ObjectNode* CLASS_METHOD()(ObjectLinkedList, node, int index)
{
    // assert isElementIndex(index);

    if (index < (self->_mSize >> 1)) {
        ObjectNode* x = self->_mFirst;
        for (int i = 0; i < index; i++)
            x = x->next;
        return x;
    } else {
        ObjectNode* x = self->_mLast;
        for (int i = self->_mSize - 1; i > index; i--)
            x = x->prev;
        return x;
    }
}

/**
 * Returns the element at the specified position in this list.
 *
 * @param index index of the element to return
 * @return the element at the specified position in this list
 */
static Object* CLASS_METHOD()(ObjectLinkedList, get, int index)
{
    if (index < 0 || index >= self->_mSize)
        return NULL;
    return self(node, index)->item;
}

/**
 * Replaces the element at the specified position in this list with the
 * specified element.
 *
 * @param index index of the element to replace
 * @param element element to be stored at the specified position
 * @return the element previously at the specified position
 */
static Object* CLASS_METHOD()(ObjectLinkedList, set, int index, Object* element)
{
    if (index < 0 || index >= self->_mSize)
        return NULL;
    ObjectNode* x = self(node, index);
    Object* oldVal = x->item;
    x->item = REFER(element);
    return oldVal;
}

static ObjectListIterator* CLASS_METHOD()(ObjectLinkedList, listIterator, int index)
{
    ObjectLinkedListItr* iterator = NEW(ObjectLinkedListItr, self, index);
    return INTERFACEOF(iterator, ObjectListIterator, ListIterator);
}

static ObjectListIterator* CLASS_METHOD()(ObjectLinkedList, listIterator)
{
    return self(listIterator, 0);
}

/**
 * Removes all of the elements from this list.
 * The list will be empty after this call returns.
 */
static void CLASS_METHOD()(ObjectLinkedList, clear)
{
    ObjectNode* x;
    for (x = self->_mFirst; x != NULL; ) {
        ObjectNode* next = x->next;
        DELETE(x);
        x = next;
    }
    self->_mFirst = self->_mLast = NULL;
    self->_mSize = 0;
}

//BEGIN_CLASS(ObjectLinkedList, Object)
// A trick to inherit AbstractObjectCollection member function
 BEGIN_CLASS(ObjectLinkedList, AbstractObjectList)
// IMPLEMENTS(ObjectLinkedList, ObjectList, List)
    CONSTRUCTOR(map)(ObjectLinkedList)
     DESTRUCTOR(map)(ObjectLinkedList)
   CLASS_METHOD(map)(ObjectLinkedList, linkFirst, Object* e)
   CLASS_METHOD(map)(ObjectLinkedList, linkLast, Object* e)
   CLASS_METHOD(map)(ObjectLinkedList, linkBefore, Object* e, ObjectNode* succ)
   CLASS_METHOD(map)(ObjectLinkedList, unlinkFirst, ObjectNode* f)
   CLASS_METHOD(map)(ObjectLinkedList, unlinkLast, ObjectNode* l)
   CLASS_METHOD(map)(ObjectLinkedList, unlink, ObjectNode* x)
   CLASS_METHOD(map)(ObjectLinkedList, getFirst)
   CLASS_METHOD(map)(ObjectLinkedList, getLast)
   CLASS_METHOD(map)(ObjectLinkedList, removeFirst)
   CLASS_METHOD(map)(ObjectLinkedList, removeLast)
   CLASS_METHOD(map)(ObjectLinkedList, addFirst, Object* e)
   CLASS_METHOD(map)(ObjectLinkedList, addLast, Object* e)
   CLASS_METHOD(map)(ObjectLinkedList, indexOf, Object* o)
   CLASS_METHOD(map)(ObjectLinkedList, lastIndexOf, Object* o)
   CLASS_METHOD(map)(ObjectLinkedList, size)
   CLASS_METHOD(map)(ObjectLinkedList, contains, Object* o)
   CLASS_METHOD(map)(ObjectLinkedList, add, Object* e)
   CLASS_METHOD(map)(ObjectLinkedList, get, int index)
   CLASS_METHOD(map)(ObjectLinkedList, set, int index, Object* element)
   CLASS_METHOD(map)(ObjectLinkedList, removeObject, Object* o)
   CLASS_METHOD(map)(ObjectLinkedList, node, int index)
   CLASS_METHOD(map)(ObjectLinkedList, listIterator)
   CLASS_METHOD(map)(ObjectLinkedList, listIterator, int index)
   CLASS_METHOD(map)(ObjectLinkedList, clear)
END_CLASS
