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





#define TAILLE_TILE 16





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
    SDL_Texture *null;
    SDL_Texture *sol;

    // Végétaux
    SDL_Texture *vegetaux;


    // Entités
    SDL_Texture *joueur;
    SDL_Texture *monstres;
    SDL_Texture *animaux;

    // Autres

} t_textures;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_textures* initTextures(SDL_Renderer *renderer);
void detruireTextures(t_textures **textures);

SDL_Texture* getTexture(const int tag, t_textures *textures);
void splitTexture(SDL_Rect *rectangle, const int x, const int y, const int tailleX, const int tailleY);





#endif