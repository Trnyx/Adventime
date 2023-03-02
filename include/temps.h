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


typedef enum {
    CYCLE_NUIT,
    CYCLE_JOUR,
} e_cycle;


typedef enum {
    DIMANCHE,
    LUNDI,
    MARDI,
    MERCREDI,
    JEUDI,
    VENDREDI,
    SAMEDI,
} e_jour;





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