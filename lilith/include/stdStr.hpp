/*/
 * Author: Waltz (Wa1t5)
 * Project: Neon Genesis
/*/

#ifndef _LILITH_STD_STR_
#define _LILITH_STD_STR_

#include "stdInt.hpp"

namespace LILITH::STD::STRING {
  typedef const char* string;
  auto StrLen(string str) -> LILITH::STD::INT::sizeT;
}

#endif
