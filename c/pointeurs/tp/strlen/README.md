# strlen
La fonction strlen sert à calculer taille d'une chaîne de caractères en C. 
Les chaines de caractère sont un cas spécial dans lequel il est possiblede 
déterminer la taille de la chain seulement à partir du pointeur (sans avoir 
besoin de passer la taille en argument de la fonction).

L'astuce est que dans la spécification du C, il est spécifié qu'une chaîne 
de caractères valide en C doit se terminer par un \0 (i.e. un char dont la 
valeur entière est 0).

Pour trouver le nombre de caractères d'une string (char \*) en C il faut donc 
parcourir la chaîne jusqu'à trouver un 0.

Pour tester votre implémentation, j'ai écrit le main de strlen.c de telle 
sorte que votre implémentation de strlen soit testée contre celle de la 
librairie standard sur tous les mots passés en argument.

Exemple d'utilisation :
>> ./strlen.[elf,exe] rouge foo bar
