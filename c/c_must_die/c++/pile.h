#ifndef LIB_PILE_TUTORIAL
#define LIB_PILE_TUTORIAL

#ifndef PILE_TAILLE_DEFAUT
#define PILE_TAILLE_DEFAUT 10
#endif

#include <stdlib.h>

struct Pile {
  void **content;
  size_t taille_pile;
  size_t taille_pile_max;
};


extern int new_pile(struct Pile *instance);
extern int pile_append(struct Pile *instance, void **element);
extern int pile_pop(struct Pile *instance, void **element);
extern int free_pile(struct Pile *instance);

#endif
