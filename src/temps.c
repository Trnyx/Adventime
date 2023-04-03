/**
 * @file temps.c
 * 
 * @brief 
 * 
 * @author Clément Hibon
 * @date 23 février
 * @version 1.1
 */





#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "../include/temps.h"
#include "../include/physique.h"
#include "../include/moteur.h"
#include "../include/audio.h"
#include "../include/animal.h"





/* -------------------------------------------------------------------------- */
/*                                     Get                                    */
/* -------------------------------------------------------------------------- */


/**
 * @brief Récupère le jour de la semaine
 * 
 * @param timestamp Le timestamp actuel
 * @return e_jour, le jour de la semaine 
 */
e_jour getJourDeLaSemaine(const time_t timestamp) {
    struct tm *temps = localtime(&timestamp);
    return temps->tm_wday;
}



/**
 * @brief Récupère le cycle jour/nuit du jeu
 * 
 * @param temps Un pointeur sur la structure temps du jeu
 * @return e_cycle, si il fait jour ou nuit
 */
e_cycle getCycleJeu(t_temps *temps) {
    if (temps->heures >= HEURE_JEU_LEVE_SOLEIL && temps->heures < HEURE_JEU_NUIT) return CYCLE_JOUR;
    else return CYCLE_NUIT;
}


/**
 * @brief Récupère le cycle jour/nuit réel
 * 
 * @param timestamp Le timestamp actuel 
 * @return e_cycle, si il fait jour ou nuit
 */
e_cycle getCycleVrai(const time_t timestamp) {
    struct tm *temps = localtime(&timestamp);

    if (temps->tm_hour >= HEURE_VRAI_JOUR && temps->tm_hour < HEURE_VRAI_NUIT) return CYCLE_JOUR;
    else return CYCLE_NUIT;
}



/**
 * @brief Récupère la période de la journée
 * 
 * @param temps 
 * @return e_periode, la periode de la journée
 */
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
 * @brief Obtient et actualise le temps du jeu en fonction du temps réel
 * 
 * @param temps Un pointeur sur la structure temps du jeu
 * @param timestamp Le timestamp réel permettant d'actualiser le temps du jeu
 * 
 * @return La structure de temps donnée en paramètre
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


/**
 * @brief Gère tous les évènements temporels du jeu
 * 
 * Ces évènements se basent sur le temps réel tout comme le temps en jeu
 * 
 * @param temps Un pointeur sur le temps
 * @param timestamp Le timestamp réel 
 */
void gestionnaireTempsEvenements(t_temps *temps, const time_t timestamp) {
    t_cache *cache = moteur->cache;
    e_periode periodePrecedente = temps->periode;


    /* ------------------------------ Actualisation ----------------------------- */

    getTemps(temps, timestamp);
    

    /* --------------------------------- Musique -------------------------------- */

    // La musique du jeu dépend du moment de la journée dans le jeu
    // Lorsque l'on change de période, on change la musique
    if (periodePrecedente != temps->periode) {
        selectionMusique(temps);
    }


    /* ------------------------------- Evenements ------------------------------- */

    struct tm *tempsActuel = localtime(&timestamp);
    struct tm *dernierRenouvellement = localtime(&cache->monde->timestampRenouvellement);


    // Renouvellement
    if (tempsActuel->tm_wday != dernierRenouvellement->tm_wday && tempsActuel->tm_hour >= HEURE_VRAI_RENOUVELLEMENT) {
        cache->monde->timestampRenouvellement = timestamp;

        apparitionTroupeau(cache->entites, cache->map);
        chargerBoss();
    }
}





/* -------------------------------------------------------------------------- */
/*                                  Affichage                                 */
/* -------------------------------------------------------------------------- */





/* -------------------------------------------------------------------------- */
/*                               Initialisation                               */
/* -------------------------------------------------------------------------- */


/**
 * @brief Alloue l'espace nécessaire pour le temps et le créer
 * 
 * @param timestamp Le timestamp réel permettant d'intialiser le temps du jeu
 * 
 * @return Un pointeur sur le temps, NULL en cas d'echec
 */
t_temps* initTemps(const time_t timestamp) {
    t_temps *temps = calloc(1, sizeof(t_temps));

    if (temps == NULL) {
        printf("Erreur mémoire : Impossible d'allouer la place nécessaire pour le temps\n");
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
 * @brief Detruit le temps est libère la mémoire allouée pour ce dernier
 * 
 * @param temps L'adresse du pointeur sur le temps 
 */
void detruireTemps(t_temps **temps) {
    if (temps != NULL && *temps != NULL) {
        free(*temps);
        *temps = NULL;
    }
}