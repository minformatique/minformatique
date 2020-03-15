erreurs.elf : erreurs.c
	cc erreurs.c -o erreurs.elf

erreurs.exe : erreurs_w.c
	clang.exe erreurs_w.c -o erreurs.exe

linux: erreurs.elf
	echo "Compilation de erreurs.elf achevée."

windows: erreurs.exe
	echo "Compilation de erreurs.exe achevée."
