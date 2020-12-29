//1. The .cc .cpp .cxx related header files
#include "Uri.h"
//2. C system include files.
#include <stdio.h>
#include <stdlib.h>
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.
#include "lang/StringBuffer.h"
#include "UriCodec.h"

/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */
/*              \\\\\\\            |         Class Uri       |           ///////           */
/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */

/** Index of a component which was not found. */
#define NOT_FOUND -1

/** Placeholder value for an index which hasn't been calculated yet. */
#define NOT_CALCULATED -2

static BUILD(global_const)(NOT_CACHED, String, "NOT CACHED")

static const char* HEX_DIGITS = "0123456789ABCDEF";

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(Uri)
{
    CONSTRUCTOR(super)(Object);
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(Uri)
{
    DESTRUCTOR(super)(Object);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++

/**
 * Returns true if the given character is allowed.
 *
 * @param c character to check
 * @param allow characters to allow
 * @return true if the character is allowed or false if it should be
 *  encoded
 */
static bool isAllowed(char c, String* allow)
{
    return (c >= 'A' && c <= 'Z')
            || (c >= 'a' && c <= 'z')
            || (c >= '0' && c <= '9')
            || strchr("_-!.~'()*", c) != NULL
            || (allow != NULL && _M(allow, indexOfChar, c) != NOT_FOUND);
}

/**
 * Encodes characters in the given string as '%'-escaped octets
 * using the UTF-8 scheme. Leaves letters ("A-Z", "a-z"), numbers
 * ("0-9"), and unreserved characters ("_-!.~'()*") intact. Encodes
 * all other characters with the exception of those specified in the
 * allow argument.
 *
 * @param s string to encode
 * @param allow set of additional characters to allow in the encoded form,
 *  null if no characters should be skipped
 * @return an encoded version of s suitable for use as a URI component,
 *  or null if s is null
 */
static String* encodex(String* s, String* allow)
{
    if (s == NULL) {
        return NULL;
    }

    // Lazily-initialized buffers.
    StringBuffer* encoded = NULL;
    String* rv = NULL;
    int oldLength = _M(s, length);

    // This loop alternates between copying over allowed characters and
    // encoding in chunks. This results in fewer method calls and
    // allocations than encoding one character at a time.
    int current = 0;
    while (current < oldLength) {
        // Start in "copying" mode where we copy over allowed chars.

        // Find the next character which needs to be encoded.
        int nextToEncode = current;
        while (nextToEncode < oldLength
                && isAllowed(_M(s, charAt, nextToEncode), allow)) {
            nextToEncode++;
        }

        // If there's nothing more to encode...
        if (nextToEncode == oldLength) {
            if (current == 0) {
                // We didn't need to encode anything!
                return CLONE(s);
            } else {
                // Presumably, we've already done some encoding.
                _M(encoded, appendString, s, current, oldLength);
                rv = _M(encoded, toString);
                DELETE(encoded);
                return rv;
            }
        }

        if (encoded == NULL) {
            encoded = NEW(StringBuffer);
        }

        if (nextToEncode > current) {
            // Append allowed characters leading up to this point.
            _M(encoded, appendString, s, current, nextToEncode);
        } else {
            // assert nextToEncode == current
        }

        // Switch to "encoding" mode.

        // Find the next allowed character.
        current = nextToEncode;
        int nextAllowed = current + 1;
        while (nextAllowed < oldLength
                && !isAllowed(_M(s, charAt, nextAllowed), allow)) {
            nextAllowed++;
        }

        // Convert the substring to bytes and encode the bytes as
        // '%'-escaped octets.
        String* toEncode = _M(s, substring, current, nextAllowed);
        const char* bytes = _M(toEncode, getCString);
        int bytesLength = _M(toEncode, length);
        for (int i = 0; i < bytesLength; i++) {
            _M(encoded, appendChar, '%');
            _M(encoded, appendChar, HEX_DIGITS[(bytes[i] & 0xf0) >> 4]);
            _M(encoded, appendChar, HEX_DIGITS[bytes[i] & 0xf]);
        }
        DELETE(toEncode);

        current = nextAllowed;
    }

    // Encoded could still be null at this point if s is empty.
    if (encoded == NULL)
        return CLONE(s);
    rv = _M(encoded, toString);DELETE(encoded);
    return rv;
}

/**
 * Encodes characters in the given string as '%'-escaped octets
 * using the UTF-8 scheme. Leaves letters ("A-Z", "a-z"), numbers
 * ("0-9"), and unreserved characters ("_-!.~'()*") intact. Encodes
 * all other characters.
 *
 * @param s string to encode
 * @return an encoded version of s suitable for use as a URI component,
 *  or null if s is null
 */
static inline String* encode(String* s)
{
    return encodex(s, NULL);
}

/**
 * Decodes '%'-escaped octets in the given string using the UTF-8 scheme.
 * Replaces invalid octets with the unicode replacement character
 * ("\\uFFFD").
 *
 * @param s encoded string to decode
 * @return the given string with escaped octets decoded, or null if
 *  s is null
 */
static inline String* decode(String* s)
{
    if (s == NULL) {
        return NULL;
    }
    return _SM(UriCodec, decode, s, false /* convertPlus */);
}

static String* STATIC_CLASS_METHOD()(Uri, decode, String* s)
{
    return decode(s);
}

static String* STATIC_CLASS_METHOD()(Uri, encode, String* s, String* allow)
{
    return encodex(s, allow);
}

static String* STATIC_CLASS_METHOD()(Uri, encode, String* s)
{
    return encode(s);
}

static bool CLASS_METHOD()(Uri, isOpaque)
{
    return !self(isHierarchical);
}

static bool CLASS_METHOD()(Uri, isAbsolute)
{
    return !self(isRelative);
}

BEGIN_CLASS(Uri, Object)
        CONSTRUCTOR(map)(Uri)
         DESTRUCTOR(map)(Uri)
       CLASS_METHOD(map)(Uri, isOpaque)
       CLASS_METHOD(map)(Uri, isAbsolute)
STATIC_CLASS_METHOD(map)(Uri, decode, String* s)
STATIC_CLASS_METHOD(map)(Uri, encode, String* s, String* allow)
STATIC_CLASS_METHOD(map)(Uri, encode, String* s)
END_CLASS

/* - - - - - - - - - - - - -  +---------------------------------+ - - - - - - - - - - - - - */
/*              \\\\\\\       |  Class AbstractHierarchicalUri  |       ///////             */
/* - - - - - - - - - - - - -  +---------------------------------+ - - - - - - - - - - - - - */

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(AbstractHierarchicalUri)
{
    CONSTRUCTOR(super)(Uri);
    self->_mPort = NOT_CALCULATED;
    self->_mHost = NOT_CACHED;
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(AbstractHierarchicalUri)
{
    if (self->_mHost != NOT_CACHED) DELETE(self->_mHost);
    DESTRUCTOR(super)(Uri);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
static String* CLASS_METHOD()(AbstractHierarchicalUri, getLastPathSegment)
{
    ObjectList* segments = self(getPathSegments);
    int size = _IM(segments, size);
    if (size == 0)
        return NULL;
    String* str = (String*)_IM(segments, get, size - 1);
    return str;
}

static Part* CLASS_METHOD()(AbstractHierarchicalUri, getUserInfoPart)
{
    if (self->_mUserInfo)
        return self->_mUserInfo;

    String* encoded = self(parseUserInfo);
    assert(encoded);
    self->_mUserInfo = _SM(Part, fromEncoded, encoded);
    DELETE(encoded);
    return self->_mUserInfo;
}

static String* CLASS_METHOD()(AbstractHierarchicalUri, parseUserInfo)
{
    String* authority = self(getEncodedAuthority);
    if (authority == NULL)
        return NULL;

    int end = _M(authority, lastIndexOfChar, '@');
    return end == NOT_FOUND ? NULL : _M(authority, substring, 0, end);
}

static String* CLASS_METHOD()(AbstractHierarchicalUri, getUserInfo)
{
    Part* part = self(getUserInfoPart);
    return _M(part, getDecoded);
}

static String* CLASS_METHOD()(AbstractHierarchicalUri, parseHost)
{
    String* authority = self(getEncodedAuthority);
    if (authority == NULL) {
        return NULL;
    }

    // Parse out user info and then port.
    int userInfoSeparator = _M(authority, lastIndexOfChar, '@');
    int portSeparator = self(findPortSeparator, authority);

    String* encodedHost = portSeparator == NOT_FOUND
            ? _M(authority, substring, userInfoSeparator + 1)
            : _M(authority, substring, userInfoSeparator + 1, portSeparator);

    String* decodedHost = decode(encodedHost);
    DELETE(encodedHost);
    return decodedHost;
}

static String* CLASS_METHOD()(AbstractHierarchicalUri, getHost)
{
    bool cached = (self->_mHost != NOT_CACHED);
    return cached ? self->_mHost : (self->_mHost = self(parseHost));
}

static int CLASS_METHOD()(AbstractHierarchicalUri, parsePort)
{
    String* authority = self(getEncodedAuthority);
    int portSeparator = self(findPortSeparator, authority);
    if (portSeparator == NOT_FOUND) {
        return -1;
    }

    String* portEncoded = _M(authority, substring, portSeparator + 1);
    String* portString = decode(portEncoded);
    int port = atoi(_M(portString, getCString));
    DELETE(portString);
    DELETE(portEncoded);
    return port;
}

static int CLASS_METHOD()(AbstractHierarchicalUri, getPort)
{
    return self->_mPort == NOT_CALCULATED
            ? self->_mPort = self(parsePort)
            : self->_mPort;
}

static int  CLASS_METHOD()(AbstractHierarchicalUri, findPortSeparator, String* authority)
{
    if (authority == NULL)
        return NOT_FOUND;

    // Reverse search for the ':' character that breaks as soon as a char that is neither
    // a colon nor an ascii digit is encountered. Thanks to the goodness of UTF-16 encoding,
    // it's not possible that a surrogate matches one of these, so this loop can just
    // look for characters rather than care about code points.
    for (int i = _M(authority, length) - 1; i >= 0; --i) {
        int character = _M(authority, charAt, i);
        if (':' == character) return i;
        // Character.isDigit would include non-ascii digits
        if (character < '0' || character > '9') return NOT_FOUND;
    }
    return NOT_FOUND;
}

BEGIN_CLASS(AbstractHierarchicalUri, Uri)
     CONSTRUCTOR(map)(AbstractHierarchicalUri)
      DESTRUCTOR(map)(AbstractHierarchicalUri)
    CLASS_METHOD(map)(AbstractHierarchicalUri, getLastPathSegment)
    CLASS_METHOD(map)(AbstractHierarchicalUri, getUserInfoPart)
    CLASS_METHOD(map)(AbstractHierarchicalUri, parseUserInfo)
    CLASS_METHOD(map)(AbstractHierarchicalUri, getUserInfo)
    CLASS_METHOD(map)(AbstractHierarchicalUri, parseHost)
    CLASS_METHOD(map)(AbstractHierarchicalUri, getHost)
    CLASS_METHOD(map)(AbstractHierarchicalUri, parsePort)
    CLASS_METHOD(map)(AbstractHierarchicalUri, getPort)
    CLASS_METHOD(map)(AbstractHierarchicalUri, findPortSeparator, String* authority)
END_CLASS

/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */
/*              \\\\\\\            |     Class StringUri     |           ///////           */
/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(StringUri, String* uriString)
{
    CONSTRUCTOR(super)(AbstractHierarchicalUri);
    assert(uriString);
    self->_mUriString = REFER(uriString);
    self->_mCachedSsi = NOT_CALCULATED;
    self->_mCachedFsi = NOT_CALCULATED;
    self->_mScheme = NOT_CACHED;
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(StringUri)
{
    DELETE(self->_mUriString);
    if (self->_mAuthority) DELETE(self->_mAuthority);
    if (self->_mPath) DELETE(self->_mPath);
    if (self->_mQuery) DELETE(self->_mQuery);
    if (self->_mFragment) DELETE(self->_mFragment);
    if (self->_mScheme != NOT_CACHED) DELETE(self->_mScheme);
    DESTRUCTOR(super)(AbstractHierarchicalUri);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
/**
 * Parses a path out of this given URI string.
 *
 * @param uriString URI string
 * @param ssi scheme separator index, -1 for a relative URI
 *
 * @return the path
 */
static String* parsePath(String* uriString, int ssi)
{
    int length = _M(uriString, length);

    // Find start of path.
    int pathStart;
    if (length > ssi + 2
            && _M(uriString, charAt, ssi + 1) == '/'
            && _M(uriString, charAt, ssi + 2) == '/') {
        // Skip over authority to path.
        pathStart = ssi + 3;
        while (pathStart < length) {
            switch (_M(uriString, charAt, pathStart)) {
                case '?': // Start of query
                case '#': // Start of fragment
                    return NEW(String, ""); // Empty path.
                case '/': // Start of path!
                case '\\':// Start of path!
                  // Per http://url.spec.whatwg.org/#host-state, the \ character
                  // is treated as if it were a / character when encountered in a
                  // host
                    goto PARSE_PATH_END1;
            }
            pathStart++;
            continue;
PARSE_PATH_END1:
            break;
        }
    } else {
        // Path starts immediately after scheme separator.
        pathStart = ssi + 1;
    }

    // Find end of path.
    int pathEnd = pathStart;
    while (pathEnd < length) {
        switch (_M(uriString, charAt, pathEnd)) {
            case '?': // Start of query
            case '#': // Start of fragment
                goto PARSE_PATH_END2;
        }
        pathEnd++;
        continue;
PARSE_PATH_END2:
        break;
    }

    return _M(uriString, substring, pathStart, pathEnd);
}

/**
 * Parses an authority out of the given URI string.
 *
 * @param uriString URI string
 * @param ssi scheme separator index, -1 for a relative URI
 *
 * @return the authority or null if none is found
 */
static String* parseAuthority(String* uriString, int ssi)
{
    int length = _M(uriString, length);
    // If "//" follows the scheme separator, we have an authority.
    if (length > ssi + 2
            && _M(uriString, charAt, ssi + 1) == '/'
            && _M(uriString, charAt, ssi + 2) == '/') {
        // We have an authority.

        // Look for the start of the path, query, or fragment, or the
        // end of the string.
        int end = ssi + 3;
        while (end < length) {
            switch (_M(uriString, charAt, end)) {
                case '/': // Start of path
                case '\\':// Start of path
                  // Per http://url.spec.whatwg.org/#host-state, the \ character
                  // is treated as if it were a / character when encountered in a
                  // host
                case '?': // Start of query
                case '#': // Start of fragment
                    goto PARSE_AUTHORITY_END;
            }
            end++;
            continue;
 PARSE_AUTHORITY_END:
            break;
        }
        return _M(uriString, substring, ssi + 3, end);
    } else {
        return NULL;
    }
}

/** Finds the first ':'. Returns -1 if none found. */
static int CLASS_METHOD()(StringUri, findSchemeSeparator)
{
    return self->_mCachedSsi == NOT_CALCULATED
            ? self->_mCachedSsi = _M(self->_mUriString, indexOfChar, ':')
            : self->_mCachedSsi;
}

/** Finds the first '#'. Returns -1 if none found. */
static int CLASS_METHOD()(StringUri, findFragmentSeparator)
{
    if (self->_mCachedFsi == NOT_CALCULATED) {
        int start = self(findSchemeSeparator);
        self->_mCachedFsi = _M(self->_mUriString, indexOfChar, '#', start);
    }
    return self->_mCachedFsi;
}

static bool CLASS_METHOD()(StringUri, isHierarchical)
{
    int ssi = self(findSchemeSeparator);

    if (ssi == NOT_FOUND) {
        // All relative URIs are hierarchical.
        return true;
    }

    if (_M(self->_mUriString, length) == ssi + 1) {
        // No ssp.
        return false;
    }

    // If the ssp starts with a '/', this is hierarchical.
    return _M(self->_mUriString, charAt, ssi + 1) == '/';
}

static bool CLASS_METHOD()(StringUri, isRelative)
{
    // Note: We return true if the index is 0
    return self(findSchemeSeparator) == NOT_FOUND;
}

static Part* CLASS_METHOD()(StringUri, getAuthorityPart)
{
    if (self->_mAuthority == NULL) {
        String* encodedAuthority
                = parseAuthority(self->_mUriString, self(findSchemeSeparator));
        self->_mAuthority = _SM(Part, fromEncoded, encodedAuthority);
        DELETE(encodedAuthority);
    }
    return self->_mAuthority;
}

static String* CLASS_METHOD()(StringUri, getEncodedAuthority)
{
    Part* part = self(getAuthorityPart);
    return _M(part, getEncoded);
}

static String* CLASS_METHOD()(StringUri, getAuthority)
{
    Part* part = self(getAuthorityPart);
    return _M(part, getDecoded);
}

static String* CLASS_METHOD()(StringUri, getScheme)
{
    bool cached = (self->_mScheme != NOT_CACHED);
    if (!cached)
        self->_mScheme = self(parseScheme);
    return self->_mScheme;
}

static String* CLASS_METHOD()(StringUri, parseScheme)
{
    int ssi = self(findSchemeSeparator);
    return ssi == NOT_FOUND ? NULL : _M(self->_mUriString, substring, 0, ssi);
}

static String* CLASS_METHOD()(StringUri, parseSsp)
{
    String* uriString = self->_mUriString;
    int ssi = self(findSchemeSeparator);
    int fsi = self(findFragmentSeparator);

    // Return everything between ssi and fsi.
    return fsi == NOT_FOUND
            ? _M(uriString, substring, ssi + 1)
            : _M(uriString, substring, ssi + 1, fsi);

}

static PathPart* CLASS_METHOD()(StringUri, getPathPart)
{
    if (self->_mPath == NULL) {
        String* encodedPath = self(parsePath);
        self->_mPath = _SM(PathPart, fromEncoded, encodedPath);
        DELETE(encodedPath);
    }
    return self->_mPath;
}

static String* CLASS_METHOD()(StringUri, parsePath)
{
    String* uriString = self->_mUriString;
    int ssi = self(findSchemeSeparator);

    // If the URI is absolute.
    if (ssi > -1) {
        // Is there anything after the ':'?
        bool schemeOnly = ssi + 1 == _M(uriString, length);
        if (schemeOnly) {
            // Opaque URI.
            return NULL;
        }

        // A '/' after the ':' means this is hierarchical.
        if (_M(uriString, charAt, ssi + 1) != '/') {
            // Opaque URI.
            return NULL;
        }
    } else {
        // All relative URIs are hierarchical.
    }

    return parsePath(uriString, ssi);
}

static String* CLASS_METHOD()(StringUri, getPath)
{
    PathPart* pathpart = self(getPathPart);
    return _M(pathpart, getDecoded);
}

static String* CLASS_METHOD()(StringUri, getEncodedPath)
{
    PathPart* pathpart = self(getPathPart);
    return _M(pathpart, getEncoded);
}

static Part* CLASS_METHOD()(StringUri, getQueryPart)
{
    if (self->_mQuery == NULL) {
        String* encodedQuery = self(parseQuery);
        self->_mQuery = _SM(Part, fromEncoded, encodedQuery);
        DELETE(encodedQuery);
    }
    return self->_mQuery;
}

static String* CLASS_METHOD()(StringUri, getEncodedQuery)
{
    Part* part = self(getQueryPart);
    return _M(part, getEncoded);
}

static String* CLASS_METHOD()(StringUri, getQuery)
{
    Part* part = self(getQueryPart);
    return _M(part, getDecoded);
}

static String* CLASS_METHOD()(StringUri, parseQuery)
{
    // It doesn't make sense to cache this index. We only ever
    // calculate it once.
    String* uriString = self->_mUriString;
    int start = self(findSchemeSeparator);
    int qsi = _M(uriString, indexOfChar, '?', start);
    if (qsi == NOT_FOUND) {
        return NULL;
    }

    int fsi = self(findFragmentSeparator);

    if (fsi == NOT_FOUND) {
        return _M(uriString, substring, qsi + 1);
    }

    if (fsi < qsi) {
        // Invalid.
        return NULL;
    }

    return _M(uriString, substring, qsi + 1, fsi);
}

static Part* CLASS_METHOD()(StringUri, getFragmentPart)
{
    if (self->_mFragment == NULL) {
        String* encoded = self(parseFragment);
        self->_mFragment = _SM(Part, fromEncoded, encoded);
        DELETE(encoded);
    }
    return self->_mFragment;
}

static String* CLASS_METHOD()(StringUri, getEncodedFragment)
{
    Part* part = self(getFragmentPart);
    return _M(part, getEncoded);
}

static String* CLASS_METHOD()(StringUri, parseFragment)
{
    int fsi = self(findFragmentSeparator);
    return fsi == NOT_FOUND ? NULL : _M(self->_mUriString, substring, fsi + 1);
}

static String* CLASS_METHOD()(StringUri, getFragment)
{
    Part* part = self(getFragmentPart);
    return _M(part, getDecoded);
}

static String* CLASS_METHOD()(StringUri, toString)
{
   return CLONE(self->_mUriString);
}

BEGIN_CLASS(StringUri, AbstractHierarchicalUri)
     CONSTRUCTOR(map)(StringUri, String* uriString)
      DESTRUCTOR(map)(StringUri)
    CLASS_METHOD(map)(StringUri, isHierarchical)
    CLASS_METHOD(map)(StringUri, isRelative)
    CLASS_METHOD(map)(StringUri, getAuthorityPart);
    CLASS_METHOD(map)(StringUri, getEncodedAuthority)
    CLASS_METHOD(map)(StringUri, findSchemeSeparator)
    CLASS_METHOD(map)(StringUri, findFragmentSeparator)
    CLASS_METHOD(map)(StringUri, getScheme)
    CLASS_METHOD(map)(StringUri, parseScheme)
    CLASS_METHOD(map)(StringUri, parsePath)
    CLASS_METHOD(map)(StringUri, getPathPart)
    CLASS_METHOD(map)(StringUri, getPath)
    CLASS_METHOD(map)(StringUri, getEncodedPath)
    CLASS_METHOD(map)(StringUri, getQueryPart)
    CLASS_METHOD(map)(StringUri, getEncodedQuery)
    CLASS_METHOD(map)(StringUri, getQuery)
    CLASS_METHOD(map)(StringUri, parseQuery)
    CLASS_METHOD(map)(StringUri, getFragmentPart)
    CLASS_METHOD(map)(StringUri, getEncodedFragment)
    CLASS_METHOD(map)(StringUri, parseFragment)
    CLASS_METHOD(map)(StringUri, getFragment)
    CLASS_METHOD(map)(StringUri, toString)
END_CLASS

/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */
/*              \\\\\\\            |    Class AbstractPart   |           ///////           */
/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */
// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(AbstractPart, String* encoded, String* decoded)
{
    CONSTRUCTOR(super)(Object);
    assert(encoded);
    assert(decoded);
    self->_mEncoded = REFER(encoded);
    self->_mDecoded = REFER(decoded);
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(AbstractPart)
{
    DELETE(self->_mEncoded);
    DELETE(self->_mDecoded);
    DESTRUCTOR(super)(Object);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
static String* CLASS_METHOD()(AbstractPart, getDecoded)
{
    bool hasDecoded = (self->_mDecoded != NOT_CACHED);
    return hasDecoded ? self->_mDecoded : (self->_mDecoded = decode(self->_mEncoded));
}

BEGIN_CLASS(AbstractPart, Object)
     CONSTRUCTOR(map)(AbstractPart, String* encoded, String* decoded)
      DESTRUCTOR(map)(AbstractPart)
    CLASS_METHOD(map)(AbstractPart, getDecoded)
END_CLASS

/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */
/*              \\\\\\\            |        Class Part       |           ///////           */
/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */
// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(Part, String* encoded, String* decoded)
{
    CONSTRUCTOR(super)(AbstractPart, encoded, decoded);
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(Part)
{
    DESTRUCTOR(super)(AbstractPart);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
static String* CLASS_METHOD()(Part, getEncoded)
{
    bool hasEncoded = (self->_mEncoded != NOT_CACHED);
    if (!hasEncoded)
        self->_mEncoded = encode(self->_mDecoded);
    return self->_mEncoded;
}

/**
 * Creates a part from the encoded and decoded strings.
 *
 * @param encoded part string
 * @param decoded part string
 */
static Part* STATIC_CLASS_METHOD()(Part, from, String* encoded, String* decoded)
{
    if (encoded == NULL) {
        return NULL;
    }
    if (_M(encoded, length) == 0) {
        return NULL;
    }

    if (decoded == NULL) {
        return NULL;
    }
    if (_M(decoded, length) == 0) {
        return NULL;
    }

    return NEW(Part, encoded, decoded);
}

/**
 * Creates a part from the encoded string.
 *
 * @param encoded part string
 */
static Part* STATIC_CLASS_METHOD()(Part, fromEncoded, String* encoded)
{
    return _SM(Part, from, encoded, NOT_CACHED);
}

/**
 * Creates a part from the decoded string.
 *
 * @param decoded part string
 */
static Part* STATIC_CLASS_METHOD()(Part, fromDecoded, String* decoded)
{
    return _SM(Part, from, NOT_CACHED, decoded);
}

BEGIN_CLASS(Part, AbstractPart)
        CONSTRUCTOR(map)(Part, String* encoded, String* decoded)
         DESTRUCTOR(map)(Part)
STATIC_CLASS_METHOD(map)(Part, from, String* encoded, String* decoded)
STATIC_CLASS_METHOD(map)(Part, fromEncoded, String* encoded)
STATIC_CLASS_METHOD(map)(Part, fromDecoded, String* decoded)
       CLASS_METHOD(map)(Part, getEncoded)
END_CLASS

/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */
/*              \\\\\\\            |     Class PathPart      |           ///////           */
/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(PathPart, String* encoded, String* decoded)
{
    CONSTRUCTOR(super)(AbstractPart, encoded, decoded);
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(PathPart)
{
    DESTRUCTOR(super)(AbstractPart);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
static String* CLASS_METHOD()(PathPart, getEncoded)
{
    bool hasEncoded = (self->_mEncoded != NOT_CACHED);
    // Don't encode '/'.
    if (!hasEncoded) {
        String* allow = NEW(String, "/");
        self->_mEncoded = encodex(self->_mDecoded, allow);
        DELETE(allow);
    }
    return self->_mEncoded;
}

/**
 * Creates a path from the encoded and decoded strings.
 *
 * @param encoded part string
 * @param decoded part string
 */
static PathPart* STATIC_CLASS_METHOD()(PathPart, from, String* encoded, String* decoded)
{
    if (encoded == NULL) {
        return NULL;
    }
    if (_M(encoded, length) == 0) {
        return NULL;
    }

    return NEW(PathPart, encoded, decoded);
}

/**
 * Creates a part from the encoded string.
 *
 * @param encoded part string
 */
static PathPart* STATIC_CLASS_METHOD()(PathPart, fromEncoded, String* encoded)
{
    return _SM(PathPart, from, encoded, NOT_CACHED);
}

/**
 * Creates a part from the decoded string.
 *
 * @param decoded part string
 */
static PathPart* STATIC_CLASS_METHOD()(PathPart, fromDecoded, String* decoded)
{
    return _SM(PathPart, from, NOT_CACHED, decoded);
}

BEGIN_CLASS(PathPart, AbstractPart)
        CONSTRUCTOR(map)(PathPart, String* encoded, String* decoded)
         DESTRUCTOR(map)(PathPart)
STATIC_CLASS_METHOD(map)(PathPart, from, String* encoded, String* decoded)
STATIC_CLASS_METHOD(map)(PathPart, fromEncoded, String* encoded)
STATIC_CLASS_METHOD(map)(PathPart, fromDecoded, String* decoded)
       CLASS_METHOD(map)(PathPart, getEncoded)
END_CLASS

