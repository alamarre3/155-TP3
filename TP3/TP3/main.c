/*



*/

#define  _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qdbmp.h"
#include "tuiles.h"
#include "recouvrement.h"

FILE * ouvrir_fich_data(const char * nom_fich, int * nb_tests);
int lire_donnees_fich(FILE * fich, char * nom_image, double *seuil, int * nb_col_tu, int * nb_lig_tu, double * prop_garde, double * prop_min);

int main(void) {

	// Déclaration des variables
	t_tuile *ptr_tuile; // Pointeur vers une tuile
	t_spectre_gris *ptr_sp; // Pointeur vers un spectre
	t_recouvrement *ptr_rec; // Pointeur vers un recouvrement
	int nb_tests; // Nombre de tests à effectuer
	int colonnes, lignes; // Taille de la nouvelle image
	int col_tuile, lig_tuile; // dimention tuile
	int nb_tuiles; // Nombre de tuiles de la nouvelle image
	int numero_tuile; // Numéro de la tuile aléatoire
	int i, k; // Valeur d'incrémentation
	double seuil; // Valeur du seuil de lumière
	double prop_garde, prop_min; // se qu'on garde
	BMP * original; // Image originale
	int codage; // Taille de l'image originale
	BMP * nouvelle; // Nouvelle image
	char nom_txt[] = "Parametre.txt";
	char nom_image[15];
	FILE * ficher_txt;
	
	ficher_txt = ouvrir_fich_data(nom_txt, &nb_tests);
	lire_donnees_fich(ficher_txt, &nom_image, &seuil, &col_tuile, &lig_tuile, &prop_garde, &prop_min);
	md_srand();

	for (i = 0; i < nb_tests; i++) {

		original = BMP_ReadFile("image.bmp");
		codage = BMP_GetDepth(original);
		ptr_tuile = (t_tuile*)malloc(sizeof(t_tuile));
		assert(ptr_tuile != NULL);
		
		calibrer_taille_tuile(original, &colonnes, &lignes);
		init_tuile(colonnes, lignes, ptr_tuile);
		ptr_rec = init_recouvrement(get_nb_tuiles(original, colonnes, lignes), colonnes, lignes);

		for (k = 0; k < get_nb_tuiles(original, colonnes, lignes); k++) {
			numero_tuile = get_kieme_tuile(original, k, ptr_tuile);
			ptr_sp = get_spectre_tuile(original, ptr_tuile);
			if (ajouter_spectre_rec(ptr_sp, ptr_rec) == 0) {
				printf("Ajout d'un spectre dans le recouvrement n a pas fonctionnee.");
				system("pause");
				return 0;
			}
		}

		//calcul_integrales_seuil(ptr_rec, seuil);
		
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
FILE * ouvrir_fich_data(const char * nom_fich, int * nb_tests) {


	FILE *fichier_txt;
	fichier_txt = fopen(nom_fich, "r");
		if (fichier_txt == NULL) {
			nb_tests = -1;
		}
		else {
			rewind(fichier_txt);
			fscanf(fichier_txt,"%d\n", nb_tests);
		}

		return fichier_txt;
}

int lire_donnees_fich(FILE * fich, char * nom_image, double *seuil, int * nb_col_tu, int * nb_lig_tu, double * prop_garde, double * prop_min) {

	// Déclaration des variables
	int validite = 1;

	fscanf(fich,"%s %lf %d %d %lf %lf\n", nom_image, seuil, nb_col_tu, nb_lig_tu, prop_garde, prop_min);
	if (nb_col_tu == NULL || nb_lig_tu == NULL)validite = 0;

	return validite;
}