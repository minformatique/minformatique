# PPP
Le protocole PPP ("Point-to-Point Protocol") est un protocole de communication 
assez ancien mais encore utilisé aujourd'hui. Il s'agit d'un protocole de 
transmission de donnée (i.e. layer 2 dans la pile de proctocole du modèle OSI 
pour ceux que cela intéresse). Il sert à transmettre des données par paquets 
entre deux machines distantes.

Un paquet ppp est toujours srtucturé de la même façon, à savoir :
 - Un octet marquant le début du paquet, toujours 0x7E
 - Un octet marquant l'adresse de destination, qui est toujours 0xFF en PPP
 - Un octet de contrôle (utile pour des considérations matérielles), 
toujours 0x03
 - Deux octets qui décrivent le proctocole des données embarquées dans le 
paquet PPP. Dans le cadre de ce TP on mettra directement une chaîne de 
caractères dans les données du paquet, et donc les deux octets de protocole 
seront fixés arbitrairement à 0xFF 0xFF
 - Les données du paquet à proprement parlé, qui feront au plus 1500 octets 
et ne contiendront pas de 0x7E dans ce TP
 - Une checksum de deux octets. Dans ce TP cette checksum sera à vérifier, et 
l'algorithme est celui de l'octet de parité, qui est décrit plus loin.
 - Un octet de terminaison, toujours 0x7E. Dans le vrai proctocole PPP cet 
octet ne serait pas répété entre les paquets, mais ici pour simplifier ce 
sera le cas.

## Algorithme de l'octet de parité
L'algorithme de l'octet de parité est un algorithme assez simple qui vérifie 
partiellement l'intégrité des données. L'idée est de choisir une longueur 
de mot (2 octets dans notre cas) puis de faire un xor (opérateur ^ en C) de 
tous les blocs de longueur de mot dans nos données. On ajoute le résultat 
obtenu comme checksum à la fin de notre message.

Un exemple pour clarifier les choses. Supposons que l'on transmette le message 
"rouge". On crée un buffer de 2 octets nommé buffer. L'algorithme à 
aplliquer est alors :
 - Etape 1 : On initialise le buffer (on écrit "ro" dans le buffer)
 - Etape 2 : On calcule le xor du buffer avec le mot suivant du buffer, ici le 
xor de "ro" avec "ug". On note le résultat (ici \7 \8) dans buffer.
 - Etape 3 : On fait de même pour la suite du mot (on complète le caractère 
manquant avec des 0 par convention). On calcule donc le xor de ce qui se trouve 
dans le buffer avec "e\0" et on inscrit le résultat dans buffer. Ici le 
résultat est \62 \8.
 - Etape 4 : On envoie le message avec écrit dedans "rouge\62\8".

Pour vérifier la checksum, on reproduit à peu près la même logique : On 
note la checksum dans une variable, on recalcule la checksum à partir de ce 
que l'on a obtenu puis on calcule (checksum calculée) xor (checksum envoyée). 
Si les deux checksum sont égales le résultat sera \0 \0, sinon cela signifie 
que le paquet est corrompu. Si un paquet dans ce TP est corrompu on se 
contentera de l'ignorer.

## IMPORTANT
Dans le cadre de cet exercice, on a fixé la taille des données transmises à 
250 octets, donc dans chaque paquet vous aurez 250 octets de données en plus 
de l'en-tête, de la checksum etc...

# But de l'exercice
Dans cette exercice, on suppose que votre recepteur PPP a déjà fait son 
travail et a déjà récupéré les données de la communications, qu'il 
stockées dans le fichier communication.ppp . Votre but est de récupérer les 
données qui se trouvent dans ces paquets ppp en respectant le protocole. 
N'oubliez pas de jeter tous les paquets dont la checksum n'est pas correcte.

Pour vous aider, une approche qui pourrait vous servir est de d'abord définir 
une structure PPP qui décrive un paquet PPP. Notez que pour vous simplifier la 
tâche, tous les paquets de données envoyés feront exactement 250 octets, 
comme cela votre structure sera bien formé et plus facile à utiliser (ce 
n'est pas le cas en pratique avec le protocole PPP, évidemment). Notez que ces 
250 octets ne représentent que le bloc de données embarquées dans le paquet, 
pas ce qui va autour.

Pour lire les données du fichier je vous conseille de lire tous les paquets 
depuis le fichier en utilisant fread (vous pouvez regarder cette fonction sur 
internet ou dans le tutoriel sur la librairie standard).
