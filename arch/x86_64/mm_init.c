#include <stdint.h>
#include <string.h>
#include <macros.h>
#include <limine.h>
#include <panic.h>
#include <printk.h>

#include "mm.h"
#include "mm_init.h"

static volatile struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0
};

void init_mm() {
    uint64_t highest_address = 0;

    struct limine_memmap_entry *entry = *memmap_request.response->entries;
    for (uint64_t i = 0; i < memmap_request.response->entry_count; entry++, i++) {
        if (entry->type == LIMINE_MEMMAP_USABLE && (entry->base + entry->length) > highest_address) {
            highest_address = entry->base + entry->length;
	}
    }

    printk("mm: highest page: 0x%llx\n", highest_address);

    // 1 bit per page
    uint64_t needed_bytes = highest_address >> 15;
    entry = *memmap_request.response->entries;
    for (uint64_t i = 0; i < memmap_request.response->entry_count; entry++, i++) {
        if(entry->type != LIMINE_MEMMAP_USABLE && entry->length < needed_bytes) {
            continue;
	}

        mm_free_bitmap = (void *) entry->base;
	mm_max_page = highest_address >> 12;

	entry->base += needed_bytes;
	entry->length -= needed_bytes;
    }

    if (mm_free_bitmap == NULL) {
        panic("mm: bitmap is NULL\n");
    } else {
        printk("mm: bitmap is at 0x%llx\n", mm_free_bitmap);
    }

    memset(mm_free_bitmap, 0, needed_bytes);

    entry = *memmap_request.response->entries;
    for (uint64_t i = 0; i < memmap_request.response->entry_count; entry++, i++) {
       memset(mm_free_bitmap + (entry->base >> 15), 0xff, entry->length >> 15);
       for (uint64_t j = 0; j < ((entry->length >> 12) & 0b111); j++) {
           SET_BIT(mm_free_bitmap + (entry->base >> 15) + (entry->length >> 15) + 1, j);
       }
    }

    memset(mm_free_bitmap, 0xff, needed_bytes);
}
