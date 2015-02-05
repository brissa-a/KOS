#include "interrupt/divide.h"
#include "interrupt/init.h"
#include "screen.h"

void divide_handler() {
  putstr("Division by 0, you noob\n");
  //  asm volatile("iret");
}

int divide_setup() {

  set_interrupt_handler(EXCEPT_IDT_BASE + EXCEPT_DIVIDE_ERROR, (ui32_t)divide_handler);
  
  return 0;
}
