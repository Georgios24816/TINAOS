#ifndef STDIO_H
#define STDIO_H

#include <stdarg.h>
#include <stdint.h>

void cprintf(uint8_t color, char* format,...);
void printf(char* format, ...);
#endif