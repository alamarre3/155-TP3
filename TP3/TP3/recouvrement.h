/**************************************************************

PAR : Alexandre Lamarre & Francis Alonzo

DATE : 01/12/18

Module d'outils demandé dans la deuxième partie du TP#3
INF-155 Automne 2018

le module offre les fonctions :


****************************************************************/

#ifndef _OUTIL_RECOUVREMENT_H_
#define _OUTIL_RECOUVREMENT_H_

//**************************************************************

#include "tuiles.h"
#include "qdbmp.h"

//**************************************************************

typedef struct {
	t_spectre_gris **tab_spectres; // Talbeau dynamique des spectres,
								   // chaque case contient l'adresse d'un spectre
	int taille_tab_spectres; // Taille du tableau dynamique tab_spectre
	int largeur_tuile; // Largeur et hauteur de chacune des tuiles
	int hauteur_tuile; // contenues dans le tableau des spectres
} t_recouvrement ;

//**************************************************************
// Fonction : Constructeur de t_recouvrement

t_recouvrement * init_recouvrement(int nb_tuiles, int nb_col_tuile, int nb_lig_tuile);

//**************************************************************
// Fonction : Destructeur du tableau de spectre de t_recouvrement

void detruire_spectres(t_recouvrement *rec);

//**************************************************************
// Fonction : Destructeur de t_recouvrement

void detruire_recouvrement(t_recouvrement *rec);

//**************************************************************
// Fonction : Ajouter_spectre_rec

int ajouter_spectre_rec(t_spectre_gris *ptr_sp, t_recouvrement *rec);

//**************************************************************
// Fonction : get_kieme_ptr_sp

t_spectre_gris * get_kieme_ptr_sp(const t_recouvrement *rec, int k);

//**************************************************************
// Fonction : calcul_integrales_seuil

void calcul_integrales_seuil(t_recouvrement *rec, double seuil);

//**************************************************************
// Fonction : trier_spectres

void trier_spectres(t_recouvrement *rec, double seuil);

//**************************************************************
// Fonction : reconstruire_image

BMP *reconstruire_image(BMP * original, const t_recouvrement *rec, double prop_garde, double prop_min, char * fichier_log);

//**************************************************************
// Fonction : tuile_plus_lumineuse

int tuile_plus_lumineuse(const t_recouvrement *rec);









#endif // !_OUTIL_RECOUVREMENT_H_
