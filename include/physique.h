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
#include "moteur.h"
#include "audio.h"





/* -------------------------------------------------------------------------- */
/*                                 Constantes                                 */
/* -------------------------------------------------------------------------- */

/* ---------------------------------- Temps --------------------------------- */

// Nombre de jour par heure (vrai) 
#define NOMBRE_JOUR 3
// Le temps d'un jour dans le jeu (en seconde)
// Nombre de seconde réelles pour faire un jour dans le jeu
#define TEMPS_JOUR (3600 / NOMBRE_JOUR)

// Le temps d'une heure dans le jeu (en seconde)
// Nombre de seconde réelles pour faire une heure dans le jeu
// #define TEMPS_HEURE (TEMPS_JOUR / 24)
// Le temps d'une minute dans le jeu (en seconde)
// Nombre de seconde réelles pour faire une minute dans le jeu
// #define TEMPS_MINUTE (TEMPS_HEURE / 60)





/* --------------------------------- Joueur --------------------------------- */

// Le rayon dans lequel la physique du jeu est concidérée comme active
#define JOUEUR_RAYON_ACTIF (TAILLE_CHUNK + (TAILLE_CHUNK / 2))
// Le rayon dans lequel la physique du jeu est concidérée comme semi active
#define JOUEUR_RAYON_SEMIACTIF (JOUEUR_RAYON_ACTIF * 2) 
// Le rayon dans lequel la physique du jeu est inactive
#define JOUEUR_RAYON_INACTIF (JOUEUR_RAYON_ACTIF * 4)





/* --------------------------------- Entite --------------------------------- */

// Le nombre d'entité total possible
#define MOB_CAP 256
#define MONSTRE_AGGRESSIF_CAP 20


#define MONSTRE_RAYON_COMBAT_DETECTION 4.0
#define MOB_RAYON_COMBAT_POSITIONNEMENT 10.0
#define MOB_RAYON_COMBAT_RETRAIT 1.5
#define MOB_RAYON_COMBAT_ATTAQUE 1.8


// La durée maximale de déplacement d'un mob [en seconde]
#define MOB_DUREE_DEPLACEMENT 5
// La durée minimale d'attente entre deux déplacements [en seconde]
#define MOB_DELAI_MIN_ENTRE_DEPLACEMENT 3
// La durée maximale d'attente entre deux déplacements [en seconde]
#define MOB_DELAI_MAX_ENTRE_DEPLACEMENT 8


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


void update(t_moteur *moteur, t_audio *audio);

