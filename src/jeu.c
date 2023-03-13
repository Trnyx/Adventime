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
#include "../include/textures.h"
#include "../include/moteur.h"
#include "../include/audio.h"
#include "../include/main.h"
#include "../include/monde.h"
#include "../include/joueur.h"
#include "../include/input_manager.h"
#include "../include/menus.h"







static void chargerEntitesDansCache(t_liste *cache, t_liste *entitesActuelles) {
    if (!liste_vide(entitesActuelles)) {
        en_tete(entitesActuelles);
        en_tete(cache);

        t_entite *entite = NULL;

        while (!hors_liste(entitesActuelles)) {
            valeur_elt(entitesActuelles, &entite);

            ajout_droit(cache, entite);
            
            suivant(entitesActuelles);
            suivant(cache);
        }
    }
}





static void viderEntitesDeListe(t_liste *liste) {
    t_entite *entite = NULL;

    en_queue(liste);
    while (!liste_vide(liste)) {
        valeur_elt(liste, &entite);
        oter_elt(liste);
        entite = NULL;
    }
}





static t_map* loadMap(t_monde *monde, e_mapType type) {
    t_map *map = NULL;

    
    switch (type) {
        case MAP_OVERWORLD: 
            map = monde->overworld;
            break;
        case MAP_CAVE: 
            map = monde->overworld;
            break;
        // case MAP_BOSS_TEMPLE: 
        //    map = getTempleBoss();
        //    break;
        default: 
            break;
    }


    /* ---------------------------------- Cache --------------------------------- */
    moteur->cache->map = map;
    moteur->cache->entites = map->entites;

    return map;
}





static int adventime(t_monde *monde) {
    t_cache *cache = moteur->cache;
    t_joueur *joueur = monde->joueur;

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
 * @brief 
 * 
 * @return int 
 */
static int nouveauMonde() {
    int seed = -1;
    t_monde *monde = creerMonde(seed);

    const t_vecteur2 positionJoueur = getPointApparitionJoueur(monde->overworld);
    monde->joueur = creerJoueur(positionJoueur);

    /* ---------------------------------- Cache --------------------------------- */
    moteur->cache->monde = monde;

    return adventime(monde);
}





/**
 * @brief 
 * 
 * @param action 
 * @return state_main 
 */
state_main jouer(e_actionMonde action) {
    switch (action) {
        default:
            nouveauMonde();
            break;
    }


    return M_MENU;
}
