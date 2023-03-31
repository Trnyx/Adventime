/**
 * \file sauvegarde.h
 * \brief Librairie pour la gestion de la sauvegardedu jeu.
 * \author Julien Houget
 * \date 12/03/23
 */

#ifndef _JEU_SAUVEGARDE_
#define _JEU_SAUVEGARDE_

#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

#include "../include/moteur.h"
#include "../include/monde.h"
#include "../include/utilitaire.h"

 /* -------------------------------------------------------------------------- */
 /*                                 Fonctions                                  */
 /* -------------------------------------------------------------------------- */


err_sauv sauvegarder_config(int largeur_fenetre, int hauteur_fenetre, float volume_general,
    float volume_musique, float volume_bruitage, int flag_plein_ecran);

void sauvegarder_entite(t_entite* entite, FILE* fichier);

void sauvegarder_entite_vivante(t_entiteVivante* entite, FILE* fichier);

void sauvegarder_mob(t_mob* mob, FILE* fichier);

err_sauv sauvegarder_joueur(t_joueur* joueur, char* chemin_monde);

err_sauv sauvegarder_map(t_map* map, char* chemin_monde, const e_mapType type);

err_sauv sauvegarder_global(t_monde* monde, char* chemin_monde);

err_sauv sauvegarder_monde(t_monde* monde, char* nom_monde);


#endif //_JEU_SAUVEGARDE_