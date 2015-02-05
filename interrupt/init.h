#pragma once

#include "types.h"

int set_interrupt_handler(int idx, ui32_t addr);
int interrupts_setup();
