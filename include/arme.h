/**
 * \file arme.h
 * \brief Librairie pour la gestion des armes.
 * \author Julien Houget
 * \date 27/01/22
 */

#include "commun.h"
#include "item.h"

#ifndef _JEU_ARME_
#define _JEU_ARME_


 /**
  * \struct arme_t
  * \brief Définit les armes.
  */
typedef struct s_arme  t_arme;
struct  s_arme {
#include "attributs_arme.h"
    t_err(*afficher)(t_arme* const);
    t_err(*detruire)(t_arme**);
};

/**
 * VARIABLE LOCALE
 * declaration du compteur d'objets t_arme comme variable externe
 * pour compter les références sur ces objets.
 */

extern unsigned long int arme_cpt;

/**
 * FONCTIONS
 */

 /**
  * \brief Vérifie que l'arme existe.
  * \param arme
  */
extern t_booleen arme_existe(t_arme* const arme);

/**
 * \brief Crée une arme.
 * \param degat Entier spécifiant le nombre de dégats infligées par l'arme.
 */
extern t_arme* arme_creer(t_item* item, int degat);

#endif