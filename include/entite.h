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
    e_entiteType entiteType;

    t_vecteur2 position;
    t_vecteur2 orientation;

    SDL_Rect hitbox;


    void (*detruire)(t_entite**);
};





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_entite* creerEntite(const t_vecteur2 position);
void detruireEntite(t_entite **entite);

float calculDistanceEntreEntites(const t_entite *entiteSource, const t_entite *entiteCible);
boolean deplacerEntite(const t_moteur *moteur, t_entite *entite, const float vitesse);





#endif