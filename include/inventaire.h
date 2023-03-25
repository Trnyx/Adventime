/**
 * @file inventaire.h
 * 
 * @brief 
 * 
 * @author Clément Hibon
 * @date 24 mars
 * @version 1.1
 */



#ifndef _JEU_INVENTAIRE_
#define _JEU_INVENTAIRE_





#include "item.h"





#define NOMBRE_SLOT_INVENTAIRE 6





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
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
 * @brief Structure modélisant la base d'un inventaire
 * 
 */
typedef struct s_stockage {
    int nbSlots;                /**< Le nombre de slots dans le stockage */
    // int nbSlotsMax;             /**< Le nombre de slots maximal que peut avoir le stockage */
    t_itemSlot *itemSlots;      /**< La liste des slots dans le stockage */
} t_stockage;



/**
 * @brief 
 * 
 */
typedef struct s_extensionInventaire {
    struct s_stockage;      /**< Les infos de stockage de l'extension */
} t_extensionInventaire;




typedef struct s_inventaire {
    struct s_stockage;                // Les infos de stockage pour l'inventaire

    // Extensions d'inventaire
    // struct s_extensionInventaire extension;    // un sac ou une petite sacoche pour avoir plus de slots disponible 
} t_inventaire;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


// void changerSlot();


t_stockage* creerStockage(const unsigned int nbSlots);
t_inventaire* creerInventaire();

void viderStockage(t_stockage *stockage);

void detruireSlot(t_itemSlot **slot);
void detruireStockage(t_stockage **stockage);
void detruireInventaire(t_inventaire **inventaire);




#endif 