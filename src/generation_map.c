/*
 * \file 
 *
 * \brief
 *
 * \author
 */



#include <stdlib.h>
#include <map.h>





/* -------------------------------------------------------------------------- */
/*                               Test Existence                               */
/* -------------------------------------------------------------------------- */


int blockEstDansLeChunk(const int x, const int y) {
    return x > 0 || y > 0 || x < TAILLE_CHUNK - 1 || y < TAILLE_CHUNK - 1;
}


int blockEstDansLaMap(const int x, const int y) {
    return x > 0 || y > 0 || x < (TAILLE_MAP * TAILLE_CHUNK) - 1 || y < (TAILLE_MAP * TAILLE_CHUNK) - 1;
}


int chunkEstDansLaMap(const int x, const int y) {
    return x > 0 || y > 0 || x < TAILLE_MAP - 1 || y < TAILLE_MAP - 1;
}



/* -------------------------------------------------------------------------- */
/*                                     Get                                    */
/* -------------------------------------------------------------------------- */


t_block* getBlockDansChunk(const int x, const int y, t_chunk *chunk) {
    return chunk->blocks[y][x];
}



t_chunk* getChunk(const int x, const int y, t_map *map) {
    return map->chunks[y][x];
}


t_predominance getPredominance(int alentours[]) {
    t_predominance predominance = { 0, 0 };  

  
    for (int i = 0; i < longueur(alentours); i++) {
        if (alentours[i] > predominance.occurence) {
            predominance.occurence = alentours[i];
            predominance.tag = i;
        }
      
        alentours[i] = 0;
    }


    return predominance;
}





/* -------------------------------------------------------------------------- */
/*                                  Selection                                 */
/* -------------------------------------------------------------------------- */


e_biome selectionBiome(const int xChunk, const int yChunk) {
    if (!chunkEstDansLaMap(xChunk, yChunk)) return PROFONDEUR;

    e_biome biome = PROFONDEUR;
  

    while (biome == PROFONDEUR) {
        int index = rand() % NB_BIOMES;
        int probabilite = rand() % 100;

        int probabiliteBiome = probabilitesBiomes[index];
        if (probabiliteBiome > probabilite) return biomes[index];
    }

  
    return biome;
}



e_blockTag selectionBlock(const int x, const int y, const e_biome biome) {
    e_blockTag blockTag = VIDE;
    t_baseBiome baseBiome = baseBiomes[biome];
    int nombreBlockPossible = sizeof(baseBiome.typeDeBlocks) / sizeof(baseBiome.typeDeBlocks[0]); // longueur(baseBiome.typeDeBlocks);


    while (blockTag == VIDE) {
        int index = rand() % nombreBlockPossible;
        int probabilite = rand() % 100;
    
        int probabiliteBlock = baseBiome.probabiliteDesBlocks[index];
        if (probabiliteBlock >= probabilite) {
            return baseBiome.typeDeBlocks[index];
        }
    }
  
  
    return blockTag;
}





/* -------------------------------------------------------------------------- */
/*                                 Changement                                 */
/* -------------------------------------------------------------------------- */


e_biome changerBiome(t_predominance biomePredominant, e_biome biomeActuel) { 
    int modificateurAltitude = 0;
    int changement = 0;
  
  
    switch (biomePredominant.tag) {
        case MONTAGNE: 
            if (biomePredominant.occurence >= 2 && biomePredominant.occurence <= 3) changement = 1;
            break;
        case PLAINE: 
        case FORET: 
            if (biomePredominant.occurence >= 2 && biomePredominant.occurence <= 6) changement = 1;
            break;
        case LAC: 
            if (biomePredominant.occurence == 5) changement = 1;
            break;
        case PROFONDEUR: 
            if (biomePredominant.occurence >= 3) changement = 1;
            break;
    }


    if (changement) {
        if (biomePredominant.tag > biomeActuel) 
            modificateurAltitude = 1;
        else if (biomePredominant.tag < biomeActuel)
            modificateurAltitude = -1;
    }


    if (biomeActuel == biomePredominant.tag) return biomeActuel;
    return biomeActuel + modificateurAltitude;
}





e_blockTag changerBlock(t_predominance blockPredominant, e_blockTag blockActuel) {
    int modificateurAltitude = 0;

    if (blockPredominant.tag > blockActuel) modificateurAltitude = 1;
    else if (blockPredominant.tag < blockActuel) modificateurAltitude = -1;

    return blockActuel + modificateurAltitude;
}





/* -------------------------------------------------------------------------- */
/*                                  Alentours                                 */
/* -------------------------------------------------------------------------- */


int* getBiomesAlentours(t_chunk chunk, t_map *map) {
    static int biomesAlentours[NB_BIOMES] = { 0 };
    t_chunk *chunkCourrant = NULL;
  

    for (int y = chunk.position.y - 1; y <= chunk.position.y + 1; y++) {
        for (int x = chunk.position.x - 1; x <= chunk.position.x + 1; x++) {
            if (!chunkEstDansLaMap(x, y)) continue;
            if (x == chunk.position.x && y == chunk.position.y) continue;

          
            chunkCourrant = getChunk(x, y, map);
            if (chunkCourrant != NULL) {
                biomesAlentours[chunkCourrant->biome]++;
            }
        }
    }


    return biomesAlentours;
}



int get = 0;
int* getBlocksAlentours(const int xBlock, const int yBlock, t_map *map) {
    static int blocksAlentours[NB_BLOCKS] = { 0 };
    t_chunk *chunk = NULL;
    t_block *blockTempo = NULL;

  
    for (int y = yBlock - 1; y <= yBlock + 1; y++) {
        for (int x = xBlock - 1; x <= xBlock + 1; x++) {
            if (x == xBlock && y == yBlock) continue;
            if (!blockEstDansLaMap(x, y)) continue;

            chunk = getChunk(x / TAILLE_CHUNK, y / TAILLE_CHUNK, map);
            if (chunk == NULL) continue;


            blockTempo = getBlockDansChunk(x % TAILLE_CHUNK, y % TAILLE_CHUNK, chunk);
            if (blockTempo == NULL) continue;
          
          
            blocksAlentours[blockTempo->tag]++;
        }
    }


    return blocksAlentours;
}





/* -------------------------------------------------------------------------- */
/*                                Normalisation                               */
/* -------------------------------------------------------------------------- */


void normalisationDuChunk(t_chunk* chunk, t_map *map) {
    e_blockTag blockVoisins[TAILLE_CHUNK][TAILLE_CHUNK] = { EAU_PROFONDE };
    t_block *block = NULL;


    for (int y = 0; y < TAILLE_CHUNK; y++) {
        for (int x = 0; x < TAILLE_CHUNK; x++) {
            block = getBlockDansChunk(x, y, chunk);

            int *blocksAlentours = getBlocksAlentours(block->position.x, block->position.y, map);
            t_predominance blockPredominant = getPredominance(blocksAlentours);

            if (blockPredominant.occurence >= 3) {
                block->tag = changerBlock(blockPredominant, block->tag);
            }
        }
    }
}





void normalisationDeLaMap(t_map* map) {  
    e_biome nouveauxBiomes[TAILLE_MAP][TAILLE_MAP] = { PROFONDEUR };
    t_chunk *chunk = NULL;


    for (int y = 0; y < TAILLE_MAP; y++) {
        for (int x = 0; x < TAILLE_MAP; x++) {
            chunk = getChunk(x, y, map);
          
            int *biomesAlentours = getBiomesAlentours(*chunk, map);
            t_predominance biomePredominant = getPredominance(biomesAlentours);

          
            nouveauxBiomes[y][x] = changerBiome(biomePredominant, chunk->biome);
        }
    }


    for (int y = 0; y < TAILLE_MAP; y++) {
        for (int x = 0; x < TAILLE_MAP; x++) {
            chunk = getChunk(x, y, map);
            chunk->biome = nouveauxBiomes[y][x];
        }
    }
}





/* -------------------------------------------------------------------------- */
/*                               Initialisation                               */
/* -------------------------------------------------------------------------- */


t_chunk* initialisationChunk(const int x, const int y) {
    t_chunk* chunk = malloc(sizeof(t_chunk));


    e_biome biome = selectionBiome(x, y);
    chunk->biome = biome;

    t_vecteur2 position = { x, y };
    chunk->position = position;


    return chunk;
}



t_block* initialisationBlock(const int x, const int y, const t_chunk chunk) {
    t_block* block = malloc(sizeof(t_block));


    e_blockTag blockTag = selectionBlock(x, y, chunk.biome);
    block->tag = blockTag;

    t_vecteur2 position = { TAILLE_CHUNK * chunk.position.x + x, TAILLE_CHUNK * chunk.position.y + y };
    t_vecteur2 positionDansChunk = { x, y };
  
    block->position = position;
    block->positionDansChunk = positionDansChunk;


    return block;
}





/* -------------------------------------------------------------------------- */
/*                                 Generation                                 */
/* -------------------------------------------------------------------------- */



t_chunk* generationChunk(t_chunk *chunk, t_map *map) {
    t_block *blockTempo = NULL;

  
    for (int y = 0; y < TAILLE_CHUNK; y++) {
        for (int x = 0; x < TAILLE_CHUNK; x++) {
            chunk->blocks[y][x] = initialisationBlock(x, y, *chunk);
        }
    }


    for (int i = 0; i < 2; i++) {
        normalisationDuChunk(chunk, map);
    }


    return chunk;
}





t_map* genererMap() {
    t_map* map = malloc(sizeof(t_map));
    t_chunk* chunkTempo = NULL;


    for (int y = 0; y < TAILLE_MAP; y++) {
        for (int x = 0; x < TAILLE_MAP; x++) {
            map->chunks[y][x] = initialisationChunk(x, y);
        }
    }


    for (int i = 0; i < 2; i++) {
        normalisationDeLaMap(map);
    }


    for (int y = 0; y < TAILLE_MAP; y++) {
        for (int x = 0; x < TAILLE_MAP; x++) {
            chunkTempo = getChunk(x, y, map);
            generationChunk(chunkTempo, map);
        }
    }

    

    return map;
}





int detruireBlock(t_block **block) {
    if (block == NULL || *block == NULL) return 0;

    free(*block);
    *block = NULL;

    return 0;
}


int detruireChunk(t_chunk **chunk) {
    if (chunk == NULL || *chunk == NULL) return 0;
    t_block *block = NULL;
  

    for (int y = 0; y < TAILLE_CHUNK; y++) {
        for (int x = 0; x < TAILLE_CHUNK; x++) {
            block = getBlockDansChunk(x, y, *chunk);
            detruireBlock(&block);
        }
    }
  
    free(*chunk);
    *chunk = NULL;

  
    return 0;
}


int detruireMap(t_map **map) {
    if (map == NULL || *map == NULL) return 0;
    t_chunk *chunk = NULL;
  

    for (int y = 0; y < TAILLE_MAP; y++) {
        for (int x = 0; x < TAILLE_MAP; x++) {
            chunk = getChunk(x, y, *map);
            detruireChunk(&chunk);
        }
    }
  
    free(*map);
    *map = NULL;

  
    return 0;
}






/**
 * Generation map
 *      Initialisationn Chunk
 *      Normalisation Chunk
 *      Génération Chunk
 *          Initialisation Block
 *          Normalisation Block
 *          Génération Block
 */