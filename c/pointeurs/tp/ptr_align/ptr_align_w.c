/*
################################################################################
################## Première partie du programme : les inclusions ###############
################################################################################
*/

#include <stdio.h> // Utile pour afficher des messages dans le main

/*
################################################################################
################## Deuxième partie du programme : les prototypes ###############
################################################################################
*/

// Prend en argument et pointeur et renvoie 0 s'il est aligné, 1 sinon.
int aligned(const void *ptr);

/*
################################################################################
##################### Troisième partie du programme : le main ##################
################################################################################
*/

int main(int argc, char *argv[]) {
  int entier;
  void *ptr = &entier;
  printf("Adresse du pointeur %p\n", ptr);
  if (aligned(ptr) != 0) {
    printf("%s\n", "A moins que votre compilateur ne se comporte bizarrement, "
                   "ce pointeur est certainement aligné.");
    return -1;
  }
  ptr++;
  printf("Nouvelle adresse %p\n", ptr);
  if (aligned(ptr) == 0) {
    printf("%s\n", "Cette adresse ne semble pas alignée, echec du test.");
    return -1;
  }
  ptr++;
  printf("Nouvelle adresse %p\n", ptr);
  if (aligned(ptr) == 0) {
    printf("%s\n", "Cette adresse ne semble pas alignée, echec du test.");
    return -1;
  }
  ptr++;
  printf("Nouvelle adresse %p\n", ptr);
  if (aligned(ptr) == 0) {
    printf("%s\n", "Cette adresse ne semble pas alignée, echec du test.");
    return -1;
  }
  ptr++;
  printf("Nouvelle adresse %p\n", ptr);
  if (aligned(ptr) != 0) {
    printf("%s\n",
           "Cette adresse devrait à son tour être alignée, echec du test.");
    return -1;
  }
  printf("%s\n", "Test passé avec succès.");
  return 0;
}

/*
################################################################################
############# Dernière partie du programme : les fonctions annexes #############
################################################################################
*/

int aligned(const void *ptr) {
  // Code à compléter
  return 0;
}
