ARCH=x86_64
KERNEL=kernel.elf

export PATH:=$(shell toolchain/use-it.sh):$(PATH)

CC=$(ARCH)-elf-gcc
LD=$(ARCH)-elf-ld

CFLAGS=-g -O2 -pipe -Wall -Wextra -std=c11 -ffreestanding -I./include -I ./kernel/ -I./arch/$(ARCH)/include -I./arch/$(ARCH)
LDFLAGS=-nostdlib -static

.PHONY: all
all: $(ARCH)_run

.PHONY: clean
clean: $(ARCH)_clean
	rm -f $(KERNEL)

include arch/$(ARCH)/build.mk
