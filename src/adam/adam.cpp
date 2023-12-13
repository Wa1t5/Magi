#include "../lilith/stdint.hpp"
#include "../lilith/bool.hpp"

/* Check if we are compiling to linux and give an error if so  */
#if defined (__linux___) || (__gnu_linux__)
#error "Using wrong compiler, this uses i686-elf"
#endif

// TODO: Rewrite the vga function to use VESA VBE and support EFI
// TODO: Fix bug where characters are being printed with a offset of 1 after scroll

/* VGA Colors */
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

static inline LILITH::uInt8T VgaEntryColor(enum vgaColor fg, enum vgaColor bg) {
  return fg | bg << 4;
}

static inline LILITH::uInt16T VgaEntry(const unsigned char uc, const LILITH::uInt8T color) {
  return  { uc, (unsigned char)color };
}

LILITH::sizeT StrLen(const char* str) {
  LILITH::sizeT len = 0;
  while (str[len])
    len++;
  return len;
}

static const LILITH::sizeT VGA_WIDTH = 80;
static const LILITH::sizeT VGA_HEIGHT = 25;

LILITH::sizeT    terminalRow;
LILITH::sizeT    terminalMaxChars;
LILITH::sizeT    terminalColumn;
LILITH::uInt8T   terminalColor;
LILITH::uInt16T* terminalBuffer;

void InitializeTerminal(void) {
  terminalRow = 0;
  terminalColumn = 0;
  terminalColor = VgaEntryColor(VGA_COLOR_MAGENTA, VGA_COLOR_WHITE);
  terminalBuffer = (LILITH::uInt16T*)0xB8000;
  terminalMaxChars = VGA_HEIGHT * VGA_WIDTH + VGA_WIDTH;

  for (LILITH::sizeT y = 0; y < VGA_HEIGHT; y++) {
    for (LILITH::sizeT x = 0; x < VGA_WIDTH; x++) {
      const LILITH::sizeT index = y * VGA_WIDTH + x;
      terminalBuffer[index] = VgaEntry(' ', terminalColor);
    }
  }
}

void TerminalSetColor(LILITH::uInt8T color) {
  terminalColor = color;
}

void TerminalSkipLine(void) {
  terminalRow++;
  terminalColumn = 0;
}

void TerminalPutEntryAt(char c, LILITH::uInt8T color, LILITH::sizeT x, LILITH::sizeT y) {
  const LILITH::sizeT index = y * VGA_WIDTH + x;
  terminalBuffer[index] = VgaEntry(c, color);
}

void TerminalPutChar(char c) {
  TerminalPutEntryAt(c, terminalColor, terminalColumn, terminalRow);  
    
  // Scroll terminal when we reach the end of the screen
  if (terminalRow >= VGA_HEIGHT) {
    
    for (LILITH::sizeT y = 0; y < VGA_HEIGHT; y++) {
      for (LILITH::sizeT x = 0; x < VGA_WIDTH; x++) {          
        const LILITH::sizeT index = y * VGA_WIDTH + x;
        const LILITH::sizeT index_bottom = (y + 1) * VGA_WIDTH + x;
        if (y < VGA_HEIGHT - 1) terminalBuffer[index] = terminalBuffer[index_bottom];
        else terminalBuffer[index] = VgaEntry(' ', terminalColor);
      }
    }
    
    // Start printing again on the start of last line
    terminalColumn = -1;
    terminalRow = VGA_HEIGHT - 1;
  }
      
  // Skip line when we reach end of line
  if (++terminalColumn >= VGA_WIDTH) TerminalSkipLine();
}

void TerminalWrite(const char* data, LILITH::sizeT size) {
  for (LILITH::sizeT i = 0; i < size; i++) {

    // New Line
    (data[i] == '\n') ? TerminalSkipLine() : TerminalPutChar(data[i]);
  }
}

void TerminalWriteString(const char* data) {
  TerminalWrite(data, StrLen(data));
}

/* Use C linkage */
extern "C" {
  void kernel_main(void) {
    InitializeTerminal();
    //while (true){
      TerminalWriteString("Hello, World!\n");
      TerminalWriteString("With newline support!\n");

      for (LILITH::sizeT i = 0; i < 9999999; i++) {
        if (i >= 9999999) TerminalWriteString("\n");
      };
    //}
  }
    
}
