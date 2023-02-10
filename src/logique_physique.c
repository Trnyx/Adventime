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

#include "../include/physique.h"
#include "../include/utilitaire.h"
#include "../include/moteur.h"





// Fonction à executer à chaque frame
void logique(t_moteur *moteur) {


    /* -------------------------------------------------------------------------- */
    /*                                    Algo                                    */
    /* -------------------------------------------------------------------------- */

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


    t_joueur *joueur = moteur->monde->joueur;
    t_liste *entites = moteur->monde->map->entites;

    t_entite *entite = NULL;



    en_tete(entites);
    if (!liste_vide(entites)) {
        unsigned int nombreMobs = 0;


        /* ---------------- Entites actuellement présente dans la map --------------- */

        while (!hors_liste(entites)) {
            valeur_elt(entites, &entite);
            
            if (entite != NULL) {
                const float distance = calculDistanceEntreEntites(entite, (t_entite*)joueur);


                if (distance < JOUEUR_RAYON_ACTIF) {
                    // Deplacement
                    // monstre => joueur détection
                    // combat
                }


                else if (distance >= JOUEUR_RAYON_SEMIACTIF && distance < JOUEUR_RAYON_INACTIF) {
                    // Gestion de la durée de vie
                }


                else if (distance >= JOUEUR_RAYON_INACTIF) {
                    // Si monstre aggrassif
                    // Supprimer monstre
                    // Monstre supprimer break;
                }


                // Ajout de la durée de vie
                nombreMobs++;
            }
        }


        /* -------------------------- Apparition d'entites -------------------------- */

        if (nombreMobs < MOB_CAP) {

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

        }

    }
    
}
