#include "graphics.h"
#include "modele.h"


/*********************************************
 *											 *
 *					MODELE  			     *
 *					 						 *
 *********************************************/


void init_echiquier()
{
	int i,j;

	for(i=0; i<8; i++)	
		for(j=0; j<8; j++)
			{
			  if(i == 1)
                echiquier[i][j].c = PION, echiquier[i][j].coul = NOIR;
			  else if(i == 6)
				echiquier[i][j].c = PION, echiquier[i][j].coul = BLANC;
			  else
              	echiquier[i][j].c = VIDE, echiquier[i][j].coul = NON_DEFINI;
			}
	echiquier[0][0].c = (echiquier[0][7].c = TOUR), echiquier[0][0].coul = (echiquier[0][7].coul  = NOIR);
	echiquier[0][1].c = (echiquier[0][6].c = CAVALIER), echiquier[0][1].coul = (echiquier[0][6].coul  = NOIR);
	echiquier[0][2].c = (echiquier[0][5].c = FOU), echiquier[0][2].coul = (echiquier[0][5].coul  = NOIR);
	echiquier[0][3].c = ROI, echiquier[0][3].coul = NOIR;
	echiquier[0][4].c = DAME, echiquier[0][4].coul = NOIR;

	echiquier[7][0].c = (echiquier[7][7].c = TOUR), echiquier[7][0].coul = (echiquier[7][7].coul  = BLANC);
    echiquier[7][1].c = (echiquier[7][6].c = CAVALIER), echiquier[7][1].coul = (echiquier[7][6].coul  = BLANC);
    echiquier[7][2].c = (echiquier[7][5].c = FOU), echiquier[7][2].coul = (echiquier[7][5].coul  = BLANC);
    echiquier[7][3].c = ROI, echiquier[7][3].coul = BLANC;
    echiquier[7][4].c = DAME, echiquier[7][4].coul = BLANC;

}


void deplace_Piece(NUMCASE src, NUMCASE dest)
{
	PIECE p;
	
	p = echiquier[src.ligne][src.colonne];

	if(p.c != VIDE)
	{
		echiquier[src.ligne][src.colonne].c = VIDE;
		echiquier[src.ligne][src.colonne].coul = NON_DEFINI;

		echiquier[dest.ligne][dest.colonne] = p;
	}
}


BOOL est_case_vide(NUMCASE n)
{

	if((n.colonne >= 0 && n.colonne <= 7) && (n.ligne >= 0 && n.ligne <= 7))
		if(echiquier[n.ligne][n.colonne].c == VIDE)
			return TRUE;

	return FALSE;
}

BOOL est_valide_clic_joueur(NUMCASE n, JOUEUR J)
{
	PIECE p;
	p = echiquier[n.ligne][n.colonne];
	
	if(p.coul == J.coul)
		return TRUE;
	
	return FALSE;
}

JOUEUR change_de_joueur(JOUEUR J)
{
	if(J.player == 1)
		J.player = 2 ,J.coul = BLANC;
	else
		J.player = 1 ,J.coul = NOIR;

	return J;

}




BOOL est_piece_adversaire_dans_case(NUMCASE n, COLOR coulJoueur)
{
	
	if(((n.ligne >= 0 && n.ligne <= 7) && (n.colonne >= 0 && n.colonne <= 7)) && (echiquier[n.ligne][n.colonne].coul != coulJoueur)) 
		return TRUE;
	
	return FALSE;

}

BOOL **init_tab_coups_possible()
{
	int i;
	BOOL **coupPossible = NULL;

	coupPossible = malloc(8 * sizeof(BOOL*));

	for(i=0; i<8; i++)
		coupPossible[i] = calloc(8,sizeof(BOOL));

	return coupPossible;
}

void reinit_tab_coups_possible(BOOL **coupPossible)
{
	int i,j;

	for(i=0; i<8; i++)
		for(j=0; j<8; j++)
			coupPossible[i][j] = FALSE;

}


void libere_tab_coups_possible(BOOL **coupPossible)
{
	int i;

	for(i=0; i<8; i++)
		free(coupPossible[i]), coupPossible[i] = NULL;

	free(coupPossible);

} 


BOOL est_coup_valide(NUMCASE dest, BOOL **coupPossible)
{
		
	if(((dest.ligne >= 0 && dest.ligne <= 7) && (dest.colonne >= 0 && dest.colonne <= 7)) && (coupPossible[dest.ligne][dest.colonne] == TRUE))
		return TRUE;

	return FALSE;

}	

void calcule_coups_possible_pion_noir(NUMCASE n,BOOL **coupPossible)
{
	 PIECE p;
     NUMCASE n1[6] = {{n.ligne + 1, n.colonne},{n.ligne + 2, n.colonne},{n.ligne + 1,n.colonne - 1 },{n.ligne + 1, n.colonne + 1},{n.ligne, n.colonne - 1},{n.ligne, n.colonne + 1}};
	 COLOR coulJoueur = echiquier[n.ligne][n.colonne].coul;
 
	 (est_case_vide(n1[0]))? coupPossible[n1[0].ligne][n1[0].colonne] = TRUE : FALSE;
 
     if((n.ligne == 1) &&  est_case_vide(n1[1]))
		 coupPossible[n1[1].ligne][n1[1].colonne] = TRUE;
    
	 if(!est_case_vide(n1[2]) && est_piece_adversaire_dans_case(n1[2],coulJoueur))
		coupPossible[n1[2].ligne][n1[2].colonne] = TRUE;

	 if(!est_case_vide(n1[3]) && est_piece_adversaire_dans_case(n1[3],coulJoueur))
		coupPossible[n1[3].ligne][n1[3].colonne] = TRUE;

	 if(n.ligne == 4)
	 {
		p = echiquier[n1[4].ligne][n1[4].colonne];
		(est_piece_adversaire_dans_case(n1[4],coulJoueur) && p.c == PION)? coupPossible[n1[4].ligne][n1[4].colonne] = TRUE : FALSE;

		p = echiquier[n1[5].ligne][n1[5].colonne];
		(est_piece_adversaire_dans_case(n1[5],coulJoueur) && p.c == PION)? coupPossible[n1[5].ligne][n1[5].colonne] = TRUE : FALSE;

	 }
     
}


void calcule_coups_possible_pion_blanc(NUMCASE n,BOOL **coupPossible)
{
      PIECE p;
      NUMCASE n1[6] = {{n.ligne - 1, n.colonne},{n.ligne - 2, n.colonne},{n.ligne - 1,n.colonne + 1 },{n.ligne - 1, n.colonne - 1},{n.ligne, n.colonne - 1},{n.ligne, n.colonne + 1}};
      COLOR coulJoueur = echiquier[n.ligne][n.colonne].coul;
      
      (est_case_vide(n1[0]))? coupPossible[n1[0].ligne][n1[0].colonne] = TRUE : FALSE;
 
      if((n.ligne == 6) &&  est_case_vide(n1[1]))
          coupPossible[n1[1].ligne][n1[1].colonne] = TRUE;
          
      if(!est_case_vide(n1[2]) && est_piece_adversaire_dans_case(n1[2],coulJoueur))
         coupPossible[n1[2].ligne][n1[2].colonne] = TRUE;
 
      if(!est_case_vide(n1[3]) && est_piece_adversaire_dans_case(n1[3],coulJoueur))
         coupPossible[n1[3].ligne][n1[3].colonne] = TRUE;
 
      if(n.ligne == 3)
      {
         p = echiquier[n1[4].ligne][n1[4].colonne];
         (est_piece_adversaire_dans_case(n1[4],coulJoueur) && p.c == PION)? coupPossible[n1[4].ligne][n1[4].colonne] = TRUE : FALSE;
 
        p = echiquier[n1[5].ligne][n1[5].colonne];
         (est_piece_adversaire_dans_case(n1[5],coulJoueur) && p.c == PION)? coupPossible[n1[5].ligne][n1[5].colonne] = TRUE : FALSE;
 
      }
 
}



void calcule_coups_possible_fou(NUMCASE n, BOOL **coupPossible)
{
	int i;
	COLOR coulJoueur = echiquier[n.ligne][n.colonne].coul;
	NUMCASE n1[4] = {{n.ligne + 1, n.colonne - 1},{n.ligne - 1, n.colonne + 1},{n.ligne + 1, n.colonne + 1},{n.ligne - 1, n.colonne - 1}};

	for(i=0; i<8; i++)
	{
		(est_case_vide(n1[0]))? coupPossible[n1[0].ligne][n1[0].colonne] = TRUE, n1[0].colonne -= 1, n1[0].ligne += 1 : ((est_piece_adversaire_dans_case(n1[0],coulJoueur))? coupPossible[n1[0].ligne][n1[0].colonne] = TRUE : FALSE );
		
		(est_case_vide(n1[1]))? coupPossible[n1[1].ligne][n1[1].colonne] = TRUE ,n1[1].colonne += 1, n1[1].ligne -= 1 : ((est_piece_adversaire_dans_case(n1[1],coulJoueur))? coupPossible[n1[1].ligne][n1[1].colonne] = TRUE : FALSE );
		
		(est_case_vide(n1[2]))? coupPossible[n1[2].ligne][n1[2].colonne] = TRUE, n1[2].colonne += 1, n1[2].ligne += 1 : ((est_piece_adversaire_dans_case(n1[2],coulJoueur))? coupPossible[n1[2].ligne][n1[2].colonne] = TRUE : FALSE );
		
		(est_case_vide(n1[3]))? coupPossible[n1[3].ligne][n1[3].colonne] = TRUE, n1[3].colonne -= 1, n1[3].ligne -= 1 : ((est_piece_adversaire_dans_case(n1[3],coulJoueur))? coupPossible[n1[3].ligne][n1[3].colonne] = TRUE : FALSE );

	}

}


void calcule_coups_possible_tour(NUMCASE n, BOOL **coupPossible)
{
	int i;
	COLOR coulJoueur = echiquier[n.ligne][n.colonne].coul;
	NUMCASE n1[4] = {{n.ligne + 1, n.colonne},{n.ligne - 1, n.colonne},{n.ligne, n.colonne - 1},{n.ligne, n.colonne + 1}};


	for(i=0; i<8; i++)
	{
		(est_case_vide(n1[0]))? coupPossible[n1[0].ligne][n1[0].colonne] = TRUE, n1[0].ligne += 1 : ((est_piece_adversaire_dans_case(n1[0],coulJoueur))? coupPossible[n1[0].ligne][n1[0].colonne] = TRUE : FALSE );
		
		(est_case_vide(n1[1]))? coupPossible[n1[1].ligne][n1[1].colonne] = TRUE, n1[1].ligne -= 1 : ((est_piece_adversaire_dans_case(n1[1],coulJoueur))? coupPossible[n1[1].ligne][n1[1].colonne] = TRUE : FALSE );
		
		(est_case_vide(n1[2]))? coupPossible[n1[2].ligne][n1[2].colonne] = TRUE, n1[2].colonne -= 1: ((est_piece_adversaire_dans_case(n1[2],coulJoueur))? coupPossible[n1[2].ligne][n1[2].colonne] = TRUE : FALSE );
		
		(est_case_vide(n1[3]))? coupPossible[n1[3].ligne][n1[3].colonne] = TRUE, n1[3].colonne += 1: ((est_piece_adversaire_dans_case(n1[3],coulJoueur))? coupPossible[n1[3].ligne][n1[3].colonne] = TRUE : FALSE );

	}

}


void calcule_coups_possible_cavalier(NUMCASE n, BOOL **coupPossible)
{
	int i;
	COLOR coulJoueur = echiquier[n.ligne][n.colonne].coul;
	NUMCASE n1[8] = {{n.ligne + 1,n.colonne - 2},{n.ligne + 2,n.colonne - 1},{n.ligne + 2,n.colonne + 1},{n.ligne + 1, n.colonne + 2},{n.ligne - 1,n.colonne + 2},{n.ligne - 2, n.colonne + 1},{n.ligne - 2, n.colonne - 1},{n.ligne - 1, n.colonne - 2}};
	

	for(i=0; i<8; i++)
		if(est_case_vide(n1[i]) || est_piece_adversaire_dans_case(n1[i],coulJoueur))
			coupPossible[n1[i].ligne][n1[i].colonne] = TRUE;

}


void calcule_coups_possible_roi(NUMCASE n, BOOL **coupPossible)
{
	int i;
	COLOR coulJoueur = echiquier[n.ligne][n.colonne].coul;
	NUMCASE n1[8] = {{n.ligne + 1,n.colonne},{n.ligne - 1, n.colonne},{n.ligne,n.colonne - 1},{n.ligne, n.colonne + 1},{n.ligne + 1,n.colonne - 1},{n.ligne - 1, n.colonne + 1},{n.ligne + 1, n.colonne + 1},{n.ligne - 1, n.colonne - 1}};

	for(i=0; i<8; i++)
		if(est_case_vide(n1[i]) || est_piece_adversaire_dans_case(n1[i],coulJoueur))
			coupPossible[n1[i].ligne][n1[i].colonne] = TRUE;
}


void calcule_coups_possible_dame(NUMCASE n, BOOL **coupPossible)
{
	int i;
	COLOR coulJoueur = echiquier[n.ligne][n.colonne].coul;	
	NUMCASE n1[8] = {{n.ligne + 1,n.colonne},{n.ligne - 1, n.colonne},{n.ligne,n.colonne - 1},{n.ligne, n.colonne + 1},{n.ligne + 1,n.colonne - 1},{n.ligne - 1, n.colonne + 1},{n.ligne + 1, n.colonne + 1},{n.ligne - 1, n.colonne - 1}};
	
	for(i=0; i<8; i++)
	{
		(est_case_vide(n1[0]))? coupPossible[n1[0].ligne][n1[0].colonne] = TRUE , n1[0].ligne += 1 : (est_piece_adversaire_dans_case(n1[0],coulJoueur))? coupPossible[n1[0].ligne][n1[0].colonne] = TRUE : FALSE;
		
		(est_case_vide(n1[1]))? coupPossible[n1[1].ligne][n1[1].colonne] = TRUE , n1[1].ligne -= 1 : (est_piece_adversaire_dans_case(n1[1],coulJoueur))? coupPossible[n1[1].ligne][n1[1].colonne] = TRUE : FALSE;
		
		(est_case_vide(n1[2]))? coupPossible[n1[2].ligne][n1[2].colonne] = TRUE , n1[2].colonne -= 1 : (est_piece_adversaire_dans_case(n1[2],coulJoueur))?	coupPossible[n1[2].ligne][n1[2].colonne] = TRUE : FALSE;	
		
		(est_case_vide(n1[3]))? coupPossible[n1[3].ligne][n1[3].colonne] = TRUE , n1[3].colonne += 1 : (est_piece_adversaire_dans_case(n1[3],coulJoueur))? coupPossible[n1[3].ligne][n1[3].colonne] = TRUE : FALSE;
		
		(est_case_vide(n1[4]))? coupPossible[n1[4].ligne][n1[4].colonne] = TRUE, n1[4].colonne -= 1, n1[4].ligne += 1 : (est_piece_adversaire_dans_case(n1[4],coulJoueur))? coupPossible[n1[4].ligne][n1[4].colonne] = TRUE : FALSE;
		
		(est_case_vide(n1[5]))? coupPossible[n1[5].ligne][n1[5].colonne] = TRUE ,n1[5].colonne += 1, n1[5].ligne -= 1 : (est_piece_adversaire_dans_case(n1[5],coulJoueur))? coupPossible[n1[5].ligne][n1[5].colonne] = TRUE : FALSE;
		
		(est_case_vide(n1[6]))? coupPossible[n1[6].ligne][n1[6].colonne] = TRUE, n1[6].colonne += 1, n1[6].ligne += 1 : (est_piece_adversaire_dans_case(n1[6],coulJoueur))? coupPossible[n1[6].ligne][n1[6].colonne] = TRUE : FALSE;
		
		(est_case_vide(n1[7]))? coupPossible[n1[7].ligne][n1[7].colonne] = TRUE, n1[7].colonne -= 1, n1[7].ligne -= 1 : (est_piece_adversaire_dans_case(n1[7],coulJoueur))? coupPossible[n1[7].ligne][n1[7].colonne] = TRUE : FALSE;

	}

}



void calcule_coups_possible(NUMCASE n, BOOL **coupPossible)
{
	PIECE p;
	p = echiquier[n.ligne][n.colonne];


	if(p.c == PION)
    {
	  	if(p.coul == NOIR)
			calcule_coups_possible_pion_noir(n,coupPossible);
	  	else
			calcule_coups_possible_pion_blanc(n,coupPossible);
	}
	else if(p.c == ROI)
		calcule_coups_possible_roi(n,coupPossible);
	else if(p.c == DAME)
		calcule_coups_possible_dame(n,coupPossible);
	else if(p.c == TOUR)
		calcule_coups_possible_tour(n,coupPossible);
	else if(p.c == FOU)
		calcule_coups_possible_fou(n,coupPossible);
	else if(p.c == CAVALIER)
		calcule_coups_possible_cavalier(n,coupPossible);

}

BOOL est_pion_promu(NUMCASE n)
{
	PIECE p;
	p = echiquier[n.ligne][n.colonne];

	if(!est_case_vide(n) && p.c == PION)
	{
		if(p.coul == BLANC)
			return (n.ligne == 0)? TRUE : FALSE;
		else
			return (n.ligne == 7)? TRUE : FALSE;
	}

	return FALSE;

}


