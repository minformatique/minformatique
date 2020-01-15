#ifndef VECTEUR_INCLUDED
#define VECTEUR_INCLUDED

#include "welcome_to_the_abyss.h"

/*

                                  Héritage - 4****

Comme on l'a écrit plus tôt, le but de ce tutoriel est de montrer dans les
grandes lignes comment on peut implémenter un système d'héritage dans un langage
de programmation. Notez que je ne vous dit pas qu'il s'agit là de la façon
d'implémenter de l'héritage en C : le C n'est pas orienté objet objet et si vous
voulez utiliser de l'héritage je vous recommande d'utiliser un langage qui le
supporte vraiment. Ce que je veux vous montrer ici est comment un langage
orienté objet peut implémenter un système d'héritage. La méthode présentée içi
n'est pas la seule possible mais je l'ai choisie car : elle utilise des
pointeurs de fonctions, elle n'est pas trop longue à écrire et c'est celle
qu'utilise le C++.

On définit dans ce qui suit le type Vecteur. Notre implémentation de vecteur
suit l'esprit de celle du C++ et du Rust, il s'agit d'un tableau déclaré en
mémoire heap dont la taille change en fonction des besoin. Ses attributs sont
donc (comme pour le type pile du tutoriel sur la compilation avancée) : un
pointeur vers son espace mémoire en heap (contenu) et sa taille réelle (taille).
Notez que pour me simplifier l'implémentation j'ai décidé que l'espace alloué en
mémoire au tableau serait toujours égal à sa taille, ce qui n'est pas du tout
optimal du point de vue de la vitesse d'exécution, mais cela rend le code plus
simple et plus lisible donc je préfère cette implémentation ici.

Mais un objet contient également des méthodes (sinon à quoi bon hériter ?), et
comme les fonctions sont un type avec lequel on peut travailler en C et même
s'il n'est pas possible d'inclure une fonction comme attribut d'une structure
(cela n'aurait pas de sens pour plusieurs raisons) on peut mettre un pointeur
vers une fonction dans notre structure, que l'on pourra alors appeller comme on
appelerait une méthode.

Attention cependant, la fonction en question reste une fonction simple du C, il
n'y a donc pas de this en C++ ou en Java accessible depuis l'intérieur de la
fonction pour modifier l'objet associé. Pour résoudre cela au moment d'appeler
notre fonction on passera comme premier argument un pointeur vers l'objet depuis
lequel on a appelé notre fonction. Notez que c'est également comme cela que les
appels de méthodes se font dans les langages orientés objets mais le langage
dispose d'une syntaxe plus adaptée qui permet de ne pas faire cette manipulation
soit-même.
*/
struct Vecteur {
  // Un pointeur vers notre vtable
  Methode *vtable;
  // Les attributs de notre objet
  int *contenu;
  size_t taille;
  // Les méthodes de notre objet
  Methode get;
  Methode set;
  Methode remove;
  Methode resize;
  Methode print;
  Methode free;
};

/*

                            Virtual Method Table - 4****

Bon, la promenade est finie, rentrons dans le vif du sujet. Comme vous pouvez le
voir, notre structure comporte un dernier attribut dont je n'ai pas encore
parlé. Il s'agit d'un pointeur vers notre virtual method table ("table des
méthodes virtuelles"), c'est à dire un pointeur vers un tableau contenant toutes
nos méthodes. Dans un vrai langage orienté objet seule une partie des méthodes
se trouveraient dans le tableau, celles que l'on compte remplacer dans les
classes filles (pour des raisons de performance on évite au maximum de mettre
les méthodes dedans), et on signale ces méthodes dans notre code avec le mot
clef "virtual" en C++ par exemple (comme dans "virtual method table").

Comment fonctionne une vtable ?

Le principe général de la vtable est assez simple. Chaque objet d'une classe
contient une référence (ou un pointeur dans notre cas) vers un tableau qui
contient les méthodes que l'objet est censé utiliser. Ainsi, lorsque l'on
appelera la méthode get sur notre objet (içi la première méthode de notre
objet), au lieu d'appeller directement une fonction, notre appel de
vecteur.get() va à son tour appeller la méthode correspondante dans la vtable,
donc faire vecteur.vtable[0]() (puisque get est la première méthode de vecteur).

Mais pourquoi faire cela ?

Notre objectif est de pouvoir ensuite écrire des méthodes (par exemple de tri)
qui fonctionnent sur tous les objets qui éritent de Vecteur et ce sans ce
soucier de leur implémentation particulière. On écrira donc une méthode qui aura
une signature semblable à :

int tri(Vecteur *source, Vecteur *destination);

Mais comme notre fonction tri prend en argument un Vecteur on ne peut pas lui
passer autre chose (même quelque chose qui hérite de Vecteur) sans le caster sur
Vecteur. A l'interieur de la fonction tri on n'aura comme argument possible
qu'un vecteur.

Mais supposons que notre classe qui hérite de vecteur (par exemple string) ait
une méthode get différente (ce qui sera notre cas ici), alors on se retrouvera
face à un problème dans notre fonction tri car on ignore que l'on a affaire à
autre chose qu'à un Vecteur (et on ne souhaite pas avoir à s'en soucier).

Du coup l'idée de la vtable est que même si de l'exterieur vous ne savez pas que
votre Vecteur est en fait une string ce n'est pas grave car l'instance de
string que vous avez récupérée, même castée sur un Vecteur, garde en interne un
pointeur vers les méthodes qui convienne pour son vrai type actuel.

Autrement dit si vous récuperez un vrai vecteur nommé cible, l'appel de get
fera:

cible.get -> cible.vtable[0] -> vecteur_get

Alors qu'avec une string le cheminement sera :

cible.get -> cible.vtable[0] -> string_get

Cela nous permettra ainsi de faire fonctionner notre fonction tri correctement
sur un Vecteur comme sur une string.

Notez que je ne peux pas placer mon constructeur ainsi, non pas que cela soit
abhérant du point de vue logique, mais plutôt parce que mon constructeur est la
fonction responsable d'initialiser les pointeurs de mes méthodes et ma vtable,
donc je ne peux pas la mettre dans ma vtable car cette dernière n'aura pas été
initalisée. Dans un langage orienté objet la syntaxe prendrait cela en charge
elle même, mais en C cela ne me semble pas possible.

Je définis juste en dessous la vtable pour les Vecteurs. Remarquez que dans la
mesure où cette vtable est définie dans le header elle sera accessible dans
n'importe quelle code qui voudra utiliser les Vecteurs (qui est ce que l'on
souhaite), c'est à dire qu'il s'agit d'une variable globale (même si elle est
cachée) de notre programme.
*/

extern Methode vecteur_vtable[6];

/*
Il nous faut tout de même définir les méthodes que l'on appliquera sur les
vecteurs.
*/

// Notre constructeur
extern int vecteur_new(Vecteur *instance);
// Pour accéder à une valeur
extern int vecteur_get(Vecteur *self, int *rang, int *valeur);
// Pour mettre à jour une valeur
extern int vecteur_set(Vecteur *self, int *rang, int *valeur);
// Pour supprimer un chaînon de notre Vecteur. Le trou est comblé directement.
extern int vecteur_remove(Vecteur *self, int *rang, int *valeur);
// Pour ajouter de l'espace au début ou à la fin du tableau.
extern int vecteur_resize(Vecteur *self, int *head, int *tail);
// Pour afficher le contenu du tableau.
extern int vecteur_print(Vecteur *self, int *_junk0, int *_junk1);
// Pour détruire le tableau.
extern int vecteur_free(Vecteur *self, int *_junk0, int *_junk1);

/*
Fin du include once header guard.
*/
#endif
