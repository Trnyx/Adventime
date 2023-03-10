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

#include "utilitaire.h"
#include "statistiques.h"
#include "liste.h"





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
    ENTITE_MOB,
} e_entiteType;


/**
 * @brief Enumérateur regroupant les différents tags des monstres
 * 
 * Un compteur du nombre de tags est également initialisé à la fin de l'énumérateur
 */
typedef enum {
    TAG_AUCUN,
    TAG_ANIMAL_VACHE,
    TAG_ANIMAL_COCHON,
    TAG_MONSTRE_BASIC,
    NB_TAGS
} e_entiteTag;


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
    t_vecteur2 position;                                                /**< La position actuelle de l'entité */
    t_vecteur2 direction;                                               /**< La direction (déplacement) actuelle de l'entité */
    e_orientation orientation;                                          /**< L'orientation (regard) actuelle de l'entité */

    e_entiteType entiteType;                                            /**< Le type de l'entité */
    e_entiteTag tag;                                                    /**< Le tag de l'entité */

    SDL_Rect hitbox;                                                    /**< La hitbox de l'entité */


    unsigned int timestampCreation;                                     /**< Le timestamp à laquelle l'entité à été créé */
    unsigned int timestampActualisation;                                /**< Le dernier timestamp à laquelle l'entité à été actualisé */

    boolean destructionInactif;                                         /**< Doit être détruite lorsqu'elle est inactive */


    int  (*update)(t_entite*, float, t_entite *cible);      /**< Fonction d'actualisation de l'entité */
    void (*detruire)(t_entite**);                                       /**< Fonction de suppression de l'entité */
};



typedef struct s_entiteVivante {
    struct s_entite;
    
    // Statistiques
    t_statistiques statistiques;            /**< Les statistiques du Mob */
    t_baseStatistiques baseStatistiques;    /**< Les statistiques de base du MoMob */

} t_entiteVivante;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_liste getEntitesAlentour(t_entite *centre, const e_entiteType type, const float range);

t_entite* creerEntite(const t_vecteur2 position);
void detruireEntite(t_entite **entite);

float calculDistanceEntreEntites(const t_entite *entiteSource, const t_entite *entiteCible);
boolean deplacerEntite(t_entite *entite, const float vitesse);
void orienterEntite(const float angle, t_entite *entite);

void dessinerEntite(t_entite *entite);





#endif