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


/**
 * @brief 
 * 
 */
typedef enum {
    CHANNEL_MASTER,
    CHANNEL_MUSIQUE,
    CHANNEL_BRUITAGE,
} e_audio_channel;



/**
 * @brief 
 * 
 */
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
    Mix_Music *menu_principal;                  /**< */

    // Ambiance
    Mix_Music *ambiance_jour_matin;             /**< */
    Mix_Music *ambiance_jour_apres_midi;        /**< */
    Mix_Music *ambiance_jour_couche_soleil;     /**< */
    Mix_Music *ambiance_nuit;                   /**< */

    // Combat
    Mix_Music *combat;                          /**< */
    // Mix_Music *combat_nuit;
    Mix_Music *boss;                            /**< */
    
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

    // Animaux
    Mix_Chunk *vache;                   /**< */
    Mix_Chunk *cochon;                  /**< */

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

    float masterVolume;             /**< */
    float musiqueVolume;            /**< */
    float bruitageVolume;           /**< */
} t_audio;


// Le moteur est en global pour faciliter l'accès
extern t_audio *audio;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_audio *initAudio(void);
int chargerAudio(const float volume, t_musiques **musiques, t_bruitages **bruitages);
void detruireAudio(t_audio **audio);

void changerVolume(const e_audio_channel channel, const float nouveauVolume);
void play_music(Mix_Music *music, boolean repeat, boolean estLaSuite);
void play_bruitage(Mix_Chunk *sound, int channel);
void play_sonAmbiance(e_entiteTag tag, float angle, float distance);
void selectionMusique(t_temps *temps);





#endif