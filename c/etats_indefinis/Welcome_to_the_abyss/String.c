/*
Pour l'implémentation du type String on va faire à peu près la même chose que
pour le type Vecteur, sauf que les méthodes qui ne sont pas redéfinies dans le
type String seront héritées manuellement de Vecteur.

Notez cependant que même si l'interface de Vecteur et String et la même, (ils
ont les mêmes méthodes), l'implémentation sous-jacente est très différente,
notamment parce que le contenu de String est en fait constitué de char et non
d'int.
*/

/*
################################################################################
################## Première partie du programme : les inclusions ###############
################################################################################
*/
#include "String.h"

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

Methode string_vtable[6] = {&string_get,    &string_set,   &string_remove,
                            &string_resize, &string_print, &vecteur_free};

/*
################################################################################
############# Dernière partie du programme : les fonctions annexes #############
################################################################################
*/

int string_new(Vecteur *self) {
  /*
  Le premier problème que l'on rencontre lorsque l'on code le type String est
  qu'un char n'occupe pas le même espace en mémoire qu'un int. pour éviter de
  gâcher de l'espace on va donc n'initialiser que ce dont on a besoin et faire
  des cast là où nécessaire. Notez aussi que comme je sais que self est une
  string je peux faire un cast directement.
  */
  String *this = (String *)self;
  this->contenu = malloc(TAILLE_DEFAUT * sizeof(char));
  this->taille = TAILLE_DEFAUT;
  // On donne à notre chaîne la bonne table.
  this->vtable = (Methode *)&string_vtable;
  this->get = this->vtable[0];
  this->set = this->vtable[1];
  this->remove = this->vtable[2];
  this->resize = this->vtable[3];
  this->print = this->vtable[4];
  this->free = this->vtable[5];
  return 0;
}

/*
Ce qui suit est essentiellement de l'implémentation, pas la peinde de vous y
attarder.
*/

int string_get(Vecteur *self, int *rang, int *valeur) {
  String *this = (String *)self;
  // J'ai besoin de ce cast pour que mon pointeur soit indexé correctement.
  char *str_contenu = (char *)this->contenu;
  if (*rang < this->taille) {
    *valeur = (int)str_contenu[*rang];
    return 0;
  } else {
    return 1;
  }
}

int string_set(Vecteur *self, int *rang, int *valeur) {
  String *this = (String *)self;
  char *str_contenu = (char *)this->contenu;
  if (*rang < this->taille) {
    str_contenu[*rang] = (char)*valeur;
    return 0;
  } else {
    return 1;
  }
}

int string_remove(Vecteur *self, int *rang, int *valeur) {
  String *this = (String *)self;
  char *str_contenu = (char *)this->contenu;
  if (*rang < this->taille) {
    /*
    Deux cas qu'il est plus rapide de traiter : si rang vaut 0 ou self->taille-1
    */
    int head = 0;
    int tail = 0;
    // Je dois utiliser self ici à cause de la signature de get.
    this->get(self, rang, valeur);
    if (*rang == 0) {
      this->contenu =
          realloc(this->contenu + 1, (this->taille - 1) * sizeof(char));
    } else if (*rang == this->taille - 1) {
      this->contenu = realloc(this->contenu, (this->taille - 1) * sizeof(char));
    } else {
      // On sépare ce qui est avant et après l'élément supprimé.
      char avant[*rang];
      char apres[this->taille - *rang];
      // On copie ce qu'il faut garder.
      memcpy(&avant, str_contenu, *rang * sizeof(char));
      memcpy(&apres, str_contenu + *rang + 1,
             (this->taille - *rang - 1) * sizeof(char));
      // On modifie la taille du tableau.
      this->contenu = realloc(str_contenu, this->taille - 1);
      // On réécrit le tableau.
      memcpy(str_contenu, &avant, *rang * sizeof(char));
      memcpy(str_contenu + *rang, &apres,
             (this->taille - *rang - 1) * sizeof(char));
    }
    this->taille--;
    return 0;
  } else {
    return 1;
  }
}

/*
head = le nombre d'éléments ajoutés à l'avant (retirés si négatif)
tail = le nombre d'éléments ajoutés à l'arrière (retirés si négatifs)
*/
int string_resize(Vecteur *self, int *head, int *tail) {
  String *this = (String *)self;
  char *str_contenu = (char *)this->contenu;
  if (this->taille + *tail + *head < 0) {
    /*
    i.e. ce qui a été donné en argument n'a pas de sens la tête du tableau se
    retrouverait après sa queue.
    */
    return 1;
  } else {
    char *new_ptr = calloc(this->taille + *tail + *head, sizeof(char));
    int offset_dest; // Le nombre de 0 que l'on laisse au début de new_ptr
    int offset_src;  // Le nombre de valeurs que l'on ne recopie pas du début
    if (*head > 0) {
      offset_dest = *head;
      offset_src = 0;
    } else {
      offset_dest = 0;
      offset_src = -*head;
    }
    int minus_dest; // Le nombre de valeurs que l'on ne recopie pas de la fin
    if (*tail >= 0) {
      minus_dest = 0;
    } else {
      minus_dest = *tail; // < 0
    }
    /*
    Je n'ai pas la place d'écrire l'appel de fonction qui suit sur une seule
    ligne.
    */
    memcpy(new_ptr + offset_dest, str_contenu + offset_src,
           (this->taille + minus_dest) * sizeof(char));
    free(str_contenu);
    this->contenu = (int *)new_ptr;
    this->taille = this->taille + *tail + *head;
    return 0;
  }
}

int string_print(Vecteur *self, int *_junk0, int *_junk1) {
  String *this = (String *)self;
  char *str_contenu = (char *)this->contenu;
  for (size_t i = 0; i < this->taille; i++) {
    putchar(str_contenu[i]);
  }
  putchar('\n');
  return 0;
}
