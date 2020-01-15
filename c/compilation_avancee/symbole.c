/*
Ce fichier fait partie du tutoriel compilation avancée et est utilisé afin
d'implémenter une calculatrice assez simple. Il contient le code source de
toutes les routines liées au type Symbole déclarées dans calculatrice.h
*/

/*
################################################################################
################## Première partie du programme : les inclusions ###############
################################################################################
*/

#include "calculatrice.h"

/*
################################################################################
################## Deuxième partie du programme : les prototypes ###############
################################################################################
*/

/*
Ils sont déjà déclarés dans calculatrice.h :


extern int new_symb_nb(Symbole *symb, float nombre);
extern int new_symb_op(Symbole *symb, char operateur);
extern float nb(Symbole *symb);
extern char op(Symbole *symb);
extern int next_symb(Symbole *symb, enum TypeSymbole type);
*/

/*  3***
Afin d'alléger l'écriture de certaines routines de ce fichier on définit aussi
des fonctions statiques.

La première fois que j'ai écrit ces fonctions j'ai fait un écart sur la syntaxe
habituelle en déclarant par exemple :

float next_nb();

Mais à la fin cela compliquais beaucoup la syntaxe des fonctions qui les
utilisaient car j'avais du mal à gérer les codes d'erreur. Pour cette raison
j'en reviens à la syntaxe habituelle en renvoyant de la fonction un code
d'erreur (cohérent avec next_symb).

Lis le prochain opérateur sur l'input, renvoie :
  - 0 en cas de succès,
  - -2 si on atteint la fin du fichier (EOF),
  - -1 si on trouve autre chose
*/
static int next_op(char *operateur);

/*
Même chose mais en plus compliqué puisque l'on doit lire un flottant sur
l'input, renvoie :
  - 0 en cas de succès,
  - -3 si on trouve une parenthèse ouvrante,
  - -2 si on atteint EOF,
  - -1 si on trouve autre chose
*/
static int next_nb(float *nombre);

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

// On initialise un symbole avec un nombre, la fonction est assez simple.
int new_symb_nb(Symbole *symb, float nombre) {
  symb->type = NOMBRE;
  (symb->valeur).nombre = nombre;
  return 0;
}

// On initialise un symbole avec un char, là aussi l'écriture est plutôt simple
int new_symb_op(Symbole *symb, char operateur) {
  symb->type = OPERATEUR;
  (symb->valeur).operateur = operateur;
  return 0;
}

float nb(Symbole *symb) {
  /*
  Avant de renvoyer la valeur il faut s'assurer que l'on n'est pas en train de
  récupérer la valeur flottant d'un symbole qui est en fait un opérateur.
  */
  float return_value;
  switch (symb->type) {
  case NOMBRE:
    return_value = (symb->valeur).nombre;
    break;
  default:
    /*
    La signature de cette fonction ne nous permet pas de renvoyer un code
    d'erreur, mais on sait que les valeurs qui seront lues seront forcément
    des flottants positifs donc on peut se servir de -1 comme code d'erreur.
    */
    return_value = -1;
    break;
  }
  /*
  Remarque : pour ceux qui ont déjà fait du Rust ce pattern devrait à raison
  vous rappeler le match.
  */
  return return_value;
}

char op(Symbole *symb) {
  /*
  Même chose, avant de renvoyer on doit vérifier que l'on n'est pas en train de
  commetre ue erreur.
  */
  char return_value;
  switch (symb->type) {
  case OPERATEUR:
    return_value = (symb->valeur).operateur;
    break;
  default:
    /*
    Les quatres operateurs valables sont +, -, * et / et leurs valeurs
    entières sont toutes différentes de -1 (respectivement 43, 45, 42 et 47).

    On aurait d'ailleur pu faire un enum pour représenter ces valeurs mais
    j'ai déjà pas mal de code à écrire comme ça.
    */
    return_value = -1;
    break;
  }
  return return_value;
}

/*
La suite du fichier est 4****
*/

int next_symb(Symbole *symb, enum TypeSymbole type) {
  /*
  Première chose : est-ce que l'on cherche un operateur ou un nombre ?
  */
  int status;
  char next_op_found;
  float next_nb_found;
  switch (type) {
  case OPERATEUR:
    // On utilise les routines dédiées.
    status = next_op(&next_op_found);
    switch (status) {
    case -1:
    /*
    On fait la même chose que dans le cas suivant donc on se contente de
    tomber dedans.
    */
    case -2:
      // On n'oublie pas d'invalider le symbole pour éviter les problèmes
      symb->type = INVALIDE;
      break;
    default:
      /*
      i.e. on a bien trouvé un opérateur. Notez que status devrait déjà
      valoir 0, mais au cas où on le remet à 0.
      */
      status = 0;
      /*
      On initialise le symbole. Cette méthode renvoie toujours 0 donc pas
      de vérification.
      */
      new_symb_op(symb, next_op_found);
      break;
    }
    break;
  case NOMBRE:
    // idem, on utilise les routines dédiées.
    status = next_nb(&next_nb_found);
    switch (status) {
    case -1:
    case -2:
    case -3:
      symb->type = INVALIDE;
      break;
    default:
      status = 0;
      new_symb_nb(symb, next_nb_found);
      break;
    }
    break;
  default:
    fprintf(stderr, "%s\n",
            "Le type d'operateur que vous cherchez n'a pas de"
            " sens");
    status = -1;
    break;
  }
  return status;
}

int next_op(char *operateur) {
  /*
  On cherche le prochain opérateur sur l'input. On remarque que seul certains
  caractères sont possibles dans une expression correcte :
   - un operateur,
   - un espace,
   - une parenthès fermante qui marque la fin d'une expression,
   - une fin d'input qu'il faut surveiller
  Dans tout autre cas on renverra -1
  */
  int return_value = 0;
  char next_char;
  int continuer_boucle = 1;
  do {
    next_char = getchar();
    switch (next_char) {
    case '\n':
    case ' ':
      // Si on trouve un espace on l'ignore
      break;
    case ')':
    case EOF:
      /*
      Normalement EOF = -1, mais pour plus de lisibilté je laisse EOF ("end
      of file").

      Dans tous les cas, si on trouve une fin de fichier ce n'est plus la
      peine de lire sur l'input, on peut juste sortir de la boucle et
      renvoyer -2
      */
      continuer_boucle = 0;
      return_value = -2;
      break;
    case '+':
    case '-':
    case '*':
    case '/':
      // i.e. si on a trouvé un opérateur que l'on cherchait
      continuer_boucle = 0;
      break;
    default:
      // i.e. si on a trouvé autre chose
      fprintf(stderr,
              "Le caractère invalide %c a été trouvé à la place d'un"
              " operateur\n",
              next_char);
      continuer_boucle = 0;
      return_value = -1;
      break;
    }
  } while (continuer_boucle);
  /*
  On assigne la valeur que l'on trouvée de next_char, qui est la bonne en cas de
  succès et une valeur indéfinie sinon. Pour tout de même avoir une méthode qui
  évite les états indéfinis on renvoie notre code d'erreur à la fin de la
  fonction.
  */
  *operateur = next_char;
  return return_value;
}

int next_nb(float *nombre) {
  /*
  On lit le prochain nombre sur l'input en faisant attention au fait qu'au lieu
  d'un nombre on peut trouver une parenthèse (c'est pour cela que je n'utilise
  pas un scanf directement).

  Pour implémenter cette fonction on va utiliser la même logique que pour la
  fonction next_op, car içi aussi il n'y a qu'un nombre fini de valeurs valables
  que l'on peut trouver sur l'input :
   - un espace,
   - EOF,
   - un chiffre 0 - 9,
   - un . de séparation entre unités et décimales.
  */
  int return_value = 0;
  char next_char;

  /*
  Attention : Si la représentation en mémoire d'un float est d'une taille bien
  connue (4 octets), sa représentation textuelle n'a pas forcément une taille
  prévisible. Par exemple 0.1 prend 3 octets à représenter alors que 124.336 en
  prend 6. Pour implémenter notre fonction ce que l'on va faire est que tant que
  sur l'input on trouve des chiffres ou au plus un point on va les placer dans
  un buffer. A partir du moment où l'on retrouve autre chose sur l'input, on
  renvoie la dernière chose que l'on a trouvée dans l'input (cette opération
  n'est garantie de fonctionner que pour renvoyer un seul élément donc cela nous
  suffit ici). Après cela on utilisera sscanf pour retrouver la valeur du nombre
  correspondant à la représentation trouvée.

  Le nombre maximal de chiffres représentatifs dans un nombre flottant est donné
  par FLT_DIG ("float digit") et c'est ce que l'on utilisera comme taille pour
  notre buffer (le +2 est pour notre bit de terminaison et pour le point de
  séparation entre unités et décimales).

  Attention, FLT_DIG vaut 6, ce n'est pas beaucoup !
  */
  char float_char_buffer[FLT_DIG + 2];
  // L'index du prochain nombre à écrire dans le buffer.
  size_t float_char_buffer_index = 0;

  /*
  Un booléen qui nous dit si on a déjà trouvé un point dans notre input, plus
  serait une erreur.
  */
  int found_point = 0;

  /*
  Un autre booléen qui nous dit si on a déjà commencé à lire notre float, auquel
  cas un espace ne devrait plus être ignoré par exemple.
  */
  int float_commence = 0;
  int continuer_boucle = 1;

  do {
    next_char = getchar();
    switch (next_char) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      // On va remettre cette valeur à 1 plusieurs fois mais peu importe
      float_commence = 1;
      if (float_char_buffer_index < FLT_DIG + 1) {
        // i.e. si on n'a pas déjà rempli notre buffer
        float_char_buffer[float_char_buffer_index] = next_char;
        float_char_buffer_index += 1;
      } else {
        // On a un problème de représentation que l'on ne peut pas résoudre
        fprintf(
            stderr, "Le nombre %s %s\n", float_char_buffer,
            "à l'intérieur"
            " du calcul ne peut pas être représenté correctement en machine");
        return_value = -1;
        continuer_boucle = 0;
      }
      break;
    case '.':
      /*
      On a trouvé un point de séparation des unités et des décimales. Si c'est
      le premier que l'on trouve on le traite normalement, sinon il y a un
      problème.
      */
      if (found_point) {
        fprintf(stderr, "Le nombre %s %s\n", float_char_buffer,
                "à l'interieur"
                " du calcul comporte plusieurs points");
        return_value = -1;
      } else {
        found_point = 1;
        if (float_char_buffer_index < FLT_DIG + 1) {
          // i.e. si on n'a pas déjà rempli notre buffer
          float_char_buffer[float_char_buffer_index] = next_char;
          float_char_buffer_index += 1;
        } else {
          // On a un problème de représentation que l'on ne peut pas résoudre
          fprintf(
              stderr, "Le nombre %s %s\n", float_char_buffer,
              "à l'intérieur"
              " du calcul ne peut pas être représenté correctement en machine");
          return_value = -1;
          continuer_boucle = 0;
        }
      }
      break;
    case '\n':
    case ' ':
      /*
      Si on rencontre un espace, deux cas se présentent : soit on a déjà
      commencé à lire un nombre sur l'input auquel cas il faut le terminer et
      renvoyer l'espace, sinon il on ignore l'espace.
      */
      switch (float_commence) {
      case 0:
        // On ignore l'espace s'il se trouve avant le nombre.
        break;
      case 1:
        /*
        Sinon, on termine notre nombre et on renvoie l'espace. La fonction
        que l'on utilise pour renvoyer l'espace est clairement inhabituelle
        et cela me fait un peu mal au coeur de m'en servir mais dans le cas
        présent elle me simplifie beaucoup la vie.
        */
        ungetc(next_char, stdin);
        // Maintenant on finit la représentation du flottant.
        continuer_boucle = 0;
        // Bit de terminaison
        float_char_buffer[float_char_buffer_index] = 0;
        break;
      }
      break;
    case '(':
      /*
      Si on trouve cette parenthèse avant d'avoir commencé à écrire le nombre
      alors on renvoie -3, sinon (il y a probablement un problème) on replace
      juste le caractère dans stdin.
      */
      switch (float_commence) {
      case 0:
        continuer_boucle = 0;
        return_value = -3;
        break;
      case 1:
        ungetc(next_char, stdin);
        continuer_boucle = 0;
        float_char_buffer[float_char_buffer_index] = 0;
        break;
      }
      break;
    case EOF:
      /*
      Si jamais on atteint la fin du fichier, on a deux cas de figure. La
      raison de cela est que si j'écris quelque chose comme "1 + 2" et que
      l'on essaie de lire on atteindra la fin du fichier après le 2, et ce
      n'est pas une erreur. Donc : si on a déjà commencé le nombre on le
      finit, sinon on renvoie une fin de fichier.
      */
      switch (float_commence) {
      case 0:
        continuer_boucle = 0;
        return_value = -2;
        break;
      case 1:
        continuer_boucle = 0;
        float_char_buffer[float_char_buffer_index] = 0;
        break;
      }
      break;
    default:
      /*
      Si on trouve n'importe quoi d'autre avant d'avoir commencé le nombre
      c'est un problème, sinon il s'agit probablement d'un opérateur dont on
      se chargera au prochain next.
      */
      switch (float_commence) {
      case 0:
        fprintf(stderr, "Un caractère invalide %c %s\n", next_char,
                "a été"
                " trouvé à la place d'un nombre");
        continuer_boucle = 0;
        return_value = -1;
        break;
      case 1:
        // On termine juste le nombre, toujours en faisant notre ungetc
        ungetc(next_char, stdin);
        continuer_boucle = 0;
        float_char_buffer[float_char_buffer_index] = 0;
        break;
      }
      break;
    }
  } while (continuer_boucle);

  /*
  Arrivé ici, si return_value vaut autre chose que 0 c'est qu'il y a eu un
  problème et donc que le contenu de float_char_buffer ne peut pas être parsé
  correctement, sinon lance sscanf.
  */
  if (return_value == 0) {
    // Note : nombre est déjà un pointeur.
    int sscanf_status = sscanf(float_char_buffer, "%f", nombre);
    /*
    Il nous faut vérifier que sscanf a bien réussi à faire son travail, pour
    cela on utilise le code d'erreur de sscanf (expliqué dans la documentation)
    */
    if (sscanf_status != 1) {
      char *format = "La valeur %s n'a pas pu être convertie en nombre\n";
      fprintf(stderr, format, float_char_buffer);
      return_value = -1;
    }
  }

  // Fiou... C'était un peu long, je ne vais pas vous mentir :-)
  return return_value;
}
