/**
 * @file liste.h
 * 
 * @brief Module de manipulation des listes
 * 
 * @author Clément Hibon
 * @date 10 février
 */





#ifndef _JEU_LISTE_
#define _JEU_LISTE_





#include "utilitaire.h"




/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


typedef struct s_entite t_entite;

/**
 * @struct t_element
 * @brief Modelise un element de la liste
 */
typedef struct s_element {
    t_entite *entite;           /**< Valeur */
    struct s_element *pred;     /**< Element precedant l'element courant*/
    struct s_element *succ;     /**< Element succedant l'element courant*/
} t_element;





/**
 * @struct t_liste
 * @brief Modelise l'emplacement actuel dans la liste
 */
typedef struct s_liste t_liste;
struct s_liste {
    t_element *drapeau;         /**< Drapeau de la liste */
    t_element *ec;              /**< L'element courant */
    t_element *cacheFlag;       /**< Element permettant de parcourir en parallèle la liste */
} ;






/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


void init_liste(t_liste *liste);
void detruire_liste(t_liste **liste);

boolean liste_vide(t_liste *liste);
boolean hors_liste(t_liste *liste);
boolean hors_liste_cache(t_liste *liste);

void en_tete(t_liste *liste);
void en_tete_cache(t_liste *liste);
void en_queue(t_liste *liste);
void en_queue_cache(t_liste *liste);
void precedent(t_liste *liste);
void precedent_cache(t_liste *liste);
void suivant(t_liste *liste);
void suivant_cache(t_liste *liste);

void valeur_elt(t_liste *liste, t_entite **entite);
void valeur_elt_cache(t_liste *liste, t_entite **entite);
void modif_elt(t_liste *liste, t_entite **entite);
void oter_elt(t_liste *liste);

void ajout_droit(t_liste *liste, t_entite *entite);
void ajout_gauche(t_liste *liste, t_entite *entite);





#endif
