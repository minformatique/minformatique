/*
Ce fichier fait partie du tutoriel en C sur les états indéfinis. Il a pour but
d'introduire la notion d'états indéfinis (Undefined Behaviors) et de faire
comprendre en quoi leur existence est problématique. Notez que ce fichier ne
comporte que peu de code, essentiellement des commentaires.

Notez que je n'ai pas écrit de Makefile pour ce tutoriel, simplement parce que
make sait tout seul comment compiler des fichiers make simples. Tapez juste
"make erreurs" dans votre ligne de commande et make compilera erreurs.c

Contributeurs : Rezal P18
*/

/*
################################################################################
################## Première partie du programme : les inclusions ###############
################################################################################
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Simple {
  int a;
  float b;
};

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

                          Segmentation Fault - 2**

Si vous avez déjà écrit des programmes en C vous même, vous n'avez sans doute
pas manqué de remarquer de 90% de ce que vous écrivez se termine toujours par
les deux mêmes mots magiques : Segmentation Fault ("faute de segmentation",
sans surprise...).

Contrairement à ce que l'on pourrait penser en venant d'un langage plus moderne,
une faute de segmentation n'est pas une erreur (ou exception) lancée par le C.
Le terme segmentation fault désigne le fait que votre programme tente d'accéder
à un segment (i.e. espace) de la mémoire qu'il n'a pas réservé. Ce mécanisme
permet notamment d'éviter qu'une application en fasse échouer une autre en
écrasant des valeurs dont elle a besoin. Par conséquent, la faute de
segmentation n'est pas un concept du C, mais de l'OS sur lequel votre programme
est en train de tourner. Elle est l'équivalent en programmation de bas niveau du
fait de se cogner contre un mur : ce n'est pas une erreur dans le sens où vous
allez faire quelque chose qui n'a pas de sens (comme le serait une division par
0 en python par exemple) mais plutôt un état de fait (i.e. vous vous êtes cognés
contre le mur).

Ce qu'il est important de comprendre est que dans à peu près n'importe quel
langage de programmation, lorsque vous rencontrez une erreur ou une exception,
c'est parce que ce que vous essayez de faire est défini comme une erreur. Par
exemple en Java ou Python, accéder au 10ème élément d'un tableau de taille 5 est
une erreur.

La grande différence du C avec ces langages est qu'en C le concept même d'erreur
n'existe pas (et non, les errno ne suffisent pas à combler ce vide). Les seules
"erreurs" que vous pouvez rencontrer en C sont des erreurs de compilation, mais
ce sont essentiellement des erreurs de syntaxe et non de sémantique. C'est la
raison pour laquelle en C vous pouvez avoir des segmentation fault alors que
dans la plupart des autres langages cela est impossible. Avant d'arriver à la
faute de segmentation il y a des signes précurseurs qui seraient considérés
comme des erreurs dans d'autres langages (par exemple l'usage de variables non
initialisées) mais que le C va très joyeusement ignorer.

La raison implicite pour laquelle le C ne dispose pas de mécanisme d'erreurs
est, comme souvent, que le concept d'erreurs n'existe pas non plus dans la
machine sous jacente, et à raison : manipuler une variable qui n'a pas été
initialisée n'est pas quelque chose qu'il est impossible de faire
materiellement, mais plutôt quelque chose que nous jugeons n'avoir pas de sens.
Cette étape de jugement est toujours effectuée par un humain, et dans le cas du
C le paradigme adopté est que cet humain soit vous. Si vous écrivez que vous
voulez accéder au 10ème élément d'un tableau qui n'a pas été initialisé, alors
le C va supposer que c'est effectivement ce que vous voulez faire, fût-ce
réellement le cas ou non.

Détail assez amusant : si vous travaillez sur un micro-controlleur ou tout autre
machine sans système d'exploitation, alors il n'y a plus personne pour dresser
de murs entre les segments de la mémoire, et donc il n'est plus possible d'avoir
de segmentation fault. Un programme en C sur un micro-controlleur ne vas donc
jamais échouer, simplement parce que la notion même d'échec lui est inconnue. Un
peu comme un élève des Mines en fait ;-)
*/

int main(int argc, char const *argv[]) {
  // exemple d'usage de variables non initialisées
  int a;
  float b;
  printf("%d + %f = %f\n", a, b, a + b);
  /*
  Attention : suivant que votre RAM ait déjà été plus ou moins utilisée (i.e.
  que vous veniez d'allumer votre PC ou non) il se peut que a et b aient
  toujours les mêmes valeurs (souvent 0). Cela dépend de si votre OS remet à 0
  la mémoire avant de vous la donner, ce qui dépend à son tour de beaucoup de
  choses et est clairement imprévisible. Tant que vous n'avez pas initialisé une
  valeur il n'est pas possible de dire ce qui se trouve dans son espace mémoire,
  contrairement à d'autres langages comme Java par exemple.
  */

  /*

                              Les pointeurs bruts - 3***

  Un exemple particulièrement flagrant du fait que le C ne se préoccupe pas le
  moins du monde de vérifier si ce que vous faîtes a un sens est l'usage
  (abusif) de pointeurs bruts. Dans la mesure où tout pointeur peut être
  convertit en et vers un pointeur brut, ce genre de manipulations est tout à
  fait valable en C:
  */

  // On récupère un pointeur vers l'entier a ...
  void *a_ptr = (void *)&a;
  /*
  Et on décide que a l'espace mémoire de a va maintenant être lu comme un
  tableau de char (parce que pourquoi pas).
  */
  char *a_char = a_ptr;
  printf("a = %d %d %d %d\n", a_char[0], a_char[1], a_char[2], a_char[3]);

  // idem pour b
  char *b_char = (void *)&b;
  printf("b = %d %d %d %d\n", b_char[0], b_char[1], b_char[2], b_char[3]);

  /*
  Vous ne manquerez sans doute pas de remarquer que ce que l'on vient de faire
  est exactement la même chose que ce que l'on avait montré dans le tutoriel sur
  les structures avancées avec les unions. La différences entre les deux est
  qu'utiliser une union correctement permet d'arriver à un programme lisible et
  rigoureux, alors que là nous sommes en train de faire un peu n'importe quoi.

  Notez que l'on peut de la même façon créer des structs en mettant bout à bout
  les valeurs qui nous intéressent derrière un même pointeur.
  */

  char raw_struct[sizeof(int) + sizeof(float)];
  void *raw_struct_ptr = &raw_struct;
  /*
  Ici on copie les 4 octets de a derrière le pointeur de
  raw_struct
  */
  memcpy(raw_struct_ptr, (void *)&a, sizeof(int));
  /*
  De même, on copie les 4 octets de b derrière le pointeur de
  raw_struct mais 4 octets plus loin (pour ne pas réécrire sur l'entier).
  */
  memcpy(raw_struct_ptr + sizeof(int), (void *)&b, sizeof(float));

  /*
  Et maintenant on vérifie que l'on a bien copié a et b correctement.
  rsc signifie raw_struct_char
  */
  char *rsc = raw_struct_ptr;
  printf("raw_struct = %d %d %d %d %d %d %d %d\n", rsc[0], rsc[1], rsc[2],
         rsc[3], rsc[4], rsc[5], rsc[6], rsc[7]);

  // Pour preuve, on fait la même chose avec un vrai struct
  struct Simple simple;
  simple.a = a;
  simple.b = b;
  char *ssc = (void *)&simple;
  printf("simple = %d %d %d %d %d %d %d %d\n", ssc[0], ssc[1], ssc[2], ssc[3],
         ssc[4], ssc[5], ssc[6], ssc[7]);

  /*
  Comme vous pouvez le constater, ce qui se trouve derrière les pointeurs de
  simple et de raw_struct est identique. La grande différence est qu'un code
  utilisant des struct sera bien écrit et abstrait alors qu'un code qui abuse
  des pointeurs bruts sera au mieux incompréhensible, au pire truffé de bugs.
  */

  /*
  Ayant lu jusqu'ici, vous ne voyez probablement pas d'où vient le problème.
  Le C est permissif, mais c'est une qualité plus qu'un défaut, non ?

  Je répondrais qu'effectivement jusqu'à un certain point, la permissivité d'un
  langage est une qualité. Le problème est que le C se trouve très clairement
  au dela de ce point. Vraiment très très loin en fait.

  Un exemple pour introduire les états indéfinis.
  */

  // C est un char
  char c;
  // Dites bonjour à C ;-)
  printf("c = %c - %d\n", c, c);
  // c_ptr est le pointeur qui va vers C.
  char *c_ptr = &c;
  // Derrière c_ptr on trouve la valeur de C...
  printf("*c_ptr = %c - %d\n", *c_ptr, *c_ptr);
  // ... Et juste après on trouve un autre char :-)
  printf("*(c_ptr+1) = %c - %d\n", *(c_ptr + 1), *(c_ptr + 1));

  /*
  Impossible! Lorsque nous avons déclaré c, nous avons reservé un espace mémoire
  de la taille d'un char, à savoir 1 octet. Donc lorsque nous tentons d'accéder
  à c_ptr + 1, l'OS devrait nous renvoyer une erreur de segmentation, non ?

  Il y a deux réponses possibles à cette question. La version courte est :
  Oui, parfois, enfin ça dépend, cette ligne de code va un peu aléatoirement
  créer fautes de segmentation. Il n'est pas possible de prédire à l'avance si
  cette ligne va créer un bug ou non, son comportement est indéfini, d'où le
  terme anglais Undefined Behavior. On passe donc dans notre programme par un
  état indéfini (roll credits ;-) ).


                          Allocation de mémoire - 4****

  Il est tout de même possible d'expliquer ce qui se passe ici, mais pour cela
  il faut en revenir à l'implémentation de l'allocation de mémoire par l'OS.
  Notez cependant que si jamais vous utilisez un OS qui a une implémentation
  différente des allocations en mémoire le comportement de cette ligne de code
  sera différent. C'est entre autre pour cela que le comportement de cette
  ligne de code n'est pas défini dans le standard.

  Pour en revenir à l'allocation de mémoire, lorsque votre programme demande de
  l'espace à l'OS, ce dernier n'a que très peu de temps pour répondre (un délai
  même minime sur ces allocations mémoires aurait un impact énorme sur le
  ressenti de l'utilisateur car tous les programmes demandent de la mémoire en
  permanence). Cela étant l'OS ne peut pas non plus faire n'importe quoi dans
  ses allocations, sinon il risque à terme de se retrouver avec une mémoire dans
  laquelle il y a plein de petits morceau reservés partout et beaucoup de vide
  entre, mais du coup si un programme demande d'un coup beaucoup de mémoire
  (par exemple pour une multiplication matricielle) l'OS va se retrouver bloqué
  parce qu'il aura mal réparti la mémoire.

  Ces questions d'allocation de mémoire sont assez complexes, et n'étant
  moi-même pas expert je ne peux qu'être superficiel dans mon explication, mais
  après beaucoup de compromis il s'avère que la meilleure solution pour l'OS est
  de ne pas allouer exactement la taille en mémoire que vous demandez, mais un
  peu plus que nécessaire de sorte à vous allouer un nombre entier de segments
  de mémoire. Donc la plupart du temps derrière vos variables et vos tableaux il
  y a toujours un peu de mémoire reservée en plus... Mais impossible de savoir
  à l'avance combien !

  En plus de cela, il s'avère que le type char (1 octet) est trop petit pour
  pouvoir être passé seul dans certains circuits du processeur et de la mémoire
  qui sont plutôt optimisés pour des types comme int ou double. Par suite la
  probabilité d'avoir une faute de segmentation sur l'adresse qui suit un char
  réservé seul est très faible (mais non nulle et encore une fois dépend de
  l'implémentation).
  */

  /*

                              Etats indéfinis - 3***

  Un état indéfini, ou comportement indéfini (en anglais Undefined Behavior)
  est un état dans lequel le standard n'impose pas la comportement d'une
  routine. Souvent ils sont indiqués dans la documentation de la fonction que
  vous souhaitez utiliser, par exemple dans la documentation de memcpy on lit
  que les espaces mémoires source et destination ne doivent pas se chevaucher.
  Mais la documentation ne précise pas ce qu'il se passe si les deux espaces
  mémoire se chevauchent.

  Le problème alors est que si par mégarde on a passé deux espaces mémoires qui
  se chevauchent à memcpy, il n'y a pas de réel moyen de s'en rendre compte :
  memcpy revoie un pointeur brut donc il n'y aura pas de code d'erreur, et dans
  la mesure où il n'y a pas de système d'exceptions en C memcpy n'a aucun moyen
  de nous prévenir du problème. Mais pour nous prévenir du problème, encore
  faudrait-il que memcpy vérifie lui-même si les pointeurs qu'on lui passe sont
  valables. Or le fait est que la plupart des fonctions ne vont pas vérifier ce
  qui leur est donné en entrée, notamment parce que le nombre de cas à vérifier
  est souvent très important et leur vérification serait chronophage (et il est
  vrai pénible à écrire).

  "Mais pourquoi nous embêter avec cela, il suffit de ne pas passer deux espaces
  qui se chevauchent à memcpy !"

  Pris individuellement, ces états indéfinis ne sont que rarement problématiques
  ou difficiles à comprendre. Mais le fait est qu'il ne sont jamais observé
  isolément. Tout ce que vous savez en tant que developpeur est que vous avez
  écrit un programme de 400 lignes et qu'il s'achève par l'immuable
  "Segmentation Fault". Mais du coup trouver la source du problème, surtout
  lorsqu'elle est non triviale, peut prendre des heures. Mais pas des heures
  comme dans "cet après midi je vais lire mon livre de QSE pendant 3 heures" !
  Des vraies heures de débuggage en ligne de commande, à mettre des printf
  partout pour trouver l'endroit où a lieu la faute de segmentation (parce que
  l'OS se moque de là où le problème a lieu, il sait juste que vous vous
  êtes pris un mur). Et puis après avoir trouvé le lieu de la faute, il faut
  remonter à son origine ! Et pour cela, quoi de mieux que le bon vieux GDB !
  Si vous aimez executer votre C en ligne de commande, vous adorerez suivre les
  adresses de vos variables pendant l'execution du programme dans un debugger en
  ligne de commande pour trouver à quel moment vous avez mal initialisé votre
  valeur !

  Et au bout de toutes ces heures de débuggage, lorsque éreinté vous vous rendez
  compte que votre problème est vous avez écrit :

  // une fonction qui prend en argument un pointeur vers un pointeur brut.
  int ptr_function(void **ptr);

  int bad_function() {
    int tableau[5];
    ptr_function( (void **) &tableau);
    return 0;
  }

  alors que les tableaux, malgré qu'ils soient convertis en pointeurs
  implicitement lorsque vous les utilisez, se comportent comme un type primitif
  pour l'opérateur & et donc que &tableau est en fait un int * et pas int **
  comme vous le pensiez; alors à ce moment vous vous mettez à vraiment regretter
  le fait que le C accepte vraiment n'importe quelles opérations pour peu
  qu'elles soient syntaxiquement possibles.

  Non, je ne veux pas convertir un pointeur vers un tableau d'entier en un
  pointeur vers un autre pointeur, cela n'a pas de sens;

  Non, je n'ai pas sciemment renvoyé de ma fonction un pointeur vers un espace
  mémoire de la stack qui sera invalidé à la fin de la fonction, je n'ai juste
  pas l'habitude de travailler avec des pointeurs et pas des références;

  Non, je n'ai pas fait exprès de ne pas initialiser ma structure ou mon
  pointeur dans mon code;

  Non, je n'ai particulièrement envie de voir ce qu'il se passe dans les espaces
  mémoire derrière c_ptr, cela n'a pas de sens de toute façon;
  */

  // Exemple de comportement indéfinis
  char buffer[10];
  char *buffer_ptr = buffer;
  sprintf(buffer_ptr, "%s", "rezal");
  printf("%s\n", buffer_ptr);
  memcpy(buffer_ptr + 2, buffer_ptr, 5);
  printf("%s\n", buffer_ptr);

  /*
  Suivant votre chance, memcpy va ou non faire ce qu'il devrait. C'est que qui
  rend les état indéfinis particulièrement difficiles à gérer : ils ont
  tendance à créer des bugs aléatoires (les meilleurs types de bugs, comme
  chacun le sait).
  */

  /*
  Un autre exemple de comportement difficilement prévisible : mixer l'usage de
  FILE et de file descriptor (cf le tutoriel sur la librairie standard).
  Normalement si vous executez votre programme depuis un terminal vous devriez
  voir la sortie s'afficher correctement, mais si vous redirigez l'output vers
  un fichier seul l'un des deux messages va s'afficher.
  */
  fprintf(stdout, "%s\n", "Petit message sympathique");
  /*
  ---> Windows seulement :
  Il n'y a pas d'équivalent à dprintf sous Windows, donc je ne peux pas montrer
  cela
  */
  // dprintf(1, "%s\n", "Autre message non moins intéressant");

  /*
  Autre exemple, faire plusieurs free sur de la mémoire reservée avec malloc
  en heap (cf le tutoriel sur la compilation avancée).
  */
  void *space = malloc(100);
  // On peut prédire ce que fera ce free ...
  free(space);
  /*
  ... Mais pas ce que fera celui là. Suivant les implémentations free peut faire
  une vraie erreur avec un message donc je commente ce code, mais vous pouvez
  voir ce qu'il fait si vous voulez.
  */
  // free(space);
  return 0;
}
/*
################################################################################
############# Dernière partie du programme : les fonctions annexes #############
################################################################################
*/

/*

                                Le mot de la fin

Pour bien clarifier les choses : le fait que le C accepte des syntaxes souvent
fantaisistes et le fait que beaucoup de beaucoup de fonctions aient des
comportements indéfinis dans beaucoup de cas de figures sont deux problèmes
distincts. Mais ces deux éléments procèdent de la même cause : le C n'a
aucun mécanisme d'exception et n'a de toute façon pas envie de vérifier ce que
vous faites. Cela n'est simplement pas la philosophie du C. Il s'agit d'un
langage de bas-niveau qui doit pouvoir être rapidement compilé en code machine.
Les exceptions et autres vérifications pendant l'exécution sont autant de poids
qui ralentissent l'exécution et la compilation.

En C plus que dans beaucoup d'autres langages, le code machine que vous obtenez
correspond à ce que vous avez écrit (modulo les optimisations de code). Il n'y
a aucun filet et bien peu d'abstractions coûteuses de votre code.

Le fait d'être aussi proche de la machine confère au C une qualité dont peu de
langages profitent autant (le seul autre évident est l'assembleur): le code
produit par un compilateur C moderne est extrèmement compact. Il n'est pas rare
que le code produit par compilateur C occupe moins de place en mémoire que le
fichier texte qui a servi à le créer. Cela peut sembler anodin, mais à l'époque
où le C est apparu (~1970) les ordinateurs et micro-controlleurs n'avaient que
très peu de mémoire (même morte) sur lequels stocker le code machine. En ordre
de grandeur, les disquettes en vente par IBM dans la fin des années 1970 avaient
une capacité de stockage de l'ordre de 1MB, d'où la nécessité de ne pas avoir
trop de surcouche autour de ce que le programmeur souhaite écrire.

Cette philosophie accordant beaucoup de liberté et de responsabilités au
developpeur a il semblerait assez bien survécu au passage du temps, toutefois il
reste légitime de la remettre en question. Après tout, nous ne vivons plus
aujourd'hui en 1980, et la technologie a beaucoup progressée (cf la loi de
Moore). Pourquoi donc se forcer à faire des programmes compacts mais longs à
écrire et débugger lorsqu'il est possible d'utiliser des langages modernes (qui
permettront de developper du code plus rapidement et sans créer autant de bugs)?

Le C est un langage qui a des forces indéniables, et il est toujours intéressant
de savoir l'utiliser car il est un outil puissant pour résoudre des problèmes
bas niveau nécessitant beaucoup de souplesse. Mais la plupart des programmes
que vous aurez à developper ne sont pas ainsi. En revanche le fait de connaitre
le C vous donne une meilleure idée du fonctionnement de la machine qui exécute
vos programmes, et vous permettra je l'espère d'apprécier à leur juste valeur
les innovations et abstractions apportées par les langages modernes.
*/
