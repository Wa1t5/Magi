
/*/
 * Author: Waltz (Wa1t5)
 * Project: Neon Genesis
/*/

#ifndef _ADAM_VGA_
#include "../include/vga.hpp"
#endif

namespace ADAM::VGA {  
  auto VgaEntryColor(enum vgaColor  fg, enum vgaColor  bg) -> LILITH::STD::INT::uInt8T {
    return fg | bg << 4;
  }

  auto VgaEntry(const char  uc, const LILITH::STD::INT::uInt8T  color) -> LILITH::STD::INT::uInt16T {
    return uc | color << 8;
  }
}
