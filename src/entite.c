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

#include "../include/NanoId/nanoid.h"

#include "../include/physique.h"
#include "../include/moteur.h"
#include "../include/monde.h"
#include "../include/entite.h"
#include "../include/utilitaire.h"





/* -------------------------------------------------------------------------- */
/*                                     Get                                    */
/* -------------------------------------------------------------------------- */


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
 * @brief 
 * 
 * @param entiteSource 
 * @param entiteCible 
 * @return float 
 */
float calculDistanceEntreEntites(const t_entite *entiteSource, const t_entite *entiteCible) {
    return calculDistanceEntrePoints(entiteSource->position, entiteCible->position);
}





/* -------------------------------------------------------------------------- */
/*                          Deplacement & Orientation                         */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param map 
 * @param entite 
 * @param positionSuivante 
 * @return boolean 
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


    // Check si collision
    t_liste entitesAlentours = getEntitesAlentour(entite, ENTITE_MOB, (entite->hitbox.w * entite->taille) / 2);

    if (!liste_vide(&entitesAlentours)) {
        t_entite *entiteTempo = NULL;

        SDL_FRect hitbox;
        hitbox.x = positionSuivante.x; 
        hitbox.y = positionSuivante.y; 
        hitbox.w = entite->hitbox.w * entite->taille;
        hitbox.h = entite->hitbox.h * entite->taille;

        en_tete(&entitesAlentours);
        while (!hors_liste(&entitesAlentours)) {
            valeur_elt(&entitesAlentours, &entiteTempo);


            if (SDL_HasIntersectionF(&hitbox, &entiteTempo->hitbox)){
                printf("COLLISION : \n");
                return FAUX;
            }
                    

            suivant(&entitesAlentours);
        }
    }


    return VRAI;
}



/**
 * @brief 
 * 
 * @param entite 
 * @param vitesse 
 * @return boolean 
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
    }


    return peutSeDeplacer;
}





/**
 * @brief 
 * 
 * @param angle 
 * @param entite 
 */
void orienterEntite(const float angle, t_entite *entite) {
    if (!angle);

    else if (angle >= 45 && angle < 135)
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
 * @brief 
 * 
 * @param entite 
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
            switch (entite->tag) {
                case TAG_ANIMAL_VACHE: 
                    texture = moteur->textures->animaux; 
                    sprite.x = 0;
                    break;
                case TAG_MONSTRE_BASIC: 
                    texture = moteur->textures->monstres; 
                    sprite.x = (((t_monstre*)entite)->estNocturne ? NB_MONSTRE_TYPES * TAILLE_SET : ((t_monstre*)entite)->type) * (TAILLE_SET);
                    break;
                default: break;
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
                sprite.y += TAILLE_TILE * 4;
                break;
            case ATTAQUE:
                sprite.y += TAILLE_TILE * 4 * 2;
                break;
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
 * @brief 
 * 
 * @param entite 
 */
void detruireEntite(t_entite **entite) {
    printf("Destruction Entite => ");
    if (entite != NULL && *entite != NULL) {
        if ((*entite)->id != NULL) {
            free((*entite)->id);
            (*entite)->id = NULL;
        }
        
        free(*entite);
        *entite = NULL;

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
        printf("Erreur mémoire : Impossible d'allouer la place nécessaire pour creer une entite\n");
        free(entite);
        return NULL;
    }

    entite->id = generate(LONGUEUR_ID);
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
    entite->hitbox.h = 1;
    entite->hitbox.w = 1;

    entite->animation = NULL;

    
    entite->update = NULL;
    entite->detruire = detruireEntite;
    

    entite->timestampCreation = SDL_GetTicks();
    entite->timestampActualisation = entite->timestampCreation;

    entite->destructionInactif = VRAI;


    return entite;
}

