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





/**
 * @brief Fonction appelé à chaque frame du jeu
 * 
 * Elle gère toute la physique et logique du jeu
 * 
 * @param moteur Pointeur sur le moteur du jeu
 * @param audio Pointeur sur l'audio du jeu
 */
void update(t_moteur *moteur, t_audio *audio) {
    // printf("Update (%li)\n", u++);
    t_monde *monde = moteur->monde;
    t_joueur *joueur = monde->joueur;


    t_map *map = NULL;
    switch (joueur->map) {
        case MAP_OVERWORLD: map = monde->map; break;
        case MAP_CAVE: map = monde->map; break;
    }


    t_liste *entites = map->entites;
    t_entite *entite = NULL;

    unsigned int nombreMobs = 0;
    unsigned int nombreMobsCombat = 0;
    unsigned int nombreMonstresAggressifs = 0;


    // printf("TIME => ");

    time_t timestampFrame = time(NULL);
    t_temps *temps = monde->temps;

    gestionnaireTempsEvenements(temps, timestampFrame);


    e_musiques_type musiqueType;



    /* -------------------------------------------------------------------------- */
    /*                                Affichage Sol                               */
    /* -------------------------------------------------------------------------- */


    dessinerSol(moteur, map);



    /* -------------------------------------------------------------------------- */
    /*                                   Joueur                                   */
    /* -------------------------------------------------------------------------- */

    joueur->update(moteur, (t_entite*) joueur, 0.0);
    dessinerEntite(moteur, (t_entite*) joueur);

    



    /* -------------------------------------------------------------------------- */
    /*                                   Entites                                  */
    /* -------------------------------------------------------------------------- */


    /* ---------------- Entites actuellement présente dans la map --------------- */

    en_tete(entites);
    if (!liste_vide(entites)) {
        printf("Update Entites => ");

        while (!hors_liste(entites)) {
            valeur_elt(entites, &entite);


            if (entite != NULL) {
                // La distance séparant l'entité actuelle et le joueur
                const float distance = calculDistanceEntreEntites(entite, (t_entite*)joueur);
                // printf("distance : %1.2f ", distance);

                // Actualisation des temps d'actualisation
                entite->timestampActualisation = timestampFrame;


                // Lorsque l'entité se trouve dans le disque actif par rapport au joueur
                if (distance <= JOUEUR_RAYON_ACTIF) {
                    // printf("(Actif) => ");
                    
                    // En fonction du type de l'entité
                    switch (entite->entiteType) {
                        // Si l'entité est un monstre 
                        case ENTITE_MONSTRE_AGGRESSIF:
                            // Si le joueur est dans le rayon de détection du monstre
                            // Le monstre est alors en mode combat
                            if (((t_mob*)entite)->deplacementType != DEPLACEMENT_COMBAT && distance <= MONSTRE_RAYON_COMBAT_DETECTION) {
                                ((t_mob*)entite)->deplacementType = DEPLACEMENT_COMBAT;
                            }


                        // Sur toutes les entités
                        default:
                            // Si le joueur est 
                            if (((t_mob*)entite)->deplacementType == DEPLACEMENT_COMBAT && distance > MOB_RAYON_COMBAT_POSITIONNEMENT) {
                                ((t_mob*)entite)->deplacementType = DEPLACEMENT_NORMAL;
                            }

                            if (((t_mob*)entite)->deplacementType == DEPLACEMENT_COMBAT) {
                                nombreMobsCombat++;
                            }
                            break;
                    }
                    

                    // Deplacement
                    entite->update(moteur, (t_entite*)entite, distance);

                    // combat
                    // entite->update(moteur, (t_entite*)entite);

                    dessinerEntite(moteur, (t_entite*)entite);
                }


                // Lorsque l'entité se trouve dans le disque semi actif par rapport au joueur
                else if (distance > JOUEUR_RAYON_ACTIF && distance <= JOUEUR_RAYON_SEMIACTIF) {
                    // printf("(Semi Actif) => ");

                    // Gestion de la durée de vie de l'entité
                    // Si l'entité à atteint la durée de vie maximale d'une entité alors elle est supprimé
                    if (entite->timestampActualisation - entite->timestampCreation >= ENTITE_DUREE_VIE_MAX) {
                        oter_elt(entites);
                        entite->detruire((t_entite**) &entite);
                        suivant(entites);
                        continue;
                    }
                    
                }


                // Lorsque l'entité se trouve au delà des deux disques précédents
                // L'entité est concidéré dans un disque inactif
                else if (distance > JOUEUR_RAYON_SEMIACTIF) {
                    // printf("(Inactif) => ");
                    // Si le monstre est aggressif
                    // Suppression du monstre
                    if (entite->entiteType == ENTITE_MONSTRE_AGGRESSIF) {
                        oter_elt(entites);
                        entite->detruire((t_entite**) &entite);
                        suivant(entites);
                        continue;
                    }
                }



                switch (entite->entiteType) {
                    case ENTITE_MONSTRE_AGGRESSIF:
                        nombreMonstresAggressifs++;
                        break;

                    default:
                        break;
                }

                nombreMobs++;
            }

            
            suivant(entites);
        }

        printf("Mobs Total : %i  /  Monstre Agressif : %i\n", nombreMobs, nombreMonstresAggressifs);
        printf("Fin Update Entites\n");
    }


    // /* -------------------------- Apparition d'entites -------------------------- */

    en_tete(entites);
    if (nombreMobs < MOB_CAP) {
        int proba = getNombreAleatoire(1, 100);

        //      Si le nombre de monstres aggressifs max n'est pas atteint
        //          Calcul la probabilité d'apparition d'un monstre
        //          Si apparition possible
        //              Apparition du monste dans le rayon semi actif
        if (nombreMonstresAggressifs < MONSTRE_AGGRESSIF_CAP) {
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
        selectionMusique(audio);
    }





    /* -------------------------------------------------------------------------- */
    /*                                  Affichage                                 */
    /* -------------------------------------------------------------------------- */

    /* ---------------- Construction de l'affichage de la caméra ---------------- */

    updateCamera(moteur, joueur->position);
    // afficherCamera(moteur, map);

    if (map->type == MAP_OVERWORLD) {
        dessinerVegetation(moteur, map);
    }

    /* --------------- Construction de l'affichage de l'interface --------------- */

    // afficherInterface(joueur);
    

    /* ------------------------ Affichage à l'utilisateur ----------------------- */

    SDL_RenderPresent(moteur->renderer);
    SDL_RenderClear(moteur->renderer);
    
}
