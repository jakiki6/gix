#include <printk.h>
#include <kmalloc.h>

#include "mm.h"
#include "arch.h"
#include "gdt.h"

void kmain() {
    init_gdt();

    init_mm();

    for (int i = 0; i < 10; i++) {
        void *ptr = malloc(1000000);
        printk("0x%llx", ptr);

        free(ptr);
    }
}
