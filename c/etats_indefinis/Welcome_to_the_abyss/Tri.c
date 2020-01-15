/*

                    Principe de substitution de Liskov - 4****

L'implémentation du type Tri. Notez que l'héritage que je fait ici de Vecteur
n'est pas tout à fait correct, en effet le type Tri ne se comporte pas vraiment
comme un vecteur. Si on décidait d'utiliser la routine sort sur un vecteur qui
est en fait un tri on aurait de mauvaises surprises. Pour l'annecdote, je brise
ce que l'on appelle le principe de substitution de Liskov (le L de l'acronyme
"SOLID"), c'est à dire que si S est un sous-type de T alors toute instance de T
peut être remplacée par une instance de S.

Un meilleur choix pour implémenter ce type tri aurait été d'utiliser de la
composition, c'est à dire de définir au sein du type Tri une variable interne
Vecteur dont on se servirait pour implémenter le tri.
*/

/*
################################################################################
################## Première partie du programme : les inclusions ###############
################################################################################
*/
#include "Tri.h"

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

Methode tri_vtable[6] = {&vecteur_get, &tri_set,       &vecteur_remove,
                         &tri_resize,  &vecteur_print, &vecteur_free};

/*
################################################################################
############# Dernière partie du programme : les fonctions annexes #############
################################################################################
*/

int tri_new(Vecteur *self) {
  Tri *this = (Tri *)self;
  this->contenu = calloc(TAILLE_DEFAUT, sizeof(int));
  this->taille = TAILLE_DEFAUT;
  this->vtable = (Methode *)&tri_vtable;
  this->get = this->vtable[0];
  this->set = this->vtable[1];
  this->remove = this->vtable[2];
  this->resize = this->vtable[3];
  this->print = this->vtable[4];
  this->free = this->vtable[5];
  return 0;
}

/*
Ce qui suit est essentiellement de l'implémentation, pas la peine de vous
attarder.
*/

int tri_set(Vecteur *self, int *rang, int *valeur) {
  Tri *this = (Tri *)self;
  // On commence par trouver le rang où l'on doit insérer valeur
  // La bonne valeur si on n'atteint jamais le break
  size_t spot = this->taille;
  for (size_t i = 0; i < this->taille; i++) {
    if (this->contenu[i] > *valeur) {
      spot = i;
      break;
    }
  }
  /*
  On rajoute de la mémoire au début du tableau avec realloc pour pouvoir insérer
  l'élément.
  */
  this->contenu = realloc(this->contenu, (this->taille + 1) * sizeof(int));
  /*
  On recopie toutes les valeurs après le spot en les décalant poour faire de la
  place.
  */
  memmove(this->contenu + spot + 1, this->contenu + spot,
          (this->taille - spot) * sizeof(int));
  // On insère notre élément.
  this->contenu[spot] = *valeur;
  this->taille++;
  return 0;
}

int tri_resize(Vecteur *self, int *head, int *tail) {
  /*
  Notez que cette implémentation est presque un copié collé de celle de Vecteur.
  */
  Tri *this = (Tri *)self;
  if (this->taille + *tail + *head < 0) {
    return 1;
  } else {
    int *new_ptr = malloc((this->taille + *tail + *head) * sizeof(int));
    int offset_dest;
    int offset_src;
    if (*head >= 0) {
      offset_dest = *head;
      offset_src = 0;
    } else {
      offset_dest = 0;
      offset_src = -*head;
    }
    int minus_dest;
    int minus_src;
    if (*tail >= 0) {
      minus_dest = *tail;
      minus_src = 0;
    } else {
      minus_dest = 0;
      minus_src = -*tail;
    }
    memcpy(new_ptr + offset_dest, this->contenu + offset_src,
           (this->taille - minus_src) * sizeof(int));
    /*
    En plus du resize de Vecteur il nous faut en plus mettre les bonnes valeurs
    aux espaces mémoires que l'on a créés avec malloc. Notez que je ne peux pas
    utiliser memset ici car malgré ce que sa signature suggère memset remplit la
    mémoire octet par octet et non pas entier par entier, donc ne fait pas ce
    que je veux içi.
    */
    for (size_t i = 0; i < offset_dest; i++) {
      new_ptr[i] = this->contenu[offset_src];
    }
    size_t new_len = this->taille + *tail + *head;
    for (size_t i = new_len - minus_dest; i < new_len; i++) {
      new_ptr[i] = this->contenu[this->taille - minus_src];
    }
    free(this->contenu);
    this->contenu = new_ptr;
    this->taille = this->taille + *tail + *head;
    return 0;
  }
}
