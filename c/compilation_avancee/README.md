#                                 Contenu

Cette partie du tutoriel sera la dernière pour beaucoup d'entre vous alors j'en
ai fait une sorte de point culminant, avec une utilisation parfois non triviale
de tout ce qui a été vu avant. Les notions abordées sont nombreuses et je ne
vous conseille pas de lire tout ce tutoriel d'un coup, mais plutôt de piocher
dedans ce qui vous intéresse.

Pêle-mêle, on trouve : compiler un programme avec une librairie externe,
compiler une librairie, le fonctionnement de la compilation en C, l'outil make,
la librairie alloc, mémoire heap et stack, l'usage de struct, enums et unions,
programmation sûre ("safe"), des mentions d'héritage et d'inversion de
dépendances (ou plutôt de leur absence) et enfin l'écriture de langages de
programmation avec un lexer et un parser (c'est une mention très appuyée).

Le support de ce tutoriel est d'écrire une calculatrice classique (avec
précédence d'opérateurs) parenthesée.

Notez que cette partie du tutoriel est globalement complexe, avec quelques
éléments 2** mais le gros est plutôt 3*** voire 4****


#                                Parcours

(Vous voyez, je vous avais dis que cette partie finirait par servir ;-) )

Si vous ne faites que le parcours 2**, vous pouvez vous dispenser du gros de
cette partie et ne lire que :

calculatrice.h -> Makefile -> calculatrice.c -> run.sh

Cela devrait vous apporter plusieurs notions intéressantes et peut-être vous
donner l'envie de lire certaines choses dans le reste.



Si vous êtes dans le parcours 3***, vous trouverez des choses intéressantes dans
un peu tous les fichiers mais ne vous focalisez pas trop sur le détail de
l'implémentation, cela est sans importance. L'ordre dans lequel vous devriez
lire les fichiers pour suivre le cours de la partie est :

pile/pile.h -> pile/pile.c -> pile/Makefile
puis faire le parcours 2**

Le reste porte essentiellement sur l'implémentation et sur ses difficultés mais
cela ne vous interessera pas forcément dans un premier temps.



Si vous souhaitez vraiment aller au fond des choses et voir à la fois comment on
peut implémenter du C sûr ("Safe") mais aussi les difficultés rencontrées à
l'implémentation alors vous pourrez, après avoir fait le parcours 3***,
regarder le fichier symbole.c et lire le fichier expression.c.

Même en 4**** je ne vous conseille pas de vous pencher trop sur le détail de
l'implémentation, après tout il est sans importance et ne la plupart du code ne
pourrait pas être réutilisé ailleurs, contrairement aux idées importantes.
