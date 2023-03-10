/**
 * @file entite.h
 * 
 * @brief 
 * 
 * @author Clément Hibon
 * @date 3 février
 * @version 1.1
 */





#ifndef _JEU_ENTITE_
#define _JEU_ENTITE_





#include <SDL2/SDL.h>
#include <time.h>

#include "utilitaire.h"





/* -------------------------------------------------------------------------- */
/*                                 Enumeration                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 */
typedef enum {
    ENTITE_RIEN,
    ENTITE_JOUEUR,
    ENTITE_ANIMAL,
    ENTITE_MONSTRE_AGGRESSIF,
    ENTITE_MONSTRE_PASSIF,
} e_entiteType;


/**
 * @brief 
 * 
 */
typedef enum {
    DEPLACEMENT_JOUEUR = -1,
    DEPLACEMENT_STATIQUE,
    DEPLACEMENT_NORMAL,
    DEPLACEMENT_COMBAT,
    DEPLACEMENT_ATTAQUE,
} e_deplacementType;


/**
 * @brief 
 * 
 */
typedef enum {
    SUD,
    OUEST,
    EST,
    NORD,
} e_orientation;





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


// Nous avons besoin de définir cette structure "temporaire"
// afin que le compilateur connaisse son existence
typedef struct s_moteur t_moteur;



/**
 * @struct t_entite
 * @brief Structure modélisant une entité
 */
typedef struct s_entite t_entite;
struct s_entite {
    // #include "attributs_entite.h"
    unsigned int id;
    t_vecteur2 position;                        /**< La position actuelle de l'entité */
    t_vecteur2 direction;                       /**< La direction (déplacement) actuelle de l'entité */
    e_orientation orientation;                  /**< L'orientation (regard) actuelle de l'entité */

    e_entiteType entiteType;                    /**< Le type de l'entité */

    SDL_Rect hitbox;                            /**< La hitbox de l'entité */


    unsigned int timestampCreation;             /**< Le timestamp à laquelle l'entité à été créé */
    unsigned int timestampActualisation;        /**< Le dernier timestamp à laquelle l'entité à été actualisé */


    int  (*update)(t_entite*, const float);      /**< Fonction d'actualisation de l'entité */
    void (*detruire)(t_entite**);                           /**< Fonction de suppression de l'entité */
};



/**
 * @brief Structure représentant un mob
 * 
 * Un mob est une entité mobile (mob correspond à l'abreviation)
 */
typedef struct s_mob {
    struct s_entite;                        /**< inclue les bases d'une entité */

    // Deplacement 
    unsigned int rayonDeplacement;          /**< Le rayon dans lequel le mob peut se déplacer */
    t_vecteur2 positionDeplacement;         /**< La position à laquelle le mob peut se déplacer */

    unsigned int timestampDebutDeplacement; /**< Timestamp de départ de déplacement */
    unsigned int timestampFinDeplacement;   /**< Timestamp de fin de déplacement */
    unsigned int delaiAttenteDeplacement;   /**< Temps d'attente entre deux déplacements (en seconde) */
    
    e_deplacementType deplacementType;      /**< Le type de déplacement du mob */

    // Attaque
    unsigned int timestampAttaque;          /**< Timestamp de la dernière attaque */
    unsigned int delaiAttenteAttaque;       /**< Temps d'attente entre deux attaque (en seconde) */
} t_mob;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_entite* creerEntite(const t_vecteur2 position);
t_mob* creerMob(const t_vecteur2 position);
void detruireEntite(t_entite **entite);
void detruireMob(t_mob **mob);

float calculDistanceEntreEntites(const t_entite *entiteSource, const t_entite *entiteCible);
boolean deplacerEntite(t_entite *entite, const float vitesse);
void orienterEntite(const float angle, t_entite *entite);

void dessinerEntite(t_entite *entite);

int (*getDeplacement(e_deplacementType deplacement))(t_mob*, const float);





#endif