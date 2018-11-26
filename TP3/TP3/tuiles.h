/************************************************************** 

PAR :

DATE :

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


int get_nb_tuiles(BMP *original, int nb_col, int nb_lig);
//************************************************************** 



void init_tuile(int nbcol_tuile, int nblig_tuile, t_tuile * tuile);

//************************************************************** 



int get_kieme_tuile(BMP *original, int k, t_tuile * tuile);
//************************************************************** 




t_spectre_gris * get_spectre_tuile(BMP *original, const t_tuile * tuile);
//************************************************************** 




//************************************************************** 




//************************************************************** 
#endif
//************************************************************** 