/**
 * @file monstre.c
 *
 * @brief Module de gestion des monstres
 *
 * @author Clément Hibon
 * @date 23 janvier
 */





#include <stdlib.h>
#include <stdio.h>

#include "../include/physique.h"
#include "../include/audio.h"
#include "../include/moteur.h"
#include "../include/monstre.h"





/* -------------------------------------------------------------------------- */
/*                                   Update                                   */
/* -------------------------------------------------------------------------- */


/**
 * @brief Actualise un monstre
 * 
 * Toute la logique propre à un monstre est gérer dans cette fonction
 * 
 * @param monstre Un pointeur sur le monstre à actualiser
 * @param distance La distance entre le monstre et le joueur
 * @param cible Un pointeur sur la cible du monstre 
 */
void updateMonstre(t_monstre *monstre, float distance, t_entiteVivante *cible) {

    // Si le joueur est dans le rayon de détection du monstre
    if (monstre->deplacementType != DEPLACEMENT_COMBAT && distance <= MONSTRE_RAYON_COMBAT_DETECTION) {
        monstre->deplacementType = DEPLACEMENT_COMBAT;
        monstre->cible = cible;
    }
    
    
    updateMob((t_mob*)monstre, distance);

}





/* -------------------------------------------------------------------------- */
/*                                 Destruction                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief Detruit un monstre est libère la mémoire allouée pour ce dernier
 * 
 * @param monstre L'adresse du pointeur du monstre à détruire
 */
void detruireMonstre(t_monstre **monstre) {
    if (monstre != NULL && *monstre != NULL) {

        detruireMob((t_mob**) monstre);
        
    }
}





/* -------------------------------------------------------------------------- */
/*                                  Création                                  */
/* -------------------------------------------------------------------------- */


/**
 * @brief Alloue l'espace nécessaire pour un monstre et le créer
 * 
 * @param position La position à laquelle le monstre doit apparaitre
 * @param biome Le biome dans lequel le monstre apparait
 * @param niveauJoueur Le niveau actuel du joueur
 * 
 * @return Un pointeur sur le monstre créé, NULL en cas d'echec
 */
t_monstre* creerMonstre(const t_vecteur2 position, const e_biome biome, const int niveauJoueur) {
    t_mob *mob = creerMob(position);
    t_monstre *monstre = realloc(mob, sizeof(t_monstre));


    if (monstre == NULL) {
        printf("Erreur mémoire : Impossible d'allouer la place nécessaire pour creer un monstre\n");
        detruireMob(&mob);
        return NULL;
    }


    // Statistiques
    monstre->aggressif = VRAI;
    genererMonstre(monstre, biome, niveauJoueur);

    // 
    monstre->rayonDetection = 0;
    monstre->rayonDeplacement = 4;
    monstre->deplacementType = DEPLACEMENT_NORMAL;

    // Animation
    monstre->animation = creerAnimation(100, 4);

    // Fonctions
    monstre->update = (void (*)(t_entite*, float, t_entite*)) updateMonstre;
    monstre->detruire = (void (*)(t_entite**)) detruireMonstre;

    // Timer
    monstre->destructionInactif = monstre->aggressif;
    monstre->destructionDelai = VRAI;


    // Audio
    monstre->bruitages = creerAudioPack();
    chargerAudioPack(monstre->bruitages, monstre->tag);


    if (monstre->aggressif)
        ++(moteur->cache->compteurEntites.mobAggressifs);
    else
        ++(moteur->cache->compteurEntites.mobPassifs);

    mob = NULL;
    return monstre;
}





/* -------------------------------------------------------------------------- */
/*                                 Apparition                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param entites 
 * @param biome 
 * @param positionJoueur 
 * @param niveauJoueur 
 */
void apparitionMonstre(t_liste *entites, t_map *map, const t_vecteur2 positionJoueur, const int niveauJoueur) {
    const float rayon = JOUEUR_RAYON_INACTIF - JOUEUR_RAYON_SEMIACTIF;
    t_vecteur2 position = choisirPointDansRayon(rayon);


    // Rapport du point généré à la position du joueur dans le disque semiactif
    if (position.x >= 0) 
        position.x = (position.x + JOUEUR_RAYON_ACTIF) + positionJoueur.x; 
    else if (position.x < 0) 
        position.x = (position.x - JOUEUR_RAYON_ACTIF) + positionJoueur.x; 

    if (position.y >= 0) 
        position.y = (position.y + JOUEUR_RAYON_ACTIF) + positionJoueur.y; 
    else if (position.y < 0) 
        position.y = (position.y - JOUEUR_RAYON_ACTIF) + positionJoueur.y; 


    if (peutApparaitre(position, map)) {
        t_chunk *chunk = getChunkGraceABlock(position.x, position.y, COUCHE_SOL, map);
        if (chunk != NULL) {
            const e_biome biome = chunk->biome;
            t_monstre *monstre = creerMonstre(position, biome, niveauJoueur);

            en_queue(entites);
            ajout_droit(entites, (t_entite*)monstre);
        }
    }
}
