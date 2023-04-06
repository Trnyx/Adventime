/**
 * @file stockage.h
 * 
 * @brief Module de gestion du stockage
 * 
 * @author Clément Hibon
 * @date 24 mars
 * @version 1.1
 */





#ifndef _JEU_STOCKAGE_
#define _JEU_STOCKAGE_





#include "item.h"





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @struct t_itemSlot
 * @brief Structure modélisant un slot d'un stockage
 * 
 */
typedef struct s_itemSlot {
    int slot;                   /**< Le numéro du slot */

    t_item *item;               /**< L'item contenue dans le slot (à voir si c'est un pointeur) */
    int quantite;               /**< Le nombre d'item contenue dans le slot */

    // boolean estSelectionne;
} t_itemSlot;




/**
 * @struct t_stockage
 * @brief Structure modélisant la base d'un inventaire
 * 
 */
typedef struct s_stockage {
    int nbSlots;                /**< Le nombre de slots dans le stockage */
    // int nbSlotsMax;          /**< Le nombre de slots maximal que peut avoir le stockage */
    t_itemSlot *itemSlots;      /**< La liste des slots dans le stockage */
} t_stockage;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


boolean stockageEstVide(t_stockage *stockage);

t_stockage* creerStockage(const unsigned int nbSlots);

void transfererStockage(t_stockage *source, t_stockage *cible);
void viderStockage(t_stockage *stockage);

void detruireSlot(t_itemSlot *slot);
void detruireStockage(t_stockage **stockage);






#endif