/*
Un programme en C très simple afin de permettre de se familiariser avec
l'utilisation du langage (notamment la compilation, les directives du
préprocesseur etc...)

Le nom du programme est évidemment un référence à K&R, qui ont défini le C vers
1970. Pour référence, le C++ est apparu en 1985, Java en 1995 et Python en 1991
(notez cependant que Python2 n'apparaitra qu'en 2000 et Python3 en 2008).
MS-DOS date de 1981 et Windows NT (l'ancètre du Windows actuel) est apparu en
1993. Dernier élément historique, l'apparition du C (et celle d'Unix) coincide
avec les tous premiers ordinateurs personnels (mais il faudra encore attendre
pour voir leur démocratisation).

Pour compiler ce programme sous linux, le plus simple est d'utiliser l'outil
make avec le Makefile fourni (dans la ligne de commande, tapez juste make en
étant à l'intérieur du dossier du Makefile).

Sinon, vous pouvez aussi effectuer la compilation manuellement en tapant en
ligne de commande (dans le dossier où se trouve ce fichier) :

cc hello_world.c -o hello_world.elf

Contributeurs : Rezal P18
*/

/*
                      Les directives du préprocesseur - 2**

Un programme en C commence toujours par des instruction qui précédées par un #
Ce sont des instructions pour le préprocesseur (un morceau du compilateur) pour
lui dire de faire certaines actions.

Les instructions du préprocesseur les plus importantes sont (à chaque fois il
faut remplacer foo par ce qui vous intéresse):

#include <foo.h> : Dit au compilateur que votre programme va utiliser
      la librairie "foo", et donc qu'il faut aller chercher cette librairie et
      la mettre à disposition

#if : Utilisé pour faire de la compilation conditionnelle, le code qui se trouve
      entre ce #if et le #endif associé ne sera compilé que si la condition dans
      le if est vérifié. Un cas d'usage classique sert à faire du cross
      plateforme, par exemple : "si on compile pour windows, on fait cela, sinon
      on fait autre chose".

#ifdef foo: raccourci pour #if defined(foo)

#elif : cf #if
#endif : cf #if
*/

/*
################################################################################
################## Première partie du programme : les inclusions ###############
################################################################################
*/

#ifdef __linux__
// i.e. si on est sous linux

/*

                                  stdio.h - 1*

La librairie standard pour la gestion d'entrée sorties (Input/Output).
En pratique vous en aurez besoin pour presque tous vos programmes puisque c'est
elle qui contient printf, l'une des fonctions les plus célèbres du C.
*/
#include <stdio.h>

#elif defined(__WIN32)
// Remarquez que #ifdef exists, mais pas #elifdef

/*

                                Windows.h - 1*

Windows a été écrit en C/C++ et pas vraiment pensé pour le C (contrairement à
Unix et Linux). Par suite le C n'y est pas aussi bien géré, en particulier :
 - Beaucoup d'API de Windows sont faites pour être utilisées en C++.
 - Presque toutes les librairies standards du C sous linux on été fondues en une
    seule grosse librairie que l'on peut utiliser grâce à windows.h
*/
#include <windows.h>

#endif

/*

                          Les fichiers header.h - 1*

Les fichiers visés par le #include (ceux qui finissent par un .h) ne sont pas
des librairies en tant que tel, ce sont des fichiers d'en-tête (header files).
Vous pouvez ouvrir ces fichiers avec n'importe quel éditeur de texte et vous
constaterez qu'ils ne contiennent pas de code, seulement des définition de
fonctions et de variables (et probablement aussi beaucoup de directives de
préprocesseur obscures).

Ces fichiers sont en fait utilisés principalement par le compilateur pour dire
si votre code est valable. Par exemple si vous essayez d'appeler printf sur un
entier, le compilateur saura grâce au header dire que cette syntaxe n'est pas
possible (le premier argument de printf est toujours une "chaine de
caractères".)

Les librairies C se trouvent en fait dans d'autres fichiers, souvent appellés
sous linux foo.so et sous windows foo.dll . Dans la plupart des langages
modernes le besoin de ces fichiers headers a disparu (ils sont souvent fusionnés
avec la librairie elle même). Cela étant le C n'est pas un langage moderne (du
tout), d'où cette séparation entre librairie et header, à laquelle on se fait
très vite.

Pour la petite histoire, une des raisons qui justifie l'existence de ces headers
est un découplage entre interface et implémentation. Deux librairies peuvent
utiliser des implémentations complètement différentes d'une même fonction,
lorsque vous appellez depuis votre code en C cela ne fait pas de différence
puisque l'interface à laquelle vous les appelez (le fichier header) est la même.
Notez cependant que dans les langages modernes l'interface et l'implémentation
sont effectivement découplés même sans fichiers header.

tl;dr : les fichiers headers.h sont un artefact d'un époque depuis longtemps
révolue, mais pour utiliser une librairie probablement appellée libFoo.so (ou
libFoo.dll) il vous faudra demander au compilateur le fichier header Foo.h.
*/

/*
################################################################################
################## Deuxième partie du programme : les prototypes ###############
################################################################################
*/

/*

                            Prototypes - 1*

En C, pour appeller une fonction dans votre code il faut avoir défini cette
fonction au préalable, faute de quoi le compilateur vous jetera une erreur de
fonction non définie.

Les fonctions que vous appelez peuvent être définies :
 - Soit dans des fichiers headers que vous avez inclus plus haut.
 - Soit au début du programme en donnant le prototype de la fonction.

Le prototype d'une fonction ne comprend pas de code executable, il ne s'agit que
d'une interface pour dire au compilateur comment votre fonction se comporte.
Dans sa forme la plus simple, un prototype de fonction aura la forme (remplacer
à chaque fois <foo> par la valeur correspondante).

<type de retour> <nom de fonction> (<type d'argument> <nom de l'argument> etc);

Plus bas vous avez un exemple de prototype de fonction simple.

Remarquez que le prototype d'une fonction seul ne suffira pas au compilateur, il
faut aussi que vous écriviez le corps de votre fonction à un endroit.
Cela est généralement fait en bas du programme, après le main.

La raison de la présence de ces prototypes est la même que pour les fichiers
header, ils permettent de séparer l'implémentation de la fonction (en bas du
programme) de son interface (déclarée en haut dans les prototypes).

Tout comme pour les fichiers header, la nécessité de prototypes a disparue dans
les langages modernes.

tl;dr : Si vous créez une fonction dans votre programme, il faut que vous
la déclariez dans les premières lignes en écrivant son prototype, sinon le
compilateur vous dira que vous utilisez une fonction non définie.
*/

// Un exemple de prototype de fonction en C
int add(int a, int b);

/*
################################################################################
##################### Troisième partie du programme : le main ##################
################################################################################
*/

/*

                                  Le main - 1*

La fonction main en C (d'autres langages comme Java ont repris ce concept) est
le point d'entrée de votre programme, c'est par là que commencera l'éxecution de
votre code lorsque vous lancerez le programme compilé.

Le main est une fonction traitée d'une façon un peu particulière par le
compilateur, et vous n'avez pas à déclarer de prototype pour le main de votre
programme. D'ailleurs vous n'avez pas le choix, le main en C n'a qu'un seul
prototype possible:

int main(int argc, char *argv[]);

MAIS

La plupart des compilateurs modernes sont très gentils et si vous mettez comme
prototype :

void main(int argc, char *argv[])

ou

int main()

le compilateur fera des substitutions dans votre code pour que cela revienne au
même.

De la même façon, si le prototype de votre main stipule que vous allez renvoyer
un entier mais que vous oubliez de mettre un return, le compilateur supposera
que vous revoyez 0 à la fin de l'exécution du main.

Ce ne sont que des conventions, et elles ne sont pas forcément respectées par
tous les compilateurs, mais cela peut parfois vous simplifier le vie.

Notez qu'un programme en C n'aura pas forcément de main, en particulier s'il
s'agit d'une librairie.
*/

int main(int argc, char *argv[]) {

  /*

                                printf - 1*

  printf (pour print format) est l'une des fonctions les plus connues en C,
  et avec ses variantes (notamment sprintf) ce sont parmi les fonctions les plus
  utiles du C.

  Le prototype de printf (simplifié est :

  int printf (char *format, ...);

  Passant pour l'instant sur la valeur de retour de printf qui n'est presque
  jamais utilisée, printf prend en argument un char * et "...".

  Sans rentrer dans le détail, char * désigne ici une chaine de caractères qui
  est un format, c'est à dire une chaîne de caractères dont certains caractères
  seront remplacés par des valeurs qui se trouvent dans le "..." .

  En fait printf est un type de fonction très rare en C (et très difficile à
  écrire) : c'est une fonction variadique, c'est à dire une fonction avec un
  nombre d'arguments variables (il n'est pas important de retenir cela, je le
  met juste içi pour information). L'implémentation de la fonction printf est
  très complexe mais son utilisation est très facile.

  Dans la chaine de caractères format :
    %s sera remplacée par une chaîne de caractères,
    %d sera remplacé par un type entier (signé ou non) plus petit que 4 octets,
          notamment int et uint;
    %f sera remplacé par un type flottant (signé ou non) plus petit que 4
          octets, notamment float;
    %ld sera remplacé par un type entier (signé ou non) plus grand que 4
          octets mais plus petit que 8, notamment long int et size_t;
    %lf sera remplacé par un type flottant (signé ou non) plus grand que 4
          octets mais plus petit que 8, notamment double;
    \n désigne un retour à la ligne (comme dans n'importe quelle chaîne de
          caractères)

  Pour savoir quel argument remplacer à quel endroit, il est possible de leur
  donner des numéros (cf la documentation de printf, je n'ai pas envie de
  détailler içi), mais la plupart du temps printf va juste remplacer les
  éléments dans l'ordre.

  Sans doute trouvez vous que cette syntaxe est très complexes (quoique dans le
  code plus loin vous verrez que c'est assez simple), mais la raison pour
  laquelle cette fonction est beaucoup aimée est que le C est en langage de bas
  niveau dans lequel il serait sinon très difficile d'effectuer ces
  substitutions.
  */

  // Déclaration d'une variable simple en C.
  int a = 2;
  // ici %d va être subtitué par la valeur de a, à savoir 2.
  printf("L'entier a vaut %d\n", a);

  int b = 3;
  int c = 4;
  float d = 8.6;

  // Un exemple de printf avec des substitutions multiples.
  printf("Les variables que l'on a déclarées valent %d %d %f\n", b, c, d);

  /* Remarque : la syntaxe
  printf("Hello World\n");
  est une syntaxe valable mais elle est déconseillée et votre compilateur va
  peut-être vous jeter des avertissements si vous faites cela.
  */
  printf("%s\n", "Hello World!");

  // Un exemple d'appel de fonctions en C
  int a_plus_b = add(a, b);

  printf("La somme de a et b vaut %d\n", a_plus_b);
  return 0;
}

/*
################################################################################
############# Dernière partie du programme : les fonctions annexes #############
################################################################################
*/

// La première ligne d'une déclaration de fonction en C est son prototype
int add(int a, int b) {
  // Les accolades sont obligatoires en C, tout comme les points virgules en fin
  // de ligne.

  // Les variables définies à l'intérieur d'une fonction ne sont pas accessibles
  // depuis l'exterieur.
  int result = a + b;

  // On retourne la valeur de la variable result.
  return result;
}

/*

                              Pass by value - 1*

Un élément important à comprendre sur le C est que ce n'est pas un langage
orienté objet (en fait le concept d'orienté objet n'était pas très répandu
lorsque le C a été défini). Par suite il n'est pas possible de passer de
référence vers une variable puisque ce concept est (assez) lié à l'existence
d'objets.

Une conséquence importante de cela est que les arguments des fonctions sont
toujours passés par valeur (c'est à dire que si vous écrivez :

d = add(a,b);

lors de l'execution c'est la valeur de a et la valeur de b qui seront
accessibles dans la fonction (donc on ne pourrait pas modifier leur valeur
depuis l'intérieur de la fonction). De même, d ne deviendrait pas égal à la
variale locale result, mais simplement à la valeur de result . C'est comme si on
copiait la valeur de result dans d.

Cette notion de pass by value est certainement un peu abstraite pour l'instant,
mais au moment de parler de pointeurs elle prendra toute son importance.
*/

/*
                                Le mot de la fin

Le C est un langage assez différent de langages comme Python ou Java car il est
beaucoup plus bas niveau (et ancien) et c'est pour cela que certaines notions
doivent être expliquées avant de commencer à pouvoir faire des choses
intéressantes.

Cela étant le C n'est pas un langage compliqué (au contraire). Il a été pensé
pour être agréable d'utilisation et consistant. La principale difficulté que
l'on rencontre en débutant en C est que la plupart des autres langages sont
beaucoup plus abstraits que le C, dont les concepts pourtant simples vont
sembler rebutant.

Le C est un langage à la fois simple à comprendre, rapide à écrire mais
également extrèmement puissant, ce qui explique en grande partie pourquoi il
reste encore aujourd'hui très utilisé dans beaucoup de domaines (notamment les
systèmes embarqués et tout ce qui a à voir avec le hardware). Notez cependant
que le C n'est pas sans défauts, en particulier en ce qui concerne les états
indéfinis (Undefined Behavior).

Sachez aussi que vous avez vu dans ce programme beaucoup de notions un peu
pénibles (directives préprocesseur, headers et la syntaxe de printf) qui sont
énormément utilisés mais que vous n'aurez à comprendre qu'une seule fois (et de
toute façon cela viendra rapidement avec la pratique).

Notez cependant que le C prédate internet de prêt de 30 ans, par suite ce n'est
pas le langage sur lequel il est le plus evident d'obtenir de la documentation
en ligne (même si vous trouverez le plus souvent les réponses à vos questions).
Notez toutefois que sous Linux une documentation extensive du C est disponible
hors ligne avec man (essayez par exemple man 3 printf).

Enfin, remarquez que 90% de ce fichier est fait de commentaires, si vous
réécrivez le code réellement utile il tient sur quelques lignes.
*/
