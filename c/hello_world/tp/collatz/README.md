# Collatz
La conjecture de Collatz est une célèbre conjecture mathématique qui reste 
encore aujourd'hui à prouver. Pour citer Jeffrey Lagarias (en 2010, source 
Wikipédia) : "C'est un problème extraordinairement difficile, complètement 
hors de portée des mathématiques contemporaines" L'énoncé de cette 
conjecture est très simple :

Pout tout entier a, on définit la suite Ua par récurrence comme :
Ua0 = a
Pour tout n,
	Si Uan est pair, Ua(n+1) sera la moitié de Uan;
	Si Uan est impair, Ua(n+1) sera un plus trois fois Uan;

La conjecture de Collatz stipule que pour tout a entier Naturel, la suite Uan 
converge vers 1.

Le principe de cette exercice est d'implémenter la fonction Collatz qui prend 
en argument un entier a et renvoie la limite de la suite Ua (i.e. si la suite 
atteint 1, on renvoie 1 car 1 est un point fixe de la fonction de récurrence, 
et sinon on renvoie collatz(Ua(n+1)).

L'objectif ensuite est de comparer l'exécutable obtenu en compilant le 
programme avec ou sans optimisations.

Lorsque vous compilerez votre code, vous verrez deux fichiers apparaitre, un 
optimizé nommé collatz.[exe,elf] et un non optimisé nommé 
collatz_debug.[exe,elf].

# Solution

Cette section explique les différences de comportement entre l'exécutable 
obtenu avec ou sans optimisations. Ne la lisez pas avant d'avoir implémenté 
compilé et testé votre programme, sinon vous aurez plus de mal à suivre.

En exécutant les deux programmes vous devriez vous rendre compte que celuis ui 
est optimisé est sensiblement plus rapide que celui qui ne l'ai pas, ce qui 
est le résultat attendu. En revanche ce qui est moins attendu ce sont les 
optimisations effectuées par le compilateur.

Sur ma machine, lorsque l'on réécrit en C ce que fait vraiment le compilateur 
(en lisant le code en assembleur produit, je vous passe ce plaisir) on optient 
ce qui se trouve dans le fichier "optimise.c".

Le commentaire le plus évident à faire là dessus est que dans la version 
optimisée, le compilateur n'appelle jamais la fonction collatz, au lieu de 
cela il assigne juste 1 à result.

Comment est-ce possible ? Alors que la conjecture de Collatz est si difficile 
à déterminer, comment se fait-il que votre compilateur trouve que votre 
fonction Collatz va toujours renvoyer 1 ?

La réponse tient dans la façon dont nous avons écrit notre fonction Collatz. 
Si vous regardez bien, la structure générale de votre code devrait être (en 
pseudo code):

collatz(n)
	Si n vaut 1 -> renvoier 1
	Sinon -> renvoyer collatz(quelque chose)

Les deux comportements possibles pour cette fonction sont donc :
 - Renvoyer 1 au bout d'un certain temps
 - Itérer indéfiniment et ne jamais renvoyer

L'optimisation utilisée par le compilateur est que dans le standard du C, il 
est écrit que le compilateur peut supposer que pour toute fonction :
 - Soit elle renvoie une valeur
 - Soit elle modifie sont contexte par effet de bord (avec des printf par 
exemple)

Or ici le compilateur remarque que collatz n'a pas d'effet de bord, et la seule 
valeur qu'elle peut renvoyer est 1 d'après son code, donc on peut 
complètement remplacer l'appel à la fonction collatz par une simple 
assignation.

De l'autre côté la version non optimisée de collatz fait bien ce que vous 
avez écrit, du coup on pourrait s'étonner que l'écart de temps d'exécution 
ne soit pas plus grand (sur ma machine la version optimisée est dix fois plus 
rapide que la version non optimisée). La raison à cela est probablement que 
les processeurs sont très rapides pour effectuer ce genre de calculs, donc 
même la version non optimisée reste rapide.

Moralité de l'histoire :
 - Si vous écrivez du code pour faire une preuve mathématique (ou autre chose 
semblable) vérifiez que le compilateur ne vous coupe pas l'herbe sous le pied;
 - Sinon laissez le compilateur gérer les optimisations pour vous et ne vous 
en faites pas trop si vous écrivez du code qui n'est pas parfaitement 
optimisé.
