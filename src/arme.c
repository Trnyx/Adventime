/**
 * \file arme.c
 * \brief Module de gestion des armes.
 * \author Julien Houget
 * \date 27/01/22
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/arme.h"

 /**
  * VARIABLE LOCALE
  */

unsigned long int arme_cpt = 0;/**<Compteur d'arme*/

/**
 * FONCTIONS
 */

 /**
  * \brief Vérifie que l'arme existe.
  * \param arme
  */
extern t_booleen arme_existe(t_arme* const arme)
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
static t_err arme_afficher(t_arme* arme)
{
    printf("\n");
    item_afficher((t_item*)arme);
    if (arme_existe(arme))
    {

        printf("%d\n", arme->degat);
    }
    printf("\n");
    return(OK);
}

/**
 * \brief Détruis une arme.
 * \param arme L'addresse de l'arme.
 */
static t_err arme_detruire(t_arme** arme)
{
    item_detruire((t_item**)arme);

    free(*arme);
    *arme = NULL;

    arme_cpt--;
    return(OK);
}

/**
 * \brief Crée une arme.
 * \param degat Entier spécifiant le nombre de dégats infligées par l'arme.
 */
extern t_arme* arme_creer(char* categorie, char* tag, char* nom, int degat)
{
    t_item* item = item_creer(categorie, tag, nom);
    t_arme* arme = realloc(item, sizeof(t_arme));

    arme->degat = degat;

    arme->afficher_arme = (t_err(*)(t_arme*)) arme_afficher;
    arme->detruire_arme = (t_err(*)(t_arme**)) arme_detruire;

    arme_cpt++;
    item = NULL;
    return(arme);
}