/*
################################################################################
################## Première partie du programme : les inclusions ###############
################################################################################
*/

#include <stdio.h>  // Utile pour afficher des informations dans le main
#include <string.h> // Contient l'implémentation de référence de strlen

/*
################################################################################
################## Deuxième partie du programme : les prototypes ###############
################################################################################
*/

// Votre version de strlen, avec un nom différent pour éviter les conflits.
size_t strlen_c(const char *s);

/*
################################################################################
##################### Troisième partie du programme : le main ##################
################################################################################
*/

int main(int argc, char *argv[]) {
  size_t reference;
  size_t calcul;
  if (argc == 1) {
    printf("%s\n", "Passez en argument en ligne de commande les mots sur "
                   "lesquels vous voulez tester votre implémentation, par "
                   "exemple :\n>> ./strlen.[exe,elf] rouge foo bar");
    return 0;
  }
  for (int i = 1; i < argc; i++) {
    reference = strlen(argv[i]);
    calcul = strlen_c(argv[i]);
    printf("Taille de %s : reference %ld - calcul %ld\n", argv[i], reference,
           calcul);
    if (calcul != reference) {
      printf("%s\n",
             "Votre fonction strlen_c ne semble pas correcte, echec du test");
      return -1;
    }
  }
  printf("%s\n", "Test passé avec succès");
  return 0;
}

/*
################################################################################
############# Dernière partie du programme : les fonctions annexes #############
################################################################################
*/

size_t strlen_c(const char *s) {
  // Code à compléter
  return 0;
}
