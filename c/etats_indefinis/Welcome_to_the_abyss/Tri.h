#ifndef TRI_INCLUDED
#define TRI_INCLUDED

#include "Vecteur.h"
/*
On définit le type tri comme étant un vecteur toujours triée. Les méthodes get,
remove, print et free sont exactement les mêmes que pour le type Vecteur. En
revanche les méthodes set et resize doivent subir quelques modifications :

 - Pour resize, les valeurs qui sont ajoutées à le fin du vecteur sont
initialisées à la dernière valeur du vecteur (si on mettait des zeros le vecteur
ne serait plus trié). De même pour les valeurs ajoutées au début du vecteur qui
sont initialisées à la valeur du  premier élément du vecteur.

 - Pour set, la valeur passée en argument est ajoutée par insertion à sa bonne
place dans la liste. L'argument rang est ignoré.
*/

struct Tri {
  // Un pointeur vers notre vtable
  Methode *vtable;
  // Les attributs de notre objet
  int *contenu;
  size_t taille;
  // Les méthodes de notre objet
  Methode get;
  Methode set;
  Methode remove;
  Methode resize;
  Methode print;
  Methode free;
};

typedef struct Tri Tri;

extern Methode tri_vtable[6];

extern int tri_new(Vecteur *self);
extern int tri_set(Vecteur *self, int *rang, int *valeur);
extern int tri_resize(Vecteur *self, int *head, int *tail);
/*
Fin du include once header guard
*/
#endif
