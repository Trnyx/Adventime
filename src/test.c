#include <stdio.h>
#include "../include/item.h"
#include "../include/test.h"
#include "../include/arme.h"

void test()
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

    
    t_arme* arme = NULL;

    printf("Test d'existance sur une t_arme inexistant :\n");
    (arme_existe(arme) ? printf("Erreur\n") : printf("OK\n"));

    printf("Test création t_arme :\n");
    arme = arme_creer(item, 4);
    printf("Nombre de t_arme  = %lu\n", arme_cpt);

    printf("Test affichage arme :\n");
    arme->afficher(arme);
    printf("\n");

    printf("Test d'existance sur un t_arme existant :\n");
    (arme_existe(arme) ? printf("OK\n") : printf("Erreur\n"));

    printf("Test destruction arme :\n");
    arme->detruire(&arme);
    printf("Nombre de t_arme  = %lu\n", arme_cpt);
}