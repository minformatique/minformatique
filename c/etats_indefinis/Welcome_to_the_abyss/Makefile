Vecteur := Vecteur.h Vecteur.c
Abyss		:= welcome_to_the_abyss.h welcome_to_the_abyss.c
String  := String.h String.c
Tri			:= Tri.h Tri.c
Source 	:= Vecteur.c welcome_to_the_abyss.c String.c Tri.c
out 		:= welcome_to_the_abyss.elf

welcome_to_the_abyss: $(Vecteur) $(Abyss) $(String) $(Tri)
	cc $(Source) -o $(out)

assembleur : welcome_to_the_abyss.c
	cc -O0 -S welcome_to_the_abyss.c -o welcome_to_the_abyss.s
