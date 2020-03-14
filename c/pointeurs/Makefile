pointeurs.elf : pointeurs.c
	# Ici encore je ne mets pas de -Wextra car je ne me sers pas de argc et argv.
	cc -Wall pointeurs.c -o pointeurs.elf

pointeurs.exe : pointeurs_w.c
	clang.exe -Wall pointeurs_w.c -o pointeurs.exe

linux: pointeurs.elf
	echo "Compilation de pointeurs.elf achevée."

windows: pointeurs.exe
	echo "Compilation de pointeurs.exe achevée."
