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



// #include <SDL2/SDL.h>
// #include <SDL2/SDL_mixer.h>



#define NB_CHANNELS





/**
 * @brief Structure contenant toutes les musiques du jeu
 */
typedef struct s_musiques {
    // Menu Principal
    // Ambiance Jour
    // Ambiance Nuit
    // Combat Jour
    // Combat Nuit
    // Combat Boss
} t_musiques;



/**
 * @brief Structure contenant tous les bruitages du jeu
 */
typedef struct s_bruitages {
    // Menu :
    //  - Menu sélection
    // Joueur :
    //  - Attaque
    //  - Dégat recu
    //  - Mort
    // Monstre :
    //  - Attaque
    //  - Dégat recu
    //  - Mort
    // Autres :
    //  - Item récupération
} t_bruitages;





int chargerAudio(int volume, t_musiques **musiques, t_bruitages **bruitages);
int detruireAudio(t_musiques **musiques, t_bruitages **bruitages);
void changerVolume(int nouveauVolume);






#endif