/************************************************************** 

PAR :

DATE :

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