/*
Ce fichier est la suite du tutoriel sur l'implémentation des fonctions en C.
Il s'agit d'un fichier de code en assembleur (d'où l'extension .s). En
assembleur les commentaires sont précédés par des # ou entourés comme en C

Le jeu d'instruction utilisé est x86_64, qui est le jeu d'instruction
propriétaire développé par Intel et AMD, les deux compagnies qui produisent
environ tous les processeurs d'ordinateurs personnels dans le monde (donc
votre ordinateur utilise aussi certainement le jeu d'instruction x86_64).
*/

/*

											Le jeu d'instruction x86_64 - 4****

Avant de rentrer dans le vif du sujet, un petit point historique s'impose. Si
l'assembleur est aujourd'hui synonyme de code machine, cela n'a pas toujours
été le cas. A l'origine l'assembleur a été concu pour être écrit ligne par
ligne par des humains. Si cet aspect a pour bonne partie disparu sur les jeux
d'instruction modernes (ARM et RISC-V par exemple) il est important de savoir
que le jeu x86_64 n'est pas moderne du tout.

En effet, si le jeu d'instruction x86_64 a conçu aux alentours des années
2000 (par AMD, d'où son autre nom AMD64) il a été pensé pour être
rétrocompatible avec le jeu d'instruction utilisé par les ordinateurs 32 bits
de l'époque nommé x86 (développé par Intel cette fois). Ce passage du jeu
d'instruction x86 à x86_64 est ce que l'on appelle communément le passage des
ordinateurs 32 bits à 64 bits.

Mais le jeu d'instruction x86 d'Intel tire son nom d'une série de processeurs
développés par Intel (dont les noms finissaient tous par 86, d'où le x86)
avec lesquel le jeu d'instruction est apparu ... en 1978 (processeur 8086)!
Or en 1978 écrire du code en assembleur n'était pas aussi rare
qu'aujourd'hui, par conséquent le jeu x86 a été pensé pour pouvoir être écrit
à la main. Pour utiliser le terme technique, il s'agit d'un jeu avec un
design CISC (Complex Instruction Set Computer) c'est à dire que les
instructions dans l'assembleur x86 peuvent réaliser des opérations clairement
non triviales, contrairement à un jeu d'intruction RISC (Reduced Instruction
Set Computer) qui ne fournit généralement que le nombre minimal
d'instructions nécessaires pour pouvoir faire fonctionner le processeur (i.e.
il y a moins voire pas d'instructions complexes plus pratiques à utiliser par
un humain). Les jeux d'instruction RISC ont souvent moins d'instructions que
leur compétiteurs CISC (d'où leur nom) et sont souvent plus récents. Les deux
design ont leurs avantages et inconvénients, mais dans notre cas un jeu CISC
sera plus facile à comprendre.
*/

/*

														  Notre programme

Le petit .text que vous voyez juste en dessous est un message destiné à
l'assembleur (le programme qui va assembler notre code) pour lui dire que ce
qui suit est le code qu'il doit assembler. Globalement les lignes qui
commencent par des . sont moins essentielles pour comprendre ce qui se passe
dans notre code et en général plus obscures, donc je préfère ne pas trop m'y
attarder.
*/

.text
.globl main

/*
Je vous mets le programme en un bloc une première fois pour que vous puissiez
le lire (et pour que l'assembleur puisse faire son travail), et ensuite j'en
commenterai longuement toutes les lignes.
*/

main:
  movl $1, %eax
  movl $2, %ebx
  call add
  movl %ecx, %ebx
  movl $1, %eax
  int $0x80

add:
  movl $0, %ecx
  addl %eax, %ecx
  addl %ebx, %ecx
  ret


/*
Comme vous pouvez le voir le code que nous avons ici à écrire est nettement
moins grand que ce qu'à proposé GCC. En effet GCC est optimisé pour pouvoir
compiler efficacement tous les programmes en C, et notre programme (faire une
seule addition d'entiers) n'est clairement pas un programme représentatif de
tout ce qui se fait en C.

Cela étant vous contaterez en relisant le fichier simple.s que l'assembleur
produit par GCC, à l'exception de tous les .cfi... est presque directement
traduit en assembleur.
*/

/*

                         L'assembleur - 4****


Comme vous avez pu le constater dans le code au dessus, l'assembleur est
assez déroutant à lire quand on n'en connait pas les secrets. Pour comprendre
(au moins un peu) l'assembleur il y a plusieurs points qu'il est nécessaires
de savoir.

L'assembleur ne fournit pas (enfin presque pas) d'abstraction entre ce que
vous écrivez et ce que fera la machine. Par suite en assembleur vous devez
vous préoccuper de notions matérielles qui n'interviendraient pas dans un
programme dans un langage de programmation. La première notion importante est
celle des registres.

Vous savez certainement qu'un ordinateur est contitué de plusieurs parties
importantes : le processeur (CPU) exécute les instructions écrites dans les
exécutables, la mémoire (RAM) sert de stockage pour les données dont nos
programmes ont besoin et le disque dur (ou SSD) sert à enregistrer des
données très lourdes ou bien auxquelles il ne faut accéder que rarement (par
exemple vos fichier). Mais lorsque l'on regarde dans le détail, ce découpage
assez simple cache certains éléments importants, le plus important d'entre
eux étant que le processeur contient déjà un peu de mémoire.

Sans parler de la mémoire cache du processeur (intéressante mais un peu hors
sujet) le processeur contient également des registres. Ces registres sont de
minuscules blocs de mémoires (de l'ordre de 10~100 bits) qui peuvent contenir
une seule variable en mémoire. Certains registres sont dits d'usage général
(ceux dont le nom finit par un 'x') tandis que d'autre ont un usage prédéfini
qu'il faut respecter dans vos programmes. Mais l'information importante est
que ces registres ne sont pas des abstractions que l'assembleur met à votre
disposition pour vous faciliter le calcul, il s'agit de petits bouts de
mémoire bien physiques qui se trouvent dans votre processeur. Dans notre
programme nous n'utiliserons que des registres d'usage général, mais pour
écrire un programme réel il faudrait savoir à quoi servent à peu près tous
les registres du processeur (il n'y en a pas tant que ça, environ un
vingtaine de différents).

Très bien, en assembleur pour faire fonctionner mon programme il faut que
j'utilise des registres. Comment fait-on cela ?

Vous voyez, c'est ici que les choses deviennent intéressantes. Les registres
de votre processeur ont un nom, et pour les utiliser dans votre code il faut
les designer par %<leur nom>. Mais le détail intéressant est que
contrairement à des variables dans un langages de programmation, ce n'est pas
vous qui nommez les registres de votre processeur, il ont un nom prédéfini et
immuable. Du coup la seule façon de savoir comment utiliser ces registres est
de connaitre quelqu'un qui sait déjà commment se nomment les registres (fût-
ce cette personne Wikipédia, dont l'article en anglais sur x86 vous sera d'un
grand secours).

La deuxième chose importante à comprendre est que commme l'assembleur ne vous
offre pas d'abstraction par rapport aux opérations que fait la machine, le
concept de variable locale n'existe pas en assembleur. Si vous voulez faire
quelque chose il vous faudra directement manipuler les adresses mémoire (ou
les registres) dans lesquels la valeur est stockée. C'est assez destabilisant
si on ne le sait pas et que l'on essaie de lire en assembleur, mais en
pratique ce n'est pas si dérangeant (jusqu'à ce qu'en fait ça le soit, vous
verrez dans le commentaire du code). Vous pouvez cependant nommer certains
espaces mémoires, mais je montrerai pas cela içi.

Enfin troisième information notable, il n'y a pas de système de types en
assembleur. Vous me rétorquerez sans doute que le C n'avait déjà pas vraiment
un système de types respectable, mais pour le coup en assembleur la notion de
type n'existe même pas. Vous ne faites que manipuler les valeurs des octets
derrière des adresses en mémoire, indépendamment du sens que vous donnez à
ces octets. La seule chose qui compte en assembleur est la longueur en
mémoire des données que vous manipulez, mais cette longueur est déterminée
non pas en utilisant le type des données, mais en fonction de l'instruction
que vous demandez d'effectuer.

Maintenant que vous connaissez tout cela vous pouvez sans trop de problèmes
lire le code qui est écrit plus haut.
*/

/*
Tout d'abord on déclare le label main, c'est à dire qu'à chaque fois que l'on
parlera de main dans notre code l'assembleur saura que nous parlons de ce qui
est à la ligne 1 de notre code.
*/

# (L1) main:

/*
On commence par écrire la valeur de 1 (notée $1, c'est à dire la constante
qui vaut 1) dans le registre nommé eax. L'instruction dédiée se nomme mov, et
ici on utilise la variante 32 bits de mov appellée movl (pour "move long").
Comme on a passé une instruction qui porte sur 32 bits à l'assembleur il sait
que la valeur $1 dont nous parlons est la valeur de 1 codée sur 32 bits.
Cette ligne correspond à la ligne (dans notre code C) :
*/

# (en C) int a = 1;
# (L2)  movl $1, %eax

/*
De même pour le registre ebx que l'on utilise pour contenir la variable de b.
La corrspondance des noms (mettre a dans eax, b dans ebx et c dans ecx) est
fortuite et pas du tout nécessaire pour que le code fonctionne.
*/

# (en C) int b = 2;
# (L3)  movl $2, %ebx

/*
Ici on fait notre appel de la fonction add. Comme vous pouvez le constater,
nous ne passons pas d'argument à add, contrairement à ce qui est fait en C.
La raison deviendra apparente lorsque nous arriverons au code de add.
*/

# (L4)  call add

/*
Nous récupérons ici la valeur dans le registre ecx (c'est là où add stocke
son résultat) et nous l'écrivons dans le registre ebx. Pourquoi dans ebx ?
Parce qu'il s'avère que la valeur de retour de notre programme
(plus_simple.elf) est récupéré depuis le registre ebx à la fin de
l'exécution. Et comment savons nous cela ? Parce que quelqu'un nous a dit que
c'est comme cela qu'il faut faire.
*/

# (L5)  movl %ecx, %ebx

/*
Je ne sais pas vraiment à quoi cela correspond, mais avant de finir
l'exécution de notre programme nous devons mettre eax à 1 pour éviter une
faute de segmentation. J'expliquerai pourquoi 1 juste après.
*/

# (L6)  movl $1, %eax

/*
La dernière ligne dans l'exécution de notre programme. Le int signifie
"interruption" et non pas integer comme on aurait pu le penser. La ligne int
$0x80 est immuable sous linux, il s'agit du célèbre system call (ou plutôt
kernel call en fait). Vous vous souvenez sans voute qu'en C nous avions la
possibilté d'utiliser la fonction pour demander à l'OS de faire quelque chose
pour nous, et bien en assembleur nous disposons de int $0x80 (moins explicite
je vous le concède) pour demander au noyau de faire quelque chose. Pour
rentrer un peu dans le détail, lorsque nous appelons int $0x80 no code va
s'interrompre pour aller exécuter ce qui se trouve à 0x80, à savoir le kernel
call. Lorsque l'exécution atteindra 0x80, le code dans le kernel call va lire
ce qui se trouve dans le registre eax et agir en conséquence. Dans notre cas
le registre eax contient la valeur 1, ce qui correspond à la fonction exit
(i.e. à la fin de l'exécution de notre programme). Mais la fonction exit doit
renvoyer une valeur à l'exterieur, qui est normalement un code d'erreur de
notre programme (0 s'il n'y a pas eu d'erreur et autre chose sinon), et il
trouve cette valeur dans le registre ebx. Or nous avons écrit le résultat de
notre calcul dans ebx, donc le code d'erreur de notre programme sera 3.

Vous vous demandez sans doute comment j'ai trouvé cela, et bien la raison est
toujours la même : je connais quelqu'un (certes Internet, mais l'idée reste
la même) qui connaissait la réponse. C'est d'ailleurs un aspect très
frustrant de la programmation bas-niveau, il y a énormément de protocoles
plus ou moins explicites et plus ou moins documentés à respecter pour faire
ce que l'on souhaite. Et autant pour les kernel call de Linux ce n'est pas un
problème parce que Linux est open-source et bien documenté, mais la plupart
du temps si vous travaillez en bas niveau c'est probablement avec du matériel
et des protocoles propriétaires, ce qui rend les recherches au mieux
éprouvantes, au pire infructueuses.
*/

# (L7)  int $0x80

/*
On arrive à la définition de add. Remarquez que même si je vous ai dit que
add est une fonction, rien dans le code ne le suggère. J'ai juste nommé la
ligne 8 de mon code add.
*/

# (L8) add:

/*
On compte renvoyer le résultat de notre addition dans le registre ecx, donc
il faut d'abord l'initialiser pour avoir le bon résultat sur notre calcul.
*/

# (L9)  movl $0, %ecx

/*
On ajoute le contenu du registre eax (que l'on a mis à 1 tout à l'heure) au
registre ecx. addl x, y signifie "ajoute x à y et note le résultat dans y".
*/

# (L10) addl %eax, %ecx

/*
idem pour b dans lequel on a mis 2 dans le main.
*/

# (L11) addl %ebx, %ecx

/*
On retourne. Remarquez que contrairement au C ou à n'importe quel langage de
programmation, on ne retourne pas "quelque chose" d'une fonction, il s'agit
plutôt d'un retour comme dans "on retourne là où on était avant d'appeller la
fonction", c'est à dire que l'on passe à la ligne 5 de notre code.
*/

# (L12)  ret

/*
En lisant ce code vous ne voyez probablement pas trop en quoi les registres
sont différents des variables locales, et dans le code écrit ci-dessus ce
n'est effectivement pas évident. Mais avant d'expliquer cela prenez le temps
de vérifier que le code ci-dessus fonctionne correctement. Pour en obtenir un
exécutable, utilisez make plus_simple, ce qui devrait vous fournir un
exécutable plus_simple.elf

L'exécution de plus_simple ne fera rien du tout, en revanche si vous regardez
le code de sortie de la fonction vous verrez qu'il vaut bien 3. Pour voir le
code de sortie d'un process sous Linux vous pouvez en ligne de commande
exécuter plus_simple.elf puis à la ligne suivant faire echo $?, qui vous
renverra le code d'erreur de ce qui vient d'être appelé.

Pour comprendre vraiment en quoi l'assembleur est différent des langages de
programmation, pourquoi ce qui semble être une fonction en assembleur n'en
est pas vraiment une et en quoi les registres sont différents des variables
locales afin de vraiment comprendre l'implémentation des fonctions en C, faites le dernier pas et lisez le tutoriel dans le dossier bottom_of_the_pit.
*/
