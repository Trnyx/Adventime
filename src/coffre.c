/**
 * @file coffre.c
 * 
 * @brief Module de gestion des coffres
 * 
 * @author Clément Hibon
 * @date 31 mars
 */





#include <stdlib.h>
#include <stdio.h>

#include "../include/joueur.h"
#include "../include/entite.h"
#include "../include/coffre.h"





/**
 * @brief Vérifie si le coffre est vide
 * 
 * @param coffre Le coffre à vérifier
 * 
 * @return VRAI si le coffre est vide, FAUX sinon
 */
boolean coffreEstVide(t_coffre *coffre) {
    return stockageEstVide(coffre->stockage);
}





/**
 * @brief Permet à une entité de récupérer le stockage d'un coffre
 * 
 * @param coffre Le coffre que l'entité souhaite récupérer
 * @param recuperateur L'entité voulant récupérer le coffre
 */
void recupererCoffre(t_coffre *coffre, t_joueur *recuperateur) {
    transfererStockage(coffre->stockage, (t_stockage*)recuperateur->inventaire);
}





/**
 * @brief Detruit un coffre est libère la mémoire allouée pour ce dernier
 * 
 * @param coffre L'adresse du pointeur du coffre à détruire
 */
void detruireCoffre(t_coffre **coffre) {
    if (coffre != NULL && *coffre != NULL) {
        if ((*coffre)->stockage != NULL)
            detruireStockage(&(*coffre)->stockage);
            
        detruireEntite((t_entite**)coffre);
    }
}





/**
 * @brief Alloue l'espace nécessaire pour un coffre et le créer
 * 
 * @param position La position à laquelle le coffre doit être créé
 * 
 * @return Un pointeur sur le coffre créé, NULL si echec
 */
t_coffre *creerCoffre(const t_vecteur2 position) {
    t_entite *entite = creerEntite(position);
    t_coffre *coffre = realloc(entite, sizeof(t_coffre));


    if (coffre == NULL) {
        printf("Erreur mémoire : Impossible d'allouer la place nécessaire pour creer un coffre\n");
        detruireEntite(&entite);
        return NULL;
    }


    coffre->entiteType = ENTITE_COFFRE;
    coffre->tag = TAG_COFFRE;

    coffre->stockage = creerStockage(NOMBRE_SLOT_INVENTAIRE);
    
    coffre->detruire = (void (*)(t_entite**)) detruireCoffre;
    coffre->interaction = (void (*)(void*, void*)) recupererCoffre;

    coffre->destructionInactif = FAUX;
    coffre->destructionDelai = FAUX;
    coffre->interargirAvec = VRAI;


    entite = NULL;
    return coffre;
}