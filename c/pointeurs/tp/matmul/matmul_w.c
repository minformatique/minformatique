/*
################################################################################
################## Première partie du programme : les inclusions ###############
################################################################################
*/

#include <stdio.h>  // Utile pour afficher des messages dans le main
#include <stdlib.h> // Utile pour la génération de matrices aléatoires

/*
################################################################################
################## Deuxième partie du programme : les prototypes ###############
################################################################################
*/

// On multiplie les matrices a et b (de taille 40 x 40) et on écrit le résultat
// dans c.
int matmul(const int *a, const int *b, int *c);
// Utile pour vérifier que notre implémentation du produit matriciel est
// correcte en testant la trace du résultat.
int trace(const int *m);

// Je déclare les matrices dans la portée globale pour permettre aux compilateur
// certaines optimisation qui éviteront au programme de tomber à court de
// mémoire (cela n'arriverait pas ici, mais pour faire bonne forme je prend la
// précaution quand même).
static int A[40 * 40];
static int B[40 * 40];
static int AB[40 * 40];
static int BA[40 * 40];

/*
################################################################################
##################### Troisième partie du programme : le main ##################
################################################################################
*/

int main(int argc, char *argv[]) {
  // On initialise le générateur de nombres aléatoires.
  srand(1);
  printf("%s\n", "Initialisation des matrices");
  // Cette étape risque d'être assez longue parce que l'initialisation n'est pas
  // vectorisée.
  for (size_t i = 0; i < 40 * 40; i++) {
    // On prend le modulo 100 pour éviter l'overflow et les erreurs de calcul.
    A[i] = rand() % 100;
    B[i] = rand() % 100;
  }
  printf("%s\n", "Calcul de AB");
  matmul(A, B, AB);
  printf("%s\n", "Calcul de BA");
  matmul(B, A, BA);
  int trace_ab = trace(AB);
  printf("Trace de AB %d\n", trace_ab);
  int trace_ba = trace(BA);
  printf("Trace de BA %d\n", trace_ba);
  if (trace_ab != trace_ba) {
    printf("%s\n", "Vos deux produits n'ont pas la même trace, votre "
                   "implémentation semble incorrecte");
    return -1;
  }
  printf("%s\n", "Test passé avec succès");
  return 0;
}

/*
################################################################################
############# Dernière partie du programme : les fonctions annexes #############
################################################################################
*/

int matmul(const int *a, const int *b, int *c) {
  // Code à compléter
  return 0;
}

int trace(const int *m) {
  // Code à compléter
  return 0;
}
