#include <printk.h>
#include <kmalloc.h>

#include "mm.h"
#include "arch.h"
#include "gdt.h"
#include "idt.h"

void kmain() {
    init_gdt();

    init_mm();
    // we need malloc for the idt
    init_idt();

    for (int i = 0; i < 10; i++) {
        void *ptr = malloc(10);
        printk("0x%llx", ptr);

        free(ptr);
    }
}
