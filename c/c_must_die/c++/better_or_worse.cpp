/*
Ce programme fait partie de l'épilogue du tutoriel du Rezal sur le C. Son but
est de mettre en avant les apports du C++ par rapport au C, mais également de
montrer les défauts du C++.

Le support de ce tutoriel est décrire un programme qui prenne en argument une
liste de mots séparés par des retours à la ligne et renvoie la liste triée par
ordre alphanumérique.

Notez que dans la mesure où ce programme n'est pas écrit en C il ne respecte
pas la structure des programmes en C que l'on peut trouver ailleurs.

Pour la compilation de ce fichier le mieux est d'utiliser le Makefile fourni,
attention cependant vous aurez besoin d'un compilateur C++ (et pas seulement C)
pour compiler ce fichier (évidemment). Dans le Makefile j'ai supposé que votre
compilateur est g++ (compilateur C++ de gcc).

Contributeurs : Rezal P18
*/

/*
Le C++ utilise un système d'espace de noms que l'on retrouve dans la plupart des
langages orientés objet. Cela n'est pas gênant en tant que tel, mais d'une part
la syntaxe choisie pour utiliser ces espaces de noms (std::string par exemple)
est assez peu à mon goût, mais surtout le C++ utilise aussi le système de
headers du C, et le mélange des deux est assez déconcertant.
*/
using namespace std;
#include "pile.h"
#include <iostream>

/*

                                Quel Bazar ! - 1*

Cela me permet d'aborder même brièvement le premier problème évident du C++ :
le langage est très inhomogène, chaotique et beaucoup trop vaste. Là où le C
vous offre une poignée de fonctions dans sa librairie standard et attend de vous
que vous refassiez tout à la main, le C++ essaie de vous fournir une syntaxe
pour tout les cas d'usage : il y a une syntaxe particulière pour gérer les
entrées sorties (celle moche avec des << que vous verrez dans ce programme), une
syntaxe particulière pour allouer de la mémoire dynamiquement (new et delete,
qui pour le coup sont un ajout très bienvenu).

Est-ce vous avez de donner l'accès à une certaine fonction extérieure à des
attributs privés de votre classe ? Vous pourriez réecrire votre programme avec
une meilleure structure pour faire disparaitre le problème ... ou vous pourriez
utiliser la syntaxe dédiée (friend) pour le faire en une ligne !

Est-ce que vous avez besoin de manipuler des tableaux mais ne voulez pas
vérifier vous même qu'ils sont bien construits ? Utiliser la librairie Boost,
qui vous fournit une nouvelle définition des tableaux.

Vous avez besoin de polymorphisme mais n'avez pas envie de faire de l'héritage ?
Utiliser des templates et le problème est résolu !

Quoiqu'individuellement intéressants (même si j'ai mes doutes sur friend), le
problème évident du C++ est l'accumulation de ces fonctionnalités pas toujours
consistante entre elles et toujours plus obscures à lire et à comprendre.

La première conséquence de cela est que beaucoup de developpeurs (qui
n'utilisent le C++ qu'occasionnelement ou que comme un outil par exemple) ne
vont pas connaitre tous les tenants et aboutissants de ces syntaxes reservées,
et vont simplement utiliser la partie du langage qu'ils connaissent. Mais cette
partie du langage ne sera pas forcément la même d'une personne à une autre, ce
qui pose problème notamment lorsque vous cherchez une réponse à un problème sur
les forums : une réponse vous dira d'utiliser la librairie C, une autre
préferera les fonctions amies et une troisième résoudra le problème en quelques
lignes à l'aide de templates. Cela donne souvent le sentiment assez dérangeant
que l'on essaie de faire quelque chose de simple (par exemple lire le contenu
d'un fichier) mais qui requiert d'utiliser des outils exotiques (par exemple la
librairie C) alors qu'en fait il existe bien une syntaxe simple en C++ pour
résoudre le problème (avec des <<) mais que l'on ne la trouve pas.

Un autre problème posé par le manque de standardisation du C++ est que personne
ne peut vraiment dire à quoi ressemble un bon code en C++. C'est un problème
certes partagé par beaucoup de langages modernes (Java et Python en tête) mais
est davantage marqué en C++. Comme le C++ propose une miriade de syntaxes
souvent contradictoires il est difficile de dire laquelle il faut utiliser
lorsque l'on tente de dégager une structure pour son programme. Vaut-il mieux
utiliser de l'héritage ou des templates pour faire du polymorphisme ? Vaut-il
mieux utiliser une classe parente comme interface ou utiliser des fonctions
amies ? Vaut-il mieux utiliser des pointeurs du C ou la librairie Boost pour
manipuler les tableaux ?

Il n'y a pas de bonne réponse à cette question, mais comme toujours je vous
recommanderai d'éviter de mixer les styles autant que possible, vous riquez
sinon de vous retrouver face à mur plus tard. Notez cependant qu'en C++ vous
n'aurez pas forcément la liberté de choisir ou non de mixer les styles, souvent
vous travaillerez avec d'autres qui n'utiliseront pas les mêmes fonctionnalités
que vous et vous devrez faire avec. Les programmes que vous obtiendrez seront
indéniablement inhomogènes et un peu Frankenstein, mais en C++ vous ne pourrez
pas faire beaucoup mieux.

Sans aller jusqu'à l'austérité du C, il est préférable pour un langage d'être un
minimum homogène, même s'il y a indéniablement un public pour les langages
fourre-tout (il suffit de voir le succès du C# aujourd'hui).

Petit bonus pour avoir lu jusqu'ici, beaucoup de programmeurs assez briants ont
fait leurs petits commentaires acidulés sur le C++, et certains sont assez
drôles. Si vous voulez les voir ils se trouvent sur la page Wikipédia du C++
(en anglais) dans la section Criticism.
*/

/*

                              Les objets - 1*

La phrase la plus connue concernant le C++ est "Le C++ est du C avec des
objets". Cette phrase, attribuée apparement à raison à Bjarne Stroustrup (le
concepteur du C++), porte cependant davantage sur l'idée originale du Stroustrup
que sur le C++ qui en a résulté. Considérer que le C++ n'a ajouté que les
classes au C serait une grossière réduction. Pour comprendre pourquoi il faut
d'abord se demander pourquoi le C++ a été créé.

Je ne vais pas rentrer dans les détails techniques ici (vous pourrez trouver des
éléments d'explication dans le tutoriel sur la compilation avancée du C), mais
le C a deux défauts principaux qui deviennent rapidement très difficiles à gérer
sur des projets de grande taille :

 - Le C permet de décrire des notions abstraites à l'aide de structures, unions
 et enums, mais cette description abstraite fait toujours référence à
 l'implémentation des notions concernées, donc si vous changez cette
 implémentation vous changerez sans doute aussi la description (i.e.
l'interface) de la notion.

 - Le C a une très forte propension à faire n'importe quoi. Le langage est bas
 niveau et n'offre aucun fillet à ce que le développeur écrit, mais cela est
 (très) souvent source de problèmes. Le C n'a pas de système d'erreurs, les
 types ne sont qu'une aide pour l'écriture du code et leur manipulation n'est
 pas assurée à la compilation. De même le C vous force à vous préoccuper de
 problèmes matériels (usage de pointeur, gestion des espaces mémoires etc...)
 dont vous ne voulez pas forcément vous occuper pendant l'écriture de votre code
 et qui seront certainement source de bugs.

Ces critiques du C sont intrinsèquement liées à ce qui fait sa force (être un
langage simple mais très proche de la machine), mais restent des obstacles à
l'écriture de programmes volumineux. Pour dépasser ces limitations, une idée de
Stroustrup était de construire un langage orienté objet à partir du C.

La programmation orientée objet avait déjà été introduite dans d'autres
langages moins utilisés, notamment Simula en 1962 et SmallTalk en 1972, mais ces
langages avaient par ailleurs d'autres défauts et étaient beaucoup moins
utilisés en pratique que le C. Quoique discutable du point de vue théorique, la
démarche de faire un langage orienté objet rétrocompatible avec le C est
indéniablement une bonne idée du point de vue économique, puisque n'importe
quelle programmeur C pourra très rapidement s'adapter au C++ et en apprécier les
avantages.

Mais au delà de ces considérations, qu'est ce que la programmation OO apporte
d'utile ? Finalement, qu'est ce que la programmation orienté objet ?

Je ne vais pas apporter une réponse définitive à cette question parce qu'il est
assez difficile de définir précisement les contours de l'orienté objet (surtout
depuis que presque tous les langages se disent orienté objet), si cela vous
intéresse je vous encourage à suivre l'ES dédié à la programmation orientée
objet en 2ème année. Je vais me contenter de mettre en évidence certains
bénéfices de la programmation orientée objet.

Le premier changement apporté par la programmation OO est ... les objets.
Quoique semblables à priori aux structures du C, leur utilisation est très
différente : là où vous modifiez vos structures depuis des routines en C, les
objets de C++ vont pouvoir se modifier eux mêmes à l'aide de méthodes.

Un exemple d'objet en C++ : le type mot détaillé dans la documentation. Notez
que l'on peut faire hériter Mot du type parent string sans difficultés. Bien
qu'il soit possible de reconstruire ce genre de comportements à la main en C
cela ne fait clairement pas partie de la syntaxe du langage. Ici nous n'avons
qu'une seule ligne à écrire pour que la classe Mot hérite de (i.e. se comporte
comme) string.
*/
class Mot : public string {
  /*
  Pour comprendre ce à quoi sert cette classe (cela ne vous intéresse
  probablement pas) lisez le fichier README.md
  */
public:
  Mot(string motEntree) : string(motEntree) {
    /*
    Ici nous faisont seulement appel au constructeur du parent. Notez que l'on
    se trouve dans un cas assez extrème : contrairement aux structs en C qui
    font toujours référence à leur implémentation, nous avons ici une classe
    entière qui n'en a pas. Grâce à l'héritage toute l'implémentation (et
    l'interface d'ailleurs) de Mot se trouve dans la classe string.
    */
  }
};

/*
Le C++ est rétrocompatible avec le C et je vais utiliser cela pour contruire
un type pile en C++. Ce que je vais faire est simplement reprendre le code du
type pile écrit pour le tutoriel compilation avancee (je répète que cette
implémentation n'est pas la seule possible et a clairement de gros défauts).
Cependant j'ai pu constater que l'utilisation de ces piles n'est pas du tout
facile. Voyons comment le C++ peut m'aider à rendre ces piles plus agréables
d'utilisation.
*/
class PileCpp {
  /*
  Je vais utiliser mes struct Pile définies dans pile.h en interne dans ma
  classe mais je ne souhaite pas que l'on puisse y accéder depuis l'exterieur,
  pour cela j'utilise l'access-specifier ("restricteur d'accès") private.

  Notez que les restricteurs d'accès sont un aspect assez critiqué de la
  programmation OO, je vous laisse libre de regarder pourquoi si cela vous
  interesse.
  */
private:
  struct Pile pileInterieure;

public:
  PileCpp() {
    // Constructeur
    new_pile(&pileInterieure);
  }

  ~PileCpp() {
    // Destructeur
    free_pile(&pileInterieure);
  }

  size_t taille() {
    // Renvoie la taille de la pile
    return pileInterieure.taille_pile;
  }

  void append(void *ptr) { pile_append(&pileInterieure, &ptr); }

  /*

                        Pass-by-reference - 1*

  Contrairement au C, le C++ dispose d'un mécanisme de pass-by-reference. Au
  lieu de passer en argument une copie de ce qui a été envoyé à la fonction
  on a ici une référence vers l'objet d'origine, ce qui nous permet de le
  modifier par effet de bord. Le gros avantage du pass-by-value sur le fait de
  simplement utiliser des pointeurs est que le pass-by-reference va conserver
  le typage de l'objet : si on a passé en argument un entier on aura dans la
  fonction une référence vers un entier que l'on pourra alors modifier comme
  un entier (cela n'est pas forcément le cas avec des pointeurs, voire le
  tutoriel sur les états indéfinis).

  Notez que grâce au pass-by-reference (symbolisé par le & en argumentde pop)
  je peux ne passer qu'un pointeur simple en argument de ma fonction et pas un
  pointeur vers un pointeur, ce qui évitera de fausses manipulations.
  */
  void pop(void *&ptr) { pile_pop(&pileInterieure, &ptr); }

  void debug() {
    printf("global - %p\n", pileInterieure.content);
    for (size_t i = 0; i < pileInterieure.taille_pile; i++) {
      printf("%ld - %p\n", i, pileInterieure.content[i]);
    }
  }
};

/*
Notre type pile est déjà plus commode à utiliser maintenant que nous n'avons
plus besoin d'utiliser des pointeurs vers des des pointeurs. Mais pour faire
fonctionner notre programme nous avons encore besoin d'une dernière classe qui
nous servira à faire notre tri par insertion.
*/
class TriMot {
private:
  PileCpp pileTriee;
  PileCpp pileBuffer;

public:
  /*

                            Omae wa mō shindeiru - 1*

  Absolument brilliant ! Vous ne lisez que le code qui fonctionne donc vous ne
  pouvez pas vous en rendre compte, mais j'ai eu un gros bug ici (parce que je
  ne suis pas habitué au C++) où j'avais tenté d'initialiser les piles avec la
  première syntaxe commentée (PileCpp()) mais cela a causé une cascade de bugs
  assez difficiles à comprendre que je détaillerai plus loin. La raison ? Si
  vous écrivez PileCpp() vous déclarez la pile en question sur la mémoire stack,
  donc même si vous l'assignez à la variable pileTriee qui existera toujours
  après l'exécution de cette fonction, le C++ va quand de même détruire la pile
  crée une fois l'exécution du constructeur terminée.

  C'est génial non ? Vous êtes dans le constructeur d'un objet en train
  d'initialiser les attributs de votre classe, et à la fin de l'exécution le C++
  va détruire les membres que vous n'avez pas initialisé correctement !

  "Mais enfin, si tes attributs n'étaient pas initialisés correctement, comment
  as-tu fait pour ne pas t'en rendre compte ?"

  Le problème est que, dans la tradition du C, cela a causé un état indéfini
  dans lequel je pouvais utiliser mes pile normalement, à un seul détail près :
  l'espace mémoire sous-jacent de pileTriee et de pileBuffer était le même, donc
  écrire sur une pile écrasait le contenu de l'autre. Mais pour comprendre cela
  il m'a fallu beaucoup de temps, ce n'est pas du tout évident en regardant
  juste le contenu de la pile. Du coup pendant tout le programme je passait mon
  temps à utiliser des piles zombies sur des espaces mémoires déjà libérés sans
  même le savoir.

  Pour résoudre ce problème il a deux solutions : ou bien utiliser la syntaxe
  très exotique que j'ai montré pour pileTriee (i.e. utiliser un new), ou bien
  laisser le C++ appeler le constructeur à votre place. En effet en C++ il n'est
  pas permis d'utiliser des objets qui n'ont pas été initialisés, donc avant que
  vous entriez dans le constructeur le C++ va déjà faire une première
  initialisation des piles en question en utilisant le constructeur par défaut.
  Donc ne rien mettre est suffisant ici.
  */
  TriMot() {
    pileTriee = *(new PileCpp());
    // pileTriee.debug();
    // pileBuffer = *(new PileCpp());
    // pileBuffer.debug();
  }

  void insert(Mot insert) {
    /*

                                  new et delete - 2**

    Si vous vous souvenez du tutoriel sur la compilation avancée il y avait un
    problème de copie VS map dans notre code. La solution pour le regler est
    sensiblement la même qu'en C mais le C++ apporte un syntaxe plus facile à
    utiliser et plus sûre pour résoudre le problème : new et delete.

    Là où l'usage de leurs équivalents en C était déconseillé, new et delete ne
    seront probablement pas source d'erreurs dans votre code si vous prenez le
    temps de lire ce qu'ils font, donc vous pouvez les utiliser dans votre code
    sans vous faire trop de soucis.
    */
    // Notez l'usage implicite du constructeur par copie.
    Mot *heapInsert = new Mot(insert);
    Mot *dernierMotPtr;
    Mot *dernierMotCopy;
    /*
    Contrairement au C, le C++ n'est pas très friand des pointeurs void * et en
    particulier des cast hasardeux. Ici par exemple j'ai besoin de passer de
    passer par un pointeur intermédiaire pour ajouter mes mots dans la pile.
    Le problème est un peu techinque mais je ne peux pas faire du
    pass-by-reference si l'argument que j'ai mis dans ma fonction est
    (void *) dernierMotPtr car le C++ a besoin d'une variable intermédiaire pour
    faire son cast, et passer une référence vers cette variable intermédiaire
    n'aurait pas de sens.
    */
    void *dernierMotRawPtr;
    /*
    Contrairement au struct du C, les objets du C++ sont forcéments initialisés.
    */
    Mot dernierMot = Mot("");
    while (pileTriee.taille() > 0) {
      // dernierMot est récupéré par effet de bord.
      pileTriee.pop(dernierMotRawPtr);
      /*
      Concernant le fait d'être moins permissif sur les cast, le C++ n'autorise
      pas à faire des conversions implicites de void * vers les autres types
      (contrairement au C).
      */
      dernierMotPtr = (Mot *)dernierMotRawPtr;
      /*
      Comme dans le tutoriel sur compilation avancee il nous faut effectuer une
      copie de l'objet récupéré par pop en heap (pour éviter d'écraser l'espace
      mémoire associé lors d'autres passages dans la boucle).
      */
      dernierMotCopy = new Mot(*dernierMotPtr);
      dernierMot = *dernierMotCopy;
      // On évite la fuite de mémoire (memory leak) en libérant l'espace
      delete dernierMotPtr;
      if (dernierMot < insert) {
        // i.e. si dernierMot vient avant insert dans l'ordre lexicographique
        pileTriee.append((void *)dernierMotCopy);
        break;
      } else {
        // insert vient avant dernierMot, donc on met dernierMot dans pileBuffer
        pileBuffer.append((void *)dernierMotCopy);
      }
    }

    pileTriee.append((void *)heapInsert);

    while (pileBuffer.taille() > 0) {
      pileBuffer.pop(dernierMotRawPtr);
      dernierMotPtr = (Mot *)dernierMotRawPtr;
      // Ici aussi on fait une copie en heap pour éviter l'écrasement.
      dernierMotCopy = new Mot(*dernierMotPtr);
      delete dernierMotPtr;
      pileTriee.append((void *)dernierMotCopy);
    }
  }

  void affiche() {
    Mot *motPtr;
    Mot *motCopy;
    void *motRawPtr;
    // Pour afficher les mots dans le bon sens il faut une étape intermédiaire.
    while (pileTriee.taille() > 0) {
      // std::cout << "---> (siz) " << pileTriee.taille() << '\n';
      // pileTriee.debug();
      pileTriee.pop(motRawPtr);
      motPtr = (Mot *)motRawPtr;
      motCopy = new Mot(*motPtr);
      // pileTriee.debug();
      delete motPtr;
      pileBuffer.append((void *)motCopy);
    }

    while (pileBuffer.taille() > 0) {
      // std::cout << "---> (buf) " << pileBuffer.taille() << '\n';
      pileBuffer.pop(motRawPtr);
      motPtr = (Mot *)motRawPtr;
      std::cout << *motPtr << '\n';
      motCopy = new Mot(*motPtr);
      delete motPtr;
      pileTriee.append((void *)motCopy);
    }
  }
};

/*

                      Cela ne résout pas le problème ! - 1*

Comme expliqué plus haut, l'objectif principal du C++ était d'être un langage
qui combine la simplicité du C avec une meilleure abstraction pour pouvoir
écrire plus facilement de larges applications. Pour cela nous avons vu que le
C++ apporte beaucoup d'innovations par rapport au C : l'orienté objet, de
meilleures syntaxes pour la manipulation de mémoire heap et un mécanisme de
références tant attendu en C. Tout semble aller pour le mieux et malgré le
manque d'homogénéité du langage on pourrait se dire que le C++ a beaucoup de
bons points pour lui (ce qui n'est pas complètement faux par ailleurs).

Mais toutes ces nouveautées, tous ces efforts pour arriver à faire un langage
mieux à utiliser que le C sont à mon sens balayés par ce qui est certainement
le meilleure et la pire décision du C++ : être rétrocompatible avec le C.

Avant tout, un point de détail : non, le C++ n'est pas complètement
rétrocompatible avec le C. Bien que les deux langages partagent beaucoup de
syntaxes certaines syntaxes du C ne sont pas valides en C++ (d'ailleur j'ai dû
changer des détails du  code source de pile.c par rapport à la version dans
compilation avancée, vous pouvez les chercher vous voulez). Mais il n'empêche
que le C++ reprend plus que l'essence de la syntaxe du C : les pointeurs, la
mémoire stack et heap et la gestion des types primitifs est partagé entre les
deux langages. L'essence de la syntaxe du C se retrouve en C++.

J'ai déjà mentionné pourquoi la retrocompatibilté avec le C était une bonne
décision économique mais alors pourquoi est-ce une mauvaise décision du point
de vue informatique ?

La raison est encore (et toujours) que le C et le C++ ont des objectifs
différents. Le C existe pour écrire de l'assembleur pour la machine
automatiquement; le C++ existe que les développeurs puissent efficacement
manipuler des concepts abstraits.

Le problème de créer un langage abstrait comme le C++ par dessus le C est que la
syntaxe du C, très proche de la machine, n'a pas de respect pour l'abstraction
que vous essayez de créer avec vos objets; cela revient à ériger un monument
d'abstraction sur des fondations qui peuvent aisément tout balayer. Ma
mésaventure dans le constructeur de TriMot est un example de cela. J'essaie
d'initialiser les attributs de mon objet (ce qui est une manipulation abstraite)
mais la syntaxe du C, orientée vers la machine, va ignorer l'abstraction que
j'essaie de créer et va détruire à la fin de l'exécution de la fonction tout ce
qui se trouve dans la mémoire stack.

Au dela d'un problème moral, cette rétrocompatibilté pose aussi un problème
plus pratique, qui est que le C++ hérite de l'aspect le moins flatteur du C,
les état indéfinis. Ces états indéfinis n'arriveront pas lorsque vous
manipulerez des objets en C++, dans lesquels vous aurez tout le loisir
d'utiliser des exceptions. En revanche la syntaxe du C, que l'on retrouve en
C++, va elle même causer des états indéfinis (notamment avec les manipulations
de pointeurs et la gestion des espaces mémoires).

tl;dr : La rétrocompatibilité avec le C fait que la syntaxe du C++ contredit
l'abstraction que le langage tente de créer, et les mauvais aspects du C se
retrouvent pour bonne part dans le C++. Même si j'aime beaucoup le C par
ailleurs, la rétrocompatibilité avec le C n'est une bonne idée pour à peu près
aucun langage qui tente de faire quelque chose de différent du C.
*/

int main(int argc, char const *argv[]) {
  TriMot trieur = TriMot();
  string bufferString = "";
  Mot motBuffer = Mot(bufferString);

  while (getline(cin, bufferString)) {
    motBuffer = Mot(bufferString);
    trieur.insert(motBuffer);
  }
  trieur.affiche();
  return 0;
}

/*

                            Le mot de la fin - 1*

Le C++ est un langage qui a des forces indéniables, mais ses points forts sont
à mon sens entachés par trop de point noir : le C++ est très inhomogène donc
difficile à apprendre et frustrant à écrire, et le C++ reprend la syntaxe du C
alors que ses objectifs sont très différents, d'où le décalage entre
l'abstraction que vous tentez de créer et les erreurs concrètes que vous
recevez.

Mais à tout cela s'ajoute un ultime problème concernant le C++ : nous ne sommes
plus en 1985, et beaucoup d'autres langages plus abstraits sont disponibles
aujourd'hui (Java en tête de liste). Que ces langages modernes aient étés
influencés par le C++ est indéniable, mais il n'empêche que pour un cas d'usage
concret le C++ n'a que peu d'argument sur ses successeseurs.

Le problème du problème du C++ aujourd'hui n'est pas qu'il est incapable de
faire certaines tâches, mais plutôt que toute tâche pourra être mieux faite par
un autre langage :
 - Vous avez besoin de faire des manipulation de bas-niveau ? Utilisez plutôt le
C, qui est plus proche de la machine donc compile plus vite et plus
efficacement.

 - Vous auvez besoin d'abstraction pour créer une application complexe ou
collaborer avec une équipe sur un même programme ? Utilisez Java, qui a
l'immense avantage de n'être pas rétrocompatible avec le C et vous évitera
toutes les erreurs de manipulation d'espaces mémoire.

 - Vous avez besoin de plus d'abstraction que le C mais moins que Java (parce
que pourquoi pas), ou souhaitez utiliser une langage qui compile vers du code
machine plutôt que du bytecode (qui requiert la JVM pour être exécuté) ?
Utilisez littéralement n'importe quel langage basé sur LLVM qui ne soit pas
rétrocompatible avec le C (avec Rust en tête de liste).

 - Vous avez besoin d'écrire un programme rapidement sans vous soucier de
problèmes liés au fonctionnement du langage, ou bien avez besoin de faire du
calcul scientifique ? Utilisez plutôt python qui aura de meilleures librairies
et une syntaxe plus agréable avec notamment des algorithmes souvent de meilleure
qualité.

Le C++ a été un langage très influent pendant une courte période, mais jamais un
langage vraiment omniprésent, contrairement au C qui le précède et à Java qui le
suit. Le langage apporte un grand nombre d'innovations sur ses prédécesseurs qui
ont fait son intérêt historiquement, mais le langage a aussi son lot de défauts
préoccupants (manque d'homogénéité et rétrocompatibilité avec le C). Le problème
est qu'aujourd'hui les avantages du C++ sont rendus assez caduques par des
outils plus modernes (Java ou Rust par exemple) alors que ses défauts dont
ancrés dans le langage et pèsent toujours autant sur les développeurs qu'en
1985.

C'est la raison pour laquelle j'aurais tendance à ne recommander le C++ à
personne. Quel que soit votre cas d'usage le C++ sera à peu près toujours
surclassé par un autre langage. En développant le C++ Bjarne Stroustrup a
raisonné en économie en cherchant à créer un langage qui satisfasse tous les cas
d'usage qui se présentaient à lui, mais ce faisant il en a fait un langage avec
très peu d'identité et un fort ancrage dans son contexte historique.
*/
