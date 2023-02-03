/**
 * \file item.h
 * \brief Librairie pour la gestion des items.
 * \author Julien Houget
 * \date 27/01/22
 */

#include "commun.h"

#ifndef _JEU_ITEM_
#define _JEU_ITEM_


 /**
  * \struct t_item
  * \brief Définit les items.
  */
typedef struct s_item t_item;
struct s_item {
#include "attributs_item.h"
};

/**
 * VARIABLE LOCALE
 * declaration du compteur d'objets t_item comme variable externe
 * pour compter les references sur ces objets.
 */

extern unsigned long int item_cpt;

/**
 * FONCTIONS
 */

 /**
  * \brief Vérifie que l'item existe.
  * \param item
  */
extern t_booleen item_existe(t_item* const item);

/**
 * \brief Crée un item.
 * \param categorie String spécifiant la catégorie de l'item (arme, outi, etc.).
 * \param tag String spécifiant le type de l'item (épée en pierre, pioche, etc.).
 * \param nom String spécifiant le nom de l'item.
 */
extern t_item* item_creer(char* categorie, char* tag, char* nom);

#endif