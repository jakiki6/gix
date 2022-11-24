#include <printk.h>

#include "arch.h"
#include "gdt.h"
#include "mm_init.h"

void kmain() {
    init_gdt();

    init_mm();

    printk("gdt: initialized GDT\n");
}
