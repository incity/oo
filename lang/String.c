//1. The .cc .cpp .cxx related header files
//2. C system include files.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.
#include "math.h"
#include "String.h"

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(String)
{
    CONSTRUCTOR(super)(Object);
    self->_mStr = NULL;
    self->_mLength = 0;
}

static CONST_CONSTRUCTOR()(String, const char* str)
{
    CONST_CONSTRUCTOR(super)(Object);
    self->_mStr = (char*)str;
    self->_mLength = strlen(str);
}

static CONSTRUCTOR()(String, const char* str)
{
    assert(str != NULL);
    CONSTRUCTOR(super)(Object);
    int len = strlen(str);
    if (len == 0)
        return;

    self->_mStr = strdup(str);
    self->_mLength = len;
}

static CONSTRUCTOR()(String, const char* str, int offset, int count)
{
    assert(str != NULL);
    assert(offset >= 0);
    assert(count > 0);
    //assert(offset <= strlen(str) - count);
    CONSTRUCTOR(super)(Object);
    self->_mStr = strndup(str+offset, count);
    self->_mLength = count;
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(String)
{
    if (self->_mStr)
        free(self->_mStr);
    DESTRUCTOR(super)(Object);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
static int CLASS_METHOD()(String, length)
{
    return self->_mLength;
}

/**
 * Returns a formatted string using the specified format string and arguments.
 *
 * @param format a format string
 * @return a formatted string.
 */
static String* CLASS_METHOD(0)()(String, format, const char* format, ...)
{
    do {
        int len = 0;
        va_list ap;

        /* Determine required size */
        va_start(ap, format);
        len = vsnprintf(NULL, len, format, ap);
        va_end(ap);

        if (len <= 0)
           break;

        /* For '\0' */
        len++;

        char* str = self->_mStr;
        if (self->_mLength < len)
            str = realloc(self->_mStr, len);

        if (str == NULL)
            break;

        va_start(ap, format);
        len = vsnprintf(str, len, format, ap);
        va_end(ap);

        self->_mStr = str;
        self->_mLength = len-1;
    } while(0);

    return self;
}

static String* CLASS_METHOD()(String, format, const char* format, va_list ap)
{
    /* TODO: to implement */
    return self;
}

/**
 * Get C style string(i.e. const char*).
 */
static const char* CLASS_METHOD()(String, getCString)
{
    return self->_mStr;
}

static const char* CLASS_METHOD()(String, getCString, int off)
{
    return self->_mStr + off;
}

static void CLASS_METHOD()(String, getChars, char* dst, int dstBegin)
{
    memcpy(dst, self->_mStr, self->_mLength);
}

static void CLASS_METHOD()(String, getChars, int srcBegin, int srcEnd, char* dst, int dstBegin)
{
    memcpy(dst + dstBegin, self->_mStr + srcBegin, srcEnd - srcBegin);
}

static bool CLASS_METHOD()(String, equals, Object* anObject)
{
    if ((Object*)self == anObject)
        return true;

    if (INSTANCEOF(anObject, String)) {
        String* anotherString = (String*)anObject;
        if (self->_mLength == anotherString->_mLength) {
            return strcmp(self->_mStr, anotherString->_mStr) == 0;
        }
    }

    return false;
}

bool CLASS_METHOD()(String, equalsIgnoreCase, String* anotherString)
{
    if (self == anotherString)
        return true;
    if (INSTANCEOF(anotherString, String)) {
        if (self->_mLength == anotherString->_mLength) {
            return strcasecmp(self->_mStr, anotherString->_mStr) == 0;
        }
    }
    return false;
}

static bool CLASS_METHOD()(String, equalsToCString, const char* str)
{
    return str && strcmp(self->_mStr, str) == 0;
}

static bool CLASS_METHOD()(String, equalsToCStringIgnoreCase, const char* str)
{
    return str && strcasecmp(self->_mStr, str) == 0;
}

/**
 * Compares two strings lexicographically.
 */
static int CLASS_METHOD()(String, compareTo, String* anotherString)
{
    return strcmp(self->_mStr, anotherString->_mStr);
}

/**
 * Compares two strings lexicographically, ignoring case differences.
 */
static int CLASS_METHOD()(String, compareToIgnoreCase, String* str)
{
    return strcasecmp(self->_mStr, str->_mStr);
}

/**
 * Compares to C style string lexicographically.
 */
static int CLASS_METHOD()(String, compareToCString, const char* str)
{
    return strcmp(self->_mStr, str);
}

/**
 * Compares to C style string lexicographically, ignoring case differences.
 */
static int CLASS_METHOD()(String, compareToCStringIgnoreCase, const char* str)
{
    return strcasecmp(self->_mStr, str);
}

/**
 * Concatenates the specified string to the end of this string.
 *
 * @param str the string that is concatenated to the end of this String.
 * @return a string that represents the concatenation of this object's
 * characters followed by the string argument's characters.
 */
static String* CLASS_METHOD()(String, concat, String* str)
{
    do {
        if (str == NULL)
            break;
        if (str->_mLength <= 0)
            break;
        self(concatCString, str->_mStr);
    } while(0);
    return self;
}

/**
 * Concatenates the specified C string to the end of this string.
 *
 * @param str the C string that is concatenated to the end of this String.
 * @return a string that represents the concatenation of this object's
 * characters followed by the string argument's characters.
 */
static String* CLASS_METHOD()(String, concatCString, const char* str)
{
    do {
        if (str == NULL)
            break;
        int len = strlen(str);
        if (len <= 0)
            break;
        self->_mStr = realloc(self->_mStr, self->_mLength + len + 1);
        strcpy(self->_mStr+self->_mLength, str);
        self->_mLength += len;
    } while(0);

    return self;
}

static String* CLASS_METHOD()(String, concatChar, char c)
{
    self->_mStr = realloc(self->_mStr, self->_mLength+1+1);
    self->_mStr[self->_mLength++] = c;
    self->_mStr[self->_mLength] = 0;
    return self;
}

static char CLASS_METHOD()(String, charAt, int index)
{
    if (index < 0 || index >= self->_mLength) {
        assert(0);
        return -1;
    }
    return self->_mStr[index];
}

static String* CLASS_METHOD()(String, clone)
{
    String* str = (String*)CLASS_METHOD(super)(Object, clone);
    str->_mStr = strdup(self->_mStr);
    return str;
}

static int CLASS_METHOD()(String, indexOf, String* str)
{
    return self(indexOf, str, 0);
}

static int CLASS_METHOD()(String, indexOf, String* str, int fromIndex)
{
    const char* p = strstr(self->_mStr + fromIndex, str->_mStr);
    if (p == NULL)
        return -1;
    return p - self->_mStr;
}

static int CLASS_METHOD()(String, indexOfChar, int ch)
{
    return self(indexOfChar, ch, 0);
}

static int CLASS_METHOD()(String, indexOfChar, int ch, int fromIndex)
{
    const char* p = strchr(self->_mStr + fromIndex, ch);
    if (p == NULL)
        return -1;
    return p - self->_mStr;
}

/**
 * Code shared by String and StringBuffer to do searches. The
 * source is the character array being searched, and the target
 * is the string being searched for.
 *
 * @param   source       the characters being searched.
 * @param   sourceOffset offset of the source string.
 * @param   sourceCount  count of the source string.
 * @param   target       the characters being searched for.
 * @param   targetOffset offset of the target string.
 * @param   targetCount  count of the target string.
 * @param   fromIndex    the index to begin searching from.
 */
static int lastIndexOf(char* source, int sourceOffset, int sourceCount,
                           char* target, int targetOffset, int targetCount,
                           int fromIndex)
{
    /*
     * Check arguments; return immediately where possible. For
     * consistency, don't check for NULL str.
     */
    int rightIndex = sourceCount - targetCount;
    if (fromIndex < 0) {
        return -1;
    }
    if (fromIndex > rightIndex) {
        fromIndex = rightIndex;
    }
    /* Empty string always matches. */
    if (targetCount == 0) {
        return fromIndex;
    }

    int strLastIndex = targetOffset + targetCount - 1;
    char strLastChar = target[strLastIndex];
    int min = sourceOffset + targetCount - 1;
    int i = min + fromIndex;

startSearchForLastChar:
    while (true) {
        while (i >= min && source[i] != strLastChar) {
            i--;
        }
        if (i < min) {
            return -1;
        }
        int j = i - 1;
        int start = j - (targetCount - 1);
        int k = strLastIndex - 1;

        while (j > start) {
            if (source[j--] != target[k--]) {
                i--;
                goto startSearchForLastChar;
            }
        }
        return start - sourceOffset + 1;
    }
}

static int CLASS_METHOD()(String, lastIndexOf, String* str)
{
    return self(lastIndexOf, str, self->_mLength);
}

static int CLASS_METHOD()(String, lastIndexOf, String* str, int fromIndex)
{
    return lastIndexOf(self->_mStr, 0, self->_mLength, str->_mStr, 0, str->_mLength, fromIndex);
}

static int CLASS_METHOD()(String, lastIndexOfChar, int ch)
{
    return self(lastIndexOfChar, ch, self->_mLength - 1);
}

static int CLASS_METHOD()(String, lastIndexOfChar, int ch, int fromIndex)
{
    int offset = 0;
    int i = min(fromIndex, self->_mLength - 1);
    for (; i >= offset; i--) {
        if (self->_mStr[i] == ch)
            return i - offset;
    }
    return -1;
}

static String* CLASS_METHOD()(String, substring, int beginIndex, int endIndex)
{
    assert(beginIndex >= 0);
    assert(endIndex <= self->_mLength);
    assert(beginIndex <= endIndex);
    return ((beginIndex == 0) && (endIndex == self->_mLength)) ? CLONE(self) :
        NEW(String, self->_mStr, beginIndex, endIndex - beginIndex);
}

static String* CLASS_METHOD()(String, substring, int beginIndex)
{
    return self(substring, beginIndex, self->_mLength);
}

/**
 * Returns a hash code for this string. The hash code for a
 * <code>String</code> object is computed as
 * <blockquote><pre>
 * s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1]
 * </pre></blockquote>
 * using <code>int</code> arithmetic, where <code>s[i]</code> is the
 * <i>i</i>th character of the string, <code>n</code> is the length of
 * the string, and <code>^</code> indicates exponentiation.
 * (The hash value of the empty string is zero.)
 *
 * @return  a hash code value for this object.
 */
static int CLASS_METHOD()(String, hashCode)
{
    int h = self->_mHash;
    if (h == 0 && self->_mLength > 0) {
        for (int i = 0; i < self->_mLength; i++) {
            h = 31*h + self->_mStr[i++];
        }
    }
    return h;
}

/**
 * This object (which is already a string!) is itself returned.
 *
 * @return  the string itself.
 */
static String* CLASS_METHOD()(String, toString)
{
    return self;
}

BEGIN_CLASS(String, Object)
       CONSTRUCTOR(map)(String)
       CONSTRUCTOR(map)(String, const char* str)
       CONSTRUCTOR(map)(String, const char* str, int offset, int count)
 CONST_CONSTRUCTOR(map)(String, const char* str)
        DESTRUCTOR(map)(String)
      CLASS_METHOD(map)(String, length)
   CLASS_METHOD(0)(map)(String, format, const char* format, ...)
      CLASS_METHOD(map)(String, format, const char* format, va_list ap)
      CLASS_METHOD(map)(String, getCString)
      CLASS_METHOD(map)(String, compareTo, String* anotherString)
      CLASS_METHOD(map)(String, compareToIgnoreCase, String* str)
      CLASS_METHOD(map)(String, compareToCString, const char* str)
      CLASS_METHOD(map)(String, compareToCStringIgnoreCase, const char* str)
      CLASS_METHOD(map)(String, concat, String* str)
      CLASS_METHOD(map)(String, concatChar, char c)
      CLASS_METHOD(map)(String, concatCString, const char* str)
      CLASS_METHOD(map)(String, charAt, int index)
      CLASS_METHOD(map)(String, equals, String* anotherString)
      CLASS_METHOD(map)(String, equalsIgnoreCase, String* anotherString)
      CLASS_METHOD(map)(String, equalsToCString, const char* str)
      CLASS_METHOD(map)(String, equalsToCStringIgnoreCase, const char* str)
      CLASS_METHOD(map)(String, clone)
      CLASS_METHOD(map)(String, hashCode)
      CLASS_METHOD(map)(String, indexOf, String* str, int fromIndex)
      CLASS_METHOD(map)(String, indexOf, String* str)
      CLASS_METHOD(map)(String, indexOfChar, String* str, int fromIndex)
      CLASS_METHOD(map)(String, indexOfChar, int ch)
      CLASS_METHOD(map)(String, lastIndexOfChar, int ch, int fromIndex)
      CLASS_METHOD(map)(String, lastIndexOfChar, int ch)
      CLASS_METHOD(map)(String, lastIndexOf, String* str, int fromIndex)
      CLASS_METHOD(map)(String, lastIndexOf, String* str)
      CLASS_METHOD(map)(String, substring, int beginIndex, int endIndex)
      CLASS_METHOD(map)(String, substring, int beginIndex)
      CLASS_METHOD(map)(String, toString)
      CLASS_METHOD(map)(String, getChars, char* dst, int dstBegin)
      CLASS_METHOD(map)(String, getChars, int srcBegin, int srcEnd, char* dst, int dstBegin)
END_CLASS
