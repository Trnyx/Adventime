/**
 * @file particules.c
 * 
 * @brief 
 * 
 * @author Clément Hibon
 * @date 28 mars
 * @version 1.1
 */





#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../include/particules.h"
#include "../include/moteur.h"




/* --------------------------------- Lumière -------------------------------- */


void dessinerCercle(int centreX, int centreY, int rayon) {
    SDL_Renderer *renderer = moteur->renderer;
    // SDL_SetRenderDrawColor(renderer, couleur.r, couleur.g, couleur.b, couleur.a);

    int x = 0;
    int y = rayon;
    int d = 3 - 2 * rayon;

    while (x <= y) {
        SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);

        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}





void dessinerLumiere(SDL_Rect source) {
    source.x += source.w / 2; 
    source.y += source.h * 0.75;
    const int rayon = 2 * source.w;


    for (int i = 0; i < rayon; i++) {
        // Calcul de l'alpha en fonction de la distance au centre
        float distance = (float)i / (float)rayon;
        float alpha = 1.0f - expf(-1.0 * distance);

        // Définition de la couleur avec l'alpha ajusté
        int alphaByte = (alpha * (float)0x70);
        SDL_SetRenderDrawColor(moteur->renderer, 0xff, 0xf0, 0xbc, alphaByte);

        // Dessin du cercle avec un rayon décroissant
        dessinerCercle(source.x, source.y, rayon - i);
    }
}