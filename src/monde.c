/**
 * @file 
 *
 * @brief
 *
 * @author
 */



#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/monde.h"





unsigned int setGenerationSeed(unsigned int seed) {
    srand(seed);
    return seed;
}





t_vecteur2 getPointApparitionJoueur(t_map *map) {
    const int centre = (TAILLE_MAP * TAILLE_CHUNK) / 2;
    
    
    const float x = centre, y = centre;


    t_vecteur2 position = { x, y };
    return position;
}





char* afficherBlock(int block) {
    char* text = NULL;
  
    switch (block) {
        case VIDE: text = (" ! "); break;
        // case SOL_EAU_PROFONDE: text = ("\U0001F7EA"); break;
        // case SOL_EAU: text = ("\U0001F7E6"); break;
        // case SOL_SABLE: text = ("\U0001F7E8"); break;
        // case SOL_HERBE_1: text = ("\U0001F7E9"); break;
        // case SOL_HERBE_2: text = ("\U0001F7E2"); break;
        // case SOL_HERBE_3: text = ("\U0001F7E4"); break;
        // case SOL_MONTAGNE_1: text = ("\U0001F7EB"); break;
        // case SOL_MONTAGNE_2: text = ("\U00002B1B"); break;
        // case SOL_NEIGE: text = ("\U00002B1C"); break;
        case SOL_EAU_PROFONDE: text = ("P"); break;
        case SOL_EAU: text = ("E"); break;
        case SOL_SABLE: text = ("S"); break;
        case SOL_HERBE_1: text = ("n"); break;
        case SOL_HERBE_2: text = ("h"); break;
        case SOL_HERBE_3: text = ("H"); break;
        case SOL_MONTAGNE_1: text = ("m"); break;
        case SOL_MONTAGNE_2: text = ("M"); break;
        case SOL_NEIGE: text = ("⬜"); break;

        // // case HERBE: text = ("\U0001F331"); break;
        // // // case ROSE: text = ("\U0001F339"); break;
        // // // case TULIPE: text = ("\U0001F337"); break;
        // // case CHAINE: text = ("\U0001F333"); break;
        // // case PALMIER: text = ("\U0001F334"); break;
        // // case SAPIN: text = ("\U0001F332"); break;
        // case HERBE:
        // // case ROSE:
        // // case TULIPE:
        // case CHAINE:
        // case PALMIER:
        // case SAPIN:
        //     text = ("\U0001F7E5");
        //     break;

        default: 
            printf("?%i", block);
            return NULL;
    }

    printf("%s", text);
    return text;
}



void afficherChunk(t_chunk chunk) {
  
}



void afficherMonde(t_monde *monde) {
    // printf("Affichage Monde\n");
    t_map* map = monde->map;
    int maxLoop = (TAILLE_MAP * TAILLE_MAP) * (TAILLE_CHUNK * TAILLE_CHUNK);

    t_block *block = NULL;
    t_chunk *chunk = NULL, *vegetationChunk = NULL;
    int xChunk = 0, 
        yChunk = 0, 
        x = 0, 
        y = 0;
  

    printf("SEED : %i\n\n", monde->seed);
    if (map == NULL) 
        printf("MAP NULL");
    else 
        while (yChunk < TAILLE_MAP) {   
            chunk = getChunk(xChunk, yChunk, COUCHE_SOL, map);
            vegetationChunk = getChunk(xChunk, yChunk, COUCHE_OBJETS, map);
          
            if (chunk == NULL) {
                xChunk++;
                maxLoop -= TAILLE_CHUNK * TAILLE_CHUNK;
                continue;
            }

          
            maxLoop--;

            block = getBlockDansChunk(x, y, vegetationChunk); // chunk->blocks[x][y];
            if (block == NULL || block->tag == VIDE) block = getBlockDansChunk(x, y, chunk); // chunk->blocks[x][y];

            if (block == NULL) 
                printf("BLOCK NULL => x : %i / y : %i (in xChunk : %i / yChunk : %i)\n", x, y, xChunk, yChunk);
            else {
                // printf("%i ", block->tag);
                afficherBlock(block->tag);
            }
          
            x++;
          
            if (x >= TAILLE_CHUNK) {
                xChunk++;
                x = 0;
                // printf("|");
            }
                    
            if (xChunk >= TAILLE_MAP) {
                xChunk = 0;
                y++;
                printf("\n");
            }
  
            if (y >= TAILLE_CHUNK) {
                y = 0;
                yChunk++;
                // for (int i = 0; i < 2 * (TAILLE_MAP * TAILLE_CHUNK); i++) printf("-");
                // printf("\n");
            }

        }
}





t_monde* creerMonde(int seed) {
    t_monde *monde = malloc(sizeof(t_monde));

    if (monde == NULL) {
        printf("Erreur mémoire : Impossible d'allouer la place nécessaire pour le monde");
        free(monde);
        return NULL;
    }


    if (seed == -1) {
        seed = setGenerationSeed(time(NULL));
    }
    else {
        seed = setGenerationSeed(seed);
    }


    monde->seed = seed;
    monde->map = genererMap();


    // t_vecteur2 position = getPointApparitionJoueur(map);
    // t_joueur *joueur = creerJoueur(position.x, position.y);


    return monde;
}




void detruireMonde(t_monde **monde) {
    printf("Destruction Monde => ");
    if (monde != NULL && *monde != NULL) {
        t_map *map = (*monde)->map;
        detruireMap(&map);

    
        free(*monde);
        *monde = NULL;  
    }
    printf("Succes\n");
}