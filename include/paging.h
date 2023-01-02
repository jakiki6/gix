#pragma once
#include <stdint.h>

void *paging_map_create();
void paging_map_delete(void *map);
void paging_map(void *map, uint64_t phys, uint64_t virt, uint64_t size);
void paging_unmap(void *map, uint64_t virt, uint64_t size);
