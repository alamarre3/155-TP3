// ===== MODULE RECOUVREMENT.C =====

#include "recouvrement.h"

// Fonction : init_recouvrement

t_recouvrement * init_recouvrement(int nb_tuiles, int nb_col_tuile, int nb_lig_tuile) {

	// Déclaration des variables
	t_recouvrement *ptr_rec; // Pointeur pour le struct créé

	ptr_rec = (t_recouvrement*)malloc(sizeof(t_recouvrement));
	assert(ptr_rec != NULL);
	ptr_rec->tab_spectres = (t_spectre_gris**)malloc(nb_tuiles * sizeof(t_spectre_gris*));
	assert(ptr_rec->tab_spectres != NULL);
	ptr_rec->taille_tab_spectres = nb_tuiles;
	ptr_rec->largeur_tuile = nb_col_tuile;
	ptr_rec->hauteur_tuile = nb_lig_tuile;

	return ptr_rec;
}

// Fonction : detruire_spectres

void detruire_spectres(t_recouvrement *rec) {

	// Déclaration des variables
	int i; // Valeur d'incrémentation

	for (i = 0; i < rec->taille_tab_spectres; i++) {
		free(rec->tab_spectres[i]);
	}
}

// Fonction : detruire_recouvrement

void detruire_recouvrement(t_recouvrement *rec) {
	detruire_spectres(rec);
	free(rec->tab_spectres);
	free(rec);
}

// Fonction : ajouter_spectre_rec

int ajouter_spectre_rec(t_spectre_gris *ptr_sp, t_recouvrement *rec) {
	rec->tab_spectres[ptr_sp->tuile.id_enum] = ptr_sp;
	if (rec->tab_spectres[ptr_sp->tuile.id_enum] == ptr_sp) {
		return 1;
	}
	return 0;
}

// Fonction : get_kieme_ptr_sp

t_spectre_gris * get_kieme_ptr_sp(const t_recouvrement *rec, int k) {
	
	//Déclaration des variables
	t_spectre_gris *ptr_sp; // Pointeur d'une spectre
	t_spectre_gris *ptr_k = NULL; // Pointeur du spectre avec le id K
	int i; // Valeur d'incrémentation

	for (i = 0; i < rec->taille_tab_spectres; i++) {
		ptr_sp = rec->tab_spectres[i];
		if (k == ptr_sp->tuile.id_enum) {
			ptr_k = ptr_sp;
		}
	}
	return ptr_k;
}

// Fonction : calcul_integrales_seuil

void calcul_integrales_seuil(t_recouvrement *rec, double seuil) {

	// Déclaration des variables
	t_spectre_gris *ptr_sp = NULL; // Pointeur vers un spectre
	int i; // Valeur d'incrémentation

	for (i = 0; i < rec->taille_tab_spectres; i++) {
		ptr_sp = rec->tab_spectres[i];
		if (seuil != ptr_sp->seuil_lumin) {
			ptr_sp->seuil_lumin = seuil;
			ptr_sp->integrale_lumin_seuil = get_integrale_avec_seuil(ptr_sp);
		}
	}
}

// Fonction : trier_spectres

void trier_spectres(t_recouvrement *rec, double seuil) {

	// Déclaration des variables
	t_spectre_gris *ptr_sp1 = NULL; // Pointeur vers un spectre1
	t_spectre_gris *ptr_sp2 = NULL; // Pointeur vers un spectre2
	t_spectre_gris *ptr_sp_copie = NULL; // Pointeur vers un spectre copie
	int i, j; // Valeurs d'incrémentation

	for (i = rec->taille_tab_spectres; i > 1; i--){
		for (j = 1; j < rec->taille_tab_spectres; j++){
			rec->tab_spectres[j] = ptr_sp1;
			rec->tab_spectres[j-1] = ptr_sp2;
			if (ptr_sp1->seuil_lumin < ptr_sp2->seuil_lumin){
				ptr_sp_copie = rec->tab_spectres[j - 1];
				rec->tab_spectres[j - 1] = rec->tab_spectres[j];
				rec->tab_spectres[j] = ptr_sp_copie;
			}
		}
	}
}

// Fonction : reconstruire_image

BMP *reconstruire_image(BMP *original, const t_recouvrement *rec, double prop_garde, double prop_min, char * fichier_log) {

	//Déclaration des variables
	BMP *nouvelle; // Nouvelle image
	int colonnes, lignes, codage; // Taille de l'image
	double seuil_lumiere; // Seuil de lumière le plus lumineuse
	double ratio_r; // Ratio utilisé pour décider les tuiles à conserver

	colonnes = BMP_GetWidth(original);
	lignes = BMP_GetHeight(original);
	codage = BMP_GetDepth(original);
	nouvelle = BMP_Create(colonnes,lignes,codage);

	seuil_lumiere = tuile_plus_lumineuse(rec);


	

	return nouvelle;
	BMP_Free(nouvelle);
}

// Fonction : tuile_plus_lumineuse

int tuile_plus_lumineuse(const t_recouvrement *rec) {

	// Déclaration des variables
	t_spectre_gris *ptr_sp = NULL;	// Pointeur vers un spectre
	int i, max = 0; // Valeur d'incrémentation

	for (i =0 ; i < rec->taille_tab_spectres; i++) {
		rec->tab_spectres[i] = ptr_sp;
		if (max < ptr_sp->integrale_lumin) {
			max = ptr_sp->integrale_lumin;
		}
	}
	return max;
}