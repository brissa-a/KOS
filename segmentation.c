
#define SEG_NULL  0 /* NULL segment, unused by the procesor */
#define SEG_KCODE 1 /* Kernel code segment */
#define SEG_KDATA 2 /* Kernel data segment */
#define BUILD_SEGMENT_REG_VALUE(desc_privilege,in_ldt,seg_index) \
  (  (((desc_privilege) & 0x3)  << 0) \
   | (((in_ldt)?1:0)            << 2) \
   | ((seg_index)               << 3) )

typedef unsigned long int  ui32_t; /* 32b unsigned */
typedef unsigned short int ui16_t; /* 16b unsigned */
typedef unsigned char      ui8_t; /* 8b unsigned */

struct x86_segment_descriptor
{
  ui16_t limit_15_0;            /* Segment limit, bits 15..0 */
  ui16_t base_paged_addr_15_0;  /* Base address, bits 15..0 */

  ui8_t  base_paged_addr_23_16; /* Base address bits 23..16 */
  ui8_t  segment_type:4;        /* Section 3.4.3.1 (code/data)
				       and 3.5 (system) of Intel x86 vol 3 */
  ui8_t  descriptor_type:1;     /* 0=system, 1=Code/Data */
  ui8_t  dpl:2;
  ui8_t  present:1;

  ui8_t  limit_19_16:4;         /* Segment limit, bits 19..16 */
  ui8_t  custom:1;
  ui8_t  zero:1;
  ui8_t  op_size:1;             /* 0=16bits instructions, 1=32bits */
  ui8_t  granularity:1;         /* 0=limit in bytes, 1=limit in pages */

  ui8_t  base_paged_addr_31_24; /* Base address bits 31..24 */
} __attribute__ ((packed, aligned (8)));


struct x86_gdt_register {
  ui16_t  limit;
  ui32_t base_addr;
} __attribute__((packed, aligned(8)));

#define BUILD_GDTE(descr_privilege_level,is_code)               \
  ((struct x86_segment_descriptor) {                            \
      .limit_15_0=            0xffff,                           \
      .base_paged_addr_15_0=  0,                                \
      .base_paged_addr_23_16= 0,                                \
      .segment_type=          ((is_code)?0xb:0x3),              \
      .descriptor_type=       1,  /* 1=Code/Data */             \
      .dpl=                   ((descr_privilege_level) & 0x3),  \
      .present=               1,                                \
      .limit_19_16=           0xf,                              \
      .custom=                0,                                \
      .op_size=               1,  /* 32 bits instr/data */      \
      .granularity=           1   /* limit is in 4kB Pages */   \
  })

static struct x86_segment_descriptor gdt[] = {
  [SEG_NULL]  = (struct x86_segment_descriptor){ 0, },
  [SEG_KCODE] = BUILD_GDTE(0, 1),
  [SEG_KDATA] = BUILD_GDTE(0, 0),
};

int	gdt_setup()
{
  struct x86_gdt_register gdtr;

  gdtr.base_addr = (ui32_t) gdt;
  gdtr.limit     = sizeof(gdt) - 1;

  asm volatile ("lgdt %0          \n\
                 ljmp %1,$1f      \n\
                 1:               \n\
                 movw %2, %%ax    \n\
                 movw %%ax,  %%ss \n\
                 movw %%ax,  %%ds \n\
                 movw %%ax,  %%es \n\
                 movw %%ax,  %%fs \n\
                 movw %%ax,  %%gs \n\
		 movl %%cr0, %%eax \n\
		 orb  $1, %%al \n\
		 movl %%eax, %%cr0 \n"
		:
		:"m"(gdtr),
		 "i"(BUILD_SEGMENT_REG_VALUE(0, 0, SEG_KCODE)),
		 "i"(BUILD_SEGMENT_REG_VALUE(0, 0, SEG_KDATA))
		:"memory","eax");

  return 0;
}
