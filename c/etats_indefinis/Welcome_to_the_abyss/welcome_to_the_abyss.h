/*
Ce fichier fait partie du tutoriel sur le C. Je l'ai placé dans la partie sur
les états indéfinis bien qu'il ne parle pas vraiment d'états indéfinis, et ce
pour deux raisons principales :
  - Pour décourager les gens de le lire (d'ailleurs il s'agit de mon dernier
  avertissement, faites demi tour maintenant, certaines choses ne peuvent pas
  être oubliées ;-) ).
  - Les manipulations invoquées dans ce fichier, quoique très courantes par
  ailleurs, s'apparentent vraiment à ce qui est fait dans le reste du tutoriel
  sur les états indéfinis.

Si vous êtes toujours ici je vous considère prévenu, donc rentrons dans le vif
du sujet. Ce tutoriel porte essentiellement sur une discussion sur les fonctions
en C, avec trois axes principaux : les pointeurs de fonctions, les vtables et
l'implémentation des fonctions en C.

Le support de la première partie de ce tutoriel est d'écrire un type Vecteur
inpsiré du C++ (ou du Rust) à partir duquel on créera un type Tri et un type
String en recréant de l'héritage. Notez cependant que le type Vecteur que nous
allons définir içi ne sera pas générique, on ne l'écrira que pour des entiers,
l'implémentation d'un type générique ayant déjà été couverte dans le tutoriel
sur la compilation avancée.

Ce tutoriel peut comme d'habitude être compilé à l'aide de l'outil make en
utilisant le Makefile fournit.

Contributeurs : Rezal P18
*/

#ifndef ABYSS_INCLUDED
#define ABYSS_INCLUDED

/*
La taille par défaut de nos vecteurs, piles et files qui peut être changée à la
compilation et sera utilisée un peu partout.
*/
#ifndef TAILLE_DEFAUT
#define TAILLE_DEFAUT 10
#endif

// Utiles à divers moments du programme.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*

                        Les pointeurs de fonctions - 4****
                          (tout le tutoriel sera 4****)

Comme beaucoup de langages de plus haut niveau, le C permet de manipuler les
fonction comme si elles étaient un type défini dans le langage (même si
l'implémentation est clairement différente). Pour déclarer une fonction comme
variable, la syntaxe à utiliser est :

<type de retour> <nom de variable> (<type d'argument> <nom de l'argument> etc);

C'est exactement la syntaxe du prototype d'une fonction ! En fait lorsque l'on
donne le prototype d'une fonction en début de programme on ne fait que déclarer
la variable qui contiendra la fonction pour la suite du programme. Cette
variable sera ensuite initialisée lorsque l'on écrira le code de la fonction
plus loin dans notre programme (contrairement à un langage de script comme
python, votre code source ne sera pas forcément lu de haut en bas). Notez
cependant que la syntaxe du C ne vous permet pas d'initaliser un fonction à
l'intérieur d'une autre fonction. Notez que je ne prononce pas pour l'instant
sur pourquoi on ne peut pas initialiser des fonctions dans d'autres fonctions
(ni sur beaucoup d'autres limitations des fonctions en C) car cela est lié à
leur implémentation.

Tout cela est culturellement intéressant, mais quelles sont les conséquences
pratiques du fait que les fonctions puissent être utilisées comme des types ?

Tout comme les autres types du C, il est possible de définir des pointeurs sur
des fonctions, ce qui permet de créer des mécanismes assez subtils mais très
utiles en pratique. Pour l'instant, je vais juste déclarer des types qui me
seront utiles pour raccourcir la syntaxe dans tous mon programme.

Remarquez que Vecteur est déclaré avant d'être défini, ce qui est tout à fait
possible en C.
*/
typedef struct Vecteur Vecteur;
/*
Le type methode est un pointeur vers une fonction qui prend en argument un
Vecteur et un pointeur vers un int et renvoie un int. L'int renvoyé est un code
d'erreur éventuel.
*/
typedef int (*Methode)(Vecteur *, int *, int *);

/*
Grâce à l'héritage que l'on a écrit, on peut écrire des routines qui
fonctionneront sur tous les types qui héritent de vecteur. La première chose à
laquelle on peut penser est de simplifier les syntaxes des différentes méthodes.
En écrivant des wrapper des différentes fonctions avec des syntaxes plus simples
on verra dans le main que l'on réussit à créer une inversion de dépendances.
*/

extern int get(Vecteur *cible, int rang);
extern int set(Vecteur *cible, int rang, int valeur);
// Je ne peux pas appeller cette fonction remove car le nom est déjà pris.
extern int pop(Vecteur *cible, int rang);
extern int resize(Vecteur *cible, int head, int tail);
extern int print(Vecteur *cible);
// Je ne peux pas appeller cette fonction free car le nom est déjà pris.
extern int collect(Vecteur *cible);

/*
Enfin, pour n'avoir pas fait tout cela pour rien, on écrit une fonction qui
prend en argument un Vecteur et le trie indépendamment de son implémentation
pratique (sauf pour le type Tri car il brise le principe de substitution de
Lyskov).
*/
extern int sort(Vecteur *source, Vecteur *destination);

/*
Fin du include once header guard.
*/
#endif
