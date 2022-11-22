#include <printk.h>

#include "arch.h"

void panic(char *format, ...) {
    printk("PANIC PANIC PANIC: ");

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    printk("\n********************************************************************************\n");

    arch_halt();
}
