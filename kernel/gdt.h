#pragma once

#include <stdint.h>
#include <macros.h>

typedef PACKED struct {
    uint8_t base_31_24;
    uint8_t flags_limit_19_16;
    uint8_t access;
    uint8_t base_23_16;
    uint16_t base_15_0;
    uint16_t limit_15_0;
} gdt_entry_t;

typedef ALIGNED(8) struct {
    uint64_t base;
    uint16_t limit;
} gdt_t;

void init_gdt();
