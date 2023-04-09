/**
 * @file stockage.c
 * 
 * @brief Module de gestion des stockages
 * 
 * @author Clément Hibon
 * @date 24 mars
 */





#include <stdlib.h>
#include <stdio.h>

#include "../include/stockage.h"





/**
 * @brief Vérifie si le stockage est vide
 * 
 * @param stockage Le stockage à vérifier
 * 
 * @return VRAI si le stockage est vide, FAUX sinon
 */
boolean stockageEstVide(t_stockage *stockage) {
    for (int i = 0; i < stockage->nbSlots; i++) {
        t_itemSlot slot = stockage->itemSlots[i];
        if (slot.item != NULL && slot.quantite > 0)
            return FAUX;
    }
    

    return VRAI;
}





/**
 * @brief Permet de transférer les items contenuent dans un stockage dans un autre stockage
 * 
 * @param source Le stockage source
 * @param cible Le stockage cible
 */
void transfererStockage(t_stockage *source, t_stockage *cible) {
    if (stockageEstVide(source)) return;

    t_itemSlot *slotSource = NULL;
    t_itemSlot *slotCible = NULL;
    

    for (int i = 0, j = 0; i < source->nbSlots && j < cible->nbSlots; j++) {
        slotSource = &source->itemSlots[i];
        slotCible = &cible->itemSlots[j];


        if (slotSource->item == NULL || slotSource->quantite == 0) {
            i++;
        }
        
        // Check si le slot dans le stockage cible est déjà utilisé
        else if (slotCible->item != NULL || slotCible->quantite > 0) {
            if (slotCible->item->tag == slotSource->item->tag) {
                t_baseItem base = basesItems[slotSource->item->tag];
                int quantite = 0;
                
                if (slotSource->quantite + slotCible->quantite > base.stackable) {
                    quantite = base.stackable - slotCible->quantite;
                }
                else {
                    quantite = slotSource->quantite;
                }
                
                slotCible->quantite += quantite;
                slotSource->quantite -= quantite;
            }
        }
        else {
            slotCible->item = slotSource->item;
            slotCible->quantite = slotSource->quantite;

            j = 0;

            slotSource->item = NULL;
            slotSource->quantite = 0;
        }    

    }
}





/* -------------------------------------------------------------------------- */
/*                               Initialisation                               */
/* -------------------------------------------------------------------------- */


/**
 * @brief Initialise un slot d'un stockage
 * 
 * @param index Le numéro du slot à initialiser
 * 
 * @return Le slot initialisé
 */
t_itemSlot initItemSlot(const int index) {
    t_itemSlot itemSlot;


    itemSlot.slot = index;

    itemSlot.item = NULL;
    itemSlot.quantite = 0;


    return itemSlot;
}





/**
 * @brief Alloue l'espace nécessaire pour un stockage et le créer
 * 
 * @param nbSlots Le nombre de slots que doit contenir le stockage 
 * 
 * @return Un pointeur sur le stockage, NULL en cas d'echec
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





/* -------------------------------------------------------------------------- */
/*                                 Destruction                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief Permet de vider l'entièreté d'un stockage sans le détruire
 * 
 * @param stockage Le stockage qui doit être vidé
 */
void viderStockage(t_stockage *stockage) {
    for (int i = 0; i < stockage->nbSlots; i++) {
        stockage->itemSlots[i].item = NULL;
        stockage->itemSlots[i].quantite = 0;
    }
}







/**
 * @brief Détruit le slot d'un stockage
 * 
 * @param slot Un pointeur sur le slot à détruire
 */
void detruireSlot(t_itemSlot *slot) {
    if (slot != NULL) {

        t_item *item = slot->item;
        if (item != NULL)
            item->detruire(&item);

    }
}





/**
 * @brief Detruit un stockage est libère la mémoire allouée pour ce dernier
 * 
 * @param stockage L'adresse du pointeur du stockage à détruire
 */
void detruireStockage(t_stockage **stockage) {
    if (stockage != NULL && *stockage != NULL) {

        int nbSlots = (*stockage)->nbSlots;
        t_itemSlot itemSlot;

        if (nbSlots) {
            for (int i = 0; i < nbSlots; i++) {
                itemSlot = (*stockage)->itemSlots[i];
                detruireSlot(&itemSlot);
            }            
        }


        free(*stockage);
        *stockage = NULL;

    }
}