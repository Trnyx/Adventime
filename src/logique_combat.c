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
#include "../include/deplacement.h"
#include "../include/combat.h"
#include "../include/experience.h"





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





/**
 * @brief Remet un mob en normal
 * 
 * @param mob Un pointeur sur le mob qui n'est plus en combat
 */
void finCombat(t_mob *mob) {
    finDeplacement(mob);

    mob->deplacementType = DEPLACEMENT_NORMAL;
    mob->operation = ATTENTE;

    mob->cible = NULL;
    
    mob->gamma = 0;     
    mob->rotation = ROTATION_HORAIRE;
}





/* -------------------------------------------------------------------------- */
/*                                 Experience                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief On calcul l'expèrience à donner au gagnant et retirer au perdant du combat
 * 
 * @param entite L'entité gagnante
 * @param cible L'entité perdante
 */
void gestionExeperience(t_entiteVivante *entite, t_entiteVivante *cible) {
    const unsigned int experience = calculExperience(cible);

    donnerExperience(cible, -experience);
    donnerExperience(entite, experience);   
}





/* -------------------------------------------------------------------------- */
/*                             Items & Inventaires                            */
/* -------------------------------------------------------------------------- */


// Créer à la position de la mort
// Un truc qui stock l'inventaire du joueur
void dropInventaire(/*t_stockage inventaire*/) {

}




void dropItems(t_mob *mob) {
    printf("DROP ITEM => ");

    t_baseMob base = basesMobs[mob->tag - TAG_ANIMAL_VACHE];
    e_itemTag tag;


    if (base.lootProbabilite[0] == 100) {
        tag = base.loots[0];
    }
    else {
        const int probabilite = getNombreAleatoire(1, 100);
        for (int i = 0; i < 2; i++) {
            if (base.lootProbabilite[i] >= probabilite) {
                tag = base.loots[i];
            }
        }
    }


    printf("TAG %i => ", tag);
    t_itemEntite *itemEntite = creerItemEntite(mob->position, tag);
    printf("ITEM ENTITE CREE\n");
    
    ajout_droit(moteur->cache->entites, (t_entite*)itemEntite);
}





/* -------------------------------------------------------------------------- */
/*                                   Degats                                   */
/* -------------------------------------------------------------------------- */


#define OUVERTURE 40

/**
 * @brief Vérifie si la cible est touché par la source qui attaque
 * 
 * @param source Un pointeur sur l'entité attaquante
 * @param cible Un pointeur sur l'entité cible attaqué
 * @param angleAttaque L'angle dans lequel l'entité attaquant arrive par rapport à la cible
 * @param range Le rayon dans lequel l'entité attaquante peut touché la cible
 * 
 * @return VRAI si la cible est touchée, FAUX sinon
 */
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





/**
 * @brief Calcul les dégâts
 * 
 * @param niveauAttaquant Le niveau de l'attaquant
 * @param pointAttaque Les points d'attaque de l'attaquant
 * @param pointDefense Les points de défense de l'attaqué
 * @param attaquantEstNocture Si l'attaquant est de type nocturne
 * @param defenseurEstNocturne Si le défenseur est de type nocturne
 * 
 * @return Les dégâts affliger à l'adversaire
 */
float calculDegat(const int niveauAttaquant, int pointAttaque, int pointDefense, const boolean attaquantEstNocture, const boolean defenseurEstNocturne) {
  printf("%d", niveauAttaquant);
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
 * @brief Applique les dégâts à l'entité
 * 
 * @param entite Un pointeur sur l'entité qui subbit les dégats
 * @param degat Les dégats à infliger
 * 
 * @return VRAI si l'entité est morte, FAUX sinon
 */
boolean appliquerDegat(t_entiteVivante *entite, const float degat) {
    entite->statistiques.pv -= degat;

    return entite->statistiques.pv <= 0;
}





/**
 * @brief Met un coup à l'entité cible
 * 
 * @param entite Un pointeur sur l'entité mettant le coup
 * @param cible Un pointeur sur l'entité recevant le coup
 * @param angleAttaque L'angle dans lequel l'entité attaque
 * @param range Le rayon dans lequel l'entité attaquante peut touché sa cible
 */
void metUnCoup(t_entiteVivante *entite, t_entiteVivante *cible, const float angleAttaque, const float range) {
    if (toucheLaCible((t_entite*)entite, (t_entite*)cible, angleAttaque, range)) {
        printf("CIBLE TOUCHE\n");
        cible->cooldownRegeneration = COOLDOWN_REGENERATION;
        

        // Lorsque le mob cible est touché, le mob cible se met en mode combat
        // et il prend pour cible le mob attaquant
        if (cible->entiteType == ENTITE_MOB) {
            ((t_mob*)cible)->deplacementType = DEPLACEMENT_COMBAT;
            ((t_mob*)cible)->cible = entite;
        }


        float degat = calculDegat(entite->statistiques.niveau, entite->statistiques.attaque, cible->statistiques.defense, FAUX, FAUX);
        // Modificateur si il y a armes
        // Modificateur si il y a armure
        const boolean cibleEstMorte = appliquerDegat(cible, degat);


        // Knockback
        



        // mort(cible);
        if (cibleEstMorte) {
            if (entite->entiteType != ENTITE_JOUEUR)
                finCombat((t_mob*)entite);

            gestionExeperience(entite, cible);
            printf("EXPERIENCE => %i / %i\n", entite->statistiques.niveau, entite->statistiques.experience);

            if (entite->entiteType == ENTITE_JOUEUR)
                dropInventaire();
            else
                dropItems((t_mob*)cible);
        }
    }
    else
        printf("CIBLE NON TOUCHE\n");
}










void mort(t_entiteVivante *entite) {
    switch (entite->entiteType) {
        case ENTITE_JOUEUR:
            // reapparitionJoueur();
            break;

        default:
            entite->statistiques.pv = 0;
            break;
    }
}
