unit_test.elf : pile.c pile.h unit_test.c
# Pour tester les méthodes définies dans la librairie pile on commence par
# compiler notre librairie avec un main écrit dans un autre fichier (unit_test.c)
		cc -o unit_test.elf pile.c unit_test.c

unit_test.exe : pile.c pile.h unit_test.c
# Notez que nous n'utilisons pas les fichiers pile_w.c et pile_w.h, qui comprennent
# des décorateurs spécifiques utilisés seulement pour la compilation en une dll.
		clang.exe -o unit_test.exe pile.c unit_test.c

linux: unit_test.elf
	echo "Compilation de unit_test.elf achevée."

windows: unit_test.exe
	echo "Compilation de unit_test.exe achevée."

liblinux : pile.c pile.h
#
#				La compilation - 4****
#
# Pour compiler une librairie dynamique en C (c'est souvent ce dont vous avez
# besoin la plupart du temps) il faut passer par une représentation objet de
# notre code (le fichier pile.o).
#
# Notre première commande sert à créer le fichier objet pile.o. Cela est fait
# grâce à l'option -c de gcc qui signifie, si on regarde la documentation,
# "compile and assemble, but do not link". Je profite de cette occasion pour
# détailler un peu le fonctionnement du compilateur C. La compilation s'effectue
# classiquement en 4 étapes :
# 1 - D'abord le preprocess, pendant cette étape le préprocesseur résout toutes
# les instructions qui lui sont destinées, par exemple #include, #ifdef etc...
#
# 2 - La compilation à proprement parlé, pendant cette étape le compilateur va
# parser et comprendre votre code, l'optimiser et renvoyer sa représentation en
# assembleur (vous vous souvenez peut-être que dans le tutoriel sur les
# pointeurs on montrait à la fin de comment voir ce code en assembleur).
#
# 3 - Suit l'assemblage du code, pendant lequel l'assembleur va traduire le code
# assembleur "lisible par un humain" en sa représentation machine, stockée dans
# un fichier objet. Dans l'absolu ce code objet est tout à fait executable par
# un processeur, et par exemple si vous travaillez sur un microprocesseur en
# bare-metal (i.e. sans OS) et que vous lui donnez ce fichier objet au démarrage
# il l'exécutera comme vous pourriez vous y attendre (il est aussi possible de
# booter un PC vers du code objet sur une clef USB mais je ne vais pas m'étendre
# sur ce sujet). Cependant pour que ce code objet fonctionne, il faut deux choses
# en pratique assez rarement réunies : votre code doit n'avoir aucune dépendance
# dynamique (donc si on utilise des librairies il faut les compiler avec notre
# code, ce qui est rare en pratique) et beaucoup plus rare encore il faut que
# notre code objet soit envoyé directement au processeur sans intermédiaire. Or
# votre OS ne vous laissera jamais faire cela, donc la seule façon d'avoir un
# exécutable dans ~100% des cas est d'aller jusqu'à la 4ème étape.
#
# 4 - L'édition de liens du code (en anglais linkage). Pendant cette étape le
# linker va habiller votre code d'informations destinées à votre OS comme : "J'ai
# besoin d'une librairie appellée stdio" ou, plus important encore, "Je suis un
# code executable". Une fois que l'OS aura reconnu votre fichier executable il va
# le passer au processeur par morceaux (pour que votre programme ne monopolise
# pas le temps de calcul du CPU...). Cette dernière étape est particulèrement
# complexe et hors du sujet, mais en gros c'est comme ça que cela fonctionne.
#
# Un détail important concernant ces différentes étapes est qu'elles ne sont pas
# faites par votre compilateur (souvent gcc ou clang) lui même, mais par d'autre
# petits programmes (pour gcc l'assembleur se nomme gas ou juste as comme
# "assembler", le linker se nomme ld, le compilateteur est gcc lui-même et pour
# le préprocesseur je n'en suis pas certain mais je crois que c'est gcc qui s'en
# occupe). En pratique vous n'interagissez qu'avec le processeur parce qu'il fait
# office d'interface et gère pour vous toutes les différentes étapes de la
# compilation, mais cela n'a historiquement pas toujours été le cas.
#
# Si vous regardez la documentation de votre processeur vous devriez trouver des
# informations sur comment passer des arguments au préprocesseur, au compilateur,
# à l'assembleur et au linker, et vous devriez aussi trouver dans la
# documentation comment ne faire que les n premières étapes de la compilation.
# Pour gcc par exemple l'option -c permet de ne faire que les 3 premières étapes
# de la compilation.

# On compile le code objet de notre librairie. Notez que pour povoir faire une
# librairie accessible dynamiquement il faut passer l'option -fPIC, qui signifie
# Position Independant Code, c'est à dire (pour faire court) que la librairie se
# compoertera bien si on la charge en mémoire à l'improviste. Le -Wall signifie
# Warnings All mais contrairement à ce que l'on pourrait penser il n'active
# pas tous les warnings, juste beaucoup d'entre eux. Souvent un warning renvoyé
# par gcc avec -Wall est en fait une erreur de code.
		cc -g -c -Wall -fPIC pile.c

# Ici on convertit le code objet généré précedemment en une librairie nommée
# libPile.so. Notez que la librairie a aussi besoin de savoir comment elle se
# nomme, d'où le -soname ("shared objet name"). Remarquez que pour pas mal
# d'options de gcc qui prennent des arguments complexes, on doit séparer ces
# arguments par des ',' et pas des ' ', sinon gcc aurait du mal à savoir si vous
# essayez de passer un argument à une option ou si vous êtes en train d'utiliser
# une nouvelle option.
		cc -g -shared -Wl,-soname,libPile.so -o libPile.so pile.o

# Pour une raison qui m'échappe, gcc déclare les librairies dynamiques qu'il
# créé (shared objects) comme exécutables alors qu'elles ne le sont pas, donc
# j'enlève cela.
		chmod -x libPile.so

# Pour la suite du tutoriel on copie la librairie produite et son fichier header
# dans le dossier parent.
		cp libPile.so pile.h ../

# 
#			Librairies dynamiques et dll - 3***
#
# Créer une dll sous windows n'est pas très complexe, # en revanche par rapport
# à UNIX vous devez en plus créer une librairie statique (.lib) qui permettra à
# votre code de savoir comment utiliser les fonctions définies dans votre dll.
# Ce wrapper peut être généré automatiquement par clang, (même si cela n'est pas
# mentionné dans la documentation) en ajoutant les bons décorateur (montrés dans
# pile_w.h) à vos fonctions.
#
# Pour explique cette diférence, je dois rapidement expliquer comment fonctionnent
# les librairies dynamiques en C. Je ne suis pas un expert et le sujet est assez
# compliqué, mais en gros dans une librairie en C vous trouverez au moins deux
# parties : une table de symbole et le corps de la librairie.
#
# Le corps de la librairie contient l'implémentation de vos fonctions, c'est à dire
# le code en binaire à exécuter pour utiliser les fonctions.
#
# La table des symboles contient une liste de tuples décrivant vos fonctions. Dans
# ces tuples vous trouverez au moins le nom de la fonction en question et l'adresse
# dans le corps de la librairie où l'implémentation de la fonction se trouve.
#
# Ainsi, lorsqu'un exécutable souhaite utiliser une fonction définie dans une
# librairie dynamique, il lui suffit de regarder dans la table des symboles à quelle
# adresse se trouve la fonction en question puis il peut la charger. Les choses sont
# évidemment plus complexes en pratiques, mais c'est tout ce que nous avons besoin
# de savoir pour l'instant.
#
# Sachant tout cela, la différence principale entre Windows et UNIX est que :
# - Sous UNIX, par défaut les fonctions définies dans la librairie (dans les .c
#   et .h) SONT AJOUTEES à la table des symboles de la librairie dynamique obtenue.
# - Sous Windows, par défaut les fonctions définies dans la librairie NE SONT PAS
#   AJOUTEES à la table des symboles de la librairie dynamique obtenue.
#
# En ommettant mon avis personnel sur la question, cela signifie que sous Windows
# vous devez explicitement marquer les fonctions que vous souhaitez exporter dans
# la table des symboles de votre libraire dynamique. Cela se fait en précédant la
# définition de votre fonction par un __declspec(dllexport).
#
# Une autre différence importante est la façon dont les librairies dynamiques sont
# cherchées au moment de l'exécution. UNIX utilise un outil nommé ld qui ira chercher
# votre librairie dynamique au moment de l'exécution (voire run.sh dans le dossier
# parent). Au contraire Windows va créer au moment où vous compilez votre dll une
# librairie statique (.lib) qui va se charger "d'enrober" (to wrap en anglais) les
# appels à votre dll.
#
# Ce sont deux approches qui ont chacune leurs avantages et leurs inconvénients, il
# est juste important de savoir que les deux OS ont des approches différentes.
libwindows: pile_w.c pile_w.h
	# Comme sous UNIX on commence par créer un fichier objet.
	clang.exe -c -o pile.o pile_w.c
	# On édite les liens de notre fichier objet pour en faire un dll.
	# Vous remarquerez à la compilation que clang va automatiquement
	# générer des fichiers .lib et .exp . En fait le compilateur
	# détecte le décorateur que nous avons utilisé. C'est une bonne idée
	# dans le fond, mais ce qui m'a fait perdre des heures ici est que
	# si vous ne mettez pas les décorateurs dans votre code source clang
	# ne va pas mentionner ces fichiers .lib et .exp dont vous avez
	# besoin, et donc vous n'avez aucun moyen de savoir que clang peut
	# vous les fournir.
	clang.exe -shared -o pile.dll pile.o
	# Remarquez que le header que nous exportons est celui sans les
	# décorateurs, qui sont utiles uniquement au moment de la création de
	# la dll, le reste du temps ils sont plutôt génants.
	cp pile.dll pile.lib pile.h ../

clean:
	# Suppression des fichiers Windows
	rm -f pile.o pile.dll pile.exp pile.lib unit_test.exe
	# Suppression des fichiers UNIX
	rm -f pile.o libPile.so unit_test.elf
