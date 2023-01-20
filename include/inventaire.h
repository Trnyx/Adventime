#ifndef _JEU_INVENTAIRE_
#define _JEU_INVENTAIRE_





typedef struct s_itemSlot {
    int slot;
    char tag; // type ItemTag
    int quantite;
} t_itemSlot;



typedef struct s_inventaire {
    int monnaie;
    t_itemSlot slots[12];
} t_inventaire;





#endif