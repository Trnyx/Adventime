/**
 * @file physique.h
 * 
 * @brief 
 * 
 * @author Clément Hibon
 * @date 10 février
 * @version 1.1
 */





#include "map.h"





/* -------------------------------------------------------------------------- */
/*                                 Constantes                                 */
/* -------------------------------------------------------------------------- */

/* ---------------------------------- Temps --------------------------------- */

// Nombre de jour par heure (vrai) 
#define NOMBRE_JOUR 4
// Le temps d'un jour dans le jeu (en seconde)
#define TEMPS_JOUR 3600 / NOMBRE_JOUR





/* --------------------------------- Joueur --------------------------------- */

// Le rayon dans lequel la physique du jeu est concidérée comme active
#define JOUEUR_RAYON_ACTIF (TAILLE_CHUNK + (TAILLE_CHUNK / 2))
// Le rayon dans lequel la physique du jeu est concidérée comme semi active
#define JOUEUR_RAYON_SEMIACTIF (JOUEUR_RAYON_ACTIF * 2) 
// Le rayon dans lequel la physique du jeu est inactive
#define JOUEUR_RAYON_INACTIF (JOUEUR_RAYON_ACTIF * 4)





/* --------------------------------- Entite --------------------------------- */

// Le nombre d'entité total possible
#define MOB_CAP 100
#define MONSTRE_AGGRESSIF_CAP 20


#define ENTITE_RAYON_COMBAT_POSITIONNEMENT 12
#define ENTITE_RAYON_COMBAT_RETRAIT 1
#define ENTITE_RAYON_COMBAT_ATTAQUE 2

// La durée de vie minimum d'une entité
#define ENTITE_DUREE_VIE_MIN TEMPS_JOUR / 4
// La durée de vie maximum d'une entité
#define ENTITE_DUREE_VIE_MAX TEMPS_JOUR / 2



// La probabimité que l'entité ne se déplace pas
#define PROBABILITE_DEPLACEMENT_AUCUN 40 
// La probabimité que l'entité se déplace 
#define PROBABILITE_DEPLACEMENT_POTENTIEL 75 
// La probabimité que l'entité se déplace obligatoirement 
#define PROBABILITE_DEPLACEMENT_OBLIGATOIRE 100





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


void update(t_moteur *moteur);

