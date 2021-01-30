#ifndef INTERFACE
#define INTERFACE

#define LARGEUR 820
#define HAUTEUR 1000
#define LARGEUR_2 1000
#define HAUTEUR_2 820

#include "modele.h"

POINT converti_numcase_en_point(NUMCASE n, int interface);
NUMCASE converti_point_en_numcase(POINT P, int interface);
POINT converti_numcase_en_pointImage(NUMCASE n, int interface);
NUMCASE converti_pointImage_en_numcase(POINT P, int interface);
POINT converti_pointClic_en_pointImage(POINT P);
POINT centre_point_clic(POINT P, int interface);

BOOL est_clic_dans_echiquier(POINT P, int interface);

void defini_titre_fenetre(char *titre);
void initialise_fenetre_graphique(int largeur, int hauteur);

SDL_Surface **charge_image_piece(int interface);
void libere_image_piece(SDL_Surface **images);

int valide_choix_interface(POINT p);
int valide_choix_modeJeu(POINT p);
CHESSMAN  retourne_choix_promotion_pion(POINT P);

void affiche_menu_choix_interface(SDL_Surface *image);
void affiche_menu_choix_modeJeu(SDL_Surface *image);
void affiche_menu_choix_promotion_pion(SDL_Surface **images, JOUEUR J);

void affiche_damier();
void affiche_damier2();

void affiche_ligne_repere(POINT P,int decalage);
void affiche_colonne_repere(POINT P,int decalage);

void affiche_echiquier(int damier,SDL_Surface **images);

void affiche_roi(POINT P, COLOR couleur, SDL_Surface *roi); // todo delete roi
void affiche_dame(POINT P, COLOR couleur, SDL_Surface *dame);
void affiche_cavalier(POINT P, COLOR couleur, SDL_Surface *cavalier);
void affiche_tour(POINT P, COLOR couleur, SDL_Surface *tour);
void affiche_fou(POINT P, COLOR couleur, SDL_Surface *fou);
void affiche_pion(POINT P, COLOR couleur, SDL_Surface *pion);

void affiche_piece_en_surbrillance(NUMCASE n, int interface);
void affiche_coups_possible(BOOL **coupPossible, int interface);

void affiche_cadre_tour_de_jeu(int px, int py, int p1x, int p1y);
void affiche_message_tour_de_jeu(char msg[], int taille, int px, int py);
void affiche_info_bas(char msgInit[], char msgFin[]);
void affiche_info_haut(char msgInit[], char msgFin[]);
void affiche_avatar(POINT P, SDL_Surface *avatar);



#endif
