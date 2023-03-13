/**
 * @file logique_physique.c
 * 
 * @brief 
 * 
 * @author Clément Hibon
 * @date 10 février
 * @version 1.1
 */



#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "../include/physique.h"
#include "../include/utilitaire.h"
#include "../include/moteur.h"
#include "../include/audio.h"
#include "../include/mob.h"





/* -------------------------------------------------------------------------- */
/*                                    Algo                                    */
/* -------------------------------------------------------------------------- */

/* --------------------------------- Joueur --------------------------------- */

// 


/* --------------------------------- Entités -------------------------------- */

// Entitées Actuelles 
//  Pour chacune des entités, on calcul la distance entre celle ci et le joueur
//  Si l'entité se situe dans le rayon au dela du rayon inactif
//      Si monstre aggressif
//          Suppression du monstre
//      Sinon
//          Ignore l'entité
//  Si l'entité se situe dans le rayon actif
//      Gestion de la logique 
//          - déplacement
//          - joueur détection
//          - combat
//  Sinon Si l'entité se situe dans le rayon semi actif 
//      Gestion de la durée de vie 
//  Pour toutes les entités non ignorées, ajout du temps
//  
//  
//
// Spawn
//  Si mob cap non atteint
//      Si le nombre de monstres aggressifs max n'est pas atteint
//          Calcul la probabilité d'apparition d'un monstre
//          Si apparition possible
//              Apparition du monste dans le rayon semi actif
//      Si le nombre de monstres passif max n'est pas atteint
//          Calcul la probabilité d'apparition d'un monstre
//          Si apparition possible
//              Apparition du monste dans le rayon semi actif
//      Si le nombre d'animaux max n'est pas atteint
//          Calcul la probabilité d'apparition d'un animal
//          Si apparition possible
//              Apparition de l'animal dans le rayon actif ou semi actif





static void suppressionEntite(t_liste *entites, t_entite *entite) {
    oter_elt(entites);
    entite->detruire((t_entite**) &entite);
    suivant(entites);
}





/* -------------------------------------------------------------------------- */
/*                                   Update                                   */
/* -------------------------------------------------------------------------- */


/**
 * @brief Fonction appelé à chaque frame du jeu
 * 
 * Elle gère toute la physique et logique du jeu
 */
void update(t_map *map, t_joueur *joueur) {
    // regulerFPS();
    // // printf("Update (%li)\n", u++);
    // t_monde *monde = moteur->monde;
    // t_joueur *joueur = monde->joueur;


    // t_map *map = NULL;
    // switch (joueur->map) {
    //     case MAP_OVERWORLD: map = monde->map; break;
    //     case MAP_CAVE: map = monde->map; break;
    // }


    t_liste *entites = moteur->cache->entites;
    t_entite *entite = NULL;

    unsigned int nombreEntites = 0;
    unsigned int nombreMobs = 0;
    unsigned int nombreAnimaux = 0;
    unsigned int nombreMobsCombat = 0;
    unsigned int nombreMobsAggressifs = 0;
    unsigned int nombreMobsPassifs = 0;


    // printf("TIME => ");

    unsigned int timestampFrame = SDL_GetTicks();
    t_temps *temps = moteur->temps;
    // printf("%i : %i\n", temps->heures, temps->minutes);

    gestionnaireTempsEvenements(temps, time(NULL));


    e_musiques_type musiqueType;



    /* -------------------------------------------------------------------------- */
    /*                                Affichage Sol                               */
    /* -------------------------------------------------------------------------- */


    dessinerSol(map);



    /* -------------------------------------------------------------------------- */
    /*                                   Joueur                                   */
    /* -------------------------------------------------------------------------- */

    joueur->update((t_entite*) joueur, 0.0, NULL);
    dessinerEntite((t_entite*) joueur);

    



    /* -------------------------------------------------------------------------- */
    /*                                   Entites                                  */
    /* -------------------------------------------------------------------------- */


    /* ---------------- Entites actuellement présente dans la map --------------- */

    en_tete(entites);
    if (!liste_vide(entites)) {
        // printf("Update Entites => ");

        while (!hors_liste(entites)) {
            valeur_elt(entites, &entite);


            if (entite != NULL) {
                // La distance séparant l'entité actuelle et le joueur
                const float distance = calculDistanceEntreEntites(entite, (t_entite*)joueur);
                // printf("distance : %1.2f ", distance);


                // Lorsque l'entité se trouve au delà des deux disques précédents
                // L'entité est concidéré dans un disque inactif
                if (distance > JOUEUR_RAYON_SEMIACTIF) {
                    // printf("(Inactif) => ");
                    // Si l'entité doit être supprimé
                    // Alors on la détruit
                    if (entite->destructionInactif) {
                        suppressionEntite(entites, entite);
                        continue;
                    }
                }


                
                // Actualisation des temps d'actualisation
                entite->timestampActualisation = timestampFrame;


                // Lorsque l'entité se trouve dans le disque semi actif par rapport au joueur
                if (distance > JOUEUR_RAYON_ACTIF && distance <= JOUEUR_RAYON_SEMIACTIF) {
                    // printf("(Semi Actif) => ");

                    // Gestion de la durée de vie de l'entité
                    // Si l'entité à atteint la durée de vie maximale d'une entité alors elle est supprimé
                    if (entite->destructionInactif) {
                        if (entite->timestampActualisation - entite->timestampCreation >= (ENTITE_DUREE_VIE_MAX * 1000)) {
                            suppressionEntite(entites, entite);
                            continue;
                        }
                    }
                }


                // Lorsque l'entité se trouve dans le disque actif par rapport au joueur
                else if (distance <= JOUEUR_RAYON_ACTIF) {
                    // printf("(Actif) => ");
                    
                    // En fonction du type de l'entité
                    switch (entite->entiteType) {
                        // Si l'entité est un mob 
                        case ENTITE_MOB:
                            // Si le mob est mort 
                            if (((t_mob*)entite)->statistiques.pv <= 0) {
                                suppressionEntite(entites, entite);
                                // play_bruitage(audio->bruitages->monstre_mort, 4);
                                continue;
                            }
                            // Si le mob est en DEPLACEMENT_COMBAT
                            // On update alors la position cible
                            if (((t_mob*)entite)->deplacementType == DEPLACEMENT_COMBAT && ((t_mob*)entite)->cible->entiteType == ENTITE_JOUEUR) {
                                nombreMobsCombat++;

                                // Update de la position cible 
                                if (((t_mob*)entite)->operation != ATTAQUE)
                                    ((t_mob*)entite)->positionDeplacement = ((t_mob*)entite)->cible->position;
                            }

                            break;


                        // Sur toutes les entités
                        default:
                            // // Si le joueur est 
                            // if (((t_mob*)entite)->deplacementType == DEPLACEMENT_COMBAT && distance > MOB_RAYON_COMBAT_POSITIONNEMENT) {
                            //     ((t_mob*)entite)->deplacementType = DEPLACEMENT_NORMAL;
                            // }

                            break;
                    }
                    

                    // Deplacement
                    entite->update((t_entite*)entite, distance, (t_entite*)joueur);

                    // combat
                    // entite->update((t_entite*)entite);

                    dessinerEntite((t_entite*)entite);
                }



                if (entite->entiteType == ENTITE_MOB) {
                    nombreMobs++;

                    if (((t_mob*)entite)->aggressif) 
                        nombreMobsAggressifs++;
                    else
                        nombreMobsPassifs++;
                }

                nombreEntites++;
            }

            
            suivant(entites);
        }

        // printf("Fin Update Entites\n");
        // printf("Entites Total : %i / Mobs Total : %i  /  Mobs Passifs : %i / Mobs Agressifs : %i\n", nombreEntites, nombreMobs, nombreMobsPassifs, nombreMobsAggressifs);
    }


    // /* -------------------------- Apparition d'entites -------------------------- */

    en_tete(entites);
    if (nombreEntites < ENTITE_CAP) {
        if (nombreMobs < MOB_CAP) {
            int proba = getNombreAleatoire(1, 100);

            //      Si le nombre de monstres aggressifs max n'est pas atteint
            //          Calcul la probabilité d'apparition d'un monstre
            //          Si apparition possible
            //              Apparition du monste dans le rayon semi actif
            if (nombreMobsAggressifs < MONSTRE_AGGRESSIF_CAP) {
                if (proba <= PROBABILITE_APPARITION_MONSTRE) {
                    apparitionMonstre(entites, map, joueur->position, joueur->statistiques.niveau);
                }
            }

            //      Si le nombre de monstres passif max n'est pas atteint
            //          Calcul la probabilité d'apparition d'un monstre
            //          Si apparition possible
            //              Apparition du monste dans le rayon semi actif


            //      Si le nombre d'animaux max n'est pas atteint
            //          Calcul la probabilité d'apparition d'un animal
            //          Si apparition possible
            //              Apparition de l'animal dans le rayon actif ou semi actif
        }
    }




    /* -------------------------------------------------------------------------- */
    /*                            Interaction & Dégâts                            */
    /* -------------------------------------------------------------------------- */





    /* -------------------------------------------------------------------------- */
    /*                                   Musique                                  */
    /* -------------------------------------------------------------------------- */


    if (nombreMobsCombat) musiqueType = MUSIC_COMBAT;
    else musiqueType = MUSIC_AMBIANCE;

    if (audio->musiqueType != musiqueType) {
        audio->musiqueType = musiqueType;
        selectionMusique(temps);
    }





    /* -------------------------------------------------------------------------- */
    /*                                  Affichage                                 */
    /* -------------------------------------------------------------------------- */

    /* ---------------- Construction de l'affichage de la caméra ---------------- */

    updateCamera(joueur->position);
    // afficherCamera(map);

    if (map->type == MAP_OVERWORLD) {
        dessinerVegetation(map);
        dessinerCalqueAmbiance(temps);
    }

    /* --------------- Construction de l'affichage de l'interface --------------- */

    // afficherInterface(joueur);
    

    /* ------------------------ Affichage à l'utilisateur ----------------------- */

    SDL_RenderPresent(moteur->renderer);
    SDL_RenderClear(moteur->renderer);
    
}
