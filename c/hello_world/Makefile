hello_world.elf : hello_world.c
		# argc et argv ne sont pas utilisés dans ce code, mais je n'ai pas envie
		# d'avoir de warnings pour cela donc je ne met pas de -Wextra ici.
		cc -Wall -o hello_world.elf hello_world.c

hello_world.exe : hello_world.c
		clang.exe -Wall -o hello_world.exe hello_world_w.c

linux: hello_world.elf
	echo "Compilation de hello_world.elf achevée."

windows: hello_world.exe
	echo "Compilation de hello_world.exe achevée."
