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
unsigned long int arme_cpt = 0;/**<Compteur d'arme*/


/**
 * FONCTIONS
 */

 /**
  * \brief Vérifie que l'item existe.
  * \param item
  */
extern boolean item_existe(t_item* const item)
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
extern int item_afficher(t_item* item)
{
    if (item_existe(item))
    {
        printf("%i\n", item->categorie);
        printf("%i\n", item->tag);
        printf("%s\n", item->nom);
    }
    printf("\n");
    return 0;
}

/**
 * \brief Détruis un item.
 * \param item L'addresse de l'item.
 */
extern int item_detruire(t_item** item)
{
    if ((*item)->id != NULL) {
        free((*item)->id);
        (*item)->id = NULL;
    }

    if ((*item)->nom != NULL) {
        free((*item)->nom);
        (*item)->nom = NULL;
    }

    free(*item);
    *item = NULL;

    item_cpt--;
    return 0;
}

/**
 * \brief Crée un item.
 * \param categorie String spécifiant la catégorie de l'item (arme, outi, etc.).
 * \param tag String spécifiant le type de l'item (épée en pierre, pioche, etc.).
 * \param nom String spécifiant le nom de l'item.
 */
extern t_item* item_creer(e_itemCategorie categorie, e_itemTag tag)
{
    t_item* item = NULL;
    item = malloc(sizeof(t_item));

    item->categorie = categorie;
    item->tag = tag;


    // item->nom = malloc(sizeof(char) * strlen(nom) + 1);
    // strcpy(item->nom, nom);

    item->afficher = (int (*)(t_item*)) item_afficher;
    item->detruire = (int (*)(t_item**)) item_detruire;

    item_cpt++;
    return(item);
}




// ARMES



 /**
  * \brief Vérifie que l'arme existe.
  * \param arme
  */
extern boolean arme_existe(t_arme* const arme)
{
    if (arme == NULL)
        return(FAUX);
    else
        return(VRAI);
}

/**
 * \brief Affiche les caractéristiques d'un arme.
 * \param arme
 */
static int arme_afficher(t_arme* arme)
{
    printf("\n");
    item_afficher((t_item*)arme);
    if (arme_existe(arme))
    {

        printf("%d\n", arme->degat);
    }
    printf("\n");
    return (0);
}

/**
 * \brief Détruis une arme.
 * \param arme L'addresse de l'arme.
 */
static int arme_detruire(t_arme** arme)
{
    item_detruire((t_item**)arme);

    arme_cpt--;
    return (0);
}

/**
 * \brief Crée une arme.
 * \param degat Entier spécifiant le nombre de dégats infligées par l'arme.
 */
extern t_arme* arme_creer(e_itemTag tag)
{
    t_item* item = item_creer(CATEGORIE_ARME, tag);
    t_arme* arme = realloc(item, sizeof(t_arme));

    arme->degat = 4; // getDegatArme

    arme->afficher = (int(*)(t_item*)) arme_afficher;
    arme->detruire = (int(*)(t_item**)) arme_detruire;

    arme_cpt++;
    item = NULL;
    return(arme);
}





/* -------------------------------------------------------------------------- */
/*                                    Drops                                   */
/* -------------------------------------------------------------------------- */


