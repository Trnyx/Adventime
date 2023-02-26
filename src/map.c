/**
 * @file camera.c
 *
 * @brief
 *
 * @author Clément Hibon
 * @date 5 février
 * @version 1.1
 */



#include <stdlib.h>
#include <stdio.h>

#include "../include/moteur.h"
#include "../include/map.h"
#include "../include/vegetations.h"
#include "../include/camera.h"





/* -------------------------------------------------------------------------- */
/*                                     Get                                    */
/* -------------------------------------------------------------------------- */


/**
 * @brief Récupère un block se situant dans un chunk
 * 
 * @param x La cooronnée x (relative au chunk) du block
 * @param y La cooronnée y (relative au chunk) du block
 * @param chunk Un pointeur sur le chunk où sera récupérer le block
 * @return Un pointeur sur le block trouvé, NULL sinon
 * 
 * @version 1.3
 */
t_block* getBlockDansChunk(const int x, const int y, t_chunk *chunk) {
    if (!blockEstDansLeChunk(x, y)) return NULL;

    for (int i = 0; i < TAILLE_CHUNK * TAILLE_CHUNK; i++) {
        if (chunk->blocks[i].positionDansChunk.x == x && chunk->blocks[i].positionDansChunk.y == y) {
            return &chunk->blocks[i];
        }
    }

    return NULL;
}


/**
 * @brief Récupère un block se situant dans la map
 * 
 * @param x La cooronnée x (relative à la map) du block
 * @param y La cooronnée y (relative à la map) du block
 * @param z La couche où se situe du block
 * @param map Un pointeur sur la map où sera récupérer le block
 * @return Un pointeur sur le block trouvé, NULL sinon
 * 
 * @version 1.2
 */
t_block* getBlockDansMap(const int x, const int y, const int z, t_map *map) {
    if (!blockEstDansLaMap(x, y)) return NULL;

    t_chunk *chunk = getChunkGraceABlock(x, y, z, map);
    if (chunk == NULL) return NULL;

    return getBlockDansChunk(x % TAILLE_CHUNK, y % TAILLE_CHUNK, chunk);
}



/**
 * @brief Récupère un chunk se situant dans la map
 * 
 * @param x La coordonnée x du chunk
 * @param y La coordonnée y du chunk
 * @param couche La couche du chunk 
 * @param map Un pointeur sur la map où sera récupéré le chunk
 * @return Un pointeur sur le chunk trouvé, NULL sinon
 * 
 * @version 1.3
 */
t_chunk* getChunk(const int x, const int y, const int couche, t_map *map) {
    if (!chunkEstDansLaMap(x, y, couche)) return NULL;

    for (int i = 0; i < TAILLE_MAP * TAILLE_MAP * NB_COUCHE; i++) {
        if (map->chunks[i].position.x == x && map->chunks[i].position.y == y && map->chunks[i].position.z == couche) {
            return &map->chunks[i];
        }
    }

    return NULL;
}


/**
 * @brief Récupère un chunk se situant dans la map grâce au coordonnée d'un block
 * 
 * @param x La coordonnée x (relative à la map) d'un block
 * @param y La coordonnée y (relative à la map) d'un block
 * @param couche La couche du chunk 
 * @param map Un pointeur sur la map où sera récupéré le chunk
 * @return Un pointeur sur le chunk trouvé, NULL sinon
 * 
 * @version 1.1
 */
t_chunk* getChunkGraceABlock(const int x, const int y, const int couche, t_map *map) {
    const int xChunk = x / TAILLE_CHUNK;
    const int yChunk = y / TAILLE_CHUNK;
    return getChunk(xChunk, yChunk, couche, map);
}





/* -------------------------------------------------------------------------- */
/*                                    Rendu                                   */
/* -------------------------------------------------------------------------- */


/* ----------------------------------- Sol ---------------------------------- */


int dessinerBlockSol(t_moteur *moteur, const int tag, SDL_Rect *rendu) {
    SDL_Rect source;


    switch (tag) {
        case SOL_EAU_PROFONDE:
        case SOL_EAU:
        case SOL_SABLE:
        case SOL_HERBE_1:
        case SOL_HERBE_2:
        case SOL_HERBE_3:
        case SOL_MONTAGNE_1:
        case SOL_MONTAGNE_2:
            splitTexture(&source, (8 + 2 * TAILLE_TILE * tag),8, TAILLE_TILE,TAILLE_TILE);
            break;
        default:
            return SDL_RenderCopy(moteur->renderer, moteur->textures->null, NULL, rendu);
    }


    return SDL_RenderCopy(moteur->renderer, moteur->textures->sol, &source, rendu);
}



/**
 * @brief 
 * 
 * @param moteur 
 * @param origine 
 * @param offset 
 * @param rendu 
 */
void dessinerSol(t_moteur *moteur, t_map *map, SDL_Rect *rendu) {
    t_camera *camera = moteur->camera;

    for (float x = camera->origine.x - 1; x <= camera->position.x + TAILLE_CAMERA_DEMI_LARGEUR + 1; x++) {
        for (float y = camera->origine.y - 1; y <= camera->position.y + TAILLE_CAMERA_DEMI_HAUTEUR + 1; y++) {
            rendu->x = positionRelativeEnPositionSurEcran(x, camera->offset.x, camera->origine.x, rendu->w) + rendu->w;
            rendu->y = positionRelativeEnPositionSurEcran(y, camera->offset.y, camera->origine.y, rendu->h) + rendu->h;


            t_block *block = getBlockDansMap(x, y, COUCHE_SOL, map);
            if (block == NULL) {
                SDL_RenderCopy(moteur->renderer, moteur->textures->null, NULL, rendu);
                continue;
            }


            // SDL_Texture *texture = getTexture(block->tag, moteur->textures);
            // if (texture == NULL) continue;

            // SDL_Rect source = dessinerSol(moteur, block->tag, rendu);
            dessinerBlockSol(moteur, block->tag, rendu);


            // SDL_RenderCopy(moteur->renderer, moteur->textures->sol, &source, &rendu);
        }
    }
}





/* ------------------------------- Vegetations ------------------------------ */


int dessinerVegetal(t_moteur *moteur, const int tag, SDL_Rect *rendu) {
    SDL_Rect source;
    SDL_Rect renduVegetaux;


    switch (tag) {
        case HERBE:
            splitTexture(&source, 0,0, TAILLE_TILE,TAILLE_TILE);
            break;
        case CHAINE:
            splitTexture(&source, (2 * TAILLE_TILE * (tag % HERBE)),0, 3*TAILLE_TILE,2*TAILLE_TILE);
            break;


        default:
            break;
    }


    renduVegetaux.x = rendu->x - rendu->w;
    renduVegetaux.y = rendu->y - rendu->h;
    renduVegetaux.w = 3 * rendu->w;
    renduVegetaux.h = 2 * rendu->h;
    
    return SDL_RenderCopy(moteur->renderer, moteur->textures->vegetaux, &source, &renduVegetaux);
}



/**
 * @brief 
 * 
 * @param moteur 
 * @param origine 
 * @param offset 
 * @param rendu 
 */
void dessinerVegetation(t_moteur *moteur, t_map *map, SDL_Rect *rendu) {
    t_camera *camera = moteur->camera;

    for (float x = camera->origine.x - 1; x <= camera->position.x + TAILLE_CAMERA_DEMI_LARGEUR + 1; x++) {
        for (float y = camera->origine.y - 1; y <= camera->position.y + TAILLE_CAMERA_DEMI_HAUTEUR + 1; y++) {
            rendu->x = positionRelativeEnPositionSurEcran(x, camera->offset.x, camera->origine.x, rendu->w) + rendu->w;
            rendu->y = positionRelativeEnPositionSurEcran(y, camera->offset.y, camera->origine.y, rendu->h) + rendu->h;


            t_block *block = getBlockDansMap(x, y, COUCHE_OBJETS, map);
            if (block == NULL) continue;
            if (block->tag == VIDE) continue;


            dessinerVegetal(moteur, block->tag, rendu);
        }
    }
}
