/**
 * @file statisitques.c
 *
 * @brief
 *
 * @author Clément Hibon
 * @date 23 janvier
 * @version 1.1
 */





#include <stdlib.h>
#include <stdio.h>

#include "../include/statistiques.h"
#include "../include/monstre.h"
#include "../include/animal.h"





/* -------------------------------------------------------------------------- */
/*                                    Bases                                   */
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
t_baseStatistiques genererStatistiquesDeBaseMonstre(const e_monstreType type) {
    t_baseStatistiques baseStatistiques;
    t_baseStatistiquesIntervales baseStatistiquesIntervale = statistiquesDeBasesIntervalesMonstres[type];
  

    baseStatistiques.attaque = getNombreAleatoire(baseStatistiquesIntervale.attaque[0], baseStatistiquesIntervale.attaque[1]);
    baseStatistiques.defense = getNombreAleatoire(baseStatistiquesIntervale.defense[0], baseStatistiquesIntervale.defense[1]);
    baseStatistiques.vitesse = getNombreAleatoire(baseStatistiquesIntervale.vitesse[0], baseStatistiquesIntervale.vitesse[1]);
    baseStatistiques.pv = baseStatistiquesIntervale.pv;
    baseStatistiques.experience_courbe = getNombreAleatoire(baseStatistiquesIntervale.courbeExp[0], baseStatistiquesIntervale.courbeExp[1]);

      
    return baseStatistiques;
}



/**
 * @brief Génère les statistiques de base d'un animal
 * 
 * Elles sont déterminées de façon aléatoire dans un intervalle définit dans les informations de base d'un animal
 * Les statistiques de base sont utilisés à chaque fois que les statistiques ont besoins d'être calculées
 * 
 * @param tag Le tag l'animal
 * @return Les statistiques de base de l'animal
 */
t_baseStatistiques genererStatistiquesDeBaseAnimal(const e_entiteTag tag) {
    t_baseStatistiques baseStatistiques;
    t_baseStatistiquesIntervales baseStatistiquesIntervale = statistiquesDeBasesIntervalesMonstres[tag % TAG_ANIMAL_VACHE];
  

    baseStatistiques.attaque = getNombreAleatoire(baseStatistiquesIntervale.attaque[0], baseStatistiquesIntervale.attaque[1]);
    baseStatistiques.defense = getNombreAleatoire(baseStatistiquesIntervale.defense[0], baseStatistiquesIntervale.defense[1]);
    baseStatistiques.vitesse = getNombreAleatoire(baseStatistiquesIntervale.vitesse[0], baseStatistiquesIntervale.vitesse[1]);
    baseStatistiques.pv = baseStatistiquesIntervale.pv;
    baseStatistiques.experience_courbe = getNombreAleatoire(baseStatistiquesIntervale.courbeExp[0], baseStatistiquesIntervale.courbeExp[1]);

      
    return baseStatistiques;
}





/* -------------------------------------------------------------------------- */
/*                                   Calculs                                  */
/* -------------------------------------------------------------------------- */


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





/* -------------------------------------------------------------------------- */
/*                                 Generation                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief Génère les statistiques d'un mob en fonction des statistiques de base
 * 
 * @param baseStatistiques Les statistiques de base d'un mob
 * @param niveau Le niveau d'un mob
 * @return Les statistiques d'un mob
 */
t_statistiques genererStatistiques(const t_baseStatistiques baseStatistiques, const int niveau) {
    t_statistiques statistiques;


    statistiques.experience = 0;
    statistiques.niveau = niveau;

    statistiques.attaque = calculStatistique(baseStatistiques.attaque, niveau);
    statistiques.defense = calculStatistique(baseStatistiques.defense, niveau);
    statistiques.vitesse = 4.0; // calculStatistique(baseStatistiques.vitesse, niveau);

    statistiques.pv = calculPv(statistiques.attaque, statistiques.defense, baseStatistiques.pv);
    statistiques.pvMax = statistiques.pv;


    return statistiques;
}