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
    ENTITE_MONSTRE,
} e_entiteType;





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @struct t_entite
 * @brief Structure modélisant une entité
 */
typedef struct s_entite {
    int id;

    t_vecteur2 position;
    t_vecteur2 orientation;
    int vitesse;

    // e_entiteType type;

    SDL_Rect hitbox;
} t_entite;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_entite* creerEntite();
void detruireEntite(t_entite **entite);

int deplacerEntite(t_entite *entite);





#endif