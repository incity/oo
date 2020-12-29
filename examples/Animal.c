//1. The .cc .cpp .cxx related header files
#include "Animal.h"
//2. C system include files.
#include <stdio.h>
#include <stdlib.h>
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.
#include "lang/String.h"
#include "util/Log.h"

static BUILD(global_const)(TAG, String, "Animal")
static BUILD(global)(msg, String)

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(Animal)
{
    CONSTRUCTOR(super)(Object);

    _M0(msg, format, "%s %d >>>>>", __func__, __LINE__);
    LOG.d(TAG, msg);

    self->_mIsWild = 0;
    self->_mAge = 0;
}

static CONSTRUCTOR()(Animal, bool isWild, int age)
{
    CONSTRUCTOR(super)(Object);

    _M0(msg, format, "%s %d >>>>>", __func__, __LINE__);
    LOG.d(TAG, msg);

    self->_mIsWild = isWild;
    self->_mAge = age;

    _M0(msg, format, "%s %d >>>>>", __func__, __LINE__);
    LOG.d(TAG, msg);
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(Animal)
{
    printf("%s %d -->\n", __func__, __LINE__);
    DESTRUCTOR(super)(Object);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
void CLASS_METHOD()(Animal, eat)
{
    LOG.i(TAG, (String*)"Animal is eating...");
}

void CLASS_METHOD()(Animal, grow)
{
    LOG.i(TAG, (String*)"Animal is growing...");
}

// +++++++++++++++++++++++++++
// |   getters and setters   |
// +++++++++++++++++++++++++++
static GET()(Animal, int, _mAge, Age)
static SET()(Animal, int, _mAge, Age)
static GET()(Animal, bool, _mIsWild, IsWild)
static SET()(Animal, bool, _mIsWild, IsWild)

BEGIN_CLASS(Animal, Object)
 CONSTRUCTOR(map)(Animal)
 CONSTRUCTOR(map)(Animal, bool isWild, int age)
  DESTRUCTOR(map)(Animal)
CLASS_METHOD(map)(Animal, eat)
CLASS_METHOD(map)(Animal, grow)
         GET(map)(Animal, int, _mAge, Age)
         SET(map)(Animal, int, _mAge, Age)
         GET(map)(Animal, bool, _mIsWild, IsWild)
         SET(map)(Animal, bool, _mIsWild, IsWild)
END_CLASS
