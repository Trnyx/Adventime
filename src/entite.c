/**
 * @file entite.c
 * 
 * @brief 
 * 
 * @author Clément Hibon
 * @date 3 février
 * @version 1.1
 */




#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/moteur.h"
#include "../include/monde.h"
#include "../include/entite.h"
#include "../include/utilitaire.h"





/**
 * @brief 
 * 
 * @param entiteSource 
 * @param entiteCible 
 * @return float 
 */
float calculDistanceEntreEntites(const t_entite *entiteSource, const t_entite *entiteCible) {
    return calculDistanceEntrePoints(entiteSource->position, entiteCible->position);
}





/**
 * @brief 
 * 
 * @param map 
 * @param entite 
 * @param positionSuivante 
 * @return boolean 
 */
boolean peutDeplacerEntite(t_map *map, const t_entite *entite, const t_vecteur2 positionSuivante) {
    t_block *block = getBlockDansMap(positionSuivante.x, positionSuivante.y, COUCHE_VEGETATION, map);
    if (block == NULL) return FAUX;

    // Check si le block est bien vide
    if (block->tag != VIDE) return FAUX;

    block = getBlockDansMap(positionSuivante.x, positionSuivante.y, COUCHE_SOL, map);
    // Check si le block est un block profondeur
    if (block->tag == SOL_EAU_PROFONDE) return FAUX;

    t_block* blockPositionActuelle = getBlockDansMap(entite->position.x, entite->position.y, COUCHE_SOL, map);
    // printf("Position Actuelle : %i => ", blockPositionActuelle->tag);

    // Check si plus de 1 de hauteur 
    if (abs(block->tag - blockPositionActuelle->tag) > 1) return FAUX;


    return VRAI;
}



/**
 * @brief 
 * 
 * @param moteur 
 * @param entite 
 * @param vitesse 
 * @return boolean 
 */
boolean deplacerEntite(const t_moteur *moteur, t_entite *entite, const float vitesse) {
    const float distance = vitesse * TPS / 1000.0;
    // printf("Vitesse : %1.2f / TPS : %1.2f => ", vitesse, TPS);

    // Justification calcul normale
    const float normale = sqrt(pow(entite->orientation.x, 2) + pow(entite->orientation.y, 2));

    // Justification calcul
    t_vecteur2 positionSuivante;
    positionSuivante.x = entite->position.x + (distance * (entite->orientation.x / normale));
    positionSuivante.y = entite->position.y + (distance * (entite->orientation.y / normale));
    // printf("(distance : %1.2f, normale : %1.2f) ", distance, normale);
    printf("Position suivante : %1.2f:%1.2f => ", positionSuivante.x, positionSuivante.y);
    
    boolean peutSeDeplacer = peutDeplacerEntite(moteur->monde->map, entite, positionSuivante);
    // printf("Peut se deplacer ? %i => ", peutSeDeplacer);


    if (peutSeDeplacer == VRAI) {
        printf("Precedente : %1.2f:%1.2f | Nouvelle : %1.2f:%1.2f\n", entite->position.x, entite->position.y, positionSuivante.x, positionSuivante.y);
        entite->position = positionSuivante;
    }


    return peutSeDeplacer;
}





/* -------------------------------------------------------------------------- */
/*                                 Destruction                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param entite 
 */
void detruireEntite(t_entite **entite) {
    printf("Destruction Entite => ");
    if (entite != NULL && *entite != NULL) {

        free(*entite);
        *entite = NULL;

    }
}



/**
 * @brief 
 * 
 * @param mob 
 */
void detruireMob(t_mob **mob) {
    printf("Destruction Mob => ");
    if (mob != NULL && *mob != NULL) {

        detruireEntite((t_entite**)mob);

    }
}





/* -------------------------------------------------------------------------- */
/*                                  Création                                  */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param position 
 * @return t_entite* 
 */
t_entite* creerEntite(const t_vecteur2 position) {
    t_entite *entite = malloc(sizeof(t_entite));

    if (entite == NULL) {
        printf("Erreur mémoire : Impossible d'allouer la place nécessaire pour creer une entite");
        free(entite);
        return NULL;
    }


    entite->position.x = position.x;
    entite->position.y = position.y;
    entite->orientation.x = 1;
    entite->orientation.y = 0;

    entite->entiteType = ENTITE_RIEN;

    entite->hitbox.x = 0;
    entite->hitbox.y = 0;
    entite->hitbox.h = 16;
    entite->hitbox.w = 16;

    
    entite->update = NULL;
    entite->detruire = detruireEntite;
    

    entite->timestampCreation = time(NULL);
    entite->timestampActualisation = entite->timestampCreation;


    return entite;
}



t_mob* creerMob(const t_vecteur2 position) {
    t_entite *entite = creerEntite(position);
    t_mob *mob = realloc(entite, sizeof(t_mob));


    mob->rayonDeplacement = 0;

    mob->positionDeplacement.x = 0;
    mob->positionDeplacement.y = 0;

    mob->deplacementType = DEPLACEMENT_STATIQUE;

    mob->detruire = detruireMob;


    entite = NULL;
    return mob;
}