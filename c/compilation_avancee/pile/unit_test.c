/*
Le rôle de ce fichier est d'aborder ce que sont les unit tests et accessoirement
de tester la librairie pile.

Contributeurs : Rezal P18
*/

/*
#################################################################################
################## Première partie du programme : les inclusions
################
#################################################################################
*/

/*
Même si on va compiler ce fichier avec le fichier source de la librairie, il
faut déclarer les prototypes de nos fonctions, les structures de données etc...
Sinon le compilateur ne saura pas quoi faire lorsque nous utiliserons dans ce
fichier des routines déclarées dans pile.c.

Notez que j'écris ici le include avec des guillemets. La différence avec les <>
est simplement l'endroit où le compilateur ira chercher le fichier pile.h.
Lorsque l'on écrit le fichier <pile.h> le compilateur va chercher le fichier
dans des emplacements standards prédéfinis (/usr/include entre autres) alors que
lorsque l'on utilise "include.h" le compilateur cherche le fichier d'abord dans
le dossier dans lequel se trouve le fichier unit_test.c avant d'essayer les
emplacements standards.
*/
#include "pile.h"
#include <stdio.h>
#include <string.h>

/*
#################################################################################
################## Deuxième partie du programme : les prototypes
################
#################################################################################
*/

// Pas besoin de prototypes ici, on va juste tester les routines de pile.c

/*
#################################################################################
##################### Troisième partie du programme : le main
###################
#################################################################################
*/

/*

                              Unit test - 3***

Les unit test sont très courant (comprendre obligatoire) en entreprise afin de
vérifier que le travail qui a été effectué ne comporte pas de bugs. Ce que je
vais faire ici ne constitue qu'un unit test très sommaire, souvent on utilise
des librairies dédiées afin d'écrire plus facilement des unit tests rigoureux.

La notion de Unit tests n'est pas du tout limitée au C, on la retrouve dans tous
les langages de programmation. Le but d'un unit test est de vérifier qu'un
morceau de code pris isolément se comporte comme il doit. Par opposition on
trouve aussi les tests d'intégration (integration test pour les non
bilingues ;-) ) dont le rôle est de vérifier que les différents morceaux d'une
application s'accordent bien entre eux.
*/
int main(int argc, char const *argv[]) {
  // uut signifie "unit under test"
  struct Pile uut;

  // On teste d'abord new_pile
  new_pile(&uut);
  if ((uut.taille_pile != 0) || (uut.taille_pile_max != PILE_TAILLE_DEFAUT)) {
    fprintf(stderr, "%s\n", "La routine new_pile n'est pas correcte");
    return 1;
  } else {
    printf("%s\n", "La routine new_pile a passé les tests");
  }

  /*
  Note importante : Pour passer de int[] à void ** il ne suffit pas de faire :
  (void **) &elt1 car en C &elt1 représente l'adresse du début du tableau et pas
  l'adresse de l'adresse du tableau (et l'opérateur &&elt1 n'existe pas car il
  ne définit pas un objet unique). Par suite, on doit passer par un pointeur
  intermédiaire avant d'utiliser notre fonction.

  Cela peut sembler anondin, mais typiquement il m'a fallu presque 2 heures pour
  résoudre ce bug dans le code que vous lisez. Encore une fois le C a des règles
  simples, mais il est très courant de faire une petite erreur qui va causer
  des bugs difficiles à cerner.
  */

  // Test de pile_append, on va voir si le resize marche bien.

  for (size_t i = 0; i < 10; i++) {
    // On n'initialise pas le tableau, peu importe ses valeurs.
    int elt[4];
    int *elt_ptr = elt;
    pile_append(&uut, (void **)&elt_ptr);
  }
  if ((uut.taille_pile != 10) || (uut.taille_pile_max != 20)) {
    fprintf(stderr, "%s\n", "La routine pile_append n'est pas correcte");
    return 2;
  }

  // Si on est arrivé là c'est que tout marche pour append
  printf("%s\n", "La routine pile_append a passé les tests");

  /*
  On initialise le tableau que l'on va passer dans la pile afin de tester pop
  */
  int elt1[4] = {0, 1, 2, 3};
  int *elt1_ptr = elt1;
  pile_append(&uut, (void **)&elt1_ptr);

  int status_pop;
  int *result;
  status_pop = pile_pop(&uut, (void **)&result);
  if (memcmp(result, elt1_ptr, 4 * sizeof(int)) != 0) {
    fprintf(stderr, "%s\n", "La routine pile_pop n'est pas correcte");
    return 3;
  }

  /*
  On regarde si la réduction de taille fonctionne bien
  */
  for (size_t i = 0; i < 10; i++) {
    status_pop = pile_pop(&uut, (void **)&result);
    if (status_pop != 0) {
      fprintf(stderr, "%s\n", "La routine pile_pop n'est pas correcte");
      return 4;
    }
  }
  if ((uut.taille_pile != 0) || (uut.taille_pile_max != 10)) {
    fprintf(stderr, "%s\n", "La routine pile_pop n'est pas correcte");
    return 5;
  }

  /*
  On teste le pop sur pile vide
  */
  status_pop = pile_pop(&uut, (void **)&result);
  if (status_pop != -1) {
    fprintf(stderr, "%s\n", "La routine pile_pop n'est pas correcte");
    return 6;
  }

  // Si on est arrivé là c'est que tout marche pour pop
  printf("%s\n", "La routine pile_pop a passé les tests");

  // On teste enfin free_pile
  free_pile(&uut);
  if ((uut.taille_pile != 0) || (uut.taille_pile_max != 0)) {
    fprintf(stderr, "%s\n", "La routine free_pile n'est pas correcte");
    return 7;
  } else {
    printf("%s\n", "La routine free_pile a passé les tests");
  }

  printf("%s\n", "L'implémentation de pile a passé les tests");
  return 0;
}

/*
#################################################################################
############# Dernière partie du programme : les fonctions annexes
##############
#################################################################################
*/

// Pas utile içi, tout est fait dans le main.
