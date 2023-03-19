/**
 * @file initialiseur.h
 * 
 * @brief Module pour les initisalisations et destructions générales
 * 
 * @author Eliott Remars & Clément Hibon
 * @date 3 février
 * @version 1.1
 */



#ifndef _JEU_INITIALISEUR_
#define _JEU_INITIALISEUR_





#include "moteur.h"
#include "audio.h"




/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


void initAll(t_moteur **moteur, t_audio **audio);
void detruireAll(t_moteur *moteur, t_audio *audio);







#endif