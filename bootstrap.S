
/* The magic number for the Multiboot header.  in the first 8192 octet of the file*/
#define MULTIBOOT_HEADER_MAGIC		0x1BADB002
/* The flags for the Multiboot header.  */
#define MULTIBOOT_HEADER_FLAGS		0x00010003
/* The magic number passed by a Multiboot-compliant boot loader.  */
#define MULTIBOOT_BOOTLOADER_MAGIC	0x2BADB002
/* The size of our stack (16KB).  */
#define MULTIBOOT_STACK_SIZE	        0x4000

#define MULTIBOOT_CMDLINE 4
#define MULTIBOOT_MODS 8

.section ".multiboot"
	.align 4
multiboot_header:
  /* magic=        */ .long MULTIBOOT_HEADER_MAGIC
  /* flags=        */ .long MULTIBOOT_HEADER_FLAGS
  /* checksum=     */ .long -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
  /* header_addr=  */ .long multiboot_header
  /* load_addr=    */ .long __b_kernel /*build with ld*/
  /* load_end_addr=*/ .long __e_load
  /* bss_end_addr= */ .long __e_kernel
  /* entry_addr=   */ .long start

.text
.global start, _start, break
start:
_start:
	/*
	mov	$753664, %eax
	movb	$65, (%eax)
	add	$1, %eax
	movb	$7, (%eax)
	hlt
	*/
	jmp start
