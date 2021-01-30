#ifndef CONTROLEUR
#define CONTROLEUR

#include "modele.h"

choix defini_parametres_du_jeu();
void modifie_pion_promu(NUMCASE n);
void init_jeu(SDL_Surface ***images, BOOL ***coupPossible, choix *c);
 


#endif
