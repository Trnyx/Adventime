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
#include "../include/combat.h"





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
    const float distance = calculDistanceEntrePoints(mob, cible);
    if (distance > 1.2)
        return FAUX;

    // Calcul l'angle
    // const float angle = calculAngleEntrePoints(mob, cible);
    // if (angle)
    
    return VRAI;
}





float calculDegat(const int pointAttaque, const int pointDefense, const int niveauAttaquant, const int niveauDefenseur) {
    return 0;
}





/**
 * @brief 
 * 
 * @param entite L'entité qui subbit les dégats
 * @param degat Les dégats à infliger
 * @return VRAI si l'entité est mort
 */
boolean appliquerDegat(t_entiteVivante *entite, const float degat) {
    entite->statistiques.pv -= degat;

    return entite->statistiques.pv <= 0;
}





/**
 * @brief 
 * 
 * @param entite 
 * @param cible 
 */
void metUnCoup(t_entiteVivante *entite, t_entiteVivante *cible) {
    if (toucheLaCible(cible->position)) {
        const float degat = calculDegat(mob->statistiques.attaque, cible->statistiques.defense, mob->statistiques.niveau, cible->statistiques.niveau);
        const boolean cibleEstMorte = appliquerDegat(cible, degat);

        if (cibleEstMorte) {
            // Calcul experience
            // distribution experience
            // drops items
            mort((t_entite*)cible);
        }
    }
}





/* -------------------------------------------------------------------------- */
/*                                 Experiences                                */
/* -------------------------------------------------------------------------- */


int calculExperience(t_mob *mob) {
    int exp = mob->statistiques.experience;
    return exp;
}





/* -------------------------------------------------------------------------- */
/*                             Items & Inventaires                            */
/* -------------------------------------------------------------------------- */


// Créer à la position de la mort
// Un truc qui stock l'inventaire du joueur
void dropInventaire(/*t_stockage inventaire*/) {

}




void dropItems() {
    // récupère la base du mob
    // Calcul la probabilité de l'item qui est drop
    // Aléatoire
}





void mort(t_entite *entite) {
    switch (entite->entiteType) {
        case ENTITE_JOUEUR:
            // reapparitionJoueur();
            break;

        default:
            entite->detruire(&entite);
            break;
    }
}