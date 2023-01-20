#ifndef _JEU_MONSTRE_
#define _JEU_MONSTRE_



#include <statistiques.h>





typedef enum s_monstreTag {
    OISEAU
} t_monstreTag;


typedef enum s_monstreType {
    MONTAGNARD,
    PLANTE
} t_monstreType;




/**
 * The data of a Monster saved in the database
 */
typedef struct s_monstre {
    struct entite_s;
    /** The current name of the Monster */
    char* name;
    /** The tag of the Monster */
    t_monstreTag tag; // type : MonstreTag
    /** The type of the Monster */
    t_monstreType type; // type : MonstreType
    /** The statistics of the Monster */
    t_statistiques statistiques;
    /** The basic data of the statistics of the Monster */
    t_baseStatistiques baseStatistiques;
} t_monstre;





#endif