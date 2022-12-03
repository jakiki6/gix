#include <stdint.h>
#include <string.h>
#include <macros.h>
#include <limine.h>
#include <panic.h>
#include <printk.h>

#include "mm.h"
#include "mm_init.h"

static char *mem_types[] = {
    "usable",
    "reserved",
    "acpi reclaimable",
    "acpi nvs",
    "bad",
    "bootloader reclaimable",
    "kernel",
    "framebuffer",
    "unknown"
};

static volatile struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0
};

void init_mm() {
    uint64_t highest_address = 0;

    printk("memory map:");
    struct limine_memmap_entry *entry = *memmap_request.response->entries;
    for (uint64_t i = 0; i < memmap_request.response->entry_count; entry++, i++) {
        printk("    addr 0x%llx len 0x%llx type '%s'", entry->base, entry->length, entry->type < 8 ? mem_types[entry->type] : mem_types[8]);
    }

    entry = *memmap_request.response->entries;
    for (uint64_t i = 0; i < memmap_request.response->entry_count; entry++, i++) {
        if (entry->type == LIMINE_MEMMAP_USABLE && (entry->base + entry->length) > highest_address) {
            highest_address = entry->base + entry->length;
	}
    }

    printk("mm: highest page: 0x%llx", highest_address);

    // 1 bit per page
    uint64_t needed_bytes = highest_address >> 15;
    entry = *memmap_request.response->entries;
    for (uint64_t i = 0; i < memmap_request.response->entry_count; entry++, i++) {
        if(entry->type != LIMINE_MEMMAP_USABLE || entry->length < needed_bytes) {
            continue;
	}

        mm_free_bitmap = (void *) entry->base;
	mm_max_page = highest_address >> 12;

	entry->base += needed_bytes;
	entry->length -= needed_bytes;
    }

    if (mm_free_bitmap == NULL) {
        panic("mm: bitmap is NULL");
    } else {
        printk("mm: bitmap is at 0x%llx", mm_free_bitmap);
    }

    memset(mm_free_bitmap, 0, needed_bytes);

    entry = *memmap_request.response->entries;
    for (uint64_t i = 0; i < memmap_request.response->entry_count; entry++, i++) {
       for (uint64_t j = entry->base >> 12; j < (entry->length >> 12); j++) {
           SET_BIT(mm_free_bitmap, j);
       }
    }
}
