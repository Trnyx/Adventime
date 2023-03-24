/**
 * @file animation.h
 * 
 * @brief Module pour manipuler les animations
 * 
 * @author Clément Hibon
 * @date 10 mars
 * @version 1.1
 */



#ifndef _JEU_ANIMATIOn_
#define _JEU_ANIMATIOn_





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @struct t_animation
 * @brief Structure modélisant une animation
 * 
 */
typedef struct s_animation {
    unsigned int vitesse;           /**< Temps (en milisecondes) entre chaque frame de l'animation */
    unsigned int nombreFrame;       /**< Nombre de frame pour une animation complète */
    unsigned int frameCourante;     /**< Indice de la frame active */
    unsigned int timestampUpdate;   /**< Timestamp du dernier changement */
} t_animation;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_animation* creerAnimation(const unsigned int vitesse, const unsigned int nombreFrame);
void detruireAnimation(t_animation **animation);
void updateAnimation(t_animation *animation, const unsigned int timestamp);





#endif