/*
 * \file 
 *
 * \brief
 *
 * \author
 */



#ifndef _JEU_ENTITE_
#define _JEU_ENTITE_





/*
 * \struct t_entite
 * \brief Structure modélisant une entité
 */
typedef struct s_entite {
    #include <attributs_entite.h>
} t_entite;



t_entite* creerEntite();
void deplacerEntite(t_entite entite);





#endif