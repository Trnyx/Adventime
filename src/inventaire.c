/**
 * @file inventaire.c
 * 
 * @brief 
 * 
 * @author Clément Hibon
 * @date 24 mars
 * @version 1.1
 */



#include <stdlib.h>
#include <stdio.h>

#include "../include/joueur.h"
#include "../include/inventaire.h"





/* -------------------------------------------------------------------------- */
/*                               Initialisation                               */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param index 
 * @return t_itemSlot 
 */
t_itemSlot initItemSlot(int index) {
    t_itemSlot itemSlot;


    itemSlot.slot = index;

    itemSlot.item = NULL;
    itemSlot.quantite = 0;


    return itemSlot;
}





/**
 * @brief 
 * 
 * @param nbSlots 
 * @return t_stockage 
 */
t_stockage* creerStockage(unsigned int nbSlots) {
    t_stockage *stockage = malloc(sizeof(t_stockage));


    stockage->nbSlots = nbSlots;
    stockage->itemSlots = calloc(nbSlots, sizeof(t_itemSlot));

    for (int i = 0; i < nbSlots; i++) {
        stockage->itemSlots[i] = initItemSlot(i);
    }


    return stockage;
}





t_inventaire creerInventaire() {
    t_stockage *stockage = creerStockage(NOMBRE_SLOT_INVENTAIRE);
    t_inventaire *inventaire = realloc(stockage, sizeof(t_inventaire));



    stockage = NULL;
    return inventaire;
}