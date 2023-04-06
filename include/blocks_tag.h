/**
 * @file blocks_tag.h
 *
 * @brief Module regroupant tous les blocks du jeu
 *
 * @author Clément Hibon
 * @date 10 mars
 * @version 1.1
 */





#ifndef _JEU_BLOCK_TAG_
#define _JEU_BLOCK_TAG_





/* -------------------------------------------------------------------------- */
/*                                 Enumeration                                */
/* -------------------------------------------------------------------------- */


/**
 * @struct e_blockTag
 * @brief Enumerateur répertoriant tous les "blocs" du jeu à afficher
 * 
 */
typedef enum {
    DEBUT_BLOCK_SANS_COLLISION = 49,


    DEBUT_BLOCK_STRUCTURE = 999,

    /* ---------------------------------- PUIT ---------------------------------- */
    BLOCK_PUIT_HAUT_GAUCHE,
    BLOCK_PUIT_HAUT_CENTRE,
    BLOCK_PUIT_HAUT_DROIT,
    BLOCK_PUIT_MILIEU_GAUCHE,
    BLOCK_PUIT_MILIEU_CENTRE,
    BLOCK_PUIT_MILIEU_DROIT,
    BLOCK_PUIT_BAS_GAUCHE,
    BLOCK_PUIT_BAS_CENTRE,
    BLOCK_PUIT_BAS_DROIT,



    /* ---------------------------------- PORTE --------------------------------- */
    BLOCK_PORTE,


    /* -------------------------------- MUR HAUT -------------------------------- */
    // Variant 1
    BLOCK_MUR_HAUT_GAUCHE_STANDARD,
    BLOCK_MUR_HAUT_CENTRE_STANDARD,
    BLOCK_MUR_HAUT_DROIT_STANDARD,
    // Variant 2
    BLOCK_MUR_HAUT_GAUCHE_ROUGE,
    BLOCK_MUR_HAUT_CENTRE_ROUGE,
    BLOCK_MUR_HAUT_DROIT_ROUGE,
    // Variant 3
    BLOCK_MUR_HAUT_GAUCHE_BLEU,
    BLOCK_MUR_HAUT_CENTRE_BLEU,
    BLOCK_MUR_HAUT_DROIT_BLEU,

    /* ----------------------------------- MUR ---------------------------------- */
    // Variant 1
    BLOCK_MUR_GAUCHE_STANDARD,
    BLOCK_MUR_CENTRE_STANDARD,
    BLOCK_MUR_DROIT_STANDARD,
    // Variant 2
    BLOCK_MUR_GAUCHE_ROUGE,
    BLOCK_MUR_CENTRE_ROUGE,
    BLOCK_MUR_DROIT_ROUGE,
    // Variant 3
    BLOCK_MUR_GAUCHE_BLEU,
    BLOCK_MUR_CENTRE_BLEU,
    BLOCK_MUR_DROIT_BLEU,


    /* ---------------------------------- TOIT ---------------------------------- */
    // Petit
    // LAYER 1
    //  Variant 1
    BLOCK_TOIT_PETIT_LAYER_1_1_STANDARD,
    BLOCK_TOIT_PETIT_LAYER_1_2_STANDARD,
    BLOCK_TOIT_PETIT_LAYER_1_3_STANDARD,
    BLOCK_TOIT_PETIT_LAYER_1_4_STANDARD,
    BLOCK_TOIT_PETIT_LAYER_1_5_STANDARD,
    BLOCK_TOIT_PETIT_LAYER_1_6_STANDARD,
    //  Variant 2
    BLOCK_TOIT_PETIT_LAYER_1_1_ROUGE,
    BLOCK_TOIT_PETIT_LAYER_1_2_ROUGE,
    BLOCK_TOIT_PETIT_LAYER_1_3_ROUGE,
    BLOCK_TOIT_PETIT_LAYER_1_4_ROUGE,
    BLOCK_TOIT_PETIT_LAYER_1_5_ROUGE,
    BLOCK_TOIT_PETIT_LAYER_1_6_ROUGE,
    //  Variant 3
    BLOCK_TOIT_PETIT_LAYER_1_1_BLEU,
    BLOCK_TOIT_PETIT_LAYER_1_2_BLEU,
    BLOCK_TOIT_PETIT_LAYER_1_3_BLEU,
    BLOCK_TOIT_PETIT_LAYER_1_4_BLEU,
    BLOCK_TOIT_PETIT_LAYER_1_5_BLEU,
    BLOCK_TOIT_PETIT_LAYER_1_6_BLEU,

    // LAYER 2
    //  Variant 1
    BLOCK_TOIT_PETIT_LAYER_2_1_STANDARD,
    BLOCK_TOIT_PETIT_LAYER_2_2_STANDARD,
    BLOCK_TOIT_PETIT_LAYER_2_3_STANDARD,
    BLOCK_TOIT_PETIT_LAYER_2_4_STANDARD,
    BLOCK_TOIT_PETIT_LAYER_2_5_STANDARD,
    BLOCK_TOIT_PETIT_LAYER_2_6_STANDARD,
    //  Variant 2
    BLOCK_TOIT_PETIT_LAYER_2_1_ROUGE,
    BLOCK_TOIT_PETIT_LAYER_2_2_ROUGE,
    BLOCK_TOIT_PETIT_LAYER_2_3_ROUGE,
    BLOCK_TOIT_PETIT_LAYER_2_4_ROUGE,
    BLOCK_TOIT_PETIT_LAYER_2_5_ROUGE,
    BLOCK_TOIT_PETIT_LAYER_2_6_ROUGE,
    //  Variant 3
    BLOCK_TOIT_PETIT_LAYER_2_1_BLEU,
    BLOCK_TOIT_PETIT_LAYER_2_2_BLEU,
    BLOCK_TOIT_PETIT_LAYER_2_3_BLEU,
    BLOCK_TOIT_PETIT_LAYER_2_4_BLEU,
    BLOCK_TOIT_PETIT_LAYER_2_5_BLEU,
    BLOCK_TOIT_PETIT_LAYER_2_6_BLEU,
    
    // LAYER 3
    //  Variant 1
    BLOCK_TOIT_PETIT_LAYER_3_1_STANDARD,
    BLOCK_TOIT_PETIT_LAYER_3_2_STANDARD,
    BLOCK_TOIT_PETIT_LAYER_3_3_STANDARD,
    BLOCK_TOIT_PETIT_LAYER_3_4_STANDARD,
    BLOCK_TOIT_PETIT_LAYER_3_5_STANDARD,
    BLOCK_TOIT_PETIT_LAYER_3_6_STANDARD,
    //  Variant 2
    BLOCK_TOIT_PETIT_LAYER_3_1_ROUGE,
    BLOCK_TOIT_PETIT_LAYER_3_2_ROUGE,
    BLOCK_TOIT_PETIT_LAYER_3_3_ROUGE,
    BLOCK_TOIT_PETIT_LAYER_3_4_ROUGE,
    BLOCK_TOIT_PETIT_LAYER_3_5_ROUGE,
    BLOCK_TOIT_PETIT_LAYER_3_6_ROUGE,
    //  Variant 3
    BLOCK_TOIT_PETIT_LAYER_3_1_BLEU,
    BLOCK_TOIT_PETIT_LAYER_3_2_BLEU,
    BLOCK_TOIT_PETIT_LAYER_3_3_BLEU,
    BLOCK_TOIT_PETIT_LAYER_3_4_BLEU,
    BLOCK_TOIT_PETIT_LAYER_3_5_BLEU,
    BLOCK_TOIT_PETIT_LAYER_3_6_BLEU,
    
    // LAYER 4
    //  Variant 1
    BLOCK_TOIT_PETIT_LAYER_4_1_STANDARD,
    BLOCK_TOIT_PETIT_LAYER_4_2_STANDARD,
    BLOCK_TOIT_PETIT_LAYER_4_3_STANDARD,
    BLOCK_TOIT_PETIT_LAYER_4_4_STANDARD,
    BLOCK_TOIT_PETIT_LAYER_4_5_STANDARD,
    BLOCK_TOIT_PETIT_LAYER_4_6_STANDARD,
    //  Variant 2
    BLOCK_TOIT_PETIT_LAYER_4_1_ROUGE,
    BLOCK_TOIT_PETIT_LAYER_4_2_ROUGE,
    BLOCK_TOIT_PETIT_LAYER_4_3_ROUGE,
    BLOCK_TOIT_PETIT_LAYER_4_4_ROUGE,
    BLOCK_TOIT_PETIT_LAYER_4_5_ROUGE,
    BLOCK_TOIT_PETIT_LAYER_4_6_ROUGE,
    //  Variant 3
    BLOCK_TOIT_PETIT_LAYER_4_1_BLEU,
    BLOCK_TOIT_PETIT_LAYER_4_2_BLEU,
    BLOCK_TOIT_PETIT_LAYER_4_3_BLEU,
    BLOCK_TOIT_PETIT_LAYER_4_4_BLEU,
    BLOCK_TOIT_PETIT_LAYER_4_5_BLEU,
    BLOCK_TOIT_PETIT_LAYER_4_6_BLEU,
    
    // LAYER 5
    //  Variant 1
    BLOCK_TOIT_PETIT_LAYER_5_1_STANDARD,
    BLOCK_TOIT_PETIT_LAYER_5_2_STANDARD,
    BLOCK_TOIT_PETIT_LAYER_5_3_STANDARD,
    BLOCK_TOIT_PETIT_LAYER_5_4_STANDARD,
    BLOCK_TOIT_PETIT_LAYER_5_5_STANDARD,
    BLOCK_TOIT_PETIT_LAYER_5_6_STANDARD,
    //  Variant 2
    BLOCK_TOIT_PETIT_LAYER_5_1_ROUGE,
    BLOCK_TOIT_PETIT_LAYER_5_2_ROUGE,
    BLOCK_TOIT_PETIT_LAYER_5_3_ROUGE,
    BLOCK_TOIT_PETIT_LAYER_5_4_ROUGE,
    BLOCK_TOIT_PETIT_LAYER_5_5_ROUGE,
    BLOCK_TOIT_PETIT_LAYER_5_6_ROUGE,
    //  Variant 3
    BLOCK_TOIT_PETIT_LAYER_5_1_BLEU,
    BLOCK_TOIT_PETIT_LAYER_5_2_BLEU,
    BLOCK_TOIT_PETIT_LAYER_5_3_BLEU,
    BLOCK_TOIT_PETIT_LAYER_5_4_BLEU,
    BLOCK_TOIT_PETIT_LAYER_5_5_BLEU,
    BLOCK_TOIT_PETIT_LAYER_5_6_BLEU,



    /* --------------------------------- TEMPLE --------------------------------- */
    BLOCK_TEMPLE_ENTREE_HAUT_GAUCHE,
    BLOCK_TEMPLE_ENTREE_HAUT_CENTRE,
    BLOCK_TEMPLE_ENTREE_HAUT_DROIT,
    BLOCK_TEMPLE_ENTREE_BAS_GAUCHE,
    BLOCK_TEMPLE_ENTREE_BAS_CENTRE,
    BLOCK_TEMPLE_ENTREE_BAS_DROIT,



    /* ------------------------------- DECORATIONS ------------------------------ */
    BLOCK_PIERRE,
    
    BLOCK_PANNEAU_AFFICHAGE_HAUT_GAUCHE,
    BLOCK_PANNEAU_AFFICHAGE_HAUT_DROIT,
    BLOCK_PANNEAU_AFFICHAGE_BAS_GAUCHE,
    BLOCK_PANNEAU_AFFICHAGE_BAS_DROIT,

    BLOCK_BROUETTE_HAUT_GAUCHE,
    BLOCK_BROUETTE_HAUT_DROIT,
    BLOCK_BROUETTE_BAS_GAUCHE,
    BLOCK_BROUETTE_BAS_DROIT,

    BLOCK_PANNEAU_DIRECTION,

    BLOCK_LAMPADAIRE_GAUCHE_HAUT,
    BLOCK_LAMPADAIRE_GAUCHE_BAS,
    BLOCK_LAMPADAIRE_DROIT_HAUT,
    BLOCK_LAMPADAIRE_DROIT_BAS,

    BLOCK_BANC_GAUCHE_HAUT,
    BLOCK_BANC_GAUCHE_BAS,
    BLOCK_BANC_DROIT_HAUT,
    BLOCK_BANC_DROIT_BAS,

    BLOCK_TONNEAU,
    FIN_BLOCK_DECORATION,



    /* -------------------------------- Denivelé -------------------------------- */

    DENIVELE_HAUT_GAUCHE = 1200,
    DENIVELE_HAUT_CENTRE,
    DENIVELE_HAUT_DROIT,
    DENIVELE_GAUCHE,
    DENIVELE_CENTRE,
    DENIVELE_DROIT,
    DENIVELE_BAS_GAUCHE,
    DENIVELE_BAS_CENTRE,
    DENIVELE_BAS_DROIT,
    

    FIN_BLOCK_STRUCTURE,
} e_blockTag;




/**
 * @enum e_decoration_flag
 * @brief Enumeration repertoriant les différents flags de décoration
 * 
 * Les flags de décorations autour des chemins permettent d'indiquer de facon temporelle
 * qu'une décoration sera placé à l'endroit du flag
 * 
 */
typedef enum {
    FLAG_LAMPADAIRE_GAUCHE,
    FLAG_BANC_GAUCHE,
    NB_CENTRE_FLAG_DECO,
    FLAG_LAMPADAIRE_DROIT,
    FLAG_BANC_DROIT,
    NB_FLAG_DECO,
} e_decoration_flag;





#endif
