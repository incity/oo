//1. The .cc .cpp .cxx related header files
#include "lang/Number.h"
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

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++

/**
 * Returns the value of the specified number as a <code>byte</code>.
 * This may involve rounding or truncation.
 *
 * @return  the numeric value represented by this object after conversion
 *          to type <code>byte</code>.
 */
static byte CLASS_METHOD()(Number, byteValue)
{
    return (byte)self(intValue);
}

/**
 * Returns the value of the specified number as a <code>short</code>.
 * This may involve rounding or truncation.
 *
 * @return  the numeric value represented by this object after conversion
 *          to type <code>short</code>.
 */
static short CLASS_METHOD()(Number, shortValue)
{
    return (short)self(intValue);
}

BEGIN_CLASS(Number, Object)
  CLASS_METHOD(map)(Number, byteValue)
  CLASS_METHOD(map)(Number, shortValue)
END_CLASS

