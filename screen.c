#include "screen.h"

static char *fb = (char*) 0xb8000;
static int cursor = 0;

int clearscr() {
    for (int i = 0; i < 80*25; i++) {
      fb[i*2] = ' ';
    }
    cursor = 0;
    return 0;
}

int putchar(char c) {
  if (c == '\n') {
    cursor += 80 - cursor % 80;
  }
  else {
    fb[++cursor * 2] = c;
  }
  return 0;
}

int putstr(char *str) {
    while(*str != 0) {
      putchar(*str);
      str += 1;
    }
    return 0;
}
