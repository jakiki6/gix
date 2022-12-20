#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <macros.h>
#include <printk.h>
#include <panic.h>

#include "mm.h"

uint8_t *mm_free_bitmap;
uint64_t mm_max_page;
static uint64_t last_page = 0;

// page size is 1<<12 so we reserve slabs of size 1<<n for sizes smaller than a page
static mm_slab_t *slabs[12];

void *mm_alloc_pages(uint64_t count) {
   uint64_t left = count;
   uint64_t page = last_page;

   do {
       if (GET_BIT(mm_free_bitmap, page)) {
           left--;

	   if (left == 0) {
               page = page - count + 1;
               for (uint64_t i = page; i < page + count; i++) {
                   CLR_BIT(mm_free_bitmap, i);
	       }

               last_page = page + count;
	       return (void *) (page << 12);
	   }
       } else {
           left = count;
       }

       page++;
       if (page >= mm_max_page) {
           page = 0;
	   left = count;
       }
   } while (page != last_page);

   return NULL;
}

void mm_free_pages(void *pages, uint64_t count) {
    for (uint64_t i = ((uint64_t) pages) >> 12; i < (((uint64_t) pages) >> 12) + count; i++) {
        SET_BIT(mm_free_bitmap, i);
    }
}

static mm_slab_t *new_slab(uint64_t size, uint16_t count) {
    mm_slab_t *slab = mm_alloc_pages(1);
    slab->size = size;
    slab->count = count;

    int bitmap_size = ceil_div(count, 4096 * 8);
    slab->bitmap = mm_alloc_pages(bitmap_size);
    memset(slab->bitmap, 0xff, bitmap_size << 12);

    int area_size = ceil_div(count * size, 4096);
    slab->area = mm_alloc_pages(area_size);
    memset(slab->area, 0xcc, area_size << 12);

    return slab;
}

/*
static void del_slab(mm_slab_t *slab) {
    mm_free_pages(slab->bitmap, ceil_div(slab->count, 4096 * 8));
    mm_free_pages(slab->area, ceil_div(slab->count * slab->size, 4096));
    mm_free_pages(slab, 1);
}
*/

static void *alloc_slab(mm_slab_t *slab) {
    for (uint64_t i = 0; i < slab->count; i++) {
        if (GET_BIT(slab->bitmap, i)) {
            CLR_BIT(slab->bitmap, i);
	    return slab->area + (slab->count * slab->size);
	}
    }

    return NULL;
}

static void free_slab(mm_slab_t *slab, void *ptr) {
    SET_BIT(slab->bitmap, ((uint64_t) ptr - (uint64_t) slab->area) / slab->size);
}

static void *malloc_big(uint64_t size) {
    void *ptr = mm_alloc_pages(ceil_div(size, 4096) + 1);
    if (ptr == NULL) {
        return ptr;
    }

    mm_obj_t *obj = ptr + 4096 - sizeof(mm_obj_t);
    obj->type = PAGES;
    obj->count_or_slab = ceil_div(size, 4096) + 1;
    
    return ptr + 4096;
}

void *malloc(uint64_t size) {
    if (size > 2048) {
        return malloc_big(size);
    }

    // add mm_obj_t right before our object
    size += sizeof(mm_obj_t);

    // get index into slabs table
    int level = 0;
    for (int i = size; i > 0; i /= 2, level++);

    mm_slab_t *slab = slabs[level];

    void *ptr = alloc_slab(slab);
    if (ptr == NULL) {
        // fallback if slab allocation fails
        return malloc_big(size);
    }

    mm_obj_t *obj = ptr;
    obj->type = SLAB;
    obj->count_or_slab = (uint64_t) slab;

    return ptr + sizeof(mm_obj_t);
}

void free(void *ptr) {
    if (ptr == NULL) {
        panic("tried to free NULL pointer");
    }

    mm_obj_t *obj = ptr - sizeof(mm_obj_t);
    switch(obj->type) {
        case PAGES:
	  mm_free_pages(ptr - 4096, obj->count_or_slab);
	  break;
	case SLAB:
	  free_slab((mm_slab_t *) obj->count_or_slab, ptr);
	  break;
	default:
	  panic("unknown type of slab at 0x%llx: %u", ptr, obj->type);
    }
}

void init_mm() {
    arch_init_mm();

    for (int i = 0; i < 12; i++) {
        slabs[i] = new_slab(1024, 1<<i);
    }
}
