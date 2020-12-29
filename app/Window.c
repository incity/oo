//1. The .cc .cpp .cxx related header files
#include "Window.h"
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
static CONSTRUCTOR()(Window)
{
    CONSTRUCTOR(super)(Object);

    printf("%s %d -->\n", __func__, __LINE__);

}

static CONSTRUCTOR()(Window)
{
    CONSTRUCTOR(super)(Object);

    printf("%s %d -->\n", __func__, __LINE__);
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(Window)
{
    printf("%s %d -->\n", __func__, __LINE__);
    DESTRUCTOR(super)(Object);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
void CLASS_METHOD()(Window, onCreate)
{
}

void CLASS_METHOD()(Window, onStart)
{
}

void CLASS_METHOD()(Window, onRestart)
{
}

void CLASS_METHOD()(Window, onResume)
{
}

void CLASS_METHOD()(Window, onPause)
{
}

void CLASS_METHOD()(Window, onStop)
{
}

void CLASS_METHOD()(Window, onDestroy)
{
}

BEGIN_CLASS(Window, Object)
 CONSTRUCTOR(map)(Window)
  DESTRUCTOR(map)(Window)

END_CLASS
