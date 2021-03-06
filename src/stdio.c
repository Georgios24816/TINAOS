#ifndef STDIO_C
#define STDIO_C
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
//Define kernel panic
#define krnl_panic(...){make_vga_terminal();cprintf(red, "[KERNEL_PANIC] => Kernel panic in %s at function %s", __FILE__, __LINE__, __func__);cprintf(red, __VA_ARGS__);for(;;);}

char tbuf[32];
char bchars[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

void htoc(uint16_t hex)
{
    printf("0x");
    put_terminal_char(bchars[(hex & 0xF0) >> 4]);
    put_terminal_char(bchars[(hex & 0x0F) >> 0]);
}

void itoa(unsigned i,unsigned base,char* buf) {
	int pos = 0;
	int opos = 0;
	int top = 0;

	if (i == 0 || base > 16) {
		buf[0] = '0';
		buf[1] = '\0';
		return;
	}

	while (i != 0) {
		tbuf[pos] = bchars[i % base];
		pos++;
		i /= base;
	}
	top=pos--;
	for (opos=0; opos<top; pos--,opos++)
		buf[opos] = tbuf[pos];
	buf[opos] = 0;
}

void cprintf(uint8_t color, char* fmt, ...)
{
    uint8_t old_color = terminal_color;
    terminal_color = vga_color_entry(color, white);
    
    va_list ap;
    char *p, *sval;
    int ival;
    double dval;

    va_start(ap, fmt);
    for(p = fmt; *p; p++) {
        if(*p != '%') {
            put_terminal_char(*p);
            continue;
        }
        switch (*++p) {
            case 'c':
                sval = (char)(va_arg(ap, int) & ~0xFFFFFF00);
                put_terminal_char(sval);
                break;
            case 'd':
                ival = va_arg(ap, int);
                printf("%f", ival );
                break;
            case 'f':
                dval  = va_arg(ap, double);
                printf("%f", dval);
                break;
            case 's':
                for(sval = va_arg(ap, char *); *sval; sval++)
                    put_terminal_char(*sval);
                break;
            default:
                put_terminal_char(*p);
                break;
        }
    }
    if(NEW_LINE_AT_END)
        //Add new line
        put_terminal_char('\n');
    va_end(ap); 
    terminal_color = old_color;
}

//Print a string with a given format
void printf(char* fmt, ...)
{
    va_list ap;
    char *p, *sval;
    int ival;
    double dval;

    va_start(ap, fmt);
    for(p = fmt; *p; p++) {
        if(*p != '%') {
            put_terminal_char(*p);
            continue;
        }
        switch (*++p) {
            case 'c':
                sval = (char)(va_arg(ap, int) & ~0xFFFFFF00);
                put_terminal_char(sval);
                break;
            case 'd':
                ival = va_arg(ap, int);
                printf("%f", ival );
                break;
            case 'f':
                dval  = va_arg(ap, double);
                printf("%f", dval);
                break;
            case 's':
                for(sval = va_arg(ap, char *); *sval; sval++)
                    put_terminal_char(*sval);
                break;
            default:
                put_terminal_char(*p);
                break;
        }
    }
    if(NEW_LINE_AT_END)
        //Add new line
        put_terminal_char('\n');
    va_end(ap); 
}


#endif