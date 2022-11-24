#pragma once

void* memmove(void* dstptr, const void* srcptr, uint64_t size);
int memcmp(const void* aptr, const void* bptr, uint64_t size);
void* memset(void* bufptr, int value, uint64_t size);
void* memcpy(void* restrict dstptr, const void* restrict srcptr, uint64_t size);
int memcmpval(void* bufptr, int value, uint64_t size);
