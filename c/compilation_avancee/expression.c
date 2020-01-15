/*
Ce fichier fait partie du tutoriel compilation avancée et est utilisé afin
d'implémenter une calculatrice assez simple. Il contient le code source de
toutes les routines liées au type Expression déclarées dans calculatrice.h
*/

/*
################################################################################
################## Première partie du programme : les inclusions ###############
#################################################################################
*/

#include "calculatrice.h"

/*
################################################################################
################## Deuxième partie du programme : les prototypes ###############
################################################################################
*/

/*
Ils sont déjà déclarés dans calculatrice.h :


extern int new_expr(Expression *expr);
extern int expr_append(Expression *expr, Symbole *symb);
extern int expr_pop(Expression *expr, Symbole *symb);
extern int free_expr(Expression *expr);
extern float resolve_expr(Expression *expr);
extern int next_expr(Expression *expr, Symbole *symb);
*/

/*
################################################################################
##################### Troisième partie du programme : le main ##################
################################################################################
*/

/*
Pas de main ici, il se trouve dans calculatrice.c
*/

/*
################################################################################
############# Dernière partie du programme : les fonctions annexes #############
################################################################################
*/

int new_expr(Expression *expr) {
  // Une expression commence toujours par un nombre, donc pas de -1 par exemple.
  expr->next = NOMBRE;
  expr->precedence = FALSE;
  // Note : new_pile renvoie toujours 0.
  return new_pile(&(expr->pile));
}

int expr_append(Expression *expr, Symbole *symb) {
  // Première chose : on ajoute le symbole sur la pile.
  /*

                  Les difficultées d'implémentation - 4****

  (Grosse digression ici pour expliquer ce qui suit)
  Vous vous souvenez peut-être que dans mon implémentation des piles j'ai écrit
  que le choix d'utiliser des pointeurs n'était pas le meilleur que l'on puisse
  faire... et bien c'est maintenant que l'on paie cela. Le problème est un peu
  complexe, mais en gros le fait est que d'avoir mixé l'approche struct + union
  (pour les Symboles) et pointeurs (pour les piles) pour faire de l'héritage,
  toute intéressante du point de vue pédagogique qu'elle soit, fait que je suis
  à présent dans une position pire que si je n'avais fait que l'un ou l'autre.

  En gros lorsque j'arrive ici deux choix s'offrent à moi pour stocker le
  symbole dans la pile : par copie ou mapping.

  Si j'essaie de mapper la valeur (i.e. de mettre son pointeur dans la pile) je
  vais avoir un problème. En effet vu que nos symboles sont déclarés sur la
  stack (la plus haute), le code dans lequel on les déclare ressemble à :

  while (<il reste des choses dans l'input>) {
    Symbole symb;
    next(...)
  }

  Le problème est qu'en écrivant les choses ainsi entre deux passages dans la
  boucle symb reste la même variable (i.e. l'adresse en mémoire de symb ne
  change pas). Mais du coup lorsque je vais enregistrer ce pointeur dans ma
  pile, il continuer lors des autres itérations de la boucle à pointer vers
  l'adresse de symb qui sera réecrite dans les autres itérations. J'aurai donc
  une pile remplie uniquement par une seule valeur.

  Une solution serait donc de travailler par copie, c'est à dire de recopier les
  valeurs de symb derrière un pointeur de la pile. Mais si je choisis de faire
  cela je vais me heurter au fait que les pointeurs de la pile correspondent à
  des adresses aléatoires qui n'ont pas été associées au programme, donc si je
  tente d'écrire dessus j'aurai une segmentation fault.

  Si j'avais dès le début utilisé des struct + unions, j'aurais pu utiliser
  l'approche par copie sans problèmes parce que la mémoire de la pile aurait été
  initialisée. Si au contraire j'avais utilisé des void * partout j'aurais
  simplement utilisé un malloc pour déclarer mes symboles, et alors j'aurais pu
  mapper leurs valeurs dans la pile sans questions puisque leurs adresses
  seraient à des endroits différents de la heap memory.

  Clairement l'approche avec uniquement des structs + unions aurait été beaucoup
  plus efficace et simple, mais puisque j'en suis arrivé là il faut trouver une
  solution. Il ne m'est pas possible de déclarer un Symbole local et d'utiliser
  son adresse pour la mettre dans la pile car elle serait dans la stack et donc
  plus valide un fois la fonction terminée. Il me semble n'y avoir qu'une seule
  solution pour régler ce problème causé par un usage peu prudent de malloc et
  des pointeurs (void *)... plus de malloc et de pointeurs bruts! Je vais devoir
  demander depuis l'interieur de cette fonction un peu d'espace en heap pour
  stocker un symbole sur une nouvelle adresse, puis copier les valeurs de symb
  sur ce symbole et enfin mapper le pointeur de ma copie dans la pile de
  l'expression.

                            Complexification - 4****

  A cause de ce mauvais choix au tout début de l'écriture du code je dois
  maintenant faire une copie + un mapping à chaque symbole au lieu de faire soit
  l'un, soit l'autre. En plus à chaque appel de la fonction il faudra faire un
  nouvel appel de malloc, ce qui nous fait perdre du temps. On arrive avec une
  implémentation beaucoup moins efficace que ce qui aurait été fait en se tenant
  à struct + union ou même à des pointeurs seuls. Certains pourraient remarquer
  que l'on peut un peu réduire cette pénalité en faisant des malloc par paquets,
  c'est à dire en reservant d'un coup un grand espace mémoire pour tous nos
  symboles, puis en l'agrandissant (ou rétrecissant) au fil des besoins. Cette
  implémentation serait assez complexe, mais me permet d'illustrer un point
  important sur les logiciels en général : plus le temps et le travail depuis
  le création initiale d'un projet passe, plus maintenir et améliorer le projet
  devient complexe et coûteux. C'est en partie ce qui explique que des logiciels
  anciens et dont le fonctionnement devrait être simple ont souvent un code
  source très complexe et peu efficace. Comme vous pouvez le constater ici, des
  choix qui étaient juste discutables au début du projet (faire une pile de
  pointeurs pour se simplifier la vie) peuvent devenir critiques et très
  handicapants plus tard dans le projet.

  Cet effet est encore plus marqué en C parce que le langage est très punitif et
  beaucoup de considérations qui sont de l'ordre de l'implémentation machine
  (la gestion de la mémoire stack - heap) qui ne sont pas facilement visibles
  dans la conception abstaite d'un projet vont avoir un vrai rôle dans son
  écriture pratique contrairement à des langages plus abstraits comme python ou
  java. Cela étant comparé à ces langages il vous est aussi plus difficile de
  vous retrouver vraiment coincé et devoir repartir à 0 en C. Dans la mesure où
  le langage repose en grande partie sur des manipulations d'octets, tant que
  vous voyez une façon de résoudre votre problème, fût-ce octet par octet, alors
  il est possible de l'implémenter en C. Mais faites attention à rester
  rigoureux, sinon vous allez progressivement vous enfoncer en faisant
  graduellement apparaitre des problèmes de plus en plus difficiles à résoudre.

  Après ce long discours, place à l'implémentation :-)




  (Le reste de ce fichier contient essentiellement de l'implémentation, donc
  si cela ne vous intéresse pas vous pouvez directement passer à la suite)

  */

  // On reserve la mémoire nécessaire en heap
  Symbole *copie_symbole = malloc(sizeof(Symbole));
  // On copie les valeurs de symb dans le symbole en heap
  copie_symbole->type = symb->type;
  copie_symbole->valeur = symb->valeur;
  // Et enfin on mappe notre copie dans la pile.
  pile_append(&(expr->pile), (void **)&copie_symbole);

  // Deuxième chose : On modifie la valeur de next.
  switch (expr->next) {
  case NOMBRE:
    expr->next = OPERATEUR;
    break;
  case OPERATEUR:
    expr->next = NOMBRE;
    break;
  default:
    /*
    i.e. Si next est INVALIDE, ce qui est absurde. Au cas où on lance un
    warning et on revient dans l'état par défaut où l'on attend un nombre.

    Notez que normalement je devrais renvoyer une valeur d'erreur différente
    ici (par exemple -2) qui serait gérée dans les fonctions qui appelent
    expr_append, mais je n'ai pas envie de me rajouter du code pour un cas
    absurde qui n'arrivera pas dans ce tutoriel. Si j'étais en train de
    travailler (par exemple) sur du code pour un Boeing la question serait
    différente.
    */
    fprintf(
        stderr, "%s\n",
        "Votre expression est entrée dans un état"
        " inconsistant, attention à n'utiliser que les méthodes définies dans"
        " calculatrice.h pour modifier les expressions. L'expression a été "
        "remise"
        " dans un état connu pour éviter la propagation de l'erreur, mais le"
        " calcul va probablement échouer");
    expr->next = NOMBRE;
    break;
  }

  // Dernière chose : on gère active la précédence si symb contient un '*' ou
  // '/'
  if (symb->type == OPERATEUR) {
    char operateur = op(symb);
    // Attention à la précédence des opérateurs booléens en C
    if ((operateur == '*') || (operateur == '/')) {
      expr->precedence = TRUE;
    }
  }
  return 0;
}

int expr_pop(Expression *expr, Symbole *symb) {
  // Première chose : on récupère le symbole depuis la pile et on le copie
  /*
  On initialise le pointeur pour ne pas avoir de warning mais c'est pop qui va
  faire l'initialisation.
  */
  Symbole *popped_symb;
  int status = pile_pop(&(expr->pile), (void **)&popped_symb);
  if (status == -1) {
    /*
    Note : ce n'est pas une erreur à proprement parlé, on utilise ce -1 pour
    savoir quand on a lu l'expression en entier dans la routine resolve.

    Pour éviter les problèmes, on va tout de même signaler que le symbole est
    invalide.
    */
    symb->type = INVALIDE;
    return -1;
  }

  // else ...
  /*
  On copie les différents attributs dans symb. Le fait de faire cela permet
  d'avoir une signature plus simple (et plus cohérente) pour notre fonction.
  */
  symb->type = popped_symb->type;
  symb->valeur = popped_symb->valeur;
  // symb est maintenant initialisé correctement

  // Deuxième chose : on met à jour next
  switch (expr->next) {
  case NOMBRE:
    expr->next = OPERATEUR;
    break;
  case OPERATEUR:
    expr->next = NOMBRE;
    break;
  default:
    fprintf(
        stderr, "%s\n",
        "Votre expression est entrée dans un état"
        " inconsistant, attention à n'utiliser que les méthodes définies dans"
        " calculatrice.h pour modifier les expressions. L'expression a été "
        "remise"
        " dans un état connu pour éviter la propagation de l'erreur, mais le"
        " calcul va probablement échouer");
    expr->next = NOMBRE;
    break;
  }

  /*
  Dernière chose : si l'élément que l'on a vidé est un '*' ou un '/' il faut
  remettre la précédence à 0.
  */
  if (symb->type == OPERATEUR) {
    char operateur = op(symb);
    if ((operateur == '*') || (operateur == '/')) {
      expr->precedence = FALSE;
    }
  }
  /*
  Evidemment on paie aussi dans pop ce dont j'ai parlé dans append, il nous
  faut libérer au fur et à mesure l'espace dont nous n'avons plus besoin en
  heap.
  */
  free(popped_symb);
  return 0;
}

int free_expr(Expression *expr) {
  expr->next = INVALIDE;
  expr->precedence = FALSE;
  return free_pile(&(expr->pile));
}

int resolve_expr(Expression *expr, Symbole *symb) {
  /*
  A cause des précédences d'opérateurs, lorsque l'on appelle cette fonction
  notre expression ne contient plus que des '+' et des '-'. De plus, une
  expression valide doit toujours finir par un nombre. On commence par vérifier
  ce critère.
  */
  if (expr->next != OPERATEUR) {
    fprintf(stderr, "%s\n",
            "L'expression traitée est incomplète car elle se"
            " termine par un opérateur");
    symb->type = INVALIDE;
    return -1;
  }

  // else...
  /*
  Pour lire notre expression on va utiliser des pop en exploitant le fait que
  pop mette next à jour pour nous. Ainsi quand next vaut OPERATEUR, on pop un
  NOMBRE et quand next vaut NOMBRE, on pop un OPERATEUR. On s'arrète lorsque pop
  renvoie -1.
  */

  int return_value = 0;
  // Le status renvoyé par pop, utile pour savoir si on a vidé l'expression
  int pop_status;
  // Le symbole en haut de la pile.
  Symbole top;
  // Le résultat de l'expression.
  float result = 0;
  // Buffer contient nos valeurs intermédiaires lorsque nous faisons les calculs
  float buffer = 0;
  /*
  L'opérateur avec lequel on doit faire notre calcul. Il est important de bien
  voir comment notre résolution va se faire, prenons pour exemple l'expression :
  1 - 2 + 3

  L'algorithme de résolution proposé ici est :
  Etape 0 : (Etat initial)
  Expr : 1 - 2 + 3
  Buffer : 0
  Result  : 0

  Etape 1 : On récupère le nombre 3, on le met dans le buffer
  Expr : 1 - 2 +
  Buffer : 3
  Result  : 0

  Etape 2 : On récupère un +, donc on ajoute le buffer au résultat
  Expr : 1 - 2
  Buffer : (insignifiant)
  Result : 3

  Etape 3 : On récupère le nombre 2, on le met dans le buffer
  Expr : 1 -
  Buffer : 2
  Result : 3

  Etape 4 : On récupère un -, donc on soustrait le buffer au résultat
  Expr : 1
  Buffer : (insignifiant)
  Result : 1

  Etape 5 : On récupère le nombre 1, on le met dans le buffer
  Expr : (vide)
  Buffer : 1
  Result : 1

  Etape 6 : On atteint la fin de la pile de l'expression, donc on ajoute le
  buffer au résultat
  Expr : (vide)
  Buffer : (insignifiant)
  Resultat : 2
  */
  int continuer_boucle = 1;
  while (continuer_boucle) {
    // printf("result %f\n", result);
    // printf("buffer %f\n", buffer);
    pop_status = expr_pop(expr, &top);
    switch (pop_status) {
    case -1:
      // i.e. on a finit notre expression. On ajoute le contenu du buffer.
      result += buffer;
      // On écrit la valeur trouvé dans le symbole passé en argument
      new_symb_nb(symb, result);
      // On sort de notre boucle
      continuer_boucle = 0;
      return_value = 0;
      break;
    default:
      // i.e. on a récupéré un symbole
      switch (top.type) {
      case NOMBRE:
        // On a trouvé un nombre, on le place dans notre buffer.
        buffer = nb(&top);
        break;
      case OPERATEUR:
        switch (op(&top)) {
        case '+':
          result += buffer;
          break;
        case '-':
          result -= buffer;
          break;
        default:
          fprintf(stderr,
                  "Votre expression contient le symbole"
                  " %c qui empèche la résolution\n",
                  op(&top));
          symb->type = INVALIDE;
          /*
          Il y a un problème, il faut sortir de suite sans finir le calcul
          */
          continuer_boucle = 0;
          return_value = -1;
          break;
        }
        // Le break de "case OPERATEUR"
        break;
      default:
        // i.e. on a tiré une valeur invalide de notre expression, absurde
        fprintf(stderr, "%s\n",
                "Lors de la résolution de votre expression"
                " une valeur absurde est apparue");
        return_value = -1;
        continuer_boucle = 0;
        break;
      }
      // Le break de "default" dans switch pop_status
      break;
    }
  }
  return return_value;
}

int partial_resolve_expr(Expression *expr, Symbole *symb) {
  /*
  On a trouvé un symbole valide à ajouter à l'expression. Ce que l'on va
  faire maintenant dépend de la valeur de précédence.
  */
  int status = 0;
  switch (expr->precedence) {
  case FALSE:
    // Rien de particulier, on ajoute juste le symbole à notre expression
    expr_append(expr, symb);
    break;
  case TRUE: {
    /*
    Notez les accolades que je place sur ce case, sans elles il ne serait
    pas correct de déclarer des variables dans ce case (l'erreur existe
    aussi en C++ mais la raison est différente).
    */
    Symbole top;
    /*
    Il faut faire notre multiplication (ou division) en suivant la même
    logique que dans résolution.
    */
    float buffer = nb(symb);
    /*
    On récupère maintenant l'opérateur, qui doit exister sinon
    precedence serait faux.
    */
    expr_pop(expr, &top);
    char operateur = op(&top);
    /*
    Enfin on récupère le nombre qui précède l'opération pour faire le
    calcul. Attention, si on a écrite a / b alors b est dans buffer et a
    est dans top.
    */
    expr_pop(expr, &top);
    switch (operateur) {
    case '*':
      buffer = nb(&top) * buffer;
      break;
    case '/':
      buffer = nb(&top) / buffer;
      break;
    default:
      fprintf(stderr,
              "L'operateur %c a été trouvé dans l'expression à"
              " un endroit où seul * ou / étaient valides",
              operateur);
      status = -1;
      break;
    }
    new_symb_nb(symb, buffer);
    expr_append(expr, symb);
    break;
  }
  }
  return status;
}

int next_expr(Expression *expr, Symbole *symb) {
  /*
  Cette méthode gère l'ajout du prochain symbole sur l'expression courante, et
  si il faut résoudre l'expression courante elle renvoie le résultat dans symb.
  Pour faire tout cela on va s'appuyer sur next_symb.
  */

  int status;
  /*
  Note importante ici : je suis obligé d'utiliser symb pour ajouter le symbole à
  la pile. Le problème est que si je décidais de le faire sur top par exemple
  (qui a été déclaré dans cette fonction) alors à la fin de l'exécution de la
  fonction courante l'adresse mémoire du symbole sera invalidée, ce qui
  causerait plein de problèmes. Au lieu de cela en utilisant symb on mémorise le
  pointeur d'un objet qui survivra à cette fonction.
  */
  status = next_symb(symb, expr->next);
  switch (status) {
  case -1:
    // Un problème est survenu, on ne peut plus avancer, on va juste propager.
  case -3:
    // On a trouvé une parenthèse ouvrante, on se contente de propager.
    symb->type = INVALIDE;
    break;
  case -2:
    // Fin de l'expression, on résout et on renvoie le résultat
    status = resolve_expr(expr, symb);
    if (status == 0) {
      // Pour respecter ce qui a été écrit dans le header
      status = 1;
    }
    // else status vaut déjà -1 donc on a rien de plus à ajouter.
    break;
  case 0:
    /*
    On appelle la méthode dédiée afin d'ajouter correctement le symbole sur
    l'expression. Le statut d'erreur de partial_resolve_expr est cohérent avec
    celui de next_expr
    */
    status = partial_resolve_expr(expr, symb);
    break;
  }
  return status;
}
