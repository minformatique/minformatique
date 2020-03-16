echo.elf: echo.c
	cc -Wall -g echo.c -o echo.elf

echo.exe: echo_w.c
	clang.exe -Wall -g echo_w.c -o echo.exe

linux: echo.elf
	# Petit test à la volée ;-)
	./echo.elf Compilation de echo.elf achevée.

windows:
	# Petit test à la volée ;-)
	./echo.exe Compilation de echo.exe achevée

clean:
	# Suppression des fichiers Windows
	rm -f echo.exe
	# Suppression des fichiers Linux
	rm -f echo.elf
