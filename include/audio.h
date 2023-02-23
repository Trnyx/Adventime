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





#define NB_CHANNELS





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief Structure contenant toutes les musiques du jeu
 */
typedef struct s_musiques {
    // Menu Principal
    Mix_Music *menu_principal;

    // Ambiance
    Mix_Music *ambiance_jour;
    Mix_Music *ambiance_nuit;

    // Combat
    Mix_Music *combat;
    // Mix_Music *combat_nuit;
    // Mix_Music *combat_boss;
    
} t_musiques;


/**
 * @brief Structure contenant tous les bruitages du jeu
 */
typedef struct s_bruitages {
    // Menu :
    Mix_Chunk *menu_selection;

    // Joueur :
    Mix_Chunk *joueur_attaque;
    Mix_Chunk *joueur_degat;
    Mix_Chunk *joueur_mort;
    
    // Monstre :
    Mix_Chunk *monstre_attaque;
    Mix_Chunk *monstre_degat;
    Mix_Chunk *monstre_mort;

    // Autres :
    Mix_Chunk *item_recuperation;
} t_bruitages;



/**
 * @brief  
 */
typedef struct s_audio {
    t_musiques *musiques;
    t_bruitages *bruitages;
} t_audio;





/* -------------------------------------------------------------------------- */
/*                                Enumerations                                */
/* -------------------------------------------------------------------------- */





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_audio *initAudio(void);
int chargerAudio(int volume, t_musiques **musiques, t_bruitages **bruitages);
int detruireAudio(t_musiques **musiques, t_bruitages **bruitages);

void changerVolume(int nouveauVolume);
void play_music(Mix_Music *music);
void play_bruitage(Mix_Chunk *sound, int channel);






#endif