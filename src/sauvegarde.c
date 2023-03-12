/**
 * 
*/
#include "../include/sauvegarde.h"

#define chemin_param "./sauvegarde/config.txt"

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


err_sauv sauvegarder_joueur(t_joueur* joueur, char* chemin_monde)
{
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

err_sauv sauvegarder_map(t_map* map, char* chemin_monde)
{
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
    fprintf(fichier, "%i ", map->chunks->biome);
    fprintf(fichier, "\n");
    // Position d'un chunk
    fprintf(fichier, "%f ", map->chunks->position.x);
    fprintf(fichier, "%f ", map->chunks->position.y);
    fprintf(fichier, "%f ", map->chunks->position.z);
    fprintf(fichier, "\n");
    // Blocs composant un chunk
    fprintf(fichier, "%f ", map->chunks->blocks->position.x);
    fprintf(fichier, "%f ", map->chunks->blocks->position.y);
    fprintf(fichier, "%f ", map->chunks->blocks->positionDansChunk.x);
    fprintf(fichier, "%f ", map->chunks->blocks->positionDansChunk.y);
    fprintf(fichier, "%i ", map->chunks->blocks->tag);
    fprintf(fichier, "\n");

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
            }
            suivant(map->entites);
        }
    }

    fclose(fichier);
    return SUCCESS;
}

err_sauv sauvegarder_global(unsigned int seed, t_temps* temps, char* chemin_monde)
{
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

err_sauv sauvegarder_monde(t_monde* monde, char* nom_monde)
{
    char chemin_monde[50] = "./sauvegarde/";
    strcat(chemin_monde, nom_monde);
    mkdir(chemin_monde, S_IRWXU);

    sauvegarder_joueur(monde->joueur, chemin_monde);
    sauvegarder_map(monde->map, chemin_monde);
    sauvegarder_global(monde->seed, monde->temps, chemin_monde);
}
