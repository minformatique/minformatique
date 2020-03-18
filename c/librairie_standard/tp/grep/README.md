# grep

grep est un outil très commun de la ligne de commande de linux. Il permet de 
chercher des expressions régulières dans des fichiers.

Réimplémenter grep complètement serait assez fastidieux et la gestion 
d'expressions régulières est assez délicate, donc pour ce TP nous nous 
contenterons d'un grep plus simple qui prend en argument un unique mot (sans 
espaces). Notre grep va ensuite lire son input (stdin) ligne par ligne, et 
afficher sur l'output (stdout) toutes les lignes qui contiennent ce mot avec 
devant le numéro de la ligne (en commençant à compter à partir de 0, 
évidemment).

Les éléments à gérer dans ce tp sont principalement :
 - Lire l'input ligne par ligne. Il y a une fonction dédiée dans la librairie 
standard pour lire un fichier ligne par ligne, à vous de voir comment 
l'utiliser içi.
 - Lire un ligne de l'input (stockée dans une chaîne de caractères char \*) 
mot par mot. Là aussi la librairie standard peut faire cela sans problèmes, 
il faut juste trouver la bonne fonction. Notez que pour ce TP, un mot est une 
suite de caractères sans espaces.

Un exemple de l'utilisation de l'outil grep obtenu pour clarifier les choses 
(notez que le Makefile en question est celui de ce dossier) :

>> cat Makefile | ./grep[elf,exe] Compilation
11 :	echo "Compilation de $(SUJET).elf achevée."
14 :	echo "Compilation de $(SUJET).exe achevée."
