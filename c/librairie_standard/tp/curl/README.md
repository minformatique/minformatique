# cURL

cURL (prononcé comme cela s'écrit) est un outil en ligne de commande 
extrèmement pratique. Il s'agit à l'origine d'une librairie (libcurl) en C 
pemettantde faire des requètes HTTP GET sur le web en donnant un URL (d'où le 
nom "C" "URL").

Cette librairie (que vous pouvez par ailleurs utiliser dans vos programmes si 
vous le souhaitez) a donné naissance à l'outil en ligne de commande curl, qui 
est le sujet de cet exercice. Le but de ce TP est d'utiliser curl en ligne de 
commande pour télécharger un fichier sans avoir à écrire de code en C 
complexe.

Le fichier que vous devrez télécharger est le .zip du dépôt GitHub du 
min'formatique. L'URL pour télécharger ce .zip avec curl est le même que 
celui que vous utiliseriez dans votre navigateur. Actuellement cet url est 
https://github.com/minformatique/minformatique/archive/master.zip . Vous pouvez 
l'ouvrir dans votre navigateur, normalement cela devrait vous ouvrir une 
fenètre qui vous demande de confirmer si vous voulez télécharger l'archive 
(il s'agit d'une sécurité supplémentaire mise en place sur les navigateurs 
web dont curl n'a pas besoin).

Attention, la commande à utiliser pour télécharger n'est pas la même sous 
Linux et sous Windows :

## Linux

Sous Linux, pour utiliser curl vous aurez trois choses à gérer :
 - Trouver la syntaxe de base pour télécharger un fichier. Vous pouvez la 
chercher en utilisant l'URL de l'archive GitHub.
 - Une fois que vous aurez trouvé cette syntaxe, normalement github devrait 
vous renvoyer une redirection. C'est à dire que pour pouvoir télécharger le 
fichier vous devez suivre cette redirection. Je vous laisse chercher dans la 
docuentation de curl comment faire.
 - Une fois que vous aurez trouvé comment suivre la redirection, par défaut 
curl affiche ce qu'il télécharge sur l'output, mais il refusera d'afficher un 
message binaire (comme le fichier .zip) sur votre terminal. Là aussi vous 
devrez chercher dans la documentation de curl comment sauvegarder ce que vous 
avez récupéré dans un fichier (ce n'est pas très compliqué).

Note : curl affiche un belle barre de progression sur stderr pendant que vous 
téléchargez un fichier. Essayez de faire en sorte que votre application 
affiche aussi cette barre de progression.

Vous pouvez aussi adapter cet exercice pour wget si vous ne souhaitez pas 
utiliser curl pour une raison ou une autre.

## Windows

Sous les versions de windows les plus récentes, il semblerait que cURL soit installé par défaut, mais je n'en suis pas absolument certain. Si cURL est insatllé sur votre machine vous pouvez l'utiliser pour faire ce TP.

Sinon, comme souvent sous Windows, vous devrez utiliser Powershell pour résoudre cela. Powershell est une ligne de commande enrichie introduite sous Windows 2006, donc qui devrait être présente sous à peu près toutes les machines Windows. Ce powershell comporte beaucoup d'outils en ligne de commande très utile qui vous permettent de faire sous Windows ce vous souhaiteriez faire sous Linux. Deux informations importantes à ce sujet :
 - La ligne de commande native de Windows (cmd.exe) est un vrai désert, n'essayez pas de chercher si vous pouvez vous en sortir avec la réponse est sans doute non. Sous Windows, 90% du temps pour faire des choses avec la ligne de commande il faut passer par Powershell.
 - Powershell est mieux que cmd.exe, mais cela ne signifie pas qu'il est bon pour autant. La syntaxe du powershell, la gestion du texte etc... sont vraiment pénibles. Par ailleurs, Powershell peut parfois être extrêmement long à se lancer (jusqu'à 2mn au démarrage sur ma machine ...).
 - Des versions plus modernes de powershell (utilisant le .net core) sont disponibles, mais pas installées par défaut sous Windows. C'est à dire que la version du powershell que vous avez sur votre machine est assez obsolète.

Néanmoins, Powershell peut vous aider à réaliser des tâches rapidement (au sens "avec peu de lignes de code") sous Windows. Sous Powershell, l'outil à utiliser pour télécharger des fichiers est Invoke-WebRequest, avec trois alias : iwr (celui que je vous recommande), curl et wget ! Attention donc, si vous tapez curl sous powershell, la version de curl que vous aurez ne sera sans doute pas celle de libcurl, mais juste un alias de Invoke-WebRequest qui se comportera différemment.

Pour réaliser cet exercice, deux approches sont possible :
 - Utiliser la librairie standard du C pour faire l'appel à iwr en une ligne. Cela reviendra à demander à cmd.exe de demander à powershell de demander à Invoke-WebRequest de télécharger un fichier. Je ne vous recommande pas cette approche car vous risquez d'avoir des problème de caractères spéciaux dans les chaines de caractères (qui ne sont pas les mêmes dans cmd.exe et dans powershell) ce qui vous obligera à mettre de multiples escape dans vos chaines de caractère. Si vous souhaitez utiliser cette approche, je vous recommande de regarder la documentation de "powershell" et de "powershell -Command" en particulier (vous pouvez l'obtenir en tapant "powershell -h" dans votre invite de commande. 
 - Utiliser la librairie standard du C pour écrire un fichier .psl dans lequel vous écrirez la commande que vous taperiez normalement sous powershell, puis demander powershell d'exécuter ce fichier, et enfin de supprimer le fichier .psl . Cette solution n'est pas très satisfaisante, mais elle pourrait être un peu plus simple en pratique. Si vous choisissez cette approche regardez la documentation de "powershell -File" (vous pouvez aussi l'obtenir en tapant "powershell -h" dans votre invite de commande.

Quelque soit l'approche que vous choisirez, je vous recommande de d'abord essayer (en ligne de commande) de télécharger le fichier "à la main" en utilisant iwr depuis l'invite de commande Powershell. Cela vous aidera à résoudre tous les problèmes liés à iwr (comme sous Linux, il faut suivre les redirections etc...). Cela vous évitera d'avancer à l'aveugle ensuite.

Petite information annexe : si faire cette tâche sous windows est infiniment plus difficile que sous Linux, c'est parce que dans l'optique de Microsoft vous n'êtes pas censé développer des applications pour Windows comme cela. Vous êtes censé utiliser le C# et faire toutes vos manipulations à travers le .Net Framework ou le .Net Core (qui sont des sortes de JVM écrites par Microsoft) ou éventuellement utiliser un autre framework.
