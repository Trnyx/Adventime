/**
 * @file monstre.c
 *
 * @brief Génération d'un monstre
 *
 * @author Clément Hibon
 * @date 23 janvier
 * @version 1.1
 */





#include <stdlib.h>
#include <stdio.h>

#include "../include/physique.h"
#include "../include/monstre.h"





int updateMonstre(t_moteur *moteur, t_monstre *monstre) {
    time_t timestampFrame = time(NULL);
    monstre->timestampActualisation = timestampFrame;


    if (difftime(monstre->timestampActualisation, monstre->timestampCreation) >= ENTITE_DUREE_VIE_MAX) {
        return -1;
    }


    return 1;
}



// Deplacement
// Deplacement

// Deplacement 





/* -------------------------------------------------------------------------- */
/*                                 Destruction                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param monstre 
 * @return int 
 */
void detruireMonstre(t_monstre **monstre) {
    if (monstre != NULL && *monstre != NULL) {
        // free(*monstre);
        // *monstre = NULL;

        detruireEntite((t_entite**) monstre);
    }

    return 0;
}





/* -------------------------------------------------------------------------- */
/*                                  Création                                  */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param position 
 * @param biome 
 * @return t_monstre* 
 */
t_monstre* creerMonstre(const t_vecteur2 position, const e_biome biome) {
    t_entite *entite = creerEntite(position);
    t_monstre *monstre = realloc(entite, sizeof(t_monstre));


    monstre->entiteType = ENTITE_MONSTRE_AGGRESSIF;
    genererMonstre(monstre, biome);

    monstre->update = (void (*)(t_moteur*, t_entite*)) updateMonstre;
    monstre->detruire = (void (*)(t_entite**)) detruireMonstre;


    entite = NULL;
    return monstre;
}
