# Interpréteur

Le but de ce TP est d'écrire en C à partir de la librairie standard un 
interpréteur pour un langage très basique. Le but de ce projet est de mettre 
en valeur le fait qu'un langage même simple (comme le C) peut servir de base 
pour construire d'autres langages. Le but est également de démystifier la 
façon dont les langages de programmation fonctionnent.

Deux information importantes avant de commencer :
 - Je l'ai déjà écrit ailleurs, mais si l'idée vous vient d'écrire un 
langage de programmation, il ne faut pas tout réécrire de 0 en C ! C'est une 
perte de temps monstrueuse, d'une part parce que beaucoup de notion dont nous 
n'aurons pas besoin içi (lexer, parser et arbre syntaxique notamment) peuvent 
être très difficiles à recoder en C, et d'autre part parce qu'il existe 
déjà des librairies toute prètes qui feront cela mieux que vous (yacc en C, 
ANTLR en Java et SLY en Python notamment).
 - Le langage que je vais décrire plus tard n'est pas vraiment un langage de 
rogrammation, dans la mesure où il n'a pas vraiment de syntaxe. En fait le 
langage est (très) fortement inspiré de l'assembleur. La raison pour laquelle 
j'ai fait cela est que gérer un syntaxe, même très simple, à la main est 
vraiment très difficile. Si certains d'entre vous sont intéressés pour 
définir un langage avec une syntaxe plus complète vous pourrez trouver 
queques ressources là dessus dans le dossier "minformatique" de ce dépôt.

# Le langage

La spécification complète du langage pour lequel vous devez définir un 
interpréteur se trouve dans le fichier LANGUAGE.md (le nom est anglais pour 
aller avec README.md).

# L'interpréteur

Pour écrire un interpréteur pour le langage vous aurez globalement deux 
parties à faire :
 - Une librairie contenant l'implémentation de toutes les instructions
 - Un noyau qui devra charger tout le code, initialiser la mémoire pile et qui 
se chargera d'appeler les bonnes fonctions de la librairie en fonction du code 
qui aura été écrit

Quelques conseils pour implémenter le noyau de l'interpréteur (qui feront 
plus sens si vous avez déjà lu le fichier LANGUAGE.md) :
 - Avant de commencer à exécuter le code dans le fichier, chargez tout le 
fichier ligne par ligne dans un tableau de char \*. Cela vous permettra de 
faire des jump plus facilement.
 - Utilisez une variable qui contienne l'index de la ligne actuelle du script. 
Comme cela pour faire des jump (ou passer d'une ligne à la suivante) vous 
n'aurez qu'à changer la valeur de cet index.
 - Pour les registres, je vous conseille de les créér explicitement dans 
votre programme afin de simplifier les manipulations (i.e. créér des 
variables globales A, B, C et D). Cela vous permettra aussi d'écrire plus 
simplement une fonction qui prenne en argument une chaîne de caractères et 
renvoie le registre concerné.
 - Gérer bien les erreurs partout dans votre programme. Si vous vous laissez 
allé et ne vérifiez pas les code de retour de toutes vos fonctions vous allez 
rapidement vous retrouver face à des situations très obscures. N'hésitez pas 
à afficher des messages d'erreurs sur stderr explicites qui vous aideront à 
retrouver le problème dans votre code.
 - Lorsque vous essayez de lire un argument passé à une instruction qui peut 
être soit un Litteral soit un Register, commencez par vérifier si c'est un 
Register.
 - Si str est un char \*, regardez ce qu'est str + n (où n est un nombre 
entier), le fait de savoir utiliser cela pourra vous aider à simplifier votre 
code.

Enfin, l'utilisation en ligne de commande demandée est assez simple :
 - Appeler l'interpréteur sans arguments en ligne de commande doit renvoyer un 
message qui demande de mettre le script en argument.
 - Appeler l'interpréteur avec au moins 1 argument en ligne de commande doit 
faire exécuter le script (premier argument) par l'interpréteur. Les autres 
arguments seront utilisés par le script.

Quelques scripts (avec un court texte expliquant ce qu'ils font) sont 
disponibles dans le dossier exemple.

Bonne chance ;-)
