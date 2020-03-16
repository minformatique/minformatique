#                                   Contenu

Ce dossier constitue le corps du tutoriel sur le langage C et ses usages. Je ne
recommande à personne de lire tout le tutoriel d'un coup, et pour que vous
puissiez profiter au maximum du tutoriel nous avons établi deux façons de s'en
servir : soit en suivant un parcours, soit en utilisant l'index (qui se trouve
dans le fichier INDEX.md).

Le fichier SETUP.md liste les outils dont vous aurez probablement besoin pour
mettre en place votre environnement de développement en C afin de suivre ces
tutoriels et expérimenter par vous même.

Notez que sur chaque fichier, la difficulté des notions abordées en commentaire
est précisée afin que vous puissiez passer ce qui ne vous intéresse pas.

Dans la mesure où la plupart des tutoriels ont été écrits pour Linux et pour
Windows, vous trouverez tout en double dans les dossiers des tutoriels.
Par convention (remplacer foo en fonction du contexte):
 - foo.c désigne le code source pour Linux;
 - foo_w.c désigne le code source pour Windows;
 - "make linux" est la commande à utiliser pour compiler sous Linux;
 - "make windows" est la commande à utiliser pour compiler sous Windows;

Les exercices se trouvent dans les sous-dossiers "tp" des différents tutoriels.

<h3>IMPORTANT SOUS WINDOWS</h3>
Si vous suivez le tutoriel sous windows vous devriez rapidement voir que les
exécutables que vous compilez sont très longs à s'exécuter. Cela est dû aux
antivirus sous windows, qui effectuent un scan complet du fichier que vous
demandez d'exécuter (car ce dernier n'est pas signé, longue histoire ...).

En fait avant de lancer votre fichier pour de vrai, l'antivirus va le faire
tourner un peu dans un conteneur (une sandbox précisément) pour voir s'il fait
quelque chose de suspect. Votre programme ne s'exécutera qu'une fois l'analyse
terminée. Notez aussi que si vous faites trop de fautes dans vos programmes en
C (en particulier l'usage de fonctions marquées "insecure"), il se peut que
votre antivirus détruise préventivement le programme que vous venez de
compiler.

Pour la petite histoire, la raison pour laquelle cela n'arrive pas en Java
ou en Python est que votre code est exécuté au sein d'une autre application
(la JVM et l'interpréteur python respectivement) qui est elle bien signée
(i.e. publiée par des gens de confiance).

#                                   Parcours

Plusieurs parcours sont proposés pour ce tutoriel, triés par difficulté et temps
de lecture croissants. Notez qu'au sein de chacune des parties de ce tutoriel
vous trouverez à nouveau des mini parcours et des index vous aidant à trouver
les informations plus vite.

Les quatres parcours proposés sont :


##   1* : "J'ai trouvé une offre de stage en finance avec le prérequis C/C++"

Pas forcément un grand adepte de l'informatique en général, vous cherchez juste
une rapide introduction au C afin de savoir quoi dire si on vous en parle, ou
pour voir si cela vous plaît. Le parcours le plus adapté est alors :

hello_world -> pointeurs -> structures_avancées -> c_must_die (juste le C++)

Cela vous donnera une rapide vue de ce qu'est le C et de son lien avec le C++



##   2** : "Je dois faire du C pour le projet de groupe"

Le traquenard ultime. On vous avait promis qu'après la prépa l'école
d'ingénieur serait facile, mais vous enchainez les projets de groupe
exténuants. Encore ce matin, les dix membres de votre groupe en réunions
écoutent le tuteur du projet:

- "Qui sait programmer en C ici ?"

Silence glaçant. La plupart des membres manient le pipo plus que le clavier
d'ordinateur, et la moitié liste pour le BDE et va disparaitre du projet après
cette réunion.

- "Bon, vous êtes là pour apprendre après tout" renchérit innocemment le
tuteur. "Qui est à l'aise en informatique ?"

Les regards insistants du groupe se tournent vers vous. Vous êtes dans le
troisième groupe d'informatique et tous le savent. Tout cela parce que vous avez
mis dans le questonnaire de début d'année que vous avez "aimé faire beaucoup de
Python pendant la prépa" et que vous êtes "motivés par les sujets d'intelligence
artificielle". Vous auriez définitivement dû faire le sous-marin, comme les
autres MP info du groupe. Le coeur serré, vous levez la main et abandonnez vos
jeudi après midi à la programmation de bas niveau.


Si telle est votre situation, le parcours le plus adapté est :

hello_world -> pointeurs -> librairie_standard -> structures_avancées ->
compilation_avancée (seulement quelques bribes) -> c_must_die (juste le C++)

Sans faire de vous un expert, cela devrait vous permettre d'écrire des
programmes simples et de faire avancer ce que vous avez en tête.



##   3*** : "J'ai du temps, il y a sport demain matin"

Adepte de l'informatique, vous connaissez sans doute déjà plusieurs langages
de programmation et souhaitez ajouter une nouvelle corde à votre arc. Vous
êtes déjà famillier des bonnes pratiques en développement et êtes capables
d'identifier avec une certaine autonomie les étapes à suivre pour résoudre un
problème d'informatique. Si ce que vous cherchez est une réflexion sur le C et
ce qui le distingue des autres langages, alors le parcours recommandé est :

hello_world -> pointeurs -> librairie_standard -> structures_avancées ->
compilation_avancée -> etats_indefinis -> c_must_die

Cela devrait vous éclairer sur les raisons de choisir (ou non) le C pour un
projet, et vous donner quelques clefs pour argumenter vos choix. Cela vous
offrira je l'espère aussi une réflexion sur les langages que vous connaissez
déjà.



##   4**** : "A part l'informatique tous les cours sont pipos de toute façon"

Il y a déjà longtemps que vous avez pénétré dans les terres arides de
l'informatique théorique, à tel point que vous ne sauriez même plus dire ce qui
vous a poussé à suivre cette voie. Aujourd'hui vous n'êtes plus un programmeur
informatique, vous êtes programmé pour faire de l'informatique. Votre corps se
compose à 80% de pâtes au beurre et de pizzas; votre chambre comporte plus de
raspberry pis que de vêtements propres.

Dernier bastion encore inconquis, le C, ancien, plus enseigné en cours et dont
le temps a en partie effacé la documentation. Python est écrit en C, Java
s'inspire du C, le C++ est une tentative de faire mieux que le C...
Toutes les pistes mènent au C, et vous cherchez à comprendre en profondeur le C
pour ce qu'il a d'originel et de structurant sur ses successeurs.

Mais avant de vous engager sur ce chemin tortueux, peut-être est-il temps de se
poser les bonnes questions. Ce temps que vous allez passer à apprendre les
rouages du C, ne serait-il pas mieux utilisé à vous détendre, ou à faire du
sport (ou autre) avec vos amis? Ne devriez vous pas plutôt diversifier vos
centres d'intérêts et prêter plus d'attention aux cours d'économie ou de
physique pour y apprendre des choses plus utiles ?

Si malgré mes avertissements vous souhaitez poursuivre cette voie, alors
enfoncez vous les notions subtiles du langage de Kernighan et Ritchie en
suivant le parcours :

hello_world -> pointeurs -> librairie_standard -> structures_avancées ->
compilation_avancée -> etats_indefinis -> c_must_die
