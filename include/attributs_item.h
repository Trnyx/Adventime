/**
 * \file attributs_item.h
 * \brief Librairie pour les attributs des items.
 * \author Julien Houget
 * \date 27/01/22
 */

 /**
  * ATTRIBUTS
  */
  // int[3] id; //Permet de spécifier un item en particulier
char* categorie;/**<Exemple : arme, outil...*/
char* tag;/**<Exemple : épée de pierre, pioche...*/
char* nom; /**<Nom de l'item*/

/**
 * POINTEURS DE FONCTION
 */
// t_err (*afficher)(t_item* const);
// t_err (*detruire)(t_item**);