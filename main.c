#define MULTIBOOT_BOOTLOADER_MAGIC	0x2BADB002

#include "segmentation.h"
#include "interrupt/init.h"
#include "screen.h"

void	print_a() {
	putchar('a');
}

int k_main(unsigned long magic, unsigned long addr) {
	clearscr();
	putstr("Before setup!\n");
	gdt_setup();
        interrupts_setup();
	set_interrupt_handler(IRQ_IDT_BASE + IRQ_TIMER, print_a);
	set_interrupt_handler(EXCEPT_IDT_BASE + EXCEPT_DEBUG, print_a);
	print_a();
	asm volatile ("sti\n");
	putstr("After setup!");
	while (1);
	return 0;
}
