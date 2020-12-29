//1. The .cc .cpp .cxx related header files
#include "ContainerHelpers.h"
//2. C system include files.
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.

/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - - */
/*              \\\\\\\            |  Class ContainerHelpers |            ///////            */
/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - - */

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

static int STATIC_CLASS_METHOD()(ContainerHelpers, binarySearchInt, int array[], int size, int value)
{
    int lo = 0;
    int hi = size - 1;

    while (lo <= hi) {
        int mid = ((unsigned int)(lo + hi)) >> 1;
        int midVal = array[mid];

        if (midVal < value) {
            lo = mid + 1;
        } else if (midVal > value) {
            hi = mid - 1;
        } else {
            return mid;  // value found
        }
    }
    return ~lo;  // value not present
}

static int STATIC_CLASS_METHOD()(ContainerHelpers, binarySearchLong, long array[], int size, long value)
{
    int lo = 0;
    int hi = size - 1;

    while (lo <= hi) {
        int mid = ((unsigned int)(lo + hi)) >> 1;
        long midVal = array[mid];

        if (midVal < value) {
            lo = mid + 1;
        } else if (midVal > value) {
            hi = mid - 1;
        } else {
            return mid;  // value found
        }
    }
    return ~lo;  // value not present
}

BEGIN_CLASS(ContainerHelpers, Object)
STATIC_CLASS_METHOD(map)(ContainerHelpers, binarySearchInt, int array[], int size, int value)
STATIC_CLASS_METHOD(map)(ContainerHelpers, binarySearchLong, long array[], int size, long value)
END_CLASS

