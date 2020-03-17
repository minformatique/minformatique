/*
################################################################################
################## Première partie du programme : les inclusions ###############
################################################################################
*/

#include <stdio.h> // Utile pour afficher des choses dans le main

// Définir Compte et ComptePlafond. Ne pas oublier de faire des typedef.

/*
################################################################################
################## Deuxième partie du programme : les prototypes ###############
################################################################################
*/

Compte compte(const char *titulaire, const unsigned somme);
Compte compten(const char *titulaire);
ComptePlafond comptep(const char *titulaire, const unsigned somme,
                      const unsigned plafond);
// Note : toutes les méthodes qui suivent doivent renvoyer 0 en cas d'echec, 1
// sinon.
int afficher(const Compte c);
int depose(Compte *c, unsigned somme);
int retire(Compte *c, unsigned somme);
int transfert(Compte *src, Compte *dest, unsigned somme);
int transfertp(Compte *src, ComptePlafond *dest, unsigned somme);

/*
################################################################################
##################### Troisième partie du programme : le main ##################
################################################################################
*/

int main(int argc, char *argv[]) {
  Compte den = compte("Denis", 1000);
  Compte vic = compten("Victor");
  int test;

  // On teste la fonction affiche
  test = affiche(den);
  if (!test) {
    printf("%s\n",
           "Que s'est-il passé ? Pourquoi n'a-t-on pas réussi à afficher le "
           "compte de Denis ?\nVérifier que vous avez bien alloué de la "
           "mémoire pour stocker les noms des titulaires des comptes.");
    return -1;
  }
  printf("%s\n", "La fonction affiche semble fonctionner.");

  // On teste la fonction depose
  test = depose(&den, 1000);
  if (!test) {
    printf("%s\n", "Pourquoi n'a-t-on pas réussi à déposer de l'argent sur le "
                   "compte de Denis ?");
    return -1;
  }
  affiche(den);

  printf("%s\n", "La fonction depose semble fonctionner.");

  // On teste la fonction retire
  test = retire(&den, 1000);
  if (!test) {
    printf("%s\n", "Pourquoi n'a-t-on pas réussi à retirer de l'argent sur le "
                   "compte de Denis ?");
    return -1;
  }
  affiche(den);

  affiche(vic);
  test = retire(&vic, 1000);
  if (test) {
    printf("%s\n", "Comment a-t-on pu retirer de l'argent sur le compte (vide) "
                   "de Victor ?");
    return -1;
  }
  affiche(vic);

  printf("%s\n", "La fonction retire semble fonctionner.");

  // Test de la routine transfert
  test = transfert(&den, &vic, 500);
  if (!test) {
    printf("%s\n", "Pourquoi n'a-t-on pas pu transférer de l'argent du compte "
                   "de Denis vers le compte de Victor ?");
    return -1;
  }
  affiche(den);
  affiche(vic);

  test = transfert(&den, &vic, 1000000);
  if (test) {
    printf("%s\n", "Ce transfert d'argent de Denis vers Victor ne devrait pas "
                   "être possible.");
    return -1;
  }
  affiche(den);
  affiche(vic);

  printf("%s\n", "La fonction transfert semble fonctionner.");

  // Test de ComptePlafond
  ComptePlafond tbr = comptep("tbr", 0, 100);

  // Test de transfertp
  test = transfertp(&den, &tbr, 200);
  if (test) {
    printf(
        "%s\n",
        "Le premier transfert de Denis vers TBR n'aurait pas du être possible");
    return -1;
  }
  affiche(den);

  test = transfertp(&den, &tbr, 50);
  if (!test) {
    printf("%s\n",
           "Le second transfert de Denis vers TBR aurait du être possible");
    return -1;
  }
  affiche(den);

  printf("%s\n", "Les comptes avec plafond semblent fonctionner correctement.");
  return 0;
}

/*
################################################################################
############# Dernière partie du programme : les fonctions annexes #############
################################################################################
*/

// Implémentation à compléter.
Compte compte(const char *titulaire, const unsigned somme);
Compte compten(const char *titulaire);
ComptePlafond comptep(const char *titulaire, const unsigned somme,
                      const unsigned plafond);
// Note : toutes les méthodes qui suivent doivent renvoyer 0 en cas d'echec, 1
// sinon.
int afficher(const Compte c);
int depose(Compte *c, unsigned somme);
int retire(Compte *c, unsigned somme);
int transfert(Compte *src, Compte *dest, unsigned somme);
int transfertp(Compte *src, ComptePlafond *dest, unsigned somme);
