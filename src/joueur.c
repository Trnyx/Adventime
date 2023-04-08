/**
 * @file joueur.c
 * 
 * @brief Module de gestion du joueur
 * 
 * @author Clément Hibon
 * @date 3 février
 * @version 1.1
 */





#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>

#include "../include/physique.h"

#include "../include/audio.h"
#include "../include/moteur.h"
#include "../include/joueur.h"
#include "../include/camera.h"
#include "../include/combat.h"
#include "../include/coffre.h"





/* -------------------------------------------------------------------------- */
/*                                Verifications                               */
/* -------------------------------------------------------------------------- */


/**
 * @brief Vérifie si le joueur peut attaquer
 * 
 * @param joueur Le joueur que l'on vérifie
 * 
 * @return VRAI si le joueur peut attaquer, FAUX sinon
 */
boolean peutAttaquer(t_joueur *joueur) {
    return !(joueur->cooldownAttaque);
}





/**
 * @brief Regarde les inputs et vérifie si le joueur doit attaquer
 * 
 * @param flags Les flags indiquant les inputs du joueur
 * 
 * @return VRAI si le joueur doit attaquer, FAUX sinon
 */
boolean doitAttaquer(t_action_flags *flags) {
    return flags->attack == 1;
}



/**
 * @brief Regarde les inputs et vérifie si le joueur doit se déplacer
 * 
 * @param flags Les flags indiquant les inputs du joueur
 * 
 * @return VRAI si le joueur doit se déplacer, FAUX sinon
 */
boolean doitSeDeplacer(t_action_flags *flags) {
    return flags->up || flags->down || flags->left || flags->right;
}



/**
 * @brief Regarde les inputs et vérifie si le joueur doit intéragir
 * 
 * @param flags Les flags indiquant les inputs du joueur
 * 
 * @return VRAI si le joueur doit interargir, FAUX sinon
 */
boolean doitInterargir(t_action_flags *flags) {
    return flags->interaction == 1;
}





/* -------------------------------------------------------------------------- */
/*                                     Get                                    */
/* -------------------------------------------------------------------------- */


/**
 * @brief Met à jour la direction du joueur en fonction de ses inputs
 * 
 * @param joueur Le joueur dont la direction est mis à jour
 */
void getDirectionJoueur(t_joueur *joueur) {
    t_vecteur2 direction = { 0, 0 };


    if (joueur->actionFlags->right == joueur->actionFlags->left)
        direction.x = 0;
    else if (joueur->actionFlags->left)
        direction.x = -1;
    else if (joueur->actionFlags->right)
        direction.x = 1;
    

    if (joueur->actionFlags->up == -joueur->actionFlags->down)
        direction.y = 0;
    else if (joueur->actionFlags->up)
        direction.y = -1;
    else if (joueur->actionFlags->down)
        direction.y = 1;
    

    joueur->direction = direction;
}



/**
 * @brief Obtient l'angle d'orientation du joueur
 * 
 * @return L'angle entre le centre de l'écran et la position de la souris
 */
float getOrientationJoueur() {
    const t_vecteur2 centreEcran = {
        moteur->window_width / 2,
        moteur->window_height / 2,
    };

    return calculAngleEntrePoints(centreEcran, moteur->positionSouris);
}





/* -------------------------------------------------------------------------- */
/*                                   Update                                   */
/* -------------------------------------------------------------------------- */


/**
 * @brief Execute une attaque du joueur
 * 
 * @param joueur Pointeur sur le joueur qui attaque
 * @param angleAttaque L'angle dans lequel le joueur attaque
 */
void joueurAttaque(t_joueur *joueur, const float angleAttaque) {
    joueur->cooldownAttaque = JOUEUR_COOLDOWN_ATTAQUE;
    t_liste *mobsAlentour = getEntitesAlentour((t_entite*)joueur, ENTITE_MOB, 2.0);

    if (!liste_vide(mobsAlentour)) {
        en_tete(mobsAlentour);
        t_mob *mob = NULL;

        while (!hors_liste(mobsAlentour)) {
            valeur_elt(mobsAlentour, (t_entite**)&mob);
            metUnCoup((t_entiteVivante*)joueur, (t_entiteVivante*)mob, angleAttaque, 2.0);

            suivant(mobsAlentour);
        }

        detruire_liste(&mobsAlentour);
    }
}





/**
 * @brief Execute une interaction du joueur
 * 
 * @param joueur Pointeur sur le joueur qui intérargit
 */
void joueurInteraction(t_joueur *joueur) {
    t_liste *entites = moteur->cache->entites;
    t_entite *entite = NULL;
    t_entite *entiteTempo = NULL;
    int distanceMin = RAYON_INTERACTION;

    en_tete_cache(entites);
    while (!hors_liste_cache(entites)) {
        valeur_elt_cache(entites, &entiteTempo);
        if (!entiteTempo->interargirAvec) {
            suivant_cache(entites);
            continue;
        }


        const float distance = calculDistanceEntreEntites((t_entite*)joueur, entiteTempo);

        if (distance <= RAYON_INTERACTION) {
            if (distance <= distanceMin)
                entite = entiteTempo;
        }

        suivant_cache(entites);
    }

    
    if (entite != NULL)
        if (entite->interaction != NULL) {
            if (entite->tag == TAG_COFFRE)
                entite->interaction(entite, joueur);
        }

}





/**
 * @brief Actualise le joueur
 * 
 * @param joueur Pointeur sur le joueur qui doit être actualisé
 */
void updateJoueur(t_joueur *joueur) {
    regenerationEntite((t_entiteVivante*)joueur);

    if (joueur->cooldownAttaque > 0) {
        --(joueur->cooldownAttaque);
    }


    if (doitInterargir(joueur->actionFlags)) {
        joueurInteraction(joueur);
    }


    if (doitSeDeplacer(joueur->actionFlags)) {
        joueur->operation = SE_DEPLACE_VERS;
        getDirectionJoueur(joueur);
        deplacerEntite((t_entite*)joueur, joueur->statistiques.vitesse);
    } 
    else if (joueur->operation != ATTAQUE) {
        joueur->operation = ATTENTE;
    }


    const float angle = getOrientationJoueur();
    orienterEntite(angle, (t_entite*)joueur);


    if (doitAttaquer(joueur->actionFlags) && peutAttaquer(joueur)) {
        joueur->operation = ATTAQUE;
        joueur->animation->frameCourante = 1;
        joueurAttaque(joueur, angle);
    }


}





/**
 * @brief Gère la mort du joueur
 * 
 * @param joueur Le joueur qui est mort
 */
void mortJoueur(t_joueur *joueur) {
    // todo : bruitage
    joueur->statistiques.pv = 0;

    // Inventaire
    // Si l'inventaire du joueur n'est pas vide
    // On créer un coffre, à la position de la mort du joueur, contenant l'inventaire de celui ci
    if (!stockageEstVide((t_stockage*)joueur->inventaire)) {
        t_coffre *coffre = creerCoffre(joueur->position);
        coffre->entiteType = ENTITE_COFFRE_INVENTAIRE;
        
        ajout_droit(moteur->cache->entites, (t_entite*)coffre);

        transfererStockage((t_stockage*)joueur->inventaire, coffre->stockage);
        viderStockage((t_stockage*)joueur->inventaire);
    }
}





/**
 * @brief Permet au joueur de réapparaitre
 * 
 * @param joueur Pointeur sur le joueur qui réapparait
 * @param position La position à laquelle le joueur réapparait
 */
void reapparitionJoueur(t_joueur *joueur, const t_vecteur2 position) {
    joueur->statistiques.pv = joueur->statistiques.pvMax;
    joueur->position = position;

    joueur->map = MAP_OVERWORLD;
}





/* -------------------------------------------------------------------------- */
/*                                 Destruction                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief Detruit les inputs du joueur est libère la mémoire allouée pour ces derniers
 * 
 * @param flags L'adresse du pointeur sur les inputs du joueur à détruire
 */
void detruireActionFlags(t_action_flags **flags) {
    if (flags != NULL && *flags != NULL) {
        free(*flags);
        *flags = NULL;
    }
}



/**
 * @brief Detruit un joueur est libère la mémoire allouée pour ce dernier
 * 
 * @param joueur L'adresse du pointeur du joueur à détruire
 */
void detruireJoueur(t_joueur **joueur) {
    if (joueur != NULL && *joueur != NULL) {

        detruireActionFlags(&(*joueur)->actionFlags);
        detruireEntite((t_entite**) joueur);

    }
};





/* -------------------------------------------------------------------------- */
/*                                  Creation                                  */
/* -------------------------------------------------------------------------- */


/**
 * @brief Alloue l'espace nécessaire pour les flags des inputs du joueur et les initialise
 * 
 * @return Un pointeur sur les flags des inputs, NULL si echec
 */
t_action_flags* initialiserActionFlags() {
    t_action_flags *flags = malloc(sizeof(t_action_flags));

    flags->up = 0;
    flags->down = 0;
    flags->left = 0;
    flags->right = 0;
    flags->attack = 0;
    flags->inventory = 0;
    flags->interaction = 0;
    flags->miniMap = 0;

    flags->bool_inventory = 0;

    return flags;
}





/**
 * @brief Alloue l'espace nécessaire pour un joueur et le créer
 * 
 * @param position La position à laquelle le joueur doit être créé
 * 
 * @return Un pointeur sur le joueur créé, NULL si echec
 */
t_joueur* creerJoueur(const t_vecteur2 position) {
    t_entite *entite = creerEntite(position);
    t_joueur *joueur = realloc(entite, sizeof(t_joueur));


    if (joueur == NULL) {
        printf("Erreur mémoire : Impossible d'allouer la place nécessaire pour creer une joueur\n");
        detruireEntite(&entite);
        return NULL;
    }


    joueur->entiteType = ENTITE_JOUEUR;
    joueur->tag = TAG_JOUEUR;
    joueur->map = MAP_OVERWORLD;

    // Statistiques
    joueur->baseStatistiques = genererStatistiquesDeBaseJoueur();
    joueur->statistiques = genererStatistiques(joueur->baseStatistiques, 1);

    joueur->inventaire = creerInventaire();
    joueur->slotSelectionne = 0;

    // Actions
    joueur->actionFlags = initialiserActionFlags();

    // Animation
    joueur->animation = creerAnimation(100, 4);

    // Fonctions
    joueur->update = (void (*)(t_entite*, const float, t_entite*)) updateJoueur;
    joueur->detruire = (void (*)(t_entite**)) detruireJoueur;

    // Timer
    joueur->cooldownAttaque = 0;
    joueur->cooldownRegeneration = 0;
    joueur->destructionInactif = FAUX;

    // Audio
    joueur->bruitages = creerAudioPack();
    chargerAudioPack(joueur->bruitages, joueur->tag);


    entite = NULL;
    return joueur;
};
