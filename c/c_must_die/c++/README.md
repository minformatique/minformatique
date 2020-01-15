Ce tutoriel présente quelques réflexions sur le C++ vu depuis le C, et tente de
mettre en lumière les innovations que le C++ apporte sur son prédécesseur ainsi
que les défauts que la démarche du C++ amène.

Le support de ce tutoriel (partagé avec celui sur Rust) est d'écrire un
programme qui prend en argument une liste de mots séparés par des retours à la
ligne et renvoie la liste de ces mots triés par ordre alphanumérique toujours
séparés par des retours à la ligne.

Pour l'implémentation de ce programme j'ai fait le choix d'exploiter au maximum
la rétrocompatibilité du C++ avec le C en réutilisant l'implémentation de pile
proposée en C (dans la tutoriel sur la compilation avancée) pour faire mon tri.
Cette démarche n'est pas du tout optimale du point de vue de la qualité du code
ni de l'efficacité du tri mais elle me permet d'aborder des idées plus
intéressantes.

Dans notre fichier en C++ intitulé better_or_worse.cpp on définit trois classe :
une classe Mot qui hérite de la classe string pour stocker les mots passés en
argument (cette classe n'est pas très utile, on pourrait utiliser string
directement), une classe PileCpp qui est un proxy pour faciliter l'utilisation
de la structure Pile définie dans pile.c et pile.h et enfin une classe TriMot
qui nous sert à faire notre tri.

Le tri utilisé est un tri par insertion sur des piles. Il n'est pas très efficace
mais au moins il ne m'a pas pris trop longtemps à implémenter. Le tri repose sur
deux piles : une pile triée et une pile buffer. Plutôt que de faire de longues
phrases je montrer comment fonctionne ce tri sur un exemple : on appelle notre
programme sur les mots ohm, volt et ampere (dans cet ordre).

Etape 0 : Etat initial, notez que Input est FIFO alors que les piles sont LIFO
Input : [ohm, volt, ampere]
Tri : ()
Buffer : ()

Etape 1 : On récupère ohm et, comme la pile triée est encore vide, on l'ajoute
au sommet de tri.
Input : [volt, ampere]
Tri : (ohm)
Buffer : ()

Etape 2 : On récupère volt et on le compare au sommet de la pile (ohm). Comme ohm
vient avant volt dans l'ordre alphanumérique on remet ohm dans la pile trie puis
on ajoute volt au sommet de la pile.
Input : [ampere]
Tri : (ohm, volt)
Buffer : ()

Etape 3 : La pile buffer est vide donc on passe au mot suivant directement.

Etape 4 : On récupère le mot ampere sur l'input. On le compare au sommet de la
pile, or ampere vient avant volt dans l'ordre choisi donc on met volt sur la
pile buffer.
Input : [ampere]
Tri : (ohm)
Buffer : (volt)

Etape 5 : On compare ampere à ohm et comme ampere vient avant ohm on met aussi
ohm sur la pile buffer. Il n'y a plus rien dans la pile Tri donc on y ajoute
ampere.
Input : []
Tri : (ampere)
Buffer : (volt, ohm)

Etape 6 : La pile buffer n'est pas vide, donc on remet son contenu dans la pile
triée toujours en resmectant l'ordre LIFO.
Input : []
Tri : (ampere, ohm, volt)
Buffer : ()

L'input est vide et la pile tri contient bien les mots triés par ordre
alphanumérique.
