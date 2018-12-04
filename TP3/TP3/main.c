/*



*/

#define  _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qdbmp.h"
#include "tuiles.h"


int main(void) {

	// D�claration des variables
	t_tuile *tuile; // Pointeur vers une tuile
	t_spectre_gris *gris; // Pointeur vers un spectre
	int nb_tests; // Nombre de tests � effectuer
	int colonnes, lignes; // Taille de la nouvelle image
	int nb_tuiles; // Nombre de tuiles de la nouvelle image
	int numero_tuile; // Num�ro de la tuile al�atoire
	int i; // Valeur d'incr�mentation
	BMP * original;
	int nb_col, nb_lig, codage;
	BMP * nouvelle;

	md_srand();

	for (i = 0; i < nb_tests, i++) {

		original = BMP_ReadFile("image.bmp");
		codage = BMP_GetDepth(original);
		tuile = (t_tuile*)malloc(sizeof(t_tuile));
		assert(tuile != NULL);

		calibrer_taille_tuile(original, colonnes, lignes);
		
		nb_tuiles = get_nb_tuiles(original,
		printf("Nombre de tuiles du recouvrement : %d\n", nb_tuiles);
		init_tuile(, tuile);
		numero_tuile = get_kieme_tuile(original, md_randint(0, nb_tuiles), tuile);
		gris = get_spectre_tuile(original, tuile);
		afficher_spectre(gris);
		/*nouvelle = get_bitmap_tuile(original, tuile);
		copier_tuile_ds_image(original, nouvelle, tuile,titre);
		printf("l'image a ete enregistre sous : %s\n\n", titre);*/
		/*switch (i) {
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
		}*/

		//}


	}
		
	system("pause");
	return 1;
}