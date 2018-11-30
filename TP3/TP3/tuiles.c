// ===== MODULE TUILE.C =====

#include "tuiles.h"

//Fonction qui trouve ne nombre de tuile
int get_nb_tuiles(BMP *original, int nb_col, int nb_lig) {
	// D�claration de variables
	int largeur; // la largeur de l'image en pixel
	int hauteur; // La hauteur de  l'image en pixel 
	int colonnes; // Le nombre de tuiles en largeur
	int lignes; // Le nombre de tuiles en hauteur
	int nb_tuiles; // le nombre de tuiles possible 

	hauteur = BMP_GetHeight(original);
	largeur = BMP_GetWidth(original);

	colonnes = largeur / nb_col;
	lignes = hauteur / nb_lig;

	nb_tuiles = colonnes * lignes;

	return (nb_tuiles);

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

	if (k <= get_nb_tuiles(original, tuile->nb_col, tuile->nb_lig)) {

		largeur = BMP_GetWidth(original);
		colonnes = largeur / tuile->nb_col;
		tuile->offset_col = (k % colonnes)*tuile->nb_col;
		tuile->offset_lig = (k / colonnes)*tuile->nb_lig;
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
	for (i = tuile->nb_lig; i < tuile->nb_lig + tuile->nb_lig; i++) {

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
			BMP_GetPixelRGB(original, px, py, &red, &green, &blue);
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
