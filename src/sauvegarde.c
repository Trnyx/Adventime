/**
 * \file sauvegarde.c
 * \brief Gestion de la sauvegarde et du chargement du jeu.
 * \author Julien Houget
 * \date 12/03/23
 */

#include "../include/sauvegarde.h"

 /* -------------------------------------------------------------------------- */
 /*                            Variables locales                               */
 /* -------------------------------------------------------------------------- */


#define chemin_param "./sauvegarde/config.txt"


/* -------------------------------------------------------------------------- */
/*                                 Fonctions                                  */
/* -------------------------------------------------------------------------- */


   /**
    * \brief Sauvegarde les paramètres d'options globaux au jeu.
    *
    * \param largeur_fenetre Largeur de la fenêtre.
    * \param hauteur_fenetre Hauteur de la fenêtre.
    * \param volume Volume sonore général (musique, effets sonores).
    * \param flag_plein_ecran Stipule si la fenêtre doit être en plein écran.
    * \return err_sauv, un code d'erreur (0 si succès).
    */
err_sauv sauvegarder_config(int largeur_fenetre, int hauteur_fenetre, float volume, int flag_plein_ecran)
{
    FILE* fichier = fopen(chemin_param, "w");

    if (fichier == NULL)
    {
        return FOPEN_FAIL;
    }
    // fprintf(fichier, "largeur = %i\n", largeur_fenetre);
    // fprintf(fichier, "hauteur = %i\n", hauteur_fenetre);
    // fprintf(fichier, "volume = %f\n", volume);
    // fprintf(fichier, "fullscreen = %i\n", flag_plein_ecran);
    fprintf(fichier, "%i ", largeur_fenetre);
    fprintf(fichier, "%i ", hauteur_fenetre);
    fprintf(fichier, "%f ", volume);
    fprintf(fichier, "%i ", flag_plein_ecran);

    fclose(fichier);
    return SUCCESS;
}

/**
 * \brief Sauvegarde les données du joueur.
 *
 * \param joueur Le joueur à sauvegarder.
 * \param chemin_monde Le chemin d'accès au fichier de sauvegarde du monde.
 * \return err_sauv, un code d'erreur (0 si succès).
 */
err_sauv sauvegarder_joueur(t_joueur* joueur, char* chemin_monde)
{
    // Explicite le chemin du fichier de sauvegarde des données joueur.
    strcat(chemin_monde, "/joueur.txt");

    FILE* fichier = fopen(chemin_monde, "w");

    if (fichier == NULL)
    {
        return FOPEN_FAIL;
    }

    // Statistiques du joueur
    fprintf(fichier, "%i ", joueur->statistiques.pvMax);
    fprintf(fichier, "%i ", joueur->statistiques.experience);
    fprintf(fichier, "%i ", joueur->statistiques.niveau);
    fprintf(fichier, "\n");

    // Map (dans quel map le joueur se trouve)
    fprintf(fichier, "%i ", joueur->map);
    fprintf(fichier, "\n");

    // Flags des bosses
    fprintf(fichier, "%i ", joueur->bossFlags.lundi);
    fprintf(fichier, "%i ", joueur->bossFlags.mardi);
    fprintf(fichier, "%i ", joueur->bossFlags.mercredi);
    fprintf(fichier, "%i ", joueur->bossFlags.jeudi);
    fprintf(fichier, "%i ", joueur->bossFlags.vendredi);
    fprintf(fichier, "%i ", joueur->bossFlags.samedi);
    fprintf(fichier, "%i ", joueur->bossFlags.dimanche);

    fclose(fichier);
    return SUCCESS;
}

/**
 * \brief Sauvegarde les données de la map.
 *
 * \param map La map à sauvegarder.
 * \param chemin_monde Le chemin d'accès au fichier de sauvegarde du monde.
 * \return err_sauv, un code d'erreur (0 si succès).
 */
err_sauv sauvegarder_map(t_map* map, char* chemin_monde)
{
    // Explicite le chemin du fichier de sauvegarde des données map.
    strcat(chemin_monde, "/map.txt");

    FILE* fichier = fopen(chemin_monde, "w");

    if (fichier == NULL)
    {
        return FOPEN_FAIL;
    }

    // Type de map
    fprintf(fichier, "%i ", map->type);
    fprintf(fichier, "\n");

    // Chunks
    t_chunk* chunk = NULL;
    t_block* bloc = NULL;

    for (int x = 0; x < TAILLE_MAP; x++)
    {
        for (int y = 0; y < TAILLE_MAP; y++)
        {
            for (int z = 0; z < NB_COUCHE; z++)
            {
                chunk = getChunk(x, y, z, map);

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
                        fprintf(fichier, "%f ", chunk->blocks->position.x);
                        fprintf(fichier, "%f ", chunk->blocks->position.y);
                        fprintf(fichier, "%f ", chunk->blocks->positionDansChunk.x);
                        fprintf(fichier, "%f ", chunk->blocks->positionDansChunk.y);
                        fprintf(fichier, "%i ", chunk->blocks->tag);
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

    // Entités
    t_entite* entite = NULL;
    en_tete(map->entites);
    if (!liste_vide(map->entites)) {
        while (!hors_liste(map->entites))
        {
            valeur_elt(map->entites, &entite);
            if (entite != NULL && entite->entiteType != ENTITE_MONSTRE_AGGRESSIF)
            {
                fprintf(fichier, "%i ", entite->id);
                fprintf(fichier, "%f ", entite->position.x);
                fprintf(fichier, "%f ", entite->position.y);
                fprintf(fichier, "%f ", entite->direction.x);
                fprintf(fichier, "%f ", entite->direction.y);
                fprintf(fichier, "%i ", entite->orientation);
                fprintf(fichier, "%i ", entite->entiteType);
                fprintf(fichier, "%i ", entite->hitbox.h);
                fprintf(fichier, "%i ", entite->hitbox.w);
                fprintf(fichier, "%i ", entite->hitbox.x);
                fprintf(fichier, "%i ", entite->hitbox.y);
                fprintf(fichier, "%i ", entite->timestampCreation);
            }
            suivant(map->entites);
        }
    }

    fclose(fichier);
    return SUCCESS;
}

err_sauv charger_map(t_map* map, char* chemin_monde)
{
    // Explicite le chemin du fichier de sauvegarde des données map.
    strcat(chemin_monde, "/map.txt");

    FILE* fichier = fopen(chemin_monde, "r");

    if (fichier == NULL)
    {
        return FOPEN_FAIL;
    }

    // Type de map
    e_mapType type = NULL;

    fscanf(fichier, "%i ", &type);
    map->type = type;
    fscanf(fichier, "\n");

    // Chunks
    


}

/**
 * \brief Sauvegarde les paramètres globaux du monde.
 *
 * \param seed Le nombre permettant de générer la map.
 * \param temps Le temps du jeu.
 * \param chemin_monde Le chemin d'accès au fichier de sauvegarde du monde.
 * \return err_sauv, un code d'erreur (0 si succès).
 */
err_sauv sauvegarder_global(unsigned int seed, t_temps* temps, char* chemin_monde)
{
    // Explicite le chemin du fichier de sauvegarde des données globales.
    strcat(chemin_monde, "/global.txt");

    FILE* fichier = fopen(chemin_monde, "w");

    if (fichier == NULL)
    {
        return FOPEN_FAIL;
    }

    // Seed
    fprintf(fichier, "%i ", seed);

    // Temps du jeu
    fprintf(fichier, "%i ", temps->heures);
    fprintf(fichier, "%i ", temps->minutes);
    fprintf(fichier, "%i ", temps->timestampJeu);
    fprintf(fichier, "%i ", temps->timestamp);
    fprintf(fichier, "%i ", temps->cycleJeu);
    fprintf(fichier, "%i ", temps->cycleVrai);


    fclose(fichier);
    return SUCCESS;
}

/**
 * \brief Charge les paramètres globaux du monde.
 *
 * \param seed Le nombre permettant de générer la map.
 * \param temps Le temps du jeu.
 * \param chemin_monde Le chemin d'accès au fichier de sauvegarde du monde.
 * \return err_sauv, un code d'erreur (0 si succès).
 */
err_sauv charger_global(unsigned int* seed, t_temps* temps, char* chemin_monde)
{
    // Explicite le chemin du fichier de sauvegarde des données globales.
    strcat(chemin_monde, "/global.txt");

    FILE* fichier = fopen(chemin_monde, "r");

    if (fichier == NULL)
    {
        return FOPEN_FAIL;
    }

    // Seed
    fscanf(fichier, "%i ", seed);

    // Temps du jeu
    fscanf(fichier, "%i ", temps->heures);
    fscanf(fichier, "%i ", temps->minutes);
    fscanf(fichier, "%i ", temps->timestampJeu);
    fscanf(fichier, "%i ", temps->timestamp);
    fscanf(fichier, "%i ", temps->cycleJeu);
    fscanf(fichier, "%i ", temps->cycleVrai);

    fclose(fichier);
    return SUCCESS;
}


/**
 * \brief Sauvegarde le monde du jeu, c'est-à-dire les données du joueur, de la map et des données globales.
 *
 * \param monde Le monde à sauvegarder.
 * \param nom_monde Le nom du mon de à sauvegarder, pour obtenir le chemin d'accès aux fichiers.
 * \return err_sauv, un code d'erreur (0 si succès).
 */
err_sauv sauvegarder_monde(t_monde* monde, char* nom_monde)
{
    // Définit le chemin d'accès aux fichiers.
    char chemin_monde[50] = "./sauvegarde/";
    strcat(chemin_monde, nom_monde);
    // Crée le dossier avec le nom du monde. 
    // S_IRWXU, définit les permissions de lecture, écriture et exécution.
    mkdir(chemin_monde, S_IRWXU);

    sauvegarder_joueur(monde->joueur, chemin_monde);
    sauvegarder_map(monde->map, chemin_monde);
    sauvegarder_global(monde->seed, monde->temps, chemin_monde);
}

/**
 * \brief Charge la sauvegarde d'un monde.
 *
 * \param nom_monde Le nom du monde à charger
 * \return err_sauv, un code d'erreur (0 si succès).
 */
err_sauv charger_monde(char* nom_monde)
{
    // Définit le chemin d'accès aux fichiers.
    char chemin_monde[50] = "./sauvegarde/";
    strcat(chemin_monde, nom_monde);


    t_monde* monde = malloc(sizeof(t_monde));


    unsigned int seed;
    t_temps* temps = malloc(sizeof(t_temps));

    charger_global(&seed, temps, chemin_monde);


    t_map* map = malloc(sizeof(t_map));
    charger_map(map, chemin_monde);


}