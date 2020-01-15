/*
J'ai confiance que vous ne soyez pas arrivé là par hasard, mais au cas où je rappelle que ce fichier fait partie d'un appendice du tutoriel écrit par le Rezal sur le C.

La partie précédente de cette appendice avait pour but de montrer comment les fonctions en C étaient traduites en assembleur, et le but de cette partie est de montrer plus en subtilité l'implémentation des fonctions en C à travers l'étude de l'assembleur.

Contributeurs : Rezal P18
*/

.text
.globl main

/*
Comme vous avez pu le lire dans la partie précédente, pour écrire une fonction en assembleur il suffit d'écrire le nom de cette fonction sur une ligne (sans argument ni type de retour), de l'appeler avec call et d'en sortir avec ret.

Mais ces "fonctions" sont elles vraiment des fonctions comme en C. Pour le vérifier, écrivons un premier bloc de code.
*/

main:
  # On initialise les registres.
  movl $0, %eax   # (L1)
  movl $0, %ebx   # (L2)
  movl $0, %ecx   # (L3)

increment:
  addl $1, %eax   # (L4)

/*
Le code que nous avons écrit jusqu'ici est assez simple, mais que fait il vraiment ?

Exécutons ce programme pas à pas après être entré dans le main pour le comprendre.

D'abord on rencontre (L1) et on met eax à 0.
Ensuite on rencontre (L2) et on met ebx à 0.
De même on rencontre (L3) et on met ecx à 0.

Mais ensuite, que se passe t'il ? Sors t'on du main et du programme comme ce serait le cas en C ? Pour trancher cela, analysons le code binaire assemblé à partir de cet assembleur, tel que commenté par l'assembleur. Pour l'obteni vous pouvez utiliser le Makefile fourni (make bottom_of_the_pit) ou bien utiliser votre propre assembleur. Par précaution j'ai fourni une version assemblée sur mon propre PC nommé bottom_of_the_pit_precommented.o

En regardans le code binaire produit vous vous apercevrez qu'entre (L3) et (L4) la ligne que nous avions écrite ("increment:") est traduite par ... rien du tout. Par suite lorsqu'il exécutera notre code le processeur, après avoir exécuté (L3) passera directement à (L4) puisque c'est la ligne qui suit !

Ce n'est pas du tout la même chose qu'en C ! Sauf dans les cas des différents case d'un switch ...
*/

/*

                                  Labels - 4****

Pour comprendre pourquoi cette exécution est si différente du C, il faut comprendre que "main:" et "increment:" ne sont pas des déclarations de code comme en C mais des labels. Même si ce n'est souvent pas ainsi qu'il est écrit, le code que nous avons écrit plus haut est équivalent à :

main:       movl $0, %eax
            movl $0, %ebx
            movl $0, %ecx
increment:  addl $1, %eax

main et increment ne sont que des labels (étiquettes) que nous plaçons sur les lignes 1 et 4 de notre programme. C'est à dire que nous nommons les 1 et 4 de notre programme 1 et 4 respectivement. Pour chaque étiquette dans notre code l'assembleur va noter la ligne à laquelle elle correspond (lisible en bas du fichier binaire commenté). Par exemple le main sera noté 0 car c'est la première ligne dans l'exécution de notre programme.

Mais alors à quoi servent ces labels, et comment l'assembleur s'en sert-il dans les fonctions call et ret ?

Pour comprendre cela, écrivons un peu plus de code.
*/

loop:
  addl $1, %ebx  # (L5)
  cmp $5, %ebx   # (L6)
  jne loop       # (L7)

/*
Le code qui précède (exécuté après increment car il n'y a pas de code binaire entre les deux) comporte pas mal d'instructions nouvelles, exécutons le pas à pas pour mieux le comprendre.

On arrive à L5, nommé loop, donc on ajoute 1 à ebx. ebx vaut 1.
On arrive à L6 qui nous demande de comparer 5 à ebx (i.e. de regarder si 5-ebx vaut 0).
Ce n'est pas le cas, on le note dans un registre quelconque et on passe à la suite de l'exécution.
On arrive à L7. jne signifie "jump if not equal", cette instruction regarde dans le registre où cmp a laissé son résultat, ici "faux" et agit en conséquence. Comme On trouve un faux dans ce registre on fait un jump vers la ligne nommée loop (i.e. L5).

On est de nouveau à L5, donc on ajoute 1 à ebx. ebx vaut à présent 2.
On arrive L6, la comparaison renvoie encore faux, donc L7 nous fait encore sauter vers L5.

Vous comprenez certainement là où nous allons, la boucle que nonus avons écrit s'exécutera 5 fois, jusqu'à ce que ebx vale 5, auquel cas jne loop se contentera de ne rien faire et nous laissera passer.

Mais comment fonctionne ce mystérieux jump ?
*/
  cmp $5, %ebx
  # Si ebx != 5 le programme s'arrète ici et renvoie 1.
  jne erreur
/*

                            Instruction pointer - 4****

En fait en plus des registres visibles dans votre processeur il y a aussi quelques registres cachés, dont le plus important est l'instruction pointer (abbrégé ip, sans lien avec les adresses ip). Le rôle de l'ip est très simple : à tout instant de l'exécution d'un programme il contient l'adresse de la prochaine instruction à exécuter.

Cette prochaine instruction est usuellement la suivante dans le programme, mais il est également possible de changer sa valeur pour aller ailleurs dans notre programme. Le processeur se contentera de sauter vers cette nouvelle instruction puis l'exécution suivra son cours à partir de là. L'équivalent en C de cette manipulation est le goto, qui est très vivement déconseillé car il rend vos programmes très difficiles à relire, et pour comprendre ce qu'ils font il est souvent nécessaire d'exécuter votre code pas à pas, ce qui est souvent très laborieux (surtout que tout code avec des goto peut se réecrire sans).

Mais en assembleur la situation est différente, simplement parce qu'à ce niveau d'abstraction (ou plutôt d'absence d'abstraction) il n'y a rien d'autre de disponible !

La différence entre un simple jump et la combinaison call + ret est que call + ret vous fournissent des instructions plus faciles à utiliser pour des fonctions.

Notamment lorsque vous appelez call, l'adresse du programme à laquelle vous vous trouvez +1 sera stockée dans un registre du processeur avant de faire le saut. Ainsi lorsque vous appelez ret l'instruction ira chercher le point où vous devez aller dans votre programme une fois que l'exécutionde votre fonction est terminée.

Notez que l'instruction call n'est donc pas vraiment indenspensable pour écrire de l'assembleur, nous pourrions aussi gérer ces étapes manuellement avec des jumps.

Le label suite est celui d'une courte fonction à la fin du fichier, et la syntaxe $suite signifie exactement ce que vous pourriez penser, à savoir que $suite représente l'adresse dans le programme à laquelle il faut sauter pour exécuter la fonction suite. On met donc l'adresse du label suite dans le registre rcx, et pour revenir à l'exécution du code la fonction self_made aura juste à faire un jump sur l'adresse notée dans rcx.

Notez qu'il serait aussi possible de faire un saut relatif en stockant dans rcx quelque chose comme "l'adresse qui se trouve n bits plus loin que l'adresse courante" mais cela est assez avancé et je ne comprends pas bien la syntaxe moi-même (parce que je n'ai pas cherché parce que je m'en fiche).
*/
  movq $suite, %rcx
  # jmp ("jump") est un simple jump sans conditions.
  jmp self_made

suite:
  cmp $18, %ebx
  /*
  Si ebx est différent de 18 l'exécution s'arrète içi et le programme renvoie 1
  */
  jne erreur

/*

                              Stack Memory - 4****

Résumons donc.

Les fonctionns en C sont traduites en assembleur par des blocs de code. Le début de ces blocs de code est indiqué par un label auquel l'exécution du programme peut aller dès qu'on le souhaite et dont on peut également revenir.

Certes semble un peu différent des fonctions en C, mais ce n'est pas grand chose non plus, si ?

En réalité cette distinction introduit une différence fondamentale : les fonctions en C sont des blocs logiques autonomes (printf fera toujours la même chose quoiqu'il se passe dans votre code) alors que les fonctions en assembleur sont comme des blocs qui s'inséreraient dans votre code.

En fait, les fonctions en assembleur sont plus proches des macros des langages de programmation (i.e. des morceaux de code qui s'écrivent automatiquement dans votre programme) que des fonctions. Pourtant dans beaucoup de langages de programmation les developpeurs trouvent les macros plus commodes à utiliser (pas forcément à écrire). Il s'agit souvent d'une fonctionnalité qui est recherchée dans un langage alors qu'elle n'y est pas présente par défaut.

Donc pourquoi ceux qui ont écrit le C (K&R) ont jugé qu'il valait mieux utiliser un système de fonctions plutôt qu'un système de macros comme on pourrait très facilement le construire par dessus l'assembleur ?

La réponse à cela est en fait à peu près la même que celle qui rend l'intégration de macros difficiles dans un langage de programmation : les variables locales. Si dans votre code vous définissez une variable var, puis que vous appellez une macro qui définit elle même en interne une variable var, que doit-il se passer ? Vous voulez insérer le code de la macro dans le votre, mais vous ne voulez pas que votre var soit modifiée par la macro non plus !

En assembleur il n'y a pas de problème avec cela, juste un cauchemar insoluble parce que non seulement l'exécution de votre code en assembleur se passera exactement comme vous aviez utilisé une macro (ou comme si vous aviez recopié le code de votre fonction à la main), mais en plus de cela vos "variables locales" sont les registres qui sont prédéfinis et dont le nombre est limité.

C'est à dire qu'en assembleur vous n'avez pas à avoir peur que l'appel d'une fonction complexe réécrive le contenu de vos "variables locales" (registres) parce que vous avez la certitude qu'elle va le faire.

Mais alors, comment le C fait-il pour implémenter des fonctions isolées logiquement alors que l'assembleur ne semble pas le permettre ?

Si les registres sont de loin l'outil le plus pratique à utiliser pour un humain, il ne sont pas le seul outil à votre disposition. La solution à ce problème de partage est une vielle amie du C : la mémoire stack (ou pile en français).

Sans doute avez vous maudit la mémoire stack en C parce qu'elle cause beaucoup de comportements difficiles à voir dans le code pour un débutant (notamment si on renvoie plus ou moins directement des pointeurs d'une fonction), mais maintenant il est temps d'expliquer pourquoi cette mémoire stack est en fait une outil extrèmement efficace pour vous protéger de comportements autrement plus difficiles à comprendre.

Notez que la notion de mémoire stack n'a pas été inventée en C, son usage était déjà obligatoire pour de gros programmes en assembleur. En revanche le C a le mérite d'automatiser le fonctionnement de cette mémoire stack pour vous, ce qui est un grand service.
*/

  # On écrit 64 dans rax.
  movq $64, %rax
  # On va appeler une fonction mais on ne veut pas perdre la valeur dans eax...
  # Rien de plus simple : on met eax sur le dessus de la mémoire stack.
  push %rax
  call fonction
  /*
  Fonction a remis rax à 0, on a donc perdu la valeur qui s'y trouvait ... mais on peut toujours la réxupérer depuis la mémoire stack. On sait que la dernière chose que l'on a mis dans la stack est rax, donc pour restaurer rax il suffit de faire :
  */
  popq %rax
  # On vérifie que cela marche bien...
  cmp $64, %rax
  jne erreur
  /*
  Ca a marché !

  En fait la seule condition pour que cela fonctionne est que chaque fonction doit ajouter autant de valeur sur la stack qu'elle en enlève. Cette condition peut devenir assez pénible à vérifier si vous le faites à la main, mais le compilateur C peut le faire pour vous sans la moindre difficulté.

  Vous pouvez également utiliser la mémoire stack pour faire d'autres choses en assembleur si vous le souhaitez, ce n'est qu'une pile de mémoire après tout.

  Notez que l'implémentation de la mémoire stack est très semblable à celle que l'on a fait d'une pile en C, il s'agit en fait d'un grand tableau contigu de mémoire. La différence avec ce que l'on ferait en C avec des mallocs (qui n'est pas la seule implémentation possible, la preuve est présente ici) est que la mémoire stack a une taille fixe prédéfinie qui est déjà allouée en mémoire. Pour ajouter un élément dans la stack il suffit donc de l'y ajouter sans autre vérification, ce qui est beaucoup plus rapide que d'utiliser la mémoire heap puisqu'il n'y a presque rien à faire.

  Enfin, même si je ne vais pas le montrer ici sachez qu'il est possible de manipuler la mémoire stack directement à l'aide de registres dédiés (respectivement le sommet et la base de la pile) mais je ne vais pas le montrer ici.
  */
  movl $0, %ebx
  movl $1, %eax
  int $0x80

fonction:
  # Cette fonction ne fait qu'une seule chose, elle remet rax à 0.
  movq $0, %rax
  ret

self_made:
  # On fait des choses içi
  movl $18, %ebx
  jmp *%rcx

erreur:
  # Une fonction utilisée si je dis une bêtise :-)
  movl $1, %eax
  movl $1, %ebx
  int $0x80


/*

                              Le mot de la fin - 5!!!!!
                                    L'abysse

Maintenant que vous avez lu tout ce tutoriel, vous avez probablement trouvé des explications sur des notions du C (et même d'autres langages) qui ne pouvaient pas être expliquées autrement. Peut-être êtes vous satisfaits et prêts à retourner à votre quotidien (et ce ne serait pas une mauvaise idée), mais vous vous rendez sans doute compte que l'explication que j'ai faite de ces mécanismes lève finalement plus de problèmes qu'elle en résout.

Comment sont écrites les instructions en assembleur ? Lorsque l'on écrit un programme en C on appelle des fonctions qui sont écrites en C ou en assembleur, mais du coup vers quoi se tournent les instructions en assembleur pour s'exécuter ? Y a t'il un code source disponible de l'instruction add ? En quoi serait-il écrit ?

Et de manière plus générale, comment votre processeur fait-il pour le code exécutable que vous lui envoyez ? Certes vous lui envoyé un code différent pour chaque instruction, mais il faut bien qu'il y ait une sorte de test effectué sur les octets que vous envoyez au processeur pour qu'il sache de quelle instruction vous parlez ... Mais si l'assembleur est la plus petite brique possible, comment est écrit un test qui permettrait au processeur de comprendre l'assembleur ?!

Ces trois problèmes procèdent toutes à leur façon d'une même question : comment est posée la première pierre en informatique ?

Mais contrairement à ce que votre philosophe intérieur pourrait penser, il y a une vraie réponse à cette question : l'assembleur est bien la première pierre de l'informatique. Les instructions en assembleur et le décodage de ces instructions ne sont écrits dans aucun langage de programmation. Il s'agit seulement de vastes circuits électroniques.

Peut-être pour mieux cerner cela est-il bon de se rappeller qu'à l'origine, un ordinateur est simplement une machine programmable. Ces instructions accessibles depuis l'assembleur ne sont en réalité qu'une forme très évoluée de "boutons" que l'on peut utiliser pour contrôler la machine.

La raison pour laquelle je parle d'abysse dans ce tutoriel est qu'en deça de l'assembleur, personne n'est vraiment capable de dire ce qui se passe dans la machine. Le design de processeur est par nature très complexe, et ceux que vous utilisez dans vos PC (Intel ou AMD) sont indéniablement les plus complexes qui soient, et vu que les implémentations faites ne sont pas open-source, il n'est simplement pas possible de dire avec assurance ce que fait votre processeur pour exécuter votre code. En dessous de l'assembleur se trouve une abysse très complexe, propriétaire et difficilement prévisible que je ne peux pas vous expliquer simplement.

Et peu importe me direz-vous : ce qui compte c'est que la machine fasse ce que l'on veut, pas comment elle le fait. Et vous auriez raison, dans une certaine mesure. Mais ce qui importe ici est que toutes ces questions sortent vraiment du champ de l'informatique et sont bien ancrées dans le domaine de l'électronique (en particulier le design digital, sous lequel on trouve encore le design analogique).

Pour ceux que le sujet pourrait intéresser, je vous fais une petite compilation de questions qui pourraient vous être utiles.

Comment crée-t-on des circuits électroniques qui réalisent des fonctions logiques (comme par exemple ceux des instructions de l'assembleur) ?
 - Voire Hardware Description Language (Verilog ou VHDL), FPGA et ASIC.

Comment fonctionne un processeur ?
 - Voire fetch-decode-execute cycle, pipelining et branch prediction pour la théorie, RISC-V pour la pratique.

Quelle est la différence entre une carte graphique et un processeur ?
 - Voire SIMD pour la théorie, OPENGL, CUDA, VULKAN ou OPENCL pour la pratique.

Pourquoi les processeurs de téléphone n'ont ils pas besoin d'être refroidis contrairement à ceux des ordinateurs ?
 - Voire RISC vs CISC, Task Parallelism et MIMD.

Pourquoi ne met-on pas plus de coeur dans les processeurs pour en améliorer les performances ?
 - Voire Memory Centric Architecture et NUMA (Non Uniform Memory Access).

Comment fonctionne la mémoire dans un PC ?
 - Voire DRAM / SRAM, Cache, Cacheline, virtual memory, page table et TLB.
*/
