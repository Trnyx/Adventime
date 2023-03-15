/**
 * @file disc_sampling.c
 *
 * @brief
 *
 * @author Clément Hibon
 * @date 15 mars
 * @version 1.1
 */





#include <stdlib.h>
#include <stdio.h>

#include "../include/disc_sampling.h"





/**
 * @brief 
 * 
 * @param elementsExistant 
 * @param nombreElementsExistant 
 * @param nouveauPoint 
 * @param rayon 
 * @return int 
 */
boolean pointValide(t_vecteur2 elementsExistant[], const int nombreElementsExistant, const t_vecteur2 nouveauPoint, const float rayon) {
    int k = 20;


    for (int i = 0; i < nombreElementsExistant; i++) {
        t_vecteur2 pointExistant = elementsExistant[i];
        const float distance = calculDistanceEntrePoints(pointExistant, nouveauPoint);
        
        // printf("DISTANCE : %.2f  |  RAYON : %.2f / %.2f", distance, rayon, rayon * 2);
    
        if (distance >= rayon && distance <= rayon * 2) {
            // printf(" => OK\n");
            return VRAI;      
        }
        // else
            // printf("\n");
        --k;
        if (!k)
            return FAUX;
    }

    
    return FAUX;
}





/**
 * @brief 
 * 
 * @param min 
 * @param max 
 * @return t_vecteur2 
 */
t_vecteur2 creerNouveauPoint(t_vecteur2 min, t_vecteur2 max) {
    t_vecteur2 nouveauPoint = {
        getNombreAleatoire(min.x, max.x),
        getNombreAleatoire(min.y, max.y),
    };

    return nouveauPoint;
}



/**
 * @brief 
 * 
 * @param grille 
 * @param nouveauPoint 
 * @param i 
 */
void ajouterPoint(t_discSampling *grille, const t_vecteur2 nouveauPoint, const int i) {
    grille->elementPositions[i] = nouveauPoint;
    (grille->nbElements)++;
}





/**
 * @brief 
 * 
 * @param minGrille 
 * @param maxGrille 
 * @param nbElementsObjectif 
 * @param rayon 
 * @return t_discSampling 
 */
t_discSampling genererGrilleDiscSampling(const t_vecteur2 minGrille, const t_vecteur2 maxGrille, int nbElementsObjectif, float rayon) {
    t_discSampling grille;

    grille.minGrille = minGrille;
    grille.maxGrille = maxGrille;
    grille.elementPositions = calloc(nbElementsObjectif, sizeof(t_vecteur2));
    grille.nbElements = 0;


    // t_vecteur2 nouveauPoint = { 
    //     (minGrille.x + maxGrille.x) / 2,
    //     (minGrille.y + maxGrille.y) / 2,
    // };
    t_vecteur2 nouveauPoint = creerNouveauPoint(minGrille, maxGrille);
    ajouterPoint(&grille, nouveauPoint, 0);

    
    for (int i = 1; i < nbElementsObjectif; i++) {
        nouveauPoint = creerNouveauPoint(minGrille, maxGrille);

        if (pointValide(grille.elementPositions, grille.nbElements, nouveauPoint, rayon)) {
            ajouterPoint(&grille, nouveauPoint, i);
        }
        else {
            // --i;
        }

    }


    grille.elementPositions = realloc(grille.elementPositions, sizeof(t_vecteur2) * grille.nbElements);
    
    return grille;
}