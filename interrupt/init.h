#pragma once

#include "types.h"


#define IRQ_IDT_BASE 32
#define IRQ_TIMER         0
#define IRQ_KEYBOARD      1
#define IRQ_SLAVE_PIC     2
#define IRQ_COM2          3
#define IRQ_COM1          4
#define IRQ_LPT2          5
#define IRQ_FLOPPY        6
#define IRQ_LPT1          7

#define EXCEPT_IDT_BASE 0
#define EXCEPT_DIVIDE_ERROR                  0         // No error code
#define EXCEPT_DEBUG                         1         // No error code
#define EXCEPT_NMI_INTERRUPT                 2         // No error code
#define EXCEPT_BREAKPOINT                    3         // No error code
#define EXCEPT_OVERFLOW                      4         // No error code
#define EXCEPT_BOUND_RANGE_EXCEDEED          5         // No error code
#define EXCEPT_INVALID_OPCODE                6         // No error code
#define EXCEPT_DEVICE_NOT_AVAILABLE          7         // No error code
#define EXCEPT_DOUBLE_FAULT                  8         // Yes (Zero)
#define EXCEPT_COPROCESSOR_SEGMENT_OVERRUN   9         // No error code
#define EXCEPT_INVALID_TSS                  10         // Yes
#define EXCEPT_SEGMENT_NOT_PRESENT          11         // Yes
#define EXCEPT_STACK_SEGMENT_FAULT          12         // Yes
#define EXCEPT_GENERAL_PROTECTION           13         // Yes
#define EXCEPT_PAGE_FAULT                   14         // Yes
#define EXCEPT_INTEL_RESERVED_1             15         // No
#define EXCEPT_FLOATING_POINT_ERROR         16         // No
#define EXCEPT_ALIGNEMENT_CHECK             17         // Yes (Zero)
#define EXCEPT_MACHINE_CHECK                18         // No



int set_interrupt_handler(int idx, ui32_t addr);
int interrupts_setup();
