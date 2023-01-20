#ifndef _JEU_STATISTIQUES_
#define _JEU_STATISTIQUES_





typedef struct s_statistiques {
    #include <attributs_statistiques.h>

    int pvMax;
    int experience;
    int niveau;
} t_statistiques;



typedef struct s_base_statistiques {
    #include <attributs_statistiques.h>
    
    int experience_courbe;
} t_baseStatistiques;





#endif