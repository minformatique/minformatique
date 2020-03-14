/*
Le fichier header utilisé pour la librairie pile. C'est l'occasion de détailler
davantage comment se tructurent ces fichiers headers

Contributeurs : Rezal P18
*/

/*

                              Headers - 2**

Les fichiers headers ("en-tête") en C sont des fichiers d'interface. Leur but
est de décrire le contenu d'une librairie afin que votre code sache comment
l'utiliser. La syntaxe d'un fichier header est la même que celle d'un fichier
source en C, mais attention : un fichier header ne fait que décrire le contenu
d'une librairie, il ne doit pas contenir d'implémentation. Cela est moins le cas
en C++.

Les fichiers headers sont des fichiers de textes lisibles par un humain, si
vous le souhaitez vous pouvez d'ailleurs regarder le contenu de fichiers headers
de librairie que vous utilisez souvent (string.h, stdio.h etc...), mais notez
que les headers de ces librairies vont souvent être assez complexes.

En plus de l'interface de la librairie en question, les fichiers headers
contiennent aussi souvent un peu de documentation sur la librairie.
*/

/*

                      Header Include Once Guard - 3***

Souvent au début d'un fichier header vous trouverez un code semblable à ce qui
suit (le ifndef - define et endif à la fin du fichier). Le but de ce code est
d'éviter des problèmes de références multiples (voire circulaires !) dans les
librairies en C. Si une librairie a réfère à une librairie b et c, mais que dans
son implémentation b réfère aussi à c, alors lorsque vous essaierez de compiler
la librairie a il est probable que vous lisiez deux fois le contenu du header de
c, ce qui peut être problématique si c définit des structures qui doivent être
uniques par exemple.

Pour éviter ce problème on va simplement définir un symbole qui déclare que la
librairie a déjà été importée, comme cela lors d'un passage ultérieur dans ce
header on verra qu'il n'est plus nécessaire de faire l'import.
*/

#ifndef LIB_PILE_TUTORIAL
#define LIB_PILE_TUTORIAL

/*
Comme souvent dans les librairies, certaines valeurs sont définies par défaut
mais ne vont pas forcément convenir à tous les contextes. Afin de permettre de
redefinir ces valeurs par défauts en recompilant la librairie (au cas où) on
peut utiliser des directives du preprocesseur.

La taille en mémoire allouée pour une pile à sa création. Dans la suite du
programme, on aura accès accès à la valeur PILE_TAILLE_DEFAUT qui vaudra 10.
Il est possible de changer cette valeur au moment de la compilation en ligne
de commande.
*/
#ifndef PILE_TAILLE_DEFAUT
#define PILE_TAILLE_DEFAUT 10
#endif

/*
La structure d'un fichier header est semblable à celle du début d'un fichier C,
on commence par définir les imports nécessaires pour utiliser la librairie,
puis les types définis par la librairie (structs, unions, enums etc...),
éventuellement on définit les alias pour ces types puis on finit par définir les
prototypes des routines définies par la librairie.
*/
#include <stdlib.h>

/*
On définit le type Pile. Notez que pour être utilisable dans d'autre fichiers
il faut inclure la définition de la structure dans le header et pas juste la
déclaration.
*/
struct Pile {
  /*
  Un pointeur vers le tableau des pointeurs contenus dans la pile.
  J'ai choisi d'utiliiser des pointeurs bruts (void *) comme type de support
  pour la pile afin d'obtenir un maximum de généricité. Grâce à cette
  implémentation on peut faire des piles de n'importe quel type d'éléments en
  empilant les pointeurs de ces éléments (on peut même en faire une pile
  d'éléments hétérogènes !). Notez cependant que cette implémentation (comparée
  à une autre plus restrictive sur le type des données à empiler) est beaucoup
  plus risquée, notamment parce qu'il n'est jamais possible de prédire le type
  réel de ce qui se trouve derrière le pointeur rendu par pop.

  Dans la suite de ce tutoriel je présenterai une autre façon d'avoir une seule
  implémentation qui couvre plusieurs types possibles (mais l'autre
  implémentation sera plus robuste). Le terme informatique derrière cette notion
  est "l'héritage", ici on exploite allègrement le fait que tous les pointeurs
  en C "héritent" du type void*. Notez cependant que l'héritage est une notion
  introduite par la programmation orientée objet, et que parler d'héritage pour
  les pointeurs bruts est assez impropre.
  */
  void **content;
  /*
  La taille actuelle de la pile, utilse pour retrouver le dernier élément dans
  le tableau content.
  */
  size_t taille_pile;

  /*
  La taille maximale en mémoire allouée pour cette pile, utile afin de savoir
  s'il est nécessaire d'augmenter ou de réduire la taille de la pile.
  */
  size_t taille_pile_max;
};

/*
Initialisation d'une pile.

Le mot réservé extern signifie juste que cette routine est définie à l'exterieur
de la librairie, sinon le compilateur ne vas comprendre ce que vous voulez
faire.
*/
extern int new_pile(struct Pile *instance);

/*
La méthode append de la pile, qui prend en argument la pile sur laquelle on veut
ajouter l'élément et un pointeur vers l'élément que l'on souhaite utiliser et
ajoute l'élément au sommet de la pile.
On aurait aussi pu définir cette fonction comme :

int pile_append(struct Pile *instance, void *element);

mais cela aurait cassé la symétrie avec pile_pop.
*/
extern int pile_append(struct Pile *instance, void **element);

/*
La méthode pop de la pile, qui prend en argument la pile de laquelle on veut
retirer un élément et un pointeur dans lequel on souhaite stocker notre
résultat. Notez que comme le C est pass by value, on n'aurait pas pu définir
cette méthode comme :

int pile_pop(struct Pile *instance, void *element);

car modifier element n'aurait pas permis de modifier le pointeur d'origine, de
plus il n'y a pas de moyen de prévoir de l'exterieur la taille nécessaire pour
stocker la taille d'un élément de la pile, donc on ne pourrait pas copier la
valeur de l'élément sur la pile derrière le pointeur élément car il y aurait
trop de risques que element n'ait pas assez d'espace pour accueillir notre
valeur.
*/
extern int pile_pop(struct Pile *instance, void **element);

/*
Libère l'espace mémoire alloué à la pile, à appeler après avoir fini de
l'utiliser.
*/
extern int free_pile(struct Pile *instance);

// Fin du header include once guard
#endif
