/**
 * \file chargement.c
 * \author Julien Houget
 * \brief Gestion du chargement du jeu.
 * \date 2023-03-31
 */

#include "../include/chargement.h"

 /***********************************************************************************************
  *                                      Variables locales                                      *
  ***********************************************************************************************/

#define CHEMIN_PARAM "./sauvegarde/config.txt"
static char* nomFichiersMap[2] =
{
    "/overworld.txt",
    "/caverne.txt" };



/***********************************************************************************************
 *                                          Fonctions                                          *
 ***********************************************************************************************/


 /***********************************************************************************************
  *                                           Config                                            *
  ***********************************************************************************************/

  // Manque une structure unifiant tous les réglages
err_sauv charger_config()
{
    FILE* fichier = fopen(CHEMIN_PARAM, "r");
    if (fichier == NULL)
    {
        return FOPEN_FAIL;
    }

    fclose(fichier);
    return SUCCESS;
}



/***********************************************************************************************
 *                                        Entité & mob                                         *
 ***********************************************************************************************/

 /**
  * \brief Charge la base d'une entité.
  *
  * \param entite L'entité à charger.
  * \param fichier Le fichier de sauvegarde de la map.
  */
void charger_entite(t_entite* entite, FILE* fichier)
{
    // // Chargement de l'entité
    // t_entite* entite = malloc(sizeof(t_entite));

    // if (entite == NULL) {
    //     printf("Erreur mémoire : Impossible d'allouer la place nécessaire pour creer une entite\n");
    //     free(entite);
    //     return LOAD_FAIL;
    // }

    // ID
    printf("ID => ");
    entite->id = malloc(sizeof(char) * (LONGUEUR_ID + 1));
    fscanf(fichier, "%s ", entite->id);

    // Position / Direction / Orientation
    // printf("Position / Direction / Orientation => ");
    fscanf(fichier, "%f ", &(entite->position.x));
    fscanf(fichier, "%f ", &(entite->position.y));
    fscanf(fichier, "%f ", &(entite->direction.x));
    fscanf(fichier, "%f ", &(entite->direction.y));
    fscanf(fichier, "%i ", (int*)&(entite->orientation));

    // Tag
    // printf("Tag => ");
    fscanf(fichier, "%i ", (int*)&entite->entiteType);
    fscanf(fichier, "%i ", (int*)&entite->tag);

    // Taille
    // printf("Taille => ");
    fscanf(fichier, "%f ", &(entite->taille));

    // Hitbox
    // printf("Hitbox => ");
    entite->hitbox.x = entite->position.x - (entite->taille / 2);
    entite->hitbox.y = entite->position.y - (entite->taille / 2);
    entite->hitbox.h = entite->taille;
    entite->hitbox.w = entite->taille;

    // Timestamp de la création
    // printf("Timestamp de la création => ");
    fscanf(fichier, "%i ", (int*)&entite->destructionInactif);
    fscanf(fichier, "%i ", (int*)&entite->destructionDelai);

    fscanf(fichier, "%u ", &(entite->timestampCreation));

    entite->update = NULL;
    entite->detruire = detruireEntite;



    // printf("TYPE ENTITE => \n");
    if (entite->entiteType == ENTITE_MOB)
    {
        entite = realloc(entite, sizeof(t_mob));
        charger_mob((t_mob*)entite, fichier);
    }
    else if (entite->entiteType == ENTITE_JOUEUR)
    {
        charger_entite_vivante((t_entiteVivante*)entite, fichier);

        entite->update = (int(*)(t_entite*, const float, t_entite*)) updateJoueur;
        entite->detruire = (void (*)(t_entite**)) detruireJoueur;
    }


    fscanf(fichier, "\n");
    printf("\n");

    ++(moteur->cache->compteurEntites.entites);
}

/**
 * \brief Charge la base d'une entité vivante.
 *
 * \param entite L'entité à charger.
 * \param fichier Le fichier de sauvegarde de la map.
 */
void charger_entite_vivante(t_entiteVivante* entite, FILE* fichier)
{
    // Statistiques
    fscanf(fichier, "%f ", &(entite->statistiques.attaque));
    fscanf(fichier, "%f ", &(entite->statistiques.defense));
    fscanf(fichier, "%f ", &(entite->statistiques.vitesse));
    fscanf(fichier, "%f ", &(entite->statistiques.pv));
    fscanf(fichier, "%u ", &(entite->statistiques.pvMax));
    fscanf(fichier, "%u ", &(entite->statistiques.experience));
    fscanf(fichier, "%u ", &(entite->statistiques.niveau));

    // Statistiques
    fscanf(fichier, "%f ", &(entite->baseStatistiques.attaque));
    fscanf(fichier, "%f ", &(entite->baseStatistiques.defense));
    fscanf(fichier, "%f ", &(entite->baseStatistiques.vitesse));
    fscanf(fichier, "%f ", &(entite->baseStatistiques.pv));
    fscanf(fichier, "%i ", (int*)&(entite->baseStatistiques.experience_courbe));
}

/**
 * \brief Charge un mob, c'est-à-dire un animal, un monstre...
 *
 * \param mob Le mob à charger.
 * \param fichier Le fichier de sauvegarde de la map.
 */
void charger_mob(t_mob* mob, FILE* fichier)
{
    charger_entite_vivante((t_entiteVivante*)mob, fichier);


    fscanf(fichier, "%i ", (int*)&mob->aggressif);
    printf("aggressif %i => ", mob->aggressif);
    fscanf(fichier, "%u ", &mob->rayonDeplacement);
    printf("rayonDeplacement %i => ", mob->rayonDeplacement);


    mob->update = (int(*)(t_entite*, const float, t_entite*)) updateMob;
    mob->detruire = (void (*)(t_entite**)) detruireMob;


    ++(moteur->cache->compteurEntites.mobs);

    if (mob->aggressif)
        ++(moteur->cache->compteurEntites.mobAggressifs);
    else
        ++(moteur->cache->compteurEntites.mobPassifs);
}





/***********************************************************************************************
 *                                           Joueur                                            *
 ***********************************************************************************************/


 /**
  * \brief Charge le joueur.
  *
  * \param joueur Stocke le joueur à charger.
  * \param chemin_monde Le chemin d'accès au fichier de sauvegarde du monde.
  * \return err_sauv, un code d'erreur (0 si succès).
  */
err_sauv charger_joueur(t_joueur* joueur, char* chemin_monde)
{
    // Explicite le chemin du fichier de sauvegarde des données joueur.
    char chemin_joueur[50];
    strcpy(chemin_joueur, chemin_monde);
    strcat(chemin_joueur, "/joueur.txt");

    FILE* fichier = fopen(chemin_joueur, "r");

    if (fichier == NULL)
    {
        return FOPEN_FAIL;
    }

    charger_entite((t_entite*)joueur, fichier);

    // Map (dans quel map le joueur se trouve)
    fscanf(fichier, "%i ", (int*)&(joueur->map));
    fscanf(fichier, "\n");

    // Actions
    joueur->actionFlags = initialiserActionFlags();

    // Animation
    joueur->animation = creerAnimation(100, 4);

    // Fonctions
    joueur->update = (int (*)(t_entite*, const float, t_entite*))updateJoueur;
    joueur->detruire = (void (*)(t_entite**))detruireJoueur;

    // Timer
    joueur->cooldownAttaque = 0;

    fclose(fichier);
    return SUCCESS;
}


/***********************************************************************************************
 *                                             Map                                             *
 ***********************************************************************************************/

 /**
  * \brief Charge l'overworld (la map de base).
  *
  * \param map Stocke la map à charger.
  * \param fichier Le fichier de sauvegarde d'où provient les données.
  * \return err_sauv, un code d'erreur (0 si succès).
  */
err_sauv charger_overworld(t_map* map, FILE* fichier)
{

    return SUCCESS;
}

/**
 * \brief Charge la map.
 *
 * \param map Stocke la map à charger.
 * \param chemin_monde Le chemin d'accès au fichier de sauvegarde du monde.
 * \param type Le type de map (pour choisir entre l'overworld, les cavernes, ...).
 * \return err_sauv, un code d'erreur (0 si succès).
 */
err_sauv charger_map(t_map* map, char* chemin_monde, const e_mapType type)
{
    // Explicite le chemin du fichier de sauvegarde des données map.
    char chemin_map[50];
    strcpy(chemin_map, chemin_monde);
    char* nomFichier = nomFichiersMap[type];
    strcat(chemin_map, nomFichier);
    printf("PATH : %s => ", chemin_map);

    FILE* fichier = fopen(chemin_map, "r");

    if (fichier == NULL)
    {
        return FOPEN_FAIL;
    }

    if (map == NULL)
    {
        printf("Erreur mémoire : Impossible d'allouer la place nécessaire pour la map\n");
        return LOAD_FAIL;
    }

    // Type
    fscanf(fichier, "%i ", (int*)&(map->type));
    fscanf(fichier, "\n");

    // printf("CHUNKS ET BLOCKS => ");
    // Chunks & Blocs
    // Initialisation chunks
    map->chunks = calloc(TAILLE_MAP * TAILLE_MAP * NB_COUCHE, sizeof(t_chunk));
    // printf("TAILLE : %ld\n", sizeof(t_chunk));

    if (map->chunks == NULL)
    {
        printf("Erreur mémoire : Impossible d'allouer l'espace nécessaire pour charger les chunks\n");
        exit(1);
    }

    for (int i = 0, z = 0; z < NB_COUCHE; z++)
    {
        for (int x = 0; x < TAILLE_MAP; x++)
        {
            for (int y = 0; y < TAILLE_MAP; y++)
            {
                // Biome
                fscanf(fichier, "%i ", (unsigned int*)&(map->chunks[i].biome));
                fscanf(fichier, "\n");

                // printf("CHUNK %i (%i) ", i, map->chunks[i].biome);
                // Position d'un chunk
                fscanf(fichier, "%f ", &(map->chunks[i].position.x));
                fscanf(fichier, "%f ", &(map->chunks[i].position.y));
                fscanf(fichier, "%f ", &(map->chunks[i].position.z));
                fscanf(fichier, "\n");

                // Blocks
                map->chunks[i].blocks = calloc(TAILLE_CHUNK * TAILLE_CHUNK, sizeof(t_block));
                // printf("TAILLE : %ld / %p\n", sizeof(t_block), map->chunks[i].blocks);

                if (map->chunks[i].blocks == NULL)
                {
                    printf("Erreur mémoire : Impossible d'allouer l'espace nécessaire pour les blocks du chunk %i\n", i);
                    exit(1);
                }

                // printf("(IB)");
                for (int i_bloc = 0, x_bloc = 0; x_bloc < TAILLE_CHUNK; x_bloc++)
                {
                    for (int y_bloc = 0; y_bloc < TAILLE_CHUNK; y_bloc++)
                    {
                        // Blocs composant un chunk
                        fscanf(fichier, "%f ", &(map->chunks[i].blocks[i_bloc].position.x));
                        fscanf(fichier, "%f ", &(map->chunks[i].blocks[i_bloc].position.y));
                        fscanf(fichier, "%f ", &(map->chunks[i].blocks[i_bloc].positionDansChunk.x));
                        fscanf(fichier, "%f ", &(map->chunks[i].blocks[i_bloc].positionDansChunk.y));
                        fscanf(fichier, "%i ", &(map->chunks[i].blocks[i_bloc].tag));
                        fscanf(fichier, "\n");
                        i_bloc++;
                    }
                    fscanf(fichier, "\n");
                }
                fscanf(fichier, "\n");

                i++;
                // printf("[OK] => ");
            }
            fscanf(fichier, "\n");
        }
        fscanf(fichier, "\n");
    }
    printf("FIN MAP\n");

    // Entités
    int nombreEntites = 0;
    fscanf(fichier, "%i ", &nombreEntites);
    fscanf(fichier, "\n");

    // printf("NOMBRE ENTITE : %i\n", nombreEntites);

    map->entites = malloc(sizeof(t_liste));
    init_liste(map->entites);

    for (int i = 0; i < nombreEntites; i++)
    {
        printf("ENTITE %i => ", i);
        t_entite* entite = malloc(sizeof(t_entite));
        charger_entite(entite, fichier);
        printf("ID : %s \n", entite->id);
        ajout_droit(map->entites, entite);
        fprintf(fichier, "\n");
    }

    // Spécifications
    switch (type)
    {
    case MAP_OVERWORLD:
        charger_overworld(map, fichier);
        break;
        // case MAP_CAVE: charger_cave(map, fichier); break;
        // Les cavernes ne sont pas encore en place.
    default:
        break;
    }

    fclose(fichier);
    return SUCCESS;
}


/***********************************************************************************************
 *                                           Global                                            *
 ***********************************************************************************************/

 /**
  * \brief Charge les paramètres globaux du monde.
  *
  * \param seed Le nombre permettant de générer la map.
  * \param chemin_monde Le chemin d'accès au fichier de sauvegarde du monde.
  * \return err_sauv, un code d'erreur (0 si succès).
  */
err_sauv charger_global(t_monde* monde, char* chemin_monde)
{
    // Explicite le chemin du fichier de sauvegarde des données globales.
    char chemin_global[50];
    strcpy(chemin_global, chemin_monde);
    strcat(chemin_global, "/global.txt");

    FILE* fichier = fopen(chemin_global, "r");

    if (fichier == NULL)
    {
        return FOPEN_FAIL;
    }

    // ID
    monde->id = malloc(sizeof(char) * (LONGUEUR_ID + 1));
    printf("ID => ");
    fscanf(fichier, "%s ", monde->id);
    fscanf(fichier, "\n");

    // Seed
    printf("Seed => ");
    fscanf(fichier, "%u ", &(monde->seed));
    fscanf(fichier, "\n");

    // Points d'apparition
    printf("Points d'apparition => ");
    fscanf(fichier, "%f ", &(monde->pointApparition.x));
    fscanf(fichier, "%f ", &(monde->pointApparition.y));

    fscanf(fichier, "%f ", &(monde->pointApparitionDefaut.x));
    fscanf(fichier, "%f ", &(monde->pointApparitionDefaut.y));
    fscanf(fichier, "\n");

    fscanf(fichier, "%f ", &(monde->positionApparitionBoss.x));
    fscanf(fichier, "%f ", &(monde->positionApparitionBoss.y));
    fscanf(fichier, "\n");

    // Flags des bosses
    printf("Flags des bosses => ");
    monde->boss = NULL;

    fscanf(fichier, "%u ", &(monde->bossFlags.lundi));
    fscanf(fichier, "%u ", &(monde->bossFlags.mercredi));
    fscanf(fichier, "%u ", &(monde->bossFlags.vendredi));
    fscanf(fichier, "\n");

    // Timestamp renouvellement
    printf("Timestamp renouvellement => ");
    fscanf(fichier, "%li ", &(monde->timestampRenouvellement));

    printf("SUCCES\n");
    fclose(fichier);
    return SUCCESS;
}



/***********************************************************************************************
 *                                            Monde                                            *
 ***********************************************************************************************/

 /**
  * \brief Charge la sauvegarde d'un monde.
  *
  * \param nom_monde Le nom du monde à charger
  * \return err_sauv, un code d'erreur (0 si succès).
  */
err_sauv charger_monde(t_monde* monde, char* nom_monde)
{
    printf("CHARGER MONDE => ");
    // Définit le chemin d'accès aux fichiers.
    char chemin_monde[50] = "./sauvegarde/";
    strcat(chemin_monde, nom_monde);

    if (monde == NULL)
    {
        printf("Erreur mémoire : Impossible d'allouer la place nécessaire pour le monde\n");
        return LOAD_FAIL;
    }


    printf("CHARGER GLOBAL => ");
    charger_global(monde, chemin_monde);


    printf("CHARGER OVERWORLD => ");
    t_map* overworld = malloc(sizeof(t_map));
    if (overworld == NULL)
    {
        printf("Erreur mémoire : Impossible d'allouer l'espace mémoire pour charger l'overworld\n");
    }
    charger_map(overworld, chemin_monde, MAP_OVERWORLD);
    monde->overworld = overworld;


    // printf("CHARGER CAVERNE => ");
    // t_map* caverne = malloc(sizeof(t_map));
    // charger_map(caverne, chemin_monde, MAP_CAVE);
    monde->caverne = NULL;


    printf("CHARGER JOUEUR => ");
    t_joueur* joueur = malloc(sizeof(t_joueur));

    charger_joueur(joueur, chemin_monde);
    monde->joueur = joueur;

    return SUCCESS;
}