#pragma once

void *malloc(uint64_t size);
void free(void *ptr);

void *malloc_pages(uint64_t count);
void free_pages(void *ptr, uint64_t count);
