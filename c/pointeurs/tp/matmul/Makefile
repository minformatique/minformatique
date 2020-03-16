matmul.elf: matmul.c
	cc -Wall -g matmul.c -o matmul.elf

matmul.exe: matmul_w.c
	clang.exe -Wall -g matmul_w.c -o matmul.exe

linux: matmul.elf
	echo "Compilation de matmul.elf achevée."

windows: matmul.exe
	echo "Compilation de matmul.exe achevée."

clean:
	# Suppression des fichiers Windows
	rm -f matmul.exe
	# Suppression des fichiers Linux
	rm -f matmul.elf
