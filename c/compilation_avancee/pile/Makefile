test : pile.c pile.h unit_test.c
# Pour tester les méthodes définies dans la librairie pile on commence par
# compiler notre librairie avec un main écrit dans un autre fichier (unit_test.c)
		cc -o unit_test.elf pile.c unit_test.c


lib : pile.c pile.h
#
#													La compilation - 4****
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
#	2 - La compilation à proprement parlé, pendant cette étape le compilateur va
#	parser et comprendre votre code, l'optimiser et renvoyer sa représentation en
#	assembleur (vous vous souvenez peut-être que dans le tutoriel sur les
#	pointeurs on montrait à la fin de comment voir ce code en assembleur).
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
