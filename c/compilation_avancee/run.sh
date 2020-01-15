#
#                            LD_LIBRARY_PATH - 2**
#
# Attention : sous Linux, vous devez faire attention à l'endroit où se trouvent
# vos librairies lors de l'exécution. A peu près tous les programmes placent
# leurs librairies dans /usr/lib ou un équivalent car si vous ne faites pas
# cela au moment de lancer votre code votre programme vous dira qu'il ne
# parvient pas à trouver votre librairie.
#
# Cette étape de l'exécution est gérée par un programme nommé ld, et pour régler
# votre problème deux solutions s'offrent à vous : placer la librairie requise
# (libPile.so) dans un emplacement où ld saura aller la chercher (/usr/lib par
# exemple) ou bien dire à ld de venir chercher la librairie requise dans le
# repertoire où elle se trouve (ici le repertoire courant ./)
export LD_LIBRARY_PATH=./:$LD_LIBRARY_PATH


# Pour utiliser la calculatrice vous pouvez juste écrire votre calcul dans le
# fichier exemple et lancer ce programme.
cat exemple | ./calculatrice.elf
