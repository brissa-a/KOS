#define MULTIBOOT_BOOTLOADER_MAGIC	0x2BADB002

#include "segmentation.h" 

int clearscr() {
    char* fb = (char*) 0xb8000;
    for (int i = 0; i < 80*25; i++) {
	    fb[i*2] = '1';
    }
    return 0;
}

int putstr(char *str) {
    char* fb = (char*) 0xb8000;	
    while(*str != 0) {
	    *fb = *str;
	    fb += 2;
	    str += 1;
    }
    return 0;
}

int k_main(unsigned long magic, unsigned long addr) {
	clearscr();
	putstr("Before setup!");
	gdt_setup();
	clearscr();
	putstr("After setup!");
	while (1);
	return 0;
}
