/*
	EXEMPLE D'UTILISATION DU MODULE QUICK & DIRTY

	D'UNE SEULE IMAGE ORIGINALE LUE (BMP_ReadFile)

	ON VA CRÉER TROIS NOUVEAUX BITMAPS (BMP_Create) POUR :

	1- COPIER TEL QUEL LE QUART  DE L'IMAGE ORIGINALE

	2- COPIER UNIQUEMENT LE VERT DE LA DEMIE GAUCHE DE L'IMAGE 

	3- SEUILLER À 0.8 LE ROUGE DES PIXELS  DE L'IMAGE

*/

/*	
	CHOISIR VOTRE IMAGE :
	choisissez une image .bmp 
	copiez-la avec les fichiers du projet ( .h et .c )
	remplacez ag.bmp par le nom de votre fichier dans le code
		image = BMP_ReadFile("ag.bmp");
	tout va fonctionner
*/

#define  _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include "qdbmp.h"

#define SEUIL_ROUGE 0.8

/*int main(void) {

	// pour conserver les valeurs RGB d'un pixel
	UCHAR red, green, blue;

	// image eoriginale et ses valeurs 
	BMP * original ;
	int nb_col, nb_lig, codage; 

	// la nouvelle image extraite de l'originale
	// et ses valeurs de taille et d'offsets
	BMP * nouvelle;
	int col_depart, lig_depart, colons, lignes;

	// les itarateurs matriciels des pixels de l'image
	int  pos_x, pos_y;


	// ouvrir le fichier original et 
	// obtenir ses caractéristiques principales
	original = BMP_ReadFile("ag.bmp");
	nb_lig = BMP_GetHeight(original);
	nb_col = BMP_GetWidth(original);
	codage = BMP_GetDepth(original);



	// PREMIERE EXTRACTION (en vert uniquement)
	
	// les tailles de la sous-image vont
	// dépendre de 	celles de l'original
	lig_depart = nb_lig / 4;
	lignes = nb_lig / 2;
	col_depart = nb_col / 4;
	colons = nb_col / 2;
	nouvelle = BMP_Create(colons, lignes, codage);
	// extraire le quart de l'image originale
	// et le copier tel quel
	for (pos_x = 0; pos_x < colons; ++pos_x) {
		for (pos_y = 0; pos_y < lignes; ++pos_y) {
			BMP_GetPixelRGB(original, col_depart + pos_x, lig_depart + pos_y, &red, &green, &blue);
			BMP_SetPixelRGB(nouvelle, pos_x, pos_y, red, green, blue);
		}
	}
	// sauvegarder l'image et libérer ensuite l'espace occupé par le BMP
	BMP_WriteFile(nouvelle, "nouvelle00.bmp");
	BMP_Free(nouvelle);



	// SECONDE EXTRACTION EN VERT

	// les tailles de la sous-image vont
	// dépendre de 	celles de l'original
	lig_depart = 0;
	lignes = nb_lig ;
	col_depart = 0;
	colons = nb_col / 2;

	nouvelle = BMP_Create(colons, lignes, codage);
	// extraire la demie gauche de l'image originale
	// et le copier en teinte  verte unique 
	for (pos_x = 0; pos_x < colons; ++pos_x) {
		for (pos_y = 0; pos_y < lignes; ++pos_y) {
			BMP_GetPixelRGB(original, col_depart + pos_x, lig_depart + pos_y, &red, &green, &blue);
			BMP_SetPixelRGB(nouvelle, pos_x, pos_y, 0, green, 0);
		}
	}
	// sauvegarder l'image et libérer ensuite l'espace occupé par le BMP
	BMP_WriteFile(nouvelle, "nouvelle01.bmp");
	BMP_Free(nouvelle);


	// LA TROISIEME IMAGE EXTRAITE VA SEUILLER LE ROUGE 
	// seul un rouge foncé est conservé aux pixels

	// les tailles de la sous-image vont
	// dépendre de 	celles de l'original
	lig_depart = 0;
	lignes = nb_lig;
	col_depart = 0;
	colons = nb_col ;

	nouvelle = BMP_Create(colons, lignes, codage);
	// extraire  l'image originale
	// et le copier en seuillant le rouge de chaque pixel
	for (pos_x = 0; pos_x < colons; ++pos_x) {
		for (pos_y = 0; pos_y < lignes; ++pos_y) {
			BMP_GetPixelRGB(original, col_depart + pos_x, lig_depart + pos_y, &red, &green, &blue);
			red = (1.0* red / 255) < SEUIL_ROUGE ? 0 : red;
			BMP_SetPixelRGB(nouvelle, pos_x, pos_y, red, green, blue);
		}
	}

	// sauvegarder l'image et libérer ensuite l'espace occupé par le BMP
	BMP_WriteFile(nouvelle, "nouvelle02.bmp");
	BMP_Free(nouvelle);


	// le free fonctionnel du BMP original
	BMP_Free(original);

	// c'est fini
	system("pause");
	return 0;
}*/