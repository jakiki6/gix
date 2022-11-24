#include <stdint.h>
#include <stddef.h>
#include <macros.h>
#include <printk.h>

#include "mm.h"

void *mm_free_bitmap;
uint64_t mm_max_page;
static uint64_t last_page = 0;

void *mm_alloc_pages(uint64_t count) {
   uint64_t left = count;
   uint64_t page = last_page;

   do {
       if (GET_BIT(mm_free_bitmap, page)) {
           left--;

	   if (left == 0) {
               page = page - count;
               for (uint64_t i = page; i < page + count; i++) {
                   CLR_BIT(mm_free_bitmap, i);
	       }

               last_page = page;
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
