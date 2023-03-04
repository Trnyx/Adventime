/**
 * @file temps.h
 * 
 * @brief 
 * 
 * @author Clément Hibon
 * @date 23 février
 * @version 1.1
 */



#ifndef _JEU_TEMPS_
#define _JEU_TEMPS_





#include <time.h>





/* -------------------------------------------------------------------------- */
/*                                Enumérations                                */
/* -------------------------------------------------------------------------- */


/**
 * @brief 
 * 
 */
typedef enum {
    CYCLE_NUIT,
    CYCLE_JOUR,
} e_cycle;


/**
 * @brief 
 * 
 */
typedef enum {
    DIMANCHE,
    LUNDI,
    MARDI,
    MERCREDI,
    JEUDI,
    VENDREDI,
    SAMEDI,
} e_jour;


typedef enum {
    PERIODE_JOUR_LEVE_SOLEIL,
    PERIODE_JOUR_MATIN,
    PERIODE_JOUR_APRES_MIDI,
    PERIODE_JOUR_COUCHE_SOLEIL,
    PERIODE_NUIT,
} e_periode;





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


typedef struct s_temps {
    unsigned int heures;            /**< */
    unsigned int minutes;           /**< */
    unsigned int timestampJeu;      /**< */
    unsigned int timestamp;         /**< */

    e_cycle cycleJeu;               /**< */
    e_cycle cycleVrai;              /**< */
    e_periode periode;              /**< */
} t_temps; 


/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_temps* initTemps(const time_t timestamp);
void detruireTemps(t_temps **temps);

e_jour getJourDeLaSemaine(const time_t timestamp);
e_cycle getCycleJeu(t_temps *temps);
e_cycle getCycleVrai(const time_t timestamp);
t_temps* getTemps(t_temps *temps, const time_t timestamp);

void gestionnaireTempsEvenements(t_temps *temps, const time_t timestamp);





#endif