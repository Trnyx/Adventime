/**
 * \file item.h
 * \brief Librairie pour la gestion des items.
 * \author Julien Houget & Clément Hibon
 * \date 27/01/22
 */



#ifndef _JEU_ITEM_
#define _JEU_ITEM_

#include "utilitaire.h"
#include "entite.h"





typedef enum {
    CATEGORIE_MATERIEL,
    CATEGORIE_ARME,
    CATEGORIE_OUTIL,
} e_itemCategorie;



typedef enum {
    ITEM_STEAK,
    ITEM_MATERIEL_BATON,
    ITEM_OUTIL_PIOCHE,
    ITEM_ARME_EPEE,
} e_itemTag;





 /**
  * \struct t_item
  * \brief Définit les items.
  */
typedef struct s_item t_item;
struct s_item {
    char* id; /**<L'id de l'item*/
    char* nom; /**<Nom de l'item*/
    
    e_itemCategorie categorie;/**<Exemple : arme, outil...*/
    e_itemTag tag;/**<Exemple : épée de pierre, pioche...*/

    int (*afficher)(t_item* const);
    int (*detruire)(t_item**);
};


 /**
  * \struct arme_t
  * \brief Définit les armes.
  */
typedef struct s_arme  t_arme;
struct  s_arme {
    struct s_item;

    unsigned int degat;
};





/**
 * @brief 
 * 
 */
typedef struct s_itemEntite {

  struct s_entite;

  t_item *item;
  unsigned int rayonPrise;
  unsigned int cooldownAvantPrise;

} t_itemEntite;





typedef struct s_baseItem {
  e_itemTag tag;
  e_itemCategorie categorie;

  int stackable;
} t_baseItem;





/**
 * VARIABLE LOCALE
 * declaration du compteur d'objets t_item comme variable externe
 * pour compter les references sur ces objets.
 */

extern unsigned long int item_cpt;
extern unsigned long int arme_cpt;

extern t_baseItem basesItems[];





/**
 * FONCTIONS
 */


/**
 * ITEMS 
 */

 /**
  * \brief Vérifie que l'item existe.
  * \param item
  */
extern boolean item_existe(t_item* const item);

/**
 * \brief Crée un item.
 * \param categorie String spécifiant la catégorie de l'item (arme, outi, etc.).
 * \param tag String spécifiant le type de l'item (épée en pierre, pioche, etc.).
 * \param nom String spécifiant le nom de l'item.
 */
extern t_item* item_creer(e_itemTag tag);

/**
 * \brief Affiche les caractéristiques d'un item.
 * \param item
 */
extern int  item_afficher(t_item* item);

/**
 * \brief Détruis un item.
 * \param item L'addresse de l'item.
 */
extern int  item_detruire(t_item** item);




/**
 * ARMES
 */


/**
  * \brief Vérifie que l'arme existe.
  * \param arme
  */
extern boolean arme_existe(t_arme* const arme);

/**
 * \brief Crée une arme.
 * \param degat Entier spécifiant le nombre de dégats infligées par l'arme.
 */
extern t_arme* arme_creer(e_itemTag tag);






void detruireItemEntite(t_itemEntite **itemEntite);
t_itemEntite *creerItemEntite(const t_vecteur2 position, const e_itemTag tag);









#endif