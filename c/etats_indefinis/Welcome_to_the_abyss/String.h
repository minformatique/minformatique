#ifndef STRING_INCLUDED
#define STRING_INCLUDED

#include "Vecteur.h"

/*
Nous avons réussi à coder un type Vecteur en utilisant une vtable, maintenant
nous allons voir en quoi cela nous aide à faire un système d'héritage.
Définissons notre type String. Notez que dans la mesure où ceci n'est qu'un
tutoriel qui montre un peu comment fonctionne le système de vtable pour
l'héritage, je ne fais pad tout ce qu'il faudrait pour que l'héritage soit
complet (par exemple, dans notre implémentation il n'est pas possible d'utiliser
l'implémentation d'une méthode de la classe parent depuis la classe enfant si la
classe enfant a remplacé la méthode du parent).

Un autre détail important : le C ne me donne pas vraiment de mécanisme pour
faire du polymorphisme de fonction basé sur l'héritage (pourquoi le ferait-il,
le C n'est pas orienté objet après tout) donc je vais être obligé de mettre la
même signature pour les fonctions de String que pour Vecteur. Donc à chaque fois
que je voudrais utiliser une de mes fonctions sur une String je devrai d'abord
la caster sur un Vecteur quitta à la recaster sur un Vecteur à l'interieur de ma
fonction. Ce n'est pas très grave en pratique mais c'est une autre différence
par rapport à un langage qui comporte une syntaxe dédiée.
*/

struct String {
  /*

                            Position de la vtable - 4****

  Le fait de placer la vtable comme premier argument de ma structure n'est pas
  anodin. Certains langages préfèrent la placer en dernière position (notamment
  le C++) ce qui est un meilleur choix si on veut manipuler directement les
  attributs de notre struture, mais est également plus difficile à implémenter
  en pratique.

  Que l'on place la vtable en première ou dernière place importe peu, ce qui
  compte en revanche est que cette vtable se trouve à un endroit prévisible.
  Dans mon cas je triche un peu : comme String et Vecteur (et Tri par ailleurs)
  ont les mêmes champs au même endroit, lorsque l'on fera notre cast de String
  vers Vecteur tous nos champs resteront bien au bon endroit, c'est à dire
  qu'aller chercher la méthode get en se pensant du type Vecteur (elle serait
  alors au 8 + 8 + 8 = 24ème octet derrière l'adresse de la structure) trouvera
  bien la méthode get à sa place dans le type String (également au 24ème octet).

  Si on avait changé l'ordre des attributs entre String et Vecteur (par exemple
  en inversant get et set) alors en pensant appeler get sur un Vecteur on aurait
  appelé la méthode set de String.

  La raison pour laquelle je dis que je triche est que même si je n'avais pas eu
  de vtable, les programmes que j'ai écrits auraient quand même marchés puisque
  Vecteur, String et Tri sont des types superposables. Tout l'intérêt de la
  vtable est que vous n'avez pas besoin que vos types soient superposables pour
  que l'héritage fonctionne, il suffit que votre vtable se trouve à un endroit
  prévisible de l'objet. Il vous suffit ensuite de faire tous vos appels de
  fonction à travers de votre vtable. Si vous êtes capables de faire cela alors
  vous n'avez plus besoin que Vecteur et String soient superposable, la seule
  chose requise est que vous soyez capable de retrouver vos méthodes dans votre
  vtable (i.e. savoir que get est à l'index etc...).

  Un petit exemple pour clarifier ce qui vient d'être dit : supposons pour
  simplifier que Vecteur et String aient pour définition :

  struct Vecteur {
    Methode *vtable;
    Methode get;  // adresse 0 dans vtable
    Methode set;  // adresse 1 dans vtable
  };

  et (on inverse get et set)

  struct String {
    Methode *vtable;
    Methode set;  // adresse 1 dans vtable
    Methode get;  // adresse 0 dans vtable
  };

  Supposons que l'on écrive :

  String str;
  // *on initialise str*
  Vecteur str_cast = (Vecteur) str;

  Que vaut str_cast.get ? En suivant la logique du C, puisque str_cast est une
  struct, vtable set trouve à l'adresse 8 derrière le pointeur de str_cast. Or
  str_cast a été initialisée comme une string, donc en réalité derrière
  l'adresse 8 de str_cast on trouve str.set, qui n'est pas ce que l'on veut.


                              Les vtable en C++ - 4****

  Mais alors comment le C++ se débrouille t'il de cela ? De ce que j'en ai
  compris la règle qu'utilise le C++ est que si une méthode (par exemple get) se
  trouve à une adresse i (ici 0) dans la vtable du parent, alors cette méthode
  se trouvera à la même adresse i dans la vtable du type enfant. Ici nous avons
  bien respecté cette règle, mais la différence avec le C++ tient dans le fait
  que je sois contraint de faire un cast pour passer mes classes filles dans des
  classes parents.

  Les plus assidus en C++ ne manqueront en effet pas de remarquer que en C++, si
  on écrivait le code :

  String str;
  *on initialise str*
  Vecteur str_cast = (Vecteur) str;

  alors str_cast.get devrait pointer vers la méthode get non pas de la classe
  str mais bien de la classe Vecteur. En fait la façon dont l'héritage
  fonctionne en C++ est un peu différente. Tous les objets qui se trouvent dans
  une classe (même s'ils ont été initialisés dans une autre classe) ont accès à
  la vtable de la classe dans laquelle ils se trouvent actuellement. Donc
  toujours dans notre exemple, str a accès à la vtable de String et str_cast a
  accès à la vtable de Vecteur.

  Vous remarquerez à cet égard que lorsque vous voulez passer un objet String à
  une fonction qui prend en argument un Vecteur en C++ vous ne faites pas de
  cast de String vers Vecteur en argument. Par suite, lorsque votre objet se
  retrouve à l'intérieur de votre fonction, il est toujours dans le type String
  et a toujours accès à la vtable de String, et donc lorsque vous appelez la
  méthode get sur votre objet l'appel n'est pas ambigu : il s'agit de la méthode
  get qui se trouve dans la vtable de String.

  Mais alors, pourquoi ne pas avoir fait pareil en C pour nous le montrer plutôt
  que de faire cette explication ambigüe qui dit tout et son contraire ?

  Parce qu'il ne m'est pas possible en C de passer une String à une fonction
  écrite pour prendre en argument un Vecteur. Le C ne dispose pas de mécanisme
  de polymorphisme, par suite je suis forcé de faire ce cast qui ne fait pas du
  tout la même chose qu'en C++.

  tl;dr : Pour que ce qui est écrit dans ce tutoriel corresponde à ce qui se
  passe en C++, il faut juste que vous considériez que String et Tri ne sont
  jamais castés vers Vecteur, car ce cast ne fait pas du tout la même chose
  qu'en C++.
  */
  Methode *vtable;
  int *contenu;
  size_t taille;
  Methode get;
  Methode set;
  Methode remove;
  Methode resize;
  Methode print;
  Methode free;
};

typedef struct String String;

// Notre vtable pour le type String
extern Methode string_vtable[6];

extern int string_new(Vecteur *self);
extern int string_get(Vecteur *self, int *rang, int *valeur);
extern int string_set(Vecteur *self, int *rang, int *valeur);
extern int string_remove(Vecteur *self, int *rang, int *valeur);
extern int string_resize(Vecteur *self, int *head, int *tail);
extern int string_print(Vecteur *self, int *_junk0, int *_junk1);
// On ne fournit pas de nouvelle définition de free.

/*
Fin du include once header guard
*/
#endif
