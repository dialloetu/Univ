#ifndef MODELE
#define MODELE

typedef struct {
	int interface;
	int modeJeu;
}choix;

typedef enum {VIDE,PION,FOU,ROI,DAME,CAVALIER,TOUR} CHESSMAN;

typedef enum {NON_DEFINI,BLANC,NOIR} COLOR;

typedef struct { 
    CHESSMAN c;
	COLOR coul;
}PIECE;

typedef struct {
	int ligne;
	int colonne;
}NUMCASE;

typedef struct {
	int player; // todo ???
	COLOR coul;
}JOUEUR;


PIECE echiquier[8][8];

void init_echiquier();
BOOL **init_tab_coups_possible();
void reinit_tab_coups_possible(BOOL **coupPossible);
void libere_tab_coups_possible(BOOL **coupPossible);
BOOL est_coup_valide(NUMCASE dest, BOOL **coupPossible);

void deplace_Piece(NUMCASE src, NUMCASE dest);


BOOL est_case_vide(NUMCASE n);
BOOL est_valide_clic_joueur(NUMCASE n, JOUEUR J); // ajouter src dans le nom de la fct ou du param
BOOL est_piece_adversaire_dans_case(NUMCASE n, COLOR coulJoueur);




JOUEUR change_de_joueur(JOUEUR J);
BOOL test_prise_pion_noir(NUMCASE src, NUMCASE dst);
BOOL test_prise_pion_blanc(NUMCASE src, NUMCASE dst);
BOOL test_prise_tour(NUMCASE src, NUMCASE dst);
BOOL test_prise_cavalier(NUMCASE src, NUMCASE dst);
BOOL test_prise_roi(NUMCASE src, NUMCASE dst);
BOOL test_prise_fou(NUMCASE src, NUMCASE dst);

 
void calcule_coups_possible_pion_noir(NUMCASE n,BOOL **coupPossible);
void calcule_coups_possible_pion_blanc(NUMCASE n, BOOL **coupPossible);
void calcule_coups_possible_fou(NUMCASE n, BOOL **coupPossible);
void calcule_coups_possible_tour(NUMCASE n, BOOL **coupPossible);
void calcule_coups_possible_cavalier(NUMCASE n, BOOL **coupPossible);
void calcule_coups_possible_roi(NUMCASE n, BOOL **coupPossible);
void calcule_coups_possible_dame(NUMCASE n, BOOL **coupPossible);
void calcule_coups_possible(NUMCASE n, BOOL **coupPossible);

BOOL est_pion_promu(NUMCASE n);
#endif
