/**
 * @file	menus.h
 *
 * @brief	Regroupe les fonctions des menus
 *
 * @author	Eliott Remars
 * @date 	2023-02-07
 * @version 	1.0
 */

#ifndef _JEU_MENUS_
#define _JEU_MENUS_

#include "Nuklear/nuklear.h"
#include "Nuklear/nuklear_sdl_renderer.h"
#include "Nuklear/style.c"
#include "main.h"
#include "audio.h"
#include "joueur.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "../include/main.h"

extern struct nk_context * ctx;


state_main main_menu(struct nk_context * ctx);
state_main menu_options(struct nk_context *ctx);
void updateHUD(struct nk_context *ctx, t_joueur *joueur);
state_main pauseMenu(struct nk_context *ctx);
state_main gameOver(struct nk_context *ctx, t_joueur *joueur);
state_main menu_inventaire(struct nk_context *ctx);
void inv_stats(struct nk_context *ctx);
void inventaire (struct nk_context * ctx);

#endif
