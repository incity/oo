#ifndef _OO_INTERFACE_H_
#define _OO_INTERFACE_H_

#include "Class.h"

#define public_interface_Ibject(IF, T)  \
	size_t _##IF##_obj_offset;          \
	size_t _##IF##_next_offset;

typedef struct _IbjectVTable IbjectVTable;
typedef struct _Ibject Ibject;

struct _IbjectVTable{
    unsigned short _obj_offset;
    unsigned short _next_offset;
};

struct _Ibject {
    IbjectVTable* _vtable;
};

#endif /* _OO_INTERFACE_H_ */
