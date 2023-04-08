/**
 * @file textures.h
 *
 * @brief Module de manipulation des textures
 *
 * @author Clément Hibon
 * @date 3 février
 * @version 1.0
 */



#ifndef _JEU_TEXTURES_
#define _JEU_TEXTURES_



#include <SDL2/SDL.h>





// La taille d'une tile (d'une case) [en pixel]
#define TAILLE_TILE 16





/* -------------------------------------------------------------------------- */
/*                                 Enumeration                                */
/* -------------------------------------------------------------------------- */





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @struct t_textures
 * @brief Structures contenant toutes les textures du jeu
 * 
 */
typedef struct s_textures {

    // Map
    SDL_Texture *null;              /**< La texture lorsque un objet est NULL */
    SDL_Texture *sol;               /**< Le tileset contenant les textures du sol */

    // Végétaux
    SDL_Texture *vegetaux;          /**< Le tileset contenant les textures des végétaux */
    SDL_Texture *structures;        /**< Le tileset contenant les textures des structures et décorations */


    // Entités
    SDL_Texture *joueur;            /**< Le tileset contenant les textures du joueur */
    SDL_Texture *monstres;          /**< Le tileset contenant les textures des monstres */
    SDL_Texture *animaux;           /**< Le tileset contenant les textures des animaux */

    // Autres
    SDL_Texture *items;             /**< Le tileset contenant les textures des items */

} t_textures;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_textures* initTextures(SDL_Renderer *renderer);
void detruireTextures(t_textures **textures);

void splitTexture(SDL_Rect *rectangle, const int x, const int y, const int tailleX, const int tailleY);





#endif