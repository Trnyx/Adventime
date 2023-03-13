/**
 * @file audio.h
 * 
 * @brief 
 * 
 * 
 * @author Clément Hibon
 * @date 1 février
 * @version 1.1
 */



#ifndef _JEU_AUDIO_
#define _JEU_AUDIO_



#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "utilitaire.h"
#include "temps.h"





#define NB_CHANNELS





/* -------------------------------------------------------------------------- */
/*                                Enumerations                                */
/* -------------------------------------------------------------------------- */


typedef enum {
    MUSIC_MENU,
    MUSIC_AMBIANCE,
    MUSIC_COMBAT,
    MUSIC_BOSS,
} e_musiques_type;





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief Structure contenant toutes les musiques du jeu
 */
typedef struct s_musiques {
    // Menu Principal
    Mix_Music *menu_principal;      /**< */

    // Ambiance
    Mix_Music *ambiance_jour_leve_soleil;       /**< */
    Mix_Music *ambiance_jour_matin;       /**< */
    Mix_Music *ambiance_jour_apres_midi;       /**< */
    Mix_Music *ambiance_jour_couche_soleil;       /**< */
    Mix_Music *ambiance_nuit;       /**< */

    // Combat
    Mix_Music *combat;              /**< */
    // Mix_Music *combat_nuit;
    Mix_Music *boss;
    
} t_musiques;


/**
 * @brief Structure contenant tous les bruitages du jeu
 */
typedef struct s_bruitages {
    // Menu :
    Mix_Chunk *menu_selection;          /**< */

    // Joueur :
    Mix_Chunk *joueur_attaque;          /**< */
    Mix_Chunk *joueur_degat;            /**< */
    Mix_Chunk *joueur_mort;             /**< */
    
    // Monstre :
    Mix_Chunk *monstre_attaque;         /**< */
    Mix_Chunk *monstre_degat;           /**< */
    Mix_Chunk *monstre_mort;            /**< */

    // Autres :
    Mix_Chunk *item_recuperation;       /**< */
} t_bruitages;



/**
 * @brief  
 */
typedef struct s_audio {
    t_musiques *musiques;           /**< */
    t_bruitages *bruitages;         /**< */

    e_musiques_type musiqueType;    /**< */
    int timestampDebutMusique;      /**< */
    int tempsEcoulee;               /**< */
} t_audio;


// Le moteur est en global pour faciliter l'accès
extern t_audio *audio;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_audio *initAudio(void);
int chargerAudio(int volume, t_musiques **musiques, t_bruitages **bruitages);
void detruireAudio(t_audio **audio);

void changerVolume(int nouveauVolume);
void play_music(Mix_Music *music, boolean repeat);
void play_bruitage(Mix_Chunk *sound, int channel);
void selectionMusique(t_temps *temps);





#endif