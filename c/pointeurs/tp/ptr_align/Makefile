ptr_align.elf: ptr_align.c
	cc -Wall -g ptr_align.c -o ptr_align.elf

ptr_align.exe: ptr_align_w.c
	clang.exe -Wall -g ptr_align_w.c -o ptr_align.exe

linux: ptr_align.elf
	echo "Compilation de ptr_align.elf achevée."

windows: ptr_align.exe
	echo "Compilation de ptr_align.exe achevée."

clean:
	# Suppression des fichiers Windows
	rm -f ptr_align.exe
	# Suppression des fichiers Linux
	rm -f ptr_align.elf
