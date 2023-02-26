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
#include "../include/monstre.h"
#include "../include/map.h"





/* -------------------------------------------------------------------------- */
/*                                  Selection                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief Choisis le type d'un monstre en fonction du biome où il apparait
 * 
 * @param baseBiome La base du biome dans lequel le monstre apparait
 * @return Le type du monstre
 */
e_monstreType choisirTypeMonstre(const t_baseBiome baseBiome) {
    e_monstreType type = -1;
    int nombreTypesPossible = sizeof(baseBiome.typesMonstre) / sizeof(baseBiome.typesMonstre[0]);

  
    while (type == -1) {
        int index = getNombreAleatoire(0, nombreTypesPossible - 1);
        int probabilite = getNombreAleatoire(0, 100);
        
        int probabiliteType = baseBiome.probabilitesTypesMonstre[index];
        if (probabiliteType >= probabilite) {
            return baseBiome.typesMonstre[index];
        }
    }


    return type;
}





/* -------------------------------------------------------------------------- */
/*                                   Calculs                                  */
/* -------------------------------------------------------------------------- */


/**
 * @brief Génère les statistiques de base d'un monstre
 * 
 * Elles sont déterminées de façon aléatoire dans un intervalle définit dans les informations de base d'un monstre
 * Les statistiques de base sont utilisés à chaque fois que les statistiques ont besoins d'être calculées
 * 
 * @param type Le type du monstre
 * @return Les statistiques de base du monstre
 */
t_baseStatistiques genererStatistiquesDeBase(const e_monstreType type) {
    t_baseStatistiques baseStatistiques;
    t_baseStatistiquesIntervales baseStatistiquesIntervale = statistiquesDeBasesIntervales[type];
  

    baseStatistiques.attaque = getNombreAleatoire(baseStatistiquesIntervale.attaque[0], baseStatistiquesIntervale.attaque[1]);
    baseStatistiques.defense = getNombreAleatoire(baseStatistiquesIntervale.defense[0], baseStatistiquesIntervale.defense[1]);
    baseStatistiques.vitesse = getNombreAleatoire(baseStatistiquesIntervale.vitesse[0], baseStatistiquesIntervale.vitesse[1]);
    baseStatistiques.pv = baseStatistiquesIntervale.pv;
    baseStatistiques.experience_courbe = getNombreAleatoire(baseStatistiquesIntervale.courbeExp[0], baseStatistiquesIntervale.courbeExp[1]);

      
    return baseStatistiques;
}



/**
 * @brief Calcul des statistiques en fonction des statistiques de bases et du niveau du monstre
 * 
 * @param base La statistique de base concerné
 * @param niveau Le niveau du monstre
 * @return La valeur de la statistique
 */
int calculStatistique(const int base, const int niveau) {
    return ((((2 * base + base * niveau * 0.6) * niveau) / 100) + niveau + 10);
}


/**
 * @brief Calcul la statistique "pv" d'un monstre en fonction de ses points d'attaque, de défense et de la base des pv
 * 
 * @param attaque Les points d'attaque du monstre
 * @param defense Les points de défense du monstre
 * @param basePv La statistique de base
 * @return Le nombre de point de vie maximum du monstre
 */
int calculPv(const int attaque, const int defense, const int basePv) {
    return (attaque + defense) + (basePv * 0.3) + 10;
}



/**
 * @brief Génère les statistiques du monstre en fonction des statistiques de base
 * 
 * @param baseStatistiques Les statistiques de base du monstre
 * @param niveau Le niveau du monstre
 * @return Les statistiques du monstre
 */
t_statistiques genererStatistiques(const t_baseStatistiques baseStatistiques, const int niveau) {
    t_statistiques statistiques;

    statistiques.attaque = calculStatistique(baseStatistiques.attaque, niveau);
    statistiques.defense = calculStatistique(baseStatistiques.defense, niveau);
    statistiques.vitesse = calculStatistique(baseStatistiques.vitesse, niveau);
    statistiques.pv = calculPv(statistiques.attaque, statistiques.defense, baseStatistiques.pv);

    return statistiques;
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
 * @return Un pointeur sur le monstre généré
 */
t_monstre* genererMonstre(t_monstre *monstre, const e_biome biome, const int niveauJoueur) {
    // monstre->tag = choisirMonstreTag();
    monstre->tag = MONSTRE_OISEAU;
    monstre->type = choisirTypeMonstre(basesBiomes[biome]);

    monstre->statistiques.niveau = niveauJoueur;
    monstre->baseStatistiques = genererStatistiquesDeBase(monstre->type);
    monstre->statistiques = genererStatistiques(monstre->baseStatistiques, monstre->statistiques.niveau);
    
    return monstre;
}



