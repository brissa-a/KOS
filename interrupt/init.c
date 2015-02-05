#include "interrupt/init.h"
#include "types.h"
#include "utils.h"
#include "segmentation.h"
#include "timer.h"

#define PIC_MASTER 0x20
#define PIC_SLAVE 0xa0

struct idt_entry {
  ui16_t handler_low_address;
  ui16_t segment;

  ui8_t reserved:5;
  ui8_t flags:3;
  ui8_t interrupt_type:3; // interrupt, trap, task ...
  ui8_t op_size:1; //0 = 16bits instruction; 1 = 32 bits instructions
  ui8_t zero:1;
  ui8_t privilege:2;
  ui8_t present:1;
  ui16_t handler_high_address;

} __attribute__((packed));

struct idt_register {
  ui16_t size; //Idt size
  ui32_t addr; //Idt address
} __attribute__((packed, aligned(8)));

static struct idt_entry idt[256];

int idt_setup() {

  struct idt_register idtr;
  int i;
  
  //Prepare the 256 interrupts
  for (i = 0; i < 256; ++i) {
    memset(idt + i, sizeof(struct idt_entry), 0);
    idt[i].segment = BUILD_SEGMENT_REG_VALUE(0, 0, SEG_KCODE);
    idt[i].interrupt_type = 0x6; //Interrupt gate
    idt[i].op_size = 1; //32 bits
  }

  idtr.addr = (ui32_t) idt;
  idtr.size = sizeof(idt) - 1;

  asm volatile("lidt %0\n"::"m"(idtr):"memory");
  
  return 0;
}

int pic_setup() {

  /* Send ICW1: 8086 mode + NOT Single ctrl + call address                                                                                                                                                  
     interval=8 */
  outb(0x11, PIC_MASTER);
  outb(0x11, PIC_SLAVE);

  /* Send ICW2: ctrl base address */
  outb(0x20, PIC_MASTER+1);
  outb(0x28, PIC_SLAVE+1);

  /* Send ICW3 master: mask where slaves are connected */
  outb(0x4, PIC_MASTER+1);
  /* Send ICW3 slave: index where the slave is connected on master */
  outb(0x2, PIC_SLAVE+1);

  /* Send ICW4: 8086 mode, fully nested, not buffered, no implicit EOI */
  outb(0x1, PIC_MASTER+1);
  outb(0x1, PIC_SLAVE+1);

  /* Send OCW1:                                                                                                                                                                                             
   * Closing all IRQs : waiting for a correct handler The only IRQ                                                                                                                                          
   * enabled is the cascade (that's why we use 0xFB for the master) */
  outb(0xFB, PIC_MASTER+1);
  outb(0xFF, PIC_SLAVE+1);

  return 0;
}

int set_interrupt_handler(int idx, ui32_t addr) {
  idt[idx].handler_low_address = addr & 0xffff;
  idt[idx].handler_high_address = (addr >> 16) & 0xffff;
  idt[idx].present = 1;

  return 0;
}

int interrupts_setup() {
  idt_setup();
  pic_setup();

  //Setup hardware interrupts
  timer_setup();

  asm volatile ("sti\n"); //Enable interrupts

  return 0;
}
