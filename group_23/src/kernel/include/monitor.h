#ifndef MONITOR_H
#define MONITOR_H

#include <stdint.h>
#include <stddef.h>
#include "../include/common.h"


// Write a single character out to the screen.
void monitor_put(char c);

// Clear the screen to all black.
void monitor_clear();

// Output a null-terminated ASCII string to the monitor.
void monitor_write(const char *str);
void monitor_write_dec(uint32_t n);
#endif
