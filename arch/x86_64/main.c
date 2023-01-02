#include <printk.h>
#include <kmalloc.h>
#include <paging.h>

#include "mm.h"
#include "arch.h"
#include "gdt.h"
#include "idt.h"

void arch_dg(void *ptr);

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

    void *map = paging_map_create();
    printk("paging map is at 0x%llx\n", map);

    paging_map(map, 0, 0, 4096 * 256);
    arch_dg(map);
}
