abyss : abyss.c
	cc abyss.c -o abyss.elf

simple : simple.c
	cc -S -O0 -fverbose-asm simple.c -o simple.s

plus_simple : plus_simple.s
	as plus_simple.s -o plus_simple.o
	ld -e main plus_simple.o -o plus_simple.elf
	rm plus_simple.o
