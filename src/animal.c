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
    return TAG_ANIMAL_VACHE;
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
    t_liste entitesAlentours = getEntitesAlentour((t_entite*)animal, ENTITE_MOB, 6.0);
    
    if (liste_vide(&entitesAlentours))
        return FAUX;


    t_entite *entite = NULL;
    float distance = 0.0;

    en_tete(&entitesAlentours);
    while (!hors_liste(&entitesAlentours)) {
        valeur_elt(&entitesAlentours, &entite);

        if (entite->tag == animal->tag) {
            distance = calculDistanceEntreEntites((t_entite*)animal, entite);
            if (distance > 3.0)
                return entite;
        }

        suivant(&entitesAlentours);
    }
    
    
    return NULL;
}





/* -------------------------------------------------------------------------- */
/*                                   Update                                   */
/* -------------------------------------------------------------------------- */


int updateAnimal(t_animal *animal, float distance, t_entiteVivante *cible) {
    updateMob((t_mob*)animal, distance);


    t_entite *animalDuTroupeauLePlusProche = estTropLoinDuTroupeau(animal);
    if (animalDuTroupeauLePlusProche != NULL) {
        const float distance = calculDistanceEntreEntites((t_entite*)animal, animalDuTroupeauLePlusProche);
        animal->operation = SE_DEPLACE_VERS;

        animal->positionDeplacement.x = animal->position.x - (distance * 0.75);
        animal->positionDeplacement.y = animal->position.y - (distance * 0.75);

        updateMob((t_mob*)animal, 0.0);
    }

    
    return 0;
}





/* -------------------------------------------------------------------------- */
/*                                 Generation                                 */
/* -------------------------------------------------------------------------- */


t_animal* genererAnimal(t_animal *animal, const e_biome biome, const int niveauJoueur) {
    return animal;
}





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


t_animal *creerAnimal(const t_vecteur2 position, const e_biome biome, const e_entiteTag tag) {
    t_mob *mob = creerMob(position);
    t_animal *animal = realloc(mob, sizeof(t_animal))    ;

    if (animal == NULL) {
        printf("Erreur mémoire : \n");
        return NULL;
    }


    animal->tag = tag;

    // Statistiques
    animal->aggressif = FAUX;
    genererAnimal(animal, biome, 1);

    // 
    animal->rayonDeplacement = 4;
    animal->deplacementType = DEPLACEMENT_NORMAL;

    // Animation
    animal->animation = creerAnimation(150, 2);

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


void apparitionAnimal(const t_vecteur2 positionTroupeau, t_liste *entites, t_map *map) {
    t_vecteur2 position = choisirPointDansRayon(5);
    position.x += positionTroupeau.x;
    position.y += positionTroupeau.y;


}



void apparitionTroupeau(t_liste *entites, t_map *map) {
    const float rayon = JOUEUR_RAYON_INACTIF - JOUEUR_RAYON_SEMIACTIF;
    t_vecteur2 positionTroupeau = choisirPointDansRayon(rayon);
    const int nombreAnimaux = getNombreAleatoire(4, 8);


    for (int i = 0; i < nombreAnimaux; i++) {
        apparitionAnimal(positionTroupeau, entites, map);
    }



}