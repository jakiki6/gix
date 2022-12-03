#pragma once
#include <stdint.h>

#define ALIGNED(x) __attribute__((aligned(x)))
#define PACKED __attribute__((packed))
#define NO_RETURN __attribute__((noreturn))
#define UNUSED(x) ((void) x)
#define CREATE(x) ((x *) kcalloc(sizeof(x)))
#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

#define SET_BIT(x, b) ((uint8_t *) x)[b >> 3] = ((uint8_t *) x)[b >> 3] | (1 << (b & 0b111))
#define CLR_BIT(x, b) ((uint8_t *) x)[b >> 3] = ((uint8_t *) x)[b >> 3] & ~(1 << (b & 0b111))
#define GET_BIT(x, b) (((uint8_t *) x)[b >> 3] & (1 << (b & 0b111)))

#define MEM_OFFSET 0xffffffff80000000

typedef struct list_head {
    struct list_head *next
} list_head_t;
