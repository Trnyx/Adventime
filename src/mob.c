/**
 * @file mob.c
 * 
 * @brief 
 * 
 * @author Clément Hibon
 * @date 3 mars
 * @version 1.1
 */




#include <stdlib.h>
#include <stdio.h>

#include "../include/mob.h"




/**
 * @file entite.c
 * 
 * @brief 
 * 
 * @author Clément Hibon
 * @date 3 février
 * @version 1.1
 */




#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/physique.h"
#include "../include/utilitaire.h"
#include "../include/moteur.h"
#include "../include/mob.h"
#include "../include/deplacement.h"
#include "../include/combat.h"





void attaquer(t_mob *mob, const float distanceFinale) {
    deplacerVers(mob, mob->statistiques.vitesse * MOB_VITESSE_MODIFICATEUR_ATTAQUE, mob->positionDeplacement);
    
    if (distanceFinale < 1.0) {
        printf("COMBAT => ");
        metUnCoup((t_entiteVivante*)mob, mob->cible, calculAngleEntrePoints(mob->position, mob->positionDeplacement));

        mob->timestampAttaque = moteur->frame;
        mob->delaiAttenteAttaque = getNombreAleatoire(2, 5);
        mob->operation = ATTENTE;
    }
}





void combatMob(t_mob *mob, float distance) {
    if (mob->operation == ATTAQUE) {
        distance = calculDistanceEntrePoints(mob->position, mob->positionDeplacement);
        attaquer(mob, distance);
    }

    else {
        // Si la cible est trop loin
        if (distance > MOB_RAYON_COMBAT_POSITIONNEMENT) {
            mob->deplacementType = DEPLACEMENT_NORMAL;
        }

        // Sinon Si la cible est dans le rayon de positionnement
        else if (distance <= MOB_RAYON_COMBAT_POSITIONNEMENT && distance > MOB_RAYON_COMBAT_ATTAQUE) {
            mob->operation = SE_DEPLACE_VERS;
        }

        // Sinon Si la cible est dans le rayon d'attaque
        else if (distance <= MOB_RAYON_COMBAT_ATTAQUE && distance > MOB_RAYON_COMBAT_RETRAIT) {
            if (mob->timestampActualisation - mob->timestampAttaque > mob->delaiAttenteAttaque * 1000) {
                mob->operation = ATTAQUE;
            }
            else
                mob->operation = SE_DEPLACE_AUTOUR;
        }

        // Sinon Si la cible est trop proche 
        else {
            mob->operation = S_ELOIGNE_DE;
        }
    }
}


/* -------------------------------------------------------------------------- */
/*                                   Update                                   */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param mob 
 * @param distance 
 */
void updateMob(t_mob* mob, const float distance) {
    if (mob->deplacementType == DEPLACEMENT_COMBAT) {
        combatMob(mob, distance);
    } 



    if (mob->operation == SE_DEPLACE_AUTOUR) {
        // Deplacement autour de la cible
        deplacerAutour(mob, mob->statistiques.vitesse * MOB_VITESSE_MODIFICATEUR_AUTOUR, mob->positionDeplacement);
    }

    else if (mob->operation == SE_DEPLACE_VERS) {
        // Deplacement vers la cible
        deplacerVers(mob, mob->statistiques.vitesse, mob->positionDeplacement);
        mob->operation = ATTENTE;
    }

    else if (mob->operation == S_ELOIGNE_DE) {
        seloigneDe(mob, mob->statistiques.vitesse * MOB_VITESSE_MODIFICATEUR_ELOIGNEMENT, mob->positionDeplacement);
        mob->operation = ATTENTE;
    }
    
    else if (mob->operation != ATTAQUE) {
        // On check si le mob est à sa position cible
        // Si il ne l'est pas
        //     Si le temps de déplacement maximum est dépassé
        //         On met fin au déplacement
        //     Sinon
        //         On déplace l'entité vers sa position cible

        // Sinon
        //     On vérifie que le temps d'attente est dépassé
        //     Si le temps d'attente est dépassé
        //         On calcul la probabilité qu'il bouge
        //         Si le mouvement est un déplacement
        //             On choisis une nouvelle position
        //             Si la position est valide
        //                 On set l'opération en SE_DEPLACE_VERS
        //                 On set la position cible du mob avec la nouvlle position
        //         Sinon si le mouvement est une rotation
        //             On choisis une nouvelle orientation
        //             On oriente l'entité
        //         Sinon 
        //             On set le temps d'attente


        if (mob->position.x != mob->positionDeplacement.x || mob->position.y != mob->positionDeplacement.y) {
            const float distanceRestante = calculDistanceEntrePoints(mob->position, mob->positionDeplacement);

            // if ((mob->timestampActualisation - mob->timestampDebutDeplacement <= (MOB_DUREE_DEPLACEMENT * 1000)) && distanceRestante > 0.1) {
            if ((mob->timestampActualisation - mob->timestampDebutDeplacement > (MOB_DUREE_DEPLACEMENT * 1000)) || distanceRestante <= 0.1) {
                finDeplacement(mob);
            }
            else {
                deplacerVers(mob, mob->statistiques.vitesse, mob->positionDeplacement);
            }
        }

        else {
            if (mob->timestampActualisation - mob->timestampFinDeplacement > mob->delaiAttenteDeplacement * 1000) {
                const int probabilite = getNombreAleatoire(1, 100);


                if (probabilite <= PROBABILITE_MOUVEMENT_AUCUN) {
                    mob->delaiAttenteDeplacement = getNombreAleatoire(MOB_DELAI_MIN_ENTRE_DEPLACEMENT, MOB_DELAI_MAX_ENTRE_DEPLACEMENT);
                }

                else if (probabilite <= PROBABILITE_MOUVEMENT_ROTATION) {
                    printf("Choix nouvelle orientation => ");

                    const float angle = getNombreAleatoire(0, 360);
                    orienterEntite(angle, (t_entite*)mob);

                    mob->delaiAttenteDeplacement = getNombreAleatoire(MOB_DELAI_MIN_ENTRE_DEPLACEMENT, MOB_DELAI_MAX_ENTRE_DEPLACEMENT);
                }

                else if (probabilite <= PROBABILITE_MOUVEMENT_DEPLACEMENT) {
                    printf("Choix nouvelle position => ");

                    const t_vecteur2 pointARejoindre = choisirPointDansRayon(mob->rayonDeplacement);
                    const t_vecteur2 positionFinale = {
                        mob->position.x + pointARejoindre.x,
                        mob->position.y + pointARejoindre.y,
                    };

                    // printf("Point : %1.2f:%1.2f => ", pointARejoindre.x, pointARejoindre.y);
                    
                    // Si le point choisit et un point valide
                    if (blockEstDansLaMap(positionFinale.x, positionFinale.y)) {
                        mob->operation = SE_DEPLACE_VERS;
                        mob->positionDeplacement.x = positionFinale.x;
                        mob->positionDeplacement.y = positionFinale.y;

                        printf("Position target : %1.2f:%1.2f\n", mob->positionDeplacement.x, mob->positionDeplacement.y);
                        mob->timestampDebutDeplacement = mob->timestampActualisation;
                    }
                }
            }
        }

    }
}





/* -------------------------------------------------------------------------- */
/*                                 Destruction                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param mob 
 */
void detruireMob(t_mob **mob) {
    printf("Destruction Mob => ");
    if (mob != NULL && *mob != NULL) {

        detruireEntite((t_entite**)mob);

    }
}





/* -------------------------------------------------------------------------- */
/*                                  Création                                  */
/* -------------------------------------------------------------------------- */



/**
 * @brief 
 * 
 * @param position 
 * @return t_mob* 
 */
t_mob* creerMob(const t_vecteur2 position) {
    t_entite *entite = creerEntite(position);
    t_mob *mob = realloc(entite, sizeof(t_mob));
    const int t = SDL_GetTicks();


    mob->entiteType = ENTITE_MOB;
    mob->aggressif = FAUX;

    mob->cible = NULL;

    // Déplacement
    mob->rayonDeplacement = 0;

    mob->positionDeplacement.x = position.x;
    mob->positionDeplacement.y = position.y;
    mob->timestampDebutDeplacement = t;
    mob->timestampFinDeplacement = t;
    mob->delaiAttenteDeplacement = 10;

    mob->deplacementType = DEPLACEMENT_STATIQUE;
    mob->operation = ATTENTE;


    // Attaque
    mob->timestampAttaque = t;
    mob->delaiAttenteAttaque = 0;


    mob->detruire = (void (*)(t_entite**)) detruireMob;

    mob->destructionInactif = FAUX;


    entite = NULL;
    return mob;
}