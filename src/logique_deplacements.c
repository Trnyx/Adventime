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
#include <math.h>

#include "../include/utilitaire.h"
#include "../include/physique.h"
#include "../include/moteur.h"
#include "../include/mob.h"
#include "../include/deplacement.h"





/* -------------------------------------------------------------------------- */
/*                                   Logique                                  */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param mob 
 */
void finDeplacement(t_mob *mob) {
    printf("FIN DEPLACEMENT\n");
    mob->positionDeplacement = mob->position;
    mob->cooldownDeplacement = getNombreAleatoire(MOB_DELAI_MIN_ENTRE_DEPLACEMENT, MOB_DELAI_MAX_ENTRE_DEPLACEMENT);
}





static void orienterVersPosition(t_mob *mob) {
    const float angle = calculAngleEntrePoints(mob->position, mob->positionDeplacement);
    orienterEntite(angle, (t_entite*)mob);
}



static void orienterVersCible(t_mob *mob) {
    const float angle = calculAngleEntrePoints(mob->position, mob->cible->position);
    orienterEntite(angle, (t_entite*)mob);
}





/**
 * @brief 
 * 
 * @param mob 
 * @param cible 
 */
void deplacerVers(t_mob *mob, const float vitesse, const t_vecteur2 cible) {
    printf("Deplacer vers => %1.2f:%1.2f (%i : %s)\n", cible.x, cible.y, mob->tag, mob->id);
    mob->direction.x = (cible.x - mob->position.x);
    mob->direction.y = (cible.y - mob->position.y);

    deplacerEntite((t_entite*)mob, vitesse);
    orienterVersPosition(mob);
}



/**
 * @brief 
 * 
 * @param mob 
 * @param cible 
 */
void deplacerAutour(t_mob *mob, const float vitesse, const t_vecteur2 cible) {
    printf("Deplacer autour => %1.2f:%1.2f ", cible.x, cible.y);

    const e_rotation rotation = ROTATION_HORAIRE; // getNombreAleatoire(ROTATION_HORAIRE, ROTATION_ANTI_HORAIRE);
    printf("Rotation : %i \n", rotation);

    t_vecteur2 vec;
    vec.x = mob->position.x > cible.x ? mob->position.x : cible.x;
    vec.y = mob->position.y > cible.y ? mob->position.y : cible.y;

    vec.x *= 0.2;
    vec.y *= 0.2;

    // const float angle = calculAngleEntrePoints(mob->position, cible);
    // t_vecteur2 vec = {
    //     cos(angle) - sin(angle),
    //     sin(angle) + cos(angle),
    // };
    // printf("VEC : %.2f:%.2f\n", vec.x, vec.y);


    switch (rotation) {
        case ROTATION_HORAIRE: 
            mob->positionDeplacement.x += vec.x;
            mob->positionDeplacement.y += vec.y;
            break;

        case ROTATION_ANTI_HORAIRE: 
            mob->positionDeplacement.x -= vec.y;
            mob->positionDeplacement.y -= vec.x;
            break;
        
        default:
            break;
    }
    

    deplacerEntite((t_entite*)mob, vitesse);
    orienterVersCible(mob);
}



/**
 * @brief 
 * 
 * @param mob 
 * @param cible 
 */
void seloigneDe(t_mob *mob, const float vitesse, const t_vecteur2 cible) {
    printf("Deplacer vers => %1.2f:%1.2f\n", cible.x, cible.y);
    mob->direction.x = (mob->position.x - cible.x);
    mob->direction.y = (mob->position.y - cible.y);

    deplacerEntite((t_entite*)mob, vitesse);
    orienterVersPosition(mob);
}





/* -------------------------------------------------------------------------- */
/*                                 Deplacement                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param mob 
 * @return int 
 */
int deplacementNormal(t_mob *mob) {
    

    // Si le mob n'a pas atteint la position qu'il doit atteindre
    //  on le fait se déplacer en direction de son point
    // Sinon cela signifie qu'il peut se déplacer à nouveau
    if (mob->cooldownDeplacement == 0) {

        if (mob->position.x != mob->positionDeplacement.x || mob->position.y != mob->positionDeplacement.y) {
            // mob->direction.x = (mob->positionDeplacement.x - mob->position.x);
            // mob->direction.y = (mob->positionDeplacement.y - mob->position.y);

            // const float distanceRestante = calculDistanceEntrePoints(mob->position, mob->positionDeplacement);

            // printf("Direction (%1.2f:%1.2f) ", mob->direction.x, mob->direction.y);
            // printf("Position Actuelle : %1.2f:%1.2f ", mob->position.x, mob->position.y);
            // printf("Position target : %1.2f:%1.2f => ", mob->positionDeplacement.x, mob->positionDeplacement.y);

            if (mob->operation != ATTENTE) {
                deplacerVers(mob, mob->statistiques.vitesse, mob->positionDeplacement);
                // deplacerEntite((t_entite*)mob, 4.0);
            }
            else {
                // finDeplacement(mob);
                // mob->cooldownDeplacement = getNombreAleatoire(MOB_DELAI_MIN_ENTRE_DEPLACEMENT, MOB_DELAI_MAX_ENTRE_DEPLACEMENT);
            }
        }
        else {
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

            const int proba = getNombreAleatoire(1, 100);
            // printf("Deplacement Normal (%i) => ", proba);

            if (proba > PROBABILITE_MOUVEMENT_AUCUN) {
                printf("Choix nouvelle position => ");
                // mob->deplacementType = DEPLACEMENT_NORMAL;

                const t_vecteur2 pointARejoindre = choisirPointDansRayon(mob->rayonDeplacement);
                const t_vecteur2 positionFinale = {
                    mob->position.x + pointARejoindre.x,
                    mob->position.y + pointARejoindre.y,
                };

                printf("Point : %1.2f:%1.2f => ", pointARejoindre.x, pointARejoindre.y);
                
                // Si le point choisit et un point valide
                if (blockEstDansLaMap(positionFinale.x, positionFinale.y)) {
                    mob->operation = SE_DEPLACE_VERS;
                    mob->positionDeplacement.x = positionFinale.x;
                    mob->positionDeplacement.y = positionFinale.y;

                    printf("Position target : %1.2f:%1.2f\n", mob->positionDeplacement.x, mob->positionDeplacement.y);

                    mob->timerDeplacement = MOB_DUREE_DEPLACEMENT;
                }
            }
        }

    }
    


    return 0;
}





int deplacementAttaque(t_mob* mob, t_joueur *joueur, const int timestamp) {
    printf("ATTAQUE\n");
    // Lorsque le mob est en position d'attaque, il se déplace autour du joueur
    //
    // Choix d'une direction
    // Le mob se déplce dans la direction choisis pendant un temps d'attente avant d'attaquer
    // Une fois le temps d'attente terminé 
    //   Déplacement rapide en direction du joueur
    //   - Logique de combat
    //   Choix aléatoire d'une nouvelle direction et du temps d'attente avant la prochaine attaque 

    float vitesse;
    // const int sensDeDeplacement = getNombreAleatoire(1, 2);

    mob->direction.x = (joueur->position.y - mob->position.y);
    mob->direction.y = (joueur->position.x - mob->position.x);


    if (mob->cooldownAttaque == 0) {
        vitesse = 5.0;
    }
    else {
        vitesse = 2.0;
    }


    deplacerEntite((t_entite*)mob, vitesse);

    const float angle = calculAngleEntrePoints(mob->position, joueur->position);
    orienterEntite(angle, (t_entite*) mob);


    return 0;
}





/**
 * @brief 
 * 
 * @param mob 
 * @param distanceJoueur 
 * @return int 
 */
int deplacementCombat(t_mob *mob, const float distanceJoueur) {
    printf("COMBAT\n");
    // Si le joueur est dans le rayon de positionnement
    //  Le monstre se déplace en direction du joueur 
    // 
    // Lorsque le joueur entre dans le rayon attaque
    //  Le monstre attaque
    // 
    // Si le joueur est trop proche
    //  Le monstre recul


    t_joueur *joueur = moteur->cache->monde->joueur;




    float vitesse = 0.0;
    
    mob->direction.x = (joueur->position.x - mob->position.x);
    mob->direction.y = (joueur->position.y - mob->position.y);

    
    if (distanceJoueur <= MOB_RAYON_COMBAT_POSITIONNEMENT && distanceJoueur > MOB_RAYON_COMBAT_ATTAQUE) {
        vitesse = 3.0;
    }

    else if (distanceJoueur < MOB_RAYON_COMBAT_RETRAIT) {
        vitesse = -2.0 / distanceJoueur;
    }

    if (distanceJoueur <= MOB_RAYON_COMBAT_ATTAQUE && distanceJoueur > MOB_RAYON_COMBAT_RETRAIT) {
        deplacementAttaque(mob, joueur, moteur->frame);
        return 0;
    } 


    deplacerEntite((t_entite*)mob, vitesse);

    const float angle = calculAngleEntrePoints(mob->position, joueur->position);
    orienterEntite(angle, (t_entite*) mob);


    return 0;
}










/* -------------------------------------------------------------------------- */
/*                                     Get                                    */
/* -------------------------------------------------------------------------- */


int (*getDeplacement(e_deplacementType deplacement))(t_mob*, const float) {
    printf("Get Deplacement %i => ", deplacement);
    switch (deplacement) {
        case DEPLACEMENT_NORMAL:  
            return (int (*)(t_mob*, const float)) deplacementNormal;

        case DEPLACEMENT_COMBAT:  
            return (int (*)(t_mob*, const float)) deplacementCombat;

            
        case DEPLACEMENT_STATIQUE: 
        default:
            return NULL;
    }
}