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

/*
################################################################################
################## Première partie du programme : les inclusions ###############
################################################################################
*/
#include "String.h"
#include "Tri.h"
#include "Vecteur.h"
/*
################################################################################
################## Deuxième partie du programme : les prototypes ###############
################################################################################
*/

/*
################################################################################
##################### Troisième partie du programme : le main ##################
################################################################################
*/
int main(int argc, char const *argv[]) {
  /*

          ---> Partie 1 : Utilisation de fonctions comme méthodes <---

  */
  printf("\n%s\n%s",
         "---> Partie 1 : Utilisation de fonctions"
         " comme méthodes <---",
         "(Appuyez sur ENTER pour continuer)");
  getchar();
  Vecteur vec;
  int a = 0;
  int b = 10;
  // On construit notre vecteur
  vecteur_new(&vec);
  // Remarquez la syntaxe, qui ressemble beaucoup à celle des méthodes en OO
  /*
  Ne faites pas trop attention aux arguments des méthodes, ils sont expliqués
  plus tard
  */
  vec.print(&vec, &a, &b);
  vec.resize(&vec, &a, &b);
  vec.print(&vec, &a, &b);
  a = 2;
  vec.set(&vec, &a, &b);
  vec.print(&vec, &a, &b);
  a = 1;
  b = 3;
  vec.set(&vec, &a, &b);
  vec.print(&vec, &a, &b);
  a = 2;
  vec.get(&vec, &a, &b);
  vec.print(&vec, &a, &b);
  printf("%d\n", b);
  a = 1;
  vec.remove(&vec, &a, &b);
  vec.print(&vec, &a, &b);
  printf("%d\n", b);
  vec.print(&vec, &a, &b);
  // On détruit notre vecteur pour éviter les memory leak.
  collect(&vec);

  /*

                  ---> Partie 2 : Inversion de dépendances <---

  */
  printf("\n%s\n%s", "---> Partie 2 : Inversion de dépendances <---",
         "(Appuyez sur ENTER pour continuer)");
  getchar();
  String str;
  /*
  Au lieu de caster mes types fils sur le parent à chaque appel de fonction,
  pour plus de lisibilité je les caste une fois au début sur le type parent.
  */
  Vecteur *str_cast = (Vecteur *)&str;
  string_new(str_cast);
  /*
  Notez que la méthode print prend comme argument un Vecteur, mais pourtant en
  pratique la méthode print qu'elle appelle est string_print et non pas
  vecteur_print (pas évident à voir vu que la première chose qu'elle affiche est
  8 espaces). C'est parce que l'objet str, même casté sur autre chose, garde à
  l'intérieur un pointeur vers sa propre vtable.

  Attention, ce n'est pas ainsi que le cast agirait en C++ (cela est expliqué
  ailleurs dans le tutoriel) !!
  */
  print(str_cast);
  /*
  On augmente la taille de notre String pour qu'elle puisse contenir "Hello
  World"
  */
  if (str.taille < 11) {
    resize(str_cast, 0, 11 - str.taille);
  }
  /*
  Notez qu'en comptant le bit de terminaison Hello_World prend 12 bits et pas
  11, mais notre implémentation des Strings (quoique riche en défauts par
  ailleurs) n'a pas besoin de ce bit de terminaison.
  */
  char *hello = "Hello_World";
  for (size_t i = 0; i < 11; i++) {
    set(str_cast, i, (int)hello[i]);
  }
  print(str_cast);
  a = pop(str_cast, 5);
  print(str_cast);
  printf("Le caractère récupéré est -> %c\n", (char)a);
  collect(str_cast);

  /*

                      ---> Partie 3 : Le type tri <---

  */
  printf("\n%s\n%s", "---> Partie 3 : Le type tri <---",
         "(Appuyez sur ENTER pour continuer)");
  getchar();

  Tri tri;
  Vecteur *tri_cast = (Vecteur *)&tri;
  tri_new(tri_cast);
  /*
  Notez que notre implémentation des tris ne permet pas d'avoir une instance de
  Tri vide, ce qui est un vrai problème pour la routine sort.
  */
  print(tri_cast);
  for (size_t i = 0; i < 5; i++) {
    set(tri_cast, 0, 5 - i);
    print(tri_cast);
  }
  for (size_t i = 0; i < 10; i++) {
    pop(tri_cast, 0);
    print(tri_cast);
  }
  for (size_t i = 0; i < 100; i += 7) {
    set(tri_cast, 0, i % 9);
    print(tri_cast);
  }
  collect(tri_cast);

  /*

              ---> Partie 4 : Une fonction de tri abstraite <---

  */

  printf("\n%s\n%s", "---> Partie 4 : Une fonction de tri abstraite <---",
         "(Appuyez sur ENTER pour continuer)");
  getchar();
  printf("%s\n", "Tri de Vecteurs :");
  Vecteur input;
  vecteur_new(&input);
  resize(&input, 0, 100 - input.taille);
  for (size_t i = 0; i < 100; i++) {
    set(&input, i, (17 * i) % 31);
  }
  printf("\n%s", "En entrée -> ");
  print(&input);
  Vecteur output;
  vecteur_new(&output);
  sort(&input, &output);
  printf("\n%s", "En sortie -> ");
  print(&output);
  collect(&input);
  collect(&output);

  printf("\n%s\n", "Tri de Strings :");
  String sinput;
  Vecteur *sin_cast = (Vecteur *)&sinput;
  string_new(sin_cast);
  if (sinput.taille < 11) {
    resize(sin_cast, 0, 11 - sinput.taille);
  }
  for (size_t i = 0; i < 11; i++) {
    set(sin_cast, i, (int)hello[i]);
  }
  printf("\n%s", "En entrée -> ");
  print(sin_cast);
  String soutput;
  Vecteur *sout_cast = (Vecteur *)&soutput;
  string_new(sout_cast);
  sort(sin_cast, sout_cast);
  printf("\n%s", "En sortie -> ");
  print(sout_cast);
  collect(sin_cast);
  collect(sout_cast);
  // Un dernier retour à la ligne pour l'esthétisme.
  printf("%s\n", "");
  return 0;
}

/*
################################################################################
############# Dernière partie du programme : les fonctions annexes #############
################################################################################
*/

/*

                          Inversion de dépendances - 4****

Remarquez l'inversion de dépendances : dans toutes les fonctions qui suivent on
ne fait jamais référence au types String ou Tri, on se contente de wrapper la
syntaxe peu agréable de nos méthodes par des fonctions simples.

Ce sont les Vecteurs eux-même qui font référence à leur implémentation. Si ce
n'était pas clair, ce qui se passerait normalement si on utilisait les fonction
explicites vecteur_get etc... pour avoir le bon comportement (par exemple pour
le type String) serait (une flèche -> signifie "fait référence à") :

fonction get -> Vecteur -> String -> string_get

Alors qu'ici ce qui se passe est plutôt :

fonction get -> Vecteur <- String -> string_get

car ni la routine get ni le type Vecteur ne font référence au type String (dans
le code qui s'exécute). On a donc inversé la dépendance entre Vecteur et String
(d'où le nom inversion de dépendances).
*/
int get(Vecteur *cible, int rang) {
  int result_buffer;
  cible->get(cible, &rang, &result_buffer);
  return result_buffer;
}

int set(Vecteur *cible, int rang, int valeur) {
  cible->set(cible, &rang, &valeur);
  return 0;
}

int pop(Vecteur *cible, int rang) {
  int buffer;
  cible->remove(cible, &rang, &buffer);
  return buffer;
}

int resize(Vecteur *cible, int head, int tail) {
  cible->resize(cible, &head, &tail);
  return 0;
}

int print(Vecteur *cible) {
  int buffer0;
  int buffer1;
  cible->print(cible, &buffer0, &buffer1);
  return 0;
}

int collect(Vecteur *cible) {
  int buffer0;
  int buffer1;
  cible->free(cible, &buffer0, &buffer1);
  return 0;
}

/*
La fonction de tri qui grâce à notre héritage sommaire fonctionne sur les
Vecteurs comme sur les Strings.
*/
int sort(Vecteur *source, Vecteur *destination) {
  Tri trieur_raw;
  Vecteur *trieur = (Vecteur *)&trieur_raw;
  resize(destination, 0, source->taille - destination->taille);
  tri_new(trieur);
  /*
  Il y a un problème lorsque l'on met le premier élément dans le trieur car un
  trieur ne peut pas être vide (cela serait équivalent à appeler collect sur le
  trieur), donc il faut que j'insère le premier élément puis supprime les zeros
  en faisant attention au fait que mon premier élément peut-être négatif.
  */
  int buffer = get(source, 0);
  set(trieur, 0, buffer);
  for (size_t i = 0; i < TAILLE_DEFAUT; i++) {
    if (buffer > 0) {
      pop(trieur, 1);
    } else {
      pop(trieur, 0);
    }
  }
  for (size_t i = 1; i < source->taille; i++) {
    buffer = get(source, i);
    set(trieur, 0, buffer);
  }
  for (size_t i = 0; i < source->taille; i++) {
    buffer = get(trieur, i);
    set(destination, i, buffer);
  }
  collect(trieur);
  return 0;
}
