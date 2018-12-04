/*



*/

#define  _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "qdbmp.h"
#include "tuiles.h"

FILE * ouvrir_fich_data(const char * nom_fich, int * nb_tests);

int main(void) {

	// Déclaration des variables
	UCHAR red, green, blue; // Valeur RGB d'un pixel
	t_tuile *tuile;
	t_spectre_gris *gris;
	int nb_tuiles; // Nombre de tuiles de la nouvelle image
	int numero_tuile; // Numéro de la tuile aléatoire
	BMP * original;
	int nb_col, nb_lig, codage, i;
	BMP * nouvelle;
	// la nouvelle image extraite de l'originale
	// et ses valeurs de taille et d'offsets
	
	int col_depart, lig_depart, colons = 0, lignes = 0;

	md_srand();

	original = BMP_ReadFile("image.bmp");
	nb_col = BMP_GetWidth(original);
	nb_lig = BMP_GetHeight(original);
	codage = BMP_GetDepth(original);
	tuile = (t_tuile*)malloc(sizeof(t_tuile));
	assert(tuile != NULL);

	


	for (i = 0; i < 3; i++) {
		do {
			printf("Entrer le nombre de colonnes de la tuile : ");
			scanf("%d", &colons);
		} while (colons < 50 || colons > nb_col);

		do {
			printf("Entrer le nombre de lignes de la tuile : ");
			scanf("%d", &lignes);
		} while (lignes < 50 || lignes > nb_lig);

		calibrer_taille_tuile(original, &colons, &lignes);
		printf("nouvelle colonne: %d    nouvelle ligne: %d\n", colons, lignes);
		nb_tuiles = get_nb_tuiles(original, colons, lignes);
		printf("Nombre de tuiles du recouvrement : %d\n", nb_tuiles);
		init_tuile(colons, lignes, tuile);
		numero_tuile = get_kieme_tuile(original, md_randint(0, nb_tuiles), tuile);
		gris = get_spectre_tuile(original, tuile);
		afficher_spectre(gris);
		/*nouvelle = get_bitmap_tuile(original, tuile);
		copier_tuile_ds_image(original, nouvelle, tuile,titre);
		printf("l'image a ete enregistre sous : %s\n\n", titre);*/
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
			nouvelle = get_bitmap_gris_tuile(original, tuile, 0.2);
			BMP_WriteFile(nouvelle, "GRISway01.bmp");
			BMP_Free(nouvelle);
			break;
		case 2 :
			nouvelle = get_bitmap_tuile(original, tuile);
			BMP_WriteFile(nouvelle, "RGBway02.bmp");
			BMP_Free(nouvelle);
			nouvelle = get_bitmap_gris_tuile(original, tuile, 0.50);
			BMP_WriteFile(nouvelle, "GRISway02.bmp");
			BMP_Free(nouvelle);
			break;
		}
		
	}
	system("pause");
	return 1;
}
FILE * ouvrir_fich_data(const char * nom_fich, int * nb_tests) {

	int nb_ligne;
	FILE *fichier_txt;
	fichier_txt; = fopen(nom_fich, "r")
		if (fichier_txt == null) {
			nb_ligne = -1;
		}
	return 0;
}