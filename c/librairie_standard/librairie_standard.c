/*
Un programme en C dont l'objectif est de montrer différents aspects de
la librairie standard du C.

Les aspects abordés sont la manipulation de chaîne de caractère,
la lecture et l'écriture de fichiers ainsi que la création de process.

Contributeurs : Rezal P18
*/

/*
################################################################################
################## Première partie du programme : les inclusions ###############
################################################################################
*/

/*
Manipulation d'entrées sorties, contient notamment printf
*/
#include <stdio.h>

/*
Librairie permettant l'usage de chaînes de caractères en C à travers des
fonctions telles que sprintf. Contient également d'autres fonction utiles comme
memcpy.
*/
#include <string.h>

/*
Librairie standard à proprement parlé, contient notamment la fonction system
*/
#include <stdlib.h>

/*
Librairie utililisée à la fin du programme pour l'usage d'une fonction
variadique
*/
#include <stdarg.h>

/*
################################################################################
################## Deuxième partie du programme : les prototypes ###############
################################################################################
*/

// Ces fonctions seront expliquées au fil du programme.
int print_char(char lettre);
int print_per_line(char *texte);
size_t get_file_size(FILE *cible);
int systemf(const char *format, ...);
int tutoriel_wait(char *message);

/*
################################################################################
##################### Troisième partie du programme : le main ##################
################################################################################
*/

int main(int argc, char const *argv[]) {

  /*
                ---> Première partie : manipulation de texte en C <---
  */

  tutoriel_wait("Première partie : manipulation de texte en C");

  /*

                                Le texte en C - 2**

  Comme expliqué dans les tutoriels précédents il n'existe pas de type "chaîne
  de caractères en C" car ce type n'aurait pas une longueur fixe en mémoire. Au
  lieu de cela, un texte est représenté en C comme un tableau de char terminé
  par un bit nul. Notez que le type char occupe 1 octet en mémoire (c'est le
  plus petit type possible en C), par conséquent lorsque vous utilisez un
  encodage de texte non trivial, "votre définition humaine de ce qu'est un char
  peut ne pas correspondre à la réalité" (citation reprise de la documentation
  du Rust), i.e. un caractère de votre texte peut prendre plusieurs char en
  mémoire. Notez que cela n'est génant que dans de rares cas, mais gardez cela
  en mémoire au cas où.

  Pourquoi terminer le tableau de caractères par un bit nul ? Rappelez vous
  qu'en C, il n'est pas possible de retrouver la taille d'un tableau à partir de
  son pointeur. Par exemple si vous récupérez dans une méthode un int * créé à
  partir d'un tableau, il ne vous sera pas possible de déduire la taille du
  tableau d'origine à partir de l'adresse mémoire (i.e. pointeur) seule. Pour
  éviter cette limitation, le C va placer un bit nul à la fin du tableau de
  caractères. Ainsi au moment de lire le texte les méthodes de la librairie
  string auront juste à continuer à lire le bit sur l'adresse suivante en
  partant du pointeur jusqu'à arriver à un 0, qui marquera la fin de la chaîne.
  Toute l'information sur le texte est donc contenue dans le pointeur char *.

  Exemple : En C, le mot "rezal" serait stocké comme "rezal\0" dans son adresse
  mémoire. Pour afficher ce mot lettre par lettre (selon l'encodage
  ASCII/Unicode réduit) on peut utiliser la routine print_per_line dans ce
  fichier.

  */

  print_per_line("rezal");

  /*
  Notez que cette façon de stocker les chaînes de caractères n'est pas sans
  défauts (sinon on aurait fait la même chose pour tous les types de pointeurs).
  Elle a l'avantage d'être simple à implémenter et de bien se méler au style du
  C, qui passe toutes le valeurs par des pointeurs, sans être lourde à écrire.
  En revanche à chaque fois que vous avez besoin de faire une manipulation non
  triviale sur un texte il vous faut lire le texte d'un bout à l'autre. En toute
  honnêteté j'ignore pourquoi K&R ont décidé que cette limitation était
  acceptable pour le texte et pas pour les autres type de tableaux.

  Attention cependant, ce n'est qu'une convention. La plupart des méthodes
  s'attendront à ce que vous la respectiez, mais rien ne vous force à mettre un
  bit nul à la fin de vos tableaux de char (ce sont des tableaux comme les
  autres après tout). Par exemple si vous déclarez :
  */

  char exemple[5] = "rezal";

  /*
  le C commencera par transformer "rezal" en un tableau de 6 caractères
  contenant "r" "e" "z" "a" "l" "\0" (le C respecte sa propre convention lorsque
  l'on déclare du texte avec des guillemets). Ensuite le C va assigner les
  valeurs de ce tableau intermédiaire au tableau exemple (je ne me prononce pas
  sur comment), mais alors le tableau exemple contiendra (encodage ASCII) "r"
  "e" "z" "a" "l" et pas de \0 à la fin parce qu'il n'y a plus de place dans
  votre tableau pour y mettre un \0.
  */

  printf("exemple : %s\n", exemple);

  /*
  Ce printf ava probablement faire quelque chose de peu intuitif. Je ne vais pas
  expliquer pourquoi ici, pour comprendre vous pourrez voir le tutoriel sur les
  états indéfinis. Pour l'instant, contentons nous de voir ce qui se passe
  lorsque l'on place en bit de terminaisonen fin de tableau.
  */

  exemple[4] = 0; // bit de terminaison.
  printf("exemple : %s\n", exemple);

  print_per_line(exemple);

  /*
  Rien n'oblige le bit de terminaison (i.e. la fin du texte) à être à la fin du
  tableau. Il ne marque que la fin du texte dans le tableau, bien souvent le
  tableau complet sera plus grand que le texte que vous mettrez dedans.
  */

  exemple[2] = 0;
  printf("exemple : %s\n", exemple);

  print_per_line(exemple);

  /*
  Autre cas de figure similaire qui arrivera souvent : vous déclarez un buffer
  pour accueillir votre texte plus grand que la taille du texte que vous comptez
  accueillir (utilile notamment pour accueillir l'input de l'utilisateur).
  */

  char big_buffer[1024] = "rezal";
  printf("big buffer : %s\n", big_buffer);

  print_per_line(big_buffer);

  /*
  Notez qu'il vous est aussi possible de remplir un tableau de char "à la main",
  après tout un char n'est qu'un type qui tient sur un octet, donc si vous lui
  donnez une valeur entière dans -127 : 127 le C saura quoi en faire.

  Je montre ici cela juste pour expliquer comment le C fonctionne, en pratique
  je ne vous recommande pas du tout de faire cela (sauf si vous n'avez pas le
  choix).
  */

  char hand_written[6];
  hand_written[0] = 114; // "r"
  hand_written[1] = 101; // "e"
  hand_written[2] = 122; // "z"
  hand_written[3] = 97;  // "a"
  hand_written[4] = 108; // "l"
  hand_written[5] = 0;   // "\0"

  printf("hand_written : %s\n", hand_written);

  /*

                                sprintf - 1*

  Comme vous l'avez constaté, les manipulations de texte en C, bien que régies
  par des règles assez simples sur le papier, peuvent s'avérer délicates en
  pratiques. Pour cela, la librairie standard propose une fonction qui va gérer
  à elle seule 90% de vos manipulations de texte : sprintf

  sprintf est l'une de mes fonctions favorites en C. Son fonctionnement est très
  simple : elle va prendre en argument un texte de formattage (le même que pour
  printf, d'où le nom) et va écrire le résultat de ce formattage dans son
  premier argument. Sa signature est donc :

  int sprintf(char *str, const char*, ...);

  Tout comme printf, sprintf est une fonction variadique, d'où le "...".
  Un exemple d'utilisation :
  */
  sprintf(big_buffer, "2 + 2 = %d", 2 + 2);
  printf("%s\n", big_buffer);

  /*
  Un exemple de concaténation de textes avec sprintf (il n'y a pas beaucoup
  d'autres moyens de faire des concaténations de texte en C).
  */
  char *message1 = "Bonjour,\n";
  char *message2 = "Ceci est un tutoriel min";
  char *message3 = "'formatique ecrit par le Rezal P18";
  sprintf(big_buffer, "%s%s%s", message1, message2, message3);
  printf("%s\n", big_buffer);
  /*
  Notez que ni printf ni sprintf ne sont bâties pour la performance, si vous
  travaillez sur un système embarqué avec des ressources très limitées (assez
  rare) printf et sprintf ne seront pas forcément les meilleurs choix.

  Attention aussi pour sprintf, vous ne pouvez pas passer en entrée et en sortie
  le même tableau, il vous faut passer par des tableaux intermédiaires.
  */

  /*
              - --> Deuxième partie : entrées sorties <---
  */

  tutoriel_wait("Deuxième partie : entrées sorties");

  /*

                                  flux - 2**

  Le C est l'un des premiers languages à avoir (pour les besoins d'UNIX) fourni
  un système d'entrée sorties très homogène. Le premier aspect par lequel on
  remarque cela. L'idée a été reprise dans la plupart des languages (et
  operating systems) ultérieur donc l'idée ne vous surprendra pas.

  Un programme en C a accès à trois flux :
    - L'input sur lequel il reçoit des messages
    - L'output sur lequel il envoie des messages
    - L'error sur lequel il renvoie ses messages d'erreur

  Vous savez déjà comment écrire sur l'output en utilisant printf, mais la
  fonction printf n'est en fait qu'un proxy d'une autre fonction appellée
  fprintf
  ("file print format"). La signature de fprintf est :

  int fprintf(FILE *stream, const char *format, ...);

  Les deux derniers arguments ne vous surprennent sans doute plus, en revanche
  le premier mérite de s'y attarder. Il s'agit d'une structure (cf le tutoriel
  sur les structures avancées), c'est à dire un paquet d'informations mises
  ensembles, ici pour décrire un fichier. Ce FILE sera utilisé par le programme
  par exemple pour savoir quel est le fichier ciblé par la routine ou pour
  synchroniser les écritures sur le fichier cible.

  Les FILE les plus simples sont stdin, stdout et stderr (respectivement input,
  output et error). Ces FILE permettent de retrouver et d'utiliser le flux
  auxquel ils sont associés. Ces trois FILE sont définis dans le fichier header
  stdio.h

  Par exemple, pour écrire sur l'output :
  */
  fprintf(stdout, "%s\n", "Un message écrit sur l'output");

  // Idem pour l'error
  fprintf(stderr, "%s\n", "Un message d'erreur");

  /*
  Vous ne pouvez pas écrire sur l'input, seulement lire. Pour cela, la librairie
  standard propose la fonction fscanf. La signature de fscanf est (oh surprise)
  :

  int fscanf(FILE *stream, const char *format, ...);

  La logique est la même que pour fprintf au détail près que fscanf écrit ses
  résultats dans les arguments variadiques, ce qui est TRES pratique mais un peu
  difficile à comprendre en lisant.

  Attention cependant, puisque le C est pass by value uniquement, les arguments
  variadiques que vous devez passer dans fscanf doivent être des pointeurs,
  faute de quoi leurs valeurs ne pourraient pas être modifiés depuis l'interieur
  de fscanf (voire le tutoriel sur les pointeurs).

  Des exemples :
  */
  printf("%s\n---> ", "Ecrivez un court message puis appuyez sur ENTER");
  fscanf(stdin, "%s", big_buffer);
  printf("Vous avez écrit %s\n", big_buffer);

  printf("%s\n--->",
         "Plus difficile, écrivez \"<un nombre> + <un autre nombre>\"");
  int first_int;
  int second_int;
  fscanf(stdin, "%d + %d", &first_int, &second_int);
  printf("Resultat : %d + %d = %d\n", first_int, second_int,
         first_int + second_int);

  /*
  De la même façon que printf est une syntaxe raccourcie de fprinf pour stdout,
  il existe une syntaxe raccourcie de fscanf pour stdin simplement appellée
  scanf.

  Un point important à noter : comme vous l'aurez remarqué, les lectures sur
  stdin dans un programme sont bloquantes, c'est à dire que l'execution du
  programme n'avancera pas tant que scanf n'aura pas réussi à lire l'input. Cela
  est utile pour mettre des pauses dans vos tutoriels min'formatique mais peut
  avoir des conséquences imprévues si vous l'oubliez (vous risquez notamment de
  crééer des deadlocks dans votre programme).

  Une conséquence assez bienvenue de cela est qu'il est en pratique très facile
  de se servir de l'input dans un programme. Vous n'avez qu'à mettre vos scanf
  là où vous en sentez le besoin, et tout se passera comme si l'input était déjà
  là, ou si vous préferrez comme si quelqu'un tapait l'input dans le terminal
  (et ce quelque soit l'origine de l'input).

                                Buffering - 2**

  Autre subtilité à connaitre : l'output est buffered par défaut lorsque vous
  écrivez sur un fichier et line buffered lorsque vous ecrivez sur le terminal.
  C'est à dire que lorsque vous écrivez votre output sur un fichier, même si
  vous faites des printf tout au long de votre programme en pratique l'OS
  n'écrira réellement sur le fichier qu'au moment où votre programme finira son
  execution. Pour le terminal, la convention est que le programme n'écrira que
  si vous finissez une ligne mais ce n'est qu'une convention et certaines
  implementation peuvent n'avoir pas de buffering du tout. L'error est
  unbuffered par défaut.
  */

  message1 = "Le programme va rester bloquer ici tant";
  message2 = "que vous ne taperez pas de message !";

  printf("%s %s\n--->", message1, message2);
  scanf("%s", big_buffer);
  printf("Votre message : %s\n", big_buffer);

  /*
  Si jamais vous avez besoin, pour une raison quelconque, que votre programme
  écrive maintenant ce qui se trouve dans son buffer vers sa cible, vous pouvez
  utiliser fflush, qui forcera l'écriture de ce qui se trouve dans le buffer en
  argument.
  */

  fflush(stdout);

  /*
  Bien qu'ils soients très utiles, les flux d'input, output et error ne sont pas
  les seuls dont on peut avoir besoin dans un programme. Toujours avec fprintf
  et fscanf, il est possible d'écrire et lire le contenu d'un fichier. Pour cela
  on a besoin de deux choses : avant l'opération il faut obtenir un FILE pour le
  fichier cible (i.e. ouvrir le fichier) et à la fin du programme il faut
  libérer cette ressource (i.e. fermer le fichier).

  Pour ouvrir un fichier, on utilise fopen, qui renvoie un FILE pour un fichier
  cible avec le mode donné (lecture ou écriture la plupart du temps).
  */

  FILE *source = fopen("librairie_standard.c", "r");
  FILE *copy_source = fopen("first_lines.txt", "w");

  // Lecture du fichier source, seulement les commentaires d'en tête au début.
  char first_line[100];
  char second_line[100];
  fscanf(source, "%s\n%s\n", first_line, second_line);
  printf("%s\n%s\n", first_line, second_line);
  /*
  Aïe, ce n'est pas du tout ce que l'on veut, fscanf n'est pas pratique du tout
  pour lire des fichiers.
  */
  fprintf(copy_source, "%s\n%s\n", first_line, second_line);

  /*
  On ferme les fichiers, ce qui va déclencher l'écriture du buffer.
  La routine à utiliser est fclose, qui agit sur les pointeurs des FILE.
  */

  fclose(source);
  fclose(copy_source);

  /*
  Comme vous pouvez le constater, fscanf n'est pas pratique du tout pour lire
  tout un fichier, parce qu'il butte sur tous les espaces et toutes les fins de
  lignes. Pour lire et écrire sur des fichiers, le mieux est d'utiliser les
  routines de bas-niveau sur lesquelles sont bâties fscanf et sprintf.

  Mais avant cela, nous avons besoin de trouver une information importante sur
  le fichier que nous comptons lire : sa taille (en octets).

  Pour cela, la méthode classique est :
   1 - Ouvrir le fichier;
   2 - Aller à la fin du fichier;
   3 - Lire la position du curseur;
   4 - Retourner au début du fichier pour faire nos manipulations
  */

  // On ouvre les fichiers
  source = fopen("librairie_standard.c", "r");
  copy_source = fopen("copy_source.txt", "w");

  /*
  On trouve la fin du fichier. Pour plus de détails sur cette routine lisez la
  documentation :-)
  */
  fseek(source, 0L, SEEK_END);

  // On lit la position actuelle du curseur qui nous sert à parcourir le fichier
  size_t file_size = ftell(source);

  // On replace le curseur au début du fichier afin de pouvoir travailler dessus
  rewind(source);

  /*
  Notez que toutes ces fonctions sont décrites sur la même page de
  documentation. Ce n'est pas un hasard, elles sont souvent utilisées ensemble.
  */

  printf("Taille du fichier : %ld\n", file_size);

  /*
  Comme toujours, vous pouvez aussi définir une routine pour n'avoir pas à vous
  souvenir de ce code à chaque fois.
  */

  printf("Taille du fichier (routine) : %ld\n", get_file_size(source));
  /*
  Une fois que cela est fait nous n'avons plus aucun travail à faire. Le C met à
  notre disposition deux fonction de bas niveau pour lire et écrire facilement
  des fichiers octets par octets : fread et fwrite.

  Pour transférer le contenu du premier fichier dans le second il nous faut tout
  de même créer une variable intermédiaire qui serve de buffer. Pour notre
  tutoriel on se contetentera d'une implémentation naïve, les améliorations
  possibles sont laissées à titre d'exercice.
  */

  char file_buffer[file_size];

  /*
  La syntaxe signifie : on lit depuis le fichier "source" vers le buffer
  "file_buffer" "file_size successive" items, tous de taille "sizeof(char)" (qui
  vaut 1 par ailleurs).
  */
  printf("%s\n", "Copie de la source");
  fread(file_buffer, sizeof(char), file_size, source);

  /*
  On écrit "file_size" items se taille "sizeof(char)" trouvé dans "file_buffer"
  sur le fichier copy_source.
  */
  fwrite(file_buffer, sizeof(char), file_size, stdout);
  fwrite(file_buffer, sizeof(char), file_size, copy_source);
  printf("%s\n", "Fin de copie de la source");

  // On referme tous les fichiers.
  fclose(source);
  fclose(copy_source);

  /*
  Notez que fwrite et fread ne sont pas les seules fonctions permettant de
  telles manipulations. On peut notamment citer fgetc ("file get char") et fgets
  ("file get string") ainsi que la variante sur stdin de fgetc appellée getchar,
  très utile car contrairement à scanf elle permet de détecter lorsque quelqu'un
  appuie sur ENTER sans taper de texte sur stdin.

  Notez que mélanger l'usage de scanf et de fgets ou getchar amène à des bugs
  étranges, pour cette raison on ne recommande généralement pas d'utiliser scanf
  directement, on préférera lire d'abord l'input avec fgets puis scanner ce qui
  a été lu avec sscanf. Ici pour éviter ces bugs je place un getchar préalable
  pour consommer le caractère "\n" laissé derrière par scanf.
  */
  getchar();
  message1 = "Tapez à nouveau <nombre> + <nombre>\n---> ";
  printf("%s\n%s", "Exemple de lecture de ligne avec fgets", message1);
  fgets(big_buffer, 1024, stdin);
  printf("%s", big_buffer);
  sscanf(big_buffer, "%d + %d", &first_int, &second_int);
  printf("%d + %d = %d\n", first_int, second_int, first_int + second_int);
  printf("%s\n", "Une petite pose avant de parler de file descriptor...");
  getchar();

  /*

                              file descriptor - 2**

  La plupart des fonctions citées ci dessus ont également une variante utilisant
  un fd ("file descriptor"). Ces fd sont un entier positif permettant au noyau
  de retrouver un fichier (par exemple 0 pour stdin, 1 pour stdout et 2 pour
  stderr). L'utilisation de ces fonctions est la même que pour celles utilisant
  un FILE mais ATTENTION : contrairement à ce qui est malheuresement suggéré
  dans la documentation, ces fonctions ne sont équivalentes que vous n'utilisez
  que l'une ou l'autre des méthodes (i.e. il ne faut pas mélanger l'utilisation
  de FILE et de fd), sinon vous ferez face à des problèmes de synchronisation
  très rapidement.

  Dans la mesure où printf et scanf utilisent en interne des FILE, je vous
  recommande de toujours en faire de même et de ne pas utiliser les fd à moins
  d'être certains de ce que vous faites.
  */

  /*
  En plus de cela, il peut souvent en C être utile de faire des opérations sur
  des tableaux d'octets en mémoire. Pour cela les fonctions les plus utiles sont
  memcpy,
  ("memory copy"), memset ("memory set") et memcmp ("memory compare"). Elles
  fonctionnent toutes sur le même principe donc je ne détaillerai que les deux
  premières (qui sont plus utiles).

  memcpy permet de copier n octets trouvés sur un pointeur source vers un
  pointeur de destination. Par exemple on peut copier les 10 premiers chars de
  message1 dans big_buffer octets par octets :
  */
  message1 = "Un nouveau message";
  memcpy(big_buffer, message1, 10 * sizeof(char));
  // On ajoute un bit de terminaison
  big_buffer[10] = 0;
  printf("message1 : %s - big_buffer : %s\n", message1, big_buffer);

  /*
  memset permet de remplir les n premiers bits d'un tableau avec une valeur
  constante (souvent 0). Notez que d'une façon contre intuitive, la valeur
  constante à donner à memset est un int et pas un char. Cela vient de raisons
  surtout historiques. De la même façon, lorsque vous écrivez 'a' le type de 'a'
  est int et pas char, encore une fois pour des raisons historiques. Notez que
  cela n'a pas d'influence sur le code que vous écrivez et que vous pouvez
  ignorer complètement cet aspect.
  */
  memset(big_buffer, 'a', 10 * sizeof(char));
  big_buffer[10] = 0;
  printf("big_buffer apres memset : %s\n", big_buffer);

  /*
              ---> Troisième partie : Les sous process <---
  */

  tutoriel_wait("Troisième partie : Les sous process");

  /*

                              Sous process - 2**

  Un process est une tâche définie au niveau de l'OS, c'est à dire une série de
  calculs ou d'opérations pour lesquelles l'OS va accorder des ressources.
  En pratique à peu près toutes les applications que vous utilisez ont leur
  propre process.

  En C plus que dans d'autres languages il est très utile de demander à l'OS de
  lancer de lancer des process (i.e. de faire des choses pour vous), parce que
  beaucoup de manipulations utiles seraient particulièrement laborieuses à
  écrire. Par exemple, si python se trouve dans votre PATH vous pouvez vous en
  servir exactement de la même façon que vous feriez en ligne de commande.

  Il y abeaucoup de routines très bas niveau pour gérer cela, mais la plus
  simple à manipuler (et souvent celle dont vous avez besoin) est system. Sa
  signature est :

  int system(const char *command);

  En argument on donne la ligne de commande que l'on souhaite utiliser et après
  l'exécution system renvoie le code d'erreur de notre commande.
  */

  // La commande que l'on souhaite utiliser.
  char *command = "python3 script_python.py";
  int exit_status = system(command);

  printf("La commande %s s'est achevée avec le code %d\n", command,
         exit_status);

  /* 3***
  Notez que vous avez en C une grande flexibilté sur l'usage de sub process.
  Je citerai notamment pour ceux intéressés les fonctions fork, execl et popen.
  */

  /*
  Je finirai ce petit tutoriel sur un pattern de code que l'on retrouve beaucoup
  dans les petits programmes en C que j'écris parce qu'il combine simplicité et
  efficacité. Un cas de figure dans lequel vous tomberez souvent est que vous
  aurez besoin d'utiliser un "system call" mais avec des arguments qui vont
  changer suivant le contexte. Par exemple si vous essayez de télécharger un
  fichier sous linux, vous pouvez d'abord chercher à voir quel outil est
  disponible en regardant si curl ou wget est disponible. Suivant le resultat de
  ce test vous aurez à lancer soit curl soit wget, donc vous aurez une commande
  différente à utiliser. Vous pouvez aussi vouloir utiliser ces outils pour
  télécharger avec ou sans redirection, avec ou sans proxy etc... Pour pouvoir
  faire cela, l'idée est d'utiliser sprintf pour modifier l'argument que vous
  passerez dans system.

  Notez que ce n'est pas du tout la seule façon de réaliser cela, mais je trouve
  cette approche facile à prendre en main.
  */

  char *executable = "python3";
  char *argument = "-c";
  char *script = "\"print('Ce tutoriel est fini !')\"";
  systemf("%s %s %s", executable, argument, script);
  return 0;
}

/*
################################################################################
############# Dernière partie du programme : les fonctions annexes #############
################################################################################
*/

int print_char(char lettre) {
  // On crée un buffer pour accueillir notre texte
  char mot[2];
  // On place la lettre souhaitée dans le buffer
  mot[0] = lettre;
  // On ajoute le bit de terminaison
  mot[1] = 0;
  // On affiche le texte
  printf("%s - %d\n", mot, lettre);
  return 0;
}

int print_per_line(char *texte) {
  char letter;
  // L'index courant dans le tableau de caractères du texte.
  size_t compteur = 0;
  do {
    letter = texte[compteur];
    print_char(letter);
    compteur++;
  } while (letter != 0);
  return 0;
}

size_t get_file_size(FILE *cible) {
  // Une routine renvoyant la taille d'un fichier passé en argument.

  /*
  On trouve la fin du fichier. Pour plus de détails sur cette routine lisez la
  documentation :-)
  */
  fseek(cible, 0L, SEEK_END);

  // On lit la position actuelle du curseur qui nous sert à parcourir le fichier
  size_t file_size = ftell(cible);

  // On replace le curseur au début du fichier afin de pouvoir travailler dessus
  rewind(cible);

  return file_size;
}

int systemf(const char *format, ...) {
  /*

                          Fonction variadique - 3***

  Cette fonction est une fonction variadique utilisant le même type de format
  que sprintf. Bien que tout le travail soit fait en interne par vsprintf,
  comprendre cette fonction nécessite de comprendre un minimum les fonctions
  variadiques en C.

  Les fonctions variadiques en C sont clairement une fonctionnalité avancée dont
  vous pouvez vous passer dans la plupart de vos programmes. Leur fonctionnement
  interne pousse la syntaxe du C dans ses derniers retranchements, toutefois il
  ne faut pas se laisser impressionner, la syntaxe pour utiliser ces fonctions
  variadiques est abordable.

  Notez toutefois que (encore plus que pour les autres fonctions) l'ordre des
  arguments d'une fonction variadique est très important.
  */

  /*
  On commence par créer une structure (définie dans stdarg) sur laquelle vont
  s'appuyer les différentes routines pour retrouver les différents arguments.
  */
  va_list args;

  /*
  On initialise cette "variadic list" en utilisant la fonction va_start et en
  passant en argument le premier argument non variadique de la fonction
  courante. Ici cet argument est format.

  La raison pour laquelle passer cet argument à va_start lui suffit à retrouver
  les arguments variadiques qui sont passés après est clairement non triviale
  et dans la mesure où je ne me suis pas trop penché sur la question j'aurai du
  mal à vous expliquer avec conviction comment cela fonctionne, mais en gros
  les différents arguments d'une fonction sont passés les uns derrière les
  autres en mémoire, donc le premier argument variadique passé après format se
  trouve à l'adresse format + sizeof(format).
  */
  va_start(args, format);

  /*
  L'implémentation de systemf est en réalité assez simple puisque nous pouvons
  utiliser la fonction vsprintf pour faire le travail à notre place.
  */
  char buffer[1024];

  vsprintf(buffer, format, args);

  /*
  Si nous avion eu besoin d'utiliser les arguments variadiques manuellement, la
  routine dédiée est va_arg.
  */

  // Releasing the variadic list.
  va_end(args);

  return system(buffer);
}

int tutoriel_wait(char *message) {
  // Utilisé pour faire des poses entre les parties
  printf("\n%s\n%s", message, "(Appuyez sur ENTER pour continuer)");
  getchar();
  printf("%s\n", "");
  return 0;
}

/*

                                Le mot de la fin

Dans ce tutoriel je n'ai pu montrer qu'une partie de la librairie du C, j'espère
avoir choisi des fonctions qui vous seront assez utiles. Cependant je me permet
de souligner un point qui me semble important concernant ces librairies.

Vous l'aurez surement remarqué, ces librairies sont très homogènes et cohérentes
entre elles. Cela n'est pas arrivé par hasard, depuis sa création le C est géré
par un groupe qui publie toutes les quelques années une version de référence du
C que les compilateurs doivent suivre. Les versions les plus notables sont le
C89 (ANSI C) qui est la première version vraiment homogène du C, puis C99 qui a
considérablement modernisé le language. Depuis quelques versions notables ont
été publiées (C11 surtout) mais le standard est assez stable et consistant.

Cependant ces standards datent d'avant l'arrivée d'internet, et bien que l'on y
trouve de la documentation sachez que les forums sur internet ne sont pas
forcément la meilleure source de documentation du C notamment parce que les
membres ont souvent tendance à proposer des solutions alambiquées aux questions
posées par manque de connaissance de la (certes vaste et assez méconnue)
librairie standard du C.

Par conséquent, contrairement aux languages plus modernes, je vous enjoins
fortement à ne pas vous trop vous appuyer sur les ressources en lignes pour
faire du C. Les forums sont une source d'information utile mais clairement pas
infaillible. De plus le C est l'un des languages avec la meilleure documentation
hors ligne qui soit. Si vous utilisez linux, cette documentation est accessible
à travers les man pages. Si vous tapez dans votre terminal "man sprintf" vous
aurez accès à une documentation souvent assez claire de la fonction sprintf
ainsi que d'autres fonctions associées. Par exemple fwrite et fread ont été mis
sur la même page de documentation pour que les gens qui cherchent à lire un
fichier trouvent par la même occasion comment écrire un fichier. En bas de page
vous trouverez aussi des fonctions qui pourraient vous intéresser.

Petit détail concernant les man pages : si jamais la fonction que vous cherchez
a le même nom qu'un outil de ligne de commande (printf par exemple) la page de
documentation C sera souvent la troisième, donc "man 3 printf"

N'oubliez pas que le C est un language de bas niveau et que par conséquent il
n'a pas vocation à fournir des "one-liners" pour tout ce que vous pourriez
souhaiter faire (contrairement à python ou java par exemple). Si ce que vous
souhaitez faire peut être atteint en manipulant des octets, alors la librairie
standard du C vous suffira certainement pour le faire, fût-ce long à coder.
L'important est de bien comprendre ce que font les fonctions que vous appelez et
de ne pas hésiter à définir des routines pour raccourcir votre code et éviter
les erreurs.
*/
