pgcd.elf: pgcd.c
	cc -g -Wall pgcd.c -o pgcd.elf

pgcd.exe: pgcd_w.c
	clang.exe -g -Wall pgcd_w.c -o pgcd.exe

linux: pgcd.elf
	echo "Compilation de pgcd.elf achevée."

windows: pgcd.exe
	echo "Compilation de pgcd.exe achevée."

clean:
	# Suppression des fichiers Windows
	rm -f pgcd.exe
	# Suppression des fichiers Linux
	rm -f pgcd.elf
