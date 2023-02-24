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
    NUIT,
    JOUR,
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
    unsigned int heures;
    unsigned int minutes;
    unsigned int timestamp;
} t_temps;


/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_temps* initTemps(time_t timestamp);
void detruireTemps(t_temps **temps);

e_jour getJourDeLaSemaine(time_t *timestamp);
t_temps getTemps(time_t t);





#endif