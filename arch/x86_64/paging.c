#include <stdint.h>
#include <kmalloc.h>
#include <paging.h>
#include <string.h>
#include <printk.h>
#include <macros.h>
#include <arch_consts.h>

void *paging_map_create() {
    void *map = malloc_pages(1);
    memset(map, 0, PAGE_SIZE);

    return map;
}

void paging_map(void *map, uint64_t phys, uint64_t virt, uint64_t size) {
    while (size > 0) {
        printk("0x%llx -> 0x%llx", phys, virt);

        uint64_t l4_index = (virt >> 39) & ((1<<9)-1);
        uint64_t l3_index = (virt >> 30) & ((1<<9)-1);
        uint64_t l2_index = (virt >> 21) & ((1<<9)-1);
	uint64_t l1_index = (virt >> 12) & ((1<<9)-1);

        uint64_t *l4_entry = (uint64_t *) map;
        if (l4_entry[l4_index] == 0) {
            l4_entry[l4_index] = ((uint64_t) malloc_pages(1)) | 0b11;
	    memset((void *) (l4_entry[l4_index] & 0x000ffffffffff000), 0, PAGE_SIZE);
        }

        uint64_t *l3_entry = (uint64_t *) l4_entry[l4_index];
        if (l3_entry[l3_index] == 0) {
            l3_entry[l3_index] = ((uint64_t) malloc_pages(1)) | 0b11;
            memset((void *) (l3_entry[l3_index] & 0x000ffffffffff000), 0, PAGE_SIZE);
        }

        uint64_t *l2_entry = (uint64_t *) l3_entry[l3_index];
        if (l2_entry[l2_index] == 0) {
            l2_entry[l2_index] = ((uint64_t) malloc_pages(1)) | 0b11;
            memset((void *) (l2_entry[l2_index] & 0x000ffffffffff000), 0, PAGE_SIZE);
        }

	uint64_t *l1_entry = (uint64_t *) l2_entry[l2_index];
        l1_entry[l1_index] = (phys & 0x000ffffffffff000) | 0b11;

	size -= PAGE_SIZE;
	phys += PAGE_SIZE;
	virt += PAGE_SIZE;

	if (size > 0x7fffffffffffffff) {
            size = 0;
	}
    }
}

void paging_unmap(void *map, uint64_t virt, uint64_t size) {
    UNUSED(map);
    UNUSED(virt);
    UNUSED(size);
}
