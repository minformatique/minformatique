collatz.elf: collatz.c
	cc -O0 -g -Wall collatz.c -o collatz_debug.elf
	cc -O3 -Wall collatz.c -o collatz.elf

collatz.exe: collatz_w.c
	clang.exe -O0 -g -Wall collatz_w.c -o collatz_debug.elf
	clang.exe -O3 -Wall collatz_w.c -o collatz.exe

linux: collatz.elf
	echo "Compilation de collatz.elf achevée."

windows: collatz.exe
	echo "Compilation de collatz.exe achevée."

clean:
	# Suppression des fichier Windows
	rm -f collatz.exe collatz_debug.exe
	# Suppression des fichiers Linux
	rm -f collatz.elf collatz_debug.elf
