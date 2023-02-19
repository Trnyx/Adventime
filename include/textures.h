/**
 * @file textures.h
 *
 * @brief
 *
 * @author Clément Hibon
 * @date 3 février
 * @version 1.0
 */



#ifndef _JEU_TEXTURES_
#define _JEU_TEXTURES_



#include <SDL2/SDL.h>





/* -------------------------------------------------------------------------- */
/*                                 Enumeration                                */
/* -------------------------------------------------------------------------- */





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief Structures contenant toutes les textures du jeu
 * 
 */
typedef struct s_textures {

    // Map
    SDL_Texture *sol;
    SDL_Texture *sol_profondeur;
    SDL_Texture *sol_eau;
    SDL_Texture *sol_sable;
    SDL_Texture *sol_herbe_1;
    SDL_Texture *sol_herbe_2;
    SDL_Texture *sol_herbe_3;
    SDL_Texture *sol_montagne_1;
    SDL_Texture *sol_montagne_2;
    SDL_Texture *sol_neige;

    // Végétaux
    SDL_Texture *vegetaux_herbe;
    SDL_Texture *vegetaux_chene;


    // Joueur
    SDL_Texture *joueur;

    // Monstres
    SDL_Texture *monstres;

    // Animaux

    // Autres

} t_textures;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_textures* initTextures(SDL_Renderer *renderer);
void detruireTextures(t_textures **textures);

SDL_Texture* getTexture(const int tag, t_textures *textures);
void splitTexture(SDL_Rect *rectangle, const int x, const int y, const int tailleX, const int tailleY, const int decalageX, const int decalageY);





#endif