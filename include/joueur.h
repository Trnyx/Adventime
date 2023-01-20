#ifndef _JEU_JOUEUR_
#define _JEU_JOUEUR_



#include <statistiques.h>
#include <inventaire.h>





typedef struct s_joueur {
    #include <attributs_entite.h>

    /** The name of the Player */
    char *name;
    /** The different statistics of the Player */
    t_statistiques statistiques;
    /** The inventory of the Player */
    t_inventaire inventaire; 
    
} t_joueur;





#endif