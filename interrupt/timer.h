#pragma once

int timer_setup();
int set_timer_frequency(ui32_t);

#define I8254_MAX_FREQ 1193180
#define KERNEL_TIMER_FREQUENCY 100
