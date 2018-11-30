/*



*/

#define  _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "qdbmp.h"
#include "tuiles.h"


int main(void) {

	// D�claration des variables
	UCHAR red, green, blue; // Valeur RGB d'un pixel
	t_tuile *tuile;
	int nb_tuiles; // Nombre de tuiles de la nouvelle image
	int numero_tuile; // Num�ro de la tuile al�atoire
	BMP * original;
	int nb_col, nb_lig, codage;

	// la nouvelle image extraite de l'originale
	// et ses valeurs de taille et d'offsets
	BMP * nouvelle;
	int col_depart, lig_depart, colons = 0, lignes = 0;

	// les itarateurs matriciels des pixels de l'image
	int  pos_x, pos_y;

	md_srand();

	original = BMP_ReadFile("image.bmp");

	do {
		printf("Entrer le nombre de colonnes de la tuile : ");
		scanf("%d", &colons);
	} while (colons < 50 || colons > 1500);

	do {
		printf("Entrer le nombre de lignes de la tuile : ");
		scanf("%d", &lignes);
	} while (lignes < 50 || lignes > 1500);

	tuile = (t_tuile*)malloc(sizeof(t_tuile));
	init_tuile(colons, lignes, tuile);
	nb_tuiles = get_nb_tuiles(original, colons, lignes);
	printf("Nombre de tuiles : %d\n", nb_tuiles);
	numero_tuile = get_kieme_tuile(original, md_randint(0, nb_tuiles),tuile);
	printf("Numero de tuiles : %d\n", tuile->id_enum);
	




	system("pause");
	return 1;
}