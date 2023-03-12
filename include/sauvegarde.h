#ifndef _JEU_SAUVEGARDE_
#define _JEU_SAUVEGARDE_

#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

#include "../include/moteur.h"
#include "../include/monde.h"

typedef enum
{
    SUCCESS = 0,
    FOPEN_FAIL = 1,
} err_sauv;


err_sauv sauvegarder_config(int largeur_fenetre, int hauteur_fenetre, float volume, int flag_plein_ecran);

err_sauv charger_config();


#endif //_JEU_SAUVEGARDE_