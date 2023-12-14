#ifndef _LILITH_STACK_PROTECTOR_
#include "../include/stackProtector.hpp"
#endif

namespace LILITH::STD::STACK_PROTECTOR{ 
  int  stackCheckGuard = -1;
  int stackCheckFail = -1;
}

int __stack_chk_guard = LILITH::STD::STACK_PROTECTOR::stackCheckGuard;
int __stack_chk_fail = LILITH::STD::STACK_PROTECTOR::stackCheckFail;
