#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hexxagon_control.h"
#include "hexxagon_graphics.h"

// fofuggveny ami vezerli a programot
int main(int argc, char *argv[]) {

    srand(time(0));

    // window_type létrehozása
    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init("Hexxagon", 880, 720, &window, &renderer);

    // struktúra letrehozasa a kepeknek
    textures used_pictures;

    //hasznalando textures betoltese
    used_pictures.game_background = (SDL_Texture*) IMG_LoadTexture(renderer, "jatek_hatter.gif");
    used_pictures.enemies_picture = (SDL_Texture*) IMG_LoadTexture(renderer, "Ellenfelek.png");
    used_pictures.hole_picture = (SDL_Texture*) IMG_LoadTexture(renderer, "Lyuk.png");
    used_pictures.menu_background = (SDL_Texture*) IMG_LoadTexture(renderer, "Hex_menu.gif");
    used_pictures.editor_background = (SDL_Texture*) IMG_LoadTexture(renderer, "Editor.gif");
    used_pictures.selected_picture = (SDL_Texture*) IMG_LoadTexture(renderer, "kijeloles.png");
    used_pictures.selected_distant_picture = (SDL_Texture*) IMG_LoadTexture(renderer, "kijeloles_tavol.png");
    used_pictures.red_win_background = (SDL_Texture*) IMG_LoadTexture(renderer, "pirosnyer.gif");
    used_pictures.blue_win_background = (SDL_Texture*) IMG_LoadTexture(renderer, "keknyer.gif");
    used_pictures.draw_game_background = (SDL_Texture*) IMG_LoadTexture(renderer, "dontetlen.gif");

    test_loaded_pictures(&used_pictures);

    // jatekosok bevezetese
    player player_1 = human;
    player player_2 = human;

    AI_difficulty AI_1_diff = easy;
    AI_difficulty AI_2_diff = easy;

    // meghatarozzuk, hogy az elso player wait_for_step
    bool player_1_steps = true;

    // adattarolas
    short playboard[17][9];

    // adatok betoltese
    reset(playboard, &player_1_steps);

    // menu_window legyen az elso megnyilo window_type
    window_type presently_used_window = menu_window;

    // fusson amig be nem zarjak
    while(presently_used_window != quit){

        // Menu
        Menu(renderer, &used_pictures, &player_1, &player_2, &AI_1_diff, &AI_2_diff, &presently_used_window);

        // Editor
        Editor(renderer, &used_pictures, playboard, &presently_used_window, &player_1_steps);

        // Jatek
        Game(renderer, playboard, &player_1_steps, &presently_used_window, &used_pictures, player_1, player_2, AI_1_diff, AI_2_diff);
    }

    //memoria felszabaditasa
    memory_free(&used_pictures);

    SDL_Quit();

    return 0;
}
