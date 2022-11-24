target remote localhost:1234
file kernel.elf

hbreak kmain
continue
display/16i $pc
