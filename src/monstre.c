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





int updateMonstre(t_monstre *monstre, float distance, t_entiteVivante *cible) {
    // printf("Update Monstre => ");

    // Si le joueur est dans le rayon de détection du monstre
    if (monstre->deplacementType != DEPLACEMENT_COMBAT && distance <= MONSTRE_RAYON_COMBAT_DETECTION) {
        monstre->deplacementType = DEPLACEMENT_COMBAT;
        monstre->cible = cible;
    }
    else if (monstre->deplacementType == DEPLACEMENT_COMBAT && distance > MOB_RAYON_COMBAT_POSITIONNEMENT) {
        monstre->deplacementType = DEPLACEMENT_NORMAL;
        monstre->cible = NULL;
        monstre->operation = ATTENTE;
    }
    

    if (monstre->deplacementType == DEPLACEMENT_COMBAT)
        distance = calculDistanceEntreEntites((t_entite*)monstre, (t_entite*)monstre->cible);

    
    updateMob((t_mob*)monstre, distance);


    // // printf("Deplacement : %i => ", monstre->deplacementType);
    // int (*deplacement)(t_mob*, const float) = getDeplacement(monstre->deplacementType);
    // // printf("Fonction : %p => ", deplacement);
    // if (deplacement != NULL) deplacement((t_mob*)monstre, distance);


    // // Si le monstre n'a pas atteint la position qu'il doit atteindre
    // //  on le fait se déplacer en direction de son point
    // // Sinon cela signifie qu'il peut se déplacer à nouveau
    // if (difftime(monstre->timestampActualisation, monstre->timestampFinDeplacement) > monstre->delaiAttenteDeplacement) {
    //     if (monstre->position.x != monstre->positionDeplacement.x || monstre->position.y != monstre->positionDeplacement.y) {
    //         monstre->direction.x = (monstre->positionDeplacement.x - monstre->position.x);
    //         monstre->direction.y = (monstre->positionDeplacement.y - monstre->position.y);

    //         const float distanceRestante = calculDistanceEntrePoints(monstre->position, monstre->positionDeplacement);

    //         printf("Orientation (%1.2f:%1.2f) ", monstre->direction.x, monstre->direction.y);
    //         printf("Position Actuelle : %1.2f:%1.2f ", monstre->position.x, monstre->position.y);
    //         printf("Position target : %1.2f:%1.2f => ", monstre->positionDeplacement.x, monstre->positionDeplacement.y);

    //         if (difftime(monstre->timestampActualisation, monstre->timestampDebutDeplacement) <= MOB_DUREE_DEPLACEMENT && distanceRestante > 0.1) {
    //             deplacerEntite(moteur, (t_entite*)monstre, 4.0);
    //         }
    //         else {
    //             monstre->positionDeplacement = monstre->position;
    //             monstre->timestampFinDeplacement = monstre->timestampActualisation;
    //             monstre->delaiAttenteDeplacement = getNombreAleatoire(MOB_DELAI_MIN_ENTRE_DEPLACEMENT, MOB_DELAI_MAX_ENTRE_DEPLACEMENT);
    //         }
    //     }
    //     else {
    //         printf("Choix nouvelle position => ");

    //         getDeplacement(monstre->deplacementType)(moteur, (t_mob*)monstre, distance);
    //         monstre->timestampDebutDeplacement = monstre->timestampActualisation;
    //     }
    // }



    // printf("Fin Update Monstre\n");
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
t_monstre* creerMonstre(const t_vecteur2 position, const e_biome biome, const int niveauJoueur) {
    t_mob *mob = creerMob(position);
    t_monstre *monstre = realloc(mob, sizeof(t_monstre));


    // Statistiques
    monstre->aggressif = VRAI;
    genererMonstre(monstre, biome, niveauJoueur);

    // 
    monstre->rayonDetection = 0;
    monstre->rayonDeplacement = 4;
    monstre->deplacementType = DEPLACEMENT_NORMAL;

    // Animation
    monstre->animation = creerAnimation(100, 4);

    // Fonctions
    monstre->update = (int (*)(t_entite*, float, t_entite*)) updateMonstre;
    monstre->detruire = (void (*)(t_entite**)) detruireMonstre;

    // Timer
    monstre->destructionInactif = monstre->aggressif;

    mob = NULL;
    return monstre;
}





/* -------------------------------------------------------------------------- */
/*                                 Apparition                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param entites 
 * @param biome 
 * @param positionJoueur 
 * @param niveauJoueur 
 */
void apparitionMonstre(t_liste *entites, t_map *map, const t_vecteur2 positionJoueur, const int niveauJoueur) {
    const float rayon = JOUEUR_RAYON_INACTIF - JOUEUR_RAYON_SEMIACTIF;
    t_vecteur2 position = choisirPointDansRayon(rayon);


    // Rapport du point généré à la position du joueur dans le disque semiactif
    if (position.x >= 0) 
        position.x = (position.x + JOUEUR_RAYON_ACTIF) + positionJoueur.x; 
    else if (position.x < 0) 
        position.x = (position.x - JOUEUR_RAYON_ACTIF) + positionJoueur.x; 

    if (position.y >= 0) 
        position.y = (position.y + JOUEUR_RAYON_ACTIF) + positionJoueur.y; 
    else if (position.y < 0) 
        position.y = (position.y - JOUEUR_RAYON_ACTIF) + positionJoueur.y; 
    // t_vecteur2 position = choisirPointDansRayon(JOUEUR_RAYON_SEMIACTIF);


    // // Rapport du point généré à la position du joueur dans le disque semiactif
    // position.x += positionJoueur.x;
    // position.y += positionJoueur.y;


    t_chunk *chunk = getChunkGraceABlock(position.x, position.y, COUCHE_OBJETS, map);

    if (chunk != NULL) {
        // printf("Chunk => ");
        const e_biome biome = chunk->biome;
        if (biome != BIOME_PROFONDEUR){
            t_block *block = getBlockDansMap(position.x, position.y, COUCHE_OBJETS, map);

            if (block != NULL) {
                // printf("Block => ");
                if (block->tag == VIDE) {
                    // printf("%i => ", block->tag);
                    t_monstre *monstre = creerMonstre(position, biome, niveauJoueur);

                    en_queue(entites);
                    ajout_droit(entites, (t_entite*)monstre);
                }
            }
        }
    }
}