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
char* nomFichiersMap[2] =
{
    "overworld.txt",
    "caverne.txt"
};


/* -------------------------------------------------------------------------- */
/*                                 Fonctions                                  */
/* -------------------------------------------------------------------------- */


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
    FILE* fichier = fopen(chemin_param, "w");

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

err_sauv charger_config()
{
    FILE* fichier = fopen(chemin_param, "r");
    if (fichier == NULL)
    {
        return FOPEN_FAIL;
    }


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


    // Id
    fprintf(fichier, "%s ", joueur->id);
    fprintf(fichier, "\n");

    // Position
    fprintf(fichier, "%f ", joueur->position.x);
    fprintf(fichier, "%f ", joueur->position.y);
    fprintf(fichier, "\n");

    // Taille
    fprintf(fichier, "%f ", joueur->taille);
    fprintf(fichier, "\n");

    // Timestamp de la création du joueur
    fprintf(fichier, "%u ", joueur->timestampCreation);
    fprintf(fichier, "\n");


    // Map (dans quel map le joueur se trouve)
    fprintf(fichier, "%i ", joueur->map);
    fprintf(fichier, "\n");

    // Statistiques
    fprintf(fichier, "%f ", joueur->statistiques.pv);
    fprintf(fichier, "%f ", joueur->statistiques.attaque);
    fprintf(fichier, "%f ", joueur->statistiques.defense);
    fprintf(fichier, "%f ", joueur->statistiques.vitesse);
    fprintf(fichier, "%u ", joueur->statistiques.pvMax);
    fprintf(fichier, "%u ", joueur->statistiques.experience);
    fprintf(fichier, "%u ", joueur->statistiques.niveau);
    fprintf(fichier, "\n");

    // Statistiques de base
    fprintf(fichier, "%f ", joueur->baseStatistiques.pv);
    fprintf(fichier, "%f ", joueur->baseStatistiques.attaque);
    fprintf(fichier, "%f ", joueur->baseStatistiques.defense);
    fprintf(fichier, "%f ", joueur->baseStatistiques.vitesse);
    fprintf(fichier, "\n");


    // Courbe d'expérience
    fprintf(fichier, "%u ", joueur->baseStatistiques.experience_courbe);
    fprintf(fichier, "\n");


    // Flags des bosses
    fprintf(fichier, "%u ", joueur->bossFlags.lundi);
    fprintf(fichier, "%u ", joueur->bossFlags.mercredi);
    fprintf(fichier, "%u ", joueur->bossFlags.vendredi);
    fprintf(fichier, "\n");


    fclose(fichier);
    return SUCCESS;
}

err_sauv charger_joueur(t_joueur* joueur, char* chemin_monde)
{
    // Explicite le chemin du fichier de sauvegarde des données joueur.
    strcat(chemin_monde, "/joueur.txt");

    FILE* fichier = fopen(chemin_monde, "r");

    if (fichier == NULL)
    {
        return FOPEN_FAIL;
    }


    // Chargement de l'entité
    t_entite* entite = malloc(sizeof(t_entite));

    if (entite == NULL) {
        printf("Erreur mémoire : Impossible d'allouer la place nécessaire pour creer une entite\n");
        free(entite);
        return LOAD_FAIL;
    }

    // Id
    fscanf(fichier, "%s", entite->id);

    // Position
    fscanf(fichier, "%f ", &(entite->position.x));
    fscanf(fichier, "%f ", &(entite->position.y));

    // Direction
    entite->direction.x = 0;
    entite->direction.y = 0;

    //Orientation
    entite->orientation = SUD;

    // Tag
    entite->tag = TAG_AUCUN;

    // Taille
    fscanf(fichier, "%f ", &(entite->taille));

    // Hitbox
    entite->hitbox.x = entite->position.x - (entite->taille / 2);
    entite->hitbox.y = entite->position.y - (entite->taille / 2);
    entite->hitbox.h = 1;
    entite->hitbox.w = 1;

    // Timestamp de la création du joueur
    fscanf(fichier, "%u ", &(entite->timestampCreation));



    // Chargement du joueur
    joueur = realloc(entite, sizeof(t_joueur));
    joueur->entiteType = ENTITE_JOUEUR;

    // Map (dans quel map le joueur se trouve)
    fscanf(fichier, "%i ", (int*)&(joueur->map));
    fscanf(fichier, "\n");

    // Statistiques
    fscanf(fichier, "%f ", &(joueur->statistiques.pv));
    fscanf(fichier, "%f ", &(joueur->statistiques.attaque));
    fscanf(fichier, "%f ", &(joueur->statistiques.defense));
    fscanf(fichier, "%f ", &(joueur->statistiques.vitesse));
    fscanf(fichier, "%u ", &(joueur->statistiques.pvMax));
    fscanf(fichier, "%u ", &(joueur->statistiques.experience));
    fscanf(fichier, "%u ", &(joueur->statistiques.niveau));
    fscanf(fichier, "\n");


    // Actions
    joueur->actionFlags = initialiserActionFlags();

    // Animation
    joueur->animation = creerAnimation(100, 4);

    // Fonctions
    joueur->update = (int(*)(t_entite*, const float, t_entite*)) updateJoueur;
    joueur->detruire = (void (*)(t_entite**)) detruireJoueur;

    // Timer
    joueur->cooldownAttaque = 0;
    joueur->destructionInactif = FAUX;


    // Statistiques de base
    fscanf(fichier, "%f ", &(joueur->baseStatistiques.pv));
    fscanf(fichier, "%f ", &(joueur->baseStatistiques.attaque));
    fscanf(fichier, "%f ", &(joueur->baseStatistiques.defense));
    fscanf(fichier, "%f ", &(joueur->baseStatistiques.vitesse));
    fscanf(fichier, "\n");

    // Courbe d'expérience
    fscanf(fichier, "%u ", &(joueur->baseStatistiques.experience_courbe));
    fscanf(fichier, "\n");


    entite = NULL;


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
                        fprintf(fichier, "%f ", bloc->position.x);
                        fprintf(fichier, "%f ", bloc->position.y);
                        fprintf(fichier, "%f ", bloc->positionDansChunk.x);
                        fprintf(fichier, "%f ", bloc->positionDansChunk.y);
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

    // Entités
    t_entite* entite = NULL;
    en_tete(map->entites);
    if (!liste_vide(map->entites)) {
        while (!hors_liste(map->entites))
        {
            valeur_elt(map->entites, &entite);
            // On ne sauvegarde pas les entités aggressives
            if (entite != NULL && entite->entiteType != ENTITE_MOB && ((t_mob*)entite)->aggressif != VRAI)
            {
                fprintf(fichier, "%s ", entite->id);
                fprintf(fichier, "%f ", entite->position.x);
                fprintf(fichier, "%f ", entite->position.y);
                fprintf(fichier, "%f ", entite->direction.x);
                fprintf(fichier, "%f ", entite->direction.y);
                fprintf(fichier, "%i ", entite->orientation);
                fprintf(fichier, "%i ", entite->entiteType);
                fprintf(fichier, "%f ", entite->hitbox.h);
                fprintf(fichier, "%f ", entite->hitbox.w);
                fprintf(fichier, "%f ", entite->hitbox.x);
                fprintf(fichier, "%f ", entite->hitbox.y);
                fprintf(fichier, "%u ", entite->timestampCreation);
                fprintf(fichier, "\n");

            }
            suivant(map->entites);
        }
    }
    fprintf(fichier, "\n");


    fclose(fichier);
    return SUCCESS;
}

err_sauv charger_map(t_map* map, char* chemin_monde, const e_mapType type)
{
    // Explicite le chemin du fichier de sauvegarde des données map.
    char* nomFichier = nomFichiersMap[type];
    strcat(chemin_monde, nomFichier);

    FILE* fichier = fopen(chemin_monde, "r");

    if (fichier == NULL)
    {
        return FOPEN_FAIL;
    }


    // Chunks


    fclose(fichier);
    return SUCCESS;

}

/**
 * \brief Sauvegarde les paramètres globaux du monde.
 *
 * \param seed Le nombre permettant de générer la map.
 * \param temps Le temps du jeu.
 * \param chemin_monde Le chemin d'accès au fichier de sauvegarde du monde.
 * \return err_sauv, un code d'erreur (0 si succès).
 */
err_sauv sauvegarder_global(t_monde* monde, char* chemin_monde)
{
    // Explicite le chemin du fichier de sauvegarde des données globales.
    strcat(chemin_monde, "/global.txt");

    FILE* fichier = fopen(chemin_monde, "w");

    if (fichier == NULL)
    {
        return FOPEN_FAIL;
    }

    // Seed
    fprintf(fichier, "%u ", monde->seed);
    fprintf(fichier, "\n");


    fclose(fichier);
    return SUCCESS;
}

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
    strcat(chemin_monde, "/global.txt");

    FILE* fichier = fopen(chemin_monde, "r");

    if (fichier == NULL)
    {
        return FOPEN_FAIL;
    }

    // Seed
    fscanf(fichier, "%u ", &(monde->seed));

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
    sauvegarder_map(monde->overworld, chemin_monde);
    sauvegarder_global(monde, chemin_monde);
    return SUCCESS;
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


    charger_global(monde, chemin_monde);


    t_map* overworld = malloc(sizeof(t_map));
    charger_map(overworld, chemin_monde, MAP_OVERWORLD);

    return SUCCESS;
}