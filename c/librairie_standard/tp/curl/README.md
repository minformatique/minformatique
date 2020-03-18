# cURL

cURL (prononcé comme cela s'écrit) est un outil en ligne de commande extrèmement pratique. Il s'agit à l'origine d'une librairie (libcurl) en C pemettantde faire des requètes HTTP GET sur le web en donnant un URL (d'où le nom "C" "URL").

Cette librairie (que vous pouvez par ailleurs utiliser dans vos programmes si vous le souhaitez) a donné naissance à l'outil en ligne de commande curl, qui est le sujet de cet exercice. Le but de ce TP est d'utiliser curl en ligne de commande pour télécharger un fichier sans avoir à écrire de code en C complexe.

Le fichier que vous devrez télécharger est le .zip du dépôt GitHub du min'formatique. L'URL pour télécharger ce .zip avec curl est le même que celui que vous utiliseriez dans votre navigateur. Actuellement cet url est https://github.com/minformatique/minformatique/archive/master.zip . Vous pouvez l'ouvrir dans votre navigateur, normalement cela devrait vous ouvrir une fenètre qui vous demande de confirmer si vous voulez télécharger l'archive (il s'agit d'une sécurité supplémentaire mise en place sur les navigateurs web dont curl n'a pas besoin).

Attention, la commande à utiliser pour télécharger n'est pas la même sous Linux et sous Windows :

## Linux

Sous Linux, pour utiliser curl vous aurez trois choses à gérer :
 - Trouver la syntaxe de base pour télécharger un fichier. Vous pouvez la chercher en utilisant l'URL de l'archive GitHub.
 - Une fois que vous aurez trouvé cette syntaxe, normalement github devrait vous renvoyer une redirection. C'est à dire que pour pouvoir télécharger le fichier vous devez suivre cette redirection. Je vous laisse chercher dans la docuentation de curl comment faire.
 - Une fois que vous aurez trouvé comment suivre la redirection, par défaut curl affiche ce qu'il télécharge sur l'output, mais il refusera d'afficher un message binaire (comme le fichier .zip) sur votre terminal. Là aussi vous devrez chercher dans la documentation de curl comment sauvegarder ce que vous avez récupéré dans un fichier (ce n'est pas très compliqué).

Note : curl affiche un belle barre de progression sur stderr pendant que vous téléchargez un fichier. Essayez de faire en sorte que votre application affiche aussi cette barre de progression.

Vous pouvez aussi adapter cet exercice pour wget si vous ne souhaitez pas utiliser curl pour une raison ou une autre.
