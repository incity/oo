#ifndef _OO_CLASS_H_
#define _OO_CLASS_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <alloca.h>
#include "types.h"
#include "metamacros.h"

/* Runtime class */
#define Class(Clss) \
        g_st##Clss##Class

/* Runtime class type */
#define ClassType(Clss) \
        Clss##Class

/* Extends another runtime class */
#define extends_class(Clss, ...) \
        extends_class_(Clss, ##__VA_ARGS__)

/* Extends another class */
#define extends(Clss, ...) \
        extends_(Clss, ##__VA_ARGS__)

/* An object can implements one or more interface. */
#define implements(Interface) \
        Interface##VTable * _##Interface;

#define IMPLEMENTS(Clss, Interface, GenericInterface...) \
        IMPLEMENTS_(Clss, Interface, metamacro_argcount(GenericInterface), GenericInterface)

/* Cast an Object to an implemented Interface. */
#define INTERFACEOF(obj, Interface, GenericInterface...) \
        INTERFACEOF_(obj, Interface, metamacro_argcount(GenericInterface), GenericInterface)

/* Adjust the interface to the object */
#define OBJECTOF(ibj, Clss...) OBJECTOF_(ibj, metamacro_argcount(Clss), Clss)

/**
 * Declare a new class with a super class
 * and a optional qualifier:
 *   1. public       -> default
 *   2. public_final
 * for example:
 *   DECLARE_CLASS(public)(Animal, Object)
 *   DECLARE_CLASS(public_final)(String, Object)
 */
#define DECLARE_CLASS(qualifier) DECLARE_CLASS_##qualifier

#define DECLARE_INTERFACE(qualifier) DECLARE_INTERFACE_##qualifier

/**
 * CLASS_METHOD macro selector
 *
 * 1. CLASS_METHOD(m)(Class, MemberFunction, args...)
 *    get member function name.
 *    e.g. CLASS_METHOD(m)(SomeClass, doSomething, int arg1, char* arg2) --> SomeClass_doSomething_v2
 *
 * 2. CLASS_METHOD(map)(Class, MemberFunction, args...)
 *    used to map member function into class
 *
 * 3. CLASS_METHOD(public/protected/private)(Class, MemberFunction, args...)
 *    used to declare a public/protected/private member function
 *    e.g. void CLASS_METHOD(public)(SomeClass, doSomething, int arg1, char* arg2)
 *         --> void (*doSomething_v2)(SomeClass* self, int arg1, char* arg2)
 *
 * 4. CLASS_METHOD()(Class, MemberFunction, args...)
 *    used to define member function
 *    for example:
 *    void CLASS_METHOD()(SomeClass, doSomething, int arg1, char* arg2)
 *    {
 *        // member function body
 *    }
 *    same as-->
 *    void SomeClass_doSomething_v2(SomeClass* self, int arg1, char* arg2)
 *    {
 *        // member function body
 *    }
 *
 * 5. CLASS_METHOD(super)(Class, MemberFunction, args...)
 *    used to call super class's member function
 *
 * 6. For all of the above use cases, functions are all overloaded.
 *    insert a (0) after CLASS_METHOD can disable it.
 *    for example:
 *    void CLASS_METHOD(0)()(String, format, const char* format, ...)
 *                     ^^^
 *                  insert here
 *    {
 *        // member function body
 *    }
 *
 */
#define        CLASS_METHOD(selector) metamacro_concat(CLASS_METHOD_, selector)
#define STATIC_CLASS_METHOD(selector) metamacro_concat(STATIC_CLASS_METHOD_, selector)
#define         CONSTRUCTOR(selector) metamacro_concat(CONSTRUCTOR_, selector)
#define   CONST_CONSTRUCTOR(selector) metamacro_concat(CONST_CONSTRUCTOR_, selector)
#define          DESTRUCTOR(selector) metamacro_concat(DESTRUCTOR_, selector)
#define                 GET(selector) metamacro_concat(GET_, selector)
#define                 SET(selector) metamacro_concat(SET_, selector)

/**
 * classOf(obj)
 *
 * Returns the runtime class of this Object.
 * runtime class: the Class object that represents the class of the object.
 *
 */
#define _c(obj)                (obj)->class
#define _SM(Clss, method, ...) Class(Clss).CLASS_METHOD(m)(ClassNoUse, method, ##__VA_ARGS__)(__VA_ARGS__)
#define _M(obj, method, ...)   _c(obj)->CLASS_METHOD(m)(ClassNoUseNow, method, ##__VA_ARGS__)(obj, ##__VA_ARGS__)
#define _M0(obj, method, ...)  _c(obj)->method(obj, __VA_ARGS__)
#define _IM(iobj, method, ...) (iobj)->_vtable->CLASS_METHOD(m)(ClassNoUseNow, method, ##__VA_ARGS__)(OBJECTOF(iobj), ##__VA_ARGS__)
#define self(method, ...)      _c(self)->CLASS_METHOD(m)(ClassNoUseNow, method, ##__VA_ARGS__)(self, ##__VA_ARGS__)

//------------------------------------------------------------------
// IMPLEMENTATION DETAILS FOLLOW!
// Do not write code that depends on anything below this line.
#ifdef  WIN32
#define TYPEOF(x)  void* //__typeof(x)
#else
#define TYPEOF(x)  typeof(x)
#endif

/* An interface can extends another interface. */
#define extends_interface(Interface)            public_interface_##Interface
#define extends_generic_interface(Interface)    public_generic_interface_##Interface

/* Runtime class can implements one or more interfaces. */
#define implements_interface(Interface, ClassImpl) public_interface_##Interface(Interface, ClassImpl)
#define implements_generic_interface(Interface, ClassImpl, ...) public_generic_interface_##Interface(Interface, ClassImpl, ##__VA_ARGS__)

#define INTERFACEOF_(obj, Interface, argc, GenericInterface...)                 \
        metamacro_if_eq(0, argc)(((Interface*)((char*)(obj) + (_c(obj)->_##Interface##_obj_offset))))(((Interface*)((char*)(obj) + (_c(obj)->_##GenericInterface##_obj_offset))))

#define OBJECTOF_(ibj, argc, Clss...)                                                    \
        metamacro_if_eq(0, argc)((void*))((Clss*))((char*)(ibj) - ((IbjectVTable*)(ibj)->_vtable)->_obj_offset)

#define IMPLEMENTS_interface(Clss, Interface)                                      \
            _class->_##Interface##_obj_offset = (size_t)&(((Clss*)0)->_##Interface);       \
            _class->_##Interface##_next_offset = 0;                                        \
            *_pintfOffset = (size_t)&(((ClassType(Clss)*)0)->_##Interface##_obj_offset);   \
            _pintfOffset = &_class->_##Interface##_next_offset;

#define IMPLEMENTS_generic_interface(Clss, Interface, GenericInterface)                   \
            _class->_##GenericInterface##_obj_offset = (size_t)&(((Clss*)0)->_##Interface);       \
            _class->_##GenericInterface##_next_offset = 0;                                        \
            *_pintfOffset = (size_t)&(((ClassType(Clss)*)0)->_##GenericInterface##_obj_offset);   \
            _pintfOffset = &_class->_##GenericInterface##_next_offset;

#define IMPLEMENTS__(Clss, Interface, argc, ...) metamacro_if_eq(0, argc)(IMPLEMENTS_interface(Clss, Interface))(IMPLEMENTS_generic_interface(Clss, Interface, __VA_ARGS__))
#define IMPLEMENTS_(Clss, Interface, argc, ...) IMPLEMENTS__(Clss, Interface, argc, ##__VA_ARGS__)

#define DECLARE_CLASS_public_final(Clss, SuperClss, ...)                    \
        DECLARE_CLASS__(Clss, SuperClss, public_final_, ##__VA_ARGS__)

#define DECLARE_CLASS_public_generic(Clss, SuperClss, ...)                  \
        DECLARE_CLASS__(Clss, SuperClss, public_generic_, ##__VA_ARGS__)

#define DECLARE_CLASS_public_abstract(Clss, SuperClss, ...)                 \
        DECLARE_CLASS__(Clss, SuperClss, public_abstract_, ##__VA_ARGS__)

#define DECLARE_CLASS_public(Clss, SuperClss, ...)                          \
        DECLARE_CLASS__(Clss, SuperClss, public_, ##__VA_ARGS__)

#define DECLARE_CLASS_protected(Clss, SuperClss, ...)                       \
        DECLARE_CLASS__(Clss, SuperClss, protected_, ##__VA_ARGS__)

#define DECLARE_CLASS_private(Clss, SuperClss, ...)                         \
        DECLARE_CLASS__(Clss, SuperClss, private_, ##__VA_ARGS__)

#define DECLARE_CLASS_forward(Clss, ...)                                    \
        typedef struct oo_##Clss##Class Clss##Class;                        \
        typedef struct oo_##Clss Clss;

#define DECLARE_CLASS_(Clss, SuperClss, ...)                                \
        DECLARE_CLASS__(Clss, SuperClss, public_, ##__VA_ARGS__)

#define DECLARE_CLASS__(Clss, SuperClss, qualifier, ...)                    \
    	typedef struct oo_##Clss##Class Clss##Class;                        \
    	typedef struct oo_##Clss Clss;                                      \
    	struct oo_##Clss##Class {                                           \
    		qualifier##class_##Clss##Class(Clss, SuperClss, ##__VA_ARGS__)  \
    	};                                                                  \
    	struct oo_##Clss {                                                  \
    		qualifier##class_##Clss(Clss)                                   \
    	};                                                                  \
    	extern Clss##Class g_st##Clss##Class;

#define DECLARE_INTERFACE_public(Interface, ...)                                   \
        DECLARE_INTERFACE__(Interface, Interface, public_, ##__VA_ARGS__)

#define DECLARE_INTERFACE_public_generic(Interface, Template, ...)                 \
        DECLARE_INTERFACE__(Interface, Template, public_generic_, ##__VA_ARGS__)

#define DECLARE_INTERFACE_(Interface, ...)                                         \
        DECLARE_INTERFACE__(Interface, Interface, public_, ##__VA_ARGS__)

#define DECLARE_INTERFACE__(Interface, Template, qualifier, ...)                   \
    	typedef struct oo_##Interface##VTable Interface##VTable;                   \
    	typedef struct oo_##Interface Interface;                                   \
        struct oo_##Interface##VTable {                                            \
            qualifier##interface_##Template(Interface, Interface, ##__VA_ARGS__)   \
        };                                                                         \
        struct oo_##Interface { Interface##VTable *_vtable; };

#define extends_class__public_abstract(Clss, ...) public_abstract_class_##Clss##Class
#define extends_class__abstract(Clss, ...)        public_abstract_class_##Clss##Class
#define extends_class__public(Clss, ...)          public_class_##Clss##Class
#define extends_class__private(Clss, ...)         private_class_##Clss##Class
#define extends_class__(Clss, ...)                public_class_##Clss##Class
#define extends_class_(Clss, ...)                 extends_class__##__VA_ARGS__(Clss, ##__VA_ARGS__)

#define extends__public_abstract(Clss, ...)       public_abstract_class_##Clss
#define extends__abstract(Clss, ...)              public_abstract_class_##Clss
#define extends__public(Clss, ...)                public_class_##Clss
#define extends__private(Clss, ...)               private_class_##Clss
#define extends__(Clss, ...)                      public_class_##Clss
#define extends_(Clss, ...)                       extends__##__VA_ARGS__(Clss, ##__VA_ARGS__)

/**
 * used to call super class's member function
 */
#define CLASS_METHOD_super__(method, argc, ...) metamacro_if_eq(0, argc)(method(__VA_ARGS__))(method##_v##argc(__VA_ARGS__))
#define CLASS_METHOD_super_(method, argc, ...) CLASS_METHOD_super__(method, argc, ##__VA_ARGS__)
#define CLASS_METHOD_super(Clss, method, ...) CLASS_METHOD_super_(Class(Clss).method, metamacro_argcount(__VA_ARGS__), (Clss*)self, ##__VA_ARGS__)

/**
 * used to get member function name
 */
#define CLASS_METHOD_m__(method, argc, ...) metamacro_if_eq(0, argc)(method)(method##_v##argc)
#define CLASS_METHOD_m_(method, argc, ...) CLASS_METHOD_m__(method, argc, ##__VA_ARGS__)
#define CLASS_METHOD_m(Clss, method, ...) CLASS_METHOD_m_(method, metamacro_argcount(__VA_ARGS__), Clss* self, ##__VA_ARGS__)

/**
 * used to get static function name
 */
#define static_CLASS_METHOD_m__(method, argc, ...) metamacro_if_eq(0, argc)(method)(method##_v##argc)
#define static_CLASS_METHOD_m_(method, argc, ...) static_CLASS_METHOD_m__(method, argc, ##__VA_ARGS__)
#define static_CLASS_METHOD_m(method, ...) static_CLASS_METHOD_m_(method, metamacro_argcount(__VA_ARGS__), ##__VA_ARGS__)

/**
 * used to map member function
 */
#define CLASS_METHOD_map__(Clss, method, ...) _class->method = (TYPEOF(_class->method))(Clss##_##method);
#define CLASS_METHOD_map_(Clss, method, ...) CLASS_METHOD_map__(Clss, method, ##__VA_ARGS__)
#define CLASS_METHOD_map(Clss, method, ...) CLASS_METHOD_map_(Clss, CLASS_METHOD_m(Clss, method, ##__VA_ARGS__))

/**
 * used to map static class function
 */
#define static_CLASS_METHOD_map__(Clss, method, ...) _class->method = (TYPEOF(_class->method))(Clss##_##method);
#define static_CLASS_METHOD_map_(Clss, method, ...) static_CLASS_METHOD_map__(Clss, method, ##__VA_ARGS__)
#define static_CLASS_METHOD_map(Clss, method, ...) static_CLASS_METHOD_map_(Clss, static_CLASS_METHOD_m(method, ##__VA_ARGS__))

/**
 * used to declare public/protected/private member function
 */
#define CLASS_METHOD_public_static__(method, argc, ...) metamacro_if_eq(0, argc)((*method)(__VA_ARGS__))((*method##_v##argc)(__VA_ARGS__))
#define CLASS_METHOD_public_static_(method, argc, ...) CLASS_METHOD_public_static__(method, argc, ##__VA_ARGS__)
#define CLASS_METHOD_public_static(method, ...) CLASS_METHOD_public_static_(method, metamacro_argcount(__VA_ARGS__), ##__VA_ARGS__)

#define CLASS_METHOD_public__(method, argc, ...) metamacro_if_eq(0, argc)((*method)(__VA_ARGS__))((*method##_v##argc)(__VA_ARGS__))
#define CLASS_METHOD_public_(method, argc, ...) CLASS_METHOD_public__(method, argc, ##__VA_ARGS__)
#define CLASS_METHOD_public_final(Clss, method, ...) CLASS_METHOD_public_(method, metamacro_argcount(__VA_ARGS__), Clss* self, ##__VA_ARGS__)
#define CLASS_METHOD_public_abstract(Clss, method, ...) CLASS_METHOD_public_(method, metamacro_argcount(__VA_ARGS__), Clss* self, ##__VA_ARGS__)
#define CLASS_METHOD_public(Clss, method, ...) CLASS_METHOD_public_(method, metamacro_argcount(__VA_ARGS__), Clss* self, ##__VA_ARGS__)

#define CLASS_METHOD_protected__(method, argc, ...) metamacro_if_eq(0, argc)((*method)(__VA_ARGS__))((*method##_v##argc)(__VA_ARGS__))
#define CLASS_METHOD_protected_(method, argc, ...) CLASS_METHOD_protected__(method, argc, ##__VA_ARGS__)
#define CLASS_METHOD_protected(Clss, method, ...) CLASS_METHOD_protected_(method, metamacro_argcount(__VA_ARGS__), Clss* self, ##__VA_ARGS__)
#define CLASS_METHOD_final(Clss, method, ...) CLASS_METHOD_protected_(method, metamacro_argcount(__VA_ARGS__), Clss* self, ##__VA_ARGS__)

#define CLASS_METHOD_private__(method, argc, ...) metamacro_if_eq(0, argc)((*method)(__VA_ARGS__))((*method##_v##argc)(__VA_ARGS__))
#define CLASS_METHOD_private_(method, argc, ...) CLASS_METHOD_private__(method, argc, ##__VA_ARGS__)
#define CLASS_METHOD_private(Clss, method, ...) CLASS_METHOD_private_(method, metamacro_argcount(__VA_ARGS__), Clss* self, ##__VA_ARGS__)

#define CLASS_METHOD_0(selector) CLASS_METHOD_0_##selector
#define CLASS_METHOD_0_(Clss, method, ...) CLASS_METHOD__(Clss, method, 0, Clss* self, ##__VA_ARGS__)
#define CLASS_METHOD_0_public_static(method, ...) CLASS_METHOD_public_static_(method, 0, ##__VA_ARGS__)
#define CLASS_METHOD_0_public(Clss, method, ...) CLASS_METHOD_public_(method, 0, Clss* self, ##__VA_ARGS__)
#define CLASS_METHOD_0_protected(Clss, method, ...) CLASS_METHOD_protected_(method, 0, Clss* self, ##__VA_ARGS__)
#define CLASS_METHOD_0_private(Clss, method, ...) CLASS_METHOD_private_(method, 0, Clss* self, ##__VA_ARGS__)
#define CLASS_METHOD_0_map(Clss, method, ...) CLASS_METHOD_map_(Clss, method, ##__VA_ARGS__)

#define static_CLASS_METHOD__(Clss, method, argc, ...) metamacro_if_eq(0, argc)(Clss##_##method(__VA_ARGS__))(Clss##_##method##_v##argc(__VA_ARGS__))
#define static_CLASS_METHOD_(Clss, method, argc, ...) static_CLASS_METHOD__(Clss, method, argc, ##__VA_ARGS__)
#define static_CLASS_METHOD(Clss, method, ...) static_CLASS_METHOD_(Clss, method, metamacro_argcount(__VA_ARGS__), ##__VA_ARGS__)

//#define static_CLASS_METHOD_0(selector) static_CLASS_METHOD_0_##selector
#define static_CLASS_METHOD_0_(Clss, method, ...) static_CLASS_METHOD__(Clss, method, 0, ##__VA_ARGS__)
#define static_CLASS_METHOD_0_map(Clss, method, ...) static_CLASS_METHOD_map_(Clss, method, ##__VA_ARGS__)

#define STATIC_CLASS_METHOD_(method, ...) static_CLASS_METHOD(method, ##__VA_ARGS__)
#define STATIC_CLASS_METHOD_0(selector) static_CLASS_METHOD_0_##selector
#define STATIC_CLASS_METHOD_map(Clss, method, ...) static_CLASS_METHOD_map(Clss, method, ##__VA_ARGS__)

/**
 * used to define member function
 */
#define CLASS_METHOD___(Clss, method, argc, ...) metamacro_if_eq(0, argc)(Clss##_##method(__VA_ARGS__))(Clss##_##method##_v##argc(__VA_ARGS__))
#define CLASS_METHOD__(Clss, method, argc, ...) CLASS_METHOD___(Clss, method, argc, ##__VA_ARGS__)
#define CLASS_METHOD_(Clss, method, ...) CLASS_METHOD__(Clss, method, metamacro_argcount(__VA_ARGS__), Clss* self, ##__VA_ARGS__)

#define CONSTRUCTOR_super(Clss, ...) CLASS_METHOD_super(Clss, construct, ##__VA_ARGS__)
#define CONSTRUCTOR_map(Clss, ...) CLASS_METHOD_map(Clss, construct, ##__VA_ARGS__)
#define CONSTRUCTOR_m(Clss, ...) CLASS_METHOD_m(Clss, construct, ##__VA_ARGS__)
#define CONSTRUCTOR_public(Clss, ...) void CLASS_METHOD_public(Clss, construct, ##__VA_ARGS__)
#define CONSTRUCTOR_(Clss, ...) void CLASS_METHOD_(Clss, construct, ##__VA_ARGS__)

#define CONST_CONSTRUCTOR_super(Clss, ...) CLASS_METHOD_super(Clss, construct_const, ##__VA_ARGS__)
#define CONST_CONSTRUCTOR_map(Clss, ...) CLASS_METHOD_map(Clss, construct_const, ##__VA_ARGS__)
#define CONST_CONSTRUCTOR_m(Clss, ...) CLASS_METHOD_m(Clss, construct_const, ##__VA_ARGS__)
#define CONST_CONSTRUCTOR_public(Clss, ...) void CLASS_METHOD_public(Clss, construct_const, ##__VA_ARGS__)
#define CONST_CONSTRUCTOR_(Clss, ...) void CLASS_METHOD_(Clss, construct_const, ##__VA_ARGS__)

#define DESTRUCTOR_super(Clss, ...) CLASS_METHOD_super(Clss, destroy, ##__VA_ARGS__)
#define DESTRUCTOR_map(Clss, ...) CLASS_METHOD_map(Clss, destroy, ##__VA_ARGS__)
#define DESTRUCTOR_m(Clss, ...) CLASS_METHOD_m(Clss, destroy, ##__VA_ARGS__)
#define DESTRUCTOR_public(Clss, ...) void CLASS_METHOD_public(Clss, destroy, ##__VA_ARGS__)
#define DESTRUCTOR_(Clss, ...) void CLASS_METHOD_(Clss, destroy, ##__VA_ARGS__)

/**
 * getters' helper macro
 */
#define GET_map(Clss, Type, MemberName, FaceName)      \
        CLASS_METHOD_map(Clss, get##FaceName)
#define GET_public(Clss, Type, MemberName, FaceName)   \
        Type CLASS_METHOD_public(Clss, get##FaceName)
#define GET_public_static(Type, MemberName, FaceName)  \
        Type CLASS_METHOD_public_static(get##FaceName)
#define GET_(Clss, Type, MemberName, FaceName)         \
        Type CLASS_METHOD_(Clss, get##FaceName)        \
        {                                              \
            return self->MemberName;                   \
        }

/**
 * setters' helper macro
 */
#define SET_map(Clss, Type, MemberName, FaceName)                  \
        CLASS_METHOD_map(Clss, set##FaceName, Type value)
#define SET_public(Clss, Type, MemberName, FaceName)               \
        void CLASS_METHOD_public(Clss, set##FaceName, Type value)
#define SET_public_static(Type, MemberName, FaceName)              \
        void CLASS_METHOD_public_static(set##FaceName, Type value)

#define SET_(Clss, Type, MemberName, FaceName)                     \
        void CLASS_METHOD_(Clss, set##FaceName, Type value)        \
        {                                                          \
            self->MemberName = value;                              \
        }

#endif /* _OO_CLASS_H_ */
