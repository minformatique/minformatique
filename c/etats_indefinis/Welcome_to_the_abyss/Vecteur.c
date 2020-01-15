/*
################################################################################
################## Première partie du programme : les inclusions ###############
################################################################################
*/
#include "Vecteur.h"

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

/*
On déclare notre vtable dans la protée globale afin qu'elle soit déterminé au
moment de la compilation.
*/
Methode vecteur_vtable[6] = {&vecteur_get,    &vecteur_set,   &vecteur_remove,
                             &vecteur_resize, &vecteur_print, &vecteur_free};

/*
################################################################################
############# Dernière partie du programme : les fonctions annexes #############
################################################################################
*/

int vecteur_new(Vecteur *instance) {
  instance->contenu = malloc(TAILLE_DEFAUT * sizeof(int));
  instance->taille = TAILLE_DEFAUT;
  instance->vtable = (Methode *)&vecteur_vtable;
  instance->get = instance->vtable[0];
  instance->set = instance->vtable[1];
  instance->remove = instance->vtable[2];
  instance->resize = instance->vtable[3];
  instance->print = instance->vtable[4];
  instance->free = instance->vtable[5];
  return 0;
}

/*
Ce qui suit est de l'implémentation, pas la peine de vous y attarder.
*/

int vecteur_get(Vecteur *self, int *rang, int *valeur) {
  if (*rang < self->taille) {
    memcpy(valeur, self->contenu + *rang, sizeof(int));
    return 0;
  } else {
    return 1;
  }
}

int vecteur_set(Vecteur *self, int *rang, int *valeur) {
  if (*rang < self->taille) {
    memcpy(self->contenu + *rang, valeur, sizeof(int));
    return 0;
  } else {
    return 1;
  }
}

int vecteur_remove(Vecteur *self, int *rang, int *valeur) {
  if (*rang < self->taille) {
    /*
    Deux cas qu'il est plus rapide de traiter : si rang vaut 0 ou self->taille-1
    */
    int head = 0;
    int tail = 0;
    self->get(self, rang, valeur);
    if (*rang == 0) {
      size_t new_size = (self->taille - 1) * sizeof(int);
      int buffer[new_size];
      memcpy(&buffer, self->contenu + 1, new_size);
      self->contenu = realloc(self->contenu, new_size);
      memcpy(self->contenu, &buffer, new_size);
    } else if (*rang == self->taille - 1) {
      self->contenu = realloc(self->contenu, (self->taille - 1) * sizeof(int));
    } else {
      // On sépare ce qui est avant et après l'élément supprimé.
      int avant[*rang];
      int apres[self->taille - *rang];
      // On copie ce qu'il faut garder.
      memcpy(&avant, self->contenu, *rang * sizeof(int));
      memcpy(&apres, self->contenu + *rang + 1,
             (self->taille - *rang - 1) * sizeof(int));
      // On modifie la taille du tableau.
      self->contenu = realloc(self->contenu, (self->taille - 1) * sizeof(int));
      // On réécrit le tableau.
      memcpy(self->contenu, &avant, *rang * sizeof(int));
      memcpy(self->contenu + *rang, &apres,
             (self->taille - *rang - 1) * sizeof(int));
    }
    self->taille--;
    return 0;
  } else {
    return 1;
  }
}

/*
head = le nombre d'éléments ajoutés à l'avant (retirés si négatif)
tail = le nombre d'éléments ajoutés à l'arrière (retirés si négatifs)
*/
int vecteur_resize(Vecteur *self, int *head, int *tail) {
  if (self->taille + *tail + *head < 0) {
    /*
    i.e. ce qui a été donné en argument n'a pas de sens la tête du tableau se
    retrouverait après sa queue.
    */
    return 1;
  } else {
    int *new_ptr = calloc(self->taille + *tail + *head, sizeof(int));
    int offset_dest; // Le nombre de 0 que l'on laisse au début de new_ptr
    int offset_src;  // Le nombre de valeurs que l'on ne recopie pas du début
    if (*head >= 0) {
      offset_dest = *head;
      offset_src = 0;
    } else {
      offset_dest = 0;
      offset_src = -*head;
    }
    int minus_src; // Le nombre de valeurs que l'on ne recopie pas de la fin
    if (*tail >= 0) {
      minus_src = 0;
    } else {
      minus_src = -*tail; // Pour conserver la symétrie
    }
    /*
    Je n'ai pas la place d'écrire l'appel de fonction qui suit sur une seule
    ligne.
    */
    memcpy(new_ptr + offset_dest, self->contenu + offset_src,
           (self->taille - minus_src) * sizeof(int));
    free(self->contenu);
    self->contenu = new_ptr;
    self->taille = self->taille + *tail + *head;
    return 0;
  }
}

int vecteur_print(Vecteur *self, int *_junk0, int *_junk1) {
  putchar('[');
  for (size_t i = 0; i < self->taille - 1; i++) {
    printf("%d, ", self->contenu[i]);
  }
  if (self->taille > 0) {
    printf("%d", self->contenu[self->taille - 1]);
  }
  putchar(']');
  putchar('\n');
  return 0;
}

int vecteur_free(Vecteur *self, int *_junk0, int *_junk1) {
  free(self->contenu);
  self->taille = 0;
  self->vtable = 0L;
  return 0;
}
