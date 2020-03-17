# Safe C

Si vous avez écrit quelques programmes en C vous avez rapidement du vous 
apercevoir de quelque chose : le C a une forte propension à faire absolument 
n'importe quoi.

J'en ai pas mal détaillé la raison dans le tutoriel sur les état indéfinis, 
mais pour faire court le problème est que même lorsqu votre programme 
rencontre une erreur il n'a pas de moyen de vous le faire savoir car 
contrairement à Python ou Java, il n'y a pas de vrai mécanisme d'erreur en C.

Certains langages modernes (Rust en tête) ont approté une solution assez 
élégante pour créer un système de gestion d'erreur qui ne ralentisse pas 
trop l'exécution et soit assez agréable à utiliser : les valeurs 
optionnelles.

L'idée est assez simple. Prenons une fonction simple qui peut rencontrer une 
erreur, par exemple la division :

float div(const float a, const float b);	// Calcule a/b

Que doit faire cette fonction si b est 0 ? Elle ne peut pas renvoier de code 
d'erreur car toute valeur flottante peut être un résultat légitime de la 
division, et elle ne peut pas lancer d'exception car il n'y a pas d'exception 
en C.

La démarche habituelle en C serait d'écrire cette fonction comme :

int div(const float a, const float b, float \*c);	// \*c = a/b;

Mais cette syntaxe est plus lourde et rapidement assez pénible à gérer. La 
solution proposée par le rust est de définir un type Result\_float (il n'y a 
pas de template en C, ce qui rend cette approche moins généralisable) et 
d'écrire notre fonction comme :

Result\_float div(const float a, const float b);

Ce Result\_float serait un type capable de représenter soit un flottant en cas 
de succès, soit une erreur (on aura donc besoin d'une union). Notez cependant 
que notre Result\_float n'est pas un flottant, et donc pour le récupérer on 
peut utiliser une fonction comme :

float unwrap(const Result\_float c);

Cette fonction va renvoyer le flottant si c contient bien et flottant, et faire 
aborter le programme avec un message sinon. Pour que cela fonctionne, il faut 
donc que Result\_float comporte un enum qui indique s'il contient un float ou 
une erreur (sinon unwrap ne saura pas quoi faire).

Notez que si l'on ne programme que cette fonction, utiliser un unwrap n'a pas 
beaucoup d'intérêt. Une autre idée est d'écrire une fonction telle que :

int match(const Result\_float c);

Qui renvoie 1 (true) si c contient un flottant et 0 (false) sinon. Cela 
permettra de faire une gestion d'erreur plus fine.

Ceux d'entre vous qui ont déjà fait du Rust ne manqueront pas de remarquer 
que c'est ainsi que le langage gère les erreurs.

Le but de ce tutoriel est de définir Result\_float et d'implémenter les 
fonctions div, unwrap et match décrites dans ce fichier. Je vous ai déjà 
fourni un main dans le code en C.
