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
    printf("Update Monstre => ");
    
    printf("Deplacement : %i => ", monstre->deplacementType);

    printf("Fin Update Monstre\n");
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
    printf("Destruction Monstre => ");
    if (monstre != NULL && *monstre != NULL) {
        // free(*monstre);
        // *monstre = NULL;

        detruireMob((t_mob**) monstre);
    }
    printf("Succes\n");
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
    t_mob *mob = creerMob(position);
    t_monstre *monstre = realloc(mob, sizeof(t_monstre));


    monstre->entiteType = ENTITE_MONSTRE_AGGRESSIF;
    genererMonstre(monstre, biome);

    monstre->update = (void (*)(t_moteur*, t_entite*)) updateMonstre;
    monstre->detruire = (void (*)(t_entite**)) detruireMonstre;


    mob = NULL;
    return monstre;
}
