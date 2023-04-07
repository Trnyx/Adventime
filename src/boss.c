/**
 * @file boss.c
 * 
 * @brief 
 * 
 * @author Clément Hibon
 * @date 18 mars
 * @version 1.1
 */





#include <stdio.h>
#include <stdlib.h>

#include "../include/physique.h"
#include "../include/utilitaire.h"
#include "../include/moteur.h"
#include "../include/blocks_tag.h"
#include "../include/combat.h"
#include "../include/boss.h"





/* -------------------------------------------------------------------------- */
/*                                   Update                                   */
/* -------------------------------------------------------------------------- */


void updateBoss(t_boss *boss, float distance, t_entiteVivante *cible) {
    const t_vecteur2 positionApparitionBoss = moteur->cache->monde->positionApparitionBoss;
    const float eloignementPointBoss = calculDistanceEntrePoints(positionApparitionBoss, boss->position);
    

    if (eloignementPointBoss > TAILLE_CHUNK) {
        if (boss->cible != NULL)
            finCombat((t_mob*)boss);

        boss->positionDeplacement = positionApparitionBoss;
        boss->operation = SE_DEPLACE_VERS;
    }


    else if (boss->deplacementType != DEPLACEMENT_COMBAT && distance <= BOSS_RAYON_COMBAT_DETECTION) {
        boss->deplacementType = DEPLACEMENT_COMBAT;
        boss->cible = cible;
    }


    
    updateMob((t_mob*)boss, distance);
}





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
 * @brief 
 * 
 * @return t_boss_flags 
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


void detruireBoss(t_boss **boss) {
    printf("Destruction Boss => ");
    if (boss != NULL && *boss != NULL) {
        
        if ((*boss)->statistiques.pv <= 0)
            changerFlag((*boss)->jour);

        detruireMob((t_mob**)boss);

    }
}





/* -------------------------------------------------------------------------- */
/*                                  Creation                                  */
/* -------------------------------------------------------------------------- */


t_boss* creerBoss(const t_vecteur2 position, const e_jour jour) {
    t_mob *mob = creerMob(position);
    t_boss *boss = realloc(mob, sizeof(t_boss));

    if (boss == NULL) {
        printf("Erreur mémoire : Impossible d'allouer la place nécessaire pour creer un boss\n");
        detruireMob(&mob);
        return NULL;
    }


    boss->jour = jour;

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
    boss->update = (int (*)(t_entite*, float, t_entite*)) updateBoss;
    boss->detruire = (void (*)(t_entite**)) detruireBoss;

    boss->destructionInactif = FAUX;
    boss->destructionDelai = FAUX;


    ++(moteur->cache->compteurEntites.mobAggressifs);

    mob = NULL;
    return boss;
}