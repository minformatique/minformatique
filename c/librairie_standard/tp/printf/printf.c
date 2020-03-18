/*
################################################################################
################## Première partie du programme : les inclusions ###############
################################################################################
*/

#include <stdio.h>  // Contient la fonction putchar (entre autres ...)
#include <string.h> // Contient la fonction strlen pour le main

/*
################################################################################
################## Deuxième partie du programme : les prototypes ###############
################################################################################
*/

// La fonction printf que vous devez implémenter
int printf_c(const char *format, ...);
// La fonction printi pour vous aider à écrire printf
int printi(const int i);

/*
################################################################################
##################### Troisième partie du programme : le main ##################
################################################################################
*/

int main(int argc, char *argv[]) {
  printf_c("%s\n", "Hello, World!");
  for (int i = -5; i < 6; i++) {
    printi(i);
    printf_c("Iteration %i de la boucle", i);
  }
  const char *succes = "Votre implémentation de la fonction printf "
                       "(restreinte) semble correcte.";
  printf_c("La chaîne :\n%s\n comporte %i caractères.", succes,
           (int)strlen(succes));
  return 0;
}

/*
################################################################################
############# Dernière partie du programme : les fonctions annexes #############
################################################################################
*/

int printf_c(const char *format, ...) {
  // Implémentation à compléter.
  return 0;
}

int printi(const int i) {
  // Implémentation à compléter.
  return 0;
}
