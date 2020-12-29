//1. The .cc .cpp .cxx related header files
#include "StringBuffer.h"
//2. C system include files.
#include <string.h>
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(StringBuffer)
{
    CONSTRUCTOR(super)(StringBuffer, 16);
}

/**
 * Constructs a string buffer with no characters in it and
 * the specified initial capacity.
 *
 * @param  capacity  the initial capacity.
 */
static CONSTRUCTOR()(StringBuffer, int capacity)
{
    CONSTRUCTOR(super)(Object);
    self->_mLength = 0;
    self->_mCapacity = capacity;
    self->_mStr = (char*)calloc(1, capacity);
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(StringBuffer)
{
    if (self->_mStr)
        free(self->_mStr);
    DESTRUCTOR(super)(Object);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
static int CLASS_METHOD()(StringBuffer, length)
{
    return self->_mLength;
}

/**
 * Returns the current capacity. The capacity is the amount of storage
 * available for newly inserted characters, beyond which an allocation
 * will occur.
 *
 * @return  the current capacity
 */
static int CLASS_METHOD()(StringBuffer, capacity)
{
    return self->_mCapacity;
}

/**
 * Ensures that the capacity is at least equal to the specified minimum.
 * If the current capacity is less than the argument, then a new internal
 * array is allocated with greater capacity. The new capacity is the
 * larger of:
 * <ul>
 * <li>The <code>minimumCapacity</code> argument.
 * <li>Twice the old capacity, plus <code>2</code>.
 * </ul>
 * If the <code>minimumCapacity</code> argument is nonpositive, this
 * method takes no action and simply returns.
 *
 * @param   minimumCapacity   the minimum desired capacity.
 */
void CLASS_METHOD()(StringBuffer, ensureCapacity, int minimumCapacity)
{
    if (minimumCapacity > 0 && minimumCapacity > self->_mCapacity) {
        _M(self, expandCapacity, minimumCapacity);
    }
}

void CLASS_METHOD()(StringBuffer, expandCapacity, int minimumCapacity)
{
    int newCapacity = self->_mCapacity * 2 + 2;
    if (newCapacity - minimumCapacity < 0)
        newCapacity = minimumCapacity;

    self->_mStr = (char*)realloc(self->_mStr, newCapacity);
    memset(self->_mStr+self->_mCapacity, 0, newCapacity-self->_mCapacity);
    self->_mCapacity = newCapacity;
}

char CLASS_METHOD()(StringBuffer, charAt, int index)
{
    assert(index >= 0 && index < self->_mLength);
    return self->_mStr[index];
}

void CLASS_METHOD()(StringBuffer, setCharAt, int index, char ch)
{
    assert(index >= 0 && index < self->_mLength);
    self->_mStr[index] = ch;
}

/**
 * Get C style string(i.e. const char*).
 */
static const char* CLASS_METHOD()(StringBuffer, getCString)
{
    return self->_mStr;
}

/**
 * Appends the string representation of the boolean argument to the sequence.
 * If the argument is true, a string equal to "true" is appended;
 * otherwise, a string equal to "false" is appended.
 *
 * @param b a boolean.
 * @return a pointer to this object.
 */
static StringBuffer* CLASS_METHOD()(StringBuffer, appendBool, bool b)
{
    if (b) {
        self(ensureCapacity, self->_mLength + 4 + 1);
        self->_mStr[self->_mLength++] = 't';
        self->_mStr[self->_mLength++] = 'r';
        self->_mStr[self->_mLength++] = 'u';
        self->_mStr[self->_mLength++] = 'e';
    } else {
        self(ensureCapacity, self->_mLength + 5 + 1);
        self->_mStr[self->_mLength++] = 'f';
        self->_mStr[self->_mLength++] = 'a';
        self->_mStr[self->_mLength++] = 'l';
        self->_mStr[self->_mLength++] = 's';
        self->_mStr[self->_mLength++] = 'e';
    }
    return self;
}

/**
 * Appends the specified C string to this character sequence.
 *
 * @param str the specified C string to be appended.
 * @return a pointer to this object.
 */
static StringBuffer* CLASS_METHOD()(StringBuffer, appendCString, const char* str)
{
    int len = strlen(str);
    self(ensureCapacity, self->_mLength + len + 1);
    strcat(self->_mStr, str);
    self->_mLength += len;
    return self;
}

/**
 * Appends the specified C string's substring to this character sequence.
 *
 * @param str the specified C string to be appended.
 * @param offset the index of the first char to append.
 * @param len the number of chars to append.
 * @return a pointer to this object.
 */
static StringBuffer* CLASS_METHOD()(StringBuffer, appendCString, const char* str, int offset, int len)
{
    assert(offset > 0 && len > 0);
    self(ensureCapacity, self->_mLength + len + 1);
    strncat(self->_mStr,  str + offset, len);
    self->_mLength += len;
    return self;
}

/**
 * Appends the specified string to this character sequence.
 * If str is NULL, then the four characters "null" are appended.
 *
 * @param str the characters to be appended.
 * @return a pointer to this object.
 */
static StringBuffer* CLASS_METHOD()(StringBuffer, appendString, String* str)
{
    const char* cstr = "NULL";
    if (str != NULL)
        cstr = _M(str, getCString);
    self(appendCString, cstr);
    return self;
}

static StringBuffer* CLASS_METHOD()(StringBuffer, appendString, String* str, int start, int end)
{
    assert(start >= 0 && start <= end);
    assert(end > _M(str, length));

    const char* cstr = "NULL";
    if (str != NULL)
        cstr = _M(str, getCString);
    self(appendCString, cstr, start, end-start);
    return self;
}

/**
 * Appends the string representation of the char argument to this sequence.
 *
 * @param c a char.
 * @return a pointer to this object.
 */
static StringBuffer* CLASS_METHOD()(StringBuffer, appendChar, char c)
{
    self(ensureCapacity, self->_mLength + 1 + 1);
    self->_mStr[self->_mLength++] = c;
    return self;
}

static StringBuffer* CLASS_METHOD()(StringBuffer, appendShort, short s)
{
    char cstr[32];
    sprintf(cstr, "%d", s);
    self(appendCString, cstr);
    return self;
}

/**
 * Appends the string representation of the int argument to this sequence.
 *
 * @param i an int.
 * @return a pointer to this object.
 */
static StringBuffer* CLASS_METHOD()(StringBuffer, appendInt, int i)
{
    char cstr[32];
    sprintf(cstr, "%d", i);
    self(appendCString, cstr);
    return self;
}

/**
 * Appends the string representation of the long argument to this sequence.
 *
 * @param lng an long.
 * @return a pointer to this object.
 */
static StringBuffer* CLASS_METHOD()(StringBuffer, appendLong, long lng)
{
    char cstr[32];
    sprintf(cstr, "%ld", lng);
    self(appendCString, cstr);
    return self;
}

/**
 * Appends the string representation of the float argument to this sequence.
 *
 * @param f an float.
 * @return a pointer to this object.
 */
static StringBuffer* CLASS_METHOD()(StringBuffer, appendFloat, float f)
{
    char cstr[32];
    sprintf(cstr, "%f", f);
    self(appendCString, cstr);
    return self;
}

/**
 * Appends the string representation of the double argument to this sequence.
 *
 * @param d an double.
 * @return a pointer to this object.
 */
static StringBuffer* CLASS_METHOD()(StringBuffer, appendDouble, double d)
{
    char cstr[32];
    sprintf(cstr, "%f", d);
    self(appendCString, cstr);
    return self;
}

/**
 * Appends the string representation of the Object argument.
 * If the argument is NULL, then a string equal to "null";
 * otherwise, the value of obj->toString() is appended.
 *
 * @param obj a pointer to Object.
 * @return a pointer to this object.
 */
static StringBuffer* CLASS_METHOD()(StringBuffer, appendObject, Object* obj)
{
    String* str = NULL;
    if (obj)
        str = _M(obj, toString);
    self(appendString, str);
    DELETE(str);
    return self;
}

static StringBuffer* CLASS_METHOD()(StringBuffer, insertCString, int offset, const char* str)
{
    assert(offset >= 0 && offset <= self -> _mLength);
    int len = strlen(str);
    self(ensureCapacity, self->_mLength + len + 1);
    memmove(self->_mStr + offset + len, self->_mStr + offset, self->_mLength - offset);
    strncpy(self->_mStr + offset, str, len);
    self->_mLength += len;
    return self;
}

static StringBuffer* CLASS_METHOD()(StringBuffer, insertCString, int index, const char* str, int offset, int len)
{
    int strLength = strlen(str);

    assert(index >= 0 && index <= strLength);
    assert(offset >= 0 && offset <= strLength - len);
    assert(len >= 0);

    self(ensureCapacity, self->_mLength + len + 1);
    memmove(self->_mStr + index + len, self->_mStr + index, self->_mLength - index);
    strncpy(self->_mStr + index, str, len);
    self->_mLength += len;
    return self;
}

static StringBuffer* CLASS_METHOD()(StringBuffer, insertString, int offset, String* str)
{
    self(insertCString, offset, str->_mStr);
    return self;
}

static StringBuffer* CLASS_METHOD()(StringBuffer, insertChar, int offset, char c)
{
    self(ensureCapacity, self->_mLength + 1 + 1);
    memmove(self->_mStr + offset + 1, self->_mStr + offset, self->_mLength - offset);
    self->_mStr[offset] = c;
    return self;
}

static StringBuffer* CLASS_METHOD()(StringBuffer, insertBool, int offset, bool b)
{
    const char* cstr;
    if (b) cstr = "true";
    else cstr = "false";
    self(insertCString, offset, cstr);
    return self;
}

static StringBuffer* CLASS_METHOD()(StringBuffer, insertInt, int offset, int i)
{
    char cstr[32];
    sprintf(cstr, "%d", i);
    self(insertCString, offset, cstr);
    return self;
}

static StringBuffer* CLASS_METHOD()(StringBuffer, insertLong, int offset, long lng)
{
    char cstr[32];
    sprintf(cstr, "%ld", lng);
    self(insertCString, offset, cstr);
    return self;
}

static StringBuffer* CLASS_METHOD()(StringBuffer, insertFloat, int offset, float f)
{
    char cstr[32];
    sprintf(cstr, "%f", f);
    self(insertCString, offset, cstr);
    return self;
}

static StringBuffer* CLASS_METHOD()(StringBuffer, insertDouble, int offset, double d)
{
    char cstr[32];
    sprintf(cstr, "%f", d);
    self(insertCString, offset, cstr);
    return self;
}

static StringBuffer* CLASS_METHOD()(StringBuffer, insertObject, int offset, Object* obj)
{
    String* str = _M(obj, toString);
    self(insertString, offset, str);
    DELETE(str);
    return self;
}

static String* CLASS_METHOD()(StringBuffer, toString)
{
    return NEW(String, self->_mStr);
}

BEGIN_CLASS(StringBuffer, Object)
    CONSTRUCTOR(map)(StringBuffer)
    CONSTRUCTOR(map)(StringBuffer, int capacity)
     DESTRUCTOR(map)(StringBuffer)
   CLASS_METHOD(map)(StringBuffer, length)
   CLASS_METHOD(map)(StringBuffer, capacity)
   CLASS_METHOD(map)(StringBuffer, getCString)
   CLASS_METHOD(map)(StringBuffer, appendCString, const char* str)
   CLASS_METHOD(map)(StringBuffer, appendCString, const char* str, int offset, int len)
   CLASS_METHOD(map)(StringBuffer, appendString, String* str)
   CLASS_METHOD(map)(StringBuffer, appendString, String* str, int start, int end)
   CLASS_METHOD(map)(StringBuffer, appendChar, char c)
   CLASS_METHOD(map)(StringBuffer, appendShort, short s)
   CLASS_METHOD(map)(StringBuffer, appendBool, bool b)
   CLASS_METHOD(map)(StringBuffer, appendInt, int i)
   CLASS_METHOD(map)(StringBuffer, appendLong, long lng)
   CLASS_METHOD(map)(StringBuffer, appendFloat, float f)
   CLASS_METHOD(map)(StringBuffer, appendDouble, double d)
   CLASS_METHOD(map)(StringBuffer, appendObject, Object* obj)
   CLASS_METHOD(map)(StringBuffer, insertCString, int offset, const char* str)
   CLASS_METHOD(map)(StringBuffer, insertCString, int index, const char* str, int offset, int len)
   CLASS_METHOD(map)(StringBuffer, insertString, int offset, String* str)
   CLASS_METHOD(map)(StringBuffer, insertChar, int offset, char c)
   CLASS_METHOD(map)(StringBuffer, insertBool, int offset, bool b)
   CLASS_METHOD(map)(StringBuffer, insertInt, int offset, int i)
   CLASS_METHOD(map)(StringBuffer, insertLong, int offset, long lng)
   CLASS_METHOD(map)(StringBuffer, insertFloat, int offset, float f)
   CLASS_METHOD(map)(StringBuffer, insertDouble, int offset, double d)
   CLASS_METHOD(map)(StringBuffer, insertObject, int offset, Object obj)
   CLASS_METHOD(map)(StringBuffer, ensureCapacity, int minimumCapacity)
   CLASS_METHOD(map)(StringBuffer, expandCapacity, int minimumCapacity)
   CLASS_METHOD(map)(StringBuffer, charAt, int index)
   CLASS_METHOD(map)(StringBuffer, setCharAt, int index, char ch)
   CLASS_METHOD(map)(StringBuffer, toString)
END_CLASS
