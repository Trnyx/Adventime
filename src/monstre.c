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





int updateMonstre(t_moteur *moteur, t_monstre *monstre, const float distance) {
    printf("Update Monstre => ");
    
    printf("Deplacement : %i => ", monstre->deplacementType);


    getDeplacement(monstre->deplacementType)(moteur, (t_mob*)monstre, distance);


    // // Si le monstre n'a pas atteint la position qu'il doit atteindre
    // //  on le fait se déplacer en direction de son point
    // // Sinon cela signifie qu'il peut se déplacer à nouveau
    // if (difftime(monstre->timestampActualisation, monstre->timestampFinDeplacement) > monstre->delaiAttente) {
    //     if (monstre->position.x != monstre->positionDeplacement.x || monstre->position.y != monstre->positionDeplacement.y) {
    //         monstre->orientation.x = (monstre->positionDeplacement.x - monstre->position.x);
    //         monstre->orientation.y = (monstre->positionDeplacement.y - monstre->position.y);

    //         const float distanceRestante = calculDistanceEntrePoints(monstre->position, monstre->positionDeplacement);

    //         printf("Orientation (%1.2f:%1.2f) ", monstre->orientation.x, monstre->orientation.y);
    //         printf("Position Actuelle : %1.2f:%1.2f ", monstre->position.x, monstre->position.y);
    //         printf("Position target : %1.2f:%1.2f => ", monstre->positionDeplacement.x, monstre->positionDeplacement.y);

    //         if (difftime(monstre->timestampActualisation, monstre->timestampDebutDeplacement) <= MOB_DUREE_DEPLACEMENT && distanceRestante > 0.1) {
    //             deplacerEntite(moteur, (t_entite*)monstre, 4.0);
    //         }
    //         else {
    //             monstre->positionDeplacement = monstre->position;
    //             monstre->timestampFinDeplacement = monstre->timestampActualisation;
    //             monstre->delaiAttente = getNombreAleatoire(MOB_DELAI_MIN_ENTRE_DEPLACEMENT, MOB_DELAI_MAX_ENTRE_DEPLACEMENT);
    //         }
    //     }
    //     else {
    //         printf("Choix nouvelle position => ");

    //         getDeplacement(monstre->deplacementType)(moteur, (t_mob*)monstre, distance);
    //         monstre->timestampDebutDeplacement = monstre->timestampActualisation;
    //     }
    // }



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

    monstre->rayonDetection = 0;
    monstre->rayonDeplacement = 4;

    monstre->update = (int (*)(t_moteur*, t_entite*, const float)) updateMonstre;
    monstre->detruire = (void (*)(t_entite**)) detruireMonstre;


    mob = NULL;
    return monstre;
}
