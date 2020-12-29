//1. The .cc .cpp .cxx related header files
#include "Dog.h"
//2. C system include files.
#include <stdio.h>
#include <stdlib.h>
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.
#include "lang/String.h"
#include "util/Log.h"

#define TAG (String*)"Dog"

static BUILD(global)(msg, String)

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(Dog)
{
    CONSTRUCTOR(super)(Animal);
    _M0(msg, format, "%s %d >>>>>", __func__, __LINE__);
    LOG.d(TAG, msg);
}

static CONSTRUCTOR()(Dog, bool isWild, int age)
{
    CONSTRUCTOR(super)(Animal, isWild, age);

    _M0(msg, format, "%s %d >>>>>", __func__, __LINE__);
    LOG.d(TAG, msg);
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(Dog)
{
    _M0(msg, format, "%s %d >>>>>", __func__, __LINE__);
    LOG.d(TAG, msg);
    DESTRUCTOR(super)(Animal);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
void CLASS_METHOD()(Dog, eat)
{
    CLASS_METHOD(super)(Animal, eat);

    LOG.i(TAG, (String*)"The dog is eating...");
}

BEGIN_CLASS(Dog, Animal)
    CONSTRUCTOR(map)(Dog)
    CONSTRUCTOR(map)(Dog, bool isWild, int age)
     DESTRUCTOR(map)(Dog)
   CLASS_METHOD(map)(Dog, eat)
END_CLASS
