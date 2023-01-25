/*
 * \file 
 *
 * \brief
 *
 * \author
 */



#ifndef _JEU_MAP_
#define _JEU_MAP_



#include <utils.h>



#define TAILLE_MAP 10
#define TAILLE_CHUNK 12

#define NB_BIOMES 5
#define NB_BLOCKS 9





typedef enum s_biomeTag {
    PROFONDEUR,
    LAC,
    PLAINE,
    FORET,
    MONTAGNE,
} e_biome;


typedef enum s_biomeProba {
    PROBA_PROFONDEUR = 0,
    PROBA_LAC = 30,
    PROBA_PLAINE = 35,
    PROBA_FORET = 25,
    PROBA_MONTAGNE = 10,
} e_biomeProba;


typedef enum s_blockTag {
    VIDE = -100,
    EAU_PROFONDE = 0,
    EAU,
    SABLE,
    HERBE_1, 
    HERBE_2, 
    HERBE_3,
    MONTAGNE_1, 
    MONTAGNE_2,
    NEIGE,
} e_blockTag;





/*
 * \struct t_block
 * \brief
 */
typedef struct s_block {
    t_vecteur2 position;
    t_vecteur2 positionDansChunk;
    e_blockTag tag;
} t_block;


/*
 * \struct t_chunk
 * \brief
 */
typedef struct s_chunk {
    e_biome biome;
    t_vecteur2 position;
    t_block *blocks[TAILLE_CHUNK][TAILLE_CHUNK];
} t_chunk;


/*
 * \struct t_map
 * \brief
 */
typedef struct s_map {
    t_chunk *chunks[TAILLE_MAP][TAILLE_MAP];
} t_map;



/*
 * \struct t_baseBiome
 * \brief
 */
typedef struct s_baseBiome {
    e_biome biome;
    int altitude;
    e_blockTag typeDeBlocks[3];
    int probabiliteDesBlocks[3];
} t_baseBiome;


/*
 * \struct t_predominance
 * \brief
 */
typedef struct s_predominance {
    int tag;
    int occurence;
} t_predominance;





const e_biome biomes[] = { 
    PROFONDEUR, 
    LAC, 
    PLAINE, 
    FORET, 
    MONTAGNE,
};


const int probabilitesBiomes[] = { 
    PROBA_PROFONDEUR, 
    PROBA_LAC, 
    PROBA_PLAINE, 
    PROBA_FORET, 
    PROBA_MONTAGNE 
};





const t_baseBiome baseBiomes[] = {
    { PROFONDEUR, -1, { EAU_PROFONDE, EAU }, { 90, 10 } },
    { LAC, 0, { EAU, SABLE }, { 80, 20 } },
    { PLAINE, 1, { HERBE_1, HERBE_2, HERBE_3 }, { 45, 35, 20 } },
    { FORET, 1, { HERBE_1, HERBE_2, HERBE_3 }, { 45, 35, 20 } },
    { MONTAGNE, 2, { MONTAGNE_1, MONTAGNE_2 }, { 50, 50 } },
};





int blockEstDansLeChunk(const int x, const int y);
int blockEstDansLaMap(const int x, const int y);
int chunkEstDansLaMap(const int x, const int y);

t_block* getBlockDansChunk(const int x, const int y, t_chunk *chunk);
t_block* getBlockDansMap(const int x, const int y, t_chunk *chunk);
t_chunk* getChunk(const int x, const int y, t_map *map);


t_map* genererMap();






#endif