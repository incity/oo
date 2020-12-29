//1. The .cc .cpp .cxx related header files
#include "InputStream.h"
//2. C system include files.
#include <stdio.h>
#include <stdlib.h>
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.
#include "lang/math.h"

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
static int CLASS_METHOD()(InputStream, read, byte* b, int len)
{
    return self(read, b, 0, len);
}

static int CLASS_METHOD()(InputStream, read, byte* b, int off, int len)
{
    int c = self(read);
    if (c == -1)
        return -1;

    b[off] = (byte)c;

    int i = 1;
    for (; i < len ; i++) {
        c = self(read);
        if (c == -1) {
            break;
        }
        b[off + i] = (byte)c;
    }

    return i;
}

/**
 * Skips over and discards <code>n</code> bytes of data from this input
 * stream. The <code>skip</code> method may, for a variety of reasons, end
 * up skipping over some smaller number of bytes, possibly <code>0</code>.
 * This may result from any of a number of conditions; reaching end of file
 * before <code>n</code> bytes have been skipped is only one possibility.
 * The actual number of bytes skipped is returned.  If <code>n</code> is
 * negative, no bytes are skipped.
 *
 * <p> The <code>skip</code> method of this class creates a
 * byte array and then repeatedly reads into it until <code>n</code> bytes
 * have been read or the end of the stream has been reached. Subclasses are
 * encouraged to provide a more efficient implementation of this method.
 * For instance, the implementation may depend on the ability to seek.
 *
 * @param      n   the number of bytes to be skipped.
 * @return     the actual number of bytes skipped.
 */
static int CLASS_METHOD()(InputStream, skip, long n)
{
    long remaining = n;
    int nr;

    if (n <= 0) {
        return 0;
    }

    int size = (int)min(MAX_SKIP_BUFFER_SIZE, (int)remaining);
    byte* skipBuffer = (byte*)malloc(size);
    while (remaining > 0) {
        nr = self(read, skipBuffer, 0, (int)min(size, (int)remaining));
        if (nr < 0) {
            break;
        }
        remaining -= nr;
    }

    return n - remaining;
}

static int CLASS_METHOD()(InputStream, available)
{
    return 0;
}

static void CLASS_METHOD()(InputStream, close)
{
}

static void CLASS_METHOD()(InputStream, mark, int readlimit)
{
}

static void CLASS_METHOD()(InputStream, reset)
{
}

static bool CLASS_METHOD()(InputStream, markSupported)
{
    return false;
}

BEGIN_CLASS(InputStream, Object)
 IMPLEMENTS(InputStream, Closeable)
CLASS_METHOD(map)(InputStream, read, void* b, int len)
CLASS_METHOD(map)(InputStream, read, void* b, int off, int len)
CLASS_METHOD(map)(InputStream, skip, long n)
CLASS_METHOD(map)(InputStream, available)
CLASS_METHOD(map)(InputStream, close)
CLASS_METHOD(map)(InputStream, mark, int readlimit)
CLASS_METHOD(map)(InputStream, reset)
END_CLASS
