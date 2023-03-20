/**
 * @file generation_structures.c
 * 
 * @brief 
 * 
 * @author Clément Hibon
 * @date 18 mars
 * @version 1.1
 */





#include <stdio.h>
#include <stdlib.h>

#include "../include/structures.h"
#include "../include/disc_sampling.h"





boolean biomeValidationPourVillage(t_chunk *chunk) {
    if (chunk->biome <= BIOME_LAC) return FAUX;
    else return chunk->biome == BIOME_PLAINE || chunk->biome == BIOME_FORET;
}






t_chunk* getChunkCentralBiome(const e_biome biome, t_map *map, boolean (*validation)(t_chunk*)) {
    t_chunk *chunkFinal = NULL;
    int max = 0;
    int compteur = 0;


    for (int x = 0; x < TAILLE_MAP; x++) {
        for (int y = 0; y < TAILLE_MAP; y++) {
            t_chunk *chunk = getChunk(x, y, COUCHE_SOL, map);


            if (chunk == NULL) continue;

            if (chunk->biome == biome) {
                for (int xChunk = chunk->position.x - 1; xChunk <= chunk->position.x + 1; xChunk++) {
                    for (int yChunk = chunk->position.y - 1; yChunk <= chunk->position.y + 1; yChunk++) {
                        t_chunk *chunkTempo = getChunk(xChunk, yChunk, COUCHE_SOL, map);

                        if (validation(chunkTempo))
                            ++compteur;
                    }
                }

                if (compteur >= max) {
                    max = compteur;
                    chunkFinal = chunk;
                }


                compteur = 0;
            }
        }
    }
    

    return chunkFinal;
}






/* -------------------------------------------------------------------------- */
/*                                  Villages                                  */
/* -------------------------------------------------------------------------- */



t_structure structuresPresets[] = {
    {
        STRUCTURE_PUIT,
        3, 3,
        {
            { BLOCK_PUIT_HAUT_GAUCHE, BLOCK_PUIT_HAUT_CENTRE, BLOCK_PUIT_HAUT_DROIT },
            { BLOCK_PUIT_MILIEU_GAUCHE, BLOCK_PUIT_MILIEU_CENTRE, BLOCK_PUIT_MILIEU_DROIT },
            { BLOCK_PUIT_BAS_GAUCHE, BLOCK_PUIT_BAS_CENTRE, BLOCK_PUIT_BAS_DROIT },
        }
    },
    {
        STRUCTURE_MAISON_1,
        7, 6,
        {
            { VIDE, BLOCK_TOIT_PETIT_LAYER_1_2, BLOCK_TOIT_PETIT_LAYER_1_3, BLOCK_TOIT_PETIT_LAYER_1_4, BLOCK_TOIT_PETIT_LAYER_1_5, VIDE },
            { BLOCK_TOIT_PETIT_LAYER_2_1, BLOCK_TOIT_PETIT_LAYER_2_2, BLOCK_TOIT_PETIT_LAYER_2_3, BLOCK_TOIT_PETIT_LAYER_2_4, BLOCK_TOIT_PETIT_LAYER_2_5, BLOCK_TOIT_PETIT_LAYER_2_6 },
            { BLOCK_TOIT_PETIT_LAYER_3_1, BLOCK_TOIT_PETIT_LAYER_3_2, BLOCK_TOIT_PETIT_LAYER_3_3, BLOCK_TOIT_PETIT_LAYER_3_4, BLOCK_TOIT_PETIT_LAYER_3_5, BLOCK_TOIT_PETIT_LAYER_3_6 },
            { BLOCK_TOIT_PETIT_LAYER_4_1, BLOCK_TOIT_PETIT_LAYER_4_2, BLOCK_TOIT_PETIT_LAYER_4_3, BLOCK_TOIT_PETIT_LAYER_4_4, BLOCK_TOIT_PETIT_LAYER_4_5, BLOCK_TOIT_PETIT_LAYER_4_6 },
            { BLOCK_TOIT_PETIT_LAYER_5_1, BLOCK_TOIT_PETIT_LAYER_5_2, BLOCK_TOIT_PETIT_LAYER_5_3, BLOCK_TOIT_PETIT_LAYER_5_4, BLOCK_TOIT_PETIT_LAYER_5_5, BLOCK_TOIT_PETIT_LAYER_5_6 },
            { BLOCK_MUR_HAUT_GAUCHE, BLOCK_MUR_HAUT_CENTRE, BLOCK_MUR_HAUT_CENTRE, BLOCK_MUR_HAUT_CENTRE, BLOCK_MUR_HAUT_CENTRE, BLOCK_MUR_HAUT_DROIT },
            { BLOCK_MUR_GAUCHE, BLOCK_MUR_CENTRE, BLOCK_MUR_CENTRE, BLOCK_MUR_CENTRE, BLOCK_MUR_CENTRE, BLOCK_MUR_DROIT },
        },
    },
    {
        STRUCTURE_MAISON_2,
        7, 6,
        {
            { VIDE, BLOCK_TOIT_PETIT_LAYER_1_2, BLOCK_TOIT_PETIT_LAYER_1_3, BLOCK_TOIT_PETIT_LAYER_1_4, BLOCK_TOIT_PETIT_LAYER_1_5, VIDE },
            { BLOCK_TOIT_PETIT_LAYER_2_1, BLOCK_TOIT_PETIT_LAYER_2_2, BLOCK_TOIT_PETIT_LAYER_2_3, BLOCK_TOIT_PETIT_LAYER_2_4, BLOCK_TOIT_PETIT_LAYER_2_5, BLOCK_TOIT_PETIT_LAYER_2_6 },
            { BLOCK_TOIT_PETIT_LAYER_3_1, BLOCK_TOIT_PETIT_LAYER_3_2, BLOCK_TOIT_PETIT_LAYER_3_3, BLOCK_TOIT_PETIT_LAYER_3_4, BLOCK_TOIT_PETIT_LAYER_3_5, BLOCK_TOIT_PETIT_LAYER_3_6 },
            { BLOCK_TOIT_PETIT_LAYER_4_1, BLOCK_TOIT_PETIT_LAYER_4_2, BLOCK_TOIT_PETIT_LAYER_4_3, BLOCK_TOIT_PETIT_LAYER_4_4, BLOCK_TOIT_PETIT_LAYER_4_5, BLOCK_TOIT_PETIT_LAYER_4_6 },
            { BLOCK_TOIT_PETIT_LAYER_5_1, BLOCK_TOIT_PETIT_LAYER_5_2, BLOCK_TOIT_PETIT_LAYER_5_3, BLOCK_TOIT_PETIT_LAYER_5_4, BLOCK_TOIT_PETIT_LAYER_5_5, BLOCK_TOIT_PETIT_LAYER_5_6 },
            { BLOCK_MUR_HAUT_GAUCHE, BLOCK_MUR_HAUT_CENTRE, BLOCK_MUR_HAUT_CENTRE, BLOCK_MUR_HAUT_CENTRE, BLOCK_MUR_HAUT_CENTRE, BLOCK_MUR_HAUT_DROIT },
            { BLOCK_MUR_GAUCHE, BLOCK_MUR_CENTRE, BLOCK_MUR_CENTRE, BLOCK_MUR_CENTRE, BLOCK_MUR_CENTRE, BLOCK_MUR_DROIT },
        },
    },
    {
        STRUCTURE_MAISON_3,
        7, 6,
        {
            { VIDE, BLOCK_TOIT_PETIT_LAYER_1_2, BLOCK_TOIT_PETIT_LAYER_1_3, BLOCK_TOIT_PETIT_LAYER_1_4, BLOCK_TOIT_PETIT_LAYER_1_5, VIDE },
            { BLOCK_TOIT_PETIT_LAYER_2_1, BLOCK_TOIT_PETIT_LAYER_2_2, BLOCK_TOIT_PETIT_LAYER_2_3, BLOCK_TOIT_PETIT_LAYER_2_4, BLOCK_TOIT_PETIT_LAYER_2_5, BLOCK_TOIT_PETIT_LAYER_2_6 },
            { BLOCK_TOIT_PETIT_LAYER_3_1, BLOCK_TOIT_PETIT_LAYER_3_2, BLOCK_TOIT_PETIT_LAYER_3_3, BLOCK_TOIT_PETIT_LAYER_3_4, BLOCK_TOIT_PETIT_LAYER_3_5, BLOCK_TOIT_PETIT_LAYER_3_6 },
            { BLOCK_TOIT_PETIT_LAYER_4_1, BLOCK_TOIT_PETIT_LAYER_4_2, BLOCK_TOIT_PETIT_LAYER_4_3, BLOCK_TOIT_PETIT_LAYER_4_4, BLOCK_TOIT_PETIT_LAYER_4_5, BLOCK_TOIT_PETIT_LAYER_4_6 },
            { BLOCK_TOIT_PETIT_LAYER_5_1, BLOCK_TOIT_PETIT_LAYER_5_2, BLOCK_TOIT_PETIT_LAYER_5_3, BLOCK_TOIT_PETIT_LAYER_5_4, BLOCK_TOIT_PETIT_LAYER_5_5, BLOCK_TOIT_PETIT_LAYER_5_6 },
            { BLOCK_MUR_HAUT_GAUCHE, BLOCK_MUR_HAUT_CENTRE, BLOCK_MUR_HAUT_CENTRE, BLOCK_MUR_HAUT_CENTRE, BLOCK_MUR_HAUT_CENTRE, BLOCK_MUR_HAUT_DROIT },
            { BLOCK_MUR_GAUCHE, BLOCK_MUR_CENTRE, BLOCK_MUR_CENTRE, BLOCK_MUR_CENTRE, BLOCK_MUR_CENTRE, BLOCK_MUR_DROIT },
        },
    },
};



// void getStructurePreset(const e_structureTag tag, t_structure *structure) {
//     structure->tag = tag;
    
//     switch (tag) {
//         case STRUCTURE_PUIT:
//             structure->hauteur = 3;        
//             structure->largeur = 3;

//             structure->collisionBox.x = 0;
//             structure->collisionBox.y = 0;
//             structure->collisionBox.w = 3;
//             structure->collisionBox.h = 3;

//             // structure->blocks[0] = { BLOCK_PUIT_HAUT_GAUCHE, BLOCK_PUIT_HAUT_CENTRE, BLOCK_PUIT_HAUT_DROIT };
//             // structure->blocks[1] = { BLOCK_PUIT_MILIEU_GAUCHE, BLOCK_PUIT_MILIEU_CENTRE, BLOCK_PUIT_MILIEU_DROIT };
//             // structure->blocks[2] = { BLOCK_PUIT_BAS_GAUCHE, BLOCK_PUIT_BAS_CENTRE, BLOCK_PUIT_BAS_DROIT };
//             break;


//         case STRUCTURE_MAISON_1:
//             // {
//             //     STRUCTURE_MAISON_1,
//             //     {
//             //         { BLOCK_TOIT, BLOCK_TOIT, BLOCK_TOIT, BLOCK_TOIT, BLOCK_TOIT, BLOCK_TOIT },
//             //         { BLOCK_TOIT, BLOCK_TOIT, BLOCK_TOIT, BLOCK_TOIT, BLOCK_TOIT, BLOCK_TOIT },
//             //         { BLOCK_MUR_GAUCHE, BLOCK_MUR_CENTRE, BLOCK_MUR_CENTRE, BLOCK_MUR_CENTRE, BLOCK_MUR_CENTRE, BLOCK_MUR_DROIT },
//             //         { BLOCK_MUR_BAS_GAUCHE, BLOCK_MUR_BAS_CENTRE, BLOCK_MUR_BAS_CENTRE, BLOCK_MUR_BAS_CENTRE, BLOCK_MUR_BAS_DROIT },
//             //     },
//             //     4, 6,
//             //     { 0, 0, 6, 1 },
//             // }
//             break;
//     }
// }





e_structureTag selectionMaisonTag() {
    return getNombreAleatoire(STRUCTURE_MAISON_1, STRUCTURE_MAISON_3);
}





void genererStructure(const t_vecteur2 position, const e_structureTag tag, t_map *map) {
    t_chunk *chunk = NULL;
    t_block *block = NULL;

    t_structure structure = structuresPresets[tag];
    
    
    for (int y = position.y, h = 0; y < position.y + structure.hauteur; y++, h++) {
        for (int x = position.x, L = 0; x < position.x + structure.largeur; x++, L++) {
            e_blockTag blockStructure = structure.blocks[h][L];
            printf("BLOCK STRUCTURE : %i (%i:%i)\n", blockStructure, x, y);

            block = getBlockDansMap(x, y, COUCHE_OBJETS, map);
            block->tag = blockStructure;
        }
    }
}





void genererVillage(t_map *map) {
    printf("GENERATION VILLAGE => ");
    printf("GET PLAINE => ");
    t_chunk *plusGrandePlaine = getChunkCentralBiome(BIOME_PLAINE, map, biomeValidationPourVillage);


    if (plusGrandePlaine != NULL) {
        const t_vecteur2 centre = {
            (plusGrandePlaine->position.x * TAILLE_CHUNK) / 2,
            (plusGrandePlaine->position.y * TAILLE_CHUNK) / 2,
        };


        printf("GENERATION PUIT %1.2f:%1.2f => ", centre.x, centre.y);
        genererStructure(centre, STRUCTURE_PUIT, map);

        
        const t_vecteur2 min = { centre.x - (TAILLE_CHUNK), centre.y - (TAILLE_CHUNK) };
        const t_vecteur2 max = { centre.x + (TAILLE_CHUNK), centre.y + (TAILLE_CHUNK) };
        

        printf("GENERATION GRILLE => ");
        const t_discSampling grille = genererGrilleDiscSampling(min, max, 8, 14);


        printf("%i => ", grille.nbElements);
        for (int i = 0; i < grille.nbElements; i++) {
            t_vecteur2 position = grille.elementPositions[i];
            const e_structureTag tag = selectionMaisonTag();

            printf("GENERATION BATIMENT %i => ", i);
            genererStructure(position, tag, map);
        }

    }

    printf("\n");
}







