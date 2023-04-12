/**
 * \file item.c
 * \brief Module de gestion des items.
 * \author Julien Houget & Clément Hibon
 * \date 27/01/22
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "../include/moteur.h"
#include "../include/audio.h"
#include "../include/physique.h"
#include "../include/item.h"
#include "../include/inventaire.h"

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
extern t_item* item_creer(e_itemTag tag)
{
    t_item* item = malloc(sizeof(t_item));

    if (item == NULL) {
        printf("Erreur méoire : Impossible d'allouer l'espace nécessaire pour un item");
        return NULL;
    }


    item->id = genererId();

    item->tag = tag;

    t_baseItem base = basesItems[tag];
    item->categorie = base.categorie;


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
    t_item* item = item_creer(tag);
    t_arme* arme = realloc(item, sizeof(t_arme));

    arme->degat = 4; // getDegatArme

    arme->afficher = (int(*)(t_item*)) arme_afficher;
    arme->detruire = (int(*)(t_item**)) arme_detruire;

    arme_cpt++;
    item = NULL;
    return(arme);
}










/**
 * @brief Met à jour l'item entité
 * 
 * @param itemEntite L'item entité qui doit être mis à jour
 * @param distance La distance entre l'item entité et le joueur
 * @param recuperateur L'entité récupérant l'item
 */
void updateItemEntite(t_itemEntite *itemEntite, const float distance, t_joueur *recuperateur) {
    if (itemEntite->cooldownAvantPrise > 0) {
        --(itemEntite->cooldownAvantPrise);
    }
    else {
        if (distance <= itemEntite->rayonPrise) {
            play_bruitage(audio->bruitages->item_recuperation, -1);

            recupererItem(itemEntite, recuperateur);
            itemEntite->detruire((t_entite**)&itemEntite);
            oter_elt(moteur->cache->entites);
        }
            
    }
}





/**
 * @brief Detruit un coffre est libère la mémoire allouée pour ce dernier
 * 
 * @param itemEntite L'adresse du pointeur de l'item entité
 */
void detruireItemEntite(t_itemEntite **itemEntite) {
    if (itemEntite != NULL && itemEntite != NULL) {

        if ((*itemEntite)->timestampActualisation - (*itemEntite)->timestampCreation >= ENTITE_DUREE_VIE_MAX * 1000) {
            t_item *item = (*itemEntite)->item;
            item->detruire(&item);
        }

        detruireEntite((t_entite**)itemEntite);
    }
}



/**
 * @brief Alloue l'espace nécessaire pour un item entité et le créer
 * 
 * @param position La position à laquelle l'item entité doit apparaitre
 * @param tag Le tag de l'item qui doit être créé
 * 
 * @return Un pointeur sur l'item, NULL en cas d'echec
 */
t_itemEntite *creerItemEntite(const t_vecteur2 position, const e_itemTag tag) {
    t_item *item = item_creer(tag);

    if (item == NULL)
        return NULL;

    t_entite *entite = creerEntite(position);
    t_itemEntite *itemEntite = realloc(entite, sizeof(t_itemEntite));

    if (itemEntite == NULL) {
        printf("Erreur mémoire : Impossible d'allouer l'espace nécessaire pour une entité");
        item_detruire(&item);
        return NULL;
    }


    itemEntite->tag = item->tag;
    itemEntite->entiteType = ENTITE_ITEM;

    itemEntite->taille = 0.5;

    itemEntite->hitbox.x = position.x - (itemEntite->taille / 2);
    itemEntite->hitbox.y = position.y - (itemEntite->taille / 2);
    itemEntite->hitbox.h = itemEntite->taille;
    itemEntite->hitbox.w = itemEntite->taille;

    itemEntite->rayonPrise = 1.0;
    itemEntite->item = item;

    itemEntite->cooldownAvantPrise = ENTITE_ITEM_DELAI_RECUPERATION;


    itemEntite->update = (void (*)(t_entite*, float, t_entite*)) updateItemEntite;
    itemEntite->detruire = (void (*)(t_entite**)) detruireItemEntite;


    entite = NULL;
    return itemEntite;
}





/* -------------------------------------------------------------------------- */
/*                                    Bases                                   */
/* -------------------------------------------------------------------------- */


/**
 * @brief Tableau regroupant les bases des différents items
 * - Tag
 * - Catégorie
 * - Le nombre d'item par stack
 * 
 */
t_baseItem basesItems[] = {
    { ITEM_STEAK, CATEGORIE_MATERIEL, 16 },
    { ITEM_PORC, CATEGORIE_MATERIEL, 16 },

    // MATERIELS
    { ITEM_MATERIEL_BATON, CATEGORIE_MATERIEL, 16 },

    // OUTILS
    { ITEM_OUTIL_PIOCHE, CATEGORIE_OUTIL, 1 },

    // ARMES
    { ITEM_ARME_EPEE, CATEGORIE_ARME, 1 },
};