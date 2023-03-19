/**
 * @file disc_sampling.c
 *
 * @brief Génération de "Poisson Disc Sampling"
 * 
 * Poisson Disc Sampling est une technique permettant de sélectionner de manière aléatoire des points serrés de façon à ce qu'ils respectent une distance minimale 
 * Comme les points sont choisis de façon aléatoire, le résultat a un aspect plus organique
 * 
 * 1. Un premier point est généré aléatoirement et est stocké dans un tableau
 * 2. 
 * 
 * 
 * @author Clément Hibon
 * @date 15 mars
 * @version 1.1
 */





#include <stdlib.h>
#include <stdio.h>

#include "../include/disc_sampling.h"





/**
 * @brief Vérifie si le point à placer est un point valide
 * 
 * @param elementsExistant Tableau des éléments déjà existant
 * @param nombreElementsExistant Le nombre d'élément déjà existant
 * @param nouveauPoint Le point à créer 
 * @param rayon Le rayon minimum autorisé 
 * 
 * @return VRAI si le point peut être placé, FAUX sinon
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
 * @brief Créer un nouveau point aléatoire entre les coordonnées min et max données
 * 
 * @param min Les coordonnées x et y minimum
 * @param max Les coordonnées x et y maximum
 * 
 * @return La position du nouveau point
 */
t_vecteur2 creerNouveauPoint(t_vecteur2 min, t_vecteur2 max) {
    t_vecteur2 nouveauPoint = {
        getNombreAleatoire(min.x, max.x),
        getNombreAleatoire(min.y, max.y),
    };

    return nouveauPoint;
}



/**
 * @brief Ajouter un nouveau point dans la grille
 * 
 * @param grille La grille contenant tous les points
 * @param nouveauPoint Le point à ajouter
 * @param i 
 */
void ajouterPoint(t_discSampling *grille, const t_vecteur2 nouveauPoint, const int i) {
    grille->elementPositions[i] = nouveauPoint;
    (grille->nbElements)++;
}





/**
 * @brief Génère une grille / un tableau de point
 * 
 * Ces points sont généré de sorte à ce qu'ils suivent l'algorithme "Poisson Disc Sampling"
 * 
 * @param minGrille Les coordonnées x et y minimum de la grille
 * @param maxGrille Les coordonnées x et y maximum de la grille
 * @param nbElementsObjectif Le nombre d'éléments souhaité (ils ne seront pas tous créés)
 * @param rayon Le rayon minimum de placement
 * 
 * @return La grille de points
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