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
/*                                Gestion Item                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief Vérifie si l'item peut bien être prit
 * 
 * @param recuperateur L'entité récupérant l'item
 * @param itemEntite L'item (entité) récupéré
 * 
 * @return Le slot où doit être ajouté l'item, -1 si l'item ne peut être prit
 */
int peutPrendreItem(t_joueur *recuperateur, t_itemEntite *itemEntite) {
    const float distance = calculDistanceEntrePoints(recuperateur->position, itemEntite->position);
    if (distance > itemEntite->rayonPrise) 
        return -1;

    
    t_stockage *stockage = (t_stockage*)recuperateur->inventaire;
    
    for (int i = 0; i < stockage->nbSlots; i++) {
        t_itemSlot itemSlot = stockage->itemSlots[i];
        t_item *item = itemSlot.item;

        // Cas où le slot est vide
        if (itemSlot.item == NULL || !itemSlot.quantite)
            return i;

        // Cas où le slot est un slot contenant un même item
        if (item->tag == itemEntite->item->tag) {
            t_baseItem base = basesItems[item->tag];
            if (itemSlot.quantite < base.stackable)
                return i;
        }
    }
    
    
    return -1;
}





/**
 * @brief Ajout d'un item dans le stockage
 * 
 * @param item L'item à ajouter dans le stockage
 * @param stockage Le stockage dans lequel est ajouté l'item
 * @param slot Le slot dans lequel l'item est ajouté
 */
void ajouterItemDansStockage(t_item *item, t_stockage *stockage, const int slot) {
    t_itemSlot *itemSlot = &stockage->itemSlots[slot];

    // Si l'emplacement ne contient pas d'item
    // Alors on ajoute l'item voulu
    if (!itemSlot->quantite || itemSlot->item == NULL)
        itemSlot->item = item;

    // On change le nombre d'item à l'emplacement indiqué
    ++(itemSlot->quantite);
}





/**
 * @brief Récupère l'item souhaité
 * 
 * @param itemEntite l'item (entité) qui doit être récupéré
 * @param recuperateur L'entité souhaitant récupérer l'item
 */
void recupererItem(t_itemEntite *itemEntite, t_joueur *recuperateur) {
    printf("RECUPERATION => ");
    t_item *item = itemEntite->item;

    const int slot = peutPrendreItem(recuperateur, itemEntite);
    if (slot != -1) {
        printf("AJOUT => ");
        ajouterItemDansStockage(item, (t_stockage*)recuperateur->inventaire, slot);
        printf("RECUPRE !\n");
    }
    
}





/* -------------------------------------------------------------------------- */
/*                             Gestion Inventaire                             */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param stockage 
 * @return boolean 
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
 * @brief 
 * 
 * @param source 
 * @param cible 
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
void detruireSlot(t_itemSlot *slot) {
    if (slot != NULL) {

        t_item *item = slot->item;
        if (item != NULL)
            item->detruire(&item);

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