#include <macros.h>
#include <kmalloc.h>

#include "idt.h"
#include "arch.h"

idt_t *idt_desc;

static void bake_entry(idt_entry_t *entry, void *offset, uint16_t selector, uint8_t ist, uint8_t is_trap) {
    entry->offset_15_0 = ((uint64_t) offset) & 0xffff;
    entry->selector = selector;
    entry->ist = ist;
    entry->type = 0x8e | (is_trap & 0x01);
    entry->offset_31_16 = (((uint64_t) offset) >> 16) & 0xffff;
    entry->offset_63_32 = (((uint64_t) offset) >> 32) & 0xffffffff;
}

void init_idt() {
    idt_desc = malloc(sizeof(idt_t));
    idt_desc->base = (uint64_t) malloc(sizeof(idt_t) * 256);
    idt_desc->limit = 4095;

    idt_entry_t *entry = (idt_entry_t *) idt_desc->base;
    for (int i = 0; i < 256; i++) {
        bake_entry(entry++, &arch_isr_unused, 0x08, 0, 0);
    }

    arch_load_idt(idt_desc);
}
