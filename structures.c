
typedef struct vector_2 {
    float x;
    float y;
} Vector2;



typedef struct vector_3 {
    float x;
    float y;
    float z;
} Vector3;





typedef struct entite_s {
    /** The ID of the Entity */
    char id[10];
    /** The current position of the Entity */
    Vector2 position;
} Entite;





typedef struct _itemSlot {
    int slot;
    char tag; // type ItemTag
    int quantite;
    int equiped;
} ItemSlot;



typedef struct _inventaire {
    int monet;
    ItemSlot slots[10];
} Inventaire;



typedef struct _statistiques {
    int healthMax;
    int health;
    int niveau;
    int exp;
    int attaque;
    int defense;
    int vitesse;
} Statistiques;

typedef struct _base_statistiques {
    int health;
    int exp;
    int attaque;
    int defense;
    int vitesse;
} BaseStatistiques;





/**
 * The data of a Player saved in the database
 */
typedef struct _joueur {
    struct entite_s;
    /** The name of the Player */
    char name[10];
    /** The different statistics of the Player */
    Statistiques statistiques;
    /** The inventory of the Player */
    Inventaire inventaire;
} Joueur;





/**
 * The data of a Monster saved in the database
 */
typedef struct _monstre {
    struct entite_s;
    /** The current name of the Monster */
    char name[10];
    /** The tag of the Monster */
    char tag; // type : MonstreTag
    /** The type of the Monster */
    char type; // type : MonstreType
    /** The statistics of the Monster */
    Statistiques statistiques;
    /** The basic data of the statistics of the Monster */
    baseStatistics: {
        speed: number,
        health: number,
        attack: number,
        attackSpeed: number,
        defense: number,
    };
} Monstre;




/**
 * The data of a Animal saved in the database
 */
typedef struct _animal {
    struct entite_s;
    /** The tag of the Animal */
    char tag; // type : AnimalTag

    /** The different statistics of the Animal */
    statistics: {
        /** of the Animal */
        health: number,
        /** of the Animal */
        speed: number,
    };
} Animal;



/**
 * The data of a Vegetal saved in the database
 */
typedef struct _vegetale {
    /** The ID of the Vegetal */
    char id[10];
    /** The Tag of the Vegetal */
    char tag; // type : VegetaleTag
    /** All the stocks of the Vegetal, used to contain the onProduction drops */
    stocks: {
        /** The tag of the Item that will be dropped */
        tag: string,
        /** The quantity of the Item that will be dropped*/
        quantity: number,
    }[];
    /** The position of the Vegetal */
    Vector2 position;
    // position: {
    //     /** The current coordinates of the Vegetal */
    //     x: number,
    //     y: number,
    //     /** The ID of the Biome where the Vegetal is located */
    //     biome: string,
    // };
} Vegetale;





/**
 * The data of an Item saved in the database
 */
typedef struct _item {
    /** The ID of the Item */
    char id[10];
    /** The current name of the Item */
    char* tag;
    /** The tag of the Item */
    char* name;
    /** The category of the Item */
    char* category;
    /** Any additional information that varies according to the Item */
    informations;
} Item;