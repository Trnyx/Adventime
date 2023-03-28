/**
 * @file map.h
 *
 * @brief
 *
 * @author Clément Hibon
 * @date 21 janvier
 * @version 1.4
 */





#ifndef _JEU_MAP_
#define _JEU_MAP_




#include "utilitaire.h"
#include "liste.h"





// #define TAILLE_MAP 8
// #define TAILLE_CHUNK 5

// La taille de la map (Le nombre de chunk)
// La map est carré
#define TAILLE_MAP 14
// La taille d'un chunk (le nombre de block)
// Le chunk est carré
#define TAILLE_CHUNK 16

// Le nombre de fois que la map est normalisé
#define NOMBRE_DE_NORMALISATION_MAP 1
// Le nombre de fois qu'un chunk est normalisé
#define NOMBRE_DE_NORMALISATION_CHUNK 2





/* -------------------------------------------------------------------------- */
/*                                 Enumeration                                */
/* -------------------------------------------------------------------------- */


/**
 * @enum e_mapType
 * @brief Le type de la map
 * 
 */
typedef enum {
    /*! La map principale */
    MAP_OVERWORLD,
    /*! La caverne */
    MAP_CAVE,
    /*! Le temple des boss */
    MAP_BOSS_TEMPLE,
    /*! L'intérieur des maisons */
    MAP_MAISON,
} e_mapType;


/**
 * @brief Tag permettant de reconnaitre la couche du chunk concerné
 * 
 * Un compteur du nombre de couche est également initialisé à la fin de l'énumérateur
 */
typedef enum {
    /*! La couche où sont stockés les blocks pour le sol */
    COUCHE_SOL,
    /*! La couche où sont stockés les blocks de décoration */
    COUCHE_OBJETS,
    /*! Le nombre de couche */
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
    // BIOME_DESERT,
    NB_BIOMES
} e_biome;


/**
 * @brief Enumérateur regroupant les probabilités d'apparition d'un biome
 */
typedef enum {
    PROBA_BIOME_PROFONDEUR = 0,
    PROBA_BIOME_LAC = 15,
    PROBA_BIOME_PLAINE = 45,
    PROBA_BIOME_FORET = 70,
    PROBA_BIOME_MONTAGNE = 100,
    // PROBA_BIOME_DESERT = 100,
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
    NB_TYPES_SOL,
    SOL_CHEMIN,
} e_solTag;





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */
#include "vegetations.h"
#include "monstre.h"



/**
 * @struct t_block
 * @brief Modélise un block
 */
typedef struct s_block {
    t_vecteur2 position;                /**< La position du block dans la map */
    t_vecteur2 positionDansChunk;       /**< La position du block dans le chunk */
    int tag;                            /**< Le tag du block */
} t_block;


/**
 * @struct t_chunk
 * @brief Modélise un chunk
 */
typedef struct s_chunk {
    e_biome biome;              /**< Le biome du chunk */
    t_vecteur3 position;        /**< La position du chunk dans la map */
    t_block *blocks;            /**< Les blocks contenue dans le chunk */
} t_chunk;


/**
 * @struct t_map
 * @brief Modélise une map
 */
typedef struct s_map {
    e_mapType type;             /**< Le type de la map */
    t_chunk *chunks;            /**< Les chunks contenue dans la map */

    // int nombreEntites;          /**< */
    // t_entite **entites;         /**< */
    t_liste *entites;           /**< Les entités contenue dans la map */
} t_map;



/**
 * @struct t_baseBiome
 * @brief Modélise la base d'un biome
 */
typedef struct s_baseBiome {
    e_biome biome;                          /**< Le biome concerné */
    int altitude;                           /**< L'altitude du biome */

    e_solTag typesDeSol[3];                 /**< Les différents type de blocks qui peuvent être générés dans le biome */
    int probabiliteDesBlocks[3];            /**< Les probabilités d'apparition des blocks */

    e_vegetalTag tagVegetations[2];         /**< Les différents tags de végétations qui peuvent être générées dans le biome */
    int probabilitesVegetations[2];         /**< Les probabilités d'apparition des végétaux */
    float vegetationDensite;                /**< La densité végétale du biome */

    e_monstreType typesMonstre[2];          /**< Les différents types de monstre qui peuvent apparaitre dans le biome */
    int probabilitesTypesMonstre[2];        /**< Les probabilités d'apparition des types de monstre */
} t_baseBiome;


/**
 * @brief Modélise un objet prédominant
 */
typedef struct s_predominance {
    int tag;                /**< Le tag de l'objet prédominant */
    int occurence;          /**< Le nombre de fois où on a compté cet objet */
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
t_block* getBlockDansMap(const int x, const int y, const int z, t_map *map);
t_chunk* getChunk(const int x, const int y, const int z, t_map *map);
t_chunk* getChunkGraceABlock(const int x, const int y, const int z, t_map *map);


// void normalisationDuChunk(t_chunk* chunk, t_map *map);


t_map* genererMap(e_mapType type);

void genererCave(t_map *map);
void genererVegetations(t_map *map);
void genererAnimaux(t_map *map);

int detruireMap(t_map **map);

void dessinerSol(t_map *map);
void dessinerObjets(t_map *map);






#endif