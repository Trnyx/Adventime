/**
 * @file structures.c
 *
 * @brief 
 *
 * @author Clément Hibon
 * @date 10 mars
 * @version 1.1
 */





#include <stdlib.h>
#include <stdio.h>

#include "../include/structures.h"
#include "../include/disc_sampling.h"





/* -------------------------------------------------------------------------- */
/*                                 Validation                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief Vérifie que le chunk donné est conforme pour la génération d'un village
 * 
 * @param chunk Le chunk qui doit être vérifié
 * @return 1 si valide, 0 sinon / Cas particulier : -1 => cas bannis
 */
int biomeValidationPourVillage(t_chunk *chunk) {
    if (chunk->biome <= BIOME_LAC) return -1;
    else return chunk->biome == BIOME_PLAINE || chunk->biome == BIOME_FORET;
}



/**
 * @brief Vérifie que le chunk donné est conforme pour la génération de l'entré du temple
 * 
 * @param chunk Le chunk qui doit être vérifié
 * @return 1 si valide, 0 sinon
 */
int biomeValidationPourEntreeTemple(t_chunk *chunk) {
    return chunk->biome == BIOME_MONTAGNE;
}





/* -------------------------------------------------------------------------- */
/*                                     Get                                    */
/* -------------------------------------------------------------------------- */


/**
 * @brief Get the Chunk Central Biome object
 * 
 * @param biome 
 * @param map 
 * @param validation 
 * @return t_chunk* 
 */
t_chunk* getChunkCentralBiome(const e_biome biome, t_map *map, int (*validation)(t_chunk*)) {
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
                        if (xChunk == chunk->position.x && yChunk == chunk->position.y) continue;
                        t_chunk *chunkTempo = getChunk(xChunk, yChunk, COUCHE_SOL, map);

                        int valide = validation(chunkTempo);

                        // Si le biome trouvé est un biome interdisant l'apparition
                        // on met le compteur avec un nombre négatif pour être sûr
                        // que le chunk ne soit pas sélectionné
                        if (valide == -1)
                            compteur = -8;
                        else if (valide)
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
    

    printf("CHUNK FINAL : %.2f:%.2f (%i)\n", chunkFinal->position.x, chunkFinal->position.y, chunkFinal->biome);
    return chunkFinal;
}





/* -------------------------------------------------------------------------- */
/*                                   Village                                  */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @return e_structureTag 
 */
e_structureTag selectionMaisonTag() {
    return getNombreAleatoire(STRUCTURE_PETITE_MAISON_1, STRUCTURE_PETITE_MAISON_3);
}



/* --------------------------------- Chemins -------------------------------- */

/**
 * @brief 
 * 
 * @param map 
 * @param x 
 * @param y 
 */
void changerBlockEnChemin(t_map *map, const float x, const float y) {
    t_block *block = getBlockDansMap(x, y, COUCHE_SOL, map);
    block->tag = SOL_CHEMIN;
}



/**
 * @brief 
 * 
 * @param map 
 * @param depart 
 * @param arrive 
 * @param x 
 * @param y 
 */
void tracerCheminVertical(t_map *map, t_vecteur2 depart, t_vecteur2 arrive, int *x, int *y) {
    // Maison en haut
    if (depart.y > arrive.y) {
        for (; *y < depart.y; (*y)++)
            changerBlockEnChemin(map, *x, *y);
    }

    // Maison en bas
    else {
        for (; *y > depart.y + 2; (*y)--)
            changerBlockEnChemin(map, *x, *y);
    }
}



/**
 * @brief 
 * 
 * @param map 
 * @param depart Le point de départ pour la création du chemin (Le puit)
 * @param arrive Le point d'arrive de la création du chemin (La maison)
 */
void tracerChemin(t_map *map, t_vecteur2 depart, t_vecteur2 arrive) {
    t_vecteur2 separation = {
        depart.x - arrive.x,
        depart.y - arrive.y,
    };
    

    int x = arrive.x;
    int y = arrive.y + 7;
    

    // Maison à gauche
    if (separation.x > 0) { 
        x += 2;

        // On trace la moitié du chemin horizontal
        for (; x < arrive.x + (separation.x / 2); x++)
            changerBlockEnChemin(map, x, y);
        
        // On trace la totalité du chemin vertical
        tracerCheminVertical(map, depart, arrive, &x, &y);
        
        // On finit de tracer le chemin vertical
        for (; x < depart.x; x++)
            changerBlockEnChemin(map, x, y);
    } 


    // Maison à droite ou alignée horizontalement
    else { 
        x += 4;

        // On trace la moitié du chemin horizontal
        for (; x > arrive.x + (separation.x / 2); x--)
            changerBlockEnChemin(map, x, y);
        
        // On trace la totalité du chemin vertical
        tracerCheminVertical(map, depart, arrive, &x, &y);
        
        // On finit de tracer le chemin vertical
        for (; x > depart.x + 2; x--)
            changerBlockEnChemin(map, x, y);
    }
    
}



/**
 * @brief 
 * 
 * @param map 
 * @param grille 
 */
void genererChemins(t_map *map, t_discSampling grille) {
    t_vecteur2 positionPuit = grille.elementPositions[0];


    // Entour le puit de dalle
    for (int x = positionPuit.x - 1; x <= positionPuit.x + 3; x++) {
        for (int y = positionPuit.y - 1; y <= positionPuit.y + 3; y++) {
            changerBlockEnChemin(map, x, y);
        }
    }


    // Relie les maisons au puit
    for (int i = 1; i < grille.nbElements; i++) {
        t_vecteur2 point = grille.elementPositions[i];

        tracerChemin(map, positionPuit, point);
    }

}





/* ------------------------------- Decorations ------------------------------ */

boolean peutEtrePlacer(t_map* map, const t_vecteur2 position, const int tailleX, const int tailleY) {
    t_block *block = NULL;

    for (int x = position.x; x < position.x + tailleX; x++) {
        for (int y = position.y; y < position.y + tailleY; y++) {
            block = getBlockDansMap(x, y, COUCHE_OBJETS, map);
            if (block->tag != VIDE)
                return FAUX;
        }
    }

    return VRAI;
}





t_vecteur2 choisirPositionDecorationAutourDePoint(t_map *map, const t_vecteur2 centre, const int tailleX, const int tailleY, const int rayon) {
    t_vecteur2 position = choisirPointDansRayon(rayon);
    position.x += centre.x;
    position.y += centre.y;


    if (peutEtrePlacer(map, position, tailleX, tailleY))
        return position;
    else
        return choisirPositionDecorationAutourDePoint(map, centre, tailleX, tailleY, rayon);
}



t_vecteur2 decorationAutourDePoint(t_map *map, const e_blockTag structure, const t_vecteur2 centre, const int tailleX, const int tailleY, const int rayon) {
    t_vecteur2 positionObjet = choisirPositionDecorationAutourDePoint(map, centre, tailleX, tailleX, rayon);
    
    
    for (int i = 0, y = positionObjet.y; y < positionObjet.y + tailleX; y++) {
        for (int x = positionObjet.x; x < positionObjet.x + tailleY; x++) {
            t_block *block = getBlockDansMap(x, y, COUCHE_OBJETS, map);
            block->tag = structure + i++;
        }
    }


    return positionObjet;
}





void genererDecorations(t_map *map, t_discSampling grille) {
    printf("DECORATINONS => ");
    const t_vecteur2 positionPuit = grille.elementPositions[0];
    
    // Panneau d'affichage
    decorationAutourDePoint(map, BLOCK_PANNEAU_AFFICHAGE_HAUT_GAUCHE, positionPuit, 2, 2, 5);

    // Brouette
    decorationAutourDePoint(map, BLOCK_BROUETTE_HAUT_GAUCHE, positionPuit, 2, 2, 6);
    
    // Decoration autour du chemin
    


    printf("\n");
}





/**
 * @brief 
 * 
 * @param map 
 */
void genererVillage(t_map *map) {
    printf("GENERATION VILLAGE => ");
    t_chunk *plusGrandePlaine = getChunkCentralBiome(BIOME_PLAINE, map, biomeValidationPourVillage);


    if (plusGrandePlaine != NULL) {
        const t_vecteur2 centre = {
            (plusGrandePlaine->position.x * TAILLE_CHUNK) + TAILLE_CHUNK / 2,
            (plusGrandePlaine->position.y * TAILLE_CHUNK) + TAILLE_CHUNK / 2,
        };
        
        const t_vecteur2 min = { centre.x - (TAILLE_CHUNK), centre.y - (TAILLE_CHUNK) };
        const t_vecteur2 max = { centre.x + (TAILLE_CHUNK), centre.y + (TAILLE_CHUNK) };

        const int nombreBatiment = getNombreAleatoire(6, 8);
        

        printf("GENERATION GRILLE => ");
        const t_discSampling grille = genererGrilleDiscSampling(min, max, nombreBatiment, 12, &centre);
        // grille.elementPositions[0] = centre;


        printf("NOMBRE STRUCTURE %i => ", grille.nbElements);
        for (int i = 0; i < grille.nbElements; i++) {
            t_vecteur2 position = grille.elementPositions[i];
            e_structureTag tag = selectionMaisonTag();

            if (!i && grille.nbElements > 1) {
                printf("GENERATION PUIT %i (%1.2f:%1.2f) => ", i, position.x, position.y);
                genererStructure(position, STRUCTURE_PUIT, map);
            }
            else {
                printf("GENERATION BATIMENT %i (%1.2f:%1.2f) => ", i, position.x, position.y);
                genererStructure(position, tag, map);
            }
        }


        if (grille.nbElements > 1) {
            genererChemins(map, grille);
            genererDecorations(map, grille);
        }


        free(grille.elementPositions);

    }

    printf("\n\n");
}





/* -------------------------------------------------------------------------- */
/*                                   Temple                                   */
/* -------------------------------------------------------------------------- */



/**
 * @brief 
 * 
 * @param map 
 */
void genererEntreeTemple(t_map *map) {
    printf("GENERATION ENTREE TEMPLE => ");
    t_chunk *plusGrandeMontagne = getChunkCentralBiome(BIOME_MONTAGNE, map, biomeValidationPourEntreeTemple);


    if (plusGrandeMontagne != NULL) {
        const t_vecteur2 centre = {
            (plusGrandeMontagne->position.x * TAILLE_CHUNK) + TAILLE_CHUNK / 2,
            (plusGrandeMontagne->position.y * TAILLE_CHUNK) + TAILLE_CHUNK / 2,
        };

        printf("%1.2f:%1.2f => ", centre.x, centre.y);
        genererStructure(centre, STRUCTURE_ENTREE_TEMPLE, map);
    }
    printf("\n");
}





/* -------------------------------------------------------------------------- */
/*                                   Caverne                                  */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param map 
 */
void genererEntreeCaverne(t_map *map) {
    printf("GENERATION ENTREE Caverne => ");

    
    printf("\n");
}

