/*/
 * Author: Waltz (Wa1t5)
 * Project: Neon Genesis
/*/

#ifndef _ADAM_
#define _ADAM_

#include "../include/tty.hpp"

/* Check if we are compiling to linux and give an error if so  */
#if defined (__linux___) || (__gnu_linux__)
#error "Using wrong compiler, this uses i686-elf"
#endif

/* Use C linkage */
extern "C" {
  
  void first_impact(void) {
    ADAM::TTY::InitializeTerminal();
    while (true){
      ADAM::TTY::TerminalWriteString("Hello, World!\n");
      ADAM::TTY::TerminalWriteString("With newline support!\n");
    }
  }  
}

#endif
