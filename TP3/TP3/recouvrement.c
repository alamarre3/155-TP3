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
	assert(ptr_k != NULL);
	return ptr_k;
}

// Fonction : calcul_integrales_seuil

void calcul_integrales_seuil(t_recouvrement *rec, double seuil) {

	// Déclaration des variables
	t_spectre_gris *ptr_sp; // Pointeur vers un spectre
	int i; // Valeur d'incrémentation

	for (i = 0; i < rec->taille_tab_spectres; i++) {
		ptr_sp = get_kieme_ptr_sp(rec, i);
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
	t_spectre_gris *ptr_sp_copie; // Pointeur vers un spectre copie
	int i, j; // Valeurs d'incrémentation

	calcul_integrales_seuil(rec, seuil);

	for (i = rec->taille_tab_spectres; i > 1; i--){
		for (j = 1; j < rec->taille_tab_spectres; j++){
			ptr_sp1 = get_kieme_ptr_sp(rec, j);
			ptr_sp2 = get_kieme_ptr_sp(rec, j - 1);
			if (ptr_sp1->seuil_lumin > ptr_sp2->seuil_lumin){
				rec->tab_spectres[j - 1] = ptr_sp1;
				rec->tab_spectres[j] = ptr_sp2;
			}
		}
	}
}

// Fonction : reconstruire_image

BMP *reconstruire_image(BMP *original, const t_recouvrement *rec, double prop_garde, double prop_min, char * fichier_log) {

	//Déclaration des variables
	BMP *nouvelle; // Nouvelle image
	int colonnes, lignes, codage; // Taille de l'image
	int i; // Valeur d'incrémentation
	int tuile_lumineuse; // Nombre de tuiles du tableau de spectre qui sont inclut dans le tableau
	int seuil; // Seuil de lumière entré par l'utilisateur
	char titre[] = "RGBway00.bmp"; // Titre de la nouvelle image

	colonnes = BMP_GetWidth(original);
	lignes = BMP_GetHeight(original);
	codage = BMP_GetDepth(original);
	nouvelle = BMP_Create(colonnes,lignes,codage);

	printf("Seuil de lumiere voulu pour la nouvelle image : ");
	scanf("%d", &seuil);
	tuile_lumineuse = tableau_tuile_lumineuse(rec, prop_garde, prop_min, seuil);
	
	for (i = 0; i < tuile_lumineuse; i++) {
		copier_tuile_ds_image(nouvelle, original, rec->tab_spectres[i], titre);
	}

	return nouvelle;
	BMP_Free(nouvelle);
}

// Fonction : tuile_plus_lumineuse

int tuile_plus_lumineuse(const t_recouvrement *rec) {

	// Déclaration des variables
	t_spectre_gris *ptr_sp=NULL;	// Pointeur vers un spectre
	int i, max = 0; // Valeur d'incrémentation

	for (i =0 ; i < rec->taille_tab_spectres; i++) {
		ptr_sp = get_kieme_ptr_sp(rec, i);
		if (max < ptr_sp->integrale_lumin) {
			max = ptr_sp->integrale_lumin;
		}
	}
	return max;
}

// Fonction : tableau_tuile_lumineuse

int tableau_tuile_lumineuse(const t_recouvrement *rec, double prop_garde, double prop_min, double seuil) {
	// Déclaration des variables
	int i, j;
	int tampon; // Tampon utilisé pour le test de validité pour la vérification d'une tuile voisine
	int validite;
	double io;
	int copie_direct = 0; // Nombre de tuiles dont le ratio du spectre lumineux est plus grand que prop_garde
	int	copie_indirect = 0; // Nombre de tuiles dont le ratio du spectre lumineux est plus grand que prop_min et adjacent à une copie_direct

	trier_spectres(rec, seuil);
	io = tuile_plus_lumineuse(rec);

	for (i = 0; i < rec->taille_tab_spectres; i++) {
		if (get_integrale_avec_seuil(rec->tab_spectres[i]) / io > prop_garde) {
			copie_direct++;
		}
	}
	for (i = copie_direct-1; i < rec->taille_tab_spectres; i++) {
		if (get_integrale_avec_seuil(rec->tab_spectres[i]) / io > prop_min) {
			for (j = 0; j > copie_direct; j++) {
				tampon = tuiles_voisines(rec->tab_spectres[i], rec->tab_spectres[j]);
				printf("%d", tampon);
				if (tampon == 1) {
					validite = tampon;
				}
			}
			if (validite == 1) {
				copie_indirect++;
			}
			else {
				criss_cross_spectre(rec, rec->tab_spectres[j], j);
			}
			validite = 0;
		}
	}
	return copie_direct + copie_indirect;
}

// Fonction : mettre_spectre_fin

void criss_cross_spectre(t_recouvrement *rec, t_spectre_gris *ptr_sp, int pos) {

	// Déclaration des variables
	int i; // Valeur d'incrémentation
	t_spectre_gris *tampon; // Tampon du spectre à déplacer

	tampon = rec->tab_spectres[pos];

	for (i = pos; i < rec->taille_tab_spectres-1; i++) {
		rec->tab_spectres[i] = rec->tab_spectres[i + 1];
	}
	rec->tab_spectres[i] = tampon;
}