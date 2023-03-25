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
 * @return un pointeur sur l'entité d'un animal se situant dans le troupeau lorque l'animal que l'on vérifie se situe trop loin du troupeau
 */
t_entite* estTropLoinDuTroupeau(t_animal *animal) {
    t_liste entitesAlentours = getEntitesAlentour((t_entite*)animal, ENTITE_MOB, ANIMAL_RAYON_DETECTION_TROUPEAU);
    
    if (liste_vide(&entitesAlentours))
        return NULL;


    t_entite *entiteTempo = NULL;
    t_entite *entite = NULL;
    float distance = 0.0;

    en_tete(&entitesAlentours);
    while (!hors_liste(&entitesAlentours)) {
        valeur_elt(&entitesAlentours, &entiteTempo);

        if (entiteTempo->tag == animal->tag) {
            distance = calculDistanceEntreEntites((t_entite*)animal, entiteTempo);

            if (distance <= ANIMAL_RAYON_TROP_LOIN_TROUPEAU)
                return NULL;
            else 
                entite = entiteTempo;
        }

        suivant(&entitesAlentours);
    }
    
    
    return entite;
}





/* -------------------------------------------------------------------------- */
/*                                   Update                                   */
/* -------------------------------------------------------------------------- */


/**
 * @brief Actualise un animal
 * 
 * Toute la logique propre à un animal est gérer dans cette fonction
 * 
 * @param animal Pointeur sur l'animal à actualiser
 * @param distance La distance entre l'animal est le joueur
 * @param cible 
 * 
 * @return int 
 */
int updateAnimal(t_animal *animal, float distance, t_entiteVivante *cible) {

    t_entite *animalDuTroupeauLePlusProche = estTropLoinDuTroupeau(animal);
    
    if (animalDuTroupeauLePlusProche != NULL) {
        printf("UPDATE ANIMAL TROP LOIN => ");
        // const float distance = calculDistanceEntreEntites((t_entite*)animal, animalDuTroupeauLePlusProche);

        // animal->positionDeplacement.x += (animal->position.x - animalDuTroupeauLePlusProche->position.x);
        // animal->positionDeplacement.y += (animal->position.y - animalDuTroupeauLePlusProche->position.y);
        animal->positionDeplacement.x = animalDuTroupeauLePlusProche->position.x;
        animal->positionDeplacement.y = animalDuTroupeauLePlusProche->position.y;

        animal->operation = SE_DEPLACE_VERS;

        updateMob((t_mob*)animal, distance);
    } else {
        // printf("UPDATE ANIMAL\n");
        updateMob((t_mob*)animal, distance);
    }

    // printf("ANIMAL (%s) => déplacement : %i / opération : %i \n", animal->id, animal->deplacementType, animal->operation);
    //     updateMob((t_mob*)animal, distance);

    
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
 * @param animal L'adrese du pointeur de l'animal à détruire
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
    animal->update = (int (*)(t_entite*, float, t_entite*)) updateAnimal;
    animal->detruire = (void (*)(t_entite**)) detruireAnimal;

    // Timer
    animal->destructionInactif = animal->aggressif;


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
    printf("APPARITION ANIMAL => ");
    t_vecteur2 position = choisirPointDansRayon(5);
    position.x += positionTroupeau.x;
    position.y += positionTroupeau.y;


    if (peutApparaitre(position, map)) {
        printf("APPARAIT ");
        t_animal *animal = creerAnimal(position, tag);

        en_queue(entites);
        ajout_droit(entites, (t_entite*)animal);
    }
    else {
        printf("PEUT PAS APPARAITRE\n");
    }
}



/**
 * @brief Génère / fait apparaitre un troupeau d'animaux
 * 
 * @param entites Pointeur sur la liste des entités dans laquelle les animaux seront stockés
 * @param map La map dans laquelle le troupeau apparait
 */
void apparitionTroupeau(t_liste *entites, t_map *map) {
    printf("APPARTITION TROUPEAU => ");

    const int nombreTroupeau = getNombreAleatoire(8, 12);

    for (int t = 0; t < nombreTroupeau; t++) {
        const int nombreAnimaux = getNombreAleatoire(4, 8);
        printf("NOMBRE ANIMAUX %i => ", nombreAnimaux);

        t_vecteur2 positionTroupeau = {
            getNombreAleatoire(TAILLE_CHUNK, (TAILLE_MAP - 1) * TAILLE_CHUNK),
            getNombreAleatoire(TAILLE_CHUNK, (TAILLE_MAP - 1) * TAILLE_CHUNK),
        };

        const e_entiteTag tag = choisirTag();

        printf("TROUPEAU %i => ", t);
        printf("POSITION TROUPEAU %1.2f:%1.2f => (%i) \n", positionTroupeau.x, positionTroupeau.y, tag);

        for (int i = 0; i < nombreAnimaux; i++) {
            apparitionAnimal(positionTroupeau, entites, map, tag);
        }
        
        printf("\n");
    }
}