#ifndef _OO_DOG_H_
#define _OO_DOG_H_

#include "Animal.h"

#define public_class_DogClass(T, SuperClss)     \
         extends_class(Animal)(T, SuperClss)

#define public_class_Dog(T)                     \
         extends(Animal)(T)

DECLARE_CLASS(public)(Dog, Animal)

#endif /* _OO_DOG_H_ */
