/**
 * \file test_item.c
 * \brief Script de test pour l'item
 * \author Julien Houget
 * \date 27/01/22
 */

#include <stdio.h>
#include "../include/item.h"

int main()
{
    t_item* item = NULL;

    printf("Test d'existance sur un t_item inexistant :\n");
    (item_existe(item) ? printf("Erreur\n") : printf("OK\n"));

    printf("Test création t_item :\n");
    item = item_creer("arme", "épée de pierre", "épée test");
    printf("Nombre de t_item  = %lu\n", item_cpt);

    printf("Test affichage item :\n");
    item->afficher(item);
    printf("\n");

    printf("Test d'existance sur un t_item existant :\n");
    (item_existe(item) ? printf("OK\n") : printf("Erreur\n"));

    printf("Test destruction item :\n");
    item->detruire(&item);
    printf("Nombre de t_item  = %lu\n", item_cpt);


    return(0);
}