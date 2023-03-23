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
#include <stdio.h>
#include <math.h>

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





int calculNiveau(const unsigned int niveauJoueur) {
    if (niveauJoueur <= 3)
        return niveauJoueur;

    else if (niveauJoueur <= 7)
        return getNombreAleatoire(niveauJoueur - 1, niveauJoueur);

    else if (niveauJoueur <= 9)
        return getNombreAleatoire(niveauJoueur - 1, niveauJoueur + 1);
    
    else
        return 10;
}





/**
 * @brief 
 * 
 * @return boolean 
 */
boolean estNocturne() {
    t_temps *temps = moteur->temps;
    struct tm *t = localtime(&temps->timestamp);

    if (temps->cycleJeu == CYCLE_NUIT && (t->tm_hour >= 0 || t->tm_hour <= 4)) {
        const int proba = getNombreAleatoire(1, 100);

        // La probabilité d'apparition d'un monstre nocturne se calcule de la manière suivante :
        // On fait la racine du nombre de nuit par heure dans l'interval entre minuit et quatre heure
        const int probabiliteApparition = sqrt(NOMBRE_JOUR * 4);

        if (proba < probabiliteApparition)
            return VRAI;
    }


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

    printf("NIVEAU => ");
    const int niveau = calculNiveau(niveauJoueur);
    printf("OK\n");

    monstre->baseStatistiques = genererStatistiquesDeBaseMonstre(monstre->type);
    monstre->statistiques = genererStatistiques(monstre->baseStatistiques, niveau);

    monstre->estNocturne = estNocturne();
    
    return monstre;
}



