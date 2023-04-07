/**
 * @file animal.c
 *
 * @brief Module de manipulation des animaux
 *
 * @author Clément Hibon
 * @date 28 février
 * @version 1.1
 */



#include <stdio.h>
#include <stdlib.h>

#include "../include/physique.h"
#include "../include/audio.h"
#include "../include/moteur.h"
#include "../include/animal.h"





/* -------------------------------------------------------------------------- */
/*                                  Selection                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief Choisit aléatoirement le tag d'un animal 
 * 
 * @return Le tag d'un animal
 */
e_entiteTag choisirTag() {
    return getNombreAleatoire(TAG_ANIMAL_VACHE, TAG_ANIMAL_COCHON);
}





/* -------------------------------------------------------------------------- */
/*                                Verifications                               */
/* -------------------------------------------------------------------------- */


/**
 * @brief Vérifie si l'animal se situe trop loin d'un troupeau
 * 
 * @param animal Pointeur sur l'animal que l'on vérifie 
 * 
 * @return Un pointeur sur l'entité d'un animal se situant dans le troupeau lorque l'animal que l'on vérifie se situe trop loin du troupeau
 */
t_entite* estTropLoinDuTroupeau(t_animal *animal) {
    t_liste *entitesAlentours = getEntitesAlentour((t_entite*)animal, ENTITE_MOB, ANIMAL_RAYON_DETECTION_TROUPEAU);
    
    if (liste_vide(entitesAlentours))
        return NULL;


    t_entite *entiteTempo = NULL;
    t_entite *entite = NULL;
    float distance = 0.0;

    en_tete(entitesAlentours);
    while (!hors_liste(entitesAlentours)) {
        valeur_elt(entitesAlentours, &entiteTempo);

        if (entiteTempo->tag == animal->tag) {
            distance = calculDistanceEntreEntites((t_entite*)animal, entiteTempo);

            if (distance <= ANIMAL_RAYON_TROP_LOIN_TROUPEAU)
                return NULL;
            else 
                entite = entiteTempo;
        }

        suivant(entitesAlentours);
    }
    
    
    detruire_liste(&entitesAlentours);
    return entite;
}





/* -------------------------------------------------------------------------- */
/*                                   Update                                   */
/* -------------------------------------------------------------------------- */


/**
 * @brief Actualise un animal
 * 
 * Toute la logique propre à un animal est gérée dans cette fonction
 * 
 * @param animal Pointeur sur l'animal à actualiser
 * @param distance La distance entre l'animal est le joueur
 * @param cible La cible de l'animal
 */
void updateAnimal(t_animal *animal, float distance, t_entiteVivante *cible) {
    if (animal->cible == NULL) {
        t_entite *animalDuTroupeauLePlusProche = estTropLoinDuTroupeau(animal);
        
        if (animalDuTroupeauLePlusProche != NULL) {
            animal->positionDeplacement.x = animalDuTroupeauLePlusProche->position.x;
            animal->positionDeplacement.y = animalDuTroupeauLePlusProche->position.y;

            animal->operation = SE_DEPLACE_VERS;
        }
    }

    updateMob((t_mob*)animal, distance);

    
    return 0;
}





/* -------------------------------------------------------------------------- */
/*                                 Generation                                 */
/* -------------------------------------------------------------------------- */





/* -------------------------------------------------------------------------- */
/*                                 Destruction                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief Detruit un animal est libère la mémoire allouée pour ce dernier
 * 
 * @param animal L'adresse du pointeur de l'animal à détruire
 */
void detruireAnimal(t_animal **animal) {
    if (animal != NULL && *animal != NULL) {
        
        detruireMob((t_mob**) animal);

    }
}





/* -------------------------------------------------------------------------- */
/*                                  Creation                                  */
/* -------------------------------------------------------------------------- */


/**
 * @brief Alloue l'espace nécessaire pour un animal et le crée 
 * 
 * @param position La position à laquelle l'animal apparait
 * @param tag Le tag de l'animal qui apparait
 * 
 * @return Le pointeur sur l'animal, NULL si echec
 */
t_animal *creerAnimal(const t_vecteur2 position, const e_entiteTag tag) {
    t_mob *mob = creerMob(position);
    t_animal *animal = realloc(mob, sizeof(t_animal))    ;

    if (animal == NULL) {
        printf("Erreur mémoire : Impossible d'allouer la mémoire nécessaire pour un animal\n");
        detruireMob(&mob);
        return NULL;
    }


    // Statistiques
    animal->aggressif = FAUX;
    genererAnimal(animal, tag);

    // 
    animal->rayonDeplacement = 2;
    animal->deplacementType = DEPLACEMENT_NORMAL;

    // Animation
    animal->animation = creerAnimation(200, 2);

    // Fonctions
    animal->update = (void (*)(t_entite*, float, t_entite*)) updateAnimal;
    animal->detruire = (void (*)(t_entite**)) detruireAnimal;

    // Timer
    animal->destructionInactif = animal->aggressif;


    // Audio
    animal->bruitages = creerAudioPack();
    chargerAudioPack(animal->bruitages, animal->tag);


    if (animal->aggressif)
        ++(moteur->cache->compteurEntites.mobAggressifs);
    else
        ++(moteur->cache->compteurEntites.mobPassifs);


    mob = NULL;
    return animal;
}





/* -------------------------------------------------------------------------- */
/*                                 Apparition                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief Génère / fait apparaitre un animal au sein d'un troupeau
 * 
 * @param positionTroupeau La position du troupeau dans lequel l'animal apparait
 * @param entites Le pointeur sur la liste d'entité dans laquelle sera ajouté l'animal
 * @param map La map dans laquelle l'animal apparait
 * @param tag Le tag de l'animal qui apparait
 */
void apparitionAnimal(const t_vecteur2 positionTroupeau, t_liste *entites, t_map *map, const e_entiteTag tag) {
    t_vecteur2 position = choisirPointDansRayon(5);
    position.x += positionTroupeau.x;
    position.y += positionTroupeau.y;


    if (peutApparaitre(position, map)) {
        t_animal *animal = creerAnimal(position, tag);

        en_queue(entites);
        ajout_droit(entites, (t_entite*)animal);
    }
}



/**
 * @brief Génère / fait apparaitre un troupeau d'animaux
 * 
 * @param entites Pointeur sur la liste des entités dans laquelle les animaux seront stockés
 * @param map La map dans laquelle le troupeau apparait
 */
void apparitionTroupeau(t_liste *entites, t_map *map) {
    const int nombreTroupeau = getNombreAleatoire(8, 12);

    for (int t = 0; t < nombreTroupeau; t++) {
        const int nombreAnimaux = getNombreAleatoire(4, 8);

        t_vecteur2 positionTroupeau = {
            getNombreAleatoire(TAILLE_CHUNK, (TAILLE_MAP - 1) * TAILLE_CHUNK),
            getNombreAleatoire(TAILLE_CHUNK, (TAILLE_MAP - 1) * TAILLE_CHUNK),
        };

        const e_entiteTag tag = choisirTag();

        for (int i = 0; i < nombreAnimaux; i++) {
            apparitionAnimal(positionTroupeau, entites, map, tag);
        }
    }
}