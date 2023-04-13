/**
 * @file jeu.c
 *
 * @brief Module de gestion pour le jeu
 *
 * @author Clément Hibon
 * @date 2 mars
 */




#include <stdlib.h>
#include <stdio.h>

#include "../include/main.h"
#include "../include/jeu.h"
#include "../include/physique.h"
#include "../include/initialiseur.h"
#include "../include/moteur.h"
#include "../include/audio.h"
#include "../include/textures.h"
#include "../include/monde.h"
#include "../include/joueur.h"
#include "../include/input_manager.h"
#include "../include/menus.h"
#include "../include/sauvegarde.h"










/**
 * @brief Vide toutes les entités de la liste donné
 *
 * @param liste Pointeur sur la liste
 */
static void viderEntitesDeListe(t_liste *liste) {
    t_entite *entite = NULL;

    en_queue(liste);
    while (!liste_vide(liste)) {
        valeur_elt(liste, &entite);

        entite->detruire(&entite);
        entite = NULL;

        oter_elt(liste);
    }
}





/**
 * @brief Charge une map dans le cache
 *
 * @param monde Le monde dans lequel est récupéré la map à charger
 * @param type Le type de la map à charger
 *
 * @return Un pointeur sur la map chargée
 */
static t_map* loadMap(t_monde *monde, e_mapType type) {
    t_map *map = NULL;


    switch (type) {
        case MAP_OVERWORLD:
            map = monde->overworld;
            break;
        case MAP_CAVE:
            map = monde->caverne;
            break;
        default:
            break;
    }


    /* ---------------------------------- Cache --------------------------------- */

    moteur->cache->map = map;
    moteur->cache->entites = map->entites;

    return map;
}





/**
 * @brief Gère tout le fonctionnement d'une partie
 *
 * @param monde Le monde dans lequel le joueur est entrain de jouer
 *
 * @return Lorsque le joueur retourne au menu principal
 */
static int adventime(t_monde *monde) {
    t_cache *cache = moteur->cache;
    t_joueur *joueur = monde->joueur;

    monde->boss = chargerBoss();

    // La map dans laquelle le joueur se situe au début de la partie
    e_mapType mapType = joueur->map;
    loadMap(monde, mapType);
    updateCamera(joueur->position);

    gestionnaireTempsEvenements(moteur->temps, time(NULL));
    selectionMusique(moteur->temps);


    int continuer = 1;
    while (continuer != M_MENU) {
        regulerFPS();

        continuer = inputManager(joueur);


        while(continuer == M_PAUSE) {
            continuer = pauseMenu(ctx);
            if (continuer == M_OPTIONS) {
                continuer = menu_options(ctx);
            }
        }


        // Affiche l'interface demandé
        // Sinon on affiche le jeu
        if(joueur->actionFlags->bool_inventory) {
            menu_inventaire(ctx, joueur);
        }
        else {
            update(cache->map, joueur);
        }


        // Affiche le game over si le joueur est mort
        if(continuer == J_MORT) {
            continuer = gameOver(ctx, joueur);
        }


        // Dès qu'on change de zone (map)
        // On sauvegarde l'état de la map précédente
        //  - Map (chunk / blocs)
        //  - Mobs
        //      - Ignore les monstres aggressifs
        //      - Ignore les entités à suppression après un temps
        if (mapType != joueur->map) {
            mapType = joueur->map;

            // sauvegarder_map(cache->map, mapType);

            viderEntitesDeListe(cache->entites);
            loadMap(monde, mapType);
        }
    }


    sauvegarder_monde(monde, "monde");

    viderEntitesDeListe(cache->entites);
    detruireMonde(&cache->monde);

    return continuer;
}





/**
 * @brief Création d'un nouveau monde
 *
 * @return La valeur si le joueur retourne au menu principal
 */
static int nouveauMonde(/* char *nom, const long long int seed */) {
    int seed = -1;

    t_monde *monde = creerMonde(seed);
    monde->joueur = creerJoueur(monde->pointApparitionDefaut);

    /* ---------------------------------- Cache --------------------------------- */
    moteur->cache->monde = monde;


    return adventime(monde);
}



/**
 * @brief Charge un monde déjà existant
 * 
 * @return La valeur si le joueur retourne au menu principal
 */
static int chargerMonde(/* char *tnom */) {
    t_monde *monde = malloc(sizeof(t_monde));
    chargerMonde(monde, "monde");

    /* ---------------------------------- Cache --------------------------------- */

    moteur->cache->monde = monde;

    return adventime(monde);
}





/**
 * @brief Lance une partie dans un monde en fonction de l'action
 *
 * @param action Le choix si on créer un nouveau monde où si on charge un monde exustant
 *
 * @return L'état indiquant le fait qu'il faut retourner au menu principal
 */
state_main jouer(e_actionMonde action) {
    switch (action) {
        default:
        case MONDE_CREER:
            nouveauMonde();
            break;

        case MONDE_CHARGER:
            chargerMonde();
            break;
    }


    return M_MENU;
}
