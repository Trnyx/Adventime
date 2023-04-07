/**
 * @file inventaire.c
 * 
 * @brief Module de gestion de l'inventaire
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
    t_item *item = itemEntite->item;

    const int slot = peutPrendreItem(recuperateur, itemEntite);
    if (slot != -1) {
        ajouterItemDansStockage(item, (t_stockage*)recuperateur->inventaire, slot);
    }
    
}





/* -------------------------------------------------------------------------- */
/*                             Gestion Inventaire                             */
/* -------------------------------------------------------------------------- */





/* -------------------------------------------------------------------------- */
/*                               Initialisation                               */
/* -------------------------------------------------------------------------- */


/**
 * @brief Alloue l'espace nécessaire pour un inventaire et le créer
 * 
 * @return Un pointeur sur le inventaire, NULL en cas d'echec
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
 * @brief Detruit un inventaire est libère la mémoire allouée pour ce dernier
 * 
 * @param inventaire L'adresse du pointeur du inventaire à détruire
 */
void detruireInventaire(t_inventaire **inventaire) {
    if (inventaire != NULL && *inventaire != NULL) {

        detruireStockage((t_stockage**)inventaire);

    }
}