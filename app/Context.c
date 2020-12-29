//1. The .cc .cpp .cxx related header files
#include "Context.h"
//2. C system include files.
#include <stdio.h>
#include <stdlib.h>
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(Context)
{
    CONSTRUCTOR(super)(Object);

    printf("%s %d -->\n", __func__, __LINE__);
}

static CONSTRUCTOR()(Context)
{
    CONSTRUCTOR(super)(Object);

    printf("%s %d -->\n", __func__, __LINE__);
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(Context)
{
    printf("%s %d -->\n", __func__, __LINE__);
    DESTRUCTOR(super)(Object);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
void CLASS_METHOD()(Context, onCreate)
{
}

void CLASS_METHOD()(Context, onStart)
{
}

void CLASS_METHOD()(Context, onRestart)
{
}

void CLASS_METHOD()(Context, onResume)
{
}

void CLASS_METHOD()(Context, onPause)
{
}

void CLASS_METHOD()(Context, onStop)
{
}

void CLASS_METHOD()(Context, onDestroy)
{
}

BEGIN_CLASS(Context, Object)
 CONSTRUCTOR(map)(Context)
 CONSTRUCTOR(map)(Context, bool isWild, int age)
  DESTRUCTOR(map)(Context)
CLASS_METHOD(map)(Context, eat)
CLASS_METHOD(map)(Context, grow)

END_CLASS
