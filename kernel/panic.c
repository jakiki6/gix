#include <printk.h>

#include "arch.h"

void panic(char *fmt, ...) {
    char print_buffer[4096];

    printk("PANIC PANIC PANIC: ");

    va_list args;
    va_start(args, fmt);
    vsnprintf((char *) &print_buffer, (size_t) -1, fmt, args);
    va_end(args);

    serial_write_string(&print_buffer);

    printk("\n********************************************************************************");

    arch_halt();
}
