# Au bout du dixième Makefile je commence à en avoir marre, je fais un template à partir de maintenant.
SUJET := network

$(SUJET).elf: $(SUJET).c
	cc -g -Wall $(SUJET).c -o $(SUJET).elf

$(SUJET).exe: $(SUJET)_w.c
	clang.exe -g -Wall $(SUJET)_w.c -o $(SUJET).exe

linux: $(SUJET).elf
	echo "Compilation de $(SUJET).elf achevée."

windows: $(SUJET).exe
	echo "Compilation de $(SUJET).exe achevée."

clean:
	# Suppression des fichiers Windows
	rm -f $(SUJET).exe
	# Suppression des fichiers Linux
	rm -f $(SUJET).elf
