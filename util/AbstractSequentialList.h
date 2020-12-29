#ifndef _OO_ABSTRACT_SEQUENTIAL_LIST_H_
#define _OO_ABSTRACT_SEQUENTIAL_LIST_H_

#include "AbstractList.h"

#define public_class_AbstractSequentialListClass(Clss, SuperClss)   \
            extends_class(AbstractList)(Clss, SuperClss)            \
           
#define public_class_AbstractSequentialList(Clss)   \
            extends(AbstractList)(Clss)

DECLARE_CLASS(AbstractSequentialList, AbstractList)

#endif /* _OO_ABSTRACT_SEQUENTIAL_LIST_H_ */
