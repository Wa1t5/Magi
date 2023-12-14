/*/
 * Author: Waltz (Wa1t6)
 * Project: Neon Genesis
/*/

#ifndef _ADAM_VGA_
#define _ADAM_VGA_

#include "../../../../lilith/include/bool.hpp"
#include "../../../../lilith/include/stdInt.hpp"
#include "../../../../lilith/include/stdStr.hpp"

namespace ADAM::VGA {  
  // VGA Colors 
  enum vgaColor {
    VGA_COLOR_BLACK          = 0,
    VGA_COLOR_BLUE           = 1,
    VGA_COLOR_GREEN          = 2,
    VGA_COLOR_CYAN           = 3,
    VGA_COLOR_RED            = 4,
    VGA_COLOR_MAGENTA        = 5,
    VGA_COLOR_BROWN          = 6,
    VGA_COLOR_LIGHT_GREY     = 7,
    VGA_COLOR_DARK_GREY      = 8,
    VGA_COLOR_LIGHT_BLUE     = 9,
    VGA_COLOR_LIGHT_GREEN    = 10,
    VGA_COLOR_LIGHT_CYAN     = 11,
    VGA_COLOR_LIGHT_RED      = 12,
    VGA_COLOR_LIGHT_MAGENTA  = 13,
    VGA_COLOR_LIGHT_BROWN    = 14,
    VGA_COLOR_WHITE          = 15,
  };
  
  
  // VGA Attrs
  const auto VGA_WIDTH = 80;
  const auto VGA_HEIGHT = 25;

  // Vga Funcs
  auto VgaEntryColor(enum vgaColor  fg, enum vgaColor  bg) -> LILITH::STD::INT::uInt8T;
  auto VgaEntry(const char  uc, const LILITH::STD::INT::uInt8T color) -> LILITH::STD::INT::uInt16T;
}

#endif
