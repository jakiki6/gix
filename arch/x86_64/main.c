#include <printk.h>

#include "arch.h"
#include "gdt.h"
#include "mm_init.h"
#include "mm.h"

void kmain() {
    init_gdt();

    init_mm();

    for (int i = 0; i < 10; i++) {
        void *ptr = mm_alloc_pages(10);
        printk("0x%llx\n", ptr);

        mm_free_pages(ptr, 10);
    }
}
