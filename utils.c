#include "utils.h"

void *memset(void *buffer, ui32_t size, ui8_t value) {
  //  asm volatile (""
  //		);
  ui32_t i;
  ui8_t *cbuffer = buffer;
  for (i = 0; i < size; ++i) {
    cbuffer[i] = value;
  }
  return buffer;
}
