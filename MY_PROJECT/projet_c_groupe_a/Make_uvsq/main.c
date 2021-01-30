#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include "Interface.h"
#include "controleur.h"

int main()
{
	SDL_Surface *rey = NULL, *roi = NULL;
	POINT P = {235, 220};	
    parametrer_info_jeu();

	WIDTH = LARGEUR, HEIGHT = HAUTEUR;

	init_graphics(WIDTH,HEIGHT);
	affiche_auto_off();
	affiche_damier();
	affiche_roi(P,BLANC,roi);

	P.x = 335, P.y = 220;
	affiche_roi(P,NOIR,rey);
	wait_clic();

	return 0;


}
