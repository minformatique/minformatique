# Langage

La spécification du langage est séparée en trois parties :
 - Fonctionnement général
 - Instructions
 - Limitations
 - Extensions possibles

# Fonctionnement général

Le langage est un assembleur de haut niveau exécuté ligne à lignes. Un script est constitué de lignes commençant toujours par une instruction suivie des arguments de l'instruction. Chaque instruction fait exactement 3 carctères ASCII et la liste complète des instruction demandées se trouve dans la partie instruction.

Pour chaque ligne du script, l'interpréteur doit d'abord exécuter ce qui se trouve sur la ligne puis passer à la suivante (comprendre le terme "suivante" au sens large, cf l'instruction JPZ).

Toutes les manipulation du langage sont des manipulations d'entiers au sens du C, c'est à dire le type int (32 bits signé sur une plateforme standard).

Le langage ne comporte pas de variables locales. Comme en assembleur, toutes les manipulations doivent être effectuées à travers de registres. Ces registres sont au nombre de 4 et sont nommés A, B, C et D. Si le concept de registre ne vous est pas familier, vous pouvez voir un registre comme une variable globale qui a déjà été déclarée. Par suite tout au long de l'exécution d'un script, les registres A, B, C et D sont toujours accessibles, mais il n'est pas possible d'en créer de nouveaux ni de les supprimer.

Attention : Sauf contre indication, il n'est pas possible de faire d'hypothèses sur la valeur des registres au début d'un programme, et rien n'impose à l'interpréteur de les initialiser.

Le langage ne comporte pas de control flow (i.e. pas de if, else, while, for etc...), seulement une instruction de saut conditionnel JPZ. Si la condition explicité dans la documentation de JPZ est vérifé, JPZ réalise un saut absolu dans l'exécution du programme. Plus d'explication sont disponibles dans la documentation de JPZ.

Le langage est par ailleurs composé de trois éléments syntaxiques :
 - Les instructions, en trois lettres majuscules. Ex : LET, JPZ, CMT
 - Les registres, nommés A, B, C et D
 - Les littéraux, c'est à dire les nombres écrits en toute lettre. Ex : 123, -98
 - Les commentaires, qui sont ignorés pas l'interpréteur (cf CMT).

Certains scripts requièrent également des arguments. Ces arguments doivent être passés en ligne de commande à l'interpréteur après le nom du script. Par exemple si votre interpréteur se nomme mft et que votre script (nommé script.mft) a besoin d'un argument (ici on donne la valeur 2) alors ce que vous devez taper dans la ligne de commande est :

\>\> mft script.mft 2

# Instructions

Les instruction du langage se séparent en deux catégories :
 - Les instructions normales
 - Les instructions méta

La liste complète des instructions du langage est : LET, ADD, SUB, MUL, DIV, MOD, JPZ, ARG, RET, CMT.

## Instructions normales

Les instructions normales sont : LET, ADD, SUB, MUL, DIV, MOD, JPZ.

La syntaxe des instructions normales est toujours la même, on la détaille sur l'exemple de LET. Une documentation individuelle de chaque instruction suit.

Pour utiliser l'instruction normale LET, la syntaxe est toujours :

LET \<Litteral ou Registre\> \<Registre\>

Pour les instruction normales qui (comme LET) modofie un registre, le registre modifié est toujours le second argument.

Dans la documentation, le premier argument (noté %a) est donc un Litteral ou un registre, tandis que le second argument (noté %b) est toujours un registre.

### Documentation des instructions normales

 - LET %a %b : Assigne au registre %b la valeur dans %a. Formellement, %b = %a . Lire "On assigne %a à %b".
 - ADD %a %b : Ajoute au registre %b la valeur dans %a. Formellement, %b = %b + %a . Lire "On ajoute %a à %b".
 - SUB %a %b : Retire au registre %b la valeur dans %a. Formellement, %b = %b - %a . Lire "On retire %a à %b".
 - MUL %a %b : Multiplie le registre %b par %a. Formellement, %b = %b * %a
 - DIV %a %b : Quotiente le registre %b par %a. Formellement, %b = %b / %a
 - MOD %a %b : Assigne à %b le reste dans la division euclidienne de %b par %a. Formellement, %b = %b % %a
 - JPZ %a %b : Saute à la ligne %a si %b vaut 0 (JPZ est l'abréviation de "JumP Zero"). Lire "On saute à %a si %b".

## Instructions méta

Les instruction méta son des instruction qui font partie du langage, mais jouent un rôle un peu particulier. Les instructions méta sont : ARG, RET, CMT.

 - ARG \<registre\> : L'instruction ARG ("ARGument") récupère le prochain entier écrit dans argv (i.e. passé en argument du programme) et assigne sa valeur dans le registre passé en argument. Si aucun nombre n'est disponible dans argv, l'interpréteur doit s'arrèter avec un message d'erreur.

 - RET \<registre\> : L'instruction RET ("RETurn") sert à arrêter le programme en cours en renvoyant la valeur dans le registre. Pour plus de facilité d'utilisation, l'interpréteur pourra aussi renvoyer un message comme "L'application s'est terminée avec le code \<la valeur dans registre\>".

 - CMT : L'instruction CMT ("CoMmenT") sert à signaler un commentaire. Le reste de la ligne après CMT ne doit pas être utilisé par l'interpréteur, il s'agit du commentaire en question. Attention, les lignes qui commencent par CMT doivent tout de même être prises en compte par l'interpréteur, sinon les numéros de ligne de JPZ seront décalés. C'est à dire qu'il ne faut pas que vous essayiez d'optimiser l'exécution en retirant les lignes avec des CMT, sinon les scripts ne vont plus marcher.

# Limitations

Afin de limiter le travail à fournir, certaines limitation sont imposées au langage :
 - Une ligne de script devra toujours faire au plus 80 caractère (Note : le nombre 80 que l'on rencontre assez souvent dans ce contexte est hérité de la largeur du papier perforé).
 - Un script ne pourra pas faire plus de 230 lignes. Toute ligne après la 230ème sera ignorée.
 - Il n'y a que 4 registres dans le langage, et ces registres sont A, B, C et D.
 - Le langage ne fait que des manipulations d'entiers signés (int en C).

# Extensions possibles

Un lecteur avisé ne manquera pas de remarquer que le langage ainsi défini n'est pas Turing complet. Pour permettre au langage d'être Turing complet, une extension est prévue. Elle comporte deux nouvelles instructions normales LOD et STO ainsi qu'un mécanisme de pile.

Pour le mécanisme de pile, l'interpréteur devra mettre à disposition un espace de mémoire contigu (i.e. array) de 180 entiers. Cette espace mémoire servira de mémoire pile, bien qu'il ne soit pas géré comme une pile pour des raison de simplicité d'implémentation.

Les deux instruction à définir sont :
 - STO %a %b : Stocke la valeur du registre %b dans la mémoire pile à l'index %a.
 - LOD %a %b : Charge la valeur trouvé à l'adresse %a de la pile dans le registre %b.

Important : Comme dans la plupart des langages, il n'y a pas de mécanisme préexistant pour signaler à un script qu'une extension est disponible. Afin de coller au mieux aux mauvaises pratiques de l'industrie, la méthode choisie pour signaler que l'extension est disponible sera d'initialiser le registre A à la valeur 1783 (Note : année de fondation de l'école des Mines de Paris).

Un script qui souhaite utiliser cette extension devra donc commencer par vérifier la valeur inscrite dans le registre A pour savoir si elle est disponible, et agira ensuite en conséquence.
