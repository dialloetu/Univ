#include "graphics.h"
#include "Interface.h"

/*********************************************
 *											 *
 *					VUE					     *
 *					 						 *
 *********************************************/

extern SDL_Surface * SDL_screen;

POINT converti_numcase_en_point(NUMCASE n, int interface)
{
	POINT P;

	(interface == 1)? (P.x = 35 + (n.colonne * 100), P.y = 120 + (n.ligne * 100)) : (P.x = 900 -  (n.ligne * 100), P.y = 799 - (n.colonne * 100));

	return centre_point_clic(P,interface);

}

NUMCASE converti_point_en_numcase(POINT P, int interface)
{
	NUMCASE n;

	(interface == 1)? (n.colonne = (P.x - 10)/100, n.ligne = (P.y - 120)/100) : (n.colonne = (810 - P.y)/100, n.ligne = (900 - P.x)/100);

	return n;
}

POINT converti_numcase_en_pointImage(NUMCASE n, int interface)
{
	POINT P;

	(interface == 1)? (P.x = 35 + (n.colonne * 100),P.y = 820 - (n.ligne * 100)) : (P.x = 820 - (n.ligne * 100),P.y = 35 + (n.colonne * 100));

	return P;
}


NUMCASE converti_pointImage_en_numcase(POINT P, int interface)
{
	NUMCASE n;

	(interface == 1)? (n.colonne = (P.x - 35)/100 , n.ligne = (820 - P.y)/100) : (n.colonne = (P.y - 35)/100, n.ligne = (820 - P.x)/100);

	return n;
}



POINT converti_pointClic_en_pointImage(POINT P)
{

	P.x = 35 + ((P.x - 10)/100) * 100;
	P.y = 820 - ((P.y/100) - 1) * 100;
 	
	return P;
}


POINT centre_point_clic(POINT P, int interface)
{

	(interface == 1)? (P.x = 60 + ((P.x - 10)/100) * 100, P.y = 50 + (P.y / 100) * 100) : (P.x = 50 + ((P.x - 10)/100) * 100, P.y = 60 + (P.y/100) * 100);

	return P;

}


BOOL est_clic_dans_echiquier(POINT P, int interface)
{
	if(interface == 1)
		return ((P.x > 10 && P.x < 810) && (P.y > 100 && P.y < 900));

	return ((P.x > 100 && P.x < 900) && (P.y > 10 && P.y < 810));
}

void defini_titre_fenetre(char *titre)
{
     SDL_WM_SetCaption(titre,NULL);
}
 
void initialise_fenetre_graphique(int largeur, int hauteur)
{
     init_graphics(largeur,hauteur);
     affiche_auto_off(); 
}


SDL_Surface **charge_image_piece(int interface)
{
 
     SDL_Surface **images = malloc(12*sizeof(SDL_Surface*));
 
     images[0] = (interface == 1)? SDL_LoadBMP("Chess/roi_blanc.bmp") : SDL_LoadBMP("Chess/roi_blanc.bmp");
     images[1] = (interface == 1)? SDL_LoadBMP("Chess/dame_blanche.bmp") : SDL_LoadBMP("Chess/dame_blanche.bmp");
     images[2] = (interface == 1)? SDL_LoadBMP("Chess/cavalier_blanc.bmp") : SDL_LoadBMP("Chess/cavalier_blanc.bmp");
     images[3] = (interface == 1)? SDL_LoadBMP("Chess/tour_blanche.bmp") : SDL_LoadBMP("Chess/tour_blanche.bmp");
     images[4] = (interface == 1)? SDL_LoadBMP("Chess/fou_blanc.bmp") : SDL_LoadBMP("Chess/fou_blanc.bmp");
     images[5] = (interface == 1)? SDL_LoadBMP("Chess/pion_blanc.bmp") : SDL_LoadBMP("Chess/pion_blanc.bmp");
     images[6] = (interface == 1)? SDL_LoadBMP("Chess/roi_noir.bmp") : SDL_LoadBMP("Chess/roi_noir.bmp");
     images[7] = (interface == 1)? SDL_LoadBMP("Chess/dame_noire.bmp") : SDL_LoadBMP("Chess/dame_noire.bmp");
     images[8] = (interface == 1)? SDL_LoadBMP("Chess/cavalier_noir.bmp") : SDL_LoadBMP("Chess/cavalier_noir.bmp");
     images[9] = (interface == 1)? SDL_LoadBMP("Chess/tour_noire.bmp") : SDL_LoadBMP("Chess/tour_noire.bmp");
     images[10] = (interface == 1)? SDL_LoadBMP("Chess/fou_noir.bmp") : SDL_LoadBMP("Chess/fou_noir.bmp");
     images[11] = (interface == 1)? SDL_LoadBMP("Chess/pion_noir.bmp") : SDL_LoadBMP("Chess/pion_noir.bmp");
 
     return images;
}
  
void libere_image_piece(SDL_Surface **images)
{
 
     int i;
 
     for(i=0; i<12; i++)
         SDL_FreeSurface(images[i]), images[i] = NULL;
 
}


int valide_choix_interface(POINT p)
{
	int choix = 0;
	
	if((p.x >= 150 && p.x <= 530) && (p.y >= 120 && p.y <= 145))
	{
		choix = 1;
	}
	else if((p.x >= 150 && p.x <= 605) && (p.y >= 80 && p.y <= 100))
	{
		choix = 2;
	}
	
	return choix;
}

int valide_choix_modeJeu(POINT p)
{
	int choix = 0;
	
	if((p.x >= 380 && p.x <= 600) && (p.y >= 720 && p.y <= 735))
	{
		choix = 1;
	}
	else if((p.x >= 380 && p.x <= 550) && (p.y >= 690 && p.y <= 705))
	{
		choix = 2;
	}
	
	return choix;
}

CHESSMAN  retourne_choix_promotion_pion(POINT P)
{
	int decalage = HEIGHT/5;
	
	if(P.y > 0 && P.y < decalage)
		return FOU;
	else if(P.y > decalage && P.y < decalage*2)
		return TOUR;
	else if(P.y > decalage*2 && P.y < decalage*3)
		return CAVALIER;
	else if(P.y > decalage*3 && P.y < decalage * 4)
		return DAME;
	else
		return VIDE;
}

void affiche_menu_choix_interface(SDL_Surface *image)
{
	POINT P;

	image = SDL_LoadBMP("chessPic2.bmp");
	SDL_BlitSurface(image,NULL,SDL_screen,NULL);
	
	P.x = 150, P.y = 750;
	aff_pol("JEU D'ECHECS",70,P,noir);

	P.x = 150, P.y = 150;
	aff_pol("1- Interface 1: haut/bas",30,P,noir);
	
	P.x = 150, P.y = 110;
	aff_pol("2- Interface 2: gauche/droite",30,P,noir);

	P.x = 150, P.y = 25;
	aff_pol("Cliquer dans la zone correspondant \xe0 votre choix",20,P,gris);

	affiche_all();
}

void affiche_menu_choix_modeJeu(SDL_Surface *image)
{
	POINT P;

	image = SDL_LoadBMP("chessPic.bmp");
	SDL_BlitSurface(image, NULL, SDL_screen, NULL);
	
	P.x = 320, P.y = 790;
	aff_pol("=== MODE DE JEU ===", 30, P, noir);
	
	P.x  = 380, P.y = 740;
	aff_pol(" 1 - Joueur Vs Joueur", 20, P, noir);
	
	P.x  = 380, P.y = 710;
	aff_pol(" 2 - Joueur Vs IA", 20, P, noir);

	P.x = 320, P.y = 680;
	aff_pol("= Choix : Cliquer sur le menu de votre choix =", 20, P, noir);

	affiche_all();
}

void affiche_menu_choix_promotion_pion(SDL_Surface **images, JOUEUR J)
{
	POINT P1,P2;
	int i, decalage = HEIGHT/5;

	fill_screen(gris);

	P1.x = 0, P1.y = 0;
	P2.x = WIDTH, P2.y = 0;

	for(i=0; i<5; i++)
		draw_line(P1,P2,blanc) , P1.y += decalage, P2.y += decalage;

	P1.x = 50, P1.y -= 20;
	aff_pol("Promouvoir au rang de ",40,P1,blanc);

	P1.x = 50, P1.y = decalage + 20 , P2.x = 110, P2.y = HEIGHT - decalage - 30;
	(J.coul == BLANC)? affiche_dame(P1,BLANC,images[1]) : affiche_dame(P1,NOIR,images[7]);
	aff_pol("Dame",30,P2,blanc);

	P1.y += decalage , P2.y -= decalage;
	(J.coul == BLANC)? affiche_cavalier(P1,BLANC,images[2]) : affiche_cavalier(P1,NOIR,images[8]);
	aff_pol("Cavalier",30,P2,blanc);

	P1.y += decalage ,P2.y -= decalage;
	(J.coul == BLANC)? affiche_tour(P1,BLANC,images[3]) : affiche_tour(P1,NOIR,images[9]);
	aff_pol("Tour",30,P2,blanc);

	P1.y += decalage , P2.y -= decalage;
	(J.coul == BLANC)? affiche_fou(P1,BLANC,images[4]) : affiche_fou(P1,NOIR,images[10]);
	aff_pol("Fou",30,P2,blanc);

	affiche_all();
}

void affiche_damier()
{

	int i,j;
	POINT P1,P2;
    P1.x = 0, P1.y = 90;
	P2.x = WIDTH, P2.y = HEIGHT - 90;
	
	draw_fill_rectangle(P1,P2,bisque);

	P1.x = 10, P1.y = 100;
	P2.x = WIDTH - 10, P2.y = HEIGHT - 100;
	draw_rectangle(P1,P2,sienna);

    P1.x = 10, P1.y = 100;
    P2.x = 110, P2.y = 200;

	for(i=1; i<=8; i++)
      {
		 if(i%2 == 0)
           P1.x = 110 , P2.x = 210 ;
         else
           P1.x = 10 , P2.x = 110;

         for( j=1; j<=8; j += 2)
		   {
			  draw_fill_rectangle(P1,P2,sienna);
				
			  P1.x += 200, P2.x += 200;

		   }
		 P1.y += 100, P2.y += 100;
		 
      }

	P1.x = 10 + 50, P1.y = 104;
	affiche_colonne_repere(P1,84);

	P2.x = 2, P2.y = 150;
	affiche_ligne_repere(P2,9);
}


void affiche_damier2()
{
	
	int i,j;
	POINT P1,P2;
	P1.x = 90, P1.y = 0;
	P2.x = WIDTH - 90, P2.y = HEIGHT;

	draw_fill_rectangle(P1,P2,bisque);

	P1.x = 100, P1.y = 10;
	P2.x = WIDTH - 100, P2.y = HEIGHT - 10;
	draw_rectangle(P1,P2,sienna);	

	P1.x = 100, P1.y = 10;
	P2.x = 200, P2.y = 110;

	for( i=1; i<=8; i++)
	{
		if(i%2 == 0)
			P1.x = 200, P2.x = 300;
		else
			P1.x = 100, P2.x = 200;

		for(j=1; j<=8; j += 2)
		  {
			 draw_fill_rectangle(P1,P2,sienna);

			 P1.x += 200, P2.x += 200; 
		  }
		P1.y += 100, P2.y += 100;
		
	}

	P1.x = 10 + 140, P1.y = 15;
	affiche_colonne_repere(P1,-5);

	P2.x = 91, P2.y = 52;
	affiche_ligne_repere(P2,99);

}

void affiche_colonne_repere(POINT P,int decalage)
{

	int i;
	char *lettre[8] = {"A","B","C","D","E","F","G","H"};
	POINT P2 = P;

	for(i=0; i<8; i++)
	{
		aff_pol(lettre[i],13,P2,noir);
		P2.x += 100;
	}

	P2.x = P.x, P2.y = HEIGHT - decalage;

	for(i=0; i<8; i++)
	{
		aff_pol(lettre[i],13,P2,noir);
		P2.x += 100;
	}

	
}

void affiche_ligne_repere(POINT P, int decalage)
{

	int i;
	char *chiffre[8] = {"1","2","3","4","5","6","7","8"};
	POINT P2 = P;

	for(i=0; i<8; i++)
	{
		aff_pol(chiffre[i],15,P2, noir);
		P2.y += 100;
	}

	P2.x = WIDTH - decalage, P2.y = P.y;

	for(i=0; i<8; i++)
    {

		aff_pol(chiffre[i],15,P2,noir);
		P2.y += 100;
	}
}



void affiche_echiquier(int damier , SDL_Surface **images)
{
	int i,j;
	POINT P;
	NUMCASE n;

	(damier == 1)? affiche_damier() : affiche_damier2();

	for(i=0; i<8; i++)
		for(j=0; j<8; j++)
		{	
			n.ligne = i, n.colonne = j;
			P = converti_numcase_en_pointImage(n,damier);

			if(echiquier[i][j].c == ROI)
				(echiquier[i][j].coul == BLANC)? affiche_roi(P,BLANC,images[0]) : affiche_roi(P,NOIR,images[6]);
			else if(echiquier[i][j].c == DAME)
				(echiquier[i][j].coul == BLANC)? affiche_dame(P,BLANC,images[1]) : affiche_dame(P,NOIR,images[7]);
			else if(echiquier[i][j].c == CAVALIER)
				(echiquier[i][j].coul == BLANC)? affiche_cavalier(P,BLANC,images[2]) : affiche_cavalier(P,NOIR,images[8]);
			else if(echiquier[i][j].c == TOUR)
				(echiquier[i][j].coul == BLANC)? affiche_tour(P,BLANC,images[3]) : affiche_tour(P,NOIR,images[9]);
			else if(echiquier[i][j].c == FOU)
				(echiquier[i][j].coul == BLANC)? affiche_fou(P,BLANC,images[4]) : affiche_fou(P,NOIR,images[10]);
			else if(echiquier[i][j].c == PION)
				(echiquier[i][j].coul == BLANC)? affiche_pion(P,BLANC,images[5]) : affiche_pion(P,NOIR,images[11]);
		}
	affiche_all();	
}


void affiche_roi(POINT P, COLOR couleur, SDL_Surface *roi)
{
	SDL_Rect r;
    r.x = P.x, r.y = P.y;

	if(roi == NULL)
	{
		if(couleur == BLANC)
			roi = SDL_LoadBMP("Chess/roi_blanc.bmp");
		else if(couleur == NOIR)
			roi = SDL_LoadBMP("Chess/roi_noir.bmp");
	}

	SDL_SetColorKey(roi,SDL_SRCCOLORKEY,blanc);
	SDL_BlitSurface(roi,NULL,SDL_screen,&r);		
}


void affiche_dame(POINT P, COLOR couleur, SDL_Surface *dame)
{
	SDL_Rect r;
    r.x = P.x, r.y = P.y;

	if(dame == NULL)
	{
		if(couleur == BLANC)
			dame = SDL_LoadBMP("Chess/dame_blanche.bmp");
		else if(couleur == NOIR)
			dame = SDL_LoadBMP("Chess/dame_noire.bmp");
	}

	SDL_SetColorKey(dame,SDL_SRCCOLORKEY,blanc);
	SDL_BlitSurface(dame,NULL,SDL_screen,&r);

}

void affiche_cavalier(POINT P, COLOR couleur, SDL_Surface *cavalier)
{
	SDL_Rect r;
    r.x = P.x, r.y = P.y;

	if(cavalier == NULL)
	{
		if(couleur == BLANC)
			cavalier = SDL_LoadBMP("Chess/cavalier_blanc.bmp");
		else if(couleur == NOIR)
			cavalier = SDL_LoadBMP("Chess/cavalier_noir.bmp");
	}

	SDL_SetColorKey(cavalier,SDL_SRCCOLORKEY,blanc);
	SDL_BlitSurface(cavalier,NULL,SDL_screen,&r);
		
}

void affiche_tour(POINT P, COLOR couleur, SDL_Surface *tour)
{
	SDL_Rect r;
    r.x = P.x, r.y = P.y;

	if(tour == NULL)
	{
		if(couleur == BLANC)
			tour = SDL_LoadBMP("Chess/tour_blanche.bmp");
		else if(couleur == NOIR)
			tour = SDL_LoadBMP("Chess/tour_noire.bmp");
	}

	SDL_SetColorKey(tour,SDL_SRCCOLORKEY,blanc);
	SDL_BlitSurface(tour,NULL,SDL_screen,&r);
		
}

void affiche_fou(POINT P, COLOR couleur, SDL_Surface *fou)
{
	SDL_Rect r;
    r.x = P.x, r.y = P.y;

	if(fou == NULL)
	{
		if(couleur == BLANC)
			fou = SDL_LoadBMP("Chess/fou_blanc.bmp");
		else if(couleur == NOIR)
			fou = SDL_LoadBMP("Chess/fou_noir.bmp");
	}

	SDL_SetColorKey(fou,SDL_SRCCOLORKEY,blanc);
	SDL_BlitSurface(fou,NULL,SDL_screen,&r);

}

void affiche_pion(POINT P, COLOR couleur, SDL_Surface *pion)
{
	SDL_Rect r;
    r.x = P.x, r.y = P.y;

	if(pion == NULL)
	{
		if(couleur == BLANC)
			pion = SDL_LoadBMP("Chess/pion_blanc.bmp");
		else if(couleur == NOIR)
			pion = SDL_LoadBMP("Chess/pion_noir.bmp");
	}

	SDL_SetColorKey(pion,SDL_SRCCOLORKEY,blanc);
	SDL_BlitSurface(pion,NULL,SDL_screen,&r);
		
}


void affiche_piece_en_surbrillance(NUMCASE n, int interface)
{
	POINT P,P1,P2;
	
	P = converti_numcase_en_point(n,interface);

	P1.x = P.x - 40, P1.y = P.y - 40;
	P2.x = P.x + 40, P2.y = P.y + 40;
	draw_rectangle(P1,P2,vert);

	P1.x -= 10, P1.y -= 10;
	P2.x -= 80, P2.y += 10;
	draw_fill_rectangle(P1,P2,vert);

	P2.x += 90, P2.y = P1.y + 10;
	draw_fill_rectangle(P1,P2,vert);

	P1.x = P2.x - 10, P1.y += 100;
	draw_fill_rectangle(P1,P2,vert);
	
	P1.x += 10,P2.x -= 90, P2.y += 80;
	draw_fill_rectangle(P1,P2,vert);

	affiche_all();
}

void affiche_coups_possible(BOOL **coupPossible, int interface)
{
	int i,j;
	POINT P;
	NUMCASE n;

	for(i=0; i<8; i++)
		for(j=0; j<8; j++)
			if(coupPossible[i][j])
			{	
				n.ligne = i, n.colonne = j;
				P = converti_numcase_en_point(n,interface);
				draw_fill_circle(P,10,vert);
			}

	affiche_all();
}

void affiche_pieces_prise(JOUEUR J,int interface,int *piecePrise, SDL_Surface *image)
{
	POINT P1, P2;

	if(interface == 1)
		(J.coul == BLANC)? (P1.x = 10, P1.y = 0, P2.x = 65, P2.y = 950) : (P1.x = 10, P1.y = 920, P2.x = 65, P2.y = 50);



}

void affiche_cadre_tour_de_jeu(int px, int py, int p1x, int p1y)
{	
	POINT p;
	POINT p1;

	p.x = px;
	p.y = py;
	p1.x = p.x + p1x;
	p1.y = p.y + p1y;
	
	draw_rectangle(p, p1, blanc);
	affiche_all();
}

void affiche_message_tour_de_jeu(char msg[], int taille, int px, int py)
{	
	POINT p;

	p.x = px;
	p.y = py;
	
	aff_pol(msg, taille, p, blanc);
	affiche_all();
}

void affiche_info_bas(char msgInit[], char msgFin[]){
		affiche_cadre_tour_de_jeu(110, 10, 500, 70); 
		affiche_message_tour_de_jeu(msgInit, 20, 150, 70);
		affiche_message_tour_de_jeu(msgFin, 20, 310, 45);
}

void affiche_info_haut(char msgInit[], char msgFin[]){
		affiche_cadre_tour_de_jeu(110, 920, 500, 70); 
		affiche_message_tour_de_jeu(msgInit, 20, 150, 980);
		affiche_message_tour_de_jeu(msgFin, 20, 310, 955);
}

void affiche_avatar(POINT P, SDL_Surface *avatar)
{
	SDL_Rect r;
    r.x = P.x, r.y = P.y;

	avatar = SDL_LoadBMP("user_avatar.bmp");
	SDL_BlitSurface(avatar,NULL,SDL_screen,&r);
	affiche_all();
}




