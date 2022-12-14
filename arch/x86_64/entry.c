#include <stdint.h>
#include <stddef.h>
#include <limine.h>
#include <printk.h>
#include <panic.h>

#include "main.h"
#include "serial.h"

void _start(void) {
    // early debugging
    serial_init();
    printk("********************************************************************************");
    printk("gix v0.0.1");

    kmain();
    panic("reached end of kmain");
}
