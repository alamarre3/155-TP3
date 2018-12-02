/*



*/

#define  _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "qdbmp.h"
#include "tuiles.h"


int main(void) {

	// Déclaration des variables
	UCHAR red, green, blue; // Valeur RGB d'un pixel
	t_tuile *tuile;
	t_spectre_gris *gris;
	int nb_tuiles; // Nombre de tuiles de la nouvelle image
	int numero_tuile; // Numéro de la tuile aléatoire
	BMP * original;
	int nb_col, nb_lig, codage, i;


	// la nouvelle image extraite de l'originale
	// et ses valeurs de taille et d'offsets
	BMP * nouvelle;
	int col_depart, lig_depart, colons = 0, lignes = 0;

	md_srand();

	original = BMP_ReadFile("image.bmp");
	codage = BMP_GetDepth(original);
	tuile = (t_tuile*)malloc(sizeof(t_tuile));
	assert(tuile != NULL);

	for (i = 0; i < 3; i++) {
		do {
			printf("Entrer le nombre de colonnes de la tuile : ");
			scanf("%d", &colons);
		} while (colons < 50 || colons > 1500);

		do {
			printf("Entrer le nombre de lignes de la tuile : ");
			scanf("%d", &lignes);
		} while (lignes < 50 || lignes > 1500);

		nb_tuiles = get_nb_tuiles(original, colons, lignes);
		printf("Nombre de tuiles du recouvrement : %d\n", nb_tuiles);
		init_tuile(colons, lignes, tuile);
		numero_tuile = get_kieme_tuile(original, md_randint(0, nb_tuiles), tuile);
		gris = get_spectre_tuile(original, tuile);
		afficher_spectre(gris);
		switch (i) {
		case 0:
			nouvelle = get_bitmap_tuile(original, tuile);
			BMP_WriteFile(nouvelle, "RGBway00.bmp");
			BMP_Free(nouvelle);
			nouvelle = get_bitmap_gris_tuile(original, tuile, 0);
			BMP_WriteFile(nouvelle, "GRISway00.bmp");
			BMP_Free(nouvelle);
			break;
		case 1 :
			nouvelle = get_bitmap_tuile(original, tuile);
			BMP_WriteFile(nouvelle, "RGBway01.bmp");
			BMP_Free(nouvelle);
			nouvelle = get_bitmap_gris_tuile(original, tuile, 0);
			BMP_WriteFile(nouvelle, "GRISway01.bmp");
			BMP_Free(nouvelle);
			break;
		case 2 :
			nouvelle = get_bitmap_tuile(original, tuile);
			BMP_WriteFile(nouvelle, "RGBway02.bmp");
			BMP_Free(nouvelle);
			nouvelle = get_bitmap_gris_tuile(original, tuile, 0);
			BMP_WriteFile(nouvelle, "GRISway02.bmp");
			BMP_Free(nouvelle);
			break;
		}
		
	}
	system("pause");
	return 1;
}