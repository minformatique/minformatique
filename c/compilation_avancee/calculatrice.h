// Include once, cf pile.h
#ifndef HEADER_CALCULATRICE
#define HEADER_CALCULATRICE

/*
On définit ce header pour rendre plus court le reste du programme, il contient
notamment les définition des différents types utilisés par le programme
calculatrice.
*/

#include <stdio.h>
// Définit FLT_DIG
#include <float.h>
#include "pile.h"


/*

							Unions, héritage et inversion de dépendances - 3***

On définit notre type RawSymbole (qui peut être soit un nombre soit un operateur)
comme... un nombre ou un char. J'ai dit dans le tutoriel sur les structures
avancées que je n'avais pas trop d'idées de quoi faire des unions en C, mais içi
on a exemple très concret de ce à quoi elles peuvent servir. On pourra facilement
et proprement écrire nos fonctions sur le type RawSymbole duquel "héritent" les
types float et char, mais encore une fois il est impropre de parler d'héritage
en C.

La raison pour laquelle cela ne peut être appelé de l'héritage, et qui fait que
le C n'est pas un langage orienté objet vient d'une considération très pratique.
En C on définit RawSymbole comme étant un type pouvant être ou bien un float,
ou bien un char. Ceux d'entre vous qui ont déjà utilisé des langages orientés
objets remarquerons que la déclaration s'y ferait dans le sens inverse, on
commencerait par déclarer le type RawSymbole, puis au moment de définir float et
char on écrirait qu'ils héritent du type RawSymbole. Ce n'est donc plus le type
parent qui réfère aux types enfants mais les types enfants qui réfèrent au type
parent.

Ce menu détail est en fait au coeur de la notion de programmation orientée objet,
il s'agit du 'D' de l'acronyme 'SOLID' de la programmation orientée objet et
s'appelle le principe d'inversion des dépendances. Cela peut sembler anodin,
mais signifie en réalité que l'on opère un découplage entre l'interface d'un
concept et son implémentation concrète. Par exemple en C si je me rend compte
que la calculatrice que j'ai écrit fait toujours des calculs sur les flottants,
mais qu'il peut parfois être intéressant de faire des calculs en limitant les
opérations à des entiers, eh bien je suis parti pour devoir tout réécrire, parce
que mon interface (RawSymbole) fait directement référence à son implémentation
(ici float), et les routines que j'ai écrites exploitent en grande partie les
opérations sur les flottants. Si la calculatrice avait été écrite en Java,
ajouter les restrictions sur les opérations entières aurait été beaucoup plus
rapide, si ce n'est instantané.
*/
union RawSymbole {
	float nombre;
	char operateur;
};

/*	2**
Notez que lorsqu'une fonction récupère un RawSymbole, il ne lui est cependant
pas possible de savoir s'il contient un nombre ou un operateur. Dans notre cas
cela ne sera pas un problème car 1/2 symbole est un nombre, mais juste pour
montrer comment cela peut-être géré je vais définir le type Symbole d'une façon
sure. Pour cela il nous faut d'abord définir un enum qui permettra de tester le
type d'un symbole.
*/
enum TypeSymbole {
	NOMBRE,
	OPERATEUR,
	/*
	Invalide est utile pour éviter de se servir d'une valeur qui n'a pas de sens.
	*/
	INVALIDE
};

/*	2**
Le type Symbole sera alors l'aggrégation de ces deux éléments : un symbole et
son type. Afin de garantir la sureté du Symbole, il faut juste s'assurer que
toutes les manipulations sur les Symbole sont gérées par des méthodes adaptées
et donc ne pas définir de routines sur le type RawSymbole; tout se fera au
travers de Symbole. Encore une fois cela n'est pas nécessaire ni utile dans
notre cadre, mais je voulais montrer comment faire ce genre de choses.
*/
struct Symbole {
	enum TypeSymbole type;
	union RawSymbole valeur;
};

/*
Notez qu'il est assez contradictoire de définir un type Symbole sûr alors que
notre implémentation des piles est on ne peut plus risquée, cf le tutoriel sur
les état indéfinis et les difficultées rencontrées lors de l'implémentation.
*/

/*	2**
Le type précedence, utilisé pour gérer la précédence dans les opérateurs
mathématiques (cf calculatrice.c). On autait pu juste utiliser un int mais je
voulais rester cohérent donc j'en ai fait un enum.
*/
enum Precedence {
	TRUE,
	FALSE
};

/*	2**
Définissons aussi le type expression, qui est une pile de symboles. Pour plus de
simplicité de l'écriture des méthodes, on va décorer ce type de plusieurs
attributs:
 - l'attibut précédence dont le rôle est détaillé dans calculatrice.c
 - Un attibut next qui nous dit si le prochain élément à récupérer est un nombre
ou un opérateur en s'appuyant sur leur alternance.
 - La pile en elle même. Notez que comme toutes les opérations sur les piles sont
définies sur des pointeurs de piles je met directement un pointeur en attribut
afin d'alléger la syntaxe plus tard. Notez aussi que ce n'est finalement pas
comme cela qu'est définie la pile dans ce fichier. Au début j'avais fait ce qui
est écrit précédemment, c'est à dire déclaré pile comme un (struct Pile *) mais
en fait en faisant cela on déclare un pointeur vers une pile qui n'existe pas
(i.e. il n'y a pas de mémoire reservée derrière ce pointeur), donc dès que l'on
essaie d'y accéder on rencontre une segmentation fault.

Je réitère donc ce que j'ai écrit dans le tutoriel sur les structures avancées :
pas de pointeurs dans les attributs d'une structure sauf si vous êtes certains
de ce que vous faites.
*/
struct Expression {
	enum TypeSymbole next;
	enum Precedence precedence;
	struct Pile pile;
};

/*	2**
De la même façon on définit aussi le type calcul comme une pile d'expressions.
On décore cela en gardant en mémoire la hauteur de la pile afin d'afficher un
message s'il y a un problème de parenthésage dans l'expression
*/
struct Calcul {
	size_t hauteur;
	struct Pile pile;
};


/*
Pour que l'écriture de tous le code soit moins lourd syntaxiquement on définit
aussi des alias vers les différentes structures que l'on a créées.
*/
typedef struct Symbole Symbole;
typedef struct Expression Expression;
typedef struct Calcul Calcul;




/*
	(le reste est sans importance, passez directement aux autres fichiers)
*/




/*
On déclare ici aussi tous les prototypes de fonctions dont on aura besoin.
*/
// Initialisation d'un symbole.
extern int new_symb_nb(Symbole *symb, float nombre);
// Remarquez que le C ne supporte pas la surcharge de méthodes.
extern int new_symb_op(Symbole *symb, char operateur);

/*
Raccourcis pour accéder rapidement aux valeurs du Symbole et d'une façon
définie.
*/
extern float nb(Symbole *symb);
extern char op(Symbole *symb);

/*
Cette routine permet de lire le prochain symbole sur l'input en s'appuyant sur
le type attendu par l'expression en cours. Cette méthode est appellée en interne
par la méthode next définie à la fin du fichier header. Sa valeur de retour est:
 - 0 si on a bien trouvé ce à quoi on s'attendait,
 - -3 si on s'attendait à un nombre mais on a trouvé une parenthèse ouvrante,
 - -2 si on a atteint la fin de l'input (EOF) ou une parenthès fermante,
 - -1 en cas de problème
*/
extern int next_symb(Symbole *symb, enum TypeSymbole type);

/*
On définit aussi toutes nos opérations sur les expressions.
*/
extern int new_expr(Expression *expr);
extern int expr_append(Expression *expr, Symbole *symb);
extern int expr_pop(Expression *expr, Symbole *symb);
extern int free_expr(Expression *expr);

/*
Cette routine est celle utilisée pour résoudre toute l'expression lorsqu'il
n'y a plus de données en entrée ou bien que l'on rencontre un parenthèse
fermante. Elle renvoie :
	- 0 si tout s'est bien passé.
	- -1 si une erreur est survenue
*/
extern int resolve_expr(Expression *expr, Symbole *symb);

/*
Méthode de haut niveau qui va gérer le fait d'ajouter un symbole à notre
expression, en appelant les append (et pop) nécessaires et en gérant le calcul
direct s'il y a précédence d'opérateurs. Elle est appelée par next_expr mais
aussi next.

Cette fonction renvoie :
- 0 si on a ajouté un symbole sur l'expression,
- -1 si on a rencontré un problème insoluble
*/
extern int partial_resolve_expr(Expression *expr, Symbole *symb);

/*
Cette routine gère le fait de lire le prochain symbole sur l'input et le fait de
résoudre l'expression courante si besoin, et renvoie alors le résultat de
l'expression dans symb. Cette fonction retourne :
 - 0 si on a ajouté un symbole sur l'expression,
 - 1 si on a résolu l'expression et marqué le résultat dans symb,
 - -1 si on a rencontré un problème insoluble
 - -3 si on a trouvé une parenthèse ouvrante (pour être cohérent avec next_symb)
*/
extern int next_expr(Expression *expr, Symbole *symb);

/*
Enfin on définit nos routines sur le type calcul.
*/
extern int new_calc(Calcul *calc);
extern int calc_append(Calcul *calc, Expression *expr);
extern int calc_pop(Calcul *calc, Expression *expr);
extern int free_calc(Calcul *calc);

/*
Il ne nous reste plus qu'à définir des routines qui feront avancer notre
programme. La méthode next va, en mettant à jour calc et expr, lire le prochain
symbole sur stdin.

Attention, pour fonctionner cette méthode a besoin qu'on lui repasse la même
expression entre deux appels (notamment lorsque l'on fait un pop sur calc).

next renvoie :
 - 0 si le calcul se poursuit
 - 1 si le calcul est achevé
 - -1 en cas d'erreur

A la fin du calcul, le résultat sera nb(symb).
*/
extern int next(Calcul *calc, Expression *expr, Symbole *symb);

#endif
