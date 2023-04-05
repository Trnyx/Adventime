/**
 * @file coffre.h
 * 
 * @brief 
 * 
 * @author Clément Hibon
 * @date 31 mars
 * @version 1.1
 */





#ifndef _JEU_COFFRE_
#define _JEU_COFFRE_





#include "stockage.h"





/* -------------------------------------------------------------------------- */
/*                                 Structures                                 */
/* -------------------------------------------------------------------------- */


/**
 * @struct t_coffre
 * @brief Structure modélisant un coffre
 * 
 */
typedef struct s_coffre {
    struct s_entite;            /**< "Etend" la structure entite */
    t_stockage *stockage;       /**< Le stockage du coffre */
} t_coffre;





/* -------------------------------------------------------------------------- */
/*                                  Fontions                                  */
/* -------------------------------------------------------------------------- */


boolean coffreEstVide(t_coffre *coffre);

t_coffre *creerCoffre(const t_vecteur2 position);
void detruireCoffre(t_coffre **coffre);





#endif