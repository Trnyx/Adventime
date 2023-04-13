/**
 * @file boss.c
 * 
 * @brief Module de gestion des boss
 * 
 * @author Clément Hibon
 * @date 18 mars
 */





#include <stdio.h>
#include <stdlib.h>

#include "../include/physique.h"
#include "../include/utilitaire.h"
#include "../include/moteur.h"
#include "../include/audio.h"
#include "../include/blocks_tag.h"
#include "../include/combat.h"
#include "../include/boss.h"





/* -------------------------------------------------------------------------- */
/*                                   Update                                   */
/* -------------------------------------------------------------------------- */


/**
 * @brief Met à jour le boss
 * 
 * @param boss Le boss qui est mit à jour
 * @param distance La distance entre le boss et sa cible
 * @param cible La cible du boss
 */
void updateBoss(t_boss *boss, float distance, t_entiteVivante *cible) {
    const t_vecteur2 positionApparitionBoss = moteur->cache->monde->positionApparitionBoss;
    const float eloignementPointBoss = calculDistanceEntrePoints(positionApparitionBoss, boss->position);


    // Si le boss est bien retourné à son temple
    if (boss->peutAttaquerJoueur == FAUX && eloignementPointBoss <= 6) {
        boss->peutAttaquerJoueur = VRAI;
    }
    

    // Si le boss est trop loin de son temple
    if (eloignementPointBoss > TAILLE_CHUNK) {
        if (boss->cible != NULL) {
            finCombat((t_mob*)boss);
            boss->peutAttaquerJoueur = FAUX;
        }

        boss->positionDeplacement = positionApparitionBoss;
        boss->operation = SE_DEPLACE_VERS;
    }


    // Si le boss détecte le joueur
    else if (boss->deplacementType != DEPLACEMENT_COMBAT && distance <= BOSS_RAYON_COMBAT_DETECTION) {
        if (boss->peutAttaquerJoueur) {
            boss->deplacementType = DEPLACEMENT_COMBAT;
            boss->cible = cible;
        }
    }


    
    updateMob((t_mob*)boss, distance);
}





/**
 * @brief Charge un boss dans la map
 * 
 * @return Le boss actif, NULL si aucun boss
 */
t_boss* chargerBoss() {
    t_monde *monde = moteur->cache->monde;
    boolean apparait = FAUX;

    t_boss *boss = monde->boss;
    e_jour jour = getJourDeLaSemaine(time(NULL));


    if (jour == LUNDI && !monde->bossFlags.lundi) 
        apparait = VRAI;
    else if (jour == MERCREDI && !monde->bossFlags.mercredi)
        apparait = VRAI;
    else if (jour == VENDREDI && !monde->bossFlags.vendredi)
        apparait = VRAI;
    else
        apparait = FAUX;


    if (apparait) {
        boss = creerBoss(monde->positionApparitionBoss, jour);
        ajout_droit(monde->overworld->entites, (t_entite*)boss);
    }
    else {
        if (boss != NULL)
            boss->detruire((t_entite**) &boss);
    }


    return boss;
}





/**
 * @brief Met à jour le flag du boss vaincu
 * 
 * @param jour Le jour du boss vaincu
 */
void changerFlag(const e_jour jour) {
    t_boss_flags *bossFlags = &moteur->cache->monde->bossFlags;

    switch (jour) {
        case LUNDI:
            bossFlags->lundi = 1;
            break;
        case MERCREDI:
            bossFlags->mercredi = 1;
            break;
        case VENDREDI:
            bossFlags->vendredi = 1;
            break;
        
        default:
            break;
    }
}





/* -------------------------------------------------------------------------- */
/*                                     Get                                    */
/* -------------------------------------------------------------------------- */


/**
 * @brief Obtient le point d'apparition du boss
 * 
 * @param map La map dans laquelle le boss doit apparaitre
 * 
 * @return La position où apparait le boss
 */
t_vecteur2 getPointApparitionBoss(t_map *map) {
    t_vecteur2 position = { 0, 0 };

    for (int x = 0; x < TAILLE_MAP * TAILLE_CHUNK; x++) {
        for (int y = 0; y < TAILLE_MAP * TAILLE_CHUNK; y++) {
            t_block *block = getBlockDansMap(x, y, COUCHE_OBJETS, map);

            if (block == NULL) continue;
            if (block->tag == BLOCK_TEMPLE_ENTREE_BAS_CENTRE) {
                position.x = block->position.x;
                position.y = block->position.y + 2;
                
                return position;
            }
        }
    }
    
    return position;
}





/**
 * @brief Créer et initialise les flags des boss vaincus à 0
 * 
 * Les flags des boss indique que le boss à bien été vaincu
 * 
 * @return Une structure contenant les flags des boss
 */
t_boss_flags initialiserBossFlags() {
    t_boss_flags flags;

    flags.lundi = 0;
    flags.mercredi = 0;
    flags.vendredi = 0;


    return flags;
}





/* -------------------------------------------------------------------------- */
/*                                 Destruction                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief Detruit un boss est libère la mémoire allouée pour ce dernier
 * 
 * @param boss L'adresse du pointeur du boss à détruire
 */
void detruireBoss(t_boss **boss) {
    if (boss != NULL && *boss != NULL) {
        
        if ((*boss)->statistiques.pv <= 0)
            changerFlag((*boss)->jour);

        detruireMob((t_mob**)boss);

    }
}





/* -------------------------------------------------------------------------- */
/*                                  Creation                                  */
/* -------------------------------------------------------------------------- */


/**
 * @brief Alloue l'espace nécessaire pour les flags des inputs du joueur et les initialise
 * 
 * @param position La position à laquelle le boss apparaît
 * @param jour Le jour correspondant au boss
 * 
 * @return Un pointeur sur les flags des inputs, NULL si echec
 */
t_boss* creerBoss(const t_vecteur2 position, const e_jour jour) {
    t_mob *mob = creerMob(position);
    t_boss *boss = realloc(mob, sizeof(t_boss));

    if (boss == NULL) {
        printf("Erreur mémoire : Impossible d'allouer la place nécessaire pour creer un boss\n");
        detruireMob(&mob);
        return NULL;
    }


    boss->jour = jour;
    boss->peutAttaquerJoueur = VRAI;

    boss->baseStatistiques = genererStatistiquesDeBaseBoss(boss->jour);
    boss->statistiques = genererStatistiques(boss->baseStatistiques, 10);


    // Entite
    boss->entiteType = ENTITE_MOB;
    boss->tag = TAG_BOSS;
    boss->taille = 3;
    boss->aggressif = VRAI;

    boss->hitbox.x = position.x - (boss->taille / 2);
    boss->hitbox.y = position.y - (boss->taille / 2);
    boss->hitbox.h = boss->taille;
    boss->hitbox.w = boss->taille;

    boss->animation = creerAnimation(400, 4);
    boss->rotation = ROTATION_HORAIRE;


    // Fonctions
    boss->update = (void (*)(t_entite*, float, t_entite*)) updateBoss;
    boss->detruire = (void (*)(t_entite**)) detruireBoss;

    boss->destructionInactif = FAUX;
    boss->destructionDelai = FAUX;

    boss->bruitages = creerAudioPack();
    chargerAudioPack(boss->bruitages, boss->tag);
    


    ++(moteur->cache->compteurEntites.mobAggressifs);

    mob = NULL;
    return boss;
}