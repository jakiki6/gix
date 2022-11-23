#pragma once
#include <stdint.h>

#define ALIGNED(x) __attribute__((aligned(x)))
#define PACKED __attribute__((packed))
#define NO_RETURN __attribute__((noreturn))
#define UNUSED(x) ((void) x)
#define CREATE(x) ((x *) kcalloc(sizeof(x)))
#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

#define MEM_OFFSET 0xffffffff80000000
