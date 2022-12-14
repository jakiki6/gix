// see https://gist.github.com/NunoLava1998/3f0bcb3d035015a4db2aa4722a99a7d4

#include <stddef.h>
#include <printk.h>

void* memmove(void* dstptr, const void* srcptr, uint64_t size) {
    unsigned char* dst = (unsigned char*) dstptr;
    const unsigned char* src = (const unsigned char*) srcptr;
    if (dst < src) {
        for (uint64_t i = 0; i < size; i++)
            dst[i] = src[i];
    } else {
        for (uint64_t i = size; i != 0; i--)
            dst[i-1] = src[i-1];
    }
    return dstptr;
}

int memcmp(const void* aptr, const void* bptr, uint64_t size) {
    const unsigned char* a = (const unsigned char*) aptr;
    const unsigned char* b = (const unsigned char*) bptr;
    for (uint64_t i = 0; i < size; i++) {
        if (a[i] < b[i])
            return -1;
        else if (b[i] < a[i])
            return 1;
    }
    return 0;
}

void* memset(void* bufptr, int value, uint64_t size) {
    unsigned char* buf = (unsigned char*) bufptr;
    for (uint64_t i = 0; i < size; i++) {
        buf[i] = value;
    }

    return bufptr;
}

void* memcpy(void* restrict dstptr, const void* restrict srcptr, uint64_t size) {
    unsigned char* dst = (unsigned char*) dstptr;
    const unsigned char* src = (const unsigned char*) srcptr;
    for (uint64_t i = 0; i < size; i++)
        dst[i] = src[i];
    return dstptr;
}

int memcmpval(void* bufptr, int value, uint64_t size) {
    // -1: Nope, not equal.
    // 0: Yes, equal!
    unsigned char* buf = (unsigned char*) bufptr;
    int r;
    for (uint64_t i = 0; i < size; i++) {
        if (buf[i] == value) {
            r = 0;
        }
        if (buf[i] != value) {
            return -1;
        }
    }
    return r;

}
