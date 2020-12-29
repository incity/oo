//1. The .cc .cpp .cxx related header files
#include "UriCodec.h"
//2. C system include files.
#include <stdio.h>
#include <stdlib.h>
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.
#include "lang/StringBuffer.h"

/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */
/*              \\\\\\\            |      Class UriCodec     |           ///////           */
/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

/**
 * Interprets a char as hex digits, returning a number from -1 (invalid char) to 15 ('f').
 */
static int hexCharToValue(char c)
{
    if ('0' <= c && c <= '9') {
        return c - '0';
    }
    if ('a' <= c && c <= 'f') {
        return 10 + c - 'a';
    }
    if ('A' <= c && c <= 'F') {
        return 10 + c - 'A';
    }
    return -1;
}

static inline char getNextCharacter(String* uri, int index, int end, String* name)
{
    if (index >= end) {
        assert(0);
    }
    return _M(uri, charAt, index);
}

/**
 * Character to be output when there's an error decoding an input.
 */
#define INVALID_INPUT_CHARACTER 0xfffd

static void appendDecoded(StringBuffer* buffer, String* s, bool convertPlus)
{
    // Holds the bytes corresponding to the escaped chars being read (empty if the last char
    // wasn't a escaped char).
    int i = 0;
    int len = _M(s, length);
    while (i < len) {
        char c = _M(s, charAt, i);
        i++;
        switch (c) {
            case '+':
                _M(buffer, appendChar, convertPlus ? ' ' : '+');
                break;
            case '%':
            {
                // Expect two characters representing a number in hex.
                byte hexValue = 0;
                for (int j = 0; j < 2; j++) {
                    c = getNextCharacter(s, i, len, NULL /* name */);
                    i++;
                    int newDigit = hexCharToValue(c);
                    if (newDigit < 0) {
                        _M(buffer, appendShort, INVALID_INPUT_CHARACTER);
                        break;
                    }
                    hexValue = (byte) (hexValue * 0x10 + newDigit);
                }
                _M(buffer, appendChar, hexValue);
                break;
            }
            default:
                _M(buffer, appendChar, c);
        }
    }
}

static inline String* decode(String* s, bool convertPlus)
{
    StringBuffer* buffer = NEW(StringBuffer, _M(s, length));
    appendDecoded(buffer, s, convertPlus);
    String* decoded = _M(buffer, toString);
    DELETE(buffer);
    return decoded;
}

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(UriCodec)
{
    CONSTRUCTOR(super)(Object);
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(UriCodec)
{
    DESTRUCTOR(super)(Object);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
static String* STATIC_CLASS_METHOD()(UriCodec, decode, String* s, bool convertPlus)
{
    return decode(s, convertPlus);
}

BEGIN_CLASS(UriCodec, Object)
        CONSTRUCTOR(map)(UriCodec)
         DESTRUCTOR(map)(UriCodec)
STATIC_CLASS_METHOD(map)(UriCodec, decode, String* s, bool convertPlus)
END_CLASS
