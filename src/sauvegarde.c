/**
 * \file sauvegarde.c
 * \brief Gestion de la sauvegarde du jeu.
 * \author Julien Houget & Clément Hibon
 * \date 12/03/23
 */

#include "../include/sauvegarde.h"

 /* -------------------------------------------------------------------------- */
 /*                            Variables locales                               */
 /* -------------------------------------------------------------------------- */

#define CHEMIN_PARAM "./sauvegarde/config.txt"
static char* nomFichiersMap[2] =
{
    "/overworld.txt",
    "/caverne.txt" };

/* -------------------------------------------------------------------------- */
/*                                 Fonctions                                  */
/* -------------------------------------------------------------------------- */

/***********************************************************************************************
 *                                           Config                                            *
 ***********************************************************************************************/

 /**
  * \brief Sauvegarde les paramètres d'options globaux au jeu.
  *
  * \param largeur_fenetre Largeur de la fenêtre.
  * \param hauteur_fenetre Hauteur de la fenêtre.
  * \param volume_general Volume sonore général.
  * \param volume_musique Volume sonore musique.
  * \param volume_bruitage Volume effets sonores.
  * \param flag_plein_ecran Stipule si la fenêtre doit être en plein écran.
  * \return err_sauv, un code d'erreur (0 si succès).
  */
err_sauv sauvegarder_config(int largeur_fenetre, int hauteur_fenetre, float volume_general,
    float volume_musique, float volume_bruitage, int flag_plein_ecran)
{
    FILE* fichier = fopen(CHEMIN_PARAM, "w");

    if (fichier == NULL)
    {
        return FOPEN_FAIL;
    }
    fprintf(fichier, "%i ", largeur_fenetre);
    fprintf(fichier, "%i ", hauteur_fenetre);
    fprintf(fichier, "%f ", volume_general);
    fprintf(fichier, "%f ", volume_musique);
    fprintf(fichier, "%f ", volume_bruitage);
    fprintf(fichier, "%i ", flag_plein_ecran);

    fclose(fichier);
    return SUCCESS;
}


/* -------------------------------------------------------------------------- */
/*                                Entite et Mob                               */
/* -------------------------------------------------------------------------- */

/**
 * \brief Sauvegarde la base d'une entité.
 *
 * \param entite L'entité à sauvegarder.
 * \param fichier Le fichier de sauvegarde de la map.
 */
void sauvegarder_entite(t_entite* entite, FILE* fichier)
{
    // ID
    fprintf(fichier, "%s ", entite->id);

    // Position
    fprintf(fichier, "%f ", entite->position.x);
    fprintf(fichier, "%f ", entite->position.y);

    // Direction
    fprintf(fichier, "%f ", entite->direction.x);
    fprintf(fichier, "%f ", entite->direction.y);

    // Orientation
    fprintf(fichier, "%i ", entite->orientation);

    // Type de l'entité
    fprintf(fichier, "%i ", entite->entiteType);

    // Tag
    fprintf(fichier, "%i ", entite->tag);

    // Taille
    fprintf(fichier, "%f ", entite->taille);
    // fprintf(fichier, "%f ", entite->hitbox.h);
    // fprintf(fichier, "%f ", entite->hitbox.w);
    // fprintf(fichier, "%f ", entite->hitbox.x);
    // fprintf(fichier, "%f ", entite->hitbox.y);

    // Destruction
    fprintf(fichier, "%i ", entite->destructionInactif);
    fprintf(fichier, "%i ", entite->destructionDelai);

    // TimestampCreation
    fprintf(fichier, "%u ", entite->timestampCreation);
    // fprintf(fichier, "\n");
}

/**
 * \brief Sauvegarde la base d'une entité vivante.
 *
 * \param entite L'entité à sauvegarder.
 * \param fichier Le fichier de sauvegarde de la map.
 */
void sauvegarder_entite_vivante(t_entiteVivante* entite, FILE* fichier)
{
    sauvegarder_entite((t_entite*)entite, fichier);

    // Statistiques
    fprintf(fichier, "%f ", entite->statistiques.attaque);
    fprintf(fichier, "%f ", entite->statistiques.defense);
    fprintf(fichier, "%f ", entite->statistiques.vitesse);
    fprintf(fichier, "%f ", entite->statistiques.pv);
    fprintf(fichier, "%u ", entite->statistiques.pvMax);
    fprintf(fichier, "%u ", entite->statistiques.experience);
    fprintf(fichier, "%u ", entite->statistiques.niveau);
    // fprintf(fichier, "\n");

    // Statistiques de base
    fprintf(fichier, "%f ", entite->baseStatistiques.attaque);
    fprintf(fichier, "%f ", entite->baseStatistiques.defense);
    fprintf(fichier, "%f ", entite->baseStatistiques.vitesse);
    fprintf(fichier, "%f ", entite->baseStatistiques.pv);
    fprintf(fichier, "%i ", entite->baseStatistiques.experience_courbe);
    // fprintf(fichier, "\n");
}

/**
 * \brief Sauvegarde un mob, c'est-à-dire un animal, un monstre...
 *
 * \param mob Le mob à sauvegarder.
 * \param fichier Le fichier de sauvegarde de la map.
 */
void sauvegarder_mob(t_mob* mob, FILE* fichier)
{
    sauvegarder_entite_vivante((t_entiteVivante*)mob, fichier);

    fprintf(fichier, "%i ", mob->aggressif);
    fprintf(fichier, "%u ", mob->rayonDeplacement);
}


/***********************************************************************************************
 *                                           Joueur                                            *
 ***********************************************************************************************/

 /**
  * \brief Sauvegarde les données du joueur.
  *
  * \param joueur Le joueur à sauvegarder.
  * \param chemin_monde Le chemin d'accès au fichier de sauvegarde du monde.
  * \return err_sauv, un code d'erreur (0 si succès).
  */
err_sauv sauvegarder_joueur(t_joueur* joueur, char* chemin_monde)
{
    printf("JOUEUR => ");
    // Explicite le chemin du fichier de sauvegarde des données joueur.
    char chemin_joueur[50];
    strcpy(chemin_joueur, chemin_monde);
    strcat(chemin_joueur, "/joueur.txt");
    printf("PATH : %s => ", chemin_joueur);

    FILE* fichier = fopen(chemin_joueur, "w");

    if (fichier == NULL)
    {
        return FOPEN_FAIL;
    }

    sauvegarder_entite_vivante((t_entiteVivante*)joueur, fichier);

    // Map (dans quel map le joueur se trouve)
    fprintf(fichier, "%i ", joueur->map);
    fprintf(fichier, "\n");

    printf("SUCCES\n");
    fclose(fichier);
    return SUCCESS;
}


/***********************************************************************************************
 *                                             Map                                             *
 ***********************************************************************************************/

 /**
  * \brief Sauvegarde les données de la map.
  *
  * \param map La map à sauvegarder.
  * \param chemin_monde Le chemin d'accès au fichier de sauvegarde du monde.
  * \return err_sauv, un code d'erreur (0 si succès).
  */
err_sauv sauvegarder_map(t_map* map, char* chemin_monde, const e_mapType type)
{
    // Explicite le chemin du fichier de sauvegarde des données map.
    char chemin_map[50];
    strcpy(chemin_map, chemin_monde);
    strcat(chemin_map, nomFichiersMap[type]);

    FILE* fichier = fopen(chemin_map, "w");

    if (fichier == NULL)
    {
        return FOPEN_FAIL;
    }

    printf("MAP => ");
    // Type de map
    fprintf(fichier, "%i ", map->type);
    fprintf(fichier, "\n");

    // Chunks
    t_chunk* chunk = NULL;
    t_block* bloc = NULL;

    for (int z = 0; z < NB_COUCHE; z++)
    {
        for (int x = 0; x < TAILLE_MAP; x++)
        {
            for (int y = 0; y < TAILLE_MAP; y++)
            {
                chunk = getChunk(x, y, z, map);

                // Biome
                fprintf(fichier, "%i ", chunk->biome);
                fprintf(fichier, "\n");

                // Position d'un chunk
                fprintf(fichier, "%f ", chunk->position.x);
                fprintf(fichier, "%f ", chunk->position.y);
                fprintf(fichier, "%f ", chunk->position.z);
                fprintf(fichier, "\n");

                for (int x_bloc = 0; x_bloc < TAILLE_CHUNK; x_bloc++)
                {
                    for (int y_bloc = 0; y_bloc < TAILLE_CHUNK; y_bloc++)
                    {
                        bloc = getBlockDansChunk(x_bloc, y_bloc, chunk);

                        // Blocs composant un chunk
                        fprintf(fichier, "%f ", bloc->position.x);
                        fprintf(fichier, "%f ", bloc->position.y);
                        fprintf(fichier, "%f ", bloc->positionDansChunk.x);
                        fprintf(fichier, "%f ", bloc->positionDansChunk.y);
                        // Tag
                        fprintf(fichier, "%i ", bloc->tag);
                        fprintf(fichier, "\n");
                    }
                    fprintf(fichier, "\n");
                }
                fprintf(fichier, "\n");
            }
            fprintf(fichier, "\n");
        }
        fprintf(fichier, "\n");
    }

    printf("ENTITES => ");
    // Entités
    // Nombre d'entité sauvegardé
    fprintf(fichier, "%i ", moteur->cache->compteurEntites.mobs - moteur->cache->compteurEntites.mobAggressifs);
    fprintf(fichier, "\n");

    t_entite* entite = NULL;

    en_tete(map->entites);
    if (!liste_vide(map->entites))
    {
        while (!hors_liste(map->entites))
        {
            valeur_elt(map->entites, &entite);
            // On ne sauvegarde pas les entités aggressives
            if (entite != NULL && !(entite->destructionInactif) && !((t_mob*)entite)->aggressif)
            {
                if (entite->entiteType == ENTITE_MOB)
                {
                    sauvegarder_mob((t_mob*)entite, fichier);
                }
                else
                {
                    sauvegarder_entite(entite, fichier);
                }
            }
            suivant(map->entites);
            fprintf(fichier, "\n");
        }
    }
    fprintf(fichier, "\n");

    printf("SUCCES => ");
    fclose(fichier);
    return SUCCESS;
}


/***********************************************************************************************
 *                                     Paramètres globaux                                      *
 ***********************************************************************************************/

 /**
  * \brief Sauvegarde les paramètres globaux du monde.
  *
  * \param chemin_monde Le chemin d'accès au fichier de sauvegarde du monde.
  * \return err_sauv, un code d'erreur (0 si succès).
  */
err_sauv sauvegarder_global(t_monde* monde, char* chemin_monde)
{
    // Explicite le chemin du fichier de sauvegarde des données globales.
    char chemin_global[50];
    strcpy(chemin_global, chemin_monde);
    strcat(chemin_global, "/global.txt");

    FILE* fichier = fopen(chemin_global, "w");

    if (fichier == NULL)
    {
        return FOPEN_FAIL;
    }

    // ID
    fprintf(fichier, "%s ", monde->id);
    fprintf(fichier, "\n");

    // Seed
    fprintf(fichier, "%u ", monde->seed);
    fprintf(fichier, "\n");

    // Points d'apparition
    fprintf(fichier, "%f ", monde->pointApparition.x);
    fprintf(fichier, "%f ", monde->pointApparition.y);

    fprintf(fichier, "%f ", monde->pointApparitionDefaut.x);
    fprintf(fichier, "%f ", monde->pointApparitionDefaut.y);
    fprintf(fichier, "\n");

    fprintf(fichier, "%f ", monde->positionApparitionBoss.x);
    fprintf(fichier, "%f ", monde->positionApparitionBoss.y);
    fprintf(fichier, "\n");

    // Flags des bosses
    fprintf(fichier, "%u ", monde->bossFlags.lundi);
    fprintf(fichier, "%u ", monde->bossFlags.mercredi);
    fprintf(fichier, "%u ", monde->bossFlags.vendredi);
    fprintf(fichier, "\n");

    // Timestamp renouvellement
    fprintf(fichier, "%li ", monde->timestampRenouvellement);

    fclose(fichier);
    return SUCCESS;
}


/***********************************************************************************************
 *                                            Monde                                            *
 ***********************************************************************************************/

 /**
  * \brief Sauvegarde le monde du jeu, c'est-à-dire les données du joueur, de la map et des données globales.
  *
  * \param monde Le monde à sauvegarder.
  * \param nom_monde Le nom du mon de à sauvegarder, pour obtenir le chemin d'accès aux fichiers.
  * \return err_sauv, un code d'erreur (0 si succès).
  */
err_sauv sauvegarder_monde(t_monde* monde, char* nom_monde)
{
    printf("DEBUT SAUVEGARDE => ");
    // Définit le chemin d'accès aux fichiers.
    char chemin_monde[50] = "./sauvegarde/";

#ifdef _WIN32
    mkdir(chemin_monde);
#else
    mkdir(chemin_monde, S_IRWXU);
#endif

    strcat(chemin_monde, nom_monde);
    // Crée le dossier avec le nom du monde.
    // S_IRWXU, définit les permissions de lecture, écriture et exécution.
    printf("PATH : %s => \n", chemin_monde);

#ifdef _WIN32
    mkdir(chemin_monde);
#else
    mkdir(chemin_monde, S_IRWXU);
#endif

    err_sauv message;

    message = sauvegarder_joueur(monde->joueur, chemin_monde);
    if (message != SUCCESS)
        printf("ERREUR SAUVEGARDE JOUEUR : %i\n", message);
    else
        printf("JOUEUR SAUVEGARDE\n");

    message = sauvegarder_map(monde->overworld, chemin_monde, MAP_OVERWORLD);
    if (message != SUCCESS)
        printf("ERREUR SAUVEGARDE MAP : %i\n", message);
    else
        printf("MAP SAUVEGARDE\n");

    message = sauvegarder_global(monde, chemin_monde);
    if (message != SUCCESS)
        printf("ERREUR SAUVEGARDE GLOBAL : %i\n", message);
    else
        printf("GLOBAL SAUVEGARDE\n");

    return SUCCESS;
}