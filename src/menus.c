/**
 * @file	menus.c
 *
 * @brief	Regroupe les fonctions des menus
 *
 * @author	Eliott Remars
 * @date 	2023-02-07
 * @version 	1.0
 */

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_SDL_RENDERER_IMPLEMENTATION

#include "../include/menus.h"

/**
 * @brief      Fait le menu principal du jeu
 *
 * @details    Afficher les boutons Jouer, Options et Quitter du menu principal
 *
 * @param      ctx
 * @param      moteur
 *
 * @return     void
 */

state_main main_menu(struct nk_context *ctx, t_moteur *moteur) {

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

  SDL_Surface *bg_img = IMG_Load("../assets/images/menu.png");
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
      if((evt.type==SDL_MOUSEBUTTONUP)||(evt.type==SDL_MOUSEBUTTONDOWN)||(evt.type==SDL_KEYUP)||(evt.type==SDL_KEYDOWN)) break;
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

    nk_clear(ctx);
  }
  return click;
}

state_main menu_options(struct nk_context *ctx, t_moteur *moteur) {

  set_style(ctx, THEME_BLACK);

  state_main click = 0;

  int hovered = 1;
  int screen_size = 0;
  static float value = 50.f;
  static int check = 1;

  static const char *size[] = {"1920x1080","1280x720"};

  while (click == 0) {
    SDL_RenderClear(moteur->renderer);
    SDL_Event evt;
    nk_input_begin(ctx);
    while (SDL_PollEvent(&evt)) {
      if (evt.type == SDL_QUIT) {
        click = JEU_QUITTER;
      }
      nk_sdl_handle_event(&evt);
      if((evt.type==SDL_MOUSEBUTTONUP)||(evt.type==SDL_MOUSEBUTTONDOWN)||(evt.type==SDL_KEYUP)||(evt.type==SDL_KEYDOWN)) break;
    }
    nk_input_end(ctx);

    if (nk_begin(ctx, "Options",
                 nk_rect(0, 0, moteur->window_width, moteur->window_height),
                 (NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR))) {

      nk_layout_space_begin(ctx, NK_STATIC, 0, 5);

      nk_layout_space_push(
          ctx, nk_rect(((float)moteur->window_width / 2) - 300.0 / 2,
                       (moteur->window_height * 0.1), 300, 50));

      nk_label(ctx, "Volume", NK_TEXT_CENTERED);

      nk_layout_space_push(
          ctx, nk_rect(((float)moteur->window_width / 2) - 300.0 / 2,
                       (moteur->window_height * 0.13), 300, 50));

      nk_slider_float(ctx, 0, &value, 100.0f, 1.0f);

      nk_layout_space_push(
			   ctx, nk_rect(((float)moteur->window_width / 2) - 300.0 / 2,
					(moteur->window_height * 0.2), 300, 50));

      screen_size = nk_combo(ctx, size, NK_LEN(size), screen_size, 25, nk_vec2(200, 200)); 

      nk_layout_space_push(
			   ctx, nk_rect(((float)moteur->window_width / 2) - 300.0 / 2,
					(moteur->window_height * 0.3), 300, 50));
      
      nk_label(ctx, "Plein écran", NK_TEXT_LEFT);

            nk_layout_space_push(
			   ctx, nk_rect(((float)moteur->window_width / 2) + 300.0 / 2,
					(moteur->window_height * 0.3), 300, 50));
	    
      if(nk_checkbox_label(ctx, "", &check)) {
	if (check) {
	  SDL_SetWindowFullscreen(moteur->window, 0);
	  updateEchelle(moteur);
	} else {
	  SDL_SetWindowFullscreen(moteur->window, SDL_WINDOW_FULLSCREEN);
	  updateEchelle(moteur);
	}
      }

      nk_layout_space_push(
          ctx, nk_rect(((float)moteur->window_width / 2) - 300.0 / 2,
                       (moteur->window_height * 0.8), 300, 50));
      if (nk_button_label(ctx, "Retour")) {
        click = M_MENU;
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
