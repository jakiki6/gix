#pragma once

#include <stdint.h>

extern uint8_t *mm_free_bitmap;
extern uint64_t mm_max_page;

typedef struct {
    uint16_t size;
    uint16_t count;
    uint8_t payload[];
} mm_slab_t;

typedef struct {
    uint16_t count;
} mm_pages_t;

enum mm_obj_type {
    PAGES,
    SLAB
};

typedef struct {
    enum mm_obj_type type;
    uint64_t count_or_slab;
} mm_obj_t;
