/**
 * \file sauvegarde.h
 * \brief Librairie pour la gestion de la sauvegarde et du chargement du jeu.
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

/* -------------------------------------------------------------------------- */
/*                                 Fonctions                                  */
/* -------------------------------------------------------------------------- */

/**
 * \enum err_sauv
 * \brief Définit les erreurs possibles durant la sauvegarde.
*/
typedef enum
{
    SUCCESS = 0,
    FOPEN_FAIL = 1,
} err_sauv;


   /**
    * \brief Sauvegarde les paramètres d'options globaux au jeu.
    *
    * \param largeur_fenetre Largeur de la fenêtre.
    * \param hauteur_fenetre Hauteur de la fenêtre.
    * \param volume Volume sonore général (musique, effets sonores).
    * \param flag_plein_ecran Stipule si la fenêtre doit être en plein écran.
    * \return err_sauv, un code d'erreur (0 si succès).
    */
err_sauv sauvegarder_config(int largeur_fenetre, int hauteur_fenetre, float volume_general,
    float volume_musique, float volume_bruitage, int flag_plein_ecran);

/**
 * \brief Sauvegarde les données du joueur.
 *
 * \param joueur Le joueur à sauvegarder.
 * \param chemin_monde Le chemin d'accès au fichier de sauvegarde du monde.
 * \return err_sauv, un code d'erreur (0 si succès).
 */
err_sauv sauvegarder_joueur(t_joueur* joueur, char* chemin_monde);

/**
 * \brief Sauvegarde les données de la map.
 * 
 * \param map La map à sauvegarder.
 * \param chemin_monde Le chemin d'accès au fichier de sauvegarde du monde. 
 * \return err_sauv, un code d'erreur (0 si succès).
 */
err_sauv sauvegarder_map(t_map* map, char* chemin_monde);

/**
 * \brief Sauvegarde les données globales de la map.
 *
 * \param seed Le nombre permettant de générer la map.
 * \param temps Le temps du jeu.
 * \param chemin_monde Le chemin d'accès au fichier de sauvegarde du monde.
 * \return err_sauv, un code d'erreur (0 si succès).
 */
err_sauv sauvegarder_monde(t_monde* monde, char* nom_monde);

/**
 * \brief Sauvegarde le monde du jeu, c'est-à-dire les données du joueur, de la map et des données globales.
 *
 * \param monde Le monde à sauvegarder.
 * \param nom_monde Le nom du mon de à sauvegarder, pour obtenir le chemin d'accès aux fichiers.
 * \return err_sauv, un code d'erreur (0 si succès).
 */
err_sauv sauvegarder_monde(t_monde* monde, char* nom_monde);

#endif //_JEU_SAUVEGARDE_