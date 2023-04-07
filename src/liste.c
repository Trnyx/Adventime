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
 * @param liste La liste à initialiser
 */
void init_liste(t_liste *liste) {
    // Crée la liste constituée du seul drapeau
    liste->drapeau = malloc(sizeof(t_element));

    liste->drapeau -> pred = liste->drapeau;
    liste->drapeau -> succ = liste->drapeau;
    liste->ec = liste->drapeau;
}



/**
 * @brief Détruit la liste et libere la mémoire allouée
 * 
 * @param liste Adresse du pointeur de la liste a détruire
 */
void detruire_liste(t_liste **liste) {
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
 * @param liste La liste
 * 
 * @return VRAI si la liste est vide, FAUX sinon
 */
boolean liste_vide(t_liste *liste) {
    return (liste->drapeau->succ == liste->drapeau);
}



/**
 * @brief Vérifie si l'element courant est hors liste
 * 
 * @param liste La liste
 * 
 * @return VRAI si l'élément courant est hors liste, FAUX sinon
 */
boolean hors_liste(t_liste *liste) {
    return (liste->ec == liste->drapeau);
}


/**
 * @brief Vérifie si l'element courant au niveau du drapeau cache est hors liste
 * 
 * @param liste La liste
 * 
 * @return VRAI si l'élément courant est hors liste, FAUX sinon
 */
boolean hors_liste_cache(t_liste *liste) {
    return (liste->cacheFlag == liste->drapeau);
}





/* -------------------------------------------------------------------------- */
/*                                 Deplacement                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief Met l'element courant au premier element de la liste
 * 
 * @param liste La liste
 */
void en_tete(t_liste *liste) {
    if (!liste_vide(liste))
        liste->ec = liste->drapeau->succ;
}


/**
 * @brief Met l'element courant du drapeau cache au premier element de la liste
 * 
 * @param liste La liste
 */
void en_tete_cache(t_liste *liste) {
    if (!liste_vide(liste))
        liste->cacheFlag = liste->drapeau->succ;
}



/**
 * @brief Met l'element courant au dernier element de la liste
 * 
 * @param liste La liste
 */
void en_queue(t_liste *liste) {
    if (!liste_vide(liste))
        liste->ec = liste->drapeau->pred;
}


/**
 * @brief Met l'element courant du drapeau cache au dernier element de la liste
 * 
 * @param liste La liste
 */
void en_queue_cache(t_liste *liste) {
    if (!liste_vide(liste))
        liste->cacheFlag = liste->drapeau->pred;
}



/**
 * @brief Met l'element courant a l'element juste avant l'element courant
 * 
 * @param liste La liste
 */
void precedent(t_liste *liste) {
    if (!hors_liste(liste))
        liste->ec = liste->ec->pred;
}


/**
 * @brief Met l'element courant au drapeau cache a l'element juste avant l'element courant
 * 
 * @param liste La liste
 */
void precedent_cache(t_liste *liste) {
    if (!hors_liste(liste))
        liste->cacheFlag = liste->cacheFlag->pred;
}



/**
 * @brief Met l'element courant a l'element juste apres l'element courant
 * 
 * @param liste La liste
 */
void suivant(t_liste *liste) {
    if (!hors_liste(liste))
        liste->ec = liste->ec->succ;
}


/**
 * @brief Met l'element courant au drapeau cache a l'element juste apres l'element courant
 * 
 * @param liste La liste
 */
void suivant_cache(t_liste *liste) {
    if (!hors_liste(liste))
        liste->cacheFlag = liste->cacheFlag->succ;
}





/* -------------------------------------------------------------------------- */
/*                                  Get & Set                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief Recupere la valeur de l'element de la liste et _entite
 * 
 * @param liste La liste
 * @param entite Adresse du pointeur sur l'entité
 */
void valeur_elt(t_liste *liste, t_entite **entite) {
    if (!hors_liste(liste))
        *entite = liste->ec->entite;
}


/**
 * @brief Recupere la valeur de l'element de la liste au niveau du drapeau "cache"
 * 
 * @param liste La liste
 * @param entite Adresse du pointeur sur l'entité
 */
void valeur_elt_cache(t_liste *liste, t_entite **entite) {
    if (!hors_liste(liste))
        *entite = liste->cacheFlag->entite;
}


/**
 * @brief Recupere la valeur de l'element de la liste et l'assigne a entité
 * 
 * @param liste La liste
 * @param entite La nouvelle valeur
 */
void modif_elt(t_liste *liste, t_entite **entite) {
    if (!hors_liste(liste))
        liste->ec->entite = *entite;
}


/**
 * @brief Supprime l'element de la liste a l'endroit ou est l'element courant
 * 
 * @param liste La liste
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
 * @brief Ajoute a droite de l'element courant
 * 
 * @param liste La liste
 * @param entite L'entité à ajouter
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
 * @brief Ajoute a gauche de l'element courant
 * 
 * @param liste La liste
 * @param entite L'entité à ajouter
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

