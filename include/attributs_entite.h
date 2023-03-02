/**
 * @file attributs_entite.h
 * 
 * @brief 
 * 
 * @author Clément Hibon
 * @date 3 février
 * @version 1.1
 */



unsigned int id;
e_entiteType entiteType;

t_vecteur2 position;
t_vecteur2 orientation;

SDL_Rect hitbox;


void (*detruire)(t_entite**);