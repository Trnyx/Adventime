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
#include "../include/structures.h"
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
 * 
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
 * 
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
 * 
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
 * 
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


/**
 * @brief Dessine un block au sol
 * 
 * @param tag Le tag du block qui doit être dessiné
 * @param rendu Les informations sur le rendu 
 * 
 * @return 0 si tout s'est bien passé, un nombre négatif sinon
 */
int dessinerBlockSol(const int tag, SDL_Rect *rendu) {
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
 * @brief Affiche le sol de la map en fonction de la taille de la caméra
 * 
 * @param map Un pointeur sur la map qui doit être affiché
 */
void dessinerSol(t_map *map) {
    t_camera *camera = moteur->camera;
    SDL_Rect rendu;
    rendu.w = camera->tailleRendu.x;
    rendu.h = camera->tailleRendu.y;

    for (float x = camera->origine.x - 1; x <= camera->position.x + TAILLE_CAMERA_DEMI_LARGEUR + 2; x++) {
        for (float y = camera->origine.y - 1; y <= camera->position.y + TAILLE_CAMERA_DEMI_HAUTEUR + 2; y++) {
            rendu.x = positionRelativeEnPositionSurEcran(x, camera->offset.x, camera->origine.x, rendu.w);
            rendu.y = positionRelativeEnPositionSurEcran(y, camera->offset.y, camera->origine.y, rendu.h);


            t_block *block = getBlockDansMap(x, y, COUCHE_SOL, map);
            if (block == NULL) {
                SDL_RenderCopy(moteur->renderer, moteur->textures->null, NULL, &rendu);
                continue;
            }


            // SDL_Texture *texture = getTexture(block->tag, moteur->textures);
            // if (texture == NULL) continue;

            // SDL_Rect source = dessinerSol(moteur, block->tag, rendu);
            dessinerBlockSol(block->tag, &rendu);


            // SDL_RenderCopy(moteur->renderer, moteur->textures->sol, &source, &rendu);
        }
    }
}





/* ------------------------------- Vegetations ------------------------------ */


#define LARGEUR_ARBRE (3 * TAILLE_TILE)
#define HAUTEUR_ARBRE (2 * TAILLE_TILE)

/**
 * @brief Affiche un Objet complet
 * 
 * @param tag Le tag de l'objet à afficher
 * @param rendu Les informations sur le rendu 
 * 
 * @return 0 si tout s'est bien passé, un nombre négatif sinon
 */
int dessinerObjet(int tag, SDL_Rect *rendu) {
    SDL_Texture *texture = NULL;
    SDL_Rect source;
    SDL_Rect renduObjet;


    if (tag > DEBUT_VEGETAL && tag < FIN_VEGETAL) {
        texture = moteur->textures->vegetaux;

        switch (tag) {
            case HERBE:
                splitTexture(&source, 0,0, TAILLE_TILE,TAILLE_TILE);
                renduObjet.x = rendu->x;
                renduObjet.y = rendu->y;
                renduObjet.w = rendu->w;
                renduObjet.h = rendu->h;
                break;
                
            case CHAINE:
            case PALMIER:
            case SAPIN:
                splitTexture(&source, (LARGEUR_ARBRE * (tag % HERBE)),0, LARGEUR_ARBRE,HAUTEUR_ARBRE);
                renduObjet.x = rendu->x - rendu->w;
                renduObjet.y = rendu->y - rendu->h;
                renduObjet.w = 3 * rendu->w;
                renduObjet.h = 2 * rendu->h;
                
                break;
        }
    }
    else if (tag > DEBUT_BLOCK_STRUCTURE && tag < FIN_BLOCK_STRUCTURE) {
        texture = moteur->textures->structures;
        t_vecteur2 decalage = { 0, 0 };


        // printf("AFFICHE STRUCTURE %i ", tag);

        /* ---------------------------------- PUIT ---------------------------------- */

        if (tag >= BLOCK_PUIT_HAUT_GAUCHE && tag <= BLOCK_PUIT_BAS_DROIT) {
            tag = (tag % BLOCK_PUIT_HAUT_GAUCHE);
            
            decalage.x = (tag % 3);
            decalage.y = (tag / 3);
        } 
        


        /* --------------------------------- MAISONS -------------------------------- */

        else if (tag >= BLOCK_MUR_HAUT_GAUCHE_STANDARD && tag <= BLOCK_MUR_DROIT_BLEU) {
            tag = (tag % BLOCK_MUR_HAUT_GAUCHE_STANDARD);

            // Le décalage se fait en fonction du nombre de bloc possible composant un mur
            // ainsi que le nombre de variants de mur possible
            decalage.x = (tag % (3 * 3));
            decalage.y = ((tag / (3 * 3)) + 14);
        } 
        

        else if (tag >= BLOCK_TOIT_PETIT_LAYER_1_1_STANDARD && tag <= BLOCK_TOIT_PETIT_LAYER_5_6_BLEU) {
            tag = (tag % BLOCK_TOIT_PETIT_LAYER_1_1_STANDARD);

            // Le décalage se fait en fonction du nombre de bloc possible composant un toit
            // ainsi que le nombre de variants de toit possible
            decalage.x = (tag % (6 * 3));
            decalage.y = ((tag / (6 * 3)) + 3);
        } 
        

        else if (tag == BLOCK_PORTE) {
            decalage.x = 0;
            decalage.y = (16);
        }


        /* --------------------------------- TEMPLE --------------------------------- */

        else if (tag >= BLOCK_TEMPLE_ENTREE_HAUT_GAUCHE && tag <= BLOCK_TEMPLE_ENTREE_BAS_DROIT) {
            tag = tag % BLOCK_TEMPLE_ENTREE_HAUT_GAUCHE;

            decalage.x = (tag % 3) + 3;
            decalage.y = tag / 3;
        }


        splitTexture(&source, decalage.x*TAILLE_TILE,decalage.y*TAILLE_TILE, TAILLE_TILE,TAILLE_TILE);
        // splitTexture(&source, 0,0, TAILLE_TILE,TAILLE_TILE);

        renduObjet.x = rendu->x;
        renduObjet.y = rendu->y;
        renduObjet.w = rendu->w;
        renduObjet.h = rendu->h;
    }


    
    return SDL_RenderCopy(moteur->renderer, texture, &source, &renduObjet);
}



/**
 * @brief Affiche les objets d'une map
 * 
 * @param map Un pointeur sur la map dans laquelle se trouve les objets
 */
void dessinerObjets(t_map *map) {
    t_camera *camera = moteur->camera;
    SDL_Rect rendu;
    rendu.w = camera->tailleRendu.x;
    rendu.h = camera->tailleRendu.y;

    for (float x = camera->origine.x - 1; x <= camera->position.x + TAILLE_CAMERA_DEMI_LARGEUR + 2; x++) {
        for (float y = camera->origine.y - 1; y <= camera->position.y + TAILLE_CAMERA_DEMI_HAUTEUR + 2; y++) {
            rendu.x = positionRelativeEnPositionSurEcran(x, camera->offset.x, camera->origine.x, rendu.w);
            rendu.y = positionRelativeEnPositionSurEcran(y, camera->offset.y, camera->origine.y, rendu.h);


            t_block *block = getBlockDansMap(x, y, COUCHE_OBJETS, map);
            if (block == NULL) continue;
            if (block->tag == VIDE) continue;


            dessinerObjet(block->tag, &rendu);
        }
    }
}
