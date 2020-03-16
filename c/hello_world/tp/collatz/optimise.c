/*
Version du code optimisée obtenue sur mon PC, reconstituée en relisant le code
en assembleur.
*/

/*
################################################################################
################## Première partie du programme : les inclusions ###############
################################################################################
*/

#include <stdio.h> // utile pour afficher le résultat de Collatz
#include <time.h>  // utile pour calculer le temps de calcul
/*
################################################################################
################## Deuxième partie du programme : les prototypes ###############
################################################################################
*/

// Renvoie la limite de la suite de Collatz de a.
unsigned collatz(unsigned a);

/*
################################################################################
##################### Troisième partie du programme : le main ##################
################################################################################
*/

int main(int argc, char *argv[]) {
  unsigned a = 63728127;
  // D'après Wikipédia, il faut 949 étapes pour que la suite Ua converge vers 1.
  unsigned result;
  clock_t begin_time = clock();
  for (size_t i = 0; i < 1000000; i++) {
    result = 1;
  }
  clock_t end_time = clock();
  printf("Valeur finale obtenue %d - temps de calcul %ld\n", result,
         end_time - begin_time);
  return 0;
}

/*
################################################################################
############# Dernière partie du programme : les fonctions annexes #############
################################################################################
*/

unsigned collatz(unsigned a) {
  // Quelques lignes à base de right shift et de compilateur qui galère.
  return 1;
}
