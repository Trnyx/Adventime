/**
 * @file temps.h
 * 
 * @brief Module de manipulation du temps
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
 * @enum e_cyle
 * @brief Enumérateur regroupant les cycles jour et nuit
 * 
 */
typedef enum {
    CYCLE_NUIT,
    CYCLE_JOUR,
} e_cycle;


/**
 * @enum e_jour
 * @brief Enumérateur regroupant les jours de la semaine
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


/**
 * @enum e_periode
 * @brief Enumérateur regroupant les différentes périodes de la journée en jeu
 * 
 */
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


/**
 * @struct t_temps
 * @brief Structures regroupant les données du temps en jeu
 * 
 */
typedef struct s_temps {
    unsigned int heures;            /**< L'heure en jeu */
    unsigned int minutes;           /**< Les minutes en jeu */
    unsigned int timestampJeu;      /**< Le timestamp en jeu */
    time_t timestamp;               /**< Le timestamp réel */

    e_cycle cycleJeu;               /**< Le cycle jour/nuit en jeu */
    e_cycle cycleVrai;              /**< Le cycle jour/nuit réel */
    e_periode periode;              /**< La période du jour en jeu */
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