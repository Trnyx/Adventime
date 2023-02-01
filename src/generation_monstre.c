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
#include <monstre.h>
#include <map.h>





/**
 * @brief Tableau regroupant les intervales des statistiques de bases en fonction du type du monstre
 * 
 */
const t_baseStatistiquesIntervales statistiquesDeBasesIntervales[NB_MONSTRE_TYPES] = {
    { { 60, 70 }, { 60, 70 }, { 10, 10 }, 80, { 0 } }, // NORMAL
    { { 65, 75 }, { 55, 65 }, { 15, 15 }, 80, { 0 } }, // PLANTE
    { { 55, 65 }, { 60, 70 }, { 10, 10 }, 90, { 0 } }, // EAU
    { { 55, 65 }, { 75, 85 }, { 15, 15 }, 80, { 0 } }, // MONTAGNARD
};





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
 * @param x La coordonnée x du monstre
 * @param y La coordonnée y du monstre
 * @param biome Le biome dans lequel le monstre apparait
 * @return Un pointeur sur le monstre généré
 */
t_monstre* creerMonstre(const int x, const int y, e_biome biome) {
    t_monstre *monstre = malloc(sizeof(t_monstre));

    monstre->position.x = x;
    monstre->position.y = y;

    monstre->tag = choisirMonstreTag();
    monstre->type = choisirTypeMonstre(basesBiomes[biome]);

    monstre->statistiques.niveau = 3;
    monstre->baseStatistiques = genererStatistiquesDeBase(monstre->type);
    monstre->statistiques = genererStatistiques(monstre->baseStatistiques, monstre->statistiques.niveau);
    
    return monstre;
}





/* -------------------------------------------------------------------------- */
/*                                 Destruction                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param monstre 
 * @return int 
 */
int detruireMonstre(t_monstre **monstre) {
    if (monstre == NULL && *monstre == NULL) return 0;

    free(*monstre);
    *monstre = NULL;

    return 0;
}
