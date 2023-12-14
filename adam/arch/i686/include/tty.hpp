/*/
 * Author: Waltz (Wa1t6)
 * Project: Neon Genesis
/*/

#ifndef _ADAM_TTY_
#define _ADAM_TTY_

#include "../../../../lilith/include/bool.hpp"
#include "../../../../lilith/include/stdInt.hpp"
#include "../../../../lilith/include/stdStr.hpp"

// TODO: Rewrite the vga function to use VESA VBE and support // TODO: Fix bug where characters are being printed with a offset of 1 after scroll
namespace ADAM::TTY {
 
  // Terminal Funcs
  void InitializeTerminal(void);
  void TerminalSetColor(LILITH::STD::INT::uInt8T color);
  void TerminalSkipLine(void);
  void TerminalPutEntryAt(char c, LILITH::STD::INT::uInt8T color, LILITH::STD::INT::sizeT x, LILITH::STD::INT::sizeT y);
  void TerminalPuChar(char c);
  void TerminalWrite(LILITH::STD::STRING::string str, LILITH::STD::INT::sizeT size);
  void TerminalWriteString(LILITH::STD::STRING::string str);
}

#endif
