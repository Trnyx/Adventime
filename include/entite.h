/**
 * @file entite.h
 * 
 * @brief Module de manipulation des entités
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
#include "animation.h"
#include "liste.h"





/* -------------------------------------------------------------------------- */
/*                                 Enumeration                                */
/* -------------------------------------------------------------------------- */


/**
 * @enum e_entiteType
 * @brief Enumérateur regroupant les différents types d'entité
 * 
 */
typedef enum {
    ENTITE_RIEN,
    ENTITE_ITEM,
    ENTITE_JOUEUR,
    ENTITE_MOB,
    ENTITE_COFFRE,
    ENTITE_COFFRE_INVENTAIRE,
} e_entiteType;


/**
 * @enum e_entiteTag
 * @brief Enumérateur regroupant les différents tags des entités
 * 
 * Un compteur du nombre de tags est également initialisé à la fin de l'énumérateur
 */
typedef enum {
    TAG_AUCUN, // Tag par défaut du joueur
    TAG_ANIMAL_VACHE,
    TAG_ANIMAL_COCHON,
    TAG_MONSTRE_BASIC,
    TAG_COFFRE,
    TAG_BOSS,
    NB_TAGS,
    TAG_JOUEUR,
} e_entiteTag;


/**
 * @enum e_orientation
 * @brief Les orientations
 * 
 * Pour simplifier, nous utilisons les points cardinaux
 * 
 */
typedef enum {
    SUD,
    OUEST,
    EST,
    NORD,
} e_orientation;



/**
 * @enum e_operation
 * @brief Enumérateur regroupant les différentes opérations des mobs
 * 
 */
typedef enum {
    /*! Lorsque le mob est en attente, aucune action particulière ne sera faite */
    ATTENTE,
    /*! Indique que le mob se déplace vers sa cible */
    SE_DEPLACE_VERS,
    /*! Indique que le mob se déplace autour de sa cible */
    SE_DEPLACE_AUTOUR,
    /*! Indique que le mob s'éloigne de sa cible */
    S_ELOIGNE_DE,
    /*! Indique que le mob attaque sa cible */
    ATTAQUE,
} e_operation;





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */
// #include "audio.h"


// Nous avons besoin de définir cette structure "temporaire"
// afin que le compilateur connaisse son existence
typedef struct s_moteur t_moteur;
typedef struct s_audioPack t_audioPack;



/**
 * @struct t_entite
 * @brief Structure modélisant une entité
 */
typedef struct s_entite t_entite;
struct s_entite {
    // #include "attributs_entite.h"
    char *id;                                               /**< L'ID de l'entité */
    t_vecteur2 position;                                    /**< La position actuelle de l'entité */
    t_vecteur2 direction;                                   /**< La direction (déplacement) actuelle de l'entité */
    e_orientation orientation;                              /**< L'orientation (regard) actuelle de l'entité */

    e_entiteType entiteType;                                /**< Le type de l'entité */
    e_entiteTag tag;                                        /**< Le tag de l'entité */

    SDL_FRect hitbox;                                       /**< La hitbox de l'entité */
    float taille;
    t_animation *animation;


    unsigned int timestampCreation;                         /**< Le timestamp à laquelle l'entité à été créé */
    unsigned int timestampActualisation;                    /**< Le dernier timestamp à laquelle l'entité à été actualisé */

    boolean destructionInactif;                             /**< Doit être détruite lorsqu'elle est inactive */
    boolean destructionDelai;                               /**< Doit être détruite lorsqu'elle est inactive */
    boolean interargirAvec;                                 /**< Peut être interargit */


    // Audio
    t_audioPack *bruitages;                                 /**< Les bruitages de l'entité vivante */


    void (*update)(t_entite*, float, t_entite* cible);      /**< Fonction d'actualisation de l'entité */
    void (*detruire)(t_entite**);                           /**< Fonction de suppression de l'entité */
    void (*interaction)(void*, void*);                      /**< Fonction d'interaction avec l'entité */
};



/**
 * @brief 
 * 
 */
typedef struct s_entiteVivante {
    struct s_entite;                        /**< On "étend" la structure "entite" */

    e_operation operation;                  /**< Ce que fait l'entité */
    
    // Statistiques
    t_statistiques statistiques;            /**< Les statistiques de l'entité */
    t_baseStatistiques baseStatistiques;    /**< Les statistiques de base de l'entité */

    // Cooldowns
    unsigned int cooldownAttaque;           /**< Cooldown entre deux attaque (en seconde) */
    unsigned int cooldownRegeneration;      /**< Cooldown pour la régénération (en seconde) */

} t_entiteVivante;



/**
 * @struct t_compteur
 * @brief Structure permettant de regroupé les compteurs d'entités
 * 
 * Les compteurs sont utilisés pour les différents caps
 * 
 */
typedef struct s_compteur {
    int entites;                /**< Compteur d'entités, la limite est définit par ENTITE_CAP */
    int mobs;                   /**< Compteur de mobs, la limite est définit par MOB_CAP */
    int mobAggressifs;          /**< Compteur de mob aggressifs, la limite est définit par MONSTRE_AGGRESSIF_CAP */
    int mobPassifs;             /**< Compteur de monstres passifs, la limite est définit par MONSTRE_PASSIF_CAP */
} t_compteur;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */
typedef struct s_map t_map;


boolean peutApparaitre(const t_vecteur2 position, t_map *map);
t_liste* getEntitesAlentour(t_entite *centre, const e_entiteType type, const float range);
void regenerationEntite(t_entiteVivante *entite);

t_entite* creerEntite(const t_vecteur2 position);
void detruireEntite(t_entite **entite);

float calculDistanceEntreEntites(const t_entite *entiteSource, const t_entite *entiteCible);
boolean deplacerEntite(t_entite *entite, const float vitesse);
void orienterEntite(const float angle, t_entite *entite);

void dessinerEntite(t_entite *entite);





#endif