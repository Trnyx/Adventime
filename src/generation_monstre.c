/**
 * @file generation_monstre.c
 *
 * @brief Génération d'un monstre
 *
 * @author Clément Hibon
 * @date 23 janvier
 * @version 1.1
 */



#include <stdlib.h>

#include "../include/physique.h"
#include "../include/moteur.h"
#include "../include/monstre.h"
#include "../include/map.h"





/* -------------------------------------------------------------------------- */
/*                                  Selection                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief Choisis le type d'un monstre en fonction du biome où il apparait
 * 
 * @param baseBiome La base du biome dans lequel le monstre apparait
 * 
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





boolean estNocturne() {
    t_temps *temps = moteur->temps;

    if (temps->cycleJeu == CYCLE_JOUR || temps->cycleVrai == CYCLE_JOUR)
        return FAUX;


    return FAUX;
}





/* -------------------------------------------------------------------------- */
/*                                 Generation                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief Génère un monstre
 * 
 * @param monstre Pointeur sur le monstre à générer
 * @param biome Le biome dans lequel le monstre apparait
 * @param niveauJoueur Le niveau du joueur
 * 
 * @return Un pointeur sur le monstre généré
 */
t_monstre* genererMonstre(t_monstre *monstre, const e_biome biome, const int niveauJoueur) {
    // monstre->tag = choisirMonstreTag();
    monstre->tag = TAG_MONSTRE_BASIC;
    monstre->type = choisirTypeMonstre(basesBiomes[biome]);

    const int niveau = niveauJoueur;

    monstre->baseStatistiques = genererStatistiquesDeBaseMonstre(monstre->type);
    monstre->statistiques = genererStatistiques(monstre->baseStatistiques, niveau);

    monstre->estNocturne = estNocturne();
    
    return monstre;
}



