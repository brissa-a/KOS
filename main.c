#define MULTIBOOT_BOOTLOADER_MAGIC	0x2BADB002

#include "segmentation.h"
#include "interrupt/init.h"
#include "screen.h"

int k_main(unsigned long magic, unsigned long addr) {
	clearscr();
	putstr("Before setup!\n");
	gdt_setup();
        interrupts_setup();
	putstr("After setup!\n");
	int a = 10, b = 0;
	int c = a / b;
	if (c > 0)
	  putstr("Salut les copains");
	while (1);
	return 0;
}
