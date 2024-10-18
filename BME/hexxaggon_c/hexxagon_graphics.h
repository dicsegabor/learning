#ifndef HEXXAGON_GRAPHICS_H_INCLUDED
#define HEXXAGON_GRAPHICS_H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hexxagon_control.h"

void test_loaded_pictures(textures *used_pictures);

void memory_free(textures *used_pictures);

void draw_background(SDL_Renderer *renderer, SDL_Texture *background);

void draw_selection(SDL_Renderer *renderer, short (*playboard)[9], SDL_Texture *selected_picture,
                     location click_location);

void draw_step(SDL_Renderer *renderer, textures *used_pictures, location *step, location *step_locations_close,
                location *step_locations_far, location click_location);

void draw_winner_background(SDL_Renderer *renderer, short (*playboard)[9], textures *used_pictures,
                             window_type *presently_used_window, bool *player_1_steps, int win_type);

void draw_state(SDL_Renderer *renderer, short (*playboard)[9]);

void draw_state_end(SDL_Renderer *renderer, short (*playboard)[9]);

void draw_entities(SDL_Renderer *renderer, short (*playboard)[9], textures *used_pictures);

void editor_button_animation(SDL_Renderer *renderer, entity placing);

void menu_button_animation(SDL_Renderer *renderer, player player_1, player player_2, AI_difficulty AI_1_diff,
                            AI_difficulty AI_2_diff);

void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer);

#endif // HEXXAGON_GRAPHICS_H_INCLUDED
