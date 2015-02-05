#pragma once

int	gdt_setup();

#define BUILD_SEGMENT_REG_VALUE(desc_privilege,in_ldt,seg_index) \
  (  (((desc_privilege) & 0x3)  << 0) \
   | (((in_ldt)?1:0)            << 2) \
   | ((seg_index)               << 3) )

#define SEG_NULL  0 /* NULL segment, unused by the procesor */
#define SEG_KCODE 1 /* Kernel code segment */
#define SEG_KDATA 2 /* Kernel data segment */
