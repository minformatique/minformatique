/*
Bon... Je sais que j'ai dit que je ne vous embêterai plus, mais j'ai menti. Je
ne sais pas pourquoi vous pensez que savoir comment les fonctions sont
implémentées en C peut vous servir, mais ce n'est probablement pas le cas. J'ai
beau réfléchir, je ne vois vraiment pas en quoi cette connaissance pourrait vous
être utile.

En plus de cela il s'avère que cette explication va faire intervenir beaucoup de
notions assez compliquées que je ne pourrai même pas vous montrer en C parce que
(accrochez vous) le C est trop haut niveau pour permettre ce genre de
manipulation (!!)

Pour vous laisser une dernière chance de repartir maintenant sans avoir les
mains vides, je vous donne le tl;dr : le concept de fonction est géré en
assembleur en utilisant des registres.

Voilà, maintenant que vous savez, vous pouvez repartir !





































... Vous êtes toujours là ? ...




































Bon, vous ne pourrez pas dire que je ne vous aurais pas prévenu.
*/

#include <stdio.h>
/*

                  Les fonctions ne sont pas un type - 4****

J'ai dit au cours du tutoriel précédent que les fonctions pouvaient être
utilisées comme des types en C, et que par voie de fait on peut utiliser des
pointeurs sur les fonctions. Mais en réalité cette assertion n'est pas tout à
fait correct. Comme vous vous en doutez les fonctions sont assez à part en C :
vous ne pouvez pas les initialiser comme vous le voulez, vous ne pouvez pas en
créer pendant l'exécution de votre code etc... En fait à part utiliser des
pointeurs sur les fonctions, vous ne pouvez pas en faire grand chose. Pour comprendre cela, regardons ce qu'il y a à l'interieur d'une fonction en C.
*/

int main(int argc, char const *argv[]) {
  // Regardons la taille de la fonction printf
  printf("Taille de printf : %ld octet(s)\n", sizeof(printf));
  /*
  A l'exécution sur ma machine j'obtient :

  Taille de printf :  octet(s)

  Comment cela est-ce possible ? 1 octet est la taille d'un char, comment peut-on stocker toutes les informations d'une fonction dans un seul caractère ?

  En fait, les fonctions en C occupent bien plus d'un octet en mémoire, cette valeur de 1 octet (que je n'ai pas trouvée documentée où que ce soit) est sans doute une façon de dire qu'il ne faut pas manipuler les fonctions directement. En réalité, les fonctions sont une classe très particulière de pointeurs :
  */
  printf("Pointeur de printf : %p\n", printf);

  /*
  Une question que l'on peut alors légitimement se poser est : Vers quoi pointe une fonction en C ? Et pourquoi le langage ne semble pas vouloir que je manipule les fonctions ainsi ?

  Regardons donc ce qui se trouve derrière le pointeur de printf :
  */
  char *printf_ptr = (void *)printf;
  printf("Contenu derrière printf : %s\n", printf_ptr);

  /*
  Hmmm... Pas très instructif n'est-ce pas ?

  En fait ce qui ce trouve derrière le pointeur de printf n'est pas très exploitable depuis le C, comme vous allez le voir ensuite. Pour mieux comprendre pourquoi, nous allons devoir descendre en dessous du C et examiner le code en assembleur produit par la compilation de notre source en C. Le fichier C que nous allons compiler (fournit dans le dossier contenant ce fichier) est simple.c pour obtenir le code en assembleur correspondant utilisez soit l'outil make si vous disposez du compilateur gcc, soit le compilateur de votre choix. La commande make est make simple.

  Attention lorsque vous compilez votre code en C pour obtenir de l'assembleur, plusieurs points sont à garder en mémoire :
   - Suivant la machine que vous utilisez l'assembleur utilisé sera différent. Un ordinateur classique utilise le jeu d'instruction x86_64 pour lequel plusieurs syntaxes d'assembleur sont disponibles (Intel, AT&T etc...) alors qu'un raspberry pi utilise le jeu d'instruction ARM (probablement aarch64) qui a un assembleur complètement différent.
   - N'oubliez pas d'utiliser le flag -fverbose-asm (ou équivalent) pour que le compilateur place dans votre des commentaires expliquant le lien entre votre code en C et l'assembleur obtenu. L'assembleur est déjà assez difficile à lire comme cela, ne vous rendez pas la tache plus ardue inutilement.
   - DESACTIVEZ LES OPTIMISATIONS ! Sur certains jeu d'instruction (ceux dits RISC en particulier) le compilateur va utiliser des heuristiques très complexes pour que votre code s'exécute le plus vite possible, et vous risquez de ne pas reconnaitre votre programme après ces optimisations.

   J'ai placé dans ce dossier un fichier simple.c que vous pourrez compiler vers son code en assmebleur en utilisant make simple. En lisant le code en assembleur obtenu vous vous apercevrez certainement de deux chose :
    - C'est absolument incompréhensible. En fait GCC est beaucoup plus fort que vous en assembleur et aime bien construire son code correctement, pour cela il rajoute plein de sections à votre code que vous ne comprenez pas vraiment et qui ne sont pas fondamentalement utiles.
    - Essayer de vous expliquer comment fonctionne les appels de fonctions en C à partir d'un code source en assembleur incompréhensible n'est pas vraiment une bonne idée. Et je suis d'accord avec vous. Pour remédier à cela j'ai écrite en m'inspirant de ce que fait simple.s un code en assembleur plus_simple.s qui explique comment fonctionnent les appels de fonctions en C. Après avoir lu plus_simple.s vous pourrez revenir à simple.s et vous le comprendrez certainement mieux (mais pas complètement).

   La suite de l'explication se trouve donc dans le fichier plus_simple.s
  */
  return 0;
}
