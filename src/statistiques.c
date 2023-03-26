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
#include <math.h>

#include "../include/statistiques.h"
#include "../include/experience.h"
#include "../include/monstre.h"
#include "../include/animal.h"
#include "../include/boss.h"





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
    t_baseStatistiquesIntervales baseStatistiquesIntervale = statistiquesDeBasesIntervalesAnimaux[tag - TAG_ANIMAL_VACHE];
  

    baseStatistiques.attaque = getNombreAleatoire(baseStatistiquesIntervale.attaque[0], baseStatistiquesIntervale.attaque[1]);
    baseStatistiques.defense = getNombreAleatoire(baseStatistiquesIntervale.defense[0], baseStatistiquesIntervale.defense[1]);
    baseStatistiques.vitesse = getNombreAleatoire(baseStatistiquesIntervale.vitesse[0], baseStatistiquesIntervale.vitesse[1]);
    baseStatistiques.pv = baseStatistiquesIntervale.pv;
    baseStatistiques.experience_courbe = getNombreAleatoire(baseStatistiquesIntervale.courbeExp[0], baseStatistiquesIntervale.courbeExp[1]);

      
    return baseStatistiques;
}



/**
 * @brief Génère les statistiques de base d'un boss
 * 
 * Elles sont déterminées de façon aléatoire dans un intervalle définit dans les informations de base d'un boss
 * Les statistiques de base sont utilisés à chaque fois que les statistiques ont besoins d'être calculées
 * 
 * @param jour Le jour du boss
 * @return Les statistiques de base du boss
 */
t_baseStatistiques genererStatistiquesDeBaseBoss(const e_jour jour) {
    t_baseStatistiques baseStatistiques = statistiquesDeBasesBoss[jour];  
      
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
 * @param niveau Le niveau du mob
 * @return Les statistiques du mob
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






/* -------------------------------------------------------------------------- */
/*                                 Experiences                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief On vérifie si l'entité change de niveau, si c'est le cas alors on met les statistiques de l'entité à jour
 * 
 * Cette vérification se fait via l'utilisation de formule mathématique calculant le nombre de point d'expérience
 * requis pour obtenir le niveau supérieur
 * 
 * @param entite L'entité que l'on vérifie
 */
void checkNiveau(t_entiteVivante *entite, const boolean gagne) {
    int ceuil;
    
    if (gagne) {
        ceuil = getExperienceCourbe(entite->baseStatistiques.experience_courbe)(entite->statistiques.niveau + 1);

        if (entite->statistiques.experience >= ceuil){
            entite->statistiques.niveau += 1;
            entite->statistiques = genererStatistiques(entite->baseStatistiques, entite->statistiques.niveau);
        }
    }
    else {
        ceuil = getExperienceCourbe(entite->baseStatistiques.experience_courbe)(entite->statistiques.niveau - 1);

        if (entite->statistiques.experience <= ceuil){
            entite->statistiques.niveau -= 1;
            entite->statistiques = genererStatistiques(entite->baseStatistiques, entite->statistiques.niveau);
        }
    }
}





/**
 * @brief On donne les points d'expèrience à l'entité
 * 
 * Donner une valeur d'experience négative pour retiré de l'expèrience
 * 
 * @param entite L'entité à laquelle les points d'expèrience sont donnée
 * @param experience Les points d'expèrience qu'il faut donner
 */
void donnerExperience(t_entiteVivante *entite, const int experience) {
    if (experience) {
        entite->statistiques.experience += experience;

        if (entite->statistiques.experience < 0)
            entite->statistiques.experience = 0;
        else
            checkNiveau(entite, experience > 0);
    }
}





/**
 * @brief Calcul le nombre de point d'expèrience qui sera donner/retirer
 * 
 * @param cible L'entité qui a été vaincu
 * @return Le nombre de point d'expèrience
 */
int calculExperience(t_entiteVivante *cible) {
    int exp = cible->statistiques.niveau * cible->statistiques.attaque / 7;
    return exp;
}





/* -------------------------------------------------------------------------- */
/*                             Courbes Experience                             */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param niveau 
 * @return int 
 */
int lent(const unsigned int niveau) {
    return (pow(niveau, 3) * 5); 
}



/**
 * @brief 
 * 
 * @param niveau 
 * @return int 
 */
int moyen(const unsigned int niveau) {
    return pow(niveau, 3) * 4;
}



/**
 * @brief 
 * 
 * @param niveau 
 * @return int 
 */
int rapide(const unsigned int niveau) {
    return pow(niveau, 3) * 1.5 * 2;
}





/**
 * @brief Obtient la formule correspondant à la courbe d'expérience
 * 
 * @param courbe Le type de courbe d'expèrience que suit l'entité
 * @return Un pointeur sur la fonction calculant la courbe choisit int(*)(const unsigned int) 
 */
int (*getExperienceCourbe(const e_courbeExperience courbe))(const unsigned int) {
    switch (courbe) {
        case EXPERIENCE_LENT:
            return lent;

        case EXPERIENCE_MOYEN:
            return moyen;
            
        case EXPERIENCE_RAPIDE:
            return rapide;
        
        default:
            return NULL;
    }
}



