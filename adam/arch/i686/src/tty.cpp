/*/
 * Author: Waltz (Wa1t5)
 * Project: Neon Genesis
/*/

#ifndef _ADAM_TTY_
#include "../include/tty.hpp"
#endif

#ifndef _ADAM_VGA
#include "../include/vga.hpp"
#endif

namespace ADAM::TTY {
 
  // Terminal Attrs
  auto  terminalRow      = 0;
  auto  terminalMaxChars = VGA::VGA_HEIGHT * VGA::VGA_WIDTH + VGA::VGA_WIDTH;
  auto  terminalColumn   = 0;
  auto  terminalColor    = 0;
  auto* terminalBuffer   = (unsigned short*)0xB8000;

  void InitializeTerminal(void) {
    terminalColor = VGA::VgaEntryColor(VGA::VGA_COLOR_MAGENTA, VGA::VGA_COLOR_WHITE);
    for (LILITH::STD::INT::sizeT index = 0; index < terminalMaxChars; index++) {
        terminalBuffer[index] = VGA::VgaEntry(' ', terminalColor);
    }
}

  void TerminalSetColor(LILITH::STD::INT::uInt8T color) {
    terminalColor = color;
  }

  void TerminalSkipLine(void) {
    terminalRow++;
    terminalColumn = 0;
  }

  void TerminalPutEntryAt(char c, LILITH::STD::INT::uInt8T color, LILITH::STD::INT::sizeT x, LILITH::STD::INT::sizeT y) {
    const LILITH::STD::INT::sizeT index = y * VGA::VGA_WIDTH + x;
    terminalBuffer[index] = VGA::VgaEntry(c, color);
  }

  void TerminalPutChar(char c) {
    TerminalPutEntryAt(c, terminalColor, terminalColumn, terminalRow);  
      
    // Scroll terminal when we reach the end of the screen
    if (terminalRow >= VGA::VGA_HEIGHT) {
    
      for (LILITH::STD::INT::sizeT y = 0; y < VGA::VGA_HEIGHT; y++) {
        for (LILITH::STD::INT::sizeT x = 0; x < VGA::VGA_WIDTH; x++) { 

          // Get current line + the line below it         
          const LILITH::STD::INT::sizeT index = y * VGA::VGA_WIDTH + x;
          const LILITH::STD::INT::sizeT index_bottom = (y + 1) * VGA::VGA_WIDTH + x;

          // Swap elements between lines and clear the last line
          if (y < VGA::VGA_HEIGHT - 1) terminalBuffer[index] = terminalBuffer[index_bottom];
          else terminalBuffer[index] = VGA::VgaEntry(' ', terminalColor);
        }
      }
    
      // Start printing again on the start of last line
      terminalColumn = -1;
      terminalRow = VGA::VGA_HEIGHT - 1;
    }
      
    // Skip line when we reach end of line
    if (++terminalColumn >= VGA::VGA_WIDTH) TerminalSkipLine();
  }
  
  void TerminalWrite(LILITH::STD::STRING::string str, LILITH::STD::INT::sizeT size) {
    for (LILITH::STD::INT::sizeT i = 0; i < size; i++) {

      // New Line
      (str[i] == '\n') ? TerminalSkipLine() : TerminalPutChar(str[i]);
    }
  }

  void TerminalWriteString(LILITH::STD::STRING::string str) {
    TerminalWrite(str, LILITH::STD::STRING::StrLen(str));
  }
}
