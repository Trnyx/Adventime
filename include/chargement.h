/**
 * \file chargement.h
 * \author Julien Houget
 * \brief Librairie pour la gestion du chargement du jeu.
 * \date 2023-03-31
 */

#ifndef _JEU_CHARGEMENT_
#define _JEU_CHARGEMENT_

#include <stdio.h>
#include <string.h>

#include "../include/moteur.h"
#include "../include/monde.h"
#include "../include/utilitaire.h"


/***********************************************************************************************
 *                                          Fonctions                                          *
 ***********************************************************************************************/


void charger_entite(t_entite* entite, FILE* fichier);

void charger_entite_vivante(t_entiteVivante* entite, FILE* fichier);

void charger_mob(t_mob* mob, FILE* fichier);

err_sauv charger_joueur(t_joueur* joueur, char* chemin_monde);

err_sauv charger_overworld(t_map* map, FILE* fichier);

err_sauv charger_map(t_map* map, char* chemin_monde, const e_mapType type);

err_sauv charger_global(t_monde* monde, char* chemin_monde);

err_sauv charger_monde(t_monde* monde, char* nom_monde);


#endif //_JEU_CHARGEMENT_