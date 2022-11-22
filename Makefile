export PATH:=$(shell toolchain/use-it.sh):$(PATH)

.PHONY: all
all: run

.PHONY: run
run: boot.img
	qemu-system-x86_64 -m 2G -hda $< -serial stdio -no-reboot -D log.txt -d cpu_reset,int

.PHONY: debug
debug: boot.img
	qemu-system-x86_64 -m 2G -hda $< -serial stdio -no-reboot -s -S


boot.img: vmgix
	make -C boot all

vmgix:
	make -C kernel all

.PHONY: clean
clean:
	rm -f vmgix boot.img
	make -C boot clean
	make -C kernel clean
