#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include "modele.h"
#include "Interface.h"
#include "controleur.h"

/*********************************************
 *											 *
 *			    CONTROLEUR				     *
 *					 						 *
 *********************************************/

extern int __init_graphics_is_already_called;

choix defini_parametres_du_jeu()
{
	POINT P;
	choix c;
	SDL_Surface *image = NULL;

	initialise_fenetre_graphique(800,800);

	defini_titre_fenetre("Jeu d'échecs - Choix de l'interface");
	affiche_menu_choix_interface(image);

	do
    {
   		 P = wait_clic();
		 c.interface = valide_choix_interface(P);
    }while(c.interface != 1 && c.interface != 2);

	SDL_FreeSurface(image);

	defini_titre_fenetre("Jeu d'échecs - Choix du mode de jeu");
	affiche_menu_choix_modeJeu(image);
	
	do
	{	 P = wait_clic();
		 c.modeJeu = valide_choix_modeJeu(P);
    }while(c.modeJeu != 1 && c.modeJeu != 2);
	
	SDL_FreeSurface(image);

	__init_graphics_is_already_called = 0;
	
	return c;		

}

void modifie_pion_promu(NUMCASE n)
{
	POINT P;
	CHESSMAN c;

	do
	{
		P = wait_clic();
		c = retourne_choix_promotion_pion(P);
	}while(c == VIDE);

	echiquier[n.ligne][n.colonne].c = c;
}

void init_jeu(SDL_Surface ***images, BOOL ***coupPossible, choix *c)
{	

	*c = defini_parametres_du_jeu();
	*images = charge_image_piece(c->interface);
	*coupPossible = init_tab_coups_possible(); 

	if(c->interface == 1)
		WIDTH = LARGEUR, HEIGHT = HAUTEUR;
	else
		WIDTH = LARGEUR_2, HEIGHT = HAUTEUR_2;

	initialise_fenetre_graphique(WIDTH,HEIGHT);
	defini_titre_fenetre("Jeu d'échecs");
}


int main()
{

	choix c;
	NUMCASE n1,n2;
	SDL_Surface **images = NULL;
/*	SDL_Surface **avatar = NULL;
	POINT avatar_haut = {50, 20}, avatar_bas = {50, 930};
	char msgHaut[] = "Toucher une piece pour commencer le jeu.";
	char msgBas[] = "Toucher une piece pour commencer le jeu.", msgTmp[]="";
	char msgJeu[] = "C'est votre tour de jeu .", msgAttente[] = "Attender votre tour.";*/
	POINT P1 =  {-1,-1}, P2 = {-1,-1};
	JOUEUR J = {1,NOIR};
	BOOL **coupPossible = NULL;

	init_jeu(&images,&coupPossible,&c);
	init_echiquier();

	while(1)
	{
		
		do
		{
			reinit_tab_coups_possible(coupPossible);
		    affiche_echiquier(c.interface,images);
		    
		   /* affiche_info_haut(msgAttente, msgTmp);
		    affiche_info_bas(msgBas, msgTmp);
		    affiche_avatar(avatar_haut, avatar);
		    affiche_avatar(avatar_bas, avatar);*/

			P1 = wait_clic();

			if(est_clic_dans_echiquier(P1,c.interface))
			{	
				n1 = converti_point_en_numcase(P1,c.interface);
				calcule_coups_possible(n1,coupPossible);
				
				if(est_valide_clic_joueur(n1,J))
				{
					affiche_piece_en_surbrillance(n1,c.interface);
					affiche_coups_possible(coupPossible, c.interface);
			
					P2 = wait_clic();
					n2 = converti_point_en_numcase(P2,c.interface);
				}
				else
					P1.x = P2.x = -1, P1.y = P2.y = -1;
			}
			else
				P1.x = P2.x = -1, P1.y = P2.y = -1;

		}while(!est_clic_dans_echiquier(P1,c.interface) || !est_coup_valide(n2,coupPossible));
	
		
		/*if(J.player == 2){
			strcpy(msgHaut, msgJeu);
			strcpy(msgBas, msgAttente);
			affiche_info_haut(msgHaut, msgTmp);
		    affiche_info_bas(msgBas, msgTmp);
		}
		if(J.player == 1)
		{
			strcpy(msgBas, msgJeu);
			strcpy(msgHaut, msgAttente);
			affiche_info_haut(msgHaut, msgTmp);
		    affiche_info_bas(msgBas, msgTmp);
	    }*/

		deplace_Piece(n1,n2);

		if(est_pion_promu(n2))
			affiche_menu_choix_promotion_pion(images,J), modifie_pion_promu(n2);			

		J = change_de_joueur(J);
		fill_screen(noir);

	}

	wait_escape();
	libere_image_piece(images);
	libere_tab_coups_possible(coupPossible);

	return 0;
}
