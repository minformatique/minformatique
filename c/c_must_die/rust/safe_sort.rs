/*
Ce fichier fait partie de l'épilogue du tutoriel sur le C et parle du langage
Rust. Le but de ce petit tutoriel est de mettre en évidence la philosophie du
Rust et de monntrer en quoi elle se distingue de celle du C.

Pour compiler ce fichier vous pouvez utiliser le Makefile fourni mais attention,
Rust a son propore compilateur nommé rustc dont vous aurez besoin pour compiler
ce fichier. Vous pouvez obtenir le compilateur Rust soit seul soit avec cargo
ou rustup sur le site de Rust https://rust-lang.com

Contributeurs : Rezal P18
*/

/*

							Qu'est ce que Rust ? - 1*

Rust est un langage moderne apparu en 2010 et qui a connu beaucoup de succès
depuis sa sortie (le langage a notamment été pendant plusieurs années le langage
le plus aimé sur Stack Overflow). Mais la popularité du Rust est-elle une effet
de mode, ou bien ce langage est-il une alternative viable au C/C++ ?

Pour répondre à cela quelques éléments de contexte s'imposent. Rust est un
projet initié par la compagnie Mozilla, une société de l'open-source très connue
pour son navigateur Mozilla Firefox. La compagnie bénéficie d'une certaine aura
dans le monde de l'open-source pour son engagement et sans doute cela a été l'un
des éléments qui ont contribués à populariser le Rust auprès de la communauté.
Mais pour qu'un langage rencontre du succès il ne suffit pas qu'il parte d'une
bonne idée ou de personnes célèbres; beaucoup de langages apparaissent et
disparaissent aussitôt parce qu'il ne parviennent pas à trouver une niche dans
laquelle les compagnies seront prêtes à payer des développeurs utilisant ce
langage. Dans le cas du langage de Mozilla le premier client est ... Mozilla
elle même. Quoique petite en comparaison avec les GAFAM qui utilisent de la même
façon leur propre poids pour porter leurs initiatives, Mozilla est détentrice
d'un des projets open-source les plus grands en terme de taille du code, de
temps de compilation, de complexité de fonctionnement et de visibilité (le
navigateur Firefox). En décidant de réécrire Firefox (et le projet Servo
également) en Rust, Mozilla a offert à son langage une niche stable sur le long
terme pour prospérer. Aujourd'hui Rust ne se limite plus à cette niche et
commence à apparaitre dans des champs d'application différents (systèmes
embarqués, applications et système d'exploitation).

Un autre élément plus technique à savoir sur Rust est que le langage s'appuie
sur l'outil LLVM. Sans rentrer dans le détail, cela permet au Rust de pouvoir
être compilé ou interprété sur des architectures très diverses sans que Mozilla
n'ait à réécrire son compilateur à chaque fois. Cela permet au Rust de bénéficier
au grand jour d'innvotions qui auront été travaillées dans l'ombre pendant des
années pour le projet LLVM (aux frais d'Apple).

Le Rust a donc été conçu dans un contexte assez favorable, mais pour bien cerner
les choix entourant le langage il nous reste un dernier élément à aborder :
pourquoi Mozilla a choisi de créer le Rust ?

Lorsque j'ai abordé le C++, j'ai dit qu'il était facilement mis en défaut par le
C pour la programmation de bas niveau et par Java pour l'écriture d'applications.
Mais il existe bien un entre deux dans lequel se trouvent pas mal de projets :
trop gros pour être raisonnablement écrits en C sans une myriade de bugs, mais
pour lesquels Java ne serait pas adapté. Quelques exemples :

 - Les projets d'IOT (Internet Of Things), qui peuvent être vu comme des gros
 systèmes embarqués dans lesquels on a souvent besoin de faire intervenir des
 algorithmes abstraits, notamment de l'intelligence artificielle. Il sont trop
 gros pour être écrits en C mais ne peuvent pas utiliser Java (ou un équivalent)
 car les runtime de ces langages ont presque toujours besoin d'un système
 d'exploitation (qui ne sera pas forcément présent sur un projet d'IOT).

 - Les runtimes eux-mêmes. Leur nom technique est machine virtuelle, mais je les
 appele runtime dans les tutoriels pour éviter les confusions avec la
 virtualisation de système d'exploitation que l'on appelle aussi couramment
 machine virtuelles (note : le nom JVM signifie d'ailleurs Java Virtual Machine,
 et l'acronyme LLVM signifiait à l'origine du projet Low-Level Virtual Machine).
 Pour des raisons pratiques (entre autres de performance) les runtimes sont
 presque toujours compilés statiquement et ne peuvent pas s'appuyer sur un autre
 runtime pendant leur execution. Mais leur code source est souvent vaste et
 complexe et tout écrire en C serait cauchemardesque. Notez que les navigateurs
 web ont des composants qui peuvent être vus comme des runtime (notamment ceux
 qui s'occupent du rendu des pages web et de l'exécution du Javascript).

 - Les systèmes d'exploitation, quoique peu nombreux, sont également des projets
 qu'il est laborieux d'écrire en C mais qu'il n'est pas possible de faire
 fonctionner au dessus d'un runtime. Pour vous donner quelques éléments
 culturels le noyau de Windows (Windows NT) est écrit surtout en C, mais le reste
 du système d'exploitation serait écrit plutôt en C++ (difficile à dire dans la
 mesure où le code n'est pas public); le noyau d'OSX est basé sur BSD donc écrit
 en C mais le gros de l'OS est plutôt en Objective-C (une variante du C avec des
 objets assez peu utilisée en dehors de OSX) mais une fois encore le code n'est
 pas disponible; le noyau de Linux (Linux au sens propre) est écrit en C et pour
 des raisons surtout idéologiques les distributions GNU/Linux sont elles aussi
 surtout écrites en C. Pour vous donner un ordre de grandeur, le noyau de Linux
 fait plus de 15 millions de lignes de code (mais tout le code n'est pas compilé
 en même temps). Notez cependant que le système d'exploitation le plus répandu
 n'est aucun de ces trois mastodontes, il s'agit d'Android dont le noyau est
 Linux (donc écrit en C) mais le gros de l'OS a été écrit en Java en utilisant
 un runtime particulier écrit par Google.

Le marché pour un langage capable de plus d'abstraction que le C tout en étant
compilé statiquement existe donc bien. Or comme je l'ai détaillé dans le
tutoriel dédié le C++, quoique très intéressant et innovant par rapport au C,
a son lot de défauts qui poussent à chercher des alternatives.

Maintenant que nous avons vu le contexte qui a motivé l'apparition voyons les
choix que les developpeurs de chez Mozilla ont faits pour apporter une meilleure
abstraction que le C sans être une copie sans âme du C++.
*/

/*
Une première différence à noter en Rust par rapport au C/C++ est l'absence de
header, qui sont complétement éclipsés au profit d'espaces de noms.
*/
use std::cmp::Ordering;
use std::io;
use std::fmt;
use std::vec::Vec;

/*

                        A quoi bon l'orienté objet ? - 1*

Contrairement à a peu près tous les langages récents, le Rust n'est pas orienté
objet. Il n'y a pas d'objets en Rust et par conséquent pas d'héritage. Au lieu
de cela Rust utilise des structs qui rappellent les structs du C. Cependant les
structs du Rust on deux différences majeures avec celles du C :

 - Les structs du Rust peuvent contenir de vraies méthodes qui agissent qui
 agissent sur l'objet lui-même.

 - Le Rust dispose d'un mécanisme d'inversion d'inversion de dépendance grâce
 aux traits (les mêmes que dans "trait de caractère"). Certainement inspirés des
 interfaces de Java, les traits en Rust décrivent un caractéristique associée à
 une structure, par exemple le trait Ord signifie que deux éléments d'une
 structure qui dérive Ord peuvent être comparés. Vous pouvez ainsi écrire des
 méthodes qui fonctionnent sur n'importe quelle structure implémentant un trait
 donné sans avoir à vous soucier de l'implémentation particulière. Notez que la
 façon dont les traits sont implémentés en Rust est fortement inspiré des
 templates du C++.

Pourquoi avoir fait cela ? Même si cela peut sembler difficile à voir, ces choix
font que le code que vous écrivez en Rust, même s'il est plus abstrait que ce
que vous feriez en C, reste plus proche de la machine et donc plus simple à
compiler que ce que vous feriez avec des objets en C++. Pourtant je peux vous
dire que si vous comparer les temps de compilation des trois langages, le Rust
est plus lent que le C++ qui est lui même sensiblement plus lent que le C en
temps de compilation. L'explication grossière est que si le Rust effectue en
principe des opérations qui sont proches de la machine et faciles à traduire,
la façon dont elles sont traduites est non triviale. Contrairement à ses
équivalents du C/C++, le Rust s'appuie sur la phase de compilation pour
effectuer de nombreuses opérations non triviales dont notamment des
vérifications plus ou moins complexes de votre code.

Notez que le Rust fournit aussi le mécanisme Deref qui aurait pu nous servir
ici mais je préfère faire autrement pour pouvoir détailler des choses plus
intéressantes.
*/
struct Mot {
    contenu : String,
}

/*

                                    Traits - 1*

Il existe plusieurs syntaxes pour dériver des traits en Rust. Pour le type Mot
dans la mesure où j'aurai besoin de trier les mots et donc de les comparer avec
un ordre total la documentation me dit que j'ai besoin de 4 traits : PartialEq
(égalité partielle), Eq (égalité totale), PartialOrd (ordre partiel), Ord (ordre
total).

La syntaxe la plus simple pour dériver un trait est de définir un bloc
d'implémentation. Comme vous l'avez constaté mon bloc struct ne contient pas de
méthodes, car celles çi doivent être placées comme les implémentation de traits
dans des blocs d'implémentation.

Ici on signale que notre structure Mot implémente le trait Eq, ce qui signifie
qu'une instance de mot est égale à elle même. Cela n'est pas le cas pour le type
float par exemple (à cause de NaN). La syntaxe se lit comme elle s'écrit : on
implémente le trait Eq pour le type Mot.
*/
impl Eq for Mot { }

/*
Ici on dérive le trait PartialEq qui permet de dire si deux instances
différentes de notre structure sont égales.
*/
impl PartialEq for Mot {
    /*

                                La bonne idée - 1*

    Pour déclarer une méthode en Rust (ici une méthode qui porte sur le type
    Mot puisque l'on se trouve dans un bloc d'implémentation qui concerne le
    type mot) la syntaxe à utiliser est présentée çi dessous.

    La première que vous pouvez vous faire est que cette syntaxe n'est pas la
    même qu'en C. Et oui, le Rust a l'immense avantage de n'être pas
    rétrocompatible avec le C mais d'utiliser une syntaxe différente pour une
    application différente. Dans la déclaration de la méthode :
        - fn signifie fonction et signale juste que ce qui suit est une
        fonction;
        - eq est le nom de la méthode (le nom est dicté par le trait PartialEq,
        vous trouverez cette information dans la documentation en ligne).
        - &self signifie que cette fonction est une méthode qui va s'appliquer à
        un objet donné, par exemple si on a un mot a et un mot b on écrira
        a.eq(b) et alors self vaudra a.
        - other : &Mot décrit un argument de la méthode. Ici l'argument se nomme
        other et son type est donné après le ':', il s'agit d'un &Mot. Notez qu'à
        l'exception du &self (qui est déduit par le compilateur qui sait que nous
        nous trouvons dans un bloc qui concerne le type Mot), il est toujours
        nécessaire de donner le type d'un argument dans une fonction en Rust.
        - -> bool signifie juste que notre fonction va renvoyer un booléen. Notez
        que si votre fonction ne renvoie rien cet appendice peut être omis.
    */
    fn eq(&self, other : &Mot) -> bool {
        /*
        La méthode en elle même n'est pas très complexe. Notez cependant que le
        return à la fin du fonction peut être omis si la valeur renvoiée se
        trouve sur la dernière ligne de la fonction et que l'on ne met pas de
        ';' à la fin de la ligne, une convention empruntée à d'autres langages
        que l'on retrouve beaucoup en Rust.
        */
        // return self.contenu == other.contenu;
        self.contenu == other.contenu
    }
}


/*

                Au revoir pointeur, bonjour référence - 1*

Je ne l'ai pas détaillé plus haut, mais le & dans &self et &Mot (de la méthode
eq) n'est pas là pour décorer, il s'agit du symbole référence. En Rust, on
n'utilise jamais des pointeurs directement, au lieu de cela le langage propose
un système de référence. Notez que ces références seront en réalité juste
traduits par des pointeurs, mais contrairement aux pointeurs du C les références
du Rust sont safe, c'est à dire que derrière un &Mot vous trouverez toujours
un mot initialisé. Vous ne pouvez pas écrire autre chose à la place et vous ne
pouvez pas accéder aux espaces mémoire derrière le Mot. C'est une référence vers
un mot et le Rust ne vous laissera pas l'utiliser autrement.

L'immense avantage de ces références sur les pointeurs est que dans la mesure
où seules les manipulations jugées comme censées sur ces références sont
autorisées, vous ne pouvez pas avoir de segmentation fault. De même, vous ne
pouvez pas avoir d'états indéfinis en manipulant des références puisque si vous
essayez de faire une manipulation non autorisée sur la référence soit le
compilateur vous renverra une erreur, soit vous aurez une erreur à l'exécution.

Notez également que contrairement au C et au C++ il n'y a pas d'opérateur de
déréférence en Rust, le langage dispose pour plus de lisibilité d'un mécanisme
de déréférence automatique donc vous n'avez que la syntaxe instance.methode à
utiliser. L'opérateur de déréférence * existe bel et bien en Rust et il
fonctionne comme on pourrait s'y attendre sur les références, mais il est plus
rarement utilisé puisque l'on n'en a pas besoin pour les appels de méthode.
Notez enfin que lorsque vous l'utilisez dans votre code l'opérateur & se
comporte d'un façon qui rappelle ce que faisait addressof en C (aussi noté &)
mais avec des fonctionnalités en plus pour éviter des bugs lorsque vous faites
de la programmation concurrente.
*/

impl PartialOrd for Mot {
    /*

                                Null - 2**

    Si vous regardez le type de renvoi de la méthode qui suit vous verrez qu'il
    s'agit d'un Option<Ordering>. Ordering est simplement un enum qui peut
    prendre des valeurs signifiant "moins que", "égal à" et "plus que" i.e. le
    résultat de notre comparaison.

    Le type Option est également un enum mais il joue un rôle particulier en
    Rust. Notez que les enum en Rust ont une définition plus large qu'en C, je
    détaillerai cela plus tard. Pour comprendre cet enum il nous faut un peu
    parler du Null de Java (et équivalents).

    La plupart des langages orienté objets comportent une valeur (souvent nommée
    Null) qui correspond en fait à une absence de résultat et tous les types
    peuvent prendre la valeur Null. Il s'agit d'une façon simple à implémenter
    de gérer les situations où un variable n'a pas de valeur, commme c'est le
    cas dans un ordre partiel si on compare deux objets qui ne sont pas
    comparables. Mais si je vous en parle vous vous doutez bien que ce choix
    n'est pas sans défauts.

    Le principal problème avec le type Null est qu'il n'y a pas de moyen de
    savoir si une variable passée en argument ou renvoyée par une fonction est
    nulle. Il faudrait donc vérifier avant de l'utiliser si elle est nulle, mais
    en pratique cela n'est pas toujours rigoureusement fait et l'utilisation
    d'une variable nulle comme si elle était non nulle est l'une des erreurs les
    plus fréquentes en programmation de haut niveau (le créateur du Null Tony
    Hoare a d'ailleurs urnommé l'invention du Null son erreur à un milliard de
    dollards).

    Pour éviter ce problème le Rust utilise un système qui rappelle les codes
    d'erreur du C (l'int que vous devez renvoyer de presque toutes vos fonctions
    sous peine de rapidement faire n'importe quoi) : au lieu de vous renvoyer
    soit le bon résultat, le Rust vous envoie un enum dont la valeur est soit ce
    que vous cherchez, soit None. Jusqu'ici vous n'avez peut-être pas
    l'impression que nous avons beaucoup avancé, mais en pratique cela va
    permettre un tour de force au Rust : il n'y a pas d'équivalent à Null en
    Rust, ce qui signifie que si vous récupérez un Ordering (par exemple) d'une
    fonction, vous savez que cet Ordering est bien défini et vous n'avez pas à
    vérifier qu'il est non nul.

    Si jamais une fonction souhaite renvoyer un null, alors elle devra passer
    par l'enum Option (ou un équivalent) pour vous renvoyer soit votre résultat
    soit None. Lorsque vous récupérez ce résultat la syntaxe du Rust vous
    forcera à vérifier que la valeur que vous avez obtenue n'est pas None, et si
    tout est bon vous récupérerez votre valeur avec le type qu'il faut (Ordering
    par exemple) et vous pourrez ensuite l'utiliser librement sans avoir à vous
    poser de questions.

    Notez qu'utiliser une variable nulle comme si elle était initialisée ne
    créerait pas un état indéfini, donc ce n'est pas si grave non plus, mais ici
    le Rust vous fournit une syntaxe pratique pour éradiquer complètement ce bug
    trop courant. Je vous montrerait dans une autre méthode comment utiliser
    cette syntaxe plus en détail.
    */
    fn partial_cmp(&self, other : &Mot) -> Option<Ordering> {
        self.contenu.partial_cmp(&other.contenu)
    }
}


/*
On définit içi l'ordre complet sur nos mots. Notez que comme deux éléments sont
forcéments comparables dans un ordre complet la méthode cmp ne renvoie pas
Option<Ordering> mais directement Ordering.
*/
impl Ord for Mot {
    fn cmp(&self, other : &Mot) -> Ordering {
        self.contenu.cmp(&other.contenu)
    }
}

/*
On implémente aussi le trait Display (de l'espace de nom "format") pour pouvoir
afficher nos mots facilement. La syntaxe de cette méthode peut vous sembler
un peu mystérieuse mais on la trouve dans la documentation du langage.
*/
impl fmt::Display for Mot {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.contenu)
    }
}

/*

                                Safe Rust - 1*

Vous commencez sans doute à le remarquer mais le Rust a une philosophie
diamétralement opposée à celle du C. Là où le C privilégiait la simplicité
d'écriture et la liberté du developpeur, le Rust est un langage qui se veut
aussi sur que possible. D'ailleurs si vous cherchez des informations sur le Rust
sur internet c'est probablement la première chose que vous lirez. Mais qu'est ce
cela signifie précisément ?

La sécurité du Rust s'axe essentiellement autour de deux aspects. Le premier (et
celui auquel les gens pensent le plus couramment) est la sécurité par rapport à
un langage comme Java : le Rust met à disposition un syntaxe qui facilite les
bonnes pratiques et décourage les mauvaises. C'est par exemple le but poursuivi
lorsque le Rust décide de ne pas mettre de type Null dans sa syntaxe. Cet aspect
est celui qui vaut à Rust une partie des critiques de ses détracteurs, notamment
le fait que le langage ait une syntaxe étouffante et qu'il soit paranoïaque. Si
je ne suis personnellement pas d'accord avec le premier il faut admettre que la
seconde critique n'est pas injustifiée.

Cependant ce jugement me semble fortement biaisé et est probablement formulé par
des developpeurs habitués à des langages de haut-niveau comme Java ou Python qui
ont à juste titre des difficultés à justifier le fait de se forcer à suivre la
rigueur, toute assisté qu'elle soit, du Rust plutôt que d'écrire un programmme
en Java ou Python.

Si vous avez lu le tutoriel sur le C vous vous doutez probablement de ce qui
amené les ingénieurs de Mozilla à faire ce choix pour le Rust plutôt que d'être
un langage très libre comme Python. Il existe déjà un langage bas niveau avec
une philosophie assez proche de Python : le C (quoiqu'il serait
chronologiquement plus correct de dire que la philosophie de Python est la même
que celle du C). Et vous savez que la liberté et la programmation bas niveau
réunies amènent à un problème on ne peut plus génant : les états indéfinis.

Et ainsi le deuxième axe de la sécurité du Rust (et pour quelqu'un qui vient
du C ou C++ l'amélioration la plus notable) est que le Rust empèche les états
indéfinis. Contrairement à un programme écrit en C ou en C++, il n'est
simplement pas possible pour un code correct en Rust de générer des états
indéfinis.

Cette affirmation n'est en réalité pas tout à fait correcte, mais pour
pleinement comprendre pourquoi il faut introduire deux notions assez simples :
le Safe Rust et l'Unsafe Rust.

Un code écrit en Rust est par défaut Safe et doit respecter toutes syntaxes
rigoureuses du Rust. Mais il est également possible d'écrire du code dit unsafe
en Rust, qu'il faudra signaler au compilateur avec le mot clef unsafe. Le code
Rust unsafe permet notamment d'utiliser des pointeurs et d'accéder à des
mécanismes internes du langage, mais il a aussi d'autres utilités comme par
exemple d'utiliser des librairies écrites dans d'autres langages (C notamment)
qui sont considérées risquées par défaut. Je ne montrerait pas de code unsafe
dans ce tutoriel car vous n'en avez que très rarement besoin en pratique.

Toutefois on peut à juste titre se demander comment le Rust fait pour empècher
les états indéfinis ? Pour répondre à cette question, écrivons une classe pile
en Rust afin de pouvoir effectuer le même tri qu'en C++. Notez que comme le Rust
n'est pas rétrocompatible avec le C (ce qui est une bonne chose de toute
évidence) je ne peux pas réutiliser la classe pile que j'ai écrit en C ici. Pour
être plus précis je pourrais l'utiliser si je le voulais vraiment mais ce n'est
pas particulièrement une bonne idée donc je vais plutôt m'appuyer sur une type
de la librairie standard Rust : le type Vec.
*/

struct PileRust {
    /*
    Le type vecteur désigne un tableau dont la taille peut changer dynamiquement
    et est très utile pour définir des piles. Notez que même si je ne l'ai pas
    utilisé dans lle tutoriel dédié il en existe un équivalent dans la librairie
    standard du C++. Comme pour les tableaux il nous faut préciser ce que notre
    vecteur va contenir, ici ce sont des mots.
    */
    vecteur_interieur : Vec<Mot>,
}

/*
Ici aussi nous écrivons nos méthodes dans un bloc d'implémentation dédié.
*/
impl PileRust {
    /*
    Notez que contrairement aux objets en C++, les structs en Rust n'ont pas de
    constructeur à proprement parlé. En revanche dans la mesure où il n'est pas
    possible d'utiliser des objets non initialisés en Rust on sait que la valeur
    de vecteurInterieur aura déjà été initialisée au moment où on voudra
    l'utiliser dans nos méthodes (cela sera visible lorsque vous verrez la
    syntaxe utilisée pour déclarer une structure).
    */

    /*

                                Immutabilité - 1*

    Un choix qui distingue le Rust de la plupart des autres langages de
    programmation et en particulier du C et du C++ est que les variables y
    sont considérées immutables par défaut. Cela signifie que non seulement
    (comme nous l'avons déjà vu) le Rust ne vous laisse pas modifier les
    variables de votre code n'importe comment, mais en plus de cela si vous
    ne précisez pas qu'une de vos variables a besoin d'être changée le langage
    ne vous laissera pas la modifier du tout!

    Utiliser des variables immutables dans votre code a beaucoup de vertus en
    terme de réduction de bugs et de lisibilité du code. Cela vous pousse à
    respecter de bonnes pratiques de séparation des responsabilités dans votre
    code et une meilleure gestion des états. Cela permet aussi d'écrire des
    programmes qui pourront plus facilement être parallélisés.

    Notez qu'une variable immutable n'est pas constante, par exemple si la
    variable immutable locale var vaut 3 il est possible d'écrire dans notre
    code que var vaut à présent 4. Il n'est par contre pas correct d'écrire
    quelque chose comme var += 1; La différence est subtile sur des types
    primitifs mais devient assez clair lorsque l'on parle de structures. Il est
    possible d'allouer une nouvelle structure à une variable immutable, en
    revanche il n'est pas possible de changer les valeurs des attributs de la
    structure d'une variable immutable.
    */
    fn append(&mut self, nouveau_mot : Mot) {
        self.vecteur_interieur.push(nouveau_mot);
    }

    fn pop(&mut self) -> Option<Mot> {
        self.vecteur_interieur.pop()
    }

    /*
    En Safe Rust nous n'avons pas besoin d'un destructeur non plus puisque
    contrairement au C le Rust va à la compilation déterminer à quel moment il
    faut libérer la mémoire que nous avons réservée.
    */
}

/*

                            La sécurité du Safe Rust - 2**

Dans le code qui précède nous avons utilisé le type Vec, qui est un type qui
fait partie du Safe Rust. Par suite nous avons la garantie que ce type ne va
pas causer de comportements indéfinis. Mais comment cela est-il possible ?
Après tout notre programme finira par être traduit en assembleur comme le serait
un programme en C ou en C++, alors comment le Rust peut-il offrir ces garanties
alors que nous avons pu constater de première main qu'elles n'existent pas au
niveau de la machine ? Quelle implémentation mysterieuse les ingénieurs de
Mozilla ont'ils pu trouver pour le type Vec ?

Pour répondre à cette question, penchons nous davantage sur l'implémentation du
type Vec en Rust. Dans la documentation on trouve les phrases suivantes :

"Most fundamentally, Vec is and always will be a (pointer, capacity, length)
triplet. No more, No less."

hmmmmm...

"If a Vec has allocated memory, then the memory it points to is on the heap
[...] and its pointer points to len initialized, contiguous elements in order
[...] followed by capacity - len logically uninitialized, contiguous elements".

HHHHMMMMMM...

C'est exactement le même principe que notre type pile en C !!

En fait la notion de Safe Rust a un double sens. Certes les structures et
méthodes définies dans la librairie standard sont bien codées (encore heureux)
et offrent un maximum de filets pour l'utilisateur, et le fait de n'utiliser
les structures qu'à travers les méthodes fournies empêche effectivement les
états indéfinis que l'on rencontrerait en C ou en C++.

Mais en vérité le Safe Rust est davantage une zone de confiance qu'autre chose.
Il n'est pas dans l'absolu impossible pour le type Vec d'atteindre un état
indéfini, mais le Rust (et le developpeur avec lui) accorde sa confiance au
type Vec et supposera dans la suite que ce type ce comportera effectivement
toujours comme il le faut.

Sur le principe cela n'est pas différent de ce qui se fait dans les autres
langages : en python vous supposez que les multiplications numpy feront
effectivement une multiplication matricielle, en Java que votre système
d'exceptions se comportera bien comme prévu, et même en C vous supposez que
printf se comportera comme le format lui demande d'agir. La grande différence
dans le cas du Rust est que le langage lui même fournit deux niveaux de
confiance : le Safe et l'Unsafe. Vous pouvez avoir confiance dans une librairie
écrite en Unsafe Rust si vous le souhaitez.

Pour le Safe Rust en revanche la situation est différente. Ce n'est pas vous qui
décidez si un code est sûr ou non. D'ailleurs ce n'est même pas un humain qui
s'en charge, mais le compilateur lui-même. La démarche, sans nul doute inspirée
de langages de preuve, est que pour compiler votre programme comme un code sûr,
le compilateur Rust (rustc) doit prouver que votre programme mérite cette
confiance en vérifiant que votre code ne va pas causer d'états indéfinis et
restpecte les bonnes pratiques poussées par le langage.

Pour effectuer cette preuve, le compilateur dispose d'un outil très puissant :
la syntaxe du langage. Au lieu de vérifier logiquement que votre programme ne
fait pas n'importe quoi, le compilateur devra juste vérifier que votre code
respecte la syntaxe du Rust, parce que cette syntaxe a été pensée en amont (par
des humains cette fois-ci) pour respecter les règles que requiert le Safe Rust.

Cela me permet de souligner (encore, je sais...) et même cette fois de justifier
un point important : le fait d'être rétrocompatible avec le C n'est pas du tout
une qualité dans l'absolu pour un langage. Si le Rust avait été rétrocompatible
avec le C la preuve de confiance de votre programme n'aurait pas été possible
parce que la syntaxe même du C est source d'états indéfinis. Ce sont d'ailleurs
bien plus les syntaxes tirées du C que les manipulations orientées objet qui
vont créer des états indéfinis dans vos programmes en C++. Le C est un langage
qui se veut simple et sa syntaxe est très adaptée pour cela; le Rust est un
langage qui se veut sûr et sa syntaxe reflète cela. Que le C++ ait repris la
syntaxe du C pour un but complètement est pour moi le choix qui mine le plus un
langage qui a par ailleurs apporté beaucoup d'innovations.

Pour fermer cette disgression sur le Safe Rust je me dois de d'apporter un
dernier élément. Toute cette preuve de confiance que fait le Rust de vos
programmes, toute aidée par la syntaxe qu'elle soit, reste une étape difficile
et coûteuse en calculs. Cela explique en partie pourquoi le Rust, malgré que sa
logique soit légèrement plus proche de la machine qu'un langage orienté objet
comme le C++, a un temps de compilation qui reste probablement toujours plus
long que celui de ses concurrents. Quelque soit la façon dont on présente le
problème, le compilateur a simplement beaucoup de choses à faire et cela se
reflètera toujours dans son temps de compilation. Cela ne signifie pas pour
autant que le compilateur Rust ne puisse pas être amélioré davantage, il reste
malgré tout plus lent qu'il le devrait et s'améliore doucement au fil des ans.
Mais même le compilateur Rust parfait ne pourrait pas être aussi rapide qu'un
compilateur C, simplement parce qu'il a beaucoup plus de travail à faire.
*/


/*
Jusqu'ici nous n'avons pas montré grand chose du Rust car nos méthodes étaient
assez simples. A travers l'écriture de TriMot nous allons pouvoir rentrer dans
le coeur du sujet.
*/

struct TriMot {
    pile_triee : PileRust,
    pile_buffer : PileRust,
}


impl TriMot {
    fn insert(&mut self, nouveau : Mot) {
        /*

                                Inférence de types - 1*

        L'inférence de types est un mécanisme par lequel un compilateur (ou
        interpréteur) peut déduire le type d'une variable dans le code source
        d'un langage sans que ce type ne soit explicitement indiqué (à partir du
        contexte entourant la variable). L'algorithme correct d'inférence de
        types a été écrit pour la première fois en 1958 mais n'a été prouvé
        qu'en 1982. D'abord utilisé surtout dans les langages fonctionnels on
        trouve aujourd'hui également de l'inférence de type dans les langages
        orienté objet (vous avez peut-être déjà vu cette fonctionnalité en C# ou
        OCaml).

        Le Rust utilise l'inférence de type, donc vous n'avez la plupart du
        temps pas besoin de spécifier le type d'une variable dans votre code
        pour la déclarer. Cette fonctionnalité, qui n'est pas présente en C ni
        en C++ (sauf erreur de ma part pour le C++) rend le code sensiblement
        plus agréable à écrire et à relire, mais ralenti aussi notablement le
        compilateur dans son travail. Dans la mesure où le compilateur Rust est
        déjà lent par ailleurs cela n'est toutefois pas très problématique et je
        vous encourage à utiliser cette inférence de type.

        Notez que l'inférence de types est différente du typage dynamique et du
        duck-typing dans la mesure où il ne s'agit que d'une facilité d'écriture.
        Que vous éciviez vous même que le type de votre variable est String ou
        que le compilateur le déduise lui même ne change rien par la suite. Votre
        variable devra rester une String pendant toute l'exécution de votre code.
        Dans le cas du duck-typing et du typage dynamique le type de votre
        variable sera ajusté (par des mécanismes distincts et dans des
        proportions différentes) dynamiquement pendant l'exécution en fonction
        du contexte.
        */


        // Premiere partie : on dépile les mots qui viennent après nouveau
        /*
        Plutôt que de mettre un while avec un booléen artificiel je vais
        utiliser la syntaxe loop du Rust, qui boucle jusqu'à être arrêtée de
        l'interieur par un break.
        */
        loop {
            let dernier_mot_option = self.pile_triee.pop();
            /*
            Ici nous devons faire quelque chose de différent suivant que l'on
            ait réussi à sortir un mot de la pile ou non. Pour cela on va
            utiliser la syntaxe match, qui est une sorte de switch inspiré de la
            programmation fonctionnelle.
            */
            match dernier_mot_option {
                /*
                J'avais du mal à comprendre cette syntaxe au début. En fait le
                type Option peut prendre deux valeurs : None (l'autre) ou
                Some(*notre mot*) si on a sorti quelque chose avec notre pop.
                Le Rust va ici faire du pattern matching (d'où le nom match) et
                remarquer que la branche Some(dernier_mot) a le même pattern que
                Some(*notre mot*), il suffit de mettre *notre mot* dans la
                variable dernier_mot (déclarée à le volée ou non). C'est ce que
                le Rust va faire, et c'est ainsi que j'ai accès à la valeur du
                mot dans le reste de la branche.

                Notez que ce mécanisme, quoique assez rapide à l'exécution, est
                sensiblement qu'un simple switch à compiler.
                */
                Some(dernier_mot) => {
                    /*
                    Notez que la comparaison est possible car Mot dérive les
                    traits PartialOrd et Ord.
                    */
                    if dernier_mot < nouveau {
                        self.pile_triee.append(dernier_mot);
                        break;
                    }
                    else {
                        self.pile_buffer.append(dernier_mot);
                    }
                },
                None => break,
            };
        }
        // Deuxième partie : On ajoute le nouveau mot à sa place.
        self.pile_triee.append(nouveau);
        /*
        Troisième partie : On remet les mots du buffer à leur place dans la pile.
        */
        loop {
            /*
            On peut aussi raccourcir la syntaxe en mettant l'expression dans le
            match.
            */
            match self.pile_buffer.pop() {
                /*
                Si nous n'avons qu'une seule ligne derrière un cas de notre
                match qui ne soit pas une déclaration, nous n'avons plus besoin
                d'accolades, en revanche la fin de ligne est différente (il faut
                mettre la virgule que nous aurions mis après des accolades).
                */
                Some(dernier_mot) => self.pile_triee.append(dernier_mot),
                None => break,
            };
        }
    }

    /*
    Cela n'est pas particulièrement nécessaire ici, mais pour montrer la syntaxe
    associée je vais écrire la méthode affiche comme une fonction associée au
    type TriMot (comme une fonction statique en Java par exemple).
    */
    fn affiche(trieur : &mut TriMot) {
        // Etape 1 : On inverse la pile pour l'afficher dans l'ordre.
        loop {
            match trieur.pile_triee.pop() {
                Some(dernier_mot) => trieur.pile_buffer.append(dernier_mot),
                None => break,
            }
        }
        // Etape 2 : On reconstruit la pile en l'affichant
        loop {
            match trieur.pile_buffer.pop() {
                Some(dernier_mot) => {
                    /*
                    println! est l'équivalent en rust du printf en C. La chaîne
                    de formattage fonctionne d'un façon assez différente, je
                    vous laisse regarder la documentation si vous êtes
                    intéressés. Notez le '!' à la fin de println!, il est là
                    pour signifier que println n'est pas un fonction mais une
                    macro, c'est à dire un bloc de code qui viendra se
                    substituer correctement là où on a écrit println! dans notre
                    code.

                    Les macro ont certains avantages sur les fonctions mais en
                    pratique je ne m'en suis jamais servi, d'une part parce que
                    les fonctions me suffisent souvent et d'autre part parce que
                    la syntaxe pour écrire des macro n'a à mon avis rien à
                    envier aux pires syntaxes du C++.
                    */
                    println!("{}", dernier_mot);
                    trieur.pile_triee.append(dernier_mot);
                },
                None => break,
            }
        }
    }

    /*
    On peut également utiliser les fonctions associées pour faire des
    constructeurs simples.
    */
    fn new() -> TriMot {
        /*
        Ici je n'ai pas besoin de déclarer les membres de mes structures comme
        mutables car je n'en ai pas besoin, ce ne sont que des variables locales
        qui vont temporairement contenir mes valeurs pendant la durée de la
        fonction. Ce qui arrivera aux valeurs après l'execution de la fonction
        n'est pas de leur ressort.
        */
        let vecteur_triee = Vec::new();
        let vecteur_buffer = Vec::new();
        let pile_triee = PileRust { vecteur_interieur : vecteur_triee };
        let pile_buffer = PileRust { vecteur_interieur : vecteur_buffer };
        /*
        Pour initialiser TriMot j'utilise une syntaxe raccourcie décrite dans
        la documentation qui fonctionne car les attributs de ma structure ont le
        même nom que les variables avec lesquelles je les initialise.

        Notez que contrairement au C et au C++ je n'ai pas de dificulté à
        renvoyer des variables locales depuis mes fonctions car même si Rust
        gère ses espaces mémoire d'une façon semblable au C/C++ le langage
        repose beaucoup moins sur l'usage de pointeurs et le compilateur détecte
        la plupart des fautes sur les accès en mémoire.
        */
        TriMot { pile_triee, pile_buffer }
    }
}


fn main() {
    let mut ligne = String::new();
    let mut trieur = TriMot::new();
    loop {
        match io::stdin().read_line(&mut ligne) {
            Ok(n) => {
                /*

                                        Responsabilité - 3***

                Remarquez le .clone() dans la suite du code. Sa raison est un
                peu technique : en fait Rust a un système de responsabilité des
                valeurs (ownership dans la documentation).

                L'idée, empruntée à la programmation orienté objet, est que
                plusieurs parties du programme ne peuvent pas simultanément être
                responsable de l'état d'une variable. Pour faire plus grossier,
                Rust n'autorise qu'une seule personne à écrire sur une variable
                à la fois.

                Le problème ici est que ligne est une variable mutable qui est
                déjà réécrite dans le match lorsque je lis l'input, donc lorsque
                j'assigne ligne comme membre de mot, Rust considère cela comme
                une erreur parce que je déplace la responsabilité de ligne sur
                mot alors que je m'apprète à appeler à nouveau read_line juste
                après (alors que ligne sera toujours sous la responsabilité de
                ma structure qui ne disparait pas).

                La solution est assez simple dans mon cas, je m'intéresse
                seulement à la valeur de ligne et pas à sa variable donc je peux
                simplement en faire une copie. Certains types vont faire cette
                copie implicitement, mais ce n'est pas le cas de String.

                Ce mécanisme de responsabilité est très présent en Rust est la
                dernière pièce de ce que le langage essaie de bâtir avec ses
                variables immutables par défaut et ses références. Je ne peux
                pas tout décrire ici mais la documentation explique en détail
                comment ce système de responsabilité fonctionne (il s'applique
                aussi aux références).
                */
                // n est le nombre de nouveaux octets lus sur stdin.
                if n == 0 {
                    break;
                }
                else {
                    let ligne_copie = ligne.clone();
                    // Il nous faut aussi supprimer le retour à la ligne
                    let ligne_trimmed = ligne_copie.trim_end_matches('\n');
                    let mot = Mot { contenu : ligne_trimmed.to_string() };

                    trieur.insert(mot);

                    /*
                    Cette ligne est celle qui m'a posé le plus de problèmes dans
                    ce tutoriel. Au lieu de réécrire le contenu de ligne la
                    méthode read_line va ajouter ce qu'elle obtient à lafin, ce
                    qui n'était pas ce à quoi je m'attendais.
                    */
                    ligne = String::new();
                }
            },
            Err(msg) => println!("{}", msg),
        }
    }
    TriMot::affiche(&mut trieur);
}


/*

                            Le mot de la fin - 1*

J'espère vous avoir montré pourquoi, malgré la probable bulle qui entoure le
langage, le Rust n'est pas qu'un effet de mode. L'objectif du langage est de
mettre à disposition des programmeurs des outils pour écrire des programmes
d'une façon aussi fiable que possible. Pour cela, le langage tente d'allier les
meilleurs éléments de ses contemporains : la fluidité des langages fonctionnels,
la séparation des rôles de l'orienté objet, la fiabilité des langages de preuve
et le fonctionnement interne des langages de bas niveau.

Est-ce que cette tentative est un succès ? Je serai personnellement tenté de
dire que oui. Le Rust n'est certainement pas un langage universel et j'y
préférerai toujours Java, Python ou le C pour certaines application, mais le
Rust se fixe un objectif et le tient surprenament bien.

Cela ne veut pas dire que le langage est exempt de critiques, certaines par
ailleurs très justifiées :

     "La syntaxe du Rust est trop restrictive et se met sans arrêt en
     travers du chemin du développeur, et donc il faut écrire énormément
     de code pour faire des choses simples."

Cette critique est à mon sens à moitié vraie mais sous-tend en fait un autre
problème. Il est vrai qu'en Rust vous devez sans cesse respecter des contraintes
de la syntaxe : faire un match sur le résultat d'une fonction au cas où elle
rencontre un problème, faire attention aux problèmes de responsabilité des
variables etc... Cela étant si vous vous souvenez des tutoriels en C (en
particulier compilation avancée et états indéfinis) alors vous n'aurez pas
manqué de remarquer que nous étions obligé de faire des choses semblables faute
de quoi nos programmes tombaient très facilement dans des états indéfinis. Donc
certes faire ces manipulations peut sembler laborieux, mais j'arguerai que ne
pas les faire n'est pas vraiment possible si on veut arriver à un programme qui
marche rapidement. Pour aller plus loin, j'ajouterai même que je trouve ces
vérifications bien plus rapides à effectuer qu'en C où il faut écrire soit même
plusieurs lignes de code pour faire moins qu'un simple match.

Il ne faut pas non plus extrapoler ce que je dis içi. Dans des langages de plus
haut niveau comme Java ou Python faire toutes ces vérifications de façon aussi
systématique serait une perte de temps indéniable et pas vraiment justifié
(d'ailleurs je suppute que beaucoup des détracteurs de cet avis sont plutôt
habitués à des langages de haut niveau). Mais le Rust reste un langage assez
bas niveau qui s'exécute nativement sur la machine, et dans ce contexte de
langages de bas niveau il est vraiment difficile de se passer de ces garde-foux.

Je me permet également de soulever un point important. Certes le Rust a une
syntaxe très rigoureuse qu'il faut respecter, mais contrairement aux
compilateurs C/C++ le compilateur rust (rustc) est extrèmement aidant. Pour la
quasi totalité des erreurs de syntaxe que vous pourrez écrire, le compilateur va
vous renvoyer un message d'erreur en soulignant le problème avec un message qui
indique précisément votre problème (et pas quelque chose de vaguement lié comme
c'est très souvent le cas en C/C++) et ce message d'erreur sera très souvent
suivi de la solution pour le résoudre avec un message explicatif. rustc est sans
doute le compilateur le plus aidant qui soit, donc je ne pense pas qu'il soit
justifié de dire que la syntaxe du langage est un obstacle pour écrire un
programme.

Toutefois il y a du vrai dans cette remarque, mais pas forcément dans le sens où
on pourrait le croire. Cette seconde idée se trouve également cachée derrière
la deuxième critique courante du Rust :

        "Pour écrire n'importe quel projet en Rust la librairie standard
        ne suffit pas et il faut récupérer des librairies extéreures, mais
        la moindre librairie a des centaines de dépendances."

Oui, le Rust est bien ce type langage... Avant d'entrer dans le vif du sujet je
mentionne que même si je ne m'en suis pas servi ici le Rust dispose d'un package
manager appelé cargo (qui gère aussi la compilation des projets) et les packages
(i.e. librairies extérieures) en Rust se nomment crates. Au cas où je rappelle
qu'un package manager est un outil dont le rôle est de mettre automatiquement à
disposition du developpeur des librairies écrites par d'autres et hébergées par
une entité centrale (par exemple le package manager de python est pip).

Cette critique est justifiée, mais la formulation commune de cette critique
(que j'ai essayé de reprosuire fidèlement ici) n'explique pas vraiment en quoi
cela est un problème. La première raison est plus psychologique que réelle et
vient simplement du fait que les langages historiques (C, C++ et Java) n'ont
pendant très longtemps pas eu de package manager, ce qui a poussé les
développeurs à plutôt écrire de larges librairies avec plein de fonctionnalités
que les developpeurs intéressés pourraient télécharger manuellement et utiliser
dans leurs projets s'ils le souhaitaient. Un défaut de cette méthode est qu'elle
force à embarquer dans les applications des librairies assez vaste dont on
n'utilise souvent qu'une petite partie.

Grâce au package manager il est possible de séparer les grosses librairies en
plein de petites librairies pour que les developpeurs ne récupèrent que ce dont
ils ont besoin (et pour simplifier la mintenance de ces librairies). C'est
d'ailleurs ce qui se passe en Rust, les grosses librairies sont séparées en
plein de petites parties, c'est la raison pour laquelle au lieu d'avoir une
grosse dépendance le projet pourra en avoir un cinquentaine (si la librairie est
découpée en 50 morceaux par exemple).

Si nous vivions dans un monde merveilleux ma réponse s'arrêterait là,
malheureusement il y a aussi de vrai problèmes à avoir des dépendances trop
éclatées. Le langage qui souffre le plus de ce problème est Javascript, où le
moindre projet aura des miliers de dépendances obscures. Or avec le retour
d'expérience on a observé trois problèmes avec ce système :
 - Les packages finissent souvent par n'avoir aucun intérêt individuel,
 Javascript est particulièrement connu pour tirer des centaines de paquets d'une
 ligne pour effectuer la moindre tâche bénine.
 - Les gros projets ont tendance à se faire contaminer par des dépendances
 intempestives héritées des projets dont ils dépendent. Et il n'est pas rare
 qu'un projet très renommé ait parmi ses dépendances des librairies de gens
 obscurs et peu intéressés. Cela pose un problème lorsque la personne décide de
 retirer sa librairie du public puisqu'elle paralyse temporairement (en général
 pas trop longtemps mais tout de même) le projet dans sa globalité. Des
 individus peuvent également retirer leurs librairies pour des raisons
 idéologiques (par exemple ârce qu'elles sont utilisées par des gouvernement ou
 entreprise dont la moralité de convient pas à l'auteur de la librairie), ce qui
 là aussi pose problème pour les projets qui en dépendent.
 - Le troisième cas de figure, qui ressemble un peu au deuxième, est que des
 développeurs ou organisations mal intentionnées peuvent mettre des librairies
 à disposition "en sommeil" puis les mettre à jour avec du code malicieux qui
 sera automatiquement mis à jour dans les librairies qui en dépendent.

Il existe des moyens de se prémunir de tous ces problèmes, mais ils demandent
du travail et de l'organisation que n'ont pas tous les développeurs indépendants.
Pour résumer, le problème de cette explosion de dépendances est qu'au lieu
d'accorder sa confiance aux développeurs d'une grande librairie connue, le
programmeur doit aujourd'hui également faire confiance à tous les developpeurs
obscurs qui ont écrit des librairies plus ou moins utiles dont la grosse
librairie dépend.


A mon sens le point vraiment intéressant qui est soulevé dans ces deux critiques
d'une façon très implicite est : pourquoi le Rust semble-t-il pénible à écrire
et pourquoi favorise-t-il l'apparition de plein de petites librairies ?

Une réponse à cela est à chercher dans le principe même du Safe Rust. Lorsque
vous écrivez du code en Safe Rust, par exemple pour utiliser Vec, vous ne
modifiez pas directement le Vec sur lequel vous travaillez (cela serait unsafe).
Au lieu de cela, vous modifiez le Vec à l'aide des méthodes fournies pour lui
faire faire ce que vous souhaitez. Mais le problème qui devient rapidement
apparent avec cette approche est que pour chaque type, vous devez donc définir
toutes les méthodes pour faire tout ce que les développeurs pourraient souhaiter
faire, sinon ils se retrouveront en difficulté au moment d'écrire leur code.

Le Rust dispose d'un mécanisme astucieux pour combattre cela (il est possible
de rajouter des méthodes à des types que vous n'avez pas défini vous même) mais
les developpeurs "en bout de chaîne", qui utilisent le Rust en entreprise pour
réaliser une mission spécifique, n'auront certainement pas envie de recoder des
méthodes souvent laborieuses à écrire pour leur travail. Au lieu de cela il leur
suffit d'ajouter une dépendance avec cargo et voilà, ils ont maintenant accès à
ce qu'ils cherchaient.

C'est à mon avis cet aspect du Rust qui est à l'origine de la première critique,
même si cela n'est pas toujours identifié. Le Rust peut effectivement être lourd
à utiliser tant que vous ne connaissez pas bien le langage, parce que vous êtes
sans arrêt en train d'utiliser des méthodes pour faire ce que vous voyez comment
faire avec des octets, mais pas d'une façon safe que le compilateur va accepter.
En connaissant bien le langage et en ayant un peu de temps devant soit on peut
évidemment réécrire ce dont on a besoin en Safe Rust, mais ce deux conditions
ne sont malheureusement pas forcément réunies.

Une dernière critique que j'ai déjà abordée est le temps de compilation et le
manque d'efficacité du compilateur. Même si la situation s'améliore d'année en
année il reste très probable que le problème ne sera jamais pleinement éliminé.
Les executables produits avec Rust sont effectivement moins efficients que ceux
produits avec du C par exemple, toutefois cette différence est essentiellement
due aux filets et aux abstractions que le Rust place pour vous.

Toutes les abstractions crées par le Rust font perdre du temps à la machine
(pendant la compilation ou l'exécution), mais elles vous font également gagner
beaucoup de temps à l'écriture et à la vérification de votre code. A titre
d'exemple pour écrire ce tutoriel la seul chose que l'ai eu à débugger est le
read_line, la reste a marché exactement comme on aurait pu s'y attendre une fois
la compilation passée. Cela représente un gain de temps énorme par rapport aux
heures que j'ai pu passer à débugger le C et le C++.

La raison pour laquelle je vous recommanderai personnellement d'utiliser le Rust
sur le C++ n'est pas pour écrire des programmes plus fiables (cela est vraiment
un gain annexe) mais pour écrire vos programmes plus vite et avec (beaucoup)
moins de debuggage. Je finirai donc ce tutoriel sur un adage très répandu dans
le monde de l'ingénieur : votre temps est précieux (et bientôt cher payé) alors
que la machine travaille gratuitement.

tl;dr : Utilisez le Rust plutôt que le C++ pour vous simplifier la vie, peu
importe la faible perte de temps que cela induit pour la machine. Si quelqu'un
veut que vous passiez du temps à écrire un programme qui s'exécute vite en
machine il faudra qu'il vous paie à la valeur du temps que vous allez passer à
écrire le code source. Mais on ne vous paiera probablement pas à cela, donc ne
vous mettez pas des bâtons dans les roues tout seul et utilisez le Rust.
*/
