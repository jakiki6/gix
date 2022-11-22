#include <printk.h>

#include "arch.h"
#include "gdt.h"

void kmain() {
    init_gdt();

    printk("initialized GDT and IDT\n");
}
