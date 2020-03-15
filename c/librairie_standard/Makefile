librairie_standard.elf: librairie_standard.c
		cc -Wall -o librairie_standard.elf librairie_standard.c

librairie_standard.exe: librairie_standard_w.c
		clang.exe -Wall -o librairie_standard.exe librairie_standard_w.c

linux: librairie_standard.elf
	echo "Compilation de librairie_standard.elf achevée."

windows: librairie_standard.exe
	echo "Compilation de libraire_standard.exe achevée."

clean:
	# Suppression des fichiers inutiles
	rm -f first_lines.txt copy_source.txt
	# Suppression des fichiers Windows
	rm -f librairie_standard.exe
	# Suppression des fichiers UNIX
	rm -f librairie_standard.elf
