/**
 * @file audio.h
 * 
 * @brief Module de manipulation pour l'audio
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
#include "entite.h"
#include "temps.h"





#define NB_CHANNELS





/* -------------------------------------------------------------------------- */
/*                                Enumerations                                */
/* -------------------------------------------------------------------------- */


/**
 * @enum e_audio_channel
 * @brief Les différents type de channel controlable 
 * 
 */
typedef enum {
    /*! Le channel principal */
    CHANNEL_MASTER,
    /*! Le channel utilisé pour la musique */
    CHANNEL_MUSIQUE,
    /*! Les channels pour les bruitages */
    CHANNEL_BRUITAGE,
} e_audio_channel;



/**
 * @enum e_musiques_type
 * @brief Les différents types de musiques 
 *  
 */
typedef enum {
    /*! Indique qu'il faut jouer la musique du menu */
    MUSIC_MENU,
    /*! Indique qu'il faut jouer la musique d'ambiance */
    MUSIC_AMBIANCE,
    /*! Indique qu'il faut jouer la musique de combat */
    MUSIC_COMBAT,
    /*! Indique qu'il faut jouer la musique du boss */
    MUSIC_BOSS,
} e_musiques_type;





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @struct t_musiques
 * @brief Structure contenant toutes les musiques du jeu
 */
typedef struct s_musiques {
    // Menu Principal
    Mix_Music *menu_principal;                  /**< La musique du menu principal */

    // Ambiance
    Mix_Music *ambiance_jour_matin;             /**< La musique d'ambiance du matin (en jeu) */
    Mix_Music *ambiance_jour_apres_midi;        /**< La musique d'ambiance de l'après midi (en jeu) */
    Mix_Music *ambiance_jour_couche_soleil;     /**< La musique d'ambiance du couché de soleil (en jeu) */
    Mix_Music *ambiance_nuit;                   /**< La musique d'ambiance de nuit (en jeu) */

    // Combat
    Mix_Music *combat;                          /**< La musique de combat */
    // Mix_Music *combat_nuit;
    Mix_Music *boss;                            /**< La musique du boss du jour */
    
} t_musiques;


/**
 * @struct t_bruitages
 * @brief Structure contenant tous les bruitages du jeu
 */
typedef struct s_bruitages {
    // Menu :
    Mix_Chunk *menu_selection;          /**< Bruit lorsque l'on clique sur un bouton */

    // Joueur :
    Mix_Chunk *joueur_attaque;          /**< Bruit lorsque le joueur attaque */
    Mix_Chunk *joueur_degat;            /**< Bruit lorsque le joueur prend des dégâts */
    Mix_Chunk *joueur_mort;             /**< Bruit lorsque le joueur meurt */
    
    // Monstre :
    Mix_Chunk *monstre_attaque;         /**< Bruit lorsqu'un monstre attaque */
    Mix_Chunk *monstre_degat;           /**< Bruit lorsqu'un monstre prend des dégâts */
    Mix_Chunk *monstre_mort;            /**< Bruit lorsqu'un monstre meurt */

    // Animaux
    Mix_Chunk *vache;                   /**< Bruit d'une vache */
    Mix_Chunk *cochon;                  /**< Bruit d'un cochon */

    // Autres :
    Mix_Chunk *degats;                  /**< Bruit lorsque des dégâts sont mis */
    Mix_Chunk *item_recuperation;       /**< Bruit lorsque qu'un item est récupéré */
} t_bruitages;



/**
 * @struct t_audio
 * @brief Structures contenant toutes les informations pour le fonctionnement de l'audio
 */
typedef struct s_audio {
    t_musiques *musiques;           /**< Les musiques du jeu */
    t_bruitages *bruitages;         /**< Les bruitages du jeu */

    e_musiques_type musiqueType;    /**< Le type de la musique qui est entrain d'être joué */

    int timestampDebutMusique;      /**< Timestamp de début de la musique */

    float masterVolume;             /**< Le volume général */
    float musiqueVolume;            /**< Le volume de la musique */
    float bruitageVolume;           /**< Le volume des bruitages */
} t_audio;


// Le moteur est en global pour faciliter l'accès
extern t_audio *audio;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_audio *initAudio(void);
int chargerAudio(t_musiques **musiques, t_bruitages **bruitages);
void detruireAudio(t_audio **audio);

void changerVolume(const e_audio_channel channel, const float nouveauVolume);
void play_music(Mix_Music *music, boolean repeat, boolean estLaSuite);
void play_bruitage(Mix_Chunk *sound, int channel);
void play_sonAmbiance(e_entiteTag tag, float angle, float distance);
void selectionMusique(t_temps *temps);





#endif