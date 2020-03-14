structures_avancees.elf : structures_avancees.c
		cc -Wall -o structures_avancees.elf structures_avancees.c

structures_avancees.exe : structures_avancees_w.c
		clang.exe -Wall -o structures_avancees.exe structures_avancees_w.c

linux: structures_avancees.elf
	echo "Compilation de structures_avancees.elf achevée."

windows: structures_avancees.exe
	echo "Compilation de structures_avancees.exe achevée."
