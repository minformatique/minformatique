# Alignement de pointeurs
(Note) Comprendre la notion de pointeurs alignés n'est pas fondamental pour 
réaliser ce tp, mais c'est toujours bien à placer dans une discussion en 
soirée si vous voulez que les gens arrêtent de vous parler et vous laissent 
manger tous les snacks tranquillement.

Le C permet la plupart du temps de s'affranchir des limitations matérielles de 
la machine sous-jacente pour que vous puissiez vous concentrer sur ce qui vous 
intéresse, mais cela ne veut pas dire que ces limitations n'existent pas!

Un cas "courant" que l'on peut rencontrer est le problème d'alignement de 
pointeur. Fondamentalement, la question de l'alignement de pointeurs vient du 
fait qu'un processeur est un circuit électronique (certes très complexe) dans 
lequel on a branché un grand nombre d'instructions afin de faire tout ce dont 
on a besoin.

Mais cela ne signifie que toutes les opérations que l'on pourrait imaginer 
sont possibles dans un processeur; certaines configurations ne sont pas 
câblées et donc impossibles à réaliser. C'est le problème qui apparait 
avec les pointeurs non alignés.

Un pointeur est dit aligné si l'adresse mémoire qu'il représente est un 
multiple du nombre d'octets du jeu d'instruction du processeur. Par exemple sur 
une machine 32 bits (i.e. 4 octets), un pointeur est dit aligné si son adresse 
mémoire est un multiple de 4 (c'est comme si on n'avait branché qu'une 
instruction sur 4). Vos PC sont très certainement des machines 64 bits 
rétrocompatibles avec le jeu 32 bit d'Intel, donc pour ce TP nous 
considérerons qu'un pointeur est aligné si son adresse est un multiple de 4.

Notez que lorsque vous écrivez un programme en C, le compilateur se charge 
pour vous de toujours utiliser des pointeurs alignés, c'est pourquoi vous 
n'avez presque jamais à vous soucier de cela. Les problèmes d'alignement de 
pointeurs arrivent plutôt lorsque l'on travaille sur des micro-controlleurs et 
que l'on essaie de faire des chose très bas niveau qui nécessitent de rentrer 
des adresses mémoire à la main.

Notez enfin que sur votre PC, il est probable que le processeur que vous 
utilisez accepte n'importe quelle adresse avec seulement une pénalité en 
performance. En revanche si vous travaillez sur des micro-controlleurs (par 
exemple des cartes arduino) ce ne sera probablement pas le cas. Par exemple le 
jeu d'instruction ARMv6 (~1980) pouvait causer des erreurs silencieuses si on 
manipulait des données non alignées. Si cela vous intéresse vous pouvez en 
apprendre plus sur Wikipédia.

Attention, pour l'alignement de pointeurs seul le bit de départ et la longueur 
lue comptent. Imaginons un entier de 4 octets se trouvant à l'adresse 24. 
Lorsqu'on lui donnera une valeur entière, certes on manipulera des octets qui ne
sont pas sur une adresse multiple de 4 (ceux sur les 25ème, 26ème et 27ème 
adresses) mais comme notre opération a commencé sur un pointeur bien aligné 
il n'y a pas de problèmes.

Le but du TP est d'écrire une fonction qui vérifie qu'un pointeur est bien
aligné. Pour résoudre ce problème vous aurez sans doute besoin de récupérer 
l'adresse d'un pointeur sous forme d'un nombre entier. Je vous laisse chercher 
comment faire sur internet : la solution canonique n'est pas très complexe une 
fois qu'elle a été trouvée.
