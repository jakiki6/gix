#pragma once

#include <stdint.h>
#include <macros.h>

typedef struct {
    uint16_t limit_15_0;
    uint16_t base_15_0;
    uint8_t base_23_16;
    uint8_t access;
    uint8_t flags_limit_19_16;
    uint8_t base_31_24;
} PACKED gdt_entry_t;

typedef struct {
    uint16_t limit;
    uint64_t base;
} PACKED gdt_t;

void init_gdt();
