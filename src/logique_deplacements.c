/**
 * @file logique_deplacements.c
 * 
 * @brief 
 * 
 * @author Clément Hibon
 * @date 10 février
 * @version 1.1
 */





#include <stdlib.h>
#include <stdio.h>

#include "../include/utilitaire.h"
#include "../include/physique.h"
#include "../include/moteur.h"
#include "../include/entite.h"






t_vecteur2 choisirPointDeDeplacement(const int rayon) {
    t_vecteur2 point = {
        getNombreAleatoire(-rayon, rayon),
        getNombreAleatoire(-rayon, rayon),
    };


    return point;
}




int deplacementNormal(t_moteur *moteur, t_mob *mob) {
    // Génère un nombre aléatoire représentant la probabilité de déplacement
    // Si l'entité se déplace
    //  Génère une position aléatoire dans un rayon
    //  Si la position est valide et attaignable
    //      L'entité se déplace
    //  Sinon
    //      Dans le cas où le déplacement est potentiel
    //          On ne fait rien
    //      Dans le cas où le déplacement est obligatoire
    //          On cherche une nouvelle position



    // Si le mob n'a pas atteint la position qu'il doit atteindre
    //  on le fait se déplacer en direction de son point
    // Sinon cela signifie qu'il peut se déplacer à nouveau
    if (difftime(mob->timestampActualisation, mob->timestampFinDeplacement) > mob->delaiAttente) {
        if (mob->position.x != mob->positionDeplacement.x || mob->position.y != mob->positionDeplacement.y) {
            mob->orientation.x = (mob->positionDeplacement.x - mob->position.x);
            mob->orientation.y = (mob->positionDeplacement.y - mob->position.y);

            const float distanceRestante = calculDistanceEntrePoints(mob->position, mob->positionDeplacement);

            printf("Orientation (%1.2f:%1.2f) ", mob->orientation.x, mob->orientation.y);
            printf("Position Actuelle : %1.2f:%1.2f ", mob->position.x, mob->position.y);
            printf("Position target : %1.2f:%1.2f => ", mob->positionDeplacement.x, mob->positionDeplacement.y);

            if (difftime(mob->timestampActualisation, mob->timestampDebutDeplacement) <= MOB_DUREE_DEPLACEMENT && distanceRestante > 0.1) {
                deplacerEntite(moteur, (t_entite*)mob, 4.0);
            }
            else {
                mob->positionDeplacement = mob->position;
                mob->timestampFinDeplacement = mob->timestampActualisation;
                mob->delaiAttente = getNombreAleatoire(MOB_DELAI_MIN_ENTRE_DEPLACEMENT, MOB_DELAI_MAX_ENTRE_DEPLACEMENT);
            }
        }
        else {
            const int proba = getNombreAleatoire(1, 100);
            printf("Deplacement Normal (%i) => ", proba);

            if (proba > PROBABILITE_DEPLACEMENT_AUCUN) {
                printf("Choix nouvelle position => ");
                mob->deplacementType = DEPLACEMENT_NORMAL;

                t_vecteur2 pointARejoindre = choisirPointDeDeplacement(mob->rayonDeplacement);
                t_vecteur2 positionFinale = {
                    mob->position.x + pointARejoindre.x,
                    mob->position.y + pointARejoindre.y,
                };

                printf("Point : %1.2f:%1.2f => ", pointARejoindre.x, pointARejoindre.y);
                
                // Si le point choisit et un point valide
                if (blockEstDansLaMap(positionFinale.x, positionFinale.y)) {
                    mob->positionDeplacement.x = positionFinale.x;
                    mob->positionDeplacement.y = positionFinale.y;

                    printf("Position target : %1.2f:%1.2f => ", mob->positionDeplacement.x, mob->positionDeplacement.y);

                    mob->timestampDebutDeplacement = mob->timestampActualisation;
                }
                else {
                    if (proba <= PROBABILITE_DEPLACEMENT_OBLIGATOIRE) {
                        
                    }
                }
            }
        }
    }
    


    return 0;
}





int deplacementCombat(t_moteur *moteur, t_mob *mob, const float distanceJoueur) {
    // Si le joueur est dans le rayon de positionnement
    //  Le monstre se déplace en direction du joueur 
    // 
    // Lorsque le joueur entre dans le rayon attaque
    //  Le monstre attaque
    // 
    // Si le joueur est trop proche
    //  Le monstre recul



    t_joueur *joueur = moteur->monde->joueur;

    const float distance = calculDistanceEntreEntites((t_entite*)mob, (t_entite*)joueur);

    
    if (distance <= ENTITE_RAYON_COMBAT_POSITIONNEMENT && distance > ENTITE_RAYON_COMBAT_ATTAQUE) {

    }


    else if (distance <= ENTITE_RAYON_COMBAT_ATTAQUE && distance > ENTITE_RAYON_COMBAT_RETRAIT) {

    } 
    
    
    else if (distance < ENTITE_RAYON_COMBAT_RETRAIT) {

    }


    return 0;
}










int (*getDeplacement(e_deplacementType deplacement))(t_moteur*, t_mob*, const float) {
    printf("Get Deplacement %i => ", deplacement);
    switch (deplacement) {
        case DEPLACEMENT_NORMAL:  
            return (int (*)(t_moteur*, t_mob*, const float)) deplacementNormal;

        case DEPLACEMENT_COMBAT:  
            return (int (*)(t_moteur*, t_mob*, const float)) deplacementNormal;//deplacementCombat;

            
        case DEPLACEMENT_STATIQUE: 
        default:
            return NULL;
    }
}