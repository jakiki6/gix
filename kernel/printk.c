#include <stdarg.h>

#include <printf.h>
#include <printk.h>
#include <macros.h>

void printk(char *fmt, ...) {
    char print_buffer[4096];

    va_list args;
    va_start(args, fmt);
    vsnprintf((char *) &print_buffer, (size_t) -1, fmt, args);
    va_end(args);

    serial_write_line(&print_buffer);
}
