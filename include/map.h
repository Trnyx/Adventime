/**
 * @file map.h
 *
 * @brief
 *
 * @author Clément Hibon
 * @date 21 janvier
 * @version 1.2
 */





#ifndef _JEU_MAP_
#define _JEU_MAP_




#include "utilitaire.h"





// #define TAILLE_MAP 8
// #define TAILLE_CHUNK 5
#define TAILLE_MAP 14
#define TAILLE_CHUNK 16

#define NOMBRE_DE_NORMALISATION_MAP 1
#define NOMBRE_DE_NORMALISATION_CHUNK 2





/* -------------------------------------------------------------------------- */
/*                                 Enumeration                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief Tag permettant de reconnaitre la couche du chunk concerné
 * 
 * Un compteur du nombre de couche est également initialisé à la fin de l'énumérateur
 */
typedef enum {
    COUCHE_SOL,
    COUCHE_VEGETATION,
    COUCHE_ENTITE,
    NB_COUCHE,
} e_coucheMap;



/**
 * @brief Tag permettant de reconnaitre le biome 
 * 
 * Un compteur du nombre de biome est également initialisé à la fin de l'énumérateur
 */
typedef enum {
    BIOME_PROFONDEUR,
    BIOME_LAC,
    BIOME_PLAINE,
    BIOME_FORET,
    BIOME_MONTAGNE,
    NB_BIOMES
} e_biome;


/**
 * @brief Enumérateur regroupant les probabilités d'apparition d'un biome
 */
typedef enum {
    PROBA_BIOME_PROFONDEUR = 0,
    PROBA_BIOME_LAC = 15,
    PROBA_BIOME_PLAINE = 50,
    PROBA_BIOME_FORET = 70,
    PROBA_BIOME_MONTAGNE = 100,
} e_biomeProba;


/**
 * @brief Tag permettant de reconnaitre le type de sol
 * 
 * Un compteur du nombre de types de sol est également initialisé à la fin de l'énumérateur
 */
typedef enum {
    VIDE = -100,
    SOL_EAU_PROFONDE = 0,
    SOL_EAU,
    SOL_SABLE,
    SOL_HERBE_1, 
    SOL_HERBE_2, 
    SOL_HERBE_3,
    SOL_MONTAGNE_1, 
    SOL_MONTAGNE_2,
    SOL_NEIGE,
    NB_TYPES_SOL
} e_solTag;





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */
#include "vegetations.h"
#include "monstre.h"



/**
 * @brief Modélise un block
 */
typedef struct s_block {
    t_vecteur2 position;
    t_vecteur2 positionDansChunk;
    int tag;
} t_block;


/**
 * @brief Modélise un chunk
 */
typedef struct s_chunk {
    e_biome biome;
    t_vecteur3 position;
    t_block *blocks;
} t_chunk;


/**
 * @brief MOdélise une map
 */
typedef struct s_map {
    t_chunk *chunks;
} t_map;



/**
 * @brief Modélise la base d'un biome
 */
typedef struct s_baseBiome {
    e_biome biome;
    int altitude;

    e_solTag typesDeSol[3];
    int probabiliteDesBlocks[3];

    e_vegetalTag tagVegetations[2];
    int probabilitesVegetations[2];
    float vegetationDensite[2];

    e_monstreType typesMonstre[2];
    int probabilitesTypesMonstre[2];
} t_baseBiome;


/**
 * @brief Modélise un objet prédominant
 */
typedef struct s_predominance {
    int tag;
    int occurence;
} t_predominance;





/* -------------------------------------------------------------------------- */
/*                                 Constantes                                 */
/* -------------------------------------------------------------------------- */


extern const e_biome biomes[];
extern const int probabilitesBiomes[];
extern const t_baseBiome basesBiomes[];





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


int blockEstDansLeChunk(const int x, const int y);
int blockEstDansLaMap(const int x, const int y);
int chunkEstDansLaMap(const int x, const int y, const int z);

t_block* getBlockDansChunk(const int x, const int y, t_chunk *chunk);
t_chunk* getChunk(const int x, const int y, const int z, t_map *map);


t_map* genererMap();
int detruireMap(t_map **map);






#endif