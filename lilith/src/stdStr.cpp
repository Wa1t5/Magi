/*/
 * Author: Waltz (Wa1t5)
 * Project: Neon Genesis
/*/

#ifndef _LILITH_STD_STR_
#include "../include/stdStr.hpp"
#endif

namespace LILITH::STD::STRING {

 auto  StrLen(const char* str) -> INT::sizeT {
    INT::sizeT len = 0;
    while (str[len])
      len++;
    return len;
  }
}
