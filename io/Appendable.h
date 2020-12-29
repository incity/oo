#ifndef _OO_APPENDABLE_H_
#define _OO_APPENDABLE_H_

#include "lang/Ibject.h"

#define public_interface_Appendable(IF, T)                      \
          extends_interface(Ibject)(IF, T)                      \
              void CLASS_METHOD(public)(T, append, char c);     \
              void CLASS_METHOD(public)(T, append, const char* buf, int len);              \
              void CLASS_METHOD(public)(T, append, const char* buf, int start, int end);   \

DECLARE_INTERFACE(public)(Appendable)

#endif /* _OO_APPENDABLE_H_ */
