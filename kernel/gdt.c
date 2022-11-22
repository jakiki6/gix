#include "arch.h"
#include "gdt.h"

gdt_entry_t global_gdt_entries[] = {
    { .base_31_24 = 0, .flags_limit_19_16 = 0x00, .access = 0x00, .base_23_16 = 0, .base_15_0 = 0, .limit_15_0 = 0x00 },
    { .base_31_24 = 0, .flags_limit_19_16 = 0xaf, .access = 0x9b, .base_23_16 = 0, .base_15_0 = 0, .limit_15_0 = 0xffff },
    { .base_31_24 = 0, .flags_limit_19_16 = 0xcf, .access = 0x93, .base_23_16 = 0, .base_15_0 = 0, .limit_15_0 = 0xffff },
    { .base_31_24 = 0, .flags_limit_19_16 = 0xaf, .access = 0xfb, .base_23_16 = 0, .base_15_0 = 0, .limit_15_0 = 0xffff },
    { .base_31_24 = 0, .flags_limit_19_16 = 0xcf, .access = 0xf3, .base_23_16 = 0, .base_15_0 = 0, .limit_15_0 = 0xffff }
};

gdt_t global_gdt = {
    .base = (uint64_t) &global_gdt_entries,
    .limit = sizeof(global_gdt_entries) - 1
};

void init_gdt() {
    arch_load_gdt(&global_gdt);
}
