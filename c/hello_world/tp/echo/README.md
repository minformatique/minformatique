# echo
Le principe du programme echo est très simple, il affiche (print) tous les arguments que vous lui passez en ligne de commande en les séparant par des espaces.

Exemple :
>> echo rouge foo bar "Hello, World!"
rouge foo bar Hello, World!

Notez que la gestion des guillemets est déjà faite par votre shell (bash sous Linux ou git-bash sous Windows) donc vous n'avez pas à vous en soucier.

Pour vous aider un peu, sachez que vous aurez sans doute besoin d'utiliser le argc et le argv qui sont passés en argument du main (vous pouvez chercher sur internet ce à quoi ils correspondent) et la fonction printf.
