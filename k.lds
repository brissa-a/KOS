OUTPUT_FORMAT("elf32-i386")
ENTRY(_start)
OUTPUT_ARCH("i386")

SECTIONS
{
	. =  0x100000 + SIZEOF_HEADERS;
	.text :
	{
		*(.text)
		*(.multiboot)
	}
}
