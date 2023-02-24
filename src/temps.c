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





/* -------------------------------------------------------------------------- */
/*                                     Get                                    */
/* -------------------------------------------------------------------------- */


e_jour getJourDeLaSemaine(time_t *timestamp) {
    struct tm *temps = localtime(timestamp);
    return temps->tm_wday;
}



t_temps getTemps(time_t t) {
    // 1 heure réelle écoulée représente NOMBRE_JOUR écoulée dans le jeu
    // Pour convertir le temps réel en temps du jeu il faut donc faire les calculs suivant
    //  Timestamp dans le jeu :
    //      Le timestamp représente le nombre de secondes écoulées depuis le 1er Jan. 1970
    //      On converti se temps en nombre de secondes écoulé depuis le début d'un jour dans le jeu
    //      Timestamp dans le jeu   =>  timestampJ = timestampR % TEMPS_JOUR
    //
    //  Secondes dans le jeu    =>  secondesJ = timestampJ / 3600
    //  Minutes dans le jeu     =>  minutesJ  = secondesJ / 60
    //  Heure dans le jeu       =>  heuresJ   = timestampJ / 3600

    const unsigned int timestamp = t % TEMPS_JOUR;

    // const unsigned int heures = timestamp / 24;
    // const unsigned int minutes = (timestamp / 24) % 60;


    const unsigned int heures = (timestamp * 24) / TEMPS_JOUR;
    const unsigned int minutes = ((timestamp * (24 * 60)) / TEMPS_JOUR) - (heures * 60);

    t_temps temps = {
        heures, 
        minutes,
        timestamp
    };


    return temps;
}





/* -------------------------------------------------------------------------- */
/*                                  Affichage                                 */
/* -------------------------------------------------------------------------- */



/* -------------------------------------------------------------------------- */
/*                                  Creation                                  */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 * @param timestamp 
 * @return t_temps* 
 */
t_temps *initTemps(time_t timestamp) {
    t_temps *temps = malloc(sizeof(temps));

    *temps = getTemps(timestamp);

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