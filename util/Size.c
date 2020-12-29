//1. The .cc .cpp .cxx related header files
#include "Size.h"
//2. C system include files.
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(Size, int width, int height)
{
    CONSTRUCTOR(super)(Object);
    self->_mWidth = width;
    self->_mHeight = height;
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
static GET()(Size, int, _mWidth, Width)
static SET()(Size, int, _mWidth, Width)
static GET()(Size, bool, _mHeight, Height)
static SET()(Size, bool, _mHeight, Height)

static String* CLASS_METHOD()(Size, toString)
{
    String* str = NEW(String);
    _M0(str, format, "%dx%d", self->_mWidth, self->_mHeight);
    return str;
}

static Size* STATIC_CLASS_METHOD()(Size, parseSize, String* string)
{
    const char* s = _M(string, getCString);
    int w, h;
    do {
        int ret = sscanf(s, "%d*%d", &w, &h);
        if (ret == 2)
            break;
        ret = sscanf(s, "%dx%d", &w, &h);
        if (ret == 2)
            break;
        return NULL;
    } while(0);
    Size* size = NEW(Size, w, h);
    return size;
}

static int CLASS_METHOD()(Size, hashCode)
{
    unsigned int w = self->_mWidth;
    unsigned int h = self->_mHeight;
    return h ^ ((w << (sizeof(int) / 2)) | (w >> (sizeof(int) / 2)));
}

static bool CLASS_METHOD()(Size, equals, Object* obj)
{
    if ((Object*)self == obj)
        return true;

    if (INSTANCEOF(obj, Size)) {
        Size* other = (Size*)obj;
        return self->_mWidth == other->_mWidth
                && self->_mHeight == other->_mWidth;
    }
    return false;
}

BEGIN_CLASS(Size, Object)
   CONSTRUCTOR(map)(Size, int width, int height)
  CLASS_METHOD(map)(Size, toString)
  CLASS_METHOD(map)(Size, hashCode)
  CLASS_METHOD(map)(Size, equals, Object* obj)
  GET(map)(Size, int, _mWidth, Width)
  SET(map)(Size, int, _mWidth, Width)
  GET(map)(Size, int, _mHeight, Height)
  SET(map)(Size, int, _mHeight, Height)
STATIC_CLASS_METHOD(map)(Size, parseSize, String* string)
END_CLASS
