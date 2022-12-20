#include <stdint.h>
#include <kmalloc.h>
#include <panic.h>
#include <macros.h>

#include "traps.h"
#include "arch.h"

void arch_trap_pagefault(trap_frame_t *frame) {
   UNUSED(frame);

   panic("pagefault, address = 0x%llx\n", arch_read_cr2());
}
