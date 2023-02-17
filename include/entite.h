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


typedef enum {
    ENTITE_RIEN,
    ENTITE_JOUEUR,
    ENTITE_ANIMAL,
    ENTITE_MONSTRE_AGGRESSIF,
    ENTITE_MONSTRE_PASSIF,
} e_entiteType;


typedef enum {
    DEPLACEMENT_JOUEUR = -1,
    DEPLACEMENT_STATIQUE,
    DEPLACEMENT_NORMAL,
    DEPLACEMENT_COMBAT,
} e_deplacementType;





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
    t_vecteur2 position;                /**< La position actuelle de l'entité */
    t_vecteur2 orientation;             /**< L'orientation actuelle de l'entité */

    e_entiteType entiteType;            /**< Le type de l'entité */

    SDL_Rect hitbox;                    /**< La hitbox de l'entité */


    time_t timestampCreation;           /**< Le timestamp à laquelle l'entité à été créé */
    time_t timestampActualisation;      /**< Le dernier timestamp à laquelle l'entité à été actualisé */


    void (*update)(t_moteur*, t_entite*);   /**< Fonction d'actualisation de l'entité */
    void (*detruire)(t_entite**);           /**< Fonction de suppression de l'entité */
};



/**
 * @brief Structure représentant un mob
 * 
 * Un mob est une entité mobile (mob correspond à l'abreviation)
 */
typedef struct s_mob {
    struct s_entite;                        /**< inclue les bases d'une entité */

    int rayonDeplacement;                   /**< Le rayon dans lequel le mob peut se déplacer */
    t_vecteur2 positionDeplacement;         /**< La position à laquelle le mob peut se déplacer */
    
    e_deplacementType deplacementType;      /**< Le type de déplacement du mob */
} t_mob;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_entite* creerEntite(const t_vecteur2 position);
t_mob* creerMob(const t_vecteur2 position);
void detruireEntite(t_entite **entite);

float calculDistanceEntreEntites(const t_entite *entiteSource, const t_entite *entiteCible);
boolean deplacerEntite(const t_moteur *moteur, t_entite *entite, const float vitesse);





#endif