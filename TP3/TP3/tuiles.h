/************************************************************** 

PAR : Alexandre Lamarre & Francis Alonzo

DATE : 01/12/18

module d'outils demandé dans la premiere partie du TP#3
INF-155 Automne 2018

le module offre les fonctions :


****************************************************************/ 

#ifndef __OUTILS_TUILE_H__
#define __OUTILS_TUILE_H__

//************************************************************** 

// merci Chai Braudo pour le beau petit module Quick n' Dirty  
#include "qdbmp.h"

#define  NB_FREQUENCES  256     //nombre d'intensités et taille du spectre


//************************************************************** 
//**************************************************************
// DEUX TYPES ESSENTIELS dont voici la définition

/*
  LA TUILE
  une tuile a une taille bien définie et occupe une position bien definie
  dans un bitmap original
  elle est représentée par 5 int ou 5 UINT (si on veut différencier)

  UNE TUILE UTILE DANS CE TP EST OBTENU AVEC LA FONCTION get_kieme_tuile()
*/
typedef struct {

	// avec ses decalages dans l'image originale
	int offset_col; // decalage colonne
	int offset_lig; // decalage ligne

	//sa taille véritable en pixels
	int nb_col;
	int nb_lig;

	// son numéro unique dans l'énumération des tuiles d'une image
	int id_enum;

} t_tuile;

/*
  LE SPECTRE
  c'est dans un spectre qu'on va conserver tout ce qui est pertinent à
  la mesure de la luminosité d'une tuile

  UN SPECTRE UTILE DANS CE TP EST OBTENU AVEC LA FONCTION get_kieme_tuile()
*/

typedef struct {

	// la tuile dont est issu le spectre est conservé
	t_tuile tuile;

	// le tableau des fréquences de chaque teinte de gris dans la tuile
	UINT spectre[NB_FREQUENCES];

	// intégrale élémentaire de la luminosité d'un spectre SANS seuil
	// obtenue de la somme des produits ((i/255.0) * spectre[i]) 
	// pour i allant de 0, 255
	double integrale_lumin;

	// les deux derniers membres sont associés à une mesure 
	// de luminosité seuillée
	double seuil_lumin;     // le seuil entre 0 et 1

	// idem à l'integrale précédente sauf que tous les i tels que
	// (i/255.0) < seuil_lumen ne sont PAS considérés dans la sommation
	double integrale_lumin_seuil;

}t_spectre_gris;


//************************************************************** 
// LES DÉCLARATIONS DES FONCTIONS
//************************************************************** 
/* Fonction  get nombre de tuiles

Description: Cette fonction sert à calculer le nombre de tuile qui peux rentrer dans l'image en fonction de sa taille.

Paramètre:'limage, la dimention de la tuiles en hauter et en largeur

Sortie: Le nombre de tuile qui rentre dans l'image.
*/

int get_nb_tuiles(BMP *original, int nb_col, int nb_lig);
//************************************************************** 
/* Fonction  Init tuile

Description: Cette fonction inscrit la dimention de la tuile dans le struct et met les autre champ a -1.

Paramètre:Le struct t_tuile, la dimention de la tuiles en hauter et en largeur

Sortie: aucun.
*/


void init_tuile(int nbcol_tuile, int nblig_tuile, t_tuile * tuile);

//************************************************************** 

/* Fonction  get_kieme_tuile

Description: Cette fonction sert à calculer le offset d'une tuile et l'inscrit dans le struct

Paramètre:'limage, le numéro de la tuile et Le struct t_tuile

Sortie: indice de validité.
*/


int get_kieme_tuile(BMP *original, int k, t_tuile * tuile);
//************************************************************** 

/* Fonction  get_spectre_tuile

Description: Cette fonction sert a calculé l'intensité de gris de chaque pixel contenu dans une tuile donnée. 
Elle indique le taux de gris entre 0 et 255, Elle inscrit ces résultat dans un tableau du struct et revoi sont adresse

Paramètre:'limage et le struct t_tuile

Sortie: L'adresse du  struct  get_spectre_tuile .
*/

t_spectre_gris * get_spectre_tuile(BMP *original, const t_tuile * tuile);

//************************************************************** 

double integrale_seuil_lum(t_spectre_gris * ptr_sp, double seuil_lum);

//************************************************************** 

BMP * get_bitmap_tuile(BMP *original, const t_tuile * tuile);

//************************************************************** 

BMP * get_bitmap_gris_tuile(BMP *original, const t_tuile * tuile, double seuil_lum);

//**************************************************************

double get_integrale_sans_seuil(const t_spectre_gris * ptr_sp);

//************************************************************** 

double get_seuil_luminosite(const t_spectre_gris * ptr_sp);

//************************************************************** 

double get_integrale_avec_seuil(const t_spectre_gris * ptr_sp);

//************************************************************** 

void get_tuile(const t_spectre_gris * ptr_sp, t_tuile * tuile);

//************************************************************** 

void afficher_spectre(const t_spectre_gris *ptr_sp);

//**************************************************************
#endif
//************************************************************** 