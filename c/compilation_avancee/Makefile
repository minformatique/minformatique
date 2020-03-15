# Ce Makefile a pour but de montrer comment on peut compiler du code en C en
# utilisant une librairie extérieure. Il montre aussi rapidement comment utiliser
# make pour compiler des projets plus complexes, par exemple avec plusieurs
# composantes.
#
# Contributeurs : Rezal P18

#
#														L'outil make - 1*
#
# Je ne l'ai pas détaillé jusqu'ici car il n'y avait souvent qu'une seule chose
# à compiler dans nos tutoriels, mais la structure de base d'une commande make
# est :
#
# <nom de la commande> : <fichiers suivis>
# 		<commandes>
#
# Le nom de la commande est ce qu'il faut taper dans la ligne de commande afin
# de déclencher l'execution (par exemple make test va compiler unit_test.elf).
# Les fichiers suivis sont ceux dont on a besoin pour notre compilation. make
# est un outil intelligent qui ne recompilera que ce dont on a besoin à chaque
# fois qu'on l'appelle. Par exemple si on ne change pas les fichiers pile.c,
# pile.h ou unit_test.c après avoir appelé make test, alors make s'en rendra
# compte et se contentera de nous le signaler sans rien recompiler. Cet aspect
# est particulièrement important lorsque l'on travaille sur de grands projets
# qui peuvent mettre des heures à recompiler entièrement. Grâce à ces
# recompilations partielles, on peut gagner beaucoup de temps lorsque l'on
# teste des modifications du code source. Notez cependant que pour que cela
# fonctionne il faut écrire ses fichiers Makefile d'une façon intelligente.
#
#
# Ces Makefiles peuvent rapidement devenir difficiles à lire, pour éviter cela il
# est fortement recommandé de définir des alias dans vos Makefiles (au début du
# fichier souvent). La syntaxe est :
#
# alias := <ce par quoi l'alias sera remplacé>
#
# Pour utiliser l'alias dans la suite du fichier il suffit alors d'écrire $(alias)
SOURCES_UNIX 	:= calculatrice.c calcul.c expression.c symbole.c
HEADER		:= calculatrice.h
LIBRAIRIE_UNIX 	:= libPile.so pile.h
CC_UNIX		:= cc

# On dédouble tout pour windows. Comme vous pouvez le reamrque, écrire de tels
# Makefile est assez pénible, c'est pourquoi on a inventé l'outil autoconf. Si
# vous avez déjà compilé des projets open-source, vous savez sans doute que la
# marche à suivre est : 
# >> ./configure
# >> make
# >> make install
#
# Le "./configure" est géré par un outil nommé autoconf, qui va générer le Makefile
# qui convient à vos besoin, et donc éviter d'avoir comme ici des Makefile redondants
# et pas très clairs.
SOURCES_WIN 	:= calculatrice.c calcul.c expression.c symbole.c
HEADER		:= calculatrice.h
LIBRAIRIE_WIN 	:= pile.dll pile.h
CC_WIN		:= clang.exe

# Les arguments de compilation que nous utilisons sont :
#  -Wall : "Warnings All", qui, contrairement à ce que son nom suggère, n'active
#  pas tous les warnings, seulement les plus courants. Notez qu'un warning de
#  -Wall est dans la plupart des cas une erreur de code.
#
#  -g : signifie au compilateur que nous souhaitons placer des symboles de
#  débuggages dans notre code. Cela permettra d'utiliser un débuggeur sur notre
#  code (le plus commun en C est gdb "GNU Debugger"). Sans cela le code sera
#  optimisé de telle sorte qu'il ne sera pas forcément possible pour le debugger
#  de dire à quelle ligne de code l'instruction courante du programme correspond.
#  Notez qu'un code avec symboles de débuggage est plus lent que le code optimisé.
#
#  -I : "Includes", doit contenir le chemin où le compilateur doit aller chercher
#  les fichiers headers de vos librairies (par exemple stdio.h etc...). Dans notre
#  cas nous pouvons nous en dispenser car les headers classiques se trouvent dans
#  un emplacement connu de votre compilateur (souvent /usr/include sous linux) et
#  nos headers pile.h et calculatrice.h sont trouvés dans le repertoire courant
#  grâce à la syntaxe include "pile.h".
#
#  -L : "Librairies", doit contenir le chemin où le compilateur doit trouver
#  toutes les librairies dont il a besoin pour compiler votre code. La syntaxe est
#  la même que pour -I, dans le cas présenté ici -L ./ signifie que les librairies
#  peuvent se trouver soit dans des emplacements standarts (/lib ou /usr/lib par
#  exemple) soit dans le repertoire courant (./).
#
#  -lPile : Lorsque vous faites usage d'une librairie autre que la librairie
#  standart en C il faut dire au compilateur le nom de la librairie dont vous
#  avez besoin. La syntaxe -lPile signifie que la librairie dont nous aurons
#  besoin se nomme libPile (si elle s'appellait libfoo.so on aurait mis -lfoo).
#  Le compilateur va alors chercher la librairie nommé "libPile.so" dans tous les
#  emplacements qu'il connait (i.e. les emplacements classiques plus ceux que vous
#  avez passé avec -L). Sous windows on applique la même logique sauf que la
#  librairie est nommée "libPile.dll".

FLAGS_UNIX	:= -Wall -g -L ./ -lPile
FLAGS_WIN	:= -Wall -g -L ./ -lpile
OUTPUT_UNIX	:= calculatrice.elf
OUTPUT_WIN	:= calculatrice.exe

# La syntaxe d'une commande make est :
# <nom de la règle> : <dépendances>
# 	<commandes>
# Par exemple pour compiler la règle "calculatrice" il faut taper "make
# calculatrice.elf" dans la ligne de commande.
$(OUTPUT_UNIX) : $(SOURCES_UNIX) $(LIBRAIRIE_UNIX) $(HEADER)
	$(CC_UNIX) $(FLAGS_UNIX) $(SOURCES_UNIX) -o $(OUTPUT_UNIX)

# idem sous windows, où il faudrait taper "make calculatrice.exe".
$(OUTPUT_WIN) : $(SOURCES_WIN) $(LIBRAIRIE_WIN) $(HEADER)
	$(CC_WIN) $(FLAGS_WIN) $(SOURCES_WIN) -o $(OUTPUT_WIN)

# (NOTE) Dans le paragraphe qui suit j'ai abrégé les noms pour que le texte soit
# plus lisible, mais je ne pense pas que cela gènera votre compréhension.

# Vous remarquerez que "make calculatrice.elf" a besoin que la librairie pile
# ait déjà été compilée. Cela est géré automatiquement par make : en effet nous
# avons défini plus bas une règle permettant de compiler libPile.so et pile.h
# s'il ne sont pas déjà présents (celle qui commence par $(LIBRAIRIE)). Or dans
# les dépendances de notre règle $(OUTPUT) nous avons noté $(LIBRAIRIE), donc
# make comprend lorsque nous lançons "make calculatrice.elf" que si libPile.so
# et pile.h ne sont pas présents il doit les compiler lui-même.

# Pour compiler la librairie pile, rien de plus simple : on lance la commande
# "make lib" dans le dossier pile (c'est le sens de make -C pile) avec l'argument
# lib. Ce n'est pas visible ici, le makefile que l'on trouve dans le dossier pile
# contient une règle qui s'appelle lib et qui compile la librairie pile (et la
# copie dans le dossier calculatrice).
$(LIBRAIRIE_UNIX) :
	$(MAKE) -C pile liblinux

# idem sous windows
$(LIBRAIRIE_WIN) :
	"$(MAKE)" -C pile libwindows

linux: $(OUTPUT_UNIX)
	echo "Compilation de $(OUTPUT_UNIX) achevée."

windows: $(OUTPUT_WIN) 
	echo "Compilation de $(OUTPUT_WIN) achevée."
