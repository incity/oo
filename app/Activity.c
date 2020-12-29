//1. The .cc .cpp .cxx related header files
#include "Activity.h"
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
static CONSTRUCTOR()(Activity)
{
    CONSTRUCTOR(super)(Object);

    printf("%s %d -->\n", __func__, __LINE__);
}

static CONSTRUCTOR()(Activity)
{
    CONSTRUCTOR(super)(Object);

    printf("%s %d -->\n", __func__, __LINE__);
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(Activity)
{
    printf("%s %d -->\n", __func__, __LINE__);
    DESTRUCTOR(super)(Object);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
void CLASS_METHOD()(Activity, onCreate)
{
}

void CLASS_METHOD()(Activity, onStart)
{
}

void CLASS_METHOD()(Activity, onRestart)
{
}

void CLASS_METHOD()(Activity, onResume)
{
}

void CLASS_METHOD()(Activity, onPause)
{
}

void CLASS_METHOD()(Activity, onStop)
{
}

void CLASS_METHOD()(Activity, onDestroy)
{
}

BEGIN_CLASS(Activity, Object)
 CONSTRUCTOR(map)(Activity)
  DESTRUCTOR(map)(Activity)
END_CLASS
