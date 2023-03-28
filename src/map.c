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
/*                               Test Existence                               */
/* -------------------------------------------------------------------------- */


/**
 * @brief Vérifie si un block se situe bien à l'intérieur d'un chunk
 * 
 * @param x La coordonnée x du block (coordonnée relative au chunk)
 * @param y La coordonnée y du block (coordonnée relative au chunk)
 * 
 * @return Vrai si le block se situe bien dans un chunk, faux sinon
 * 
 * @version 1.1
 */
int blockEstDansLeChunk(const int x, const int y) {
    return x >= 0 && y >= 0 && x < TAILLE_CHUNK && y < TAILLE_CHUNK;
}


/**
 * @brief Vérifie si un block se situe bien à l'intérieur de la map
 * 
 * @param x La coordonnée x du block (cordonnée relative à la map)
 * @param y La coordonnée y du block (cordonnée relative à la map)
 * 
 * @return Vrai si le block se situe bien dans la map, faux sinon
 * 
 * @version 1.1
 */
int blockEstDansLaMap(const int x, const int y) {
    return x >= 0 && y >= 0 && x < (TAILLE_MAP * TAILLE_CHUNK) && y < (TAILLE_MAP * TAILLE_CHUNK);
}


/**
 * @brief Vérifie que un chunk est bien à l'intérieur de la map
 * 
 * @param x La coordonnée x du chunk
 * @param y La coordonnée y du chunk
 * @param z La coordonnée z du chunk (correspond à la couche du chunk)
 * 
 * @return Vrai si le chunk se situe bien dans la map, faux sinon
 * 
 * @version 1.1
 */ 
int chunkEstDansLaMap(const int x, const int y, const int z) {
    return x >= 0 && y >= 0 && z >= 0 && x < TAILLE_MAP && y < TAILLE_MAP && z < NB_COUCHE;
}






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
int dessinerBlockSol(int tag, SDL_Rect *rendu) {
    SDL_Rect source;


    if (tag >= SOL_EAU_PROFONDE && tag <= SOL_MONTAGNE_2) {
        splitTexture(&source, (8 + 2 * TAILLE_TILE * tag),8, TAILLE_TILE,TAILLE_TILE);
    }

    else if (tag >= SOL_CHEMIN && tag < DEBUT_BLOCK_STRUCTURE) {
        tag = tag % SOL_CHEMIN;

        splitTexture(&source, tag*TAILLE_TILE,2*TAILLE_TILE, TAILLE_TILE,TAILLE_TILE);
    }

    else {
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

    t_vecteur2 decalage = { 0, 0 };


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



    else if (tag > DEBUT_BLOCK_SANS_COLLISION && tag < DEBUT_BLOCK_STRUCTURE) {
        texture = moteur->textures->sol;

        tag = tag % (DEBUT_BLOCK_SANS_COLLISION + 1);

        decalage.x = tag;
        decalage.y = 2;


        splitTexture(&source, decalage.x*TAILLE_TILE,decalage.y*TAILLE_TILE, TAILLE_TILE,TAILLE_TILE);

        renduObjet.x = rendu->x;
        renduObjet.y = rendu->y;
        renduObjet.w = rendu->w;
        renduObjet.h = rendu->h;
    }



    else if (tag > DEBUT_BLOCK_STRUCTURE && tag < FIN_BLOCK_STRUCTURE) {
        texture = moteur->textures->structures;


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


        /* ------------------------------- DECORATIONS ------------------------------ */

        else if (tag >= BLOCK_PANNEAU_AFFICHAGE_HAUT_GAUCHE && tag < FIN_BLOCK_STRUCTURE) {
            // Allume les lampadaire pendant la nuit
            switch (tag) {
                case BLOCK_LAMPADAIRE_GAUCHE_HAUT:
                case BLOCK_LAMPADAIRE_DROIT_HAUT:
                    if (moteur->temps->cycleJeu == CYCLE_NUIT)
                        decalage.y += 1;
                    break;
                
                default:
                    break;
            }

            tag = tag % BLOCK_PANNEAU_AFFICHAGE_HAUT_GAUCHE;

            decalage.x = tag;
            decalage.y += (17);
        }




        /* ---------------------------------- RENDU --------------------------------- */

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





/* -------------------------------------------------------------------------- */
/*                                 Destruction                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param block 
 *  
 * @version 1.1
 */
int detruireBlock(t_block **block) {
    if (block == NULL || *block == NULL) return 0;

    free(*block);
    *block = NULL;

    return 0;
}


/**
 * @brief 
 * 
 * @param chunk 
 * 
 * @version 1.2
 */
int detruireChunk(t_chunk **chunk) {
    if (chunk == NULL || *chunk == NULL) return 0;


    free((*chunk)->blocks);
    (*chunk)->blocks = NULL;

  
    return 0;
}


/**
 * @brief 
 * 
 * @param map 
 * 
 * @version 1.2
 */
int detruireMap(t_map **map) {
    printf("Destruction Map => ");
    if (map == NULL || *map == NULL) return 0;
    t_chunk *chunk = NULL;
  

    for (int x = 0; x < TAILLE_MAP; x++) {
        for (int y = 0; y < TAILLE_MAP; y++) {
            for (int z = 0; z < NB_COUCHE; z++) {
                chunk = getChunk(x, y, z, *map);
                detruireChunk(&chunk);
            }
        }
    }


    free((*map)->chunks);
    (*map)->chunks = NULL;
  
    free(*map);
    *map = NULL;

  
    return 0;
}
