#include <stdlib.h>
#include <stdio.h>

#include "../include/monstre.h"
#include "../include/map.h"




void divider() {
    printf("--------------------------------------------\n");
}





void afficherMonstre(t_monstre *monstre) {
    printf("{ ");

    printf("TYPE : %i\n", monstre->type);

    printf("Statistiques : {\n");
    printf("\tPV      : %1.2f \n", monstre->statistiques.pv);
    printf("\tAttaque : %1.2f \n", monstre->statistiques.attaque);
    printf("\tDefense : %1.2f \n", monstre->statistiques.defense);
    printf("\tVitesse : %1.2f \n", monstre->statistiques.vitesse);

    printf(" }\n");
}




int main() {

    t_monstre *monstre = NULL;
    const t_vecteur2 position = { 0, 0 };
    int niveauJoueur = 1;

    // Couleur des monstres en fonction des types :
    //  - NORMAL        : bleu
    //  - PLANTE        : vert
    //  - MONTAGNARD    : gris
    //  - NOCTURNE      : violet





    // Création d'un monstre dans un biome PLAINE
    // Le type du monstre attendu est un type NORMAL ou PLANTE
    printf("Apparition d'un monstre dans un biome PLAINE\n");

    monstre = creerMonstre(position, BIOME_PLAINE, niveauJoueur);
    afficherMonstre(monstre);
    detruireMonstre(monstre);

    divider();



    // Création d'un monstre dans un biome FORET
    // Le type du monstre attendu est un type PLANTE ou NORMAL
    printf("Apparition d'un monstre dans un biome FORET\n");

    monstre = creerMonstre(position, BIOME_FORET, niveauJoueur);
    afficherMonstre(monstre);
    detruireMonstre(monste);

    divider();


    // Création d'un monstre dans un biome MONTAGNE
    // Le type du monstre attendu est un type MONTAGNARD
    printf("Apparition d'un monstre dans un biome MONTAGNE\n");


}