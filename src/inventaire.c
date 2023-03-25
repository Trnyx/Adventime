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
/*                                Gestionnaire                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param source 
 * @param cible 
 */
void transfererStockage(t_stockage *source, t_stockage *cible) {
    t_itemSlot *slotSource = NULL;
    t_itemSlot *slotCible = NULL;
    

    for (int i = 0; i < source->nbSlots; i++) {
        slotSource = &source->itemSlots[i];
        slotCible = &cible->itemSlots[i];
        
        slotCible->item = slotSource->item;
        slotCible->quantite = slotSource->quantite;
    }
}








/* -------------------------------------------------------------------------- */
/*                               Initialisation                               */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param index 
 * @return t_itemSlot 
 */
t_itemSlot initItemSlot(const int index) {
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
t_stockage* creerStockage(const unsigned int nbSlots) {
    t_stockage *stockage = malloc(sizeof(t_stockage));


    stockage->nbSlots = nbSlots;
    stockage->itemSlots = calloc(nbSlots, sizeof(t_itemSlot));

    for (int i = 0; i < nbSlots; i++) {
        stockage->itemSlots[i] = initItemSlot(i);
    }


    return stockage;
}





/**
 * @brief 
 * 
 * @return t_inventaire 
 */
t_inventaire* creerInventaire() {
    t_stockage *stockage = creerStockage(NOMBRE_SLOT_INVENTAIRE);
    t_inventaire *inventaire = realloc(stockage, sizeof(t_inventaire));



    stockage = NULL;
    return inventaire;
}





/* -------------------------------------------------------------------------- */
/*                                 Destruction                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param stockage 
 */
void viderStockage(t_stockage *stockage) {
    for (int i = 0; i < stockage->nbSlots; i++) {
        stockage->itemSlots[i].item = NULL;
        stockage->itemSlots[i].quantite = 0;
    }
}





/**
 * @brief 
 * 
 * @param slot 
 */
void detruireSlot(t_itemSlot **slot) {
    if (slot != NULL && *slot != NULL) {

        t_item *item = (*slot)->item;
        if (item != NULL)
            item->detruire(&item);

        free(*slot);
        *slot = NULL;

    }
}





/**
 * @brief 
 * 
 * @param stockage 
 */
void detruireStockage(t_stockage **stockage) {
    if (stockage != NULL && *stockage != NULL) {

        int nbSlots = (*stockage)->nbSlots;
        t_itemSlot *itemSlot = NULL;

        if (nbSlots) {
            for (int i = 0; i < nbSlots; i++) {
                itemSlot = &(*stockage)->itemSlots[i];
                detruireSlot(&itemSlot);
            }            
        }


        free(*stockage);
        *stockage = NULL;

    }
}





/**
 * @brief 
 * 
 * @param inventaire 
 */
void detruireInventaire(t_inventaire **inventaire) {
    if (inventaire != NULL && *inventaire != NULL) {

        detruireStockage((t_stockage**)inventaire);

    }
}