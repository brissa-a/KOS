#include "utils.h"
#include "timer.h"

#define I8254_MAX_FREQ 1193180

#define I8254_TIMER0  0x40
#define I8254_TIMER1  0x41
#define I8254_TIMER2  0x42
#define I8254_CONTROL 0x43


int timer_setup() {

  set_timer_frequency(KERNEL_TIMER_FREQUENCY);
  
  return 0;
}

int set_timer_frequency(ui32_t f) {
  unsigned int nb_tick;

  nb_tick = I8254_MAX_FREQ / f;

  if (nb_tick > 65536 || nb_tick <= 0)
    return -1;

  outb(0x34, I8254_CONTROL);//TIMER0 0x30 ; Mode 2 rate generator 0x4
  
  /* LSB */
  outb((nb_tick & 0xFF), I8254_TIMER0);

  /* MSB */
  outb((nb_tick >> 8) & 0xFF, I8254_TIMER0);
  return 0;
}
