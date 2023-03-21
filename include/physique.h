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
#include "joueur.h"
#include "temps.h"





/* -------------------------------------------------------------------------- */
/*                                 Constantes                                 */
/* -------------------------------------------------------------------------- */

/* ------------------------------ Temps en jeu ------------------------------ */

// Nombre de jour par heure (vrai) 
#define NOMBRE_JOUR 4
// Le temps d'un jour dans le jeu (en seconde)
// Nombre de seconde réelles pour faire un jour dans le jeu
#define TEMPS_JOUR (3600 / NOMBRE_JOUR)

// L'heure (en jeu) à laquelle il est concidéré que c'est le matin
#define HEURE_JEU_MATIN 8 
// L'heure (en jeu) à laquelle il est concidéré que c'est l'après midi
#define HEURE_JEU_APRES_MIDI 14
// L'heure (en jeu) à laquelle il est concidéré que c'est la nuit
#define HEURE_JEU_NUIT 20

// L'heure (en jeu) à laquelle il est concidéré que le soleil se lève
#define HEURE_JEU_LEVE_SOLEIL 6 
// L'heure (en jeu) à laquelle il est concidéré que le soleil se couche
#define HEURE_JEU_COUCHE_SOLEIL 18





/* ------------------------------- Temps vrai ------------------------------- */

// Heure (vrai) à laquelle il est concidéré qu'il fait jour
#define HEURE_VRAI_JOUR 6
// Heure (vrai) à laquelle il est concidéré qu'il fait nuit
#define HEURE_VRAI_NUIT 20
// Heure (vrai) à laquelle on change de journée (pour le renouvellement des ressources dans le jeu)
#define HEURE_VRAI_RENOUVELLEMENT 4





/* --------------------------------- Joueur --------------------------------- */

// Le rayon dans lequel la physique du jeu est concidérée comme active
#define JOUEUR_RAYON_ACTIF (TAILLE_CHUNK + (TAILLE_CHUNK / 2))
// Le rayon dans lequel la physique du jeu est concidérée comme semi active
#define JOUEUR_RAYON_SEMIACTIF (JOUEUR_RAYON_ACTIF * 3) 
// Le rayon dans lequel la physique du jeu est inactive
#define JOUEUR_RAYON_INACTIF (JOUEUR_RAYON_ACTIF * 4)





/* ----------------------------- Mobs Et Entités ---------------------------- */

// Le nombre d'entité total possible
#define ENTITE_CAP 256
// Le nombre de mob total possible
#define MOB_CAP 128
// Le nombre maximum de montstre aggressif
#define MONSTRE_AGGRESSIF_CAP 16
// Le nombre maximum d'animaux
#define MONSTRE_PASSIF_CAP 24


// Rayon dans lequel un monstre détecte un joueur pour se mettre en combat
#define MONSTRE_RAYON_COMBAT_DETECTION 4.5
// Rayon dans lequel les mobs se positionne (suivent leur cible) pour combattre
#define MOB_RAYON_COMBAT_POSITIONNEMENT 6.0
// Rayon dans lequel les mobs recul face à leur cible
#define MOB_RAYON_COMBAT_RETRAIT 1.8
// Rayon dans lequel les mobs sont suffisamment proche pour attaquer
#define MOB_RAYON_COMBAT_ATTAQUE 2.2

// Rayon dans lequel le boss détecte le joueur
#define BOSS_RAYON_COMBAT_DETECTION 6.0
// Rayon dans lequel le boss se positionne
#define BOSS_RAYON_COMBAT_POSITIONNEMENT 8.0


//
#define MOB_VITESSE_MODIFICATEUR_POSITIONNEMENT
//
#define MOB_VITESSE_MODIFICATEUR_AUTOUR 0.5
//
#define MOB_VITESSE_MODIFICATEUR_ELOIGNEMENT 0.8
//
#define MOB_VITESSE_MODIFICATEUR_ATTAQUE 1.6


// La durée maximale de déplacement d'un mob [en seconde]
#define MOB_DUREE_DEPLACEMENT (5 * FPS)

// La durée minimale d'attente entre deux déplacements [en seconde]
#define MOB_DELAI_MIN_ENTRE_DEPLACEMENT (3 * FPS)
// La durée maximale d'attente entre deux déplacements [en seconde]
#define MOB_DELAI_MAX_ENTRE_DEPLACEMENT (8 * FPS)

// La durée minimale d'attente entre deux attaques [en seconde]
#define MOB_DELAI_MIN_ENTRE_ATTAQUE (2 * FPS)
// La durée maximale d'attente entre deux attaques [en seconde]
#define MOB_DELAI_MAX_ENTRE_ATTAQUE (5 * FPS)

// La durée minimale d'attente entre deux bruitages [en seconde]
#define MOB_DELAI_MIN_ENTRE_BRUIT (12 * FPS)
// La durée maximale d'attente entre deux bruitages [en seconde]
#define MOB_DELAI_MAX_ENTRE_BRUIT (20 * FPS)


// La durée de vie minimum d'une entité
#define ENTITE_DUREE_VIE_MIN TEMPS_JOUR / 4
// La durée de vie maximum d'une entité
#define ENTITE_DUREE_VIE_MAX TEMPS_JOUR / 2



// La probabimité que le mob ne face rien
#define PROBABILITE_MOUVEMENT_AUCUN 20
// La probabimité que le mob se tourne
#define PROBABILITE_MOUVEMENT_ROTATION 55
// La probabimité que le mob se déplace 
#define PROBABILITE_MOUVEMENT_DEPLACEMENT 100

//
#define PROBABILITE_APPARITION_MONSTRE 30

// Rayon dans lequel un animal détecte un troupeau
#define ANIMAL_RAYON_DETECTION_TROUPEAU 12
// Rayon dans lequel un animal se concidère comme trop loin du troupeau
#define ANIMAL_RAYON_TROP_LOIN_TROUPEAU 5





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


void update(t_map *map, t_joueur *joueur);

