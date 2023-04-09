/**
 * @file inventaire.h
 * 
 * @brief Module de manipulation de l'inventaire
 * 
 * @author Clément Hibon
 * @date 24 mars
 */



#ifndef _JEU_INVENTAIRE_
#define _JEU_INVENTAIRE_





#include "stockage.h"





#define NOMBRE_SLOT_INVENTAIRE 36





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @struct t_extensionInventaire
 * @brief Structure modélisant une extension d'inventaire
 * 
 */
typedef struct s_extensionInventaire {
    struct s_stockage;      /**< Les infos de stockage de l'extension */
} t_extensionInventaire;




/**
 * @struct t_inventaire
 * @brief Structure modélisant l'inventaire
 * 
 */
typedef struct s_inventaire {
    struct s_stockage;                /**< "Etend" la structure stockage */

    // Extensions d'inventaire
    // struct s_extensionInventaire extension;    // un sac ou une petite sacoche pour avoir plus de slots disponible 
} t_inventaire;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */

typedef struct s_joueur t_joueur;



t_inventaire* creerInventaire();

void recupererItem(t_itemEntite *itemEntite, t_joueur *recuperateur);

void detruireInventaire(t_inventaire **inventaire);





#endif 
