/************************************************************** 

PAR : Alexandre Lamarre & Francis Alonzo

DATE : 01/12/18

module d'outils demand� dans la premiere partie du TP#3
INF-155 Automne 2018

le module offre les fonctions :


****************************************************************/ 

#ifndef __OUTILS_TUILE_H__
#define __OUTILS_TUILE_H__

//************************************************************** 

// merci Chai Braudo pour le beau petit module Quick n' Dirty  
#include "qdbmp.h"

#define  NB_FREQUENCES  256     //nombre d'intensit�s et taille du spectre


//************************************************************** 
//**************************************************************
// DEUX TYPES ESSENTIELS dont voici la d�finition

/*
  LA TUILE
  une tuile a une taille bien d�finie et occupe une position bien definie
  dans un bitmap original
  elle est repr�sent�e par 5 int ou 5 UINT (si on veut diff�rencier)

  UNE TUILE UTILE DANS CE TP EST OBTENU AVEC LA FONCTION get_kieme_tuile()
*/
typedef struct {

	// avec ses decalages dans l'image originale
	int offset_col; // decalage colonne
	int offset_lig; // decalage ligne

	//sa taille v�ritable en pixels
	int nb_col;
	int nb_lig;

	// son num�ro unique dans l'�num�ration des tuiles d'une image
	int id_enum;

} t_tuile;

/*
  LE SPECTRE
  c'est dans un spectre qu'on va conserver tout ce qui est pertinent �
  la mesure de la luminosit� d'une tuile

  UN SPECTRE UTILE DANS CE TP EST OBTENU AVEC LA FONCTION get_kieme_tuile()
*/

typedef struct {

	// la tuile dont est issu le spectre est conserv�
	t_tuile tuile;

	// le tableau des fr�quences de chaque teinte de gris dans la tuile
	UINT spectre[NB_FREQUENCES];

	// int�grale �l�mentaire de la luminosit� d'un spectre SANS seuil
	// obtenue de la somme des produits ((i/255.0) * spectre[i]) 
	// pour i allant de 0, 255
	double integrale_lumin;

	// les deux derniers membres sont associ�s � une mesure 
	// de luminosit� seuill�e
	double seuil_lumin;     // le seuil entre 0 et 1

	// idem � l'integrale pr�c�dente sauf que tous les i tels que
	// (i/255.0) < seuil_lumen ne sont PAS consid�r�s dans la sommation
	double integrale_lumin_seuil;

}t_spectre_gris;


//************************************************************** 
// LES D�CLARATIONS DES FONCTIONS
//************************************************************** 
/* Fonction  get nombre de tuiles

Description: Cette fonction sert � calculer le nombre de tuile qui peux rentrer dans l'image en fonction de sa taille.

Param�tre:'limage, la dimention de la tuiles en hauter et en largeur

Sortie: Le nombre de tuile qui rentre dans l'image.
*/

int get_nb_tuiles(BMP *original, int nb_col, int nb_lig);
//************************************************************** 
/* Fonction  Init tuile

Description: Cette fonction inscrit la dimention de la tuile dans le struct et met les autre champ a -1.

Param�tre:Le struct t_tuile, la dimention de la tuiles en hauter et en largeur

Sortie: aucun.
*/


void init_tuile(int nbcol_tuile, int nblig_tuile, t_tuile * tuile);

//************************************************************** 

/* Fonction  get_kieme_tuile

Description: Cette fonction sert � calculer le offset d'une tuile et l'inscrit dans le struct

Param�tre:'limage, le num�ro de la tuile et Le struct t_tuile

Sortie: indice de validit�.
*/


int get_kieme_tuile(BMP *original, int k, t_tuile * tuile);
//************************************************************** 

/* Fonction  get_spectre_tuile

Description: Cette fonction sert a calcul� l'intensit� de gris de chaque pixel contenu dans une tuile donn�e. 
Elle indique le taux de gris entre 0 et 255, Elle inscrit ces r�sultat dans un tableau du struct et revoi sont adresse

Param�tre:'limage et le struct t_tuile

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