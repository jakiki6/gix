#pragma once

#include <stdint.h>
#include <macros.h>

typedef struct {
    uint16_t offset_15_0;
    uint16_t selector;
    uint8_t ist;
    uint8_t type;
    uint16_t offset_31_16;
    uint32_t offset_63_32;
    uint32_t reserved;
} PACKED idt_entry_t;

typedef struct {
    uint16_t limit;
    uint64_t base;
} PACKED idt_t;

void init_idt();
