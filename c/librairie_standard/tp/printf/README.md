# printf

printf est une fonction fondamentale de la librairie standard du C et est 
notoirement difficile à réimplémenter entièrement. Dans le cadre de ce TP, 
nous allons nous contenter de réimplémenter une fonction printf qui accepte 
dans sa chaîne de format :
 - des %d pour afficher des entiers
 - des %s pour afficher des chaînes de caractères
 - pas de % isolés dans la chaîne

La méthode que l'on demande d'utiliser pour implémenter printf est de 
s'appuyer sur la fonction putchar (qui affiche un caractère sur l'output). Ce 
n'est pas la seule façon de faire, mais cette méthode est plus simple et 
correspond à ce qui serait fait par exemple sur un micro-controlleur sans OS 
qui afficherait des messages par la liaison série.

Afin d'implémenter votre fonction printf (nommée printf\_c pour éviter les 
conflits de nom), on vous propose de commencer par écrire une fonction printi 
qui affiche l'entier passé en argument sur l'output. Pour implémenter cette 
fonction, vous pourrez avantageusement vous appuyer sur le fait qu'un nombre 
qui s'écrit (par exemple) 156 vaut 1\*10^2 + 5\*10^1 + 6\*10^0. Pensez aussi 
à gérer le signe de l'argument.

Ensuite pour le corps de votre fonction printf vous aurez deux choses à gérer 
:
 - Le fait que ce soit une fonction variadique (il faudra donc utiliser 
va\_arg, va\_start etc...)
 - La lecture de la chaîne de format, je vous recommande de chercher sa taille 
en utilisant la fonction dédiée de la librairie standard, puis de la 
parcourir caractère par caractère.
 - Pour afficher des entiers, vous pouvez utiliser la fonction printi que vous 
aurez écrit, et pour afficher des chaînes de caractères vous pourrez 
utiliser la fonction dédiée de la librairie standard (si jamais vous ne la 
retrouvez pas vous pouvez toujours faire des putchar mais cela risque d'être 
un peu plus délicat.
 - Notez que la gestion des "\n" est faite automatiquement par votre terminal 
au moment de l'affichage, vous n'avez pas à vous en soucier.
