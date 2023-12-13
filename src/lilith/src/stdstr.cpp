/*/
 * Author: Waltz (Wa1t5)
 * Project: Neon Genesis
/*/

#include "../include/stdstr.hpp"

LILITH::sizeT LILITH::StrLen(const char* str) {
  LILITH::sizeT len = 0;
  while (str[len])
    len++;
  return len;
}
