/*
Ce fichier constitue la seconde partie du tutoriel sur la compilation avancée
en C. La première partie de ce tutoriel se trouve dans le dossier pile.

Le but de ce tutoriel est de montrer comment réutiliser une librairie que vous
avez écrite vous même dans votre code. Comme dans l'autre partie du tutoriel,
beaucoup d'informations se trouve dans le Makefile en non dans le code en C.

Le programme qui sert de support à ce tutoriel est une mini calculatrice (comme
l'indique le nom du fichier). Cette calculatrice va prendre en argument une
ligne de calculs parenthésés avec des +, -, * et / et résoudre tout le calcul
d'un coup en respectant les priorités opératoires. Notez que la calculatrice
n'est pas interactive et qu'elle est insensible au espaces et aux retours à la
ligne. Notez aussi que cette calculatrice a certainement beaucoup de bugs, ne
m'en tenez pas rigueur.

Ce tutoriel est probablement le dernier que vous lirez dans cette série (à
l'exception de celui sur les états indéfinis pour les plus courageux) et
constitue aussi un petit best of de tout ce qui a été vu jusqu'ici, donc si vous
n'avez pas lu les tutoriels précédents vous risquez d'avoir un peu de mal à
suire celui ci.

Contributeurs : Rezal P18
*/

/*

            Comment implémenter une telle calculatrice en C ? - 3***

Il y a beaucoup de façon de faire un tel programme en C, celle que nous allons
montrer ici utilisant des piles (et un espèce d'héritage) n'est clairement pas
la plus simple, mais elle a le mérite d'être assez abstraite et de montrer
plusieurs aspects intéressants du C. La logique pourrait facilement (et à
profit) être transportée en Java ou en Python sans trop d'efforts.

Au début du programme, on va définir une expression (mathématique) comme une
pile de symboles, un symbole pouvant être soit un nombre, soit un opérateur. En
plus de cela on définit notre calcul comme étant une pile d'expressions. Au fil
de notre calcul on va s'appuyer qur le fait que dans une expression mathématique
valable on trouve toujours une alternance de nombres et d'opérateurs.

Dans un premier temps on va lire ce qui nous a été donné en entrée. On va lire
alternativement un nombre, puis un symbole etc... Pour résoudre les opérations
mathématiques dans l'ordre qui convient, nous allons définir un attribut
"precedence". Lorsque l'on rencontrera un '*' ou un '/' dans notre entrée on
mettra cet operateur à 1, puis au moment de lire le nombre suivant on fera le
calcul directement sans le mettre dans la pile. Par exemple :

Etape 0:
Expr : (vide)
Input : 1 + 2 * 4

Etape 1: On lit un nombre et on le met dans la pile
Expr : [1]
Input : + 2 * 4

Etape 2: On lit un symbole et on le met dans la pile
Expr: [1, +]
Input : 2 * 4

Etape 3 :
Expr : [1, +, 2]
Input : * 4

Etape 4 : On récupère un *, donc on le met dans la pile et on active la
précédence
Expr : [1, +, 2, *]
Input : 4
PRECEDENCE

Etape 5 : On récupère un nombre, et comme la précédence est active on va vider
les deux derniers éléments de la pile pour faire le calcul de la valeur qui
doit aller dans la pile en respectant les précédences d'opérateurs
Expr : [1, +, 8]
Input : (vide)

A la fin on aura juste à faire toutes nos opérations en vidant la pile  pour
trouver le résultat.

Une autre chose à gérer est l'usage de parenthèses dans le calcul. Pour cela
la règle que l'on va adopter est que dès que l'on trouve une parenthèse en input
on met l'expression courante dans la pile du calcul et on ouvre une nouvelle
expression. Lorsque 'on rencontre un parenthèse fermante on rèsout l'expression
en cours et on son résultat à la fin de l'expression précedente dans la pile.
Par exemple :

Etape 0:
Calcul : (vide)
Expr : (vide)
Input : 1 + 2 - (4 + 3)

Etape 4: (Je vais vite sur le début, vous avez comprsi le principe)
Calcul : (vide)
Expr : [1, +, 2, -]
Input : (4 + 3)

Etape 5: On remarque un parenthèse donc on ouvre une nouvelle expression
Calcul : [[1, +, 2, -]]
Expr : (vide)
Input : 4 + 3)

Etape 8: (Idem, je passe cette partie)
Calcul : [[1, +, 2, -]]
Expr : [4, +, 3]
Input : )

Etape 9: On récupère un parenthèse fermante, donc on résout l'expression
en cours et on renvoie son résultat son résultat sur le haut de la pile de
l'expression de la pile précédente.
Calcul : (vide)
Expr : [1, +, 2, -, 7]
Input : (vide)

L'input est vide donc on résout l'expression et on a finit.
*/

/*
################################################################################
################## Première partie du programme : les inclusions ###############
################################################################################
*/

/*
Toutes les déclarations de tous les fichiers de la calculatrice se trouvent dans
le header calculatrice.h

Ce fichier ne contient que le main du programme et la fonction next. Le fichier
symbole.c contient le code source de toutes les méthodes en lien avec les
symboles, expression.c contient tout le code source des routines liées aux
expressions et calcul.c les routines liées au type calcul (elles sont toutes
déclarées dans calculatrice.h).
*/
#include "calculatrice.h"

/*

Note importante : A moins que vous ne soyez intéressés par l'implémentation
de la calculatrice, je vous conseille de passer directement au mot de la fin
pour les idées importantes.

*/

/*
################################################################################
################## Deuxième partie du programme : les prototypes ###############
################################################################################
*/

/*
Ils sont déjà déclarés dans calculatrice.h, ici le seul qui nous concerne est :

extern int next(Calcul *calc, Expression *expr);
*/

/*
################################################################################
##################### Troisième partie du programme : le main ##################
################################################################################
*/

int main(int argc, char const *argv[]) {
  /*
  En raison de tout le travail qui a déjà été fait dans les autres fichiers,
  le main de calculatrice est assez simple. On commence par créer les variables
  sur lesquelles toutes les sous fonctions vont travailler.
  */
  Symbole symb;
  Expression expr;
  Calcul calc;
  /*
  Il nous faut tout de même initialiser calc et expr pour la première itération
  */
  new_calc(&calc);
  new_expr(&expr);
  /*
  Puis on fait tourner next jusqu'à arriver au résultat.
  */
  int status;
  int continuer_boucle = 1;
  do {
    status = next(&calc, &expr, &symb);
    switch (status) {
    case -1:
      fprintf(stderr, "%s\n", "Une erreur est survenue pendant le calcul");
      continuer_boucle = 0;
      break;
    case 1:
      printf("Le résultat est : %f\n", nb(&symb));
      status = 0;
      continuer_boucle = 0;
      break;
    case 0:
      // Le calcul se poursuit, nous n'avons rien de plus à faire ici.
      break;
    default:
      fprintf(stderr,
              "Votre calcul a atteint un état inconsistant %d,"
              " le programme abandonne\n",
              status);
      status = -1;
      continuer_boucle = 0;
      break;
    }
  } while ((status == 0) && continuer_boucle);
  return status;
}

/*
################################################################################
############# Dernière partie du programme : les fonctions annexes #############
################################################################################
*/

int next(Calcul *calc, Expression *expr, Symbole *symb) {
  // On met à jour l'expression courante.
  int status = next_expr(expr, symb);

  switch (status) {
  case 0:
    /*
    i.e. l'expression a été mise à jour sans rien d'intéressant, status est
    déjà à la bonne valeur.
    */
    break;
  case -1:
    // i.e. on a rencontré un problème, on se contente de propager
    expr->next = INVALIDE;
    break;
  case 1:
    /*
    i.e. on a rencontré une parenthèse fermante (ou EOF) et résolu
    l'expression en cours. Il nous faut alors récupérer l'expression
    précédente de la pile et lui ajouter symb. Notez que si nous faisons juste
    un pop l'expression qui aura été obtenue de la pile sera perdue à la fin
    de l'execution de notre fonction, popur éviter cela il nous faut la copier
    dans expr (en supposant que l'expression passée entre deux appels sera
    bien la même, comme demandé dans la documentation).
    */
    status = calc_pop(calc, expr);
    switch (status) {
    case 0:
      // i.e. on a bien récupéré une expression du calcul, on continue.
      /*
      Il ne faut plus qu'ajouter le résultat de l'expression précédente
      (celle entre parenthèses) à la nouvelle expression courante. Il faut
      tenir compte des précédences d'opérateurs ici, c'est pourquoi on
      appelle partial resolve et pas juste append.
      */
      status = partial_resolve_expr(expr, symb);
      // Si tout s'est bien passé status = 0, sinon status = -1
      break;
    case -1:
      /*
      i.e. la pile de calc est vide, on se contente de propager au main qui
      va afficher le résultat (qui est celui de la dernière expression, donc
      contenu dans symb).
      */
      status = 1;
      break;
    }
    break;
  case -3:
    /*
    i.e. on a trouvé une parenthèse ouvrante, on append l'expression courante
    sur le calcul et on crée un nouvelle expression.
    */
    calc_append(calc, expr);
    // On crée notre nouvelle expression pour continuer le calcul.
    new_expr(expr);
    // Rien d'intéressant pour le main
    status = 0;
    break;
  default:
    // Cas absurde
    fprintf(stderr,
            "Votre calcul a atteint un état inconsistant %d,"
            " le programme abandonne\n",
            status);
    status = -1;
    break;
  }
  return status;
}

/*

                            Le mot de la fin

En regardant ce tutoriel (et encore plus si vous n'avez regardé que ce fichier),
une reflexion que vous vous êtes probablement faite est :
Pourquoi y a-t-il autant de code pour faire une simple calculatrice ? C'est
pourtant simple une calculatrice, non ?

La réponse à cette question est malheureusement non, un calculatrice n'est pas
simple à programmer. Une exception à cela est la calculatrice en écriture
polonaise inverse que vous avez probablement déjà écrite en TP d'informatique.
La différence entre une calculatrice classique et une calculatrice polonaise
inversée faite en TP semble pourtant tenir à peu de choses : l'ordre dans lequel
on donne les opérateurs, nombre opérateur nombre pour une calculatrice classique
contre nombre nombre opérateur en notation polonaise inversée et la présence de
parenthèses dans une calculatrice classique.

Pourtant ces deux changements (en particulier la présence de parenthèses)
induisent une différence fondamentale entre ces deux types de calculatrice :
la calculatrice classique va effectuer les opérations non pas dans l'ordre où
elles viennent mais suivant une syntaxe prédéfinie. L'existence de cette syntaxe
fait que la calculatrice classique et la calculatrice en écriture polonaise
inversée appartiennent en fait à deux catégories de problèmes différents : là où
la calculatrice polonaise inversée est un problème de piles assez sommaire, la
calculatrice classique est l'exemple minimal de langage de programmation.
D'ailleurs si vous cherchez des outils permettant de définir un langage de
programmation il est probable que leur exemple introductif soit une
calculatrice.

L'implémentation que nous avons suivie ici correspond d'ailleurs
(involontairement) à ce qu'il faudrait faire pour implémenter un langage de
programmation. Le fichier symbole.c contient notre embryon de lexer, et la
logique de notre parser est gérée surtout dans expression.c . Dans calcul.c on
trouve enfin une implémentation sommaire d'un système de stack memory évoquant
ce qui existe pour gérer les appels de fonctions dans un langage de
programmation comme le C.

Je me permet toutefois de soulever deux points importants à ce sujet : d'une
part notre implémentation ne se voulais par particulièrement être celle d'un
parser + lexer donc les frontière y sont un peu brouillées (ne pensez pas que
les fichiers dans ce tutoriel constituent un exemple parfait de cette
structure), d'autre part si jamais vous avez l'envie d'essayer définir vous même
un langage de programmation:
 - C'est en pratique assez difficile à faire parce que les parser fonctionnent
 d'une façon assez contre intuitive et vous devez malgré tout faire beaucoup de
 choses vous même;
 - NE RECODEZ PAS TOUT EN C A PARTIR DE 0 ! J'imagine que peu d'entre vous
 auraient cette idée de toute façon, mais le cas échéant cela se solderait
 au pire par un échec et au mieux (peu probable) par une immense perte de temps.
 Il existe beaucoup de librairies qui vont gérer parser + lexer beaucoup mieux
 que vous ne le feriez vous même (en particulier python a des packages assez
 pratiques si vous souhaitez apprendre).

Outre le fait qu'il soit assez poétique de finir un tutoriel sur un langage de
programmation par la façon dont on peut s'en servir pour coder d'autres langages
de programmation, cela me permet d'insister sur deux éléments importants. Ceux
qui ont lu tous les fichiers de ce tutoriel (probablement peu de gens) auront
peut-être remarqué cela, mais le C est un langage particulièrement adapté pour
définir des langages de programmation. Il est très proche de la machine donc il
n'y a quasiment aucune surcouche due au langage à l'exécution; il est capable de
suffisamment d'abstraction pour réaliser des projets complexes et suffisamment
bas niveau pour que tout ce qu'il semble possible de faire avec des octets
puisse être écrit en C.

La deuxième chose importante que je voulais souligner est que malgré toutes ces
qualités, le C n'est pas un langage adapté à tous types de situations. Comme
les lecteurs les plus assidus auront pu le constater, à mesure que la complexité
de votre projet croit, il devient de plus en plus difficile de faire abstraction
de de la façon dont le C fonctionne pour écrire votre code (notamment comprendre
comment stack memory et heap memory fonctionnent), et de plus dans la mesure où
le langage n'est pas orienté objet il n'est pas possible d'y séparer
complétement l'interface d'un concept abstrait de son implémentation. Cela
requiererait l'un des principaux apports de la programmation orientée objet :
l'inversion de dépendances (regardez sur internet ou dans le fichier
calculatrice.h si vous êtes intéressés).

La moralité de cela est que le C est un langage très puissant, mais pour des
projets de grandes tailles, ou bien pour des programmeurs qui n'y sont pas
habitué, les langages orientés objets (et Java en tête de liste) seront plus
adaptés. L'abstraction supplémentaire que proposent ces langages permet en outre
de ne pas avoir à se poser de questions sur leur fonctionnent interne, (vous
pouvez écrire du code très complexe en Java sans avoir la première idée de la
façon dont Java gère sa mémoire). Ce regain d'abstraction vous évitera aussi
beaucoup de bugs plus ou moins coriaces dont le C est par ailleurs friand.

La programmation orientée objet et (au passage) les 50 années d'évolution de la
programmation depuis l'apparition du C ont apporté beaucoup d'innovations dont
il serait vraiment dommage de se priver sans une bonne raison. Le C marque
un tournant dans l'histoire de l'informatique, et même aujourd'hui reste un
outil tout à fait efficace dont il est toujours utile de se munir lorsqu'un
programme nécessite des manipulations très précises ou très bas-niveau
(manipulations d'octets etc...), domaines dans lequel la simplicité et la
liberté du C ont fait sa popularité autrefois et sa longévité jusqu'à
aujourd'hui.
*/
