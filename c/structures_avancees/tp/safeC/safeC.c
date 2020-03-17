/*
################################################################################
################## Première partie du programme : les inclusions ###############
################################################################################
*/

#include <stdio.h> // Utile pour afficher des messages dans le main

// Compléter avec la définition de Result_float
// Ne pas oublier de faire un typedef pour Result_float

/*
################################################################################
################## Deuxième partie du programme : les prototypes ###############
################################################################################
*/

Result_float div(const float a, const float b);
float unwrap(const Result_float c);
int match(const Result_float c);

/*
################################################################################
##################### Troisième partie du programme : le main ##################
################################################################################
*/

int main(int argc, char *argv[]) {
  // On teste d'abord le code sur un example qui marche
  float a = 5.36;
  float b = 7.48;
  Result_float c = div(a, b);
  if (match(c)) {
    printf("Valeur réelle : %f, Valeur calculée : %f", a / b, unwrap(c));
  } else {
    printf("%s\n", "Vous devriez pouvoir faire ce calcul, il doit y avoir un "
                   "problème d'implémentation");
    return -1;
  }

  // Un exemple qui ne marche pas
  b = 0.0;
  c = div(a, b);
  if (match(c)) {
    printf("%s\n", "Vous ne devriez pas pouvoir faire ce calcul, il doit y "
                   "avoir un problème d'implémentation");
    return -1;
  } else {
    printf("%s\n", "Le match fonctionne bien, on teste à présent unwrap");
    unwrap(c);
    printf("%s\n", "Vous êtes encore içi ?\nUnwrap aura du interrompre le "
                   "programma en cours (avec un exit probablement).");
    return -1;
  }
  return 0;
}

/*
################################################################################
############# Dernière partie du programme : les fonctions annexes #############
################################################################################
*/

// Implémenation à compléter.
Result_float div(const float a, const float b);
float unwrap(const Result_float c);
int match(const Result_float c);
