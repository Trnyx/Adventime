/**
 * @file	menus.c
 *
 * @brief	Regroupe les fonctions des menus
 *
 * @author	Eliott Remars
 * @date 	2023-02-07
 * @version 	1.0
 */

#include "SDL2/SDL_render.h"
#include "SDL2/SDL_ttf.h"
#include <stdio.h>
#define NK_IMPLEMENTATION
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
// #define NK_INCLUDE_STANDARD_VARARGS
#define NK_SDL_RENDERER_IMPLEMENTATION

#include "../include/menus.h"
#include "../include/moteur.h"
#include "../include/statistiques.h"
#include "../include/experience.h"

/**
 * @brief      Fait le menu principal du jeu
 *
 * @details    Afficher les boutons Jouer, Options et Quitter du menu principal
 *
 * @param      ctx
 *
 * @return     void
 */

struct nk_context *ctx = NULL;

state_main main_menu(struct nk_context *ctx) {

  /* set_style(ctx, THEME_BLUE); */

  state_main click = 0;

  SDL_Rect dstrect;
  dstrect.h = moteur->window_height;
  dstrect.w = moteur->window_width;
  dstrect.x = 0;
  dstrect.y = 0;

  struct nk_colorf bg;
  struct nk_font_atlas *atlas;
  struct nk_font_config config = nk_font_config(0);
  struct nk_font *font;

  int hovered = 1;

  int render_w, render_h;
  float scale_x, scale_y;
  float font_scale = 1;
  SDL_GetRendererOutputSize(moteur->renderer, &render_w, &render_h);
  scale_x = (float)(render_w) / (float)(moteur->window_width);
  scale_y = (float)(render_h) / (float)(moteur->window_height);
  SDL_RenderSetScale(moteur->renderer, scale_x, scale_y);
  font_scale = scale_y;

  ctx->style.window.background = nk_rgba(0, 0, 0, 0);
  ctx->style.window.fixed_background = nk_style_item_color(nk_rgba(0, 0, 0, 0));
  ctx->style.window.border_color = nk_rgba(0, 0, 0, 0);
  ctx->style.window.border = 1;

  /* set up the font atlas and add desired font; note that font sizes are
   * multiplied by font_scale to produce better results at higher DPIs */
  nk_sdl_font_stash_begin(&atlas);
  font = nk_font_atlas_add_default(atlas, 16 * font_scale, &config);
  nk_sdl_font_stash_end();

  /* this hack makes the font appear to be scaled down to the desired
   * size and is only necessary when font_scale > 1 */
  font->handle.height /= font_scale;
  nk_style_set_font(ctx, &font->handle);

  bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;

  SDL_Surface *bg_img = IMG_Load("assets/images/menu.png");
  SDL_Texture *texture = SDL_CreateTextureFromSurface(moteur->renderer, bg_img);

  while (click == 0) {
    SDL_SetRenderDrawColor(moteur->renderer, bg.r * 255, bg.g * 255, bg.b * 255,
                           bg.a * 255);
    SDL_RenderClear(moteur->renderer);
    SDL_Event evt;
    nk_input_begin(ctx);
    while (SDL_PollEvent(&evt)) {
      if (evt.type == SDL_QUIT) {
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(bg_img);
        click = JEU_QUITTER;
      }
      nk_sdl_handle_event(&evt);
      if ((evt.type == SDL_MOUSEBUTTONUP) ||
          (evt.type == SDL_MOUSEBUTTONDOWN) || (evt.type == SDL_KEYUP) ||
          (evt.type == SDL_KEYDOWN))
        break;
    }
    nk_input_end(ctx);

    SDL_RenderCopy(moteur->renderer, texture, NULL, &dstrect);

    if (nk_begin(ctx, "Menu",
                 nk_rect(0, 0, moteur->window_width, moteur->window_height),
                 (NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR))) {

      nk_layout_space_begin(ctx, NK_STATIC, 0, 3);

      nk_layout_space_push(
          ctx, nk_rect(((float)moteur->window_width / 2) - 300.0 / 2,
                       (moteur->window_height * 0.6), 300, 50));
      if (nk_button_label(ctx, "Jouer")) {
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(bg_img);
        click = M_JOUER;
      }

      if (nk_widget_is_hovered(ctx)) {
        if (!hovered) {
          hovered = 1;
        } else {
          hovered = 0;
        }
      }

      nk_layout_space_push(
          ctx, nk_rect(((float)moteur->window_width / 2) - 300.0 / 2,
                       (moteur->window_height * 0.7), 300, 50));
      if (nk_button_label(ctx, "Options")) {
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(bg_img);
        click = M_OPTIONS;
      }

      if (nk_widget_is_hovered(ctx)) {
        if (!hovered) {
          hovered = 1;
        } else {
          hovered = 0;
        }
      }

      nk_layout_space_push(
          ctx, nk_rect(((float)moteur->window_width / 2) - 300.0 / 2,
                       (moteur->window_height * 0.8), 300, 50));
      if (nk_button_label(ctx, "Quitter")) {
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(bg_img);
        click = JEU_QUITTER;
      }

      if (nk_widget_is_hovered(ctx)) {
        if (!hovered) {
          hovered = 1;
        } else {
          hovered = 0;
        }
      }

      nk_layout_space_end(ctx);
    }

    nk_end(ctx);

    nk_sdl_render(NK_ANTI_ALIASING_ON);

    SDL_RenderPresent(moteur->renderer);
  }
  return click;
}

state_main menu_options(struct nk_context *ctx) {

  set_style(ctx, THEME_BLACK);

  state_main click = 0;

  int hovered = 1;
  int screen_size = 0;
  int previous_size = screen_size;

  static float value_general = 50.f;
  static float value_musiques = 50.f;
  static float value_bruitages = 50.f;
  static int check = 1;

  static const char *size[] = {"1920x1080", "1280x720"};

  while (click == 0) {
    SDL_RenderClear(moteur->renderer);
    SDL_Event evt;
    nk_input_begin(ctx);
    while (SDL_PollEvent(&evt)) {
      if (evt.type == SDL_QUIT) {
        click = JEU_QUITTER;
      }
      nk_sdl_handle_event(&evt);
      if ((evt.type == SDL_MOUSEBUTTONUP) ||
          (evt.type == SDL_MOUSEBUTTONDOWN) || (evt.type == SDL_KEYUP) ||
          (evt.type == SDL_KEYDOWN))
        break;
    }
    nk_input_end(ctx);

    if (nk_begin(ctx, "Options",
                 nk_rect(0, 0, moteur->window_width, moteur->window_height),
                 (NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR))) {

      nk_layout_space_begin(ctx, NK_STATIC, 0, 8);

      nk_layout_space_push(
          ctx, nk_rect(((float)moteur->window_width * 0.25) - 300.0 / 2,
                       (moteur->window_height * 0.1), 300, 50));

      nk_label(ctx, "Volume général", NK_TEXT_CENTERED);

      nk_layout_space_push(
          ctx, nk_rect(((float)moteur->window_width * 0.25) - 300.0 / 2,
                       (moteur->window_height * 0.15), 300, 50));

      nk_slider_float(ctx, 0, &value_general, 100.0f, 1.0f);
      changerVolume(CHANNEL_MASTER, value_general/100);

      nk_layout_space_push(
          ctx, nk_rect(((float)moteur->window_width * 0.25) - 300.0 / 2,
                       (moteur->window_height * 0.2), 300, 50));

      nk_label(ctx, "Musiques", NK_TEXT_CENTERED);

      nk_layout_space_push(
          ctx, nk_rect(((float)moteur->window_width * 0.25) - 300.0 / 2,
                       (moteur->window_height * 0.25), 300, 50));

      nk_slider_float(ctx, 0, &value_musiques, 100.0f, 1.0f);
      changerVolume(CHANNEL_MUSIQUE, value_musiques/100);

      nk_layout_space_push(
          ctx, nk_rect(((float)moteur->window_width * 0.25) - 300.0 / 2,
                       (moteur->window_height * 0.3), 300, 50));

      nk_label(ctx, "Bruitages", NK_TEXT_CENTERED);

      nk_layout_space_push(
          ctx, nk_rect(((float)moteur->window_width * 0.25) - 300.0 / 2,
                       (moteur->window_height * 0.35), 300, 50));

      nk_slider_float(ctx, 0, &value_bruitages, 100.0f, 1.0f);
      changerVolume(CHANNEL_BRUITAGE, value_bruitages/100);

      nk_layout_space_push(
          ctx, nk_rect(((float)moteur->window_width * 0.7) - 300.0 / 2,
                       (moteur->window_height * 0.2), 300, 50));

      nk_label(ctx, "Résolution", NK_TEXT_CENTERED);

      nk_layout_space_push(
          ctx, nk_rect(((float)moteur->window_width * 0.7) - 300.0 / 2,
                       (moteur->window_height * 0.28), 300, 40));

      screen_size =
          nk_combo(ctx, size, NK_LEN(size), screen_size, 25, nk_vec2(200, 200));

      if (screen_size != previous_size) {

        switch (screen_size) {
        case 0:
          moteur->window_width = 1920;
          moteur->window_height = 1080;
          break;
        case 1:
          moteur->window_width = 1280;
          moteur->window_height = 720;
          break;
        }

        previous_size = screen_size;
        SDL_SetWindowSize(moteur->window, moteur->window_width,
                          moteur->window_height);
        updateEchelle(moteur);
      }

      nk_layout_space_push(
          ctx, nk_rect(((float)moteur->window_width * 0.7) - 300.0 / 2,
                       (moteur->window_height * 0.30), 300, 50));

      nk_label(ctx, "Plein écran", NK_TEXT_LEFT);

      nk_layout_space_push(
          ctx, nk_rect(((float)moteur->window_width * 0.7) + 270.0 / 2,
                       (moteur->window_height * 0.30), 300, 50));

      if (nk_checkbox_label(ctx, "", &check)) {
        if (check) {
          SDL_SetWindowFullscreen(moteur->window, 0);
          SDL_SetWindowSize(moteur->window, moteur->window_width,
                            moteur->window_height);
          updateEchelle(moteur);
        } else {
          SDL_SetWindowFullscreen(moteur->window,
                                  SDL_WINDOW_FULLSCREEN_DESKTOP);
          updateEchelle(moteur);
        }
      }

      nk_layout_space_push(
          ctx, nk_rect(((float)moteur->window_width / 2) - 300.0 / 2,
                       (moteur->window_height * 0.8), 300, 50));
      if (nk_button_label(ctx, "Retour")) {
	if (moteur->state == M_PAUSE) {
	  click = M_PAUSE;
	} else {
	  click = M_MENU;
	}
      }

      if (nk_widget_is_hovered(ctx)) {
        if (!hovered) {
          hovered = 1;
        } else {
          hovered = 0;
        }
      }

      nk_layout_space_end(ctx);
    }

    nk_end(ctx);

    nk_sdl_render(NK_ANTI_ALIASING_ON);

    SDL_RenderPresent(moteur->renderer);
  }
  return click;
}

void updateHUD(struct nk_context *ctx, t_joueur *joueur) {

  ctx->style.window.background = nk_rgba(0, 0, 0, 0);
  ctx->style.window.fixed_background = nk_style_item_color(nk_rgba(0, 0, 0, 0));
  ctx->style.window.border_color = nk_rgba(0, 0, 0, 0);
  ctx->style.window.border = 1;

  ctx->style.progress.cursor_normal =
      nk_style_item_color(nk_rgba(223, 46, 56, 255));

  unsigned long current_hp = joueur->statistiques.pv <= 0 ? 0 : joueur->statistiques.pv;
  unsigned long max_hp = joueur->statistiques.pvMax;

  unsigned long current_xp = joueur->statistiques.experience;
  unsigned long max_xp = getExperienceCourbe(joueur->baseStatistiques.experience_courbe)(joueur->statistiques.niveau + 1);
  
  if (current_hp <= 0) {

    SDL_Rect calque;
    calque.x = calque.y = 0;
    calque.h = moteur->window_height;
    calque.w = moteur->window_width;
    
    SDL_SetRenderDrawColor(moteur->renderer, 180, 30, 40, 10);
    SDL_RenderFillRect(moteur->renderer, &calque);
    moteur->state = J_MORT;
    
  } else {

    SDL_Color color;
    color.r = 255;
    color.b = 255;
    color.g = 255;
    color.a = 255;
    
    char horloge[6];
    sprintf(horloge, "%s%d:%s%d", moteur->temps->heures < 10 ? "0" : "" ,moteur->temps->heures, moteur->temps->minutes < 10 ? "0" : "" , moteur->temps->minutes);

    SDL_Surface * surface = TTF_RenderText_Solid(moteur->font, horloge , color);
	
    SDL_Texture * texture = SDL_CreateTextureFromSurface(moteur->renderer, surface);

    SDL_Rect Message_rect;
    Message_rect.w = (moteur->window_width)*0.17;
    Message_rect.h = (moteur->window_height)*0.09;

    Message_rect.x = (moteur->window_width) - 5 - Message_rect.w;
    Message_rect.y = 4;

    if (nk_begin(ctx, "HUD", nk_rect(0, 0, 370, 300),
                 (NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR))) {

      nk_layout_space_begin(ctx, NK_STATIC, 0, 2);
      nk_layout_space_push(ctx, nk_rect(5, 5, 350, 30));
      nk_progress(ctx, &current_hp, max_hp, NK_FIXED);
      
      nk_layout_space_push(ctx, nk_rect(5, 40, 300, 20));

      ctx->style.progress.cursor_normal =
	nk_style_item_color(nk_rgba(8, 255, 114, 255));

	
      nk_progress(ctx, &current_xp, max_xp, NK_FIXED);
      nk_layout_space_end(ctx);
    }

    nk_end(ctx);
    SDL_RenderCopy(moteur->renderer, texture, NULL, &Message_rect);
    nk_sdl_render(NK_ANTI_ALIASING_ON);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    
  }
}

state_main pauseMenu(struct nk_context *ctx) {

  set_style(ctx, THEME_BLACK);
  
  int hovered = 1;
  state_main click = 0;

  while (click == 0) {
    SDL_RenderClear(moteur->renderer);
    SDL_Event evt;
    nk_input_begin(ctx);
    while (SDL_PollEvent(&evt)) {
      if (evt.type == SDL_QUIT) {
        click = JEU_QUITTER;
      }
      nk_sdl_handle_event(&evt);
      if ((evt.type == SDL_MOUSEBUTTONUP) ||
          (evt.type == SDL_MOUSEBUTTONDOWN) || (evt.type == SDL_KEYUP) ||
          (evt.type == SDL_KEYDOWN))
        break;
    }
    nk_input_end(ctx);

    if (nk_begin(ctx, "Pause",
                 nk_rect(0, 0, moteur->window_width, moteur->window_height),
                 (NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR))) {


      nk_layout_space_begin(ctx, NK_STATIC, 0, 3);

      nk_layout_space_push(
          ctx, nk_rect(((float)moteur->window_width / 2) - 300.0 / 2,
                       (moteur->window_height * 0.3), 300, 50));
      if (nk_button_label(ctx, "Continuer")) {
	moteur->state = M_JOUER;
        click = M_JOUER;
      }

      if (nk_widget_is_hovered(ctx)) {
        if (!hovered) {
          hovered = 1;
        } else {
          hovered = 0;
        }
      }

      nk_layout_space_push(
          ctx, nk_rect(((float)moteur->window_width / 2) - 300.0 / 2,
                       (moteur->window_height * 0.5), 300, 50));
      if (nk_button_label(ctx, "Options")) {
	click = M_OPTIONS;
      }

      if (nk_widget_is_hovered(ctx)) {
        if (!hovered) {
          hovered = 1;
        } else {
          hovered = 0;
        }
      }

      nk_layout_space_push(
          ctx, nk_rect(((float)moteur->window_width / 2) - 300.0 / 2,
                       (moteur->window_height * 0.7), 300, 50));
      if (nk_button_label(ctx, "Quitter")) {
        click = M_MENU;
      }
      nk_layout_space_end(ctx);
    }
    nk_end(ctx);
    nk_sdl_render(NK_ANTI_ALIASING_ON);
    SDL_RenderPresent(moteur->renderer);
  }

  return click;
}

state_main gameOver(struct nk_context *ctx, t_joueur *joueur) {

  state_main click;
  SDL_Color color;
  color.r = 255;
  color.b = 255;
  color.g = 255;
  color.a = 255;
  
  SDL_Surface * surface = TTF_RenderText_Solid(moteur->font, "GAME OVER", color);
  SDL_Texture * texture = SDL_CreateTextureFromSurface(moteur->renderer, surface);

  SDL_Rect Message_rect;
  Message_rect.w = (moteur->window_width)*0.5;
  Message_rect.h = (moteur->window_height)*0.17;

  Message_rect.x = (moteur->window_width)*0.5 - Message_rect.w/2;
  Message_rect.y = (moteur->window_height)*0.3 - Message_rect.h/2;

  while (moteur->state == J_MORT) {

    SDL_RenderClear(moteur->renderer);
    SDL_RenderCopy(moteur->renderer, texture, NULL, &Message_rect);
    
    SDL_Event evt;
    nk_input_begin(ctx);
    while (SDL_PollEvent(&evt)) {
      if (evt.type == SDL_QUIT) {
        moteur->state = M_MENU;

	click = M_MENU;
      }
      nk_sdl_handle_event(&evt);
      if ((evt.type == SDL_MOUSEBUTTONUP) ||
          (evt.type == SDL_MOUSEBUTTONDOWN) || (evt.type == SDL_KEYUP) ||
          (evt.type == SDL_KEYDOWN))
        break;
    }
    nk_input_end(ctx);

    if (nk_begin(ctx, "GameOver",
                 nk_rect(0, 0, moteur->window_width, moteur->window_height),
                 (NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR))) {

      nk_layout_space_begin(ctx, NK_STATIC, 0, 2);

      nk_layout_space_push(
			   ctx, nk_rect(((float)moteur->window_width / 2) - 300.0 / 2,
					(moteur->window_height * 0.6), 300, 50));
      
      if (nk_button_label(ctx, "Réapparaitre")) {
        reapparitionJoueur(joueur, moteur->cache->monde->pointApparitionDefaut);
	moteur->state = M_JOUER;
	click = M_JOUER;
        }

      nk_layout_space_push(
			   ctx, nk_rect(((float)moteur->window_width / 2) - 300.0 / 2,
					(moteur->window_height * 0.7), 300, 50));
      
      if (nk_button_label(ctx, "Quitter")) {
	moteur->state = M_MENU;
        click = M_MENU;
      }

      nk_layout_space_end(ctx);
      
      
    }
    nk_end(ctx);
    menu_inventaire(ctx);
    nk_sdl_render(NK_ANTI_ALIASING_ON);
    SDL_RenderPresent(moteur->renderer);
    
  }

  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);

  return click;
}

state_main menu_inventaire(struct nk_context *ctx) {

  set_style(ctx, THEME_BLACK);

  if (nk_begin(ctx, "inv_menu",
               nk_rect(0, 0, moteur->window_width, moteur->window_height),
               (NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR))) {
    
  }
  nk_end(ctx);
  inv_stats(ctx);
  inventaire(ctx);
  
  nk_sdl_render(NK_ANTI_ALIASING_ON);
}

void inv_stats (struct nk_context * ctx) {
  
    if (nk_begin(ctx, "Stats",
               nk_rect(moteur->window_width*0.03, moteur->window_height*0.15, moteur->window_width*0.2, moteur->window_height*0.7),
               (NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_TITLE))) {
    
  }
  nk_end(ctx);
}

void inventaire (struct nk_context * ctx) {

      if (nk_begin(ctx, "Inventaire",
               nk_rect(moteur->window_width*0.25, moteur->window_height*0.15, moteur->window_width*0.72, moteur->window_height*0.7),
               (NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_TITLE))) {
    
  }
  nk_end(ctx);
  
}
