//1. The .cc .cpp .cxx related header files
#include "PrimeRun.h"
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
static CONSTRUCTOR()(PrimeRun)
{
    CONSTRUCTOR(super)(Object);
    self->_mHelloWorld = "Hello, World!";
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(PrimeRun)
{
    DESTRUCTOR(super)(Object);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
static void CLASS_METHOD()(PrimeRun, run)
{
    //while(1) {
        //printf("%s %d ---->\n", __func__, __LINE__);
        //printf("%s\n", self->_mHelloWorld);
        //sleep(1);
    //}
}

BEGIN_CLASS(PrimeRun, Object)
       IMPLEMENTS(PrimeRun, Runnable)
 CONSTRUCTOR(map)(PrimeRun)
  DESTRUCTOR(map)(PrimeRun)
CLASS_METHOD(map)(PrimeRun, run)
END_CLASS

