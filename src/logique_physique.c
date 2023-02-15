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




unsigned long int u = 0;
/**
 * @brief Fonction appelé à chaque frame du jeu
 * 
 * Elle gère toute la physique et logique du jeu
 * 
 * @param moteur Pointeur sur le moteur du jeu
 */
void update(t_moteur *moteur) {
    // printf("Update (%li)\n", u++);
    t_joueur *joueur = moteur->monde->joueur;

    t_liste *entites = moteur->monde->map->entites;
    t_entite *entite = NULL;
    unsigned int nombreMobs = 0;

    time_t timestampFrame = time(NULL);



    /* -------------------------------------------------------------------------- */
    /*                                   Joueur                                   */
    /* -------------------------------------------------------------------------- */

    joueur->update(moteur, (t_entite*) joueur);

    



    /* -------------------------------------------------------------------------- */
    /*                                   Entites                                  */
    /* -------------------------------------------------------------------------- */


    /* ---------------- Entites actuellement présente dans la map --------------- */

    // en_tete(entites);
    // if (!liste_vide(entites)) {

    //     while (!hors_liste(entites)) {
    //         valeur_elt(entites, &entite);



    //         if (entite != NULL) {
    //             const float distance = calculDistanceEntreEntites(entite, (t_entite*)joueur);

    //             // Actualisation 
    //             entite->timestampActualisation = timestampFrame;


    //             if (distance < JOUEUR_RAYON_ACTIF) {
    //                 entite->update(moteur, (t_entite*) entite);
    //                 // Deplacement
    //                 // monstre => joueur détection
    //                 // combat
    //             }


    //             else if (distance >= JOUEUR_RAYON_SEMIACTIF && distance < JOUEUR_RAYON_INACTIF) {

    //                 // Gestion de la durée de vie
    //                 if (entite->timestampActualisation - entite->timestampCreation >= ENTITE_DUREE_VIE_MAX) {                        
    //                     entite->detruire((t_entite**) &entite);
    //                     oter_elt(entites);
    //                 }
                    
    //             }


    //             else if (distance >= JOUEUR_RAYON_INACTIF) {
    //                 // Si monstre aggrassif
    //                 // Supprimer monstre
    //                 // Monstre supprimer break;
    //             }


    //             nombreMobs++;
    //         }
    //     }
    // }


    // /* -------------------------- Apparition d'entites -------------------------- */

    // if (nombreMobs < MOB_CAP) {

    //     //      Si le nombre de monstres aggressifs max n'est pas atteint
    //     //          Calcul la probabilité d'apparition d'un monstre
    //     //          Si apparition possible
    //     //              Apparition du monste dans le rayon semi actif
    //     //      Si le nombre de monstres passif max n'est pas atteint
    //     //          Calcul la probabilité d'apparition d'un monstre
    //     //          Si apparition possible
    //     //              Apparition du monste dans le rayon semi actif
    //     //      Si le nombre d'animaux max n'est pas atteint
    //     //          Calcul la probabilité d'apparition d'un animal
    //     //          Si apparition possible
    //     //              Apparition de l'animal dans le rayon actif ou semi actif

    // }





    /* -------------------------------------------------------------------------- */
    /*                            Interaction & Dégâts                            */
    /* -------------------------------------------------------------------------- */





    /* -------------------------------------------------------------------------- */
    /*                                  Affichage                                 */
    /* -------------------------------------------------------------------------- */

    /* ---------------- Construction de l'affichage de la caméra ---------------- */

    updateCamera(moteur, joueur->position);
    afficherCamera(moteur);


    /* --------------- Construction de l'affichage de l'interface --------------- */

    // afficherInterface(joueur);
    

    /* ------------------------ Affichage à l'utilisateur ----------------------- */

    SDL_RenderPresent(moteur->renderer);
    SDL_RenderClear(moteur->renderer);
    
}
