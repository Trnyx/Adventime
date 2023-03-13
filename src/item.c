/**
 * \file item.c
 * \brief Module de gestion des items.
 * \author Julien Houget & Clément Hibon
 * \date 27/01/22
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/item.h"

 /**
  * VARIABLE LOCALE
  */

unsigned long int item_cpt = 0;/**<Compteur d'item*/


/**
 * FONCTIONS
 */

 /**
  * \brief Vérifie que l'item existe.
  * \param item
  */
extern t_booleen item_existe(t_item* const item)
{
    if (item == NULL)
        return(FAUX);
    else
        return(VRAI);
}

/**
 * \brief Affiche les caractéristiques d'un item.
 * \param item
 */
extern t_err item_afficher(t_item* item)
{
    if (item_existe(item))
    {
        printf("%s\n", item->categorie);
        printf("%s\n", item->tag);
        printf("%s\n", item->nom);
    }
    printf("\n");
    return(OK);
}

/**
 * \brief Détruis un item.
 * \param item L'addresse de l'item.
 */
extern t_err item_detruire(t_item** item)
{
    free((*item)->nom);
    (*item)->nom = NULL;
    free(*item);
    *item = NULL;
    item_cpt--;
    return(OK);
}

/**
 * \brief Crée un item.
 * \param categorie String spécifiant la catégorie de l'item (arme, outi, etc.).
 * \param tag String spécifiant le type de l'item (épée en pierre, pioche, etc.).
 * \param nom String spécifiant le nom de l'item.
 */
extern t_item* item_creer(e_itemCategorie categorie, e_itemTag tag, char* nom)
{
    t_item* item = NULL;
    item = malloc(sizeof(t_item));

    item->categorie = categorie;
    item->tag = tag;

    item->nom = malloc(sizeof(char) * strlen(nom) + 1);
    strcpy(item->nom, nom);

    item->afficher_item = (t_err (*)(t_item*)) item_afficher;
    item->detruire_item = (t_err (*)(t_item**)) item_detruire;

    item_cpt++;
    return(item);
}
