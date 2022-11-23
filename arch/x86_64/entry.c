#include <stdint.h>
#include <stddef.h>
#include <limine.h>
#include <printk.h>
#include <panic.h>

#include "main.h"
#include "serial.h"

static volatile struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0
};

void _start(void) {
    // early debugging
    serial_init();
    printk("********************************************************************************\n");
    printk("gix v0.0.1\n");

    kmain();
    panic("reached end of kmain\n");
}
