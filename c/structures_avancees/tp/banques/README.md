# Banques

Le TP sur les banques est un classique du cours de Java du CRI des Mines de 
Paris (que la plupart d'entre vous ont dû suivre), je vous propose de le 
refaire en C afin que vous sentiez dans quel mesure les structs du C se 
substituent aux objets en Java et en quoi leur utilisation peut être 
différente.

Pour ce TP, il faut définir une structure "Compte" avec deux attributs :
 - Le solde, un entier
 - Le nom du titulaire (attention à la gestion de la mémoire !)

Les fonctions que vous devez définir sont :
 - Un "constructeur" (i.e. une fonction qui initialise la structure) nommé 
"compte"prenant en argument un nom de titulaire et un versement initial;
 - Un autre "constructeur" nommé "compten" qui ne prenne en argument que le 
nom du titulaire et crée un compte avec un solde vide;
 - Un routine "afficher" permettant d'afficher les informations sur un compte 
bancaire;
 - Une routine pour déposer de l'argent sur un compte nommé "depose" qui 
prend en argument le montant à déposer;
 - Une routine pour retirer de l'argent d'un compte nommé "retire" qui prend 
en argument le montant à retirer;
 - Une routine "transfert" permettant de transférer de l'argent d'un compte à 
un autre;
 - Créer un nouveau type de compte avec plafond (i.e. on ne peut pas déposer 
plus d'argent que le plafond indiqué) nommé ComptePlafond. Faire les 
modifications nécessaires pour pouvoir transférer de l'argent d'un compte 
avec plafond vers un compte sans plafond. On ne demande pas de réécrire les 
autres routines. Ce plafond sera dépendant du compte et initialisé à la 
création du compte grâce à la routine "comptep". La routine pour transférer 
de l'argent d'un compte sans plafond vers un compte avec plafond sera 
"transfertp".

Toutes ces fonctions peuvent être testées avec le main fourni.
