#pragma once

#include "types.h"

void *memset(void *buffer, ui32_t size, ui8_t value); 

#define outb(value, port) __asm__ volatile("outb %b0,%w1"::"a" (value),"Nd" (port))
#define inb(port)				\
  ({						\
    unsigned char _v;				\
    __asm__ volatile (				\
		      "inb %w1,%0"		\
		      :"=a" (_v)		\
		      :"Nd" (port));		\
    _v;						\
  })
