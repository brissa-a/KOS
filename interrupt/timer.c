#include "timer.h"

int timer_setup() {

  set_timer_frequency(KERNEL_TIMER_FREQUENCY);
  
  return 0;
}

int set_timer_frequency(ui32_t f) {
  unsigned int nb_tick;

  nb_tick = I8254_MAX_FREQ / f;

  if (nb_tick > 65536 || nb_tick <= 0)
    return -1;

  
  
  return 0;
}
