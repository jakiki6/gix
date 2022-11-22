target remote localhost:1234
file vmgix

hbreak kmain
continue
display/16i $pc
