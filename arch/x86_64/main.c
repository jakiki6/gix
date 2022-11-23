#include <printk.h>

#include "arch.h"
#include "gdt.h"
#include "mm.h"

void kmain() {
    init_gdt();

    init_mm();

    printk("initialized GDT and IDT\n");
}
