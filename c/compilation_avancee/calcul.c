/*
Ce fichier fait partie du tutoriel compilation avancée et est utilisé afin
d'implémenter une calculatrice assez simple. Il contient le code source de
toutes les routines liées au type Calcul déclarées dans calculatrice.h
*/

/*
################################################################################
################## Première partie du programme : les inclusions ###############
################################################################################
*/

#include "calculatrice.h"

/*
################################################################################
################## Deuxième partie du programme : les prototypes ###############
################################################################################
*/

/*
Ils sont déjà déclarés dans calculatrice.h :

extern int new_calc(Calcul *calc);
extern int calc_append(Calcul *calc, Expression *expr);
extern int calc_pop(Calcul *calc, Expression *expr);
extern int free_calc(Calcul *calc);
*/

/*
################################################################################
##################### Troisième partie du programme : le main ##################
################################################################################
*/

/*
Pas de main ici, il se trouve dans calculatrice.c
*/

/*
################################################################################
############# Dernière partie du programme : les fonctions annexes #############
################################################################################
*/

int new_calc(Calcul *calc) {
  // L'initialisation est à peu près la même que pour une expression
  calc->hauteur = 0;
  return new_pile(&(calc->pile));
}

int calc_append(Calcul *calc, Expression *expr) {
  /*
  Je ne vais pas refaire ma digression de expr_append ici, mais on a le même
  problème de copie contre mapping que pour les expressions. Pour revenir sur
  la remarque faite dans calculatrice.h concernant RawSymbole et l'inversion de
  dépendances, je souligne que dans un langage orienté objet comme Java le
  problème que nous avons ne se serait jamais posé, puisque nous aurions
  intuitivement défini notre pile comme une pile d'objet et tout aurait été fait
  par copie.
  */
  Expression *copie_expr = malloc(sizeof(Expression));
  copie_expr->next = expr->next;
  copie_expr->precedence = expr->precedence;
  copie_expr->pile = expr->pile;
  pile_append(&(calc->pile), (void **)&copie_expr);

  // On n'oublie pas d'augmenter la hauteur du calcul.
  calc->hauteur++;
  return 0;
}

int calc_pop(Calcul *calc, Expression *expr) {
  Expression *popped_expr;
  int status = pile_pop(&(calc->pile), (void **)&popped_expr);
  if (status == -1) {
    /*
    Ce status = -1 signifie que l'on essaie de vider une pile vide. Cela ne
    devrait que lorsque l'on atteindra la fin de notre expression, juste après
    avoir résolu notre dernière expression on tentera de l'ajouter au sommet de
    le pile précédente qui n'existe pas, ce qui sonnera la fin du calcul. Sur
    un calcul mal parenthèsé cela signifie aussi que notre programme pourrait
    renvoyer un résultat en ignorant la fin de cae qui aura été donné en entrée
    (s'il y a plus de parenthèses fermantes qu'ouvrantes).
    */
    expr->next = INVALIDE;
    return -1;
  }
  // else...
  expr->next = popped_expr->next;
  expr->precedence = popped_expr->precedence;
  expr->pile = popped_expr->pile;

  // Dernière chose : on met à jour la hauteur du calcul.
  calc->hauteur--;
  return 0;
}

int free_calc(Calcul *calc) {
  calc->hauteur = 0;
  return free_pile(&(calc->pile));
}
