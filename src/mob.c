/**
 * @file mob.c
 * 
 * @brief Module de gestion des mobs
 * 
 * @author Clément Hibon
 * @date 3 mars
 * @version 1.1
 */





#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/physique.h"
#include "../include/utilitaire.h"
#include "../include/moteur.h"
#include "../include/audio.h"
#include "../include/deplacement.h"
#include "../include/combat.h"

#include "../include/mob.h"




/* -------------------------------------------------------------------------- */
/*                                     Get                                    */
/* -------------------------------------------------------------------------- */





/* -------------------------------------------------------------------------- */
/*                                   Combat                                   */
/* -------------------------------------------------------------------------- */


/**
 * @brief Execute l'attaque d'un mob
 * 
 * @param mob Le mob qui attaque
 * @param distanceFinale La séparant la cible du mob et celui-ci
 */
void attaquer(t_mob *mob, const float distanceFinale) {
    deplacerVers(mob, mob->statistiques.vitesse * MOB_VITESSE_MODIFICATEUR_ATTAQUE, mob->positionDeplacement);
    
    if (distanceFinale < 1.0) {
        metUnCoup((t_entiteVivante*)mob, mob->cible, calculAngleEntrePoints(mob->position, mob->positionDeplacement), 1.4);

        mob->cooldownAttaque = getNombreAleatoire(MOB_DELAI_MIN_ENTRE_ATTAQUE, MOB_DELAI_MAX_ENTRE_ATTAQUE);
        mob->operation = ATTENTE;
    }
}





/**
 * @brief Gère la logique de combat d'un mob
 * 
 * @param mob Un pointeur sur le mob qui combat
 * @param distance La distance entre le mob et sa cible
 */
void combatMob(t_mob *mob, float distance) {
    if (mob->operation == ATTAQUE) {
        distance = calculDistanceEntrePoints(mob->position, mob->positionDeplacement);
        attaquer(mob, distance);
    }

    else {
        // Si la cible est trop loin
        if (distance > BOSS_RAYON_COMBAT_POSITIONNEMENT) {
            finCombat(mob);       
        }

        // Sinon Si la cible est dans le rayon de positionnement
        else if (distance <= MOB_RAYON_COMBAT_POSITIONNEMENT && distance > MOB_RAYON_COMBAT_ATTAQUE) {
            mob->operation = SE_DEPLACE_VERS;
        }

        // Sinon Si la cible est dans le rayon d'attaque
        else if (distance <= MOB_RAYON_COMBAT_ATTAQUE && distance > MOB_RAYON_COMBAT_RETRAIT) {
            if (mob->cooldownAttaque == 0) {
                mob->operation = ATTAQUE;
                mob->animation->frameCourante = 1;
            }
            else {
                --(mob->cooldownAttaque);
                mob->operation = SE_DEPLACE_AUTOUR;
            }
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
 * @brief Actualise un mob
 * 
 * Toute la logique propre aux mobs est gérer dans cette fonction
 * 
 * @param mob Un pointeur sur le mob qui doit être actualisé
 * @param distance La distance entre le mob est le joueur
 */
void updateMob(t_mob* mob, float distance) {
    regenerationEntite((t_entiteVivante*)mob);


    /* -------------------------------- Bruitage -------------------------------- */

    if (mob->cooldownBruitage > 0) {
        --(mob->cooldownBruitage);
    }
    else {
        const float angle = calculAngleEntrePoints(moteur->cache->monde->joueur->position, mob->position);
        play_sonAmbiance(mob->bruitages->normal, angle, distance);
        mob->cooldownBruitage = getNombreAleatoire(MOB_DELAI_MIN_ENTRE_BRUIT, MOB_DELAI_MAX_ENTRE_BRUIT);
    }



    /* --------------------------------- Combat --------------------------------- */

    if (mob->deplacementType == DEPLACEMENT_COMBAT) {        
        distance = calculDistanceEntreEntites((t_entite*)mob, (t_entite*)mob->cible);
        combatMob(mob, distance);
    } 



    /* ------------------------------- Déplacement ------------------------------ */

    // Deplacement autour de la cible
    if (mob->operation == SE_DEPLACE_AUTOUR) {
        deplacerAutour(mob, mob->statistiques.vitesse * MOB_VITESSE_MODIFICATEUR_AUTOUR, mob->cible->position);
    }

    // Deplacement vers la cible
    else if (mob->operation == SE_DEPLACE_VERS) {
        deplacerVers(mob, mob->statistiques.vitesse, mob->positionDeplacement);
        mob->operation = ATTENTE;
    }

    // Deplacement s'éloigne de la cible
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

            if (distanceRestante > 0.1) {
                deplacerVers(mob, mob->statistiques.vitesse, mob->positionDeplacement);
                --(mob->timerDeplacement);
            }
            else {
                finDeplacement(mob);
            }


            if (mob->timerDeplacement == 0) {
                finDeplacement(mob);
            }
        }

        else {
            if (mob->cooldownDeplacement) {
                --(mob->cooldownDeplacement);
                // printf("%i\n",mob->cooldownDeplacement);
            }
            else {
                const int probabilite = getNombreAleatoire(1, 100);


                if (probabilite <= PROBABILITE_MOUVEMENT_AUCUN) {
                    mob->cooldownDeplacement = getNombreAleatoire(MOB_DELAI_MIN_ENTRE_DEPLACEMENT, MOB_DELAI_MAX_ENTRE_DEPLACEMENT);
                }

                else if (probabilite <= PROBABILITE_MOUVEMENT_ROTATION) {
                    const float angle = getNombreAleatoire(0, 360);
                    orienterEntite(angle, (t_entite*)mob);

                    mob->cooldownDeplacement = getNombreAleatoire(MOB_DELAI_MIN_ENTRE_DEPLACEMENT, MOB_DELAI_MAX_ENTRE_DEPLACEMENT);
                }

                else if (probabilite <= PROBABILITE_MOUVEMENT_DEPLACEMENT) {
                    const t_vecteur2 pointARejoindre = choisirPointDansRayon(mob->rayonDeplacement);
                    const t_vecteur2 positionFinale = {
                        mob->position.x + pointARejoindre.x,
                        mob->position.y + pointARejoindre.y,
                    };

                    
                    // Si le point choisit et un point valide
                    if (blockEstDansLaMap(positionFinale.x, positionFinale.y)) {
                        mob->operation = SE_DEPLACE_VERS;
                        mob->positionDeplacement.x = positionFinale.x;
                        mob->positionDeplacement.y = positionFinale.y;

                        mob->timerDeplacement = MOB_DUREE_DEPLACEMENT;
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
 * @brief Detruit un mob est libère la mémoire allouée pour ce dernier
 * 
 * @param mob L'adresse du pointeur du mob à détruire
 */
void detruireMob(t_mob **mob) {
    if (mob != NULL && *mob != NULL) {

        if ((*mob)->aggressif)
            --(moteur->cache->compteurEntites.mobAggressifs);
        else
            --(moteur->cache->compteurEntites.mobPassifs);

        --(moteur->cache->compteurEntites.mobs);


        detruireEntite((t_entite**)mob);

    }
}





/* -------------------------------------------------------------------------- */
/*                                  Création                                  */
/* -------------------------------------------------------------------------- */



/**
 * @brief Alloue l'espace nécessaire pour un mob et le créer
 * 
 * @param position La position à laquelle le mob doit apparaitre
 * 
 * @return Un pointeur sur le mob, NULL en cas d'echec
 */
t_mob* creerMob(const t_vecteur2 position) {
    t_entite *entite = creerEntite(position);
    t_mob *mob = realloc(entite, sizeof(t_mob));


    if (mob == NULL) {
        printf("Erreur mémoire : Impossible d'allouer la place nécessaire pour creer un mob\n");
        detruireEntite(&entite);
        return NULL;
    }
    

    mob->orientation = getNombreAleatoire(SUD, NORD);
    

    mob->entiteType = ENTITE_MOB;
    mob->aggressif = FAUX;

    mob->cible = NULL;

    // Déplacement
    mob->rayonDeplacement = 0;

    mob->positionDeplacement.x = position.x;
    mob->positionDeplacement.y = position.y;
    mob->timerDeplacement = 0;
    mob->cooldownDeplacement = getNombreAleatoire(MOB_DELAI_MIN_ENTRE_DEPLACEMENT, MOB_DELAI_MAX_ENTRE_DEPLACEMENT);

    mob->deplacementType = DEPLACEMENT_STATIQUE;
    mob->operation = ATTENTE;

    mob->gamma = 0.0;
    mob->rotation = ROTATION_HORAIRE;


    // cooldown
    mob->cooldownAttaque = getNombreAleatoire(MOB_DELAI_MIN_ENTRE_ATTAQUE, MOB_DELAI_MAX_ENTRE_ATTAQUE);
    mob->cooldownBruitage = getNombreAleatoire(MOB_DELAI_MIN_ENTRE_BRUIT, MOB_DELAI_MAX_ENTRE_BRUIT);
    mob->cooldownRegeneration = 0;


    mob->detruire = (void (*)(t_entite**)) detruireMob;

    mob->destructionInactif = FAUX;
    mob->destructionDelai = FAUX;


    ++(moteur->cache->compteurEntites.mobs);
    entite = NULL;
    return mob;
}