/**
 * @file logique_combat.c
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
#include "../include/moteur.h"
#include "../include/mob.h"
#include "../include/deplacement.h"





// On attend avant de faire une action
// Une fois le temps d'attente terminé 
//     Le mob se déplace en direction du joueur rapidement
//     On check distance et ouverture
//     Si le joueur est assez proche et dans l'ouverture 
//         On calcul les dégâts infligés au joueur (attaque / défense)
//         On applique les dégâts
//         On vérifie si le joueur est mort
//         Si le joueur est mort
//             gestion des drops
//             gestion de l'expérience
//     Choix aléatoire du temps d'attente avant prochaine attaque 





/* -------------------------------------------------------------------------- */
/*                                   Degats                                   */
/* -------------------------------------------------------------------------- */


boolean toucheLaCible(const t_vecteur2 mob, const t_vecteur2 cible) {
    // Calcul la distance
    // Calcul l'angle
    return VRAI;
}





float calculDegat(const int pointAttaque, const int pointDefense, const int niveauAttaquant, const int niveauDefenseur) {
    return 0;
}





// Renvoie si le mob est mort
boolean appliquerDegat(t_mob *mob, const float degat) {
    // Check mort
    mob->statistiques.pv -= degat;

    return mob->statistiques.pv <= 0;
}



void metUncoup(t_mob *mob, t_mob *cible) {
    if (toucheLaCible(cible->position)) {
        const float degat = calculDegat();
        const boolean cibleEstMorte = appliquerDegat(cible, degat);

        if (cibleEstMorte) {
            cible->detruire(&cible);
        }
    }
}





/* -------------------------------------------------------------------------- */
/*                                 Experiences                                */
/* -------------------------------------------------------------------------- */


int calculExperience() {
    return 0;
}





/* -------------------------------------------------------------------------- */
/*                             Items & Inventaires                            */
/* -------------------------------------------------------------------------- */


//Créer 
void dropInventaire(/*t_stockage inventaire*/) {

}