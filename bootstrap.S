
#define MULTIBOOT_HEADER_MAGIC		0x1BADB002
#define MULTIBOOT_HEADER_FLAGS		7
#define MULTIBOOT_BOOTLOADER_MAGIC	0x2BADB002

.section ".multiboot"
multiboot_header:
	.align 4
  /* magic=        */ .long MULTIBOOT_HEADER_MAGIC
  /* flags=        */ .long MULTIBOOT_HEADER_FLAGS
  /* checksum=     */ .long -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

.text
.global start, _start
start:
_start:
	jmp start
