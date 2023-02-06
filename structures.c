
// typedef struct s_vecteur2 {
//     float x;
//     float y;
// } t_vecteur2;



// typedef struct s_vecteur3 {
//     float x;
//     float y;
//     float z;
// } t_vecteur3;





// typedef struct entite_s {
//     /** The ID of the Entity */
//     int id;
//     /** The current position of the Entity */
//     t_vecteur2 position;
//     /** */
//     // Texture / Tag
// } Entite;





// typedef struct s_itemSlot {
//     int slot;
//     char tag; // type ItemTag
//     int quantite;
// } t_itemSlot;



// typedef struct s_inventaire {
//     int monnaie;
//     t_itemSlot slots[12];
// } t_inventaire;



// typedef struct s_statistiques {
//     int pvMax;
//     int pv;
//     int niveau;
//     int exp;
//     int attaque;
//     int defense;
//     int vitesse;
// } t_statistiques;



// typedef struct s_base_statistiques {
//     int pv;
//     int exp;
//     int attaque;
//     int defense;
//     int vitesse;
// } t_baseStatistiques;





// /**
//  * The data of a Player saved in the database
//  */
// typedef struct s_joueur {
//     struct entite_s;
//     /** The name of the Player */
//     char *name;
//     /** The different statistics of the Player */
//     t_statistiques statistiques;
//     /** The inventory of the Player */
//     t_inventaire inventaire; 
// } t_joueur;





typedef enum s_monstreTag {
    OISEAU
} e_monstreTag;


typedef enum s_monstreType {
    MONTAGNARD,
    PLANTE
} e_typeMonstre;




/**
 * The data of a Monster saved in the database
 */
typedef struct s_monstre {
    struct entite_s;
    /** The current name of the Monster */
    char* name;
    /** The tag of the Monster */
    e_monstreTag tag; // type : MonstreTag
    /** The type of the Monster */
    e_typeMonstre type; // type : MonstreType
    /** The statistics of the Monster */
    t_statistiques statistiques;
    /** The basic data of the statistics of the Monster */
    t_baseStatistiques baseStatistiques;
} t_monstre;




// /**
//  * The data of a Monster saved in the database
//  */
// typedef struct s_monstre {
//     struct entite_s;
//     /** The current name of the Monster */
//     char* name;
//     /** The tag of the Monster */
//     e_monstreTag tag; // type : MonstreTag
//     /** The type of the Monster */
//     e_typeMonstre type; // type : MonstreType
//     /** The statistics of the Monster */
//     t_statistiques statistiques;
//     /** The basic data of the statistics of the Monster */
//     t_baseStatistiques baseStatistiques;
// } t_monstre;




// // /**
// //  * The data of a Animal saved in the database
// //  */
// // typedef struct _animal {
// //     struct entite_s;
// //     /** The tag of the Animal */
// //     char tag; // type : AnimalTag

// //     /** The different statistics of the Animal */
// //     statistics: {
// //         /** of the Animal */
// //         health: number,
// //         /** of the Animal */
// //         speed: number,
// //     };
// // } Animal;



// // /**
// //  * The data of a Vegetal saved in the database
// //  */
// // typedef struct _vegetale {
// //     /** The ID of the Vegetal */
// //     char id[10];
// //     /** The Tag of the Vegetal */
// //     char tag; // type : VegetaleTag
// //     /** All the stocks of the Vegetal, used to contain the onProduction drops */
// //     stocks: {
// //         /** The tag of the Item that will be dropped */
// //         tag: string,
// //         /** The quantity of the Item that will be dropped*/
// //         quantity: number,
// //     }[];
// //     /** The position of the Vegetal */
// //     Vecteur2 position;
// //     // position: {
// //     //     /** The current coordinates of the Vegetal */
// //     //     x: number,
// //     //     y: number,
// //     //     /** The ID of the Biome where the Vegetal is located */
// //     //     biome: string,
// //     // };
// // } Vegetale;





// // /**
// //  * The data of an Item saved in the database
// //  */
// // typedef struct _item {
// //     /** The ID of the Item */
// //     char id[10];
// //     /** The current name of the Item */
// //     char* tag;
// //     /** The tag of the Item */
// //     char* name;
// //     /** The category of the Item */
// //     char* category;
// //     /** Any additional information that varies according to the Item */
// //     informations;
// // } Item;





