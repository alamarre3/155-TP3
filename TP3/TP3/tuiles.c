// ===== MODULE TUILE.C =====

#include "tuiles.h"
#include "qdbmp.h"

//Fonction : get_nb_tuiles
int get_nb_tuiles(BMP *original, int nb_col, int nb_lig) {
	
	// D�claration de variables
	int largeur; // la largeur de l'image en pixel
	int hauteur; // La hauteur de  l'image en pixel 
	int colonnes; // Le nombre de tuiles en largeur
	int lignes; // Le nombre de tuiles en hauteur

	hauteur = BMP_GetHeight(original);
	largeur = BMP_GetWidth(original);
	colonnes = largeur / nb_col;
	lignes = hauteur / nb_lig;
	
	return colonnes * lignes;
}

// Fonction qui initialise une tuile
void init_tuile(int nbcol_tuile, int nblig_tuile, t_tuile * tuile) {

	tuile->offset_col=-1;
	tuile->offset_lig=-1;
	tuile->nb_col= nbcol_tuile;
	tuile->nb_lig = nblig_tuile;
	tuile->id_enum = -1;
}

int get_kieme_tuile(BMP *original, int k, t_tuile * tuile){

	int largeur; // la largeur de l'image en pixel
	int hauteur; // La hauteur de  l'image en pixel 
	int val_retour=0;
	int colonnes;
	int ligne;

	if (k <= get_nb_tuiles(original, tuile->nb_col, tuile->nb_lig)) {

		largeur = BMP_GetWidth(original);
		hauteur = BMP_GetHeight(original);
		colonnes = largeur / tuile->nb_col;
		ligne = hauteur/ tuile->nb_lig;
		tuile->offset_col = (k % colonnes)*tuile->nb_col;
		tuile->offset_lig = (k % ligne)*tuile->nb_lig;
		val_retour = 1;
		tuile->id_enum = k;
	}
	return val_retour;
}

t_spectre_gris * get_spectre_tuile(BMP *original, const t_tuile * tuile) {
	int i; //compteur y
	int j; //compteur x
	int gris; // Intensit� de gris
	UCHAR red, green, blue; // Couleurs primaires
	t_spectre_gris*ptr_sp;

	ptr_sp = (t_spectre_gris*)malloc(sizeof(t_spectre_gris)); // allocation dynamique
	assert(ptr_sp != NULL);

	for (i = 0; i < NB_FREQUENCES; i++) {
		ptr_sp->spectre[i] = 0;
	}

	// Mettre les d�ffinition non utilis� � -1
	ptr_sp->integrale_lumin=-1;
	ptr_sp->seuil_lumin = -1;
	ptr_sp->integrale_lumin_seuil = -1;

	// Compte le spectre de gris
	for (i = tuile->offset_lig; i < tuile->offset_lig + tuile->nb_lig; i++) {

		for (j = tuile->offset_col; j < tuile->offset_col + tuile->nb_col; j++) {

			BMP_GetPixelRGB(original, j, i, &red, &green, &blue);
			gris = (red * 0.299) + (green * 0.587) + (blue * 0.144);
			ptr_sp->spectre[gris]++;
		}
	}
	return ptr_sp;
}

//************************************************************** 
// Fonction : intregale_seuil_lum

double integrale_seuil_lum(t_spectre_gris * ptr_sp, double seuil_lum) {

	// D�claration des variables
	int i; // Valeur d'incr�mentation
	double seuil_integral = 0; // Valeur calcul�e de l'int�grale

	if (seuil_lum < 0 || seuil_lum > 1) {
		return -1;
	}
	for (i = NB_FREQUENCES - 1; i / 255 > seuil_lum; i--) {
		seuil_integral += (i / 255) * ptr_sp->spectre[i];
	}
	ptr_sp->seuil_lumin = seuil_lum;
	ptr_sp->integrale_lumin_seuil = seuil_integral;

	return seuil_integral;
}

//**************************************************************
// Fonction : get_bitmap_tuile

BMP * get_bitmap_tuile(BMP *original, const t_tuile * tuile) {

	// D�claration des variables
	UCHAR red, blue, green; // Diff�rentes couleurs dont l'image est compos�e
	USHORT profond; // Nombre de bits par pixel
	UINT px, py; // Les positions des pixels dans la tuile
	BMP *nouvelle_image; // Nouvelle image cr��e

	profond = BMP_GetDepth(original);
	nouvelle_image = BMP_Create(tuile->nb_col, tuile->nb_lig, profond);

	for (px = 0; px < tuile->nb_col; px++) {
		for (py = 0; py < tuile->nb_lig; py++) {
			BMP_GetPixelRGB(original, px + tuile->offset_col, py + tuile->offset_lig, &red, &green, &blue);
			BMP_SetPixelRGB(nouvelle_image, px, py, red, green, blue);
		}
	}
	return nouvelle_image;
	BMP_Free(nouvelle_image);
}

//************************************************************** 
// Fonction : get_bitmap_gris_tuile

BMP * get_bitmap_gris_tuile(BMP *original, const t_tuile * tuile, double seuil_lum) {

	// D�claration des variables
	UCHAR red, blue, green, gris; // Diff�rentes couleurs dont l'image est compos�e + teinte de gris
	USHORT profond; // Nombre de bits par pixel
	UINT px, py; // Les positions des pixels dans la tuile
	double seuil; // Valeur calcul�e du seuil de luminosit�
	BMP *nouvelle_image_grise; // Nouvelle image grise cr��e
	t_spectre_gris *spectre_tuile; // Spectre de gris de la tuile choisie

	profond = BMP_GetDepth(original);
	nouvelle_image_grise = BMP_Create(tuile->nb_col, tuile->nb_lig, profond);
	spectre_tuile = get_spectre_tuile(original, tuile);
	seuil = integrale_seuil_lum(spectre_tuile, seuil_lum);

	for (px = 0; px < tuile->nb_col; px++) {
		for (py = 0; py < tuile->nb_lig; py++) {
			BMP_GetPixelRGB(original, px + tuile->offset_col, py + tuile->offset_lig, &red, &green, &blue);
			gris = (0.299 * red + 0.587 * green + 0.114 * blue);
			gris = (gris / 255.0) < seuil_lum ? 0 : gris;
			BMP_SetPixelRGB(nouvelle_image_grise, px, py, gris, gris, gris);
		}
	}
	return nouvelle_image_grise;
	BMP_Free(nouvelle_image_grise);
}

//**************************************************************
// Fonction : get_integrale_sans_seuil

double get_integrale_sans_seuil(const t_spectre_gris * ptr_sp) {
	return ptr_sp->integrale_lumin;
}

//************************************************************** 
// Fonction : get_seuil_luminosite

double get_seuil_luminosite(const t_spectre_gris * ptr_sp) {
	return ptr_sp->seuil_lumin;
}

//************************************************************** 
// Fonction : get_integrale_avec_seuil

double get_integrale_avec_seuil(const t_spectre_gris * ptr_sp) {
	return ptr_sp->integrale_lumin_seuil;
}

//************************************************************** 
// Fonction : get_tuile

void get_tuile(const t_spectre_gris * ptr_sp, t_tuile * tuile) {
	*tuile = ptr_sp->tuile;
}

//************************************************************** 
// Fonction : afficher_spectre

void afficher_spectre(const t_spectre_gris *ptr_sp) {

	// D�claration des variables
	int i; // Valeur d'incr�mentation
 

	printf("\n==== Tableau du spectre de lumiere =====\n");
	for (i = 0; i < NB_FREQUENCES; i++) {
	
			printf("%d : %d.\n", i, ptr_sp->spectre[i]);
	}
}

//************************************************************** 
// Fonction Calibrer taille de la tuile

 void calibrer_taille_tuile(BMP *original, int *nb_col, int *nb_lig) {

	 // D�claration des variables
	int largeur; // la largeur de l'image en pixel
	int hauteur; // La hauteur de  l'image en pixel 
	int min_colonnes = *nb_col; // Le nombre de pixel en largeur
	int min_lignes = *nb_lig; // Le nombre min de pixel en hauteur
	int nb_tuiles; // le nombre de tuiles possible 
	int pixel_colonne; // Le nombre de pixel restant en colonne
	int pixel_ligne; // Le nombre restant de pixel en ligne
	int pixel_recomander_col; // nombre de pixel recomander en colonnes
	int pixel_recomander_ligne; // nombre de pixel recomander en ligne

	int i;

	hauteur = BMP_GetHeight(original);
	largeur = BMP_GetWidth(original);


	for (i = -TOLLERANCE; i < TOLLERANCE; i++) {

		pixel_colonne = largeur % (*nb_col + i);
		pixel_ligne = hauteur % (*nb_lig + i);

		if (pixel_colonne < min_colonnes) {
			min_colonnes = pixel_colonne;
			pixel_recomander_col = *nb_col + i;
		}
		if (pixel_ligne < min_lignes) {
			min_lignes = pixel_colonne;
			pixel_recomander_ligne = *nb_lig + i;
		}

	}
	*nb_col = pixel_recomander_col;
	*nb_lig = pixel_recomander_ligne;
	return 0;
}
//************************************************************** 
// Fonction tuiles voisines

int tuiles_voisines(const t_tuile *tuile1, const t_tuile *tuile2) {

	// D�claration des variables
	int hauteur_min, hauteur_max; // hauteur max et min de la frontiere.
	int largeur_min, largeur_max; // largeur max et min de la frontiere.
	int tuile2_col, tuile2_lig; // centre de la tuile 2.
	int validite = 0; // indice de validit�.

					  //trouver le centre de la tuile 2
	tuile2_lig = tuile2->offset_lig + (tuile2->nb_lig / 2);
	tuile2_col = tuile2->offset_col + (tuile2->nb_col / 2);

	//cr�ation de la fontriere de la tuile 1
	hauteur_min = tuile1->offset_lig - tuile1->nb_lig;
	hauteur_max = tuile1->offset_lig + (tuile1->nb_lig * 2);

	largeur_min = tuile1->offset_col - tuile1->nb_col;
	largeur_max = tuile1->offset_col + (tuile1->nb_col * 2);

	//v�rifier si la tuile 2 se trouve dans la frontiere de la zone 1
	if (tuile2_lig > hauteur_min && tuile2_lig < hauteur_max && tuile2_col>largeur_min && tuile2_col < largeur_max) {
		validite = 1;
	}
	return validite;
}
//************************************************************** 
// Fonction copier tuiles dans image
void copier_tuile_ds_image(BMP *image_res, BMP *image_tu, const t_tuile *tuile, char titre[]) {

	// D�claration des variables
	BMP*validation; // image qui sert trouver le bon nom.


	validation = get_bitmap_tuile(image_res, tuile);
	
	do{  
		validation = BMP_ReadFile(titre);
		if (BMP_GetError() != BMP_FILE_NOT_FOUND) {
			if (titre[7] == 57) {
				titre[6]++;
				titre[7] = 48;
			}
			else titre[7]++;
		}

	} while (BMP_GetError() != BMP_FILE_NOT_FOUND);


	image_tu = get_bitmap_tuile(image_res, tuile);
	BMP_WriteFile(image_tu, titre);
	BMP_Free(image_tu);
	image_tu = get_bitmap_gris_tuile(image_res, tuile, 0);
	BMP_WriteFile(image_tu, titre);
	BMP_Free(image_tu);
}