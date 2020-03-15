#                                Contenu

Ce fichier explique brièvement comment mettre en place un environnement de
développement en C et liste les outils les plus courants en lien avec le C.

## IMPORTANT:

Le gros de ce tutoriel a été écrit pour linux, et les Makefile ont été faits en
partant du principe que vous utilisez gcc. Si vous souhaitez utiliser un autre
OS ou compilateur vous devrez adapter les Makefile ou bien modifier le code
(dans le cas où vous seriez sous Windows ou MacOS).

# 1 - IDE ou éditeur de code ?

Afin de pouvoir travailler en C, le premier choix que vous devez faire est :
vais-je utiliser un éditeur de code, qui servira juste à surligner et écrire
mon code avec quelques raccourcis pratiques ? Ou vais-je plutôt utiliser
une IDE ("Integrated developement environnment") qui va gérer pour moi l'édition
du code, la compilation et le débuggage ?

Pour le bien-être de votre santé mentale je vous reccomande globalement
d'utiliser un éditeur de code avec un compilateur en ligne de commande. Cela
peut sembler austère au début, mais le problème des IDE est que vous ne pouvez
pas tout faire depuis un interface graphique, et si vous êtes habitués à vous
appuyer sur un IDE vous avez toutes les chances qu'un jour où vous vous lancerez
dans un projet plus complexe votre IDE finisse par échouer avec un ravissant
message du goût de "dependancy make build failed, toolchain clang-armv7 is not
available" sans que vous n'ayez aucune idée du sens de ce message. Et alors
retour à la case départ et vous devrez quand même apprendre à travailler en
ligne de commande. Donc faites vous une faveur et utilisez les outils en ligne
de commande.

Quelque soit votre choix je vous fais tout de même des recommendations
d'éditeurs de code et d'IDE.

# 2 - IDE

N'utilisant moi-même pas d'IDE j'ai quelques difficultés à vous en recommander,
toutefois pour rester dans les sentiers battus :

 - eclipse : Si vous avez déjà utilisé des IDE propriétaires vous avez sans
 doute remarqués qu'ils se ressemblent tous un peu. C'est parce que la plupart
 sont basés sur le projet open-source eclipse. Je trouve personnelement cet IDE
 un peu laid, mais au moins il est fonctionnel et en le choissisant vous ne
 pouvez pas faire fausse route (parmi les IDE en tous cas).

 - Visual Studio (Windows uniquement) : Un IDE que j'ai moi-même beaucoup
 utilisé jusqu'à en atteindre les limites et abandonner complètement les IDE.
 Microsoft voulais faire de Visual Studio le meilleur IDE du marché, et ils y
 sont probablement arrivés (non pas que la barre soit bien haute par ailleurs).
 L'IDE est agréable à utiliser et vous trouverez beaucoup de ressources en
 ligne si vous avez une question sur son utilisation. Attention cependant à
 n'installer que les modules qui vous intéressent, Visual Studio peut rapidement
 devenir très gourmand en espace disque (~100GB pour une installation de tous
 les modules possibles). Visual Studio n'est pas open-source.

Il existe beaucoup d'autres IDE sur le marché, faites vos recherches si vous
voulez en utiliser un. Encore une fois je vous recommande de plutôt utiliser la
ligne de commande, mais vous êtes libres de faire ce que vous voulez.

# 3 - Editeurs de code

Même si j'ai recommandé l'usage d'éditeurs de code en général, il m'est
difficile de vous en recommander un en particulier parce que la plupart sont
finalement assez décevants. Je ne vais pas les décrire en détail car je n'ai
rien d'interessant (ou plutôt rien qui ne soit politisé) à dire dessus, je me
contente de lister leurs noms pour que vous puissiez en un qui vous plaise sur
internet (l'ordre est un peu arbitraire):

 - Visual Studio Code;
 - Atom;
 - Sublime Text;
 - Notepad++;
 - GNU Emacs;
 - evim ou gvim (interface graphique de vim)

Faites vous votre opinion, mais vous vous rendrez vite compte qu'il est facile
de passer de l'un à l'autre sans grande difficulté contrairement aux IDE, donc
vous ne vous enfermez pas en faisant un choix plutôt qu'un autre.

# 4 - Compilateur

Pour travailler en ligne de commande, le premier outil dont vous aurez besoin
est évidemment un compilateur. En effet le C est un langage compilé, c'est à
dire que votre code sera compilé en un fichier exécutable que vous pourrez par
la suite exécuter. Il existe plusieurs compilateurs C mais les deux principaux
sont de loin :

 - gcc ("Gnu C Collection") : le compilateur C utilisé massivement dans le monde
 de l'open-source. Il s'agit sans doute de l'un des projets les plus importants
 du mouvement GNU, et également l'un de ceux qui aura eu le plus de succès.
 gcc est n'est pas seulement le compilateur le plus utilisé, il incarne
 également l'archétype du compilateur obscur. Peu de gens savent vraiment
 comment fonctionne gcc, mais si vous lui passez en entrée un code simple
 utilisant des additions d'entiers, il est probable que gcc trouve des
 optimisations plus ou moins exotiques pour finalement produire un executable
 absolument incompréhensible utilisant surtout des shifts, mais qui étonnament
 fera exactement la même chose que ce que vous aviez écrit. Les executables
 produits par gcc sont extrèmement compacts et optimisés, et la vitesse de
 compilation de gcc est encore aujourd'hui imbattable.
 Pour installer gcc sous linux je vous recommande d'utiliser le package manager
 de votre choix, par exemple sous debian "sudo apt install gcc".

 - clang : Depuis bien des années l'industrie cherche à remplacer le C (qui date
 de 1972!) par un langage plus moderne, et pour accélerer cette émergence
 plusieurs gros acteurs (avec Apple en tête de file) se sont réunis derrière un
 projet pour créer une architecture de compilation réutilisable nommée LLVM.
 Pour démontrer l'efficacité de LLVM, mais aussi pour fournir une alternative au
 toujours plus obscur gcc, le projet LLVM a été utilisé pour créer un
 compilateur C nommé clang. clang est également très performant dans ses
 optimisations de code et ses temps de compilation même s'il n'égale pas gcc.
 Sous debian, vous pouvez installer clang avec "sudo apt install clang". Pour
 installer clang sous Windows, vous pouvez le télécharger depuis
 https://releases.llvm.org/9.0.0/LLVM-9.0.0-win64.exe . Attention, pour pouvoir
 utiliser clang depuis la ligne de commande, vous devez ajouter clang au PATH de
 windows. Je vais avoir du mal à vous expliquer comment faire avec du texte, je
 vous conseille de regarder des vidéos sur Youtube pour voir comment on fait
 cela. C'est l'une des étapes pénibles sous Windows, et vous aurez besoin de le
 faire plusieurs fois ici. Pour vous aider un peu, sur ma machine le chemin que
 j'ai du ajouter au path est : "C:/Program Files/LLVM/bin".

 - msvc : Sous Windows seulement, "Microsoft Visual C", il s'agit du compilateur
 C utilisé utilisé en interne par Visual Studio. Je le met ici seulement pour
 votre culture, même si vous essayiez de l'utiliser en ligne de commande vous
 n'y arriveriez probablement pas.

Suivant la plateforme sur laquelle vous travaillez l'un ou l'autre pourra être
un meilleur choix :

 - sous linux je vous recommande gcc car il est plus couramment utilisé, mais
 clang est aussi une option valable;

 - sous windows clang est plus facile et naturel à utiliser, si pour une raison
 quelconque vous voulez utiliser gcc il vous faudra passer par MinGW;

 - sous OSX (i.e. Mac) je vous recommande plutôt clang même si je n'ai jamais eu
 l'occasion de développer sous Mac.

Dans tous les tutoriels :
 - Si vous êtes sous Linux je suppose que vous utilisez gcc ou clang.
 - Si vous êtes sous Windows je suppose que vous utilisez clang.
 - Si vous êtes sous Mac je suppose que vous saurez vous débrouiller seul ;-)

# 5 - make

Souvent pour compiler vos projets vous ne voudrez pas réécrire toutes vos lignes
de compilation à la main, pour cela je vous recommande l'omniprésent make s'il
est disponible sur votre plateforme. make peut auss trouver seul comment
compiler des projets simples en C, et son usage sera détaillé pendant les
tutoriels.

<h3>IMPORTANT</h3>
Pour ceux qui suivent ce tutoriel sous Windows, je suppose que vous travaillez
en permanence depuis l'invite de commande de git (i.e. git bash). Si ce n'est
pas le cas certains Makefile (tous ?) risquent de mal se comporter.

Installer git (et git-bash) sous windows est assez facile, n'oubliez juste pas
de créer un raccourci vers git bash pour vous faire gagner du temps pour plus
tard. Vous pouvez sous windows télécharger git à l'adresse :
https://github.com/git-for-windows/git/releases/download/v2.25.1.windows.1/Git-2.25.1-64-bit.exe

Toujours sous Windows, vous pouvez télécharger make à l'adresse :
http://gnuwin32.sourceforge.net/downlinks/make.php
Cette adresse devrait vous rediriger vers SourceForge qui vous enverra
automatiquement le fichier de setup assez rapidement. Attention, comme pour
clang, vous devrez ajouter make à votre PATH pour pouvoir l'utiliser en ligne
de commande. Sur ma machine, le chemin à ajouter au PATH est :
"C:/Program Files (x86)/GnuWin32/bin"

Sous debian vous pouvez tout installer avec "sudo apt install make git".

# 6 - Debugger

En plus de cela vous aurez surement besoin d'outils de débuggages afin de
trouver les problèmes dans votre code. Les deux outils que je connais sont :

 - gdb ("GNU Debugger") : Un débuggeur assez ancien mais toujours solide. Il
 s'utilise en ligne de commande (vous pourrez trouver la documentation sur
 internet) et est souvent le débuggeur utilisé en interne par les IDE. gdb est
 suffisant pour la plupart des problèmes que vous rencontrerez.

 - lldb : Version LLVM de gdb, l'usage est à peu près le même mais je trouve
 personnelement que lldb est un peu plus agréable que gdb.

 - valgrind : Un outil de debuggage en ligne de commande, je n'en ai jamais eu
 l'usage mais il est apparement très puissant.

Vous ne devriez pas avoir besoin de debugger pour ce tutoriel, mais sous windows
normallement si vous avez installé clang correctement vous devriez avoir accès à
lldb directement. Pour tester cela vous pouvez utiliser "lldb.exe -v" dans la
ligne de commande

Vous êtes maintenant prêts à suivre le tutoriel :-)
