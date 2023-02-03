/**
 * @file entite.h
 * 
 * @brief 
 * 
 * @author Clément Hibon
 * @date 3 février
 * @version 1.1
 */




#ifndef _JEU_ENTITE_
#define _JEU_ENTITE_





/**
 * @struct t_entite
 * @brief Structure modélisant une entité
 */
typedef struct s_entite {
    #include <attributs_entite.h>
    t_vecteur2 position;
} t_entite;





/* -------------------------------------------------------------------------- */
/*                                  Fonctions                                 */
/* -------------------------------------------------------------------------- */


t_entite* creerEntite();
void deplacerEntite(t_entite entite);





#endif