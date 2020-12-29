#ifndef _OO_BUNDLE_H_
#define _OO_BUNDLE_H_

#include "BaseBundle.h"
#include "util/Size.h"

/**
 * A mapping from String keys to values of various types.
 */
#define public_class_BundleClass(T, SuperClss)                             \
           extends_class(BaseBundle)(T, SuperClss)                         \
       void CLASS_METHOD(public)(T, putSize, String* key, Size* value);    \
      Size* CLASS_METHOD(public)(T, getSize, String* key);                 \

#define public_class_Bundle(T)    \
        extends(BaseBundle)(T)    \

DECLARE_CLASS(public)(Bundle, BaseBundle)

#endif /* _OO_BUNDLE_H_ */
