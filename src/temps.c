/**
 * @file temps.c
 * 
 * @brief 
 * 
 * @author Clément Hibon
 * @date 23 février
 * @version 1.1
 */



#include <SDL2/SDL.h>
// #include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/temps.h"
#include "../include/physique.h"
#include "../include/moteur.h"
#include "../include/audio.h"





/* -------------------------------------------------------------------------- */
/*                                     Get                                    */
/* -------------------------------------------------------------------------- */


/**
 * @brief Get the Jour De La Semaine object
 * 
 * @param timestamp 
 * @return e_jour 
 */
e_jour getJourDeLaSemaine(const time_t timestamp) {
    struct tm *temps = localtime(&timestamp);
    return temps->tm_wday;
}



/**
 * @brief Get the Cycle Jeu object
 * 
 * @param temps 
 * @return e_cycle 
 */
e_cycle getCycleJeu(t_temps *temps) {
    if (temps->heures >= HEURE_JEU_LEVE_SOLEIL && temps->heures < HEURE_JEU_NUIT) return CYCLE_JOUR;
    else return CYCLE_NUIT;
}


/**
 * @brief Get the Cycle Vrai object
 * 
 * @param timestamp
 * @return e_cycle 
 */
e_cycle getCycleVrai(const time_t timestamp) {
    struct tm *temps = localtime(&timestamp);

    if (temps->tm_hour >= HEURE_VRAI_JOUR && temps->tm_hour < HEURE_VRAI_NUIT) return CYCLE_JOUR;
    else return CYCLE_NUIT;
}



e_periode getPeriode(t_temps *temps) {
    e_periode periode = temps->periode;


    if (temps->minutes == 0) {
        if ( (temps->heures >= HEURE_JEU_LEVE_SOLEIL) && (temps->heures < HEURE_JEU_LEVE_SOLEIL) )
            periode = PERIODE_JOUR_LEVE_SOLEIL;
        else if ( (temps->heures >= HEURE_JEU_MATIN) && (temps->heures < HEURE_JEU_APRES_MIDI) )
            periode = PERIODE_JOUR_MATIN;
        else if ( (temps->heures >= HEURE_JEU_APRES_MIDI) && (temps->heures < HEURE_JEU_COUCHE_SOLEIL) )
            periode = PERIODE_JOUR_APRES_MIDI;
        else if ( (temps->heures >= HEURE_JEU_COUCHE_SOLEIL) && (temps->heures < HEURE_JEU_NUIT ) )
            periode = PERIODE_JOUR_COUCHE_SOLEIL;
        else 
            periode = PERIODE_NUIT;
    }


    return periode;
}





/**
 * @brief Get the Temps object
 * 
 * @param t 
 * @return t_temps 
 */
t_temps* getTemps(t_temps *temps, const time_t timestamp) {
    // 1 heure réelle écoulée représente NOMBRE_JOUR écoulée dans le jeu
    // Timestamp dans le jeu :
    //      Le timestamp représente le nombre de secondes écoulées depuis le 1er Jan. 1970
    //      On converti se temps en nombre de secondes écoulé depuis le début d'un jour dans le jeu
    //      Timestamp dans le jeu   =>  timestampJ = timestampR % TEMPS_JOUR
    

    const unsigned int t = timestamp % TEMPS_JOUR;
    const unsigned int heures = (t * 24) / TEMPS_JOUR;
    const unsigned int minutes = ((t * (24 * 60)) / TEMPS_JOUR) - (heures * 60);


    temps->heures = heures;
    temps->minutes = minutes;
    temps->timestampJeu = t;
    temps->timestamp = timestamp;

    temps->cycleJeu = getCycleJeu(temps);
    if (!heures) {
        temps->cycleVrai = getCycleVrai(timestamp);
    }

    temps->periode = getPeriode(temps);


    return temps;
}





/* -------------------------------------------------------------------------- */
/*                            Gestion d'évènements                            */
/* -------------------------------------------------------------------------- */


void gestionnaireTempsEvenements(t_temps *temps, const time_t timestamp) {
    e_cycle cyclePrecedent = temps->cycleJeu;
    e_periode periodePrecedente = temps->periode;
    getTemps(temps, timestamp);
    

    if (periodePrecedente != temps->periode) {
        if (cyclePrecedent != temps->cycleJeu)
            audio->timestampDebutMusique = moteur->frame;
        
        selectionMusique(temps);
    }
}





/* -------------------------------------------------------------------------- */
/*                                  Affichage                                 */
/* -------------------------------------------------------------------------- */





/* -------------------------------------------------------------------------- */
/*                               Initialisation                               */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param timestamp 
 * @return t_temps 
 */
t_temps* initTemps(const time_t timestamp) {
    t_temps *temps = malloc(sizeof(t_temps));

    if (temps == NULL) {
        printf("Erreur mémoire : Impossible d'allouer la place nécessaire pour le temps\n");
        free(temps);
        return NULL;
    }

    getTemps(temps, timestamp);
    temps->cycleVrai = getCycleVrai(timestamp);

    return temps;
}





/* -------------------------------------------------------------------------- */
/*                                 Destruction                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param temps 
 */
void detruireTemps(t_temps **temps) {
    if (temps != NULL && *temps != NULL) {
        free(*temps);
        *temps = NULL;
    }
}