#include <stdint.h>

#include "arch.h"

void arch_outb(uint16_t port, uint8_t val) {
	__asm__ volatile ("outb %0, %1"::"a"(val), "Nd"(port));
}

void arch_outw(uint16_t port, uint16_t val) { 
        __asm__ volatile ("outw %0, %1"::"a"(val), "Nd"(port));     
}

uint8_t arch_inb(uint16_t port) {
	uint8_t ret;
	__asm__ volatile ("inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port));
	return ret;
}

uint16_t arch_inw(uint16_t port) {            
        uint16_t ret;
        __asm__ volatile ("inw %1, %0" 
                   : "=a"(ret) 
                   : "Nd"(port)); 
        return ret;
}

void arch_halt() {
	arch_interrupts_disable();
	while (1) {
		__asm__ volatile ("hlt");
	}
}

void arch_interrupts_enable() {
        __asm__ volatile("sti");
}

void arch_interrupts_disable() {
	__asm__ volatile("cli");
}

unsigned long arch_are_interrupts_enabled() {
	unsigned long flags;
	__asm__ volatile ("pushf\n\t"
		"pop %0"
		: "=g"(flags));
	return flags & (1 << 9);
}

void arch_nmi_enable() {
	arch_outb(0x70, arch_inb(0x70) & 0x7F);
}
 
void arch_nmi_disable() {
	arch_outb(0x70, arch_inb(0x70) | 0x80);
}

void arch_cpuid(int code, uint32_t *a, uint32_t *d) {
	__asm__ volatile ("cpuid" : "=a"(*a), "=d"(*d) : "0"(code) : "ebx", "ecx");
}

uint64_t arch_rdtsc() {
	uint64_t ret;
	__asm__ volatile ("rdtsc" : "=A"(ret));
	return ret;
}

uint64_t arch_read_cr0() {
	uint64_t val;
	__asm__ volatile ("mov %%cr0, %0" : "=r"(val));
	return val;
}

void arch_write_cr0(uint64_t val) {
	__asm__ volatile ("mov %0, %%cr0" : "=r"(val));
}

uint64_t arch_read_cr2() {    
        uint64_t val;
        __asm__ volatile ("mov %%cr2, %0" : "=r"(val));
        return val;
}

uint64_t arch_read_cr4() {    
        uint64_t val;
        __asm__ volatile ("mov %%cr4, %0" : "=r"(val));
        return val;
}
 
void arch_write_cr4(uint64_t val) {
        __asm__ volatile ("mov %0, %%cr4" : "=r"(val)); 
}

void arch_set_cr3(uint64_t pointer) {
	__asm__ volatile ("mov %0, %%cr3" : "=r"(pointer));
}

void arch_wrmsr(uint64_t msr, uint64_t value) {
	uint32_t low = value & 0xFFFFFFFF;
	uint32_t high = value >> 32;
	__asm__ volatile (
		"wrmsr"
		:
		: "c"(msr), "a"(low), "d"(high)
	);
}

uint64_t arch_rdmsr(uint64_t msr) {
	uint32_t low, high;
	__asm__ volatile (
		"rdmsr"
		: "=a"(low), "=d"(high)
		: "c"(msr)
	);
	return ((uint64_t) high << 32) | low;
}

