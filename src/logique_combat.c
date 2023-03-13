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


#define OUVERTURE 30
boolean toucheLaCible(const t_entite *source, const t_entite *cible, const float angleAttaque, const float range) {
    // Calcul la distance
    const float distance = calculDistanceEntreEntites(source, cible);
    // printf("\n\nDISTANCE : %1.2f\n", distance);
    if (distance > range)
        return FAUX;

    /* ------------------------------ Calcul Angle ------------------------------ */

    const float angleMinimum = revolution(angleAttaque - OUVERTURE / 2);
    const float angleMaximum = revolution(angleAttaque + OUVERTURE / 2);
    
    t_vecteur2 pointHitbox;
    float anglePointHitbox;

    const t_vecteur2 tailleDemiHitbox = {
        cible->hitbox.w / 2,
        cible->hitbox.h / 2,
    };

    // Point HItbox Haut Gauche
    pointHitbox.x = cible->position.x - tailleDemiHitbox.x;
    pointHitbox.y = cible->position.y - tailleDemiHitbox.y;
    anglePointHitbox = revolution(calculAngleEntrePoints(source->position, pointHitbox));

    if (angleMaximum >= anglePointHitbox && angleMinimum <= anglePointHitbox)
        return VRAI;


    // Point HItbox Haut Droit
    pointHitbox.x = cible->position.x + tailleDemiHitbox.x;
    pointHitbox.y = cible->position.y - tailleDemiHitbox.y;
    anglePointHitbox = revolution(calculAngleEntrePoints(source->position, pointHitbox));

    if (angleMaximum >= anglePointHitbox && angleMinimum <= anglePointHitbox)
        return VRAI;

    // Point HItbox Bas Gauche
    pointHitbox.x = cible->position.x - tailleDemiHitbox.x;
    pointHitbox.y = cible->position.y + tailleDemiHitbox.y;
    anglePointHitbox = revolution(calculAngleEntrePoints(source->position, pointHitbox));

    if (angleMaximum >= anglePointHitbox && angleMinimum <= anglePointHitbox)
        return VRAI;

    // Point HItbox Bas Droit
    pointHitbox.x = cible->position.x + tailleDemiHitbox.x;
    pointHitbox.y = cible->position.y + tailleDemiHitbox.y;
    anglePointHitbox = revolution(calculAngleEntrePoints(source->position, pointHitbox));

    if (angleMaximum >= anglePointHitbox && angleMinimum <= anglePointHitbox)
        return VRAI;

    // printf("ANGLE ATTAQUE : %1.2f\nANGLE ENTRE SOURCE ET CIBLE : %1.2f \nMIN : %1.2f\nMAX : %1.2f\nMIN REVO : %1.2f\nMAX REVO : %1.2f\n\n", angleAttaque, angleFinale, angleAttaque + OUVERTURE / 2, angleAttaque - OUVERTURE / 2, revolution(angleAttaque + OUVERTURE / 2), revolution(angleAttaque - OUVERTURE / 2));
    
    return FAUX;

}





float calculDegat(const int niveauAttaquant, int pointAttaque, int pointDefense, const boolean attaquantEstNocture, const boolean defenseurEstNocturne) {
    if (defenseurEstNocturne) {
        pointDefense += (((pointDefense / 2.5) + pointDefense + 2));
    }


    int degat = (((niveauAttaquant * 0.6 + 2) * pointAttaque) / pointDefense) + 10;


    if (attaquantEstNocture) {
        degat += (((niveauAttaquant / 4.7) + niveauAttaquant + 2));
    }


    return degat;
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
void metUnCoup(t_entiteVivante *entite, t_entiteVivante *cible, const float angleAttaque, const float range) {
    if (toucheLaCible((t_entite*)entite, (t_entite*)cible, angleAttaque, range)) {
        printf("CIBLE TOUCHE\n");

        float degat = calculDegat(entite->statistiques.niveau, entite->statistiques.attaque, cible->statistiques.defense, FAUX, FAUX);
        // Modificateur si il y a armes
        // Modificateur si il y a armure

        const boolean cibleEstMorte = appliquerDegat(cible, degat);


        // mort(cible);
        if (cibleEstMorte) {
            
            // Calcul experience
            // distribution experience
            // drops items
        }
    }
    else
        printf("CIBLE NON TOUCHE\n");
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





void mort(t_entiteVivante *entite) {
    switch (entite->entiteType) {
        case ENTITE_JOUEUR:
            // reapparitionJoueur();
            break;

        default:
            entite->statistiques.pv = 0;
            // entite->detruire(&entite);
            break;
    }
}