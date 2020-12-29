#ifndef _OO_LINKED_LIST_H_
#define _OO_LINKED_LIST_H_

#include "List.h"

/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */
/*              \\\\\\\            |     Class ObjectNode    |           ///////           */
/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */

#define private_class_ObjectNodeClass(T, SuperClss)                                              \
                extends_class(Object)(T, SuperClss)                                              \
                  CONSTRUCTOR(public)(T, ObjectNode* prev, Object* element, ObjectNode* next);

#define private_class_ObjectNode(T)    \
                 extends(Object)(T)    \
                 Object* item;         \
             ObjectNode* next;         \
             ObjectNode* prev;

DECLARE_CLASS(private)(ObjectNode, Object)

/* - - - - - - - - - - - - - - - +---------------------------+ - - - - - - - - - - - - - - */
/*              \\\\\\\          | Class ObjectLinkedListItr |           ///////           */
/* - - - - - - - - - - - - - - - +---------------------------+ - - - - - - - - - - - - - - */
DECLARE_CLASS(forward)(ObjectLinkedList, Object)

#define   private_class_ObjectLinkedListItrClass(T, SuperClss)     \
                     extends_class(Object)(T, SuperClss)           \
implements_generic_interface(ListIterator, T, Object*)             \
                       CONSTRUCTOR(public)(T, ObjectLinkedList* list, int index); \

#define private_class_ObjectLinkedListItr(T)   \
           extends(Object)(T)                  \
        implements(ObjectListIterator)         \
   ObjectLinkedList* list;                     \
         ObjectNode* lastReturned;             \
         ObjectNode* next;                     \
                 int nextIndex;

DECLARE_CLASS(private)(ObjectLinkedListItr, Object)

/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */
/*              \\\\\\\            |  Class ObjectLinkedList |           ///////           */
/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */

#define public_class_ObjectLinkedListClass(T, SuperClss)                                  \
                     extends_class(Object)(T, SuperClss)                                  \
        implements_generic_interface(List, T, Object*, ObjectListIterator*)               \
                 void CLASS_METHOD(public)(T, linkFirst, Object* e);                      \
                 void CLASS_METHOD(public)(T, linkLast, Object* e);                       \
                 void CLASS_METHOD(public)(T, linkBefore, Object* e, ObjectNode* succ);   \
              Object* CLASS_METHOD(public)(T, unlink, ObjectNode* x);          \
              Object* CLASS_METHOD(public)(T, getFirst);                       \
              Object* CLASS_METHOD(public)(T, getLast);                        \
              Object* CLASS_METHOD(public)(T, removeFirst);                    \
              Object* CLASS_METHOD(public)(T, removeLast);                     \
                 void CLASS_METHOD(public)(T, addFirst, Object* x);            \
                 void CLASS_METHOD(public)(T, addLast, Object* x);             \
              Object* CLASS_METHOD(public)(T, push, Object* e);                \
              Object* CLASS_METHOD(public)(T, pop);                            \
          ObjectNode* CLASS_METHOD(public)(T, node, int index);                \
              Object* CLASS_METHOD(private)(T, unlinkFirst, ObjectNode* f);    \
              Object* CLASS_METHOD(private)(T, unlinkLast, ObjectNode* l);     \

#define public_class_ObjectLinkedList(T)     \
                      extends(Object)(T)     \
                   implements(ObjectList)    \
                      int _mSize;            \
                      ObjectNode* _mLast;    \
                      ObjectNode* _mFirst;

DECLARE_CLASS(public)(ObjectLinkedList, Object)


#endif /* _OO_LINKED_LIST_H_ */
