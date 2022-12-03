#pragma once

#include <printf.h>

#ifndef MOD
#define MOD ""
#endif

#define log(fmt, ...) printk(MOD ": " fmt, __VA_ARGS__)
#define debug(fmt, ...) printk(MOD ": [debug] " fmt, __VA_ARGS__)

void printk(char *fmt, ...);
