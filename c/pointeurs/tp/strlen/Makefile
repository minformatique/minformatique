strlen.elf: strlen.c
	cc -Wall -Wextra -g strlen.c -o strlen.elf

strlen.exe: strlen_w.c
	clang.exe -Wall -Wextra -g strlen_w.c -o strlen.exe

linux: strlen.elf
	echo "Compilation de strlen.elf achevée."

windows: strlen.exe
	echo "Compilation de strlen.exe achevée."

clean:
	# Suppression des fichiers Windows
	rm -f strlen.exe
	# Suppression des fichiers Linux
	rm -f strlen.elf
