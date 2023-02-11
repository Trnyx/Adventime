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
    t_vecteur2 position;
    t_vecteur2 orientation;

    e_entiteType entiteType;

    SDL_Rect hitbox;

    t_vecteur2 positionDeplacement;
    unsigned int rayonDeplacement;
    e_deplacementType deplacementType;


    time_t timestampCreation;
    time_t timestampActualisation;


    void (*update)(t_moteur*, t_entite*);
    void (*detruire)(t_entite**);
};


/*
typedef struct s_entite {
    struct s_entite_base;

    t_vecteur2 positionDeplacement;
    int rayonDeplacement;
    e_deplacementType deplacementType;

} t_entite;
*/





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_entite* creerEntite(const t_vecteur2 position);
void detruireEntite(t_entite **entite);

float calculDistanceEntreEntites(const t_entite *entiteSource, const t_entite *entiteCible);
boolean deplacerEntite(const t_moteur *moteur, t_entite *entite, const float vitesse);





#endif