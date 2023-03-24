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
#include <string.h>

#include "../include/physique.h"
#include "../include/moteur.h"
#include "../include/monde.h"
#include "../include/entite.h"
#include "../include/utilitaire.h"





/* -------------------------------------------------------------------------- */
/*                                Verification                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief Vérifie si l'entité peut apparaître
 * 
 * @param position La position à laquelle l'entité doit apparaître
 * @param map La map dans laquelle l'entité apparait
 * 
 * @return VRAI si l'entité peut apparaitre, FAUX sinon
 */
boolean peutApparaitre(const t_vecteur2 position, t_map *map) {
    t_chunk *chunk = getChunkGraceABlock(position.x, position.y, COUCHE_OBJETS, map);

    if (chunk == NULL) 
        return FAUX;

    const e_biome biome = chunk->biome;
    if (biome == BIOME_PROFONDEUR)
        return FAUX;

    t_block *block = getBlockDansMap(position.x, position.y, COUCHE_SOL, map);
    if (block->tag == SOL_EAU)
        return FAUX;

    block = getBlockDansMap(position.x, position.y, COUCHE_OBJETS, map);
    if (block == NULL)
        return FAUX;
    
    if (block->tag != VIDE)
        return FAUX;
            
    return VRAI;
}





/* -------------------------------------------------------------------------- */
/*                                     Get                                    */
/* -------------------------------------------------------------------------- */


/**
 * @brief Obtient toutes les entités souhaités dans un rayon aux alentours d'une entité 
 * 
 * @param centre L'entité centrale
 * @param type Le type de l'entité à regarder
 * @param range Le rayon dans lequel les entités seront "détecté"
 * 
 * @return Une liste contenant toutes les entités detectées aux alentours de l'entité centrale
 */
t_liste getEntitesAlentour(t_entite *centre, const e_entiteType type, const float range) {
    t_liste *entitesActuelles = moteur->cache->entites;
    t_liste entitesAlentours;
    init_liste(&entitesAlentours);

    t_entite *entite = NULL;


    en_tete_cache(entitesActuelles);
    while (!hors_liste_cache(entitesActuelles)) {
        valeur_elt_cache(entitesActuelles, &entite);

        if (!strcmp(centre->id, entite->id)) {
            suivant_cache(entitesActuelles);
            continue;
        }


        const float distance = calculDistanceEntreEntites(centre, entite);

        if (entite->entiteType == type && distance <= range)
            ajout_droit(&entitesAlentours, entite);

        suivant_cache(entitesActuelles);
    }
    

    return entitesAlentours;
}





/* -------------------------------------------------------------------------- */
/*                                   Calcul                                   */
/* -------------------------------------------------------------------------- */


/**
 * @brief Calcul la distance entre deux entités
 * 
 * @param entiteSource L'entité source
 * @param entiteCible L'entité cible
 * 
 * @return La distance entre les deux entités
 */
float calculDistanceEntreEntites(const t_entite *entiteSource, const t_entite *entiteCible) {
    return calculDistanceEntrePoints(entiteSource->position, entiteCible->position);
}





/**
 * @brief Pousse l'entité cible
 * 
 * @param source L'entité qui pousse
 * @param cible L'entité poussé
 */
void pousseEntite(t_entite *source, t_entite *cible) {
    t_vecteur2 deltaMouvement = {
        cible->position.x - source->position.x,
        cible->position.y - source->position.y,
    };


    float force = deltaMouvement.x >= deltaMouvement.y ? deltaMouvement.x : deltaMouvement.y;
    force = abs(force);


    if (force >= 0.01) {
        force = sqrt(force);
        deltaMouvement.x /= force;
        deltaMouvement.y /= force;

        float modifieur = 1.0 / force;
        if (modifieur > 1.0) {
            modifieur = 1.0;
        }

        deltaMouvement.x *= modifieur;
        deltaMouvement.y *= modifieur;
        deltaMouvement.x *= 0.05f;
        deltaMouvement.y *= 0.05f;
    }

    
    // Applique la force à l'entité cible
    ((t_mob*)cible)->positionDeplacement.x += deltaMouvement.x;
    ((t_mob*)cible)->positionDeplacement.y += deltaMouvement.y;

}





/* -------------------------------------------------------------------------- */
/*                          Deplacement & Orientation                         */
/* -------------------------------------------------------------------------- */


/**
 * @brief Vérifie si l'entité peut se déplacer à la position suivante donnée
 * 
 * @param map La map dans laqeulle l'entité se déplace
 * @param entite L'entité se déplaçant
 * @param positionSuivante La position suivante à laquelle l'entité doit se déplacer
 * 
 * @return VRAI si l'entité peut se déplacer, FAUX sinon
 */
boolean peutDeplacerEntite(t_map *map, t_entite *entite, const t_vecteur2 positionSuivante) {
    t_block *block = getBlockDansMap(positionSuivante.x, positionSuivante.y, COUCHE_OBJETS, map);
    if (block == NULL) 
        return FAUX;

    // Check si le block est bien vide
    if (block->tag != VIDE) 
        return FAUX;


    // Check si le block est un block profondeur
    block = getBlockDansMap(positionSuivante.x, positionSuivante.y, COUCHE_SOL, map);
    if (block == NULL)
        return FAUX;

    if (block->tag == SOL_EAU_PROFONDE) 
        return FAUX;


    // Check si plus de 1 de hauteur 
    t_block* blockPositionActuelle = getBlockDansMap(entite->position.x, entite->position.y, COUCHE_SOL, map);
    if (abs(block->tag - blockPositionActuelle->tag) > 1) 
        return FAUX;


    // Check si il y a une collision avec les entités autour
    t_liste entitesAlentours = getEntitesAlentour(entite, ENTITE_MOB, (entite->hitbox.w * entite->taille) * 0.8);

    if (!liste_vide(&entitesAlentours)) {
        t_entite *entiteTempo = NULL;

        SDL_FRect hitbox;
        hitbox.x = positionSuivante.x; 
        hitbox.y = positionSuivante.y; 
        hitbox.w = entite->hitbox.w;
        hitbox.h = entite->hitbox.h;

        en_tete(&entitesAlentours);
        while (!hors_liste(&entitesAlentours)) {
            valeur_elt(&entitesAlentours, &entiteTempo);


            if (SDL_HasIntersectionF(&hitbox, &entiteTempo->hitbox)) {
                pousseEntite(entite, entiteTempo);
                // entiteTempo->position.x;
                // entiteTempo->position.y;

                return FAUX;
            }
                    

            suivant(&entitesAlentours);
        }
    }


    return VRAI;
}



/**
 * @brief Déplace une entité
 * 
 * @param entite Un pointeur sur l'entité à déplacer
 * @param vitesse La vitesse à laquelle l'entité doit se déplacer 
 * 
 * @return VRAI si l'entié à pu se déplacer, FAUX sinon
 */
boolean deplacerEntite(t_entite *entite, const float vitesse) {
    const float distance = vitesse * TPS / 1000.0;
    // printf("Vitesse : %1.2f / TPS : %1.2f => ", vitesse, TPS);

    // Justification calcul normale
    const float normale = sqrt(pow(entite->direction.x, 2) + pow(entite->direction.y, 2));

    // Justification calcul
    t_vecteur2 positionSuivante;
    positionSuivante.x = entite->position.x + (distance * (entite->direction.x / normale));
    positionSuivante.y = entite->position.y + (distance * (entite->direction.y / normale));
    // printf("(distance : %1.2f, normale : %1.2f) ", distance, normale);
    // printf("Position suivante : %1.2f:%1.2f => ", positionSuivante.x, positionSuivante.y);
    
    boolean peutSeDeplacer = peutDeplacerEntite(moteur->cache->map, entite, positionSuivante);
    // printf("Peut se deplacer ? %i => ", peutSeDeplacer);


    if (peutSeDeplacer == VRAI) {
        // printf("Precedente : %1.2f:%1.2f | Nouvelle : %1.2f:%1.2f\n", entite->position.x, entite->position.y, positionSuivante.x, positionSuivante.y);
        entite->position = positionSuivante;
        
        entite->hitbox.x = entite->position.x - (entite->taille / 2);
        entite->hitbox.y = entite->position.y - (entite->taille / 2);
        entite->hitbox.w = entite->taille;
        entite->hitbox.h = entite->taille;
    }


    return peutSeDeplacer;
}





/**
 * @brief Oriente l'entité
 * 
 * Il y a quatre orientations : NORD, EST, OUEST et SUD
 * 
 * @param angle L'angle dans lequel l'entité regarde [0; 360[
 * @param entite Pointeur sur l'entité à orienter
 */
void orienterEntite(const float angle, t_entite *entite) {
    if (angle >= 45 && angle < 135)
        entite->orientation = NORD;
    else if (angle >= 135 && angle < 225)
        entite->orientation = EST;
    else if (angle >= 225 && angle < 315)
        entite->orientation = SUD;
    else
        entite->orientation = OUEST;
}





/* -------------------------------------------------------------------------- */
/*                                  Affichage                                 */
/* -------------------------------------------------------------------------- */


#define TAILLE_SET (8 * TAILLE_TILE)

/**
 * @brief Dessine l'entité sur l'écran
 * 
 * @param entite Pointeur sur l'entite à afficher
 */
void dessinerEntite(t_entite *entite) {
    SDL_Texture *texture = NULL;
    SDL_Rect sprite;
    sprite.h = sprite.w = TAILLE_TILE;
    sprite.x = 0;
    sprite.y = entite->orientation * TAILLE_TILE;


    SDL_Rect rendu;
    rendu.w = moteur->camera->tailleRendu.x;
    rendu.h = moteur->camera->tailleRendu.y;

    rendu.x = positionRelativeEnPositionSurEcran(entite->position.x, 0.0, moteur->camera->origine.x, rendu.w) - rendu.w / 2;
    rendu.y = positionRelativeEnPositionSurEcran(entite->position.y, 0.0, moteur->camera->origine.y, rendu.h) - rendu.h / 2;

    // SDL_SetRenderDrawColor(moteur->renderer, 255, 0, 0, 255);
    // SDL_RenderFillRect(moteur->renderer, &rendu);


    switch (entite->entiteType) {
        case ENTITE_JOUEUR: 
            texture = moteur->textures->joueur; 
            break;

        case ENTITE_MOB:
            if (entite->tag >= TAG_ANIMAL_VACHE && entite->tag <= TAG_ANIMAL_COCHON) {
                texture = moteur->textures->animaux; 
                sprite.x = (entite->tag - TAG_ANIMAL_VACHE) * (TAILLE_SET / 2);
            }
            else if (entite->tag == TAG_MONSTRE_BASIC) {
                texture = moteur->textures->monstres; 
                sprite.x = (((t_monstre*)entite)->estNocturne ? NB_MONSTRE_TYPES * TAILLE_SET : ((t_monstre*)entite)->type) * (TAILLE_SET);
            }
            else if (entite->tag == TAG_BOSS) {
                texture = moteur->textures->monstres;
                // sprite.x = (((t_boss*)entite)->jour) * (TAILLE_SET);
                rendu.w *= entite->taille;
                rendu.h *= entite->taille;
            }
            break;

        default:
            break;
    }


    // Animation
    if (entite->animation != NULL) {
        updateAnimation(entite->animation, moteur->frame);
        sprite.x += TAILLE_TILE * entite->animation->frameCourante;
        
        // Deplacement
        switch (((t_entiteVivante*)entite)->operation) {
            case SE_DEPLACE_VERS:
            case SE_DEPLACE_AUTOUR:
            case ATTAQUE:
                sprite.y += TAILLE_TILE * 4;
                break;
                // sprite.y += TAILLE_TILE * 4 * 2;
                // break;
            default:
                break;
        }
    }




    SDL_RenderCopy(moteur->renderer, texture, &sprite, &rendu);
    // SDL_Rect point = {
    //     positionRelativeEnPositionSurEcran(entite->hitbox.x, 0.0, moteur->camera->origine.x, rendu.w), 
    //     positionRelativeEnPositionSurEcran(entite->hitbox.y, 0.0, moteur->camera->origine.y, rendu.h), 
    //     moteur->camera->tailleRendu.x,
    //     moteur->camera->tailleRendu.y,
    // };
    // SDL_SetRenderDrawColor(moteur->renderer, 0, 0, 0, 255);
    // SDL_RenderFillRect(moteur->renderer, &point);
}





/* -------------------------------------------------------------------------- */
/*                                 Destruction                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief Detruit une entité est libère la mémoire allouée pour cette dernière
 * 
 * @param entite L'adrese du pointeur de l'entité à détruire
 */
void detruireEntite(t_entite **entite) {
    printf("Destruction Entite => ");
    if (entite != NULL && *entite != NULL) {
        if ((*entite)->id != NULL) {
            free((*entite)->id);
            (*entite)->id = NULL;
        }

        if ((*entite)->animation != NULL) {
            detruireAnimation(&(*entite)->animation);
            (*entite)->animation = NULL;
        }
        

        free(*entite);
        *entite = NULL;
    }
}





/* -------------------------------------------------------------------------- */
/*                                  Création                                  */
/* -------------------------------------------------------------------------- */


/**
 * @brief Alloue l'espace nécessaire pour une entité et la créée
 * 
 * @param position La position à laquelle l'entité doit être créée
 * 
 * @return Un pointeur sur l'entité créée, NULL si echec
 */
t_entite* creerEntite(const t_vecteur2 position) {
    t_entite *entite = malloc(sizeof(t_entite));

    if (entite == NULL) {
        printf("Erreur mémoire : Impossible d'allouer la place nécessaire pour creer une entite\n");
        return NULL;
    }

    entite->id = genererId();
    printf("ID : %s\n", entite->id);


    entite->position.x = position.x;
    entite->position.y = position.y;
    entite->direction.x = 0;
    entite->direction.y = 0;
    entite->orientation = SUD;

    entite->entiteType = ENTITE_RIEN;
    entite->tag = TAG_AUCUN;

    entite->taille = 1;

    entite->hitbox.x = position.x - (entite->taille / 2);
    entite->hitbox.y = position.y - (entite->taille / 2);
    entite->hitbox.h = entite->taille;
    entite->hitbox.w = entite->taille;

    entite->animation = NULL;

    
    entite->update = NULL;
    entite->detruire = detruireEntite;
    

    entite->timestampCreation = SDL_GetTicks();
    entite->timestampActualisation = entite->timestampCreation;

    entite->destructionInactif = VRAI;
    entite->destructionDelai = VRAI;


    return entite;
}

