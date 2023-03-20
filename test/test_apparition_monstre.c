#include <stdlib.h>
#include <stdio.h>





#define NB_GEN 10





/* -------------------------------------------------------------------------- */
/*                                 Definitions                                */
/* -------------------------------------------------------------------------- */


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



/**
 * @brief Enumérateur regroupant les différents types des monstres
 * 
 * Un compteur du nombre de types est également initialisé à la fin de l'énumérateur
 */
typedef enum {
    MONSTRE_TYPE_NORMAL,
    MONSTRE_TYPE_PLANTE,
    MONSTRE_TYPE_MONTAGNARD,
    // MONSTRE_TYPE_DESERTIQUE,
    NB_MONSTRE_TYPES,
} e_monstreType;





/**
 * @brief Modélise la base d'un biome très simplifié
 */
typedef struct s_baseBiome {
    e_biome biome;                          /**< */

    e_monstreType typesMonstre[2];          /**< */
    int probabilitesTypesMonstre[2];        /**< */
} t_baseBiome;



const t_baseBiome basesBiomes[] = {
    { 
        BIOME_PROFONDEUR, 
        // Monstres
        { 0 }, { 0 },
    },


    { 
        BIOME_LAC,
        // Monstres
        { MONSTRE_TYPE_NORMAL }, { 100 },
    },
  
  
    { 
        BIOME_PLAINE,
        // Monstres
        { MONSTRE_TYPE_NORMAL, MONSTRE_TYPE_PLANTE }, { 90, 100 },
    },
  
  
    { 
        BIOME_FORET,
        // Monstres
        { MONSTRE_TYPE_NORMAL, MONSTRE_TYPE_PLANTE }, { 10, 100 },
    },
  
  
    { 
        BIOME_MONTAGNE, 
        // Monstres
        { MONSTRE_TYPE_MONTAGNARD }, { 100 },
    },
  
  
    // { 
    //     BIOME_DESERT,
    //     // Monstres
    //     { MONSTRE_TYPE_DESERTIQUE }, { 100 },
    // },
};





int getNombreAleatoire(const int min, const int max) {
    return min + rand() % ((max + 1) - min);
}





/**
 * @brief Modélise un monstre très simplifié
 */
typedef struct s_monstre {
    
    int niveau;
    
    e_monstreType type;         /**< Le type du Monstre */
    int estNocturne;

} t_monstre;










/**
 * @brief Choisis le type d'un monstre en fonction du biome où il apparait
 * 
 * @param baseBiome La base du biome dans lequel le monstre apparait
 * @return Le type du monstre
 */
e_monstreType choisirTypeMonstre(const t_baseBiome baseBiome) {
    e_monstreType type = MONSTRE_TYPE_NORMAL;
    const int nombreTypesPossible = sizeof(baseBiome.typesMonstre) / sizeof(baseBiome.typesMonstre[0]);


    if (baseBiome.probabilitesTypesMonstre[0] == 100) {
        return baseBiome.typesMonstre[0];
    }

  
    // const int index = getNombreAleatoire(0, nombreTypesPossible - 1);
    const int probabilite = getNombreAleatoire(1, 100);
    for (int i = 0; i < nombreTypesPossible; i++) {
        if (baseBiome.probabilitesTypesMonstre[i] >= probabilite) {
            return baseBiome.typesMonstre[i];
        }
    }


    return type;
}





/**
 * @brief 
 * 
 * @param biome 
 * @param niveauJoueur 
 * @return t_monstre* 
 */
t_monstre* creerMonstre(const e_biome biome, const int niveauJoueur) {
    t_monstre *monstre = malloc(sizeof(t_monstre));


    if (monstre == NULL) {
        printf("Erreur lors de la création du monstre");
        return NULL;
    }


    monstre->type = choisirTypeMonstre(basesBiomes[biome]);


    
    return monstre;
}





/**
 * @brief 
 * 
 * @param monstre 
 * @return int 
 */
void detruireMonstre(t_monstre **monstre) {
    if (monstre != NULL && *monstre != NULL) {

        free(*monstre);
        *monstre = NULL;
        
    }
}










/* -------------------------------------------------------------------------- */
/*                                  Affichage                                 */
/* -------------------------------------------------------------------------- */


void divider() {
    printf("\n--------------------------------------------\n");
}





void afficherMonstre(t_monstre *monstre) {
    printf("{");

    printf("TYPE: %i", monstre->type);

    // printf("\tStatistiques : {\n");
    // printf("\t\tPV      : %1.2f \n", monstre->statistiques.pv);
    // printf("\t\tAttaque : %1.2f \n", monstre->statistiques.attaque);
    // printf("\t\tDefense : %1.2f \n", monstre->statistiques.defense);
    // printf("\t\tVitesse : %1.2f \n", monstre->statistiques.vitesse);
    // printf("\t}\n");

    printf("} ");
}










void creationDesMonstres(const e_biome biome) {
    t_monstre *monstre = NULL;


    for (int niveau = 1; niveau <= 10; niveau++) {
        printf("NIVEAU DU JOUEUR : %i\t", niveau);

        for (int i = 0; i < NB_GEN; i++) {
            monstre = creerMonstre(biome, niveau);

            if (monstre == NULL) {
                printf("Erreur creation monstre : Gen. n %i / NIVEAU %i / BIOME : %i\n", i, niveau, biome);
                return;
            }


            afficherMonstre(monstre);
            detruireMonstre(&monstre);
        }

        printf("\n");
    }
}










int main(int argc, char *argv[]) {
    // Couleur des monstres en fonction des types :
    //  - NORMAL        : bleu
    //  - PLANTE        : vert
    //  - MONTAGNARD    : gris
    //  - NOCTURNE      : violet



    printf("Debut du programme de test d'apparition des monstres\n");
    printf("10 générations pour des niveaux de joueur allant de 1 à 10\n");
    divider();


    // Création de monstres dans un biome PLAINE
    // Le type du monstre attendu est un type NORMAL ou PLANTE
    printf("Apparition de monstres dans un biome PLAINE (%i)\n", BIOME_PLAINE);
    printf("Le type du monstre attendu est un type NORMAL ou PLANTE (%i ou %i)\n", MONSTRE_TYPE_NORMAL, MONSTRE_TYPE_PLANTE);

    creationDesMonstres(BIOME_PLAINE);
    divider();



    // Création de monstres dans un biome FORET
    // Le type du monstre attendu est un type PLANTE ou NORMAL
    printf("Apparition de monstres dans un biome FORET (%i)\n", BIOME_FORET);
    printf("Le type du monstre attendu est un type PLANTE ou NORMAL (%i ou %i)\n", MONSTRE_TYPE_PLANTE, MONSTRE_TYPE_NORMAL);

    creationDesMonstres(BIOME_FORET);
    divider();


    // Création de monstres dans un biome MONTAGNE
    // Le type du monstre attendu est un type MONTAGNARD
    printf("Apparition de monstres dans un biome MONTAGNE (%i)\n", BIOME_MONTAGNE);
    printf("Le type du monstre attendu est un type MONTAGNARD (%i)\n", MONSTRE_TYPE_MONTAGNARD);

    creationDesMonstres(BIOME_MONTAGNE);
    divider();




    printf("Fin du programme de test d'apparition des monstres\n");


    return EXIT_SUCCESS;
}