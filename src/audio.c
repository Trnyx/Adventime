/**
 * @file audio.c
 * 
 * @brief Gestion des musiques et des bruitages
 * 
 * 
 * @author Clément Hibon
 * @date 1 février
 * @version 1.1
 */





#include <stdio.h>
#include <stdlib.h>

#include "../include/physique.h"
#include "../include/audio.h"
#include "../include/moteur.h"
#include "../include/entite.h"




/* ----------------------------- Pointeur Global ---------------------------- */

t_audio *audio = NULL;




/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


/* --------------------------------- Volume --------------------------------- */

/**
 * @brief Fonction permettant de changer le volume du channel spécifié
 * 
 * La channel ici n'est pas une piste audio mais plus une catégorie
 * 
 * @param channel Le channel où le volume sera modifié
 * @param nouveauVolume Le nouveau volume (en %)
 */
void changerVolume(const e_audio_channel channel, const float nouveauVolume) {
    switch (channel) {
        case CHANNEL_MASTER: 
            audio->masterVolume = nouveauVolume; 
            break;
        case CHANNEL_MUSIQUE: audio->musiqueVolume = nouveauVolume; break;
        case CHANNEL_BRUITAGE: audio->bruitageVolume = nouveauVolume; break;
    }
    

    Mix_Volume(-1, audio->bruitageVolume * audio->masterVolume * MIX_MAX_VOLUME);
    Mix_VolumeMusic(audio->musiqueVolume * audio->masterVolume * MIX_MAX_VOLUME * 0.75);
    Mix_MasterVolume(audio->masterVolume * MIX_MAX_VOLUME);
    
}





/* ---------------------------------- Play ---------------------------------- */

/**
 * @brief Joue une musique donnée en paramètre
 * 
 * @param music La musique qui sera joué
 * @param repeat Si la musique doit être répété
 * @param estLaSuite [Musique évolutive] Si la musique donnée est une autre version de la musique actuellement jouée
 */
void play_music(Mix_Music *music, boolean repeat, boolean estLaSuite) {
    Mix_PlayMusic(music, repeat ? -1 : 0);
    double tempsEcoule = 0.0;

    if (estLaSuite) 
        tempsEcoule = (moteur->frame - audio->timestampDebutMusique) / 1000;

    Mix_SetMusicPosition(tempsEcoule);
    audio->timestampDebutMusique = moteur->frame;
}



/**
 * @brief Joue un bruitage
 * 
 * @param sound Le bruitage à joué
 * @param channel Le channel dans lequel sera joué le bruitage, -1 si on veut utilisé le premier channel disponible 
 */
void play_bruitage(Mix_Chunk *sound, int channel) {
    if (sound != NULL)
        Mix_PlayChannel(channel, sound, 0);
}



/**
 * @brief Joue le bruit d'une entité
 * 
 * @param tag Le tag de l'entité originelle du bruit
 * @param angle L'angle entre l'entité est le joueur
 * @param distance La distance séparant l'entité du joueur
 */
void play_sonAmbiance(Mix_Chunk *bruitage, float angle, float distance) {
    int channel = -1;


    if (bruitage != NULL) {
        // On ajuste l'angle
        angle = revolution(angle - 90);

        // On converti la distance entre 0 et 255
        distance = (distance * 255) / 16;
        if (distance > 255)
            distance = 255;

        // Récupère le premier channel libre
        channel = Mix_PlayChannel(channel, bruitage, 1);

        
        Mix_UnregisterAllEffects(channel);
        Mix_SetPosition(channel, angle, distance);
    }
}





/**
 * @brief Sélectionne la musique à jouer en fonction du temps dans le jeu
 * 
 * @param temps Le temps actuel du jeu
 */
void selectionMusique(t_temps *temps) {
    t_musiques *musiques = audio->musiques;
    Mix_Music *musique = NULL;
    boolean estLaSuite = FAUX;


    switch (audio->musiqueType) {
        case MUSIC_AMBIANCE:
            switch (temps->periode) {
                case PERIODE_NUIT: musique = musiques->ambiance_nuit; break;

                case PERIODE_JOUR_MATIN: 
                    musique = musiques->ambiance_jour_matin; 
                    break;
                case PERIODE_JOUR_APRES_MIDI: 
                    musique = musiques->ambiance_jour_apres_midi; 
                    break;
                case PERIODE_JOUR_COUCHE_SOLEIL: 
                    musique = musiques->ambiance_jour_couche_soleil; 
                    estLaSuite = VRAI; 
                    break;

                default: musique = musiques->ambiance_jour_matin; break;
            }
            break;
            

        case MUSIC_COMBAT: musique = musiques->combat; break;

        case MUSIC_BOSS: musique = musiques->boss; break;
        
        
        default: musique = musiques->menu_principal; break;
    }


    play_music(musique, VRAI, estLaSuite);
}





/* -------------------------------------------------------------------------- */
/*                                 Chargement                                 */
/* -------------------------------------------------------------------------- */


/**
 * @brief Charge dans la structure musique la musique du boss correspondant au jour de la semaine
 * 
 * @param musiques Un pointeur sur la structure musique dans laquelle sera chargé la musique 
 * @param jour Le jour actuel de la semaine
 */
void loadMusiqueBoss(t_musiques *musiques, e_jour jour) {
    char buffer[64];
    sprintf(buffer, "assets/audio/musiques/boss/boss_%i.mp3", jour);

    if (musiques->boss != NULL) 
        Mix_FreeMusic(musiques->boss);

    musiques->boss = Mix_LoadMUS(buffer);
}


/**
 * @brief Charge tous les fichiers audio au sein des structures de musiques et de bruitages
 *
 * @param musiques L'adresse du pointeur de la structure de musique dans laquelle seront chargées les musiques
 * @param bruitages L'adresse du pointeur de la structure de bruitages dans laquelle seront chargées les bruitages
 * 
 * @return 0 Si tout se passe bien, -1 si echec
 */
int chargerAudio(t_musiques **musiques, t_bruitages **bruitages) {
    t_musiques *m = malloc(sizeof(t_musiques));
    if (m == NULL) {
        printf("Erreur mémoire : Impossible d'allouer la mémoire nécessaire pour les musiques");
        return -1;
    }


    t_bruitages *b = malloc(sizeof(t_bruitages));
    if (b == NULL) {
        printf("Erreur mémoire : Impossible d'allouer la mémoire nécessaire pour les bruitages");
        return -1;
    }



    /* -------------------------------- Musiques -------------------------------- */
    // Menu
    m->menu_principal = Mix_LoadMUS("assets/audio/musiques/menu.mp3");

    // Ambiance
    m->ambiance_jour_matin = Mix_LoadMUS("assets/audio/musiques/ambiance_jour_matin.ogg");
    m->ambiance_jour_apres_midi = Mix_LoadMUS("assets/audio/musiques/ambiance_jour_apres_midi.ogg");
    m->ambiance_jour_couche_soleil = Mix_LoadMUS("assets/audio/musiques/ambiance_jour_couche_soleil.ogg");
    m->ambiance_nuit = Mix_LoadMUS("assets/audio/musiques/ambiance_nuit.mp3");

    // Combat
    m->combat = Mix_LoadMUS("assets/audio/musiques/combat.mp3");
    // m->combat_nuit = Mix_LoadMUS("assets/audio/musiques/.mp3");
    m->boss = NULL;
    loadMusiqueBoss(m, getJourDeLaSemaine(time(NULL)));
    // m->combat_boss = Mix_LoadMUS("assets/audio/musiques/.mp3");
    
    
    /* -------------------------------- Bruitages ------------------------------- */
    // Menu
    b->menu_selection = Mix_LoadWAV("assets/audio/bruitages/menu_selection.ogg");

    // Joueur
    // b->joueur_degat = Mix_LoadWAV("assets/audio/bruitages/.ogg");
    // b->joueur_mort = Mix_LoadWAV("assets/audio/bruitages/.ogg");

    // Monstre
    // b->monstre_attaque = Mix_LoadWAV("assets/audio/bruitages/.ogg");
    // b->monstre_degat = Mix_LoadWAV("assets/audio/bruitages/.ogg");
    // b->monstre_mort = Mix_LoadWAV("assets/audio/bruitages/.ogg");

    // Animaux
    b->vache = Mix_LoadWAV("assets/audio/bruitages/vache.ogg");
    b->vache_degat = Mix_LoadWAV("assets/audio/bruitages/vache_degat.ogg");
    b->vache_mort = Mix_LoadWAV("assets/audio/bruitages/vache_mort.ogg");
    b->cochon = Mix_LoadWAV("assets/audio/bruitages/cochon.ogg");
    b->cochon_degat = Mix_LoadWAV("assets/audio/bruitages/cochon_degat.ogg");
    b->cochon_mort = Mix_LoadWAV("assets/audio/bruitages/cochon_mort.ogg");

    // Autres
    b->attaque = Mix_LoadWAV("assets/audio/bruitages/attaque.ogg");
    b->item_recuperation = Mix_LoadWAV("assets/audio/bruitages/item_recuperation.ogg");



    *musiques = m;
    *bruitages = b;


    return 0;
}





void chargerAudioPack(t_audioPack *pack, e_entiteTag tag) {
    switch (tag) {
        case TAG_JOUEUR:
            // pack->degat = audio->bruitages->joueur_degat;
            // pack->mort = audio->bruitages->joueur_mort;
            break;
        

        case TAG_MONSTRE_BASIC:
            // pack->degat = audio->bruitages->monstre_degat;
            // pack->mort = audio->bruitages->monstre_mort;
            break;
     
     
        case TAG_ANIMAL_VACHE:
            pack->normal = audio->bruitages->vache;
            pack->degat = audio->bruitages->vache_degat;
            pack->mort = audio->bruitages->vache_mort;
            break;
     
        case TAG_ANIMAL_COCHON:
            pack->normal = audio->bruitages->cochon;
            pack->degat = audio->bruitages->cochon_degat;
            pack->mort = audio->bruitages->cochon_mort;
            break;



        default:
            break;
    }


    pack->attaque = audio->bruitages->attaque;
}





/* -------------------------------------------------------------------------- */
/*                                    Init                                    */
/* -------------------------------------------------------------------------- */


/**
 * @brief Initialise, crée et alloue la mémoire pour l'audio du jeu
 * 
 * @return Un pointeur sur la structure gérant l'audio, NULL si echec
 */
t_audio* initAudio() {
    t_audio *a = malloc(sizeof(t_audio));


    if (a == NULL) {
        printf("Erreur mémoire : Impossible d'allouer la mémoire nécessaire pour l'audio\n");
        return NULL;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
        printf("WARNING : Erreur d'initialisation de SDL MIXER : %s\n", Mix_GetError());
        free(a);
        return NULL;
    }


    a->masterVolume = 1.0;
    a->musiqueVolume = 1.0;
    a->bruitageVolume = 1.0;


    chargerAudio(&a->musiques, &a->bruitages);
    a->musiqueType = MUSIC_MENU;
    a->timestampDebutMusique = 0;


    return a;
}





/**
 * @brief Alloue l'espace nécessaire pour un pack audio et le créer
 * 
 * Le pack audio correspond au bruitages que produit une entité
 * 
 * @return Un pointeur sur le pack audio créé, NULL si echec
 */
t_audioPack *creerAudioPack() {
    t_audioPack *pack = malloc(sizeof(t_audioPack));

    if (pack == NULL) {
        printf("Erreur mémoire : impossible d'allouer l'espace nécessaire pour l'audio pack\n");
        return NULL;
    }


    pack->normal = NULL;
    pack->attaque = NULL;
    pack->degat = NULL;
    pack->mort = NULL;


    return pack;
}





/* -------------------------------------------------------------------------- */
/*                                 Destruction                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief Detruit l'audio est libère la mémoire allouée pour ce dernier
 * 
 * @param audio L'adresse du pointeur sur l'audio 
 */
void detruireAudio(t_audio **audio) {
    if (audio != NULL && *audio != NULL) {

        t_musiques *musiques = (*audio)->musiques;
        t_bruitages *bruitages = (*audio)->bruitages;





        /* -------------------------------- Musiques -------------------------------- */
        if (musiques != NULL) {
            // Mix_FreeMusic((*musiques)->);

            Mix_FreeMusic((*audio)->musiques->menu_principal);
            Mix_FreeMusic((*audio)->musiques->ambiance_jour_matin);
            Mix_FreeMusic((*audio)->musiques->ambiance_jour_apres_midi);
            Mix_FreeMusic((*audio)->musiques->ambiance_jour_couche_soleil);
            Mix_FreeMusic((*audio)->musiques->ambiance_nuit);
            Mix_FreeMusic((*audio)->musiques->combat);
            Mix_FreeMusic((*audio)->musiques->boss);

            free(musiques);
            musiques = NULL;
        }
        

        /* -------------------------------- Bruitages ------------------------------- */
        if (bruitages != NULL) {
            // Mix_FreeChunk((*bruitages)->);

            // Menu
            Mix_FreeChunk((*audio)->bruitages->menu_selection);

            // Joueur
            // Mix_FreeChunk((*audio)->bruitages->joueur_degat);
            // Mix_FreeChunk((*audio)->bruitages->joueur_mort);

            // Monstre
            // Mix_FreeChunk((*audio)->bruitages->monstre_degat);
            // Mix_FreeChunk((*audio)->bruitages->monstre_mort);

            // Animaux
            Mix_FreeChunk((*audio)->bruitages->vache);
            Mix_FreeChunk((*audio)->bruitages->vache_degat);
            Mix_FreeChunk((*audio)->bruitages->vache_mort);
            Mix_FreeChunk((*audio)->bruitages->cochon);
            Mix_FreeChunk((*audio)->bruitages->cochon_degat);
            Mix_FreeChunk((*audio)->bruitages->cochon_mort);

            // Autres
            Mix_FreeChunk((*audio)->bruitages->attaque);
            Mix_FreeChunk((*audio)->bruitages->item_recuperation);

            free(bruitages);
            bruitages = NULL;
        }
        

        free(*audio);
        *audio = NULL;

        Mix_CloseAudio();

    }
}





/**
 * @brief Detruit le pack audio est libère la mémoire allouée pour ce dernier
 * 
 * @param pack L'adresse du pointeur sur le pack audio
 */
void detruireAudioPack(t_audioPack **pack) {
    if (pack != NULL && *pack != NULL) {
        free(*pack);
        *pack = NULL;
    }
}