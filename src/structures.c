/**
 * @file structures.c
 *
 * @brief 
 *
 * @author Clément Hibon
 * @date 10 mars
 * @version 1.1
 */





#include <stdlib.h>
#include <stdio.h>

#include "../include/structures.h"
#include "../include/disc_sampling.h"





/* -------------------------------------------------------------------------- */
/*                                 Validation                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief Vérifie que le chunk donné est conforme pour la génération d'un village
 * 
 * @param chunk Le chunk qui doit être vérifié
 * 
 * @return 1 si valide, 0 sinon / Cas particulier : -1 => cas bannis
 */
int biomeValidationPourVillage(t_chunk *chunk) {
    if (chunk->biome <= BIOME_LAC) return -1;
    else return chunk->biome == BIOME_PLAINE || chunk->biome == BIOME_FORET;
}



/**
 * @brief Vérifie que le chunk donné est conforme pour la génération de l'entré du temple
 * 
 * @param chunk Le chunk qui doit être vérifié
 * 
 * @return 1 si valide, 0 sinon
 */
int biomeValidationPourEntreeTemple(t_chunk *chunk) {
    return chunk->biome == BIOME_MONTAGNE;
}





/* -------------------------------------------------------------------------- */
/*                                     Get                                    */
/* -------------------------------------------------------------------------- */


/**
 * @brief Permet d'obtenir le chunk central correspondant à la condition
 * 
 * @param biome Le biome du chunk recherché
 * @param map La map dans lequel on recherche le chunk
 * @param validation Un pointeur sur la fonction de validation, cette fonction de validation doit retourner 1 pour un cas valide, 0 pour un cas non valide, -1 pour un cas banni (interdisant donc la sélection du chunk regardé)
 * 
 * @return t_chunk* Le chunk correspondant le plus à la condition de validation
 */
t_chunk* getChunkCentralBiome(const e_biome biome, t_map *map, int (*validation)(t_chunk*)) {
    t_chunk *chunkFinal = NULL;
    int max = 0;
    int compteur = 0;


    for (int x = 0; x < TAILLE_MAP; x++) {
        for (int y = 0; y < TAILLE_MAP; y++) {
            t_chunk *chunk = getChunk(x, y, COUCHE_SOL, map);


            if (chunk == NULL) continue;

            if (chunk->biome == biome) {
                for (int xChunk = chunk->position.x - 1; xChunk <= chunk->position.x + 1; xChunk++) {
                    for (int yChunk = chunk->position.y - 1; yChunk <= chunk->position.y + 1; yChunk++) {
                        if (xChunk == chunk->position.x && yChunk == chunk->position.y) continue;
                        t_chunk *chunkTempo = getChunk(xChunk, yChunk, COUCHE_SOL, map);

                        int valide = validation(chunkTempo);

                        // Si le biome trouvé est un biome interdisant l'apparition
                        // on met le compteur avec un nombre négatif pour être sûr
                        // que le chunk ne soit pas sélectionné
                        if (valide == -1)
                            compteur = -8;
                        else if (valide)
                            ++compteur;
                    }
                }


                if (compteur >= max) {
                    max = compteur;
                    chunkFinal = chunk;
                }

                compteur = 0;
            }
        }
    }
    

    printf("CHUNK FINAL : %.2f:%.2f (%i)\n", chunkFinal->position.x, chunkFinal->position.y, chunkFinal->biome);
    return chunkFinal;
}





/* -------------------------------------------------------------------------- */
/*                                   Village                                  */
/* -------------------------------------------------------------------------- */


/**
 * @brief Sélectionne un tag d'une maison
 * 
 * @return Le tag de la maison choisi
 */
e_structureTag selectionMaisonTag() {
    return getNombreAleatoire(STRUCTURE_PETITE_MAISON_1, STRUCTURE_PETITE_MAISON_3);
}





/* ------------------------------- Decorations ------------------------------ */


/**
 * @brief Vérifie si la décoration peut être placé
 * 
 * @param map La map dans laquelle on souhaite placé la décoration
 * @param positionX La coordonné x (relative à la map) à laquelle doit être placé la décoration (angle en haut à gauche)
 * @param positionY La coordonné y (relative à la map) à laquelle doit être placé la décoration (angle en haut à gauche)
 * @param largeur La largeur de la décoration
 * @param hauteur La hauteur de la décoration
 * 
 * @return VRAI si la décoration peut être placé, FAUX sinon
 */
boolean peutEtrePlacer(t_map* map, const float positionX, const float positionY, const int largeur, const int hauteur) {
    t_block *block = NULL;

    for (int x = positionX; x < positionX + largeur; x++) {
        for (int y = positionY; y < positionY + hauteur; y++) {
            block = getBlockDansMap(x, y, COUCHE_OBJETS, map);
            if (block->tag != VIDE && block->tag >= NB_FLAG_DECO)
                return FAUX;

            block = getBlockDansMap(x, y, COUCHE_SOL, map);
            if (block->tag <= SOL_EAU || block->tag == SOL_CHEMIN)
                return FAUX;
        }
    }

    return VRAI;
}





/**
 * @brief Choisis un flag de décoration
 * 
 * @param cote De quel côté se trouve la décoration, 0 à gauche, 1 à droite
 * 
 * @return Le flag de la décoration qui sera placé
 */
e_decoration_flag choisirFlagDecoAutourDeChemin(const int cote) {
    const int decorationFlag = getNombreAleatoire(0, NB_CENTRE_FLAG_DECO - 1);

    if (cote == 0) 
        return decorationFlag;
    else 
        return decorationFlag + NB_CENTRE_FLAG_DECO + 1;
}





/**
 * @brief Choisit une position pour une décoration autour d'un point central
 * 
 * @param map La map dans laquelle sera placé la décoration
 * @param centre Le point central autour duquel doit être placé la décoration
 * @param largeur La largeur de la décoration
 * @param hauteur La hauteur de la décoration
 * @param rayon Le rayon autour duquel doit être placé la décoration
 * 
 * @return La position de la décoration
 */
t_vecteur2 choisirPositionDecorationAutourDePoint(t_map *map, const t_vecteur2 centre, const int largeur, const int hauteur, const int rayon) {
    t_vecteur2 position = choisirPointDansRayon(rayon);
    position.x += centre.x;
    position.y += centre.y;


    if (peutEtrePlacer(map, position.x, position.y, largeur, hauteur))
        return position;
    else
        return choisirPositionDecorationAutourDePoint(map, centre, largeur, hauteur, rayon);
}



/**
 * @brief Construit une décoration autour d'un point donné
 * 
 * @param map La map dans laquelle sera placé la décoration
 * @param blockDecoration Le block de départ de la décoration
 * @param centre Le point autour duquel la décoration doit être construite
 * @param largeur La largeur de la décoration
 * @param hauteur La hauteur de la décoration
 * @param rayon Le rayon autour duquel doit être placé la décoration
 * 
 * @return La position de la décoration 
 */
t_vecteur2 decorationAutourDePoint(t_map *map, const e_blockTag blockDecoration, const t_vecteur2 centre, const int largeur, const int hauteur, const int rayon) {
    t_vecteur2 positionObjet = choisirPositionDecorationAutourDePoint(map, centre, largeur, hauteur, rayon);
    
    
    for (int i = 0, y = positionObjet.y; y < positionObjet.y + largeur; y++) {
        for (int x = positionObjet.x; x < positionObjet.x + hauteur; x++) {
            t_block *block = getBlockDansMap(x, y, COUCHE_OBJETS, map);
            block->tag = blockDecoration + i++;
        }
    }


    return positionObjet;
}





/**
 * @brief Remplace les flags de décorations
 * 
 * Les flags doivent être placé au préalables
 * 
 * @param map La map dans laquelle les flags seront remplacé
 */
void decorationRemplacerFlags(t_map *map) {
    for (int x = 0; x < TAILLE_MAP * TAILLE_CHUNK; x++) {
        for (int y = 0; y < TAILLE_MAP * TAILLE_CHUNK; y++) {

            t_block *block = getBlockDansMap(x, y, COUCHE_OBJETS, map);
            

            switch (block->tag) {
                case FLAG_LAMPADAIRE_GAUCHE:
                    if (peutEtrePlacer(map, block->position.x, block->position.y - 1, 1, 2)) {
                        block->tag = BLOCK_LAMPADAIRE_GAUCHE_BAS;
                        block = getBlockDansMap(x, y - 1, COUCHE_OBJETS, map);
                        block->tag = BLOCK_LAMPADAIRE_GAUCHE_HAUT;
                    }
                    break;
                case FLAG_LAMPADAIRE_DROIT:
                    if (peutEtrePlacer(map, block->position.x, block->position.y - 1, 1, 2)) {
                        block->tag = BLOCK_LAMPADAIRE_DROIT_BAS;
                        block = getBlockDansMap(x, y - 1, COUCHE_OBJETS, map);
                        block->tag = BLOCK_LAMPADAIRE_DROIT_HAUT;
                    }
                    break;


                case FLAG_BANC_GAUCHE:
                    if (peutEtrePlacer(map, block->position.x, block->position.y - 1, 1, 2)) {
                        block->tag = BLOCK_BANC_GAUCHE_BAS;
                        block = getBlockDansMap(x, y - 1, COUCHE_OBJETS, map);
                        block->tag = BLOCK_BANC_GAUCHE_HAUT;
                    }
                    break;
                case FLAG_BANC_DROIT:
                    if (peutEtrePlacer(map, block->position.x, block->position.y - 1, 1, 2)) {
                        block->tag = BLOCK_BANC_DROIT_BAS;
                        block = getBlockDansMap(x, y - 1, COUCHE_OBJETS, map);
                        block->tag = BLOCK_BANC_DROIT_HAUT;
                    }
                    break;

                
                default:
                    break;
            }
            
        }
    }
}





/**
 * @brief Génère les décorations d'un village
 * 
 * @param map La map dans laquelle les décorations sont générées
 * @param grille La grille contenant la position des maisons du village
 */
void genererDecorations(t_map *map, t_discSampling grille) {
    printf("DECORATINONS => ");
    // Flags
    decorationRemplacerFlags(map);

    
    /* ---------------------------------- Puit ---------------------------------- */

    if (grille.nbElements > 1) {
        const t_vecteur2 positionPuit = grille.elementPositions[0];

        // Panneau d'affichage
        decorationAutourDePoint(map, BLOCK_PANNEAU_AFFICHAGE_HAUT_GAUCHE, positionPuit, 2, 2, 5);
        // Brouette
        decorationAutourDePoint(map, BLOCK_BROUETTE_HAUT_GAUCHE, positionPuit, 2, 2, 6);
    }


    /* ---------------------------------- Ferme --------------------------------- */

    const int numeroMaison = getNombreAleatoire(1, grille.nbElements - 1);
    t_vecteur2 positionFerme = grille.elementPositions[numeroMaison];
    positionFerme.y += 6;
    const int nombreTonneaux = getNombreAleatoire(2, 4);

    const t_vecteur2 tonneau = decorationAutourDePoint(map, BLOCK_TONNEAU, positionFerme, 1, 1, 3);
    for (int i = 0; i < nombreTonneaux; i++) {
        decorationAutourDePoint(map, BLOCK_TONNEAU, tonneau, 1, 1, 1);
    }



    printf("\n");
}





/* --------------------------------- Chemins -------------------------------- */

/**
 * @brief Change le tag du block se trouvant aux coordonnées données
 * 
 * @param map La map dans laquelle le block est changer
 * @param x La coordonnée x (relative à la map) du block à changer
 * @param y La coordonnée y (relative à la map) du block à changer
 * @param z La coordonnée z (relative à la map) du block à changer
 * @param nouveauBlock Le tag du nouveau block
 */
void changerBlock(t_map *map, const float x, const float y, const int z, const int nouveauBlock) {
    t_block *block = getBlockDansMap(x, y, z, map);
    block->tag = nouveauBlock;
}





/**
 * @brief Trace un chemin vertical
 * 
 * @param map La map dans laquelle sera créé le chemin
 * @param depart Le point de départ original
 * @param arrive Le point d'arriver original
 * @param x 
 * @param y 
 */
void tracerCheminVertical(t_map *map, t_vecteur2 depart, t_vecteur2 arrive, int *x, int *y) {
    const int longueur = abs(depart.y - arrive.y);
    const int nombreDecoration = getNombreAleatoire(1, 3);

    int yParcourue = 0;
    int cote, modifieur;

    // Maison en haut
    if (depart.y > arrive.y) {
        for (; *y < depart.y; (*y)++) {
            changerBlock(map, *x, *y, COUCHE_SOL, SOL_CHEMIN);
            
            // On place des décoration le long du chemin
            if (yParcourue == longueur / nombreDecoration) {
                yParcourue = 0;

                // Choisis le côté du chemin 0 pour gauche, 1 pour droite
                cote = getNombreAleatoire(0, 1);
                e_decoration_flag flag = choisirFlagDecoAutourDeChemin(cote);

                modifieur = cote ? 1 : -1;
                changerBlock(map, *x + modifieur, *y, COUCHE_OBJETS, flag);
            }
            
            ++yParcourue;
        }
    }

    // Maison en bas
    else {
        for (; *y > depart.y + 2; (*y)--) {
            changerBlock(map, *x, *y, COUCHE_SOL, SOL_CHEMIN);
            
            // On place des décoration le long du chemin
            if (yParcourue == longueur / nombreDecoration) {
                yParcourue = 0;

                // Choisis le côté du chemin 0 pour gauche, 1 pour droite
                cote = getNombreAleatoire(0, 1);
                e_decoration_flag flag = choisirFlagDecoAutourDeChemin(cote);

                modifieur = cote ? 1 : -1;
                changerBlock(map, *x + modifieur, *y, COUCHE_OBJETS, flag);
            }   

            ++yParcourue;
        }
    }
}



/**
 * @brief 
 * 
 * @param map La map dans laquelle est tracée les chemins
 * @param depart Le point de départ pour la création du chemin (Le puit)
 * @param arrive Le point d'arrive de la création du chemin (La maison)
 */
void tracerChemin(t_map *map, t_vecteur2 depart, t_vecteur2 arrive) {
    t_vecteur2 separation = {
        depart.x - arrive.x,
        depart.y - arrive.y,
    };
    

    int x = arrive.x;
    int y = arrive.y + 7;
    

    // Maison à gauche
    if (separation.x > 0) { 
        x += 2;

        // On trace la moitié du chemin horizontal
        for (; x < arrive.x + (separation.x / 2); x++)
            changerBlock(map, x, y, COUCHE_SOL, SOL_CHEMIN);
        
        // Indique qu'il y aura un lampadaire en bout de chemin
        changerBlock(map, x+1, y, COUCHE_OBJETS, FLAG_LAMPADAIRE_DROIT);

        // On trace la totalité du chemin vertical
        tracerCheminVertical(map, depart, arrive, &x, &y);

        // Indique qu'il y aura un lampadaire en bout de chemin
        changerBlock(map, x-1, y, COUCHE_OBJETS, FLAG_LAMPADAIRE_GAUCHE);
        
        // On finit de tracer le chemin vertical
        for (; x < depart.x; x++)
            changerBlock(map, x, y, COUCHE_SOL, SOL_CHEMIN);

    } 


    // Maison à droite ou alignée horizontalement
    else { 
        x += 4;

        // On trace la moitié du chemin horizontal
        for (; x > arrive.x + (separation.x / 2); x--)
            changerBlock(map, x, y, COUCHE_SOL, SOL_CHEMIN);
        
        // Indique qu'il y aura un lampadaire en bout de chemin
        changerBlock(map, x-1, y, COUCHE_OBJETS, FLAG_LAMPADAIRE_GAUCHE);

        // On trace la totalité du chemin vertical
        tracerCheminVertical(map, depart, arrive, &x, &y);

        // Indique qu'il y aura un lampadaire en bout de chemin
        changerBlock(map, x+1, y, COUCHE_OBJETS, FLAG_LAMPADAIRE_DROIT);
        
        // On finit de tracer le chemin vertical
        for (; x > depart.x + 2; x--)
            changerBlock(map, x, y, COUCHE_SOL, SOL_CHEMIN);
        
    }
    
}



/**
 * @brief Génère les chemins d'un village
 * 
 * @param map La map dans laquelle les chemins sont générées
 * @param grille La grille contenant la position des maisons du village
 */
void genererChemins(t_map *map, t_discSampling grille) {
    t_vecteur2 positionPuit = grille.elementPositions[0];


    // Relie les maisons au puit
    for (int i = 1; i < grille.nbElements; i++) {
        t_vecteur2 point = grille.elementPositions[i];

        tracerChemin(map, positionPuit, point);
    }


    // Entoure le puit de dalle
    for (int x = positionPuit.x - 1; x <= positionPuit.x + 3; x++) {
        for (int y = positionPuit.y - 1; y <= positionPuit.y + 3; y++) {
            changerBlock(map, x, y, COUCHE_SOL, SOL_CHEMIN);
            changerBlock(map, x, y, COUCHE_OBJETS, VIDE);
        }
    }

}










/**
 * @brief Génère un village
 * 
 * @param map La map dans laquelle est généré le village
 */
void genererVillage(t_map *map) {
    printf("GENERATION VILLAGE => ");
    t_chunk *plusGrandePlaine = getChunkCentralBiome(BIOME_PLAINE, map, biomeValidationPourVillage);


    if (plusGrandePlaine != NULL) {
        const t_vecteur2 centre = {
            (plusGrandePlaine->position.x * TAILLE_CHUNK) + TAILLE_CHUNK / 2,
            (plusGrandePlaine->position.y * TAILLE_CHUNK) + TAILLE_CHUNK / 2,
        };
        
        const t_vecteur2 min = { centre.x - (TAILLE_CHUNK), centre.y - (TAILLE_CHUNK) };
        const t_vecteur2 max = { centre.x + (TAILLE_CHUNK), centre.y + (TAILLE_CHUNK) };

        const int nombreBatiment = getNombreAleatoire(6, 8);
        

        printf("GENERATION GRILLE => ");
        const t_discSampling grille = genererGrilleDiscSampling(min, max, nombreBatiment, 12, &centre);
        // grille.elementPositions[0] = centre;


        if (grille.nbElements > 1) {
            genererChemins(map, grille);
        }


        printf("NOMBRE STRUCTURE %i => ", grille.nbElements);
        for (int i = 0; i < grille.nbElements; i++) {
            t_vecteur2 position = grille.elementPositions[i];
            e_structureTag tag = selectionMaisonTag();

            if (!i && grille.nbElements > 1) {
                printf("GENERATION PUIT %i (%1.2f:%1.2f) => ", i, position.x, position.y);
                genererStructure(position, STRUCTURE_PUIT, map);
            }
            else {
                printf("GENERATION BATIMENT %i (%1.2f:%1.2f) => ", i, position.x, position.y);
                genererStructure(position, tag, map);
            }
        }

        genererDecorations(map, grille);



        free(grille.elementPositions);

    }

    printf("\n\n");
}





/* -------------------------------------------------------------------------- */
/*                                   Temple                                   */
/* -------------------------------------------------------------------------- */



/**
 * @brief Génère l'entrée du temple du boss
 * 
 * @param map La map dans laquelle l'entrée du boss est généré
 */
void genererEntreeTemple(t_map *map) {
    printf("GENERATION ENTREE TEMPLE => ");
    t_chunk *plusGrandeMontagne = getChunkCentralBiome(BIOME_MONTAGNE, map, biomeValidationPourEntreeTemple);


    if (plusGrandeMontagne != NULL) {
        const t_vecteur2 centre = {
            (plusGrandeMontagne->position.x * TAILLE_CHUNK) + TAILLE_CHUNK / 2,
            (plusGrandeMontagne->position.y * TAILLE_CHUNK) + TAILLE_CHUNK / 2,
        };

        printf("%1.2f:%1.2f => ", centre.x, centre.y);
        genererStructure(centre, STRUCTURE_ENTREE_TEMPLE, map);
    }
    printf("\n");
}





/* -------------------------------------------------------------------------- */
/*                                   Caverne                                  */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param map 
 */
void genererEntreeCaverne(t_map *map) {
    printf("GENERATION ENTREE Caverne => ");

    
    printf("\n");
}

