#                                Contenu

Ce dossier fait partie de l'épilogue du tutoriel sur le C et porte sur le
langage Rust. Il a pour but de montrer dans quelle mesure le Rust peut-être
considéré comme une alternative au C ou au C++ pour un projet.

Le support de ce tutoriel est le même que pour le C++ : il s'agit d'écrire un
programme qui prenne en entrée une liste de mots séparés par des retours à la
ligne et renvoie ses mots triés dans l'ordre alphanumérique séparés par des
retours à la ligne.

Même si ce code ne réutilise pas ce qui avait été écrit pour le type pile en C,
pour des raisons de symétrie j'ai décidé de réutiliser la même implémentation
pour faire le tri (vous pouvez en lire le détail dans le README.md du dossier
C++).

Notez que pour compiler ce code vous aurez besoin du compilateur Rust en plus
des objets habituels (évidemment), il se nomme rustc et vous pouvez l'obtenir
soit seul soit avec rustup sur le site officiel du langage https://rust-lang.com
