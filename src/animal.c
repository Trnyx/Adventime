/**
 * @file animal.c
 *
 * @brief
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


e_entiteTag choisirTag() {
    return getNombreAleatoire(TAG_ANIMAL_VACHE, TAG_ANIMAL_COCHON);
}





/* -------------------------------------------------------------------------- */
/*                                Verifications                               */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param animal 
 * @return t_entite* 
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
        valeur_elt(&entitesAlentours, &entite);

        if (entite->tag == animal->tag) {
            distance = calculDistanceEntreEntites((t_entite*)animal, entite);
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


int updateAnimal(t_animal *animal, float distance, t_entiteVivante *cible) {

    t_entite *animalDuTroupeauLePlusProche = estTropLoinDuTroupeau(animal);
    
    if (animalDuTroupeauLePlusProche != NULL) {
        // printf("UPDATE VACHE TROP LOIN\n");
        const float distance = calculDistanceEntreEntites((t_entite*)animal, animalDuTroupeauLePlusProche);
        animal->operation = SE_DEPLACE_VERS;

        animal->positionDeplacement.x += (animalDuTroupeauLePlusProche->position.x - animal->position.x);
        animal->positionDeplacement.y += (animalDuTroupeauLePlusProche->position.y - animal->position.y);

        updateMob((t_mob*)animal, 0.0);
    } else {
        // printf("UPDATE VACHE\n");
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


void detruireAnimal(t_animal **animal) {
    if (animal != NULL && *animal != NULL) {
        
        detruireMob((t_mob**) animal);

    }
}





/* -------------------------------------------------------------------------- */
/*                                  Creation                                  */
/* -------------------------------------------------------------------------- */


t_animal *creerAnimal(const t_vecteur2 position, const e_entiteTag tag) {
    t_mob *mob = creerMob(position);
    t_animal *animal = realloc(mob, sizeof(t_animal))    ;

    if (animal == NULL) {
        printf("Erreur mémoire : \n");
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