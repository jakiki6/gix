NASMFLAGS = -F dwarf -g -f elf64
CFLAGS += -m64 -march=x86-64 -mabi=sysv -mno-80387 -mno-mmx -mno-sse -mno-sse2 -mno-red-zone -mcmodel=kernel -MMD
LDFLAGS += -m elf_x86_64 -z max-page-size=0x1000 -T arch/$(ARCH)/linker.ld

override CFILES := $(shell find kernel -type f -name '*.c') $(shell find arch/$(ARCH) -type f -name '*.c')
override ASFILES := $(shell find arch/$(ARCH) -type f -name '*.S')
override NASMFILES := $(shell find arch/$(ARCH) -type f -name '*.asm')
override OBJ := $(CFILES:.c=.o) $(ASFILES:.S=.o) $(NASMFILES:.asm=.o)
override HEADER_DEPS := $(CFILES:.c=.d) $(ASFILES:.S=.d)

$(KERNEL): $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) -o $@

-include $(HEADER_DEPS)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

%.o: %.asm
	nasm $(NASMFLAGS) $< -o $@

include arch/$(ARCH)/boot/build.mk

.PHONY: $(ARCH)_run
$(ARCH)_run: boot.img
	qemu-system-x86_64 -hda $< -m 2G -no-reboot -serial stdio

.PHONY: $(ARCH)_debug
$(ARCH)_debug: boot.img
	qemu-system-x86_64 -hda $< -m 2G -no-reboot -serial stdio -s -S &
	gdb -x debug.gdb
	killall qemu-system-x86_64

.PHONY: $(ARCH)_clean
$(ARCH)_clean:
	rm -rf $(OBJ) $(HEADER_DEPS) boot.img
