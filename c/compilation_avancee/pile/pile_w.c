/*
Ce fichier contient une implémentation du type pile utilisant des pointeurs
bruts. Le principal point développé dans ce fichier est l'utilisation de alloc

Contributeurs : Rezal P18
*/

/*
################################################################################
################## Première partie du programme : les inclusions ###############
################################################################################
*/

/*

                          La librairie alloc - 3***

Je le détaillerai davantage par la suite, mais je ne voulais pas parler de cette
librairie dans ces tutoriels, cependant il s'avère que je me trouve précisément
dans un cas de figure où alloc est très adapté (à savoir pour définir des types
dont la longueur doit changer au fil de l'usage).

Pour faire concis, la librairie alloc est source d'énormément d'état indéfinis
et de mauvaises pratiques. Cette librairie, qui a pourtant un usage en principe
assez restreint, est utilisée à tous va dans beaucoup de programmes où elle n'a
pas sa place et est par suite source d'un grand combre de bugs.

tl;dr : Je fais ici la démonstration de alloc, mais autant que possible tachez
de ne pas utiliser cette librairie dans vos programmes, ce n'est dans 99% des
cas pas d'elle dont vous avez besoin.

Notez que la librairie alloc est une partie de stdlib.h
*/
// #include <stdlib.h> (déjà dans pile.h)

/*
Notez que l'on peut utiliser le header d'une librairie dans la librairie elle
même afin d'éviter d'écrire deux fois la même chose (notamment pour les
prototypes et les déclarations de types).
*/
#include "pile_w.h"

/*
################################################################################
################## Deuxième partie du programme : les prototypes ###############
################################################################################
*/

/*
Comme précisé plus tôt, la plupart des prototypes sont définis dans pile.h
*/

/*
Ce protoype est noté static, donc ne sera quoi qu'il arrive pas accessible
depuis l'extérieur de la librairie.
*/
static int pile_resize(struct Pile *instance, size_t new_size);

/*
################################################################################
##################### Troisième partie du programme : le main ##################
################################################################################
*/

/*
Pour des raisons évidentes, il n'y a pas de main dans une librairie.
*/

/*
################################################################################
############# Dernière partie du programme : les fonctions annexes #############
################################################################################
*/

/*
Cette routine initialise la pile passée en argument.
*/

/*
---> Windows seulement :

La signification du __declspec(dllexport) est expliquée dans le Makefile,
en pratique si vous ne le mettez pas vous ne pourrez pas utiliser cette fonction
sera inaccessible de l'exterieur de la dll, et si vous ne mettez aucun de ces
décorateurs clang ne va même pas vous créer le .lib dont vous avez besoin pour
utiliser cette librairie.
*/

__declspec(dllexport)
int new_pile(struct Pile *instance) {
  // On commence par initialiser la taille de la pile
  instance->taille_pile = 0;
  /*
  On va allouer la taille par défaut à la pile, définie par le préprocesseur en
  début de programme.
  */
  instance->taille_pile_max = PILE_TAILLE_DEFAUT;

  // Il nous reste maintenant à allouer de l'espace en mémoire pour la pile.

  /*

                                malloc - 3***

  malloc ("memory allocation") est la fonction la plus emblématique de alloc
  Il s'agit aussi d'une des fonctions les plus connues du C, davantage en mal
  qu'en bien.

  La signature de malloc est :

  void *malloc(size_t size);

  Son principe de base est assez simple : malloc va reserver en mémoire un
  espace de size octets et renvoyer un pointeur vers cet espace mémoire. Son
  usage en pratique, toujours déconseillé, est en revanche autrement plus
  subtil.

  Si sur le principe malloc ressemble à une création de tableau, en réalité les
  ont une différence fondamentale. Lorsque vous déclarez un tableau, il s'agit
  d'une variable locale, valable seulement au sein de la fonction courante.
  L'espace en mémoire dans lequel se trouve ces tableaux se nomme "stack
  memory". Cette "stack memory" est gérée automatiquement par le compilateur, et
  le fait qu'une variable se trouve dans cette "stack memory" a plusieurs
  conséquences, la plus évidente d'entre elles étant que VOUS NE POUVEZ PAS
  RENVOYER UN POINTEUR VERS UNE VARIABLE DANS LA "STACK MEMORY", parce que
  l'espace dans lequel cette adresse se trouve va être réécrite à la fin de la
  fonction. Notez également que dans la mesure où la "stack memory" est faite
  pour contenir des objets courants, elle n'est pas très grande et peut ne pas
  suffire pour contenir des objets immenses (vous rencontrerez rarement ce
  problème sur un ordinateur, mais la question peut devenir importante par
  exemple sur un système embarqué).

  Les pointeurs renvoyés par malloc en revanche se trouvent dans la "heap
  memory", qui est une sorte de mémoire globale du programme. On y trouve entre
  autres toutes les grandeurs définies globalement pour le programme
  (PILE_TAILLE_DEFAUT par exemple). Dans la mesure où ces espaces mémoire ne
  sont pas réecrits au fil du programme, il est tout à fait valide de renvoyer
  depuis une fonction un pointeur vers un espace mémoire de la "heap memory"
  (d'ailleurs malloc elle-même le fait). En revanche comme la "heap mémory"
  n'est pas gérée automatiquement il vous faut gérer davantage de choses vous
  même. Notez aussi que la "heap memory" est plus grande que la "stack memory",
  mais encore une fois vous aurez rarement à vous en soucier.

  Mais alors, quel est le problème ? Si malloc nous alloue des espaces mémoires
  que l'on peut renvoyer depuis nos fonctions, n'est-ce pas encore mieux que
  d'utiliser des tableaux ? Pourquoi ne pas mettre des malloc partout dans mes
  programmes ?

  En réalité beaucoup de gens font exactement cela, et mettent des malloc
  partout. Le problème de malloc n'est pas la fonction en elle même (la plupart
  du temps malloc fera ce que vous pensez qu'elle fait), mais plutôt ce qu'elle
  induit :

   - Contrairement aux tableaux, les pointeurs bruts renvoyés par malloc sont
   entièrement sous votre responsabilité. A chaque fois que vous ferez une
   manipulation sur ces pointeurs il faudra vous assurer que vous ne cassez
  rien, c'est à dire éviter les fausses manipulations mais aussi ne pas vous
   retrouver dans des états indéfinis. Cela peut sembler bénin si vous n'avez
  pas l'habitude d'écrire des programmes en C, mais en réalité faire des
  mauvaises manipulations sur les espaces mémoires (qui induiront ensuite des
  états indéfinis) est vraiment très difficile et nécessite beaucoup de rigueur.

   - Le fait de pouvoir retourner des pointeurs en sortie de fonctions est une
   facilité qui contraste avec la rigueur habituelle de la syntaxe des fonctions
   en C. Cela étant il ne faut pas utiliser cela aveuglément et cesser d'être
   rigoureux sur la structure de ses fonctions. Le C est un langage simple mais
   très punitif, et si vous vous autorisez à faire n'importe quoi dans avec vos
   fonctions vous allez à coup rencontrer un état indéfini plus ou moins subtil
   qui pourra être très long à résoudre si vous avez utilisé des syntaxes
   exotiques pendant tout votre programme.

  La raison pour laquelle malloc (et alloc) ne sont pas recommandés est que
  cette librairie est concue pour résoudre un problème précis (allocation dans
  la "heap memory" plutôt que la "stack memory") mais peut facilement être
  détournée pour créer toute une panoplie de syntaxes peu orthodoxes et de bugs
  qui seront très difficiles à résoudre.

  Même si la comparaison est sévère, je vous dirai pour être concis de ne pas
  utiliser malloc pour les mêmes raisons que vous n'utiliseriez pas goto (oui,
  le goto existe en C, mais pour le coup on ne le rencontre jamais) : ces
  outils sont utiles dans certains cas assez subtils, mais mal utilisés il
  casseront toute rigueur dans vos programmes et induiront des bugs que vous ne
  saurez probablement pas résoudre en un temps court.

  tl;dr : Faites vous une faveur et évitez malloc autant que faire se peut.
  Cette fonction est utile, mais seulement si vous comprenez vraiment ce qu'elle
  fait. Et surtout, que vous l'utilisiez ou non, tachez de rester consistants et
  rigoureux dans l'écriture de vos routines en C si vous voulez vous éviter de
  longs maux de tête.
  */
  instance->content = malloc(PILE_TAILLE_DEFAUT * sizeof(void *));
  return 0;
}

__declspec(dllexport)
int pile_append(struct Pile *instance, void **element) {
  /*
  Ajoute un élément sur la pile, il faut juste faire attention à bien changer
  la taille de la pile si jamais elle commence à être pleine.
  */
  if (instance->taille_pile + 1 >= instance->taille_pile_max) {
    /*
    Notez que l'on augmente la taille de la pile de 10 d'un coup pour éviter
    de faire des resize en permanence
    */
    pile_resize(instance, instance->taille_pile_max + 10);
  }
  /*
  Une fois l'éventuel redimensionnement effectué, on ajoute l'élément dans notre
  pile.
  */
  instance->content[instance->taille_pile] = *element;
  instance->taille_pile++;
  return 0;
}

__declspec(dllexport)
int pile_pop(struct Pile *instance, void **element) {
  /*
  Un peu comme dans pile_append, la seule chose à laquelle il faille faire
  attention est la taille de la pile.
  */
  if (instance->taille_pile == 0) {
    // On renvoie un code d'erreur car il n'est pas possible de retirer de la
    // pile
    return -1;
  } else {
    if (instance->taille_pile + PILE_TAILLE_DEFAUT <
        instance->taille_pile_max) {
      // i.e. si la pile se vide.
      pile_resize(instance, instance->taille_pile_max - PILE_TAILLE_DEFAUT);
    }
    *element = instance->content[instance->taille_pile - 1];
    /*
    Notez que l'on ne remet pas l'élément de la pile à 0 ni quoi que ce soit
    d'autre, car on sait que si besoin il sera réécrit lorsque l'on appelera
    pile_append.
    */
    instance->taille_pile--;
    return 0;
  }
}

__declspec(dllexport)
int free_pile(struct Pile *instance) {
  /*

                                free - 3***

  Contrairement à la stack memory, la heap memory n'est pas gérée
  automatiquement, donc après avoir fini d'utiliser des ressources en mémoire
  dans la heap memory il faut libérer l'espace que vous avez reservé avec
  malloc, sinon vous pouvez finir par remplir le heap et arriver à des erreurs
  de type "out of memory", qui sont très difficiles à détecter et à gérer en C.

  Pour cela on utilise la fonction free, qui prend en argument un pointeur créé
  par malloc (i.e. dans la heap) et libère la mémoire qui lui est associée.

  Attention cependant, il ne faut jamais faire d'opérations sur un pointeur dans
  la heap memory qui a été libéré par free (le résultat est assez imprévisible).

  Notez aussi ne pas libérer les ressources dans la heap (i.e. ne jamais appeler
  free après malloc) constitue un "resource leak", ce qui n'est en fait pas très
  grave la plupart du temps. Deux raisons à cela :
   - Sur un ordinateur moderne la mémoire est très grande de toute façon donc il
   est très peu probable que vous remplissiez la heap pendant l'execution de
   votre programme de toute façon.

   - Les systèmes d'exploitation modernes (Linux, Windows) et Mac OS (pique
   gratuite mais pas injustifiée) gardent trace de la mémoire utilisée par votre
   programme, et une fois son execution terminée vont libérer toute la heap
   quoiqu'il arrive. Dans la mesure où l'OS sera beaucoup plus rapide que vous
   pour libérer de grands espaces mémoires le fait de ne pas libérer la heap
   peut parfois être une stratégie volontaire.

  tl;dr : Après avoir alloué de la mémoire avec malloc il faut la libérer avec
  free, mais si vous oubliez de le faire ce n'est ên général pas trop grave.

  Attention, on n'utilise jamais free sur des pointeurs de la stack (je ne suis
  même pas certain de ce que cela ferait).
  */
  free(instance->content);
  instance->taille_pile = 0;
  instance->taille_pile_max = 0;
  return 0;
}

static int pile_resize(struct Pile *instance, size_t new_size) {
  /*

                              realloc - 3***

  realloc ("reallocation") est une autre fonction importante de la librairie
  alloc. Sa signature est :

  void *realloc(void *ptr, size_t size);

  Son rôle est assez simple : elle prend en argument un pointeur créé avec
  malloc (avec l'espace mémoire derrière le pointeur dont la taille a été donnée
  au moment d'appeler malloc) et une taille de mémoire souhaitée et renvoie un
  pointeur contenant les mêmes valeurs que celles du pointeur d'origine avec
  comme taille en mémoire derrière le pointeur la taille ciblée. Pour faire plus
  court, on change la taille du tableau derrière le pointeur pour la taille
  souhaitée.

  Attention cependant, le pointeur passé initialement à realloc ne doit plus
  être utilisé après l'appel de la fonction realloc car il pourrait n'être plus
  défini.
  */
  instance->content = realloc(instance->content, new_size * sizeof(void *));
  instance->taille_pile_max = new_size;

  /*
  Je profite aussi de cette fonction pour détailler pourquoi j'avais besoin de
  realloc pour implémenter le piles correctement.

  L'alternative envisageable à realloc aurait été de déclarer un tableau de
  void* vers lequel on aurait fait pointer content. Le problème est que lorsque
  je devrai aller dans la fontion pile_resize pour augmenter la taille de la
  pile, je vais déclarer un nouveau tableau (dans la stack !) vers lequel je
  ferai pointer content. Or le nouveau tableau se trouvant dans la stack il sera
  invalidé dès que pile_resize aura fini de s'exécuter, et donc tout ce qui s'y
  trouvait ne sera plus accessible.

  C'est pour cela qu'il me faut stocker les valeurs de content dans la heap
  (i.e. avec des malloc et realloc) et pas dans la stack (i.e. avec des
  tableaux). Notez cependant que des tableaux auraient été suffisants pour
  implémenter des piles avec une taille fixe.
  */
  return 0;
}
