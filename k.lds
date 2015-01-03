OUTPUT_FORMAT("elf32-i386")
ENTRY(_start)
OUTPUT_ARCH("i386")

SECTIONS
{
    . = 0x200000;
    __b_load   = .;

    .multiboot :
    {
	*(.multiboot);
	/*	LONG(0);/*/
    }

    /*. = ALIGN(4096);*/
    __b_kernel = .;
  
    .text /*ALIGN(4096)*/ :
    {   
        *(.text)
	/*
        PROVIDE(etext = .);
        PROVIDE(_etext = .);
	*/
    }

/*
    .data . :
    {   
    	*(.data*) 
        PROVIDE(edata = .);
	PROVIDE(_edata = .);
    }

    .rodata . :
    {   *(.rodata*)
        PROVIDE(erodata = .);
        PROVIDE(_erodata = .);
    }
*/
    __e_load = .;
/*
    .bss SIZEOF(.rodata) + ADDR(.rodata) :
    {   *(.bss)
        *(COMMON)
        PROVIDE(ebss = .);
	PROVIDE(_ebss = .);
    }
*/
    __e_kernel = .;
/*
    /DISCARD/ :{
    	      *(.note*)
              *(.indent)
	      *(.comment)
    	      *(.stab)
    	      *(.stabstr)
    }
*/

}
