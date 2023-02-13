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
        getNombreAleatoire(1, rayon),
        getNombreAleatoire(1, rayon),
    };


    return point;
}




int deplacementNormal(t_moteur *moteur, t_mob *mob) {
    // Génère un nombre aléatoire représentant la possibilité de déplacement
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

    if (proba > PROBABILITE_DEPLACEMENT_AUCUN) {
        mob->deplacementType = DEPLACEMENT_NORMAL;

        t_vecteur2 pointARejoindre = choisirPointDeDeplacement(mob->rayonDeplacement);
        mob->positionDeplacement.x = mob->position.x + pointARejoindre.x;
        mob->positionDeplacement.y = mob->position.y + pointARejoindre.y;
        
        if (blockEstDansLaMap(mob->positionDeplacement.x, mob->positionDeplacement.y)) {

        }
        else {
            if (proba <= PROBABILITE_DEPLACEMENT_OBLIGATOIRE) {
                
            }
        }
    }


    return 0;
}





int deplacementCombat(t_moteur *moteur, t_mob *mob) {
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










int (*getDeplacement(e_deplacementType deplacement))(t_moteur*, t_mob*) {
    switch (deplacement) {
        case DEPLACEMENT_NORMAL:  
            return deplacementNormal;

        case DEPLACEMENT_COMBAT:  
            return deplacementCombat;

            
        case DEPLACEMENT_STATIQUE: 
        default:
            return NULL;
    }
}