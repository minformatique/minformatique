# Matrix Multiplication
Le but de ce programme est d'utiliser les pointeurs en C afin d'effectuer un 
produit matriciel.

Pour simplifier l'écriture, dans cet exercice on travaillera uniquement avec 
des matrices de taille 40 x 40 (cela rendra le code plus lisible). Les matrices 
sont initialisées avec des nombres aléatoires au début du programme, donc 
pour tester que votre code fonctionne je propose de simplement vérifier que 
la formule suivante est vérifiée dans votre implémentation du produit 
matriciel :

Pour tout A, B on a : Tr(AB) = Tr(BA).

Vous devez aussi écrire l'implémentation de la fonction trace.

Un détail qui pourrait vous surprendre est que nous avons déclaré nos 
matrices (qui sont des objets de dimension 2) comme des int\*, et pas comme des 
int\*\*. Cela n'est pas une erreur, dans la plupart des librairies 
mathématiques en C c'est ainsi que les matrices sont ordonnées.

Cela vient du fait que le C a du mal à gérer des structures récursives (i.e. 
des listes des listes ou équivalents), donc pour se simplifier la vie on 
aplatit notre matrice en un tableau à une dimension et on fait attention au 
moment où on l'utilise à ne pas faire n'importe quoi. Pour plus 
d'informations, vous pouvez chercher sur internet le terme "Row Major Order", 
ce qui vous expliquera pourquoi cette approche peut améliorer les performances 
des calculs dans certains contextes.
