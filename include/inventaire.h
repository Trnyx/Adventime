/*
 * \file 
 *
 * \brief
 *
 * \author
 */



#ifndef _JEU_INVENTAIRE_
#define _JEU_INVENTAIRE_





/*
 * \struct t_itemSlot
 * \brief
 */
typedef struct s_itemSlot {
    int slot;
    char tag; // type ItemTag
    int quantite;
} t_itemSlot;



/*
 * \struct t_inventaire
 * \brief
 */
typedef struct s_inventaire {
    int monnaie;
    t_itemSlot slots[12];
} t_inventaire;





#endif