/*
Le but de ce tutoriel est de montrer comment utiliser les structures avancées du
C pour introduire de l'abstraction dans vos code.

Pour compiler ce programme sous linux, le plus simple est d'utiliser l'outil
make avec le Makefile fourni (dans la ligne de commande, tapez juste make en
étant à l'intérieur du dossier du Makefile).

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

/*

                            Structures avancées

Les structures avancées en C les plus courantes sont les enums, les structs et
les unions (plus rares). Leurs usages sont différents mais l'idée générale est
la même : il s'agit d'aggrégats de données qui sont censées avoir un sens
abstrait dans le programme. Leur existence a de quoi surprendre dans un langage
qui est par ailleurs fondé sur l'idée de manipuler des objets concrets pour la
machine (des pointeurs, des ints etc...) auquels le programmeur est censé donner
un sens lui même.

Sans pouvoir pleinement répondre à cette question je dirai tout de même que ces
structures avancées ne sont pas en contradition avec cette philosophie, mais
plutôt son aboutissement. Elles sont un moyen pour le programmeur de créer
l'abstraction dont il a besoin en s'appuyant sur les outils bas-niveau que le C
met à sa disposition.

Quelques choses importantes à savoir sur ces structures avancées :

 - Les mêmes structure avancées existent aussi en C++, mais les règles y sont
 différentes donc faites attention !

 - Dans la mesure où ses structures avancées ne sont que des description et ne
 contiennent pas de code (contrairement à des objets en programmation orientée
 objet) très souvent ils sont déclarés dans des fichiers .h de librairies pour
 pouvoir être utilisés depuis l'exterieur. Notez aussi que pour pouvoir être
 utilisables dans le main et les fonctions annexes vos structures avancées
doivent être déclarées avant le main. Ces deux facteurs combinés font que le
meilleur endroit pour déclarer ces structures est après les "include" et avant
les prototypes de fonctions.

 - Pour respecter les idiomes du C éviter certains bugs assez coriaces, je vous
 conseille de ne jamais renvoyer de structure depuis une fonction mais de
 modifier vos structures en passant leurs pointeurs en argument des fonctions.
*/

/*

                                  enums - 1*

Les enums ("enumeration") sont une structure de donnée très simple qui est
présente presque à l'identique dans beaucoup d'autres langages. Un enum ne peut
prendre qu'un nombre fini et prédeterminé de valeurs. Ils sont très utiles pour
représenter des états (en marche/repos/éteint par exemple) d'une façon plus
simple et plus sûre que d'utiliser des types primitifs.

Par exemple, pour une machine qui peut prendre les états marche/repos/éteint, on
pourrait décider de représenter l'état par un char dont la valeur serait 0 pour
marche, 1 pour repos et 2 pour éteint (c'est d'ailleurs ce que va faire le
compilateur). Cependant on risquerait de se tromper au fil du programme, ou bien
d'avoir une erreur à un moment dans le code qui ferait que l'état de la machine
prenne une valeur abhérrante (par exemple que faire si l'état vaut 4 ?). En
utilisant un enum on sait que l'état ne prendra que des valeurs prédifines parce
que si on essaie de donner une autre valeur à l'enum, d'une part ce ne sera pas
syntaxiquement possible et d'autre part le compilateur essaiera de nous en
empécher.

Dans la mesure où les membres d'un enum sont accessibles de l'exerieur (pour
faire des switch ou lorsqu'ils sont utilisés comme flags par exemple) une bonne
convention de notation est de mettre leur nom en majuscule, cela rendra le code
plus clair à terme.

Un exemple d'enum basé sur la machine que nous avons décrite :
*/
enum Etat {
  MARCHE, // <--- c'est une "," et pas un ";"
  REPOS,
  ARRET
}; // <--- le ";" est obligatoire ici

/*

                                structs - 1*

Les structs ("structure") sont en C ce qui se rapproche le plus d'un objet.
Une struct est un ensemble d'attributs qui sont réunis ensembles (pas de
méthodes dans un struct, en tout cas pas au sens de l'orienté objet). D'un point
de vue abstrait, on peut dire que les structs sont uniquement stateful, alors
que les méthodes qui agissent dessus sont parfaitement stateless, ce qui fait
des structs une outil de prédilection pour écrire du code réutilisable, abstrait
et simple à prendre en main.

Quelques exemples de structs : les FILE de stdio et les va_list des fonctions
variadiques. Je mentionnerait la librairie libcurl (utilisée par curl) qui sert
à télécharger des fichiers sur internet (quelque chose de très abstrait) depuis
du code en C (souvent peu abstrait) en quelques lignes grâce à une structure
définie dans easy_curl.

De manière générale, puisque vous êtes souvent déjà familiers avec la
programmation orientée objet je vous recommande très fortement d'utiliser au
maximum les structs dans vos codes en C afin de réussir à faire des choses plus
abstraites.

Un exemple de déclaration de struct :
*/
struct Machine {
  int energie;
  /*
  IMPORTANT : Lorsque vous déclarez un enum, struct ou union dans votre code
  vous devez placer le mot clef correspondant en début de déclaration pour que
  le C sache de quel objet vous parlez (vous pourriez aussi avoir une fonction
  avec le même nom par exemple).
  */
  enum Etat etat;
  char identifiant[8];
}; // <--- Là aussi le ";" est obligatoire.

/*

                                unions - 2**

Les unions sont clairement beaucoup moins utiles que les structs et les enums,
mais au cas où je les inclus dans ce tutoriel. Le principe d'une union est de
partager le même espace mémoire pour l'exploiter avec différents types. Pourquoi
voudriez vous faire cela ? Je n'en ai aucune idée, mais le C vous permet de le
faire d'une façon controllée.

Les différents attributs d'une union partagent le même pointeur et la taille
totale de l'union est suffisante pour contenir le plus grand des membres de
l'union.

Attention : Encore plus que dans les structures, déclarer un tableau ou un
pointeur dans une structure ne fera pas du tout la même chose ! Dans le doute
celui que vous cherchez à utiliser est probablement le tableau. Si vous déclarez
un pointeur dans l'union c'est la valeur de l'adresse (sur 32 ou 64 bits) qui
sera stockée dans l'union et non pas les valeurs que vous mettez derrière votre
pointeur !

Un exemple d'union qui va nous servir à séparer les différents octets qui
composent un int (on se rappele qu'un int prend 4 octets et un unsigned char en
prend 1) :
*/
union IntSplitter {
  int entier;
  /*
  On utilise un unsigned char pour avoir des valeurs entre 0 et 255 plutôt
  qu'entre -127 et 127 pour un char.
  */
  unsigned char bits[4];
}; // <--- encore une fois, il faut un ";" à la fin de la déclaration.

/*
################################################################################
################## Deuxième partie du programme : les prototypes ###############
################################################################################
*/

/*

                                typedef -1*

Le mot clef typedef en C permet de définir un alias vers une structure avancée.
Grâce à ces alias vous n'avez pas à mettre de enum, struct ou union devant
chaque déclaration, par exemple là où vous auriez mis "union IntSplitter" vous
pouvez à présent mettre juste "isplt".
*/
typedef union IntSplitter isplt;
/*
Notez que vous n'avez pas besoin de mettre des noms différents à la structure
avancée et à l'alias, en revanche vous devez faire attention au fait qu'un alias
ne peut pas avoir le même nom qu'une fonction.
*/
typedef struct Machine Machine;

/*
Notez que vous n'avez pas besoin d'avoir défini une structure avancée vous même
pour lui donner un alias, vous pourriez tout à fait créer une alias pour FILE si
vous le désiriez.
*/

/*
Vous pouvez évidemment utiliser les structures avancées que vous définissez dans
des fonctions.
*/
int split_int(isplt valeur);
int produire_machine(Machine *instance, char *identifiant);
int mauvais_produire_machine(Machine instance, char *identifiant);
int etat_machine(Machine instance);
int allumer_machine(Machine *instance);
int recharger_machine(Machine *instance, int energie);
int lancer_machine(Machine *instance, int cout);
int eteindre_machine(Machine *instance);

/*
################################################################################
##################### Troisième partie du programme : le main ##################
################################################################################
*/

int main(int argc, char const *argv[]) {

  /*
                              ---> Partie 1 : union <---
  */
  printf("\n%s\n%s", "Partie 1 : union", "(Appuyez sur ENTER pour continuer)");
  getchar();

  /*
  On commence par montrer l'usage de l'union parce que ce sera plus court.
  Tout d'abord grace à notre alias, deux syntaxes sont possibles pour déclarer
  un IntSplitter :
  */
  union IntSplitter splitter0;
  isplt splitter1;

  /*
  On peut utiliser ce splitter pour voir les valeurs octales d'un entier au
  hasard. La syntaxe pour manipuler les attributs d'un enum, d'un struct ou
  d'une union est la même et c'est celle qui a été reprise dans beaucoup de
  langages orientés objets.
  */
  splitter0.entier = 1136268;
  split_int(splitter0);

  /*
  On peut également faire le contraire et définir un entier à partir de ses
  valeurs octales.
  */
  splitter1.bits[0] = 255;
  splitter1.bits[1] = 255;
  splitter1.bits[2] = 255;
  splitter1.bits[3] = 255;
  split_int(splitter1);

  /*
  Dans la mesure où les éléments d'une union partagent le même espace mémoire on
  peut continuer à modifier librement l'un ou l'autre et voir les effets
  repercutés sur le second.
  */
  splitter1.entier++;
  split_int(splitter1);

  /*
  Notez que les octets sont lus de gauche à droite alors que les nombres
  croissent de droite à gauche dans notre système d'écriture par position.
  */
  splitter1.bits[0]++;
  split_int(splitter1);

  /*
  Personnelement je ne trouve pas qu'il y ait beaucoup de cas d'usage de ces
  unions, mais leur avantage est qu'elles permettent de faire d'une façon propre
  et plus rigoureuse des choses que l'on serait tenté de faire en passant par de
  états indéfinis (cette remarque s'adresse surtout à ceux qui auraient déjà lu
  le tutoriel sur les états indéfinis et pensent par suite que les unions ne
  font rien).

  P.S. Cette remarque a été écrite avant que le tutoriel sur la compilation
  avancée ne soit écrit, en fait on peut se servir d'une union comme d'un type
  parent de plusieurs autres types. Cela pose plusieurs difficultés en pratique,
  si vous voulez en savoir plus il y a des informations dessus dans
  le fichier calculatrice.h du tutoriel sur la compilation avancée.
  */

  /*
                          ---> Partie 2 : struct et enum <---
  */
  char *message = "struct et enum";
  char *press_enter_msg = "(Appuyez sur ENTER pour continuer)";
  printf("\n%s %s\n%s", "Partie 2 :", message, press_enter_msg);
  getchar();

  /*
  Pour montrer cette partie on va se donner les règles suivantes concernant les
  machines :
   - Avant tout chose une machine doit être construite;
   - Pour pouvoir faire des choses avec une machine il faut d'abord l'allumer;
   - Une fois la machine allumée avant de l'utiliser il faut la recharger;
   - Une machine au repos et chargée peut être utilisée;
   - Une fois vide, la machine retourne au repos et peut être chargée à nouveau;
   - Afin d'éviter les accidents, pensez à éteindre la machine après
  utilisation;
  */

  // On commence par créer une machine.
  Machine my_machine;

  /*
  Je donne des valeurs absurdes à la machine pour commencer (vous comprendrez
  plus tard pourquoi). Normalement vous n'auriez pas besoin de faire cela.

  Remarquez que pour utiliser les valeurs d'un enum il suffit de les écrire sans
  autre forme de procès, d'où l'intérêt de les écrire en majuscule afin de les
  rendre visibles.
  */
  my_machine.etat = MARCHE;
  my_machine.energie = 1000;
  strncpy(my_machine.identifiant, "absurde", 8 * sizeof(char));

  // On vérifie son état :
  etat_machine(my_machine);

  mauvais_produire_machine(my_machine, "my_machine");

  // On vérifie son état :
  etat_machine(my_machine);

  /*
  Rien n'a changé alors que nous avons appellé demandé d'initialiser notre
  machine! Le problème est que le C est uniquement pass by value, c'est à dire
  que la valeur de "instance" accessible dans mauvais_produire_machine est une
  copie de "my_machine" et pas directement "my_machine", donc changer instance
  directement ne sert à rien.

  Cela peut sembler déstabilisant, mais lorsque vous regardez la syntaxe cela
  est très cohérent :
   - Lorsque vous passez en argument un type primitif (int, char etc...) il n'y
  a pas de "*" dans la déclaration donc vous ne pouvez pas modifier la variable
   d'origine depuis l'interieur de la fonction.

   - Lorsque vous passez en argument un pointeur vers un type primitif (int *,
   char *, etc...) il y a une "*" et donc vous pouvez modifier la variable
  d'origine depuis l'intérieur de la fonction.

  De même :
    - Lorsque vous passez en argument d'une fonction un struct, il n'y a pas de
  "*" donc vous ne pouvez pas modifier le struct d'origine depuis l'interieur de
  la fonction.

    - Lorsque vous passez en argument d'une fonction un pointeur vers un struct,
  il y a une "*" donc vous pouvez modifier le struct d'origine depuis
  l'interieur de la fonction.


  Notez cependant que si un attribut du struct est lui même un pointeur (plus
  rare), vous pourrez modifier la valeur de ce qui se trouve derrière ce
  pointeur depuis l'interieur de la fonction (puisque vous accédez bien à la
  bonne adresse mémoire).

  Pour initialiser une structure depuis une fonction, il suffit donc de faire :
  */

  printf("\n%s\n\n", "Nouvelle méthode d'initialisation");
  Machine machine;

  machine.etat = MARCHE;
  machine.energie = 1000;
  strncpy(machine.identifiant, "absurde", 8 * sizeof(char));

  /*
  Pour etat machine, utiliser une copie de machine n'est pas un problème pusique
  l'on ne fait que lire les valeurs les valeurs des attibuts sans les modifier.
  */
  etat_machine(machine);

  produire_machine(&machine, "T1000");

  etat_machine(machine);

  /*
  Le reste se fait sans problèmes, vous pouvez modifier le programme pour lui
  faire faire ce que vous voulez si cela vous amuse. Je vous recommande tout de
  même de chercher des hobbies si tel est le cas :-p
  */
  allumer_machine(&machine);

  etat_machine(machine);

  lancer_machine(&machine, 10);

  etat_machine(machine);

  recharger_machine(&machine, 5);

  etat_machine(machine);

  lancer_machine(&machine, 8);

  etat_machine(machine);

  eteindre_machine(&machine);

  etat_machine(machine);

  lancer_machine(&machine, 13);

  etat_machine(machine);
  return 0;
}

/*
################################################################################
############# Dernière partie du programme : les fonctions annexes #############
################################################################################
*/

int split_int(isplt valeur) {
  /*
  On utilise le tableau de unsigned char défini dans l'union pour accéder
  facilement aux valeurs de chaque octets de l'int.
  */
  printf("Valeur de l'entier : %d\n", valeur.entier);
  unsigned char bit0 = valeur.bits[0];
  unsigned char bit1 = valeur.bits[1];
  unsigned char bit2 = valeur.bits[2];
  unsigned char bit3 = valeur.bits[3];
  printf("Valeur des octets : %d %d %d %d\n", bit0, bit1, bit2, bit3);
  return 0;
}

int mauvais_produire_machine(Machine instance, char *identifiant) {
  /*
  On initialise tous les attributs de notre machine.
  */
  instance.etat = ARRET;
  /*
  La syntaxe précédente est assez peu commode à utiliser et possède une forme
  raccourcie qui est l'opérateur de déreférence ->
  */
  instance.energie = 0;
  strncpy(instance.identifiant, identifiant, 8 * sizeof(char));
  /*
  Au cas où on nous ait passé un mauvais identifiant on place un bit de
  terminaison à la fin de l'identifiant (cf le tutoriel sur la librairie
  standard).
  */
  instance.identifiant[8] = 0;
  return 0;
}

int produire_machine(Machine *instance, char *identifiant) {
  /*
  Attention cependant à la syntaxe à utiliser pour accéder aux éléments d'un
  struct derrière un pointeur:

   - instance.etat va vous renvoyer une erreur car un pointeur n'a pas
  d'attibuts, donc <pointeur>.<...> n'a jamais de sens.

   - *instance.etat est équivalent à *(instance.etat) donc vous
   renverra la même erreur que la syntaxe précedente. Cette syntaxe serait utile
   si jamais l'attribut "etat" du struct "instance" était lui même un
   pointeur, nous pourrions alors accéder à la valeur derrière ce pointeur.

  Ici la syntaxe qui nous intéresse est :
  */
  (*instance).etat = ARRET;
  /*
  La syntaxe précédente est assez peu commode à utiliser et possède une forme
  raccourcie qui est l'opérateur de déreférence ->
  */
  instance->energie = 0;
  strncpy(instance->identifiant, identifiant, 8 * sizeof(char));
  /*
  Au cas où on nous ait passé un mauvais identifiant on place un bit de
  terminaison à la fin de l'identifiant (cf le tutoriel sur la librairie
  standard).
  */
  instance->identifiant[8] = 0;
  return 0;
}

int etat_machine(Machine instance) {
  int energie = instance.energie;
  char *identifiant = instance.identifiant;

  char *format; // Utilisé dans plusieurs branches du switch donc je le met ici.

  /*
  Un point fort des enums est qu'ils peuvent être utilisés dans les switch,
  ce qui rend le code plus facile à lire et à écrire. De plus, dans la mesure
  où contrairement à un if - else la condition à évaluer ne requiert pas de
  calcul (il faut juste aller dans la bonne branche suivant la valeur dans le
  switch) la machine sera subtilement plus efficace avec un switch qu'avec un
  if.
  */
  switch (instance.etat) {
  case ARRET: // i.e. si la machine est à l'arrêt
    printf("La machine %s est à l'arrêt\n", identifiant);
    /*
    Il faut placer un break à la fin de chaque cas dans les switch en C. Le
    code serait toujours valable sans mais ne ferait plus la même chose (et
    il ne ferait probablement pas ce que vous cherchez à faire).
    */
    break;
  case REPOS:
    format = "La machine %s est au repos, il lui reste %d d'energie\n";
    printf(format, identifiant, energie);
    break;
  case MARCHE:
    format = "La machine %s est en marche, il lui reste %d d'energie\n";
    printf(format, identifiant, energie);
    break;
    /*
    Pas besoin de default, dans la mesure où on utilise un enum on sait que
    notre traitement des cas est exhaustif.
    */
  }
  return 0;
}

int allumer_machine(Machine *instance) {
  int return_code;
  /*
  On commence encore par regarder l'état de la machine.
  */
  enum Etat etat = (*instance).etat;

  char *error_message;
  switch (etat) {
  case ARRET:
    return_code = 0;
    instance->etat = REPOS;
    break;
  default:
    /*
    Le compilateur va automatiquement concaténer des textes qui se suivent
    comme dans l'exemple qui suit. Cela fait partie de la specification C89.
    */
    error_message = "Vous ne pouvez allumer une machine qui"
                    "n'est pas à l'arrêt !";
    fprintf(stderr, "%s\n", error_message);
    return_code = 1;
    break;
  }
  return return_code;
}

int recharger_machine(Machine *instance, int energie) {
  int return_code;
  char *error_message;

  switch (instance->etat) {
  case ARRET:
    error_message = "Vous devez allumer la machine pour la charger.";
    fprintf(stderr, "%s\n", error_message);
    return_code = 1;
    break;
  case MARCHE:
    error_message = "Vous ne pouvez pas charger une machine en marche !";
    fprintf(stderr, "%s\n", error_message);
    return_code = 1;
    break;
  case REPOS:
    instance->energie = energie;
    return_code = 0;
    break;
  }
  return return_code;
}

int lancer_machine(Machine *instance, int cout) {
  int abort = 0;
  char *error_message;

  /*
  Notez qu'il serait plus correct d'écrire cette fonction avec un do-while mais
  je ne crois pas avoir déjà utilisé de boucles for dans tous les tutoriels donc
  comme cela j'aurais montré la syntaxe au moins une fois.
  */
  for (size_t i = 0; i < cout; i++) {

    if (instance->etat == ARRET) {
      error_message = "Vous ne pouvez pas lancer une machine à l'arrêt, "
                      "allumez la machine avant de la lancer !";
      fprintf(stderr, "%s\n", error_message);
      abort = 1;
      break; // i.e. on sort de la boucle car la machine ne peut plus tourner
    }

    else if (instance->energie == 0) {
      error_message = "La machine n'a plus d'energie.";
      fprintf(stderr, "%s\n", error_message);
      instance->etat = REPOS;
      break; // idem, on sort de la boucle car la machine n'a plus d'energie
    }

    else {
      switch (instance->etat) {
      case REPOS:
        instance->etat = MARCHE;
        /*
        Notez ici l'absence de break. Cela signifie que une fois la branche
        "repos" aura été exécutée le programme va "tomber" dans la branche
        "marche" et l'exécuter à son tour. Cela peut servir dans de rares cas,
        mais est surtout une source d'erreur lorsque l'on oublie de mettre le
        break...
        */
      case MARCHE:
        instance->energie--; // i.e. -= 1;
        printf("%ld - %s\n", i, "La machine produit du travail");
        break;
      case ARRET:
        /*
        Cas impossible dans cette branche du if, mais ce case rassure le
        compilateur.
        */
        break;
      }
    }
  }
  return abort;
}

int eteindre_machine(Machine *instance) {
  int return_code;
  char *error_message;

  switch (instance->etat) {
  case ARRET:
    error_message = "La machine est déjà éteinte";
    fprintf(stderr, "%s\n", error_message);
    return_code = 0; // Pas une erreur, on a juste un warning.
    break;
  case MARCHE:
    error_message = "Il est dangeureux d'essayer d'éteindre une machine "
                    "en marche";
    fprintf(stderr, "%s\n", error_message);
    return_code = 1;
  case REPOS:
    instance->etat = ARRET;
    printf("%s\n", "La machine s'éteint, "
                   "merci de prêter attention aux consignes de sécurité ;-)");
  }
  return return_code;
}

/*

                              Le mot de la fin

Les structures avancées en C font à mon avis vraiment contraste avec le reste du
langage. Comme discuté plus haut, le reste du C est beaucoup plus bas niveau
et proche de la machine. Toutefois cela ne veut pas dire qu'il ne faut pas
utiliser ces structures avancées, bien au contraire (d'autant plus que la
plupart des étudiants sont déjà familiers avec le concept de programmation
orientée objet).

Ces structures avancées permettent d'introduire de l'abstraction dans votre code
à moindre frais tout en respectant de bonnes pratiques (séparer les variables
stateful des fonctions stateless). De manière générale, les structures avancées
rendent votre code beaucoup plus lisible, plus facile à réutiliser, à comprendre
et à écrire sans faire d'erreurs.

Il n'y a que peu de raisons de ne pas utiliser ces structures avancées, et
pourtant leur usage n'est pas si répandu. Plusieurs facteurs peuvent expliquer
cela, l'un d'entre eux est notamment le fait que certains domaines d'usages du
C, notamment les systèmes embarqués, requierent souvent des programmes très
concrets et proches de la machine pour lesquels il n'y a de toute façon que peu
d'abstraction à introduire, ou alors pour lesquels les types primitifs
suffisent.

Mais je crois qu'une raison plus importante à cela est le trop répandu :

                      "Le C++ est du C avec des objets"

Sans être complètement faux (après tout le C++ est orienté objet contrairement
au C), cela suggère involontairement que le C est un langage purement impératif
ne permettant pas de définir des notions abstraites dans le code facilement.
Cela n'est (sans rien vouloir enlever au C++) évidemment pas le cas, mais cette
réputation pousse sans doute des programmeurs occasionnels à choisir le C++
plutôt que le C pour des applications pour lesquelles le C suffirait amplement.

Le C++ amène des nouveautés bienvenues par rapport au C, mais l'abstraction n'en
fait pas partie. Cela est d'autant plus important que le C++ n'est pas exempt
de faiblesses. Personnelement, j'aurais davantage tendance à recommander à un
programmeur occasionnel d'écrire son code en C plutôt qu'en C++ car le C, bien
que très concret et cruel, a au moins le mérite de l'homogénéité, ce qui le rend
plus simple à apprendre.

Discuter les avantages respectifs du C et du C++ requiererait (et a) son propre
tutoriel, l'idée que je veux transmettre ici est simplement que malgré la
réputation qu'on lui prête le C est un langage tout à fait suffisant pour
réaliser des tâches abstraites. Le C a des défauts qui justifient de le
remplacer par d'autres languages (cf le tutoriel sur les états indéfinis) mais
le manque d'abstraction n'en fait pas partie.
*/
