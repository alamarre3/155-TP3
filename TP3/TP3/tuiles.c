
#include "tuiles.h"

//Fonction qui trouve ne nombre de tuile
int get_nb_tuiles(BMP *original, int nb_col, int nb_lig) {
	// Déclaration de variables
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

	if (k <= get_nb_tuiles(BMP *original, tuile->nb_col, tuile->nb_lig)) {

		largeur = BMP_GetWidth(original);
		colonnes = largeur / tuile->nb_col;
		tuile->offset_col = (k % colonnes)*tuile->nb_col;
		tuile->nb_lig = (k / colonnes)*tuile->nb_lig;
		val_retour = 1;
		tuile->id_enum = k;
	}
	return val_retour;
}

t_spectre_gris * get_spectre_tuile(BMP *original, const t_tuile * tuile) {
	int x;
	int y;

	t_spectre_gris*pointeur_spectre;
	pointeur_spectre = (t_spectre_gris*)malloc(t_spectre_gris);

}