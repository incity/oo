#ifndef _OO_URI_H_
#define _OO_URI_H_

#include "lang/String.h"
#include "util/List.h"

/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */
/*              \\\\\\\            |         Class Uri       |           ///////           */
/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */

/*
 * A basic URI syntax can be generalized as:
 *   scheme:[//[user:password@]host[:port]][/]path[?query][#fragment]
 */

/**
 * Immutable URI reference. A URI reference includes a URI and a fragment, the
 * component of the URI following a '#'. Builds and parses URI references
 * which conform to
 * <a href="http://www.faqs.org/rfcs/rfc2396.html">RFC 2396</a>.
 */
#define public_abstract_class_UriClass(T, SuperClss)                              \
                 extends_class(Object)(T, SuperClss)                              \
             bool CLASS_METHOD(public)(T, isHierarchical);                        \
             bool CLASS_METHOD(public)(T, isOpaque);                              \
             bool CLASS_METHOD(public)(T, isRelative);                            \
             bool CLASS_METHOD(public)(T, isAbsolute);                            \
          String* CLASS_METHOD(public)(T, getScheme);                             \
          String* CLASS_METHOD(public)(T, getSchemeSpecificPart);                 \
          String* CLASS_METHOD(public)(T, getEncodedSchemeSpecificPart);          \
          String* CLASS_METHOD(public)(T, getAuthority);                          \
          String* CLASS_METHOD(public)(T, getEncodedAuthority);                   \
          String* CLASS_METHOD(public)(T, getUserInfo);                           \
          String* CLASS_METHOD(public)(T, getEncodedUserInfo);                    \
          String* CLASS_METHOD(public)(T, getHost);                               \
              int CLASS_METHOD(public)(T, getPort);                               \
          String* CLASS_METHOD(public)(T, getPath);                               \
          String* CLASS_METHOD(public)(T, getEncodedPath);                        \
          String* CLASS_METHOD(public)(T, getQuery);                              \
          String* CLASS_METHOD(public)(T, getEncodedQuery);                       \
          String* CLASS_METHOD(public)(T, getFragment);                           \
          String* CLASS_METHOD(public)(T, getEncodedFragment);                    \
      ObjectList* CLASS_METHOD(public)(T, getPathSegments);                       \
          String* CLASS_METHOD(public)(T, getLastPathSegment);                    \
             Uri* CLASS_METHOD(public)(T, parse, String* uriString);              \
          String* CLASS_METHOD(public_static)(encode, String* s);                 \
          String* CLASS_METHOD(public_static)(encode, String* s, String* allow);  \
          String* CLASS_METHOD(public_static)(decode, String* s);                 \

#define public_abstract_class_Uri(T)  \
                  extends(Object)(T)  \

DECLARE_CLASS(public_abstract)(Uri, Object)

/* - - - - - - - - - - - - -  +---------------------------------+ - - - - - - - - - - - - - */
/*              \\\\\\\       |  Class AbstractHierarchicalUri  |       ///////             */
/* - - - - - - - - - - - - -  +---------------------------------+ - - - - - - - - - - - - - */

DECLARE_CLASS(forward)(Part, AbstractPart)
DECLARE_CLASS(forward)(PathPart, AbstractPart)

#define public_abstract_class_AbstractHierarchicalUriClass(T, SuperClss)             \
                              extends_class(Uri, abstract)(T, SuperClss)             \
            String* CLASS_METHOD(private)(T, parseUserInfo);                         \
            String* CLASS_METHOD(private)(T, parseHost);                             \
                int CLASS_METHOD(private)(T, parsePort);                             \
                int CLASS_METHOD(private)(T, findPortSeparator, String* authority);  \
              Part* CLASS_METHOD(private)(T, getUserInfoPart);                       \

#define public_abstract_class_AbstractHierarchicalUri(T)  \
                               extends(Uri, abstract)(T)  \
                                 String* _mHost;          \
                                 int _mPort;              \
                                 Part* _mUserInfo;

DECLARE_CLASS(public_abstract)(AbstractHierarchicalUri, Uri)

/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */
/*              \\\\\\\            |     Class StringUri     |           ///////           */
/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */

#define public_class_StringUriClass(T, SuperClss)                                 \
          extends_class(AbstractHierarchicalUri, abstract)(T, SuperClss)          \
              CONSTRUCTOR(public)(T, String* uriString);                          \
        int CLASS_METHOD(private)(T, findSchemeSeparator);                        \
        int CLASS_METHOD(private)(T, findFragmentSeparator);                      \
    String* CLASS_METHOD(private)(T, parseScheme);                                \
    String* CLASS_METHOD(private)(T, parseSsp);                                   \
    String* CLASS_METHOD(private)(T, parsePath);                                  \
    String* CLASS_METHOD(private)(T, parseQuery);                                 \
    String* CLASS_METHOD(private)(T, parseFragment);                              \
    String* CLASS_METHOD(private)(T, parseAuthority, String* uriString, int ssi); \
    String* CLASS_METHOD(private)(T, parsePath, String* uriString, int ssi);      \
      Part* CLASS_METHOD(private)(T, getAuthorityPart);                           \
  PathPart* CLASS_METHOD(private)(T, getPathPart);                                \
      Part* CLASS_METHOD(private)(T, getQueryPart);                               \
      Part* CLASS_METHOD(private)(T, getFragmentPart);                            \

#define public_class_StringUri(T)                               \
          extends(AbstractHierarchicalUri, abstract)(T)         \
            /* URI string representation. */                    \
        String* _mUriString;                                    \
            /* Cached scheme separator index. */                \
            int _mCachedSsi;                                    \
            /* Cached fragment separator index. */              \
            int _mCachedFsi;                                    \
          Part* _mAuthority;                                    \
      PathPart* _mPath;                                         \
          Part* _mQuery;                                        \
          Part* _mFragment;                                     \
          Part* _mSsp;                                          \
        String* _mScheme;                                       \

DECLARE_CLASS(public)(StringUri, AbstractHierarchicalUri)

/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */
/*              \\\\\\\            |    Class AbstractPart   |           ///////           */
/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */

typedef enum {
    BOTH    = 0,
    ENCODED = 1,
    DECODED = 2
} Representation;

#define public_abstract_class_AbstractPartClass(T, SuperClss)          \
          extends_class(Object)(T, SuperClss)                          \
            CONSTRUCTOR(public)(T, String* encoded, String* decoded);  \
   String* CLASS_METHOD(public)(T, getEncoded);                        \
   String* CLASS_METHOD(public)(T, getDecoded);                        \

#define public_abstract_class_AbstractPart(T)  \
          extends(Object)(T)                   \
            String* _mEncoded;                 \
            String* _mDecoded;

DECLARE_CLASS(public_abstract)(AbstractPart, Object)

/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */
/*              \\\\\\\            |        Class Part       |           ///////           */
/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */

#define public_class_PartClass(T, SuperClss)                                          \
          extends_class(AbstractPart, abstract)(T, SuperClss)                         \
          Part* CLASS_METHOD(public_static)(fromEncoded, String* encoded);            \
          Part* CLASS_METHOD(public_static)(fromDecoded, String* decoded);            \
          Part* CLASS_METHOD(public_static)(from, String* encoded, String* decoded);

#define public_class_Part(T)                  \
          extends(AbstractPart, abstract)(T)  \

DECLARE_CLASS(public)(Part, AbstractPart)

/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */
/*              \\\\\\\            |     Class PathPart      |           ///////           */
/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */

#define public_class_PathPartClass(T, SuperClss)                                            \
          extends_class(AbstractPart, abstract)(T, SuperClss)                               \
            PathPart* CLASS_METHOD(public_static)(fromEncoded, String* encoded);            \
            PathPart* CLASS_METHOD(public_static)(fromDecoded, String* decoded);            \
            PathPart* CLASS_METHOD(public_static)(from, String* encoded, String* decoded);

#define public_class_PathPart(T)              \
          extends(AbstractPart, abstract)(T)  \

DECLARE_CLASS(public)(PathPart, AbstractPart)

#endif /* _OO_URI_H_ */
