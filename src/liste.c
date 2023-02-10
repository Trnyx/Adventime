/**
 * @file liste.c
 * 
 * @brief 
 * 
 * @author Clément Hibon
 * @date 10 février
 * @version 1.1
 */





#include <stdlib.h>
#include <stdio.h>

#include "../include/liste.h"






/**
 * @brief Initialise la liste
 * 
 * @param l la liste à initialiser
 */
void init_liste(t_liste *l) {
    // Crée la liste constituée du seul drapeau
    l->drapeau = malloc(sizeof(t_element));

    l->drapeau -> pred = l->drapeau;
    l->drapeau -> succ = l->drapeau;
    l->ec = l->drapeau;
}



/**
 * @brief Détruit la liste et libere la mémoire allouée
 * 
 * @param liste La liste a détruire
 */
void detruire_liste(t_liste **liste)
{
    if(liste != NULL && *liste != NULL) {
        en_queue(*liste);

        while(!liste_vide(*liste))
            oter_elt(*liste);

        free((*liste)->drapeau);

        free(*liste);
        *liste = NULL;
    }
}





/* -------------------------------------------------------------------------- */
/*                                    Tests                                   */
/* -------------------------------------------------------------------------- */


/**
 * @brief Vérifie si la liste est vide
 * 
 * @param l Lne liste
 * 
 * @return int booleen 1 : vrai, 0 : faux
 */
boolean liste_vide(t_liste *liste){
    return (liste->drapeau->succ == liste->drapeau) ;
}


/**
 * @brief Booleen, l'element courant est hors liste
 * 
 * @param liste une liste
 * 
 * @return int booleen 1 : vrai, 0 : faux
 */
boolean hors_liste(t_liste *liste){
    return (liste->ec == liste->drapeau) ;
}





/* -------------------------------------------------------------------------- */
/*                                 Deplacement                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief Met l'element courant au premier element de la liste
 * 
 * @param liste une liste
 */
void en_tete(t_liste *liste){
    if (!liste_vide(liste))
        liste->ec = liste->drapeau->succ;
}


/**
 * @brief Met l'element courant au dernier element de la liste
 * 
 * @param liste une liste
 */
void en_queue(t_liste *liste){
    if (!liste_vide(liste))
        liste->ec = liste->drapeau->pred ;
}


/**
 * @brief Met l'element courant a l'element juste avant l'element courant
 * 
 * @param liste une liste
 */
void precedent(t_liste *liste){
    if (!hors_liste(liste))
        liste->ec = liste->ec->pred;
}


/**
 * @brief Met l'element courant a l'element juste apres l'element courant
 * 
 * @param liste une liste
 */
void suivant(t_liste *liste) {
    if (!hors_liste(liste))
        liste->ec = liste->ec->succ;
}





/* -------------------------------------------------------------------------- */
/*                                  Get & Set                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief Recupere la valeur de l'element de la liste et _entite *
 */
void valeur_elt(t_liste *liste, t_entite **entite) {
    if (!hors_liste(liste))
        *entite = liste->ec->entite;
}


/**
 * @brief Recupere la valeur de l'element de la liste et l'assigne a v
 * 
 * @param liste une liste
 * @param entite une valeur
 */
void modif_elt(t_liste *liste, t_entite **entite) {
    if (!hors_liste(liste))
        liste->ec->entite = *entite;
}


/**
 * @brief Supprime l'element de la liste a l'endroit ou est l'ec
 * 
 * @param liste une liste
 */
void oter_elt(t_liste *liste) {
    if (!hors_liste(liste)) {
        t_element *p;

        (liste->ec->pred)->succ = liste->ec->succ;
        (liste->ec->succ)->pred = liste->ec->pred;
        p = liste->ec;

        precedent(liste);
        free(p);
    }
}





/* -------------------------------------------------------------------------- */
/*                                    Ajout                                   */
/* -------------------------------------------------------------------------- */


/**
 * @brief Ajoute a droite de l'element courant une valeur v
 * 
 * @param liste une liste
 * @param entite une valeur
 */
void ajout_droit(t_liste *liste, t_entite *entite) {
    if (liste_vide(liste) || !hors_liste(liste)) {
        t_element *nouv = (t_element*) malloc(sizeof(t_element));

        nouv->entite = entite;
        nouv->pred = liste->ec;
        nouv->succ = liste->ec->succ;

        // Mise a jour des chainages des voisins
        (liste->ec->succ)->pred = nouv;
        liste->ec->succ = nouv;

        // On se positionne sur le nouvel ?lement
        liste->ec = nouv;
    }
}


/**
 * @brief Ajoute a gauche de l'element courant une valeur v
 * 
 * @param liste La liste dans 
 * @param entite Une entite
 */
void ajout_gauche(t_liste *liste, t_entite *entite) {
    if (liste_vide(liste) || !hors_liste(liste)) {
        t_element * nouv = malloc(sizeof(t_element));

        nouv->entite = entite;
        nouv->pred = liste->ec->pred;
        nouv->succ = liste->ec;

        // Mise a jour des chainages des voisins
        (liste->ec->pred)->succ = nouv;
        liste->ec->pred = nouv;

        // On se positionne sur le nouvel element
        liste->ec = nouv;
    }
}

