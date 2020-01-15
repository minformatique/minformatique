/*
Un programme en C afin d'expliquer le concept des pointeurs en C.

Pour executer ce fichier, utilisez le Makefile ou bien reproduisez les commandes
manuellement en ligne de commande.

Contributeurs : Rezal P18
*/

/*
################################################################################
################## Première partie du programme : les inclusions ###############
################################################################################
*/
#include <stdio.h>

/*
################################################################################
################## Deuxième partie du programme : les prototypes ###############
################################################################################
*/

int bad_sum(int *array);
int good_sum(int *array, size_t taille);
int oppose(int *array, size_t taille);

/*
################################################################################
##################### Troisième partie du programme : le main ##################
################################################################################
*/

/*

                            Les types en C - 1*

Le C est un language de bas niveau, c'est à dire que le fonctionnement du C
reflète fortement le fonction de la machine sous jacente, contrairement à
d'autres languages comme Python ou Java qui visent au contraire à masquer le
fonctionnement de la machine pour ne présenter que des conceptes abstraits à
l'utilisateur.

La manifestation de ce bas-niveau est le fonctionnement des types en C. Un type
en C est un concept dont la taille peu être représenté de façon fixe en mémoire.
Par exemple, un int occupera 4 octets et un char 1. Un exemple d'objet dont la
taille n'est pas constante en mémoire est la chaine de caractère ("piche"
prendrait au minimum 5 octets en mémoire alors que "min'formatique" en prendrait
au moins 14). On pourrait aussi citer les listes, les arbres et même les
tableaux.

                                pointeurs - 1*

Pour s'abstraire de cette limitation (qui est présente dans la machine elle
même), le C va utiliser la notion de pointeur. Est un pointeur en C est une
adresse mémoire (virtuelle, mais peu importe). Or la mémoire sur votre machine
n'est pas infinie, et on peut à l'avance dire que sur une machine 64bits, une
adresse mémoire prendra au plus ... 64 bits. C'est en partie de là que vient la
dénomination, et c'est aussi ce qui explique les ordinateurs 32 bits ne peuvent
pas avoir plus de 2**32 - 1 = 2GB de RAM.

Le C va ensuite utiliser ces adresses mémoires pour exploiter les données que
l'on y a stockées, permettant ainsi de construire des objets plus complexes
(notamment les tableaux). Des exemples d'utilisation des pointeurs se trouvent
dans le main.

                                tableaux - 1*

Ces pointeurs sont ce qui permet en C de définir des tableaux. La syntaxe pour
utiliser des tableaux en C est très semblable à celle d'un language comme Java,
même si le fonctionnement des tableaux en interne est très différent entre les
deux languages. En fait les tableaux en C ne sont qu'une syntaxe raccourcie pour
manipuler les pointeurs d'une façon plus sûre. Un tableau en C peut être vu
comme un pointeur + une taille, et est beaucoup plus simple à utiliser qu'un
pointeur seul. Notez cependant que cette abstraction est assurée par compilateur
(et pas pendant l'exécution, contrairement à d'autres languages), ce qui
implique certaines contraintes, notamment que les tableaux en C doivent avoir
une taille prévisible lors de la compilation.

Une question qui peut arriver rapidement en lisant cela est : "Pourquoi diable
utiliserais-je des pointeurs en C lorsque les tableaux sont disponibles?". La
réponse à cette question est tout simplement : "Parce que vous n'avez pas le
choix :-)" En effet, il y a beaucoup de cas de figures où en C vous êtes
contraints d'utiliser des pointeurs alors que vous voudriez utiliser des
tableaux. La raison implicite pour laquelle le C vous force à cela est le
concept de tableau n'existe pas pour la machine sous-jacente, elle ne connait
que quelques objets de taille fixe et les adresses mémoire. En fait l'existence
même des tableaux en C n'est qu'un confort qui est créé par le compilateur pour
vous simplifier la vie lorsque vous faites des manipulations simples qui
auraient sinon requis d'utiliser des pointeurs ce qui arrive très souvent en
pratique.

tl;dr : Les types en C sont de taille (en mémoire) fixe et prédéfinie, mais cela
empêche de définir des objets abtraits mais très utiles (notamment les chaînes
de caractères). Pour s'affranchir de cela, le C utilise des pointeurs, qui sont
en fait des adresses mémoires, et des tableaux, qui sont une variante plus
facile des pointeurs et qui est transformée en pointeurs au moment de la
compilation.
*/

int main(int argc, char const *argv[]) {
  /*

                            argv, argc - 1*

  Note : les "const" signifie au compilateur que le code dans le main n'a pas
  le droit de modifier la valeur de argv (cela n'aurait pas de sens, argv
  désigne les arguments en ligne de commande donnés par l'utilisateur.

  Notez aussi que la char *argv[] comme argument de fontion n'existe pas en C,
  il ne s'agit que d'une convention définie uniquement pour la fonction main par
  le compilateur pour vous simplifier la vie.

  Dans le main, argc désigne le nombre de commandes passées en argument du
  programme (i.e. la taille de argv) et argv est un tableau contenant tous ces
  arguments. Notez que argv[0] désigne le chemin relatif pour aller du dossier
  courant à ce fichier executable.
  */

  // Définition d'un simple entier en mémoire.
  int a = 3;
  printf("Valeur de la variable a %d\n", a);

  // La fonction sizeof permet de connaitre la taille d'un objet en mémoire.
  size_t sizea = sizeof(a);

  printf("Taille d'un entier en mémoire %d octets\n", sizeof(a));

  /*
  sizeof est une fonction très pratique qui peut aussi être utilisée
  directement sur un type pour en connaitre la taille (en octets).
  */
  printf("Taille d'un flottant en mémoire %d octets\n", sizeof(float));

  // Déclaration d'un tableau avec des valeurs préremplies
  int tab[3] = {1, 2, 3};

  // Création d'un tableau non initialisé
  int tab_empty[3];
  /*
  Remplissage du tableau, la syntaxe a été reprise dans beaucoup d'autres
  languages.
  */
  tab_empty[0] = 4;
  tab_empty[1] = 5;
  tab_empty[2] = 6;

  printf("Première valeur de tab %d\n", tab[0]);
  printf("Première valeur de tab_empty %d\n", tab_empty[0]);

  /*
  La fonction sizeof fonctionne aussi sur les tableaux mais attention,
  sizeof renvoie toujours une taille en octets et pas en nombre d'éléments.
  */

  printf("Taille de tab %d\n", sizeof(tab));
  printf("Taille de tab_empty %d\n", sizeof(tab_empty));

  // Déclaration d'un pointeur void *
  void *ptr;

  // Les pointeurs sont un type en C, et ont une taille fixe en mémoire
  printf("Taille du pointeur %d\n", sizeof(ptr));

  /*
  Les pointeurs bruts en C (de type void *) ne sont pas utilisés en tant que
  tel, souvent on préférera utiliser un pointeur typé en C afin de donner
  davantage d'information au compilateur sur ce que l'on souhaite faire.
  */

  // Déclaration d'un pointeur qui va vers des entiers.
  int *intptr;

  // Pour utiliser un pointeur en C, plusieurs syntaxes sont possibles

  /*
  Cas 1 : Très fréquent, on initialise le pointeur à partir d'un tableau.
  La syntaxe qui suit signifie que l'on associe le pointeur intptr avec le
  tableau tab, donc la valeur de l'adresse mémoire vers laquelle pointe intptr
  est la première adresse du tableau tab.
  */
  intptr = tab;

  /*
  Le fait d'utiliser des pointeurs typés à un gros avantage, c'est que dans
  la mesure où les entiers ont une taille fixe en mémoire, le compilateur saura
  que pour passer du premier élément du tableau désigné par intptr au deuxième
  il suffit de faire un bon de sizeof(int) = 4 octets. Cela permet d'accéder aux
  éléments du tableau à partir du pointeur comme on le ferait à partir du
  tableau.
  */

  printf("Premier entier trouvé à l'adresse mémoire de intptr %d\n", intptr[0]);
  printf("Deuxième entier trouvé à l'adresse mémoire de intptr %d\n",
         intptr[1]);

  // Attention cependant, un pointeur n'est pas un tableau, et notamment :
  printf("sizeof intptr %d\n", sizeof(intptr));

  /*
  Une conséquence importante de cela est qu'il n'est pas possible de retrouver
  à partir du pointeur seul la taille du tableau vers lequel il pointe. Il n'est
  pas non plus possible de savoir si le pointeur a vraiment été associé à
  quelque chose.
  */

  /*
  Il est également possible de modifier les valeurs du tableau à partir du
  pointeur en utilisant la même syntaxe que plus haut.
  */
  intptr[1] = 11;
  printf("Valeur de tab[1] %d\n", tab[1]);

  /*

                              addressof - 1*

  Une autre syntaxe est également possible pour déclarer un pointeur,
  en utilisant le "&" qui va permettre d'accéder à l'adresse mémoire d'une
  variable. La syntaxe qui suit va associer intptr2 à l'adresse en mémoire de la
  variable a. Remarquez que a n'est pas un tableau (juste un entier), mais cela
  n'est pas un problème, parce que lorsque le programme va aller chercher la
  valeur derrière l'adresse de intptr2 il va effectivement trouver un entier.

  L'operateur & se nomme "addressof" en C.

                            rvalue, lvalue - 4****

  Petite aparté, si vous trouvez qu'il y a un problème de récursion dans le fait
  de stocker les adresses des variables dans d'autres variables (qui ont elles
  aussi des adresses !) pour pouvoir les manipuler, sachez que cela est résolu
  en faisant une différence entre les lvalues et les rvalues, mais je préfère ne
  pas mettre un gros pavé d'explication ici, regardez plutôt sur internet.
  */
  int *intptr2 = &a;

  // On peut toujours afficher la valeur de a ...
  printf("Première valeur derrière intptr2 %d\n", intptr2[0]);

  // ... et la modifier (la syntaxe raccourcie ++ signifie += 1)
  intptr2[0]++;

  /*
  Il existe également une syntaxe opposé au &, c'est le *, qui permet d'accéder
  à la valeur derrière un espace mémoire. Le lien avec la syntaxe pour déclarer
  des pointeurs n'est pas évident, il vaut mieux considérer que ce sont deux
  usages décorrélés du même symbole.
  */
  printf("Valeur trouvée à l'adresse intptr2 %d\n", *intptr2);
  printf("Valeur de a %d\n", a);

  // Notez que la même syntaxe est possible avec un tableau, moyennant un cast:
  int *intptr3 = (int *)&tab_empty;
  printf("Valeur à l'adresse intptr3[0] %d\n", intptr3[0]);

  /*
  Notez que la syntaxe du "*" est assez puissante et permet d'accéder non
  seulement le premier élément du tableau derrière un pointeur, mais aussi les
  suivants.
  */
  printf("Première valeur derrière le pointeur intptr3 %d\n", *intptr3);
  printf("Deuxième valeur derrière le pointeur intptr3 %d\n", *(intptr3 + 1));
  /*
  Le raisonnement derrière cette syntaxe est que dans le fond, intptr3 est juste
  une adresse mémoire, c'est à dire un entier. On peut donc légitimement vouloir
  accéder à la valeur suivante en mémoire (pour parcourir un tableau par
  exemple). Cela étant aller juste à l'adresse suivante n'aurait aucun sens,
  puisque l'on sait que l'entier suivant se trouve sizeof(int) = 4 octets plus
  loin que le premier entier derrière le pointeur en mémoire. Par suite (intptr3
  + i) désigne l'adresse mémoire qui se trouve i longueurs d'entiers plus loin
  en mémoire par rapport à l'adresse de intptr3.

  Notez que l'on a par suite intptr3[i] == *(intptr3 + i), mais la première
  syntaxe est plus courante.
  */

  /*
  D'autres manifestations assez subtiles sont encore possibles sur les pointeurs
  sont possibles, mais nous en avons déjà vu l'essentiel. Passons plutôt à la
  raison principale pour laquelle vous êtes forcés d'utiliser des pointeurs en
  C:

  En C, il est impossible de passer un tableau en argument d'une fonction. De
  même, il est impossible de retourner un tableau en sortie d'une fonction.

  Notez que la restriction n'est pas aussi forte en C++, donc si vous utilisez
  un compilateur C++ pour compiler votre code en C, certaines syntaxes seront
  interpretées en C++ et non en C.

  Par suite, si vous souhaitez faire une manipulation sur un tableau depuis une
  autre fonction, vous serez forcés de passer en argument de la fonction le
  pointeur vers votre tableau, avec toutes les contraintes de manipulation qui
  en découlent.
  */

  int tableau_example[5] = {0, 1, 20, -1, -1};
  printf("%s\n", "Mauvais usage des pointeurs :");
  bad_sum((int *)&tableau_example);

  /*
  Dans le print qui suit, remarquez la division par la taille en octets d'un
  entier afin d'obtenir le nombre d'éléments dans le tableau.
  */
  printf("%s\n", "Meilleur usage des pointeurs :");
  printf("%d\n", good_sum((int *)&tableau_example,
                          sizeof(tableau_example) / sizeof(int)));

  /*

                          Renvoyer un pointeur - 2**

  Il est très rare (et déconseillé) de renvoyer un pointeur depuis une fonction
  en C. Le pattern utilisé à peu près dans tous les cas de figures consiste à
  passer en argument de la fonction un pointeur vers l'adresse d'un objet
  préinitialisé que l'on souhaite modifier, et en renvoyant de la fonction un
  code d'erreur (0 si la fonction a réussi son travail), un code identifiant
  l'erreur sinon (C'est par exemple le cas de la fonction main, qui renvoie 0
  en cas de succès de l'exécution du code).

  La raison pour laquelle retourner des pointeurs à la fin d'une fonction est
  (très) fortement déconseillé est que vous ne pouvez pas renvoyer un pointeur
  vers une variable définie localement à l'interieur de la fonction parce que
  l'espace mémoire vers lequel pointe cette adresse sera invalidé au moment où
  la fonction aura finie de s'exécuter. Pour être plus explicite, à chaque fois
  que votre fonction crée une variable locale elle va la mettre dans un espace
  mémoire (ici le stack) qui sera libéré une fois que la fonction aura fini de
  s'exécuter. Or la valeur de l'adresse inscrite dans votre pointeur sera
  toujours la même, donc vous renverrez de votre fonction une adresse vers un
  espace mémoire qui n'est plus utilisable.

  Le principal cas dans lequel votre pointeur resterait valide est s'il s'agit
  d'un pointeur qui a été déclaré dans la fonction parente (celle qui a appellé
  la fonction depuis laquelle vous souhaitez retourner votre pointeur), mais
  alors il n'est plus utile de renvoyer le pointeur puisqu'il est déjà
  accessible dans la fonction parente...

  Il existe une exception à cette règle, détaillée dans le tutoriel sur la
  compilation avancée, mais elle est source de (très) mauvaises pratiques en C
  et de beaucoup d'autres bugs autrement plus complexes.

  Notez que le C ne comporte pas de mécanisme de gestion d'erreurs comme en
  Python ou Java, et ces codes d'erreur constituent à peu prêt le seul error
  control flow disponible en C, encore une fois parce que la notion n'existe pas
  dans la machine sous-jacente.
  */

  // On modifie le tableau d'exemple en utilisant son pointeur dans une fonction
  int status =
      oppose((int *)&tableau_example, sizeof(tableau_example) / sizeof(int));

  if (status == 0) {
    printf("%s\n", "Nouvelle valeur de la somme :");
    printf("%d\n", good_sum((int *)&tableau_example,
                            sizeof(tableau_example) / sizeof(int)));
  } else {
    printf("%s\n", "Comment êtes vous arrivés içi ?");
  }

  /*
  Un exemple d'error control flow, on considère que la fonction main est un
  succès si la fonction oppose a fonctionné.
  */

  /*
  Petit bonus avant de partir, en C vous pouvez afficher (et même manipuler
  comme un entier, mais cela est rarement une bonne idée) l'adresse d'un
  pointeur :
  */
  printf("Adresse de tableau_example : %p\n", &tableau_example);
  return status;
}

/*
################################################################################
############# Dernière partie du programme : les fonctions annexes #############
################################################################################
*/

int bad_sum(int *array) {
  // Dans cette fonction on cherche à calculer la somme des éléments dans array.
  int result = 0;
  // La première chose à faire est de savoir combien d'éléments sommer ...
  printf("sizeof array %d\n", sizeof(array));

  /*
  Le message ne tient pas sur une ligne, donc je le sépare en plusieurs lignes
  grâce à la syntaxe de substitution du printf.
  */
  char *debut_du_message = "C'est la taille en mémoire du pointeur";
  char *fin_du_message = "et pas la taille en octets du tableau ...";

  printf("Oups ...\n%s, %s\n", debut_du_message, fin_du_message);

  /*
  En n'ayant que le pointeur vers le tableau, il n'est pas possible d'en
  déterminer la taille, ni même de savoir si il a une taille, donc on est
  coincé...
  */

  return -1;
}

int good_sum(int *array, size_t taille) {
  /*
  Dans cette fonction aussi on cherche à calculer la somme des éléments de
  array.
  */
  int result = 0;

  /*
  Dans la mesure où on nous a passé la taille du tableau en argument, on peut
  effectuer notre somme aisément.
  */

  for (size_t i = 0; i < taille; i++) {
    result += array[i];
  }

  // On renvoie le résultat sans soucis
  return result;
}

int oppose(int *array, size_t taille) {
  /*
  Dans cette fonction on va remplir le tableau en entrée en opposant toutes
  les valeurs.
  */

  /*
  Notez que l'on modifie le tableau passé en argument par "effet de bord".
  Je ne détaille pas maintenant pourquoi ce n'est en réalité pas un effet de
  bord au sens strict, vous pourrez avoir plus de détails là dessus dans le
  programme sur les états indéfinis (Undefined Behaviors).
  */
  for (size_t i = 0; i < taille; i++) {
    array[i] *= -1;
  }

  // Si on arrive ici, la fonction s'est exécutée correctement.
  return 0;
}

/*

                              Le mot de la fin

Les pointeurs sont un élément central du C, mais sont (un peu à raison) vu comme
difficiles à utiliser et peu pratiques en venant d'un autre language. Il est
vrai qu'un pointeur est moins facile à utiliser qu'une référence (même si la
différence est asse subtile), mais les pointeurs se rapprochent davantage du
fonction de la machine sous-jacente. Cela permet de souligner un point important
concernant le C :

Le C n'est pas d'un language de programmation de haut niveau fait pour manipuler
efficacement et automatiquement des concepts utiles pour un humain (comme le
sont python, java et par certains aspects le C++). Il s'agit en fait d'un
language de bas niveau, c'est à dire un language qui permet d'écrire
automatiquement du code compréhensible par une machine.

La raison d'être du C (pour ainsi dire) est que si ce type de language
n'existait pas, nous serions forcés d'écrire du code en assembleur pour faire
effectuer toute tache à une machine. Si jamais vous ne voyez pas le problème, je
me contenterai d'écrire que l'assembleur est extrèmement laborieux à utiliser,
par exemple il vous faut généralement plusieurs lignes pour faire une addition
en assembleur, avec du contenu aussi passionnant que (en pseudo code pour plus
de lisibilité):

1: Charger depuis un adresse mémoire la pemière valeur à ajouter dans un
  registre
2: Charger depuis une autre adresse mémoire la seconde valeur dans un registre
3: Sommer les contenus des deux registres et mettre le résultat dans le premier
  registre
4: Ecrire le résultat contenu dans le registre de sortie à la bonne adresse
  mémoire

Je vous laisse imaginer le nombre de lignes nécéssaires pour effectuer un simple
printf... Cela permet de mieux comprendre pourquoi le C existe et permet
également d'expliquer la logique du C.

Pourquoi forcer à utiliser des pointeurs et pas des références, qui sont
pourtant plus faciles à utiliser pour le programmeur ?
    - Parce que le concept de référence n'existe pas en assembleur, on n'y
    trouve seulement des adresses mémoires et des valeurs, par suite il n'est
    pas possible d'efficacement traduire un code qui utilise des références en
    assembleur.

Pourquoi ne pas introduire un système d'erreurs avec interruptions comme en
python ou en Java ?
    - Encore une fois ce concept n'existe pas dans la plupart des assembleurs,
    donc il ne serait pas forcément possible de traduire efficacement du code
    utilisant de telles exception en assembleur.

Pourquoi ne pas laisser le programmeur définir des types de taille variable
qui représenteront des objets abstraits pour son code ?
    - Parce que lorsque vous écrivez le code correspondant en assembleur, vous
    avez besoin de savoir le nombre d'extraction de données que vous devez faire
    depuis la mémoire.


Notez que si cela vous intéresse, vous pouvez demander à votre compilateur C de
vous montrer ce en quoi il compile votre code (le code en assembleur qu'il
génère). Par exemple, pour gcc la commande à utiliser est :

gcc -S -fverbose-asm -O0 <fichier source>

Et gcc va créer un fichier .S contenant un code en assembleur de votre
programme. Le flag -S indique que gcc doit produire du code en assembleur, -O0
signifie à gcc qu'il ne doit pas optimiser le code (sinon vous aurez du mal à
trouver la correspondance entre ce que vous avez écrit et ce qui est fait
réellement), -fverbose-asm indique au compilateur qu'il doit commenter le code
en assembleur avec des informations pour aider à la relecture. Pour d'autres
compilateurs, cherchez sur internet la commande à passez en argument.

tl;dr : Le C n'est qu'un "framework" pour générer du code en assembleur
automatiquement et pas un language de programmation au sens où on l'entend
habituellement (i.e. programmation de haut niveau), et cela explique une grande
partie des choix qui ont été faits dans la conception du language, notamment les
types de taille fixe et les pointeurs.
*/
