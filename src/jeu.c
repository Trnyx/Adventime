/**
 * @file jeu.c
 * 
 * @brief 
 * 
 * @author Clément Hibon
 * @date 2 mars
 * @version 1.1
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
        oter_elt(liste);
        entite = NULL;
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
            // printf("\nAPPARITION BOSS : %.2f:%1.2f / BOSS : %.2f:%1.2f / ID => %s \n\n", monde->positionApparitionBoss.x, monde->positionApparitionBoss.y, monde->boss->position.x, monde->boss->position.y, monde->boss->id);
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
 * @return int 
 */
static int adventime(t_monde *monde) {
    t_cache *cache = moteur->cache;
    t_joueur *joueur = monde->joueur;

    monde->boss = chargerBoss(monde);

    // La map dans laquelle se situe au début de la partie
    e_mapType mapType = joueur->map;
    loadMap(monde, mapType);
    updateCamera(joueur->position);


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
	
	update(cache->map, joueur);

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
            // sauvegarde

            viderEntitesDeListe(cache->entites);
            loadMap(monde, mapType);
        }
    }


    // Sauvegarde du monde complet ici

    viderEntitesDeListe(cache->entites);
    viderEntitesDeListe(cache->map->entites);

    return continuer;
}





/**
 * @brief Création d'un nouveau monde 
 * 
 * @return int 
 */
static int nouveauMonde() {
    // int seed = -1;
    // int seed = 1679905571;
    // int seed = 1679940582;
    int seed = 1680032110;
    t_monde *monde = creerMonde(seed);
    monde->joueur = creerJoueur(monde->pointApparitionDefaut);

    /* ---------------------------------- Cache --------------------------------- */
    moteur->cache->monde = monde;


    return adventime(monde);
}



static int chargerMonde() {
    t_monde *monde = NULL;

    // Charger le monde depuis la sauvegarde

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
