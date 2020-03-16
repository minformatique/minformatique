/*
################################################################################
################## Première partie du programme : les inclusions ###############
################################################################################
*/

#include <stdio.h> 	// Utile dans le main pour afficher des résultats

/*
################################################################################
################## Deuxième partie du programme : les prototypes ###############
################################################################################
*/

// Renvoie le pgcd de a et b.
unsigned pgcd(unsigned a, unsigned b);

/*
################################################################################
##################### Troisième partie du programme : le main ##################
################################################################################
*/

int main(int argc, char *argv[]) {
	unsigned a = 6;
	unsigned b = 9;
	printf("Calcul du pgcd de %d et %d\n", a, b);
	unsigned c = pgcd(a,b);
	printf("Le pgcd trouvé est %d.\n", c);
	if (c == 3) {
		printf("%s\n", "C'est le bon résultat.");
	}
	else {
		printf("%s\n", "Ce n'est pas le bon résultat, echec du test.");
		return -1;
	}
	a = 51;
	b = 17;
	printf("Calcul du pgcd de %d et %d\n", a, b);
	c = pgcd(a,b);
	printf("Le pgcd trouvé est %d.\n", c);
	if (c == 17) {
		printf("%s\n", "C'est le bon résultat.");
	}
	else {
		printf("%s\n", "Ce n'est pas le bon résultat, echec du test.");
		return -1;
	}
	a = 1;
	b = 104;
	printf("Calcul du pgcd de %d et %d\n", a, b);
	c = pgcd(a,b);
	printf("Le pgcd trouvé est %d.\n", c);
	if (c == 1) {
		printf("%s\n", "C'est le bon résultat.");
	}
	else {
		printf("%s\n", "Ce n'est pas le bon résultat, echec du test.");
		return -1;
	}
	printf("%s\n", "Les tests (sommaires) se sont bien passés, l'implémentation de pgcd semble correcte.");
	return 0;
}

/*
################################################################################
############# Dernière partie du programme : les fonctions annexes #############
################################################################################
*/

unsigned pgcd(unsigned a, unsigned b) {
	// Code à compléter ...
	return 0;
}
