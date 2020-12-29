#ifndef _OO_URI_CODEC_H_
#define _OO_URI_CODEC_H_

#include "lang/String.h"
#include "util/List.h"

/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */
/*              \\\\\\\            |      Class UriCodec     |           ///////           */
/* - - - - - - - - - - - - - - - - +-------------------------+ - - - - - - - - - - - - - - */

/**
 * Decodes "application/x-www-form-urlencoded" content.
 *
 * @hide
 */

#define public_final_class_UriCodecClass(T, SuperClss)           \
                   extends_class(Object)(T, SuperClss)           \
       String* CLASS_METHOD(public_static)(decode, String* s, bool convertPlus/*, Charset* charset*/); \

#define public_final_class_UriCodec(T)  \
                    extends(Object)(T)  \

DECLARE_CLASS(public_final)(UriCodec, Object)

#endif /* _OO_URI_CODEC_H_ */
