#include "hexxagon_control.h"
#include "hexxagon_graphics.h"

// leteszteli, hogy be vannak-e toltve textures
void test_loaded_pictures(textures *used_pictures){

    if (used_pictures -> game_background == NULL || used_pictures -> enemies_picture == NULL || used_pictures -> hole_picture == NULL ||
        used_pictures -> menu_background == NULL || used_pictures -> editor_background == NULL || used_pictures -> selected_picture == NULL ||
        used_pictures -> selected_distant_picture == 0, used_pictures -> draw_game_background == 0){

        SDL_Log("Nem nyithato meg az egyik kepfajl.");
        exit(1);
    }
}

// felszabaditja a meghivott textures altal lefoglalt memoriat
void memory_free(textures *used_pictures){

    SDL_DestroyTexture(used_pictures -> menu_background);
    SDL_DestroyTexture(used_pictures -> game_background);
    SDL_DestroyTexture(used_pictures -> enemies_picture);
    SDL_DestroyTexture(used_pictures -> editor_background);
    SDL_DestroyTexture(used_pictures -> hole_picture);
    SDL_DestroyTexture(used_pictures -> selected_picture);
    SDL_DestroyTexture(used_pictures -> selected_distant_picture);
    SDL_DestroyTexture(used_pictures -> red_win_background);
    SDL_DestroyTexture(used_pictures -> blue_win_background);
    SDL_DestroyTexture(used_pictures -> draw_game_background);
}

// kirajzolja a parameterkent kapott hatteret
void draw_background(SDL_Renderer *renderer, SDL_Texture *background){

    SDL_Rect src = { 0, 0, 880, 720};
    SDL_Rect dest = { 0, 0, 880, 720};
    SDL_RenderCopy(renderer, background, &src, &dest);
    SDL_RenderPresent(renderer);
}

// az egerrel selected_location entity kore kijelolest rajzol
void draw_selection(SDL_Renderer *renderer, short (*playboard)[9], SDL_Texture *selected_picture,
                     location click_location){

    SDL_Rect src = { 0, 0, 105, 64};
    SDL_Rect dest = { 29 + click_location.x * 90, 19 + click_location.y * 39, 105, 64};
    SDL_RenderCopy(renderer, selected_picture, &src, &dest);
    SDL_RenderPresent(renderer);
}

// kirajzolja a palyara a lehetseges lepeseket illetve fajtajukat, es elmenti a lehetseges lepese fajtainak helyeit
void draw_step(SDL_Renderer *renderer, textures *used_pictures, location *step, location *step_locations_close,
                location *step_locations_far, location click_location){

    int i1 = 0;
    int i2 = 0;

    for(int i = 0; i < 18; i++){

        if(step[i].x == - 1 || step[i].y == - 1)
            break;

        if(distance(step[i].x, step[i].y, click_location.x, click_location.y) < 2){

            SDL_Rect src = { 0, 0, 105, 64};
            SDL_Rect dest = { 29 + step[i].y * 90, 18 + step[i].x * 39, 105, 64};
            SDL_RenderCopy(renderer, used_pictures -> selected_picture, &src, &dest);

            step_locations_close[i1].x = step[i].x;
            step_locations_close[i1].y = step[i].y;
            i1++;
        }

        else{

            SDL_Rect src = { 0, 0, 105, 64};
            SDL_Rect dest = { 29 + step[i].y * 90, 18 + step[i].x * 39, 105, 64};
            SDL_RenderCopy(renderer, used_pictures -> selected_distant_picture, &src, &dest);

            step_locations_far[i2].x = step[i].x;
            step_locations_far[i2].y = step[i].y;
            i2++;
        }
    }

    SDL_RenderPresent(renderer);
}

// kirajzolja az aktualis gyoztes kepernyojet
void draw_winner_background(SDL_Renderer *renderer, short (*playboard)[9], textures *used_pictures,
                             window_type *presently_used_window, bool *player_1_steps, int win_type){

    if(win_type == 2)
        draw_background(renderer, used_pictures -> blue_win_background);

    if(win_type == 3)
        draw_background(renderer, used_pictures -> red_win_background);

    if(win_type == 4)
        draw_background(renderer, used_pictures -> draw_game_background);

    if(win_type != 4)
        draw_state_end(renderer, playboard);

     while(*presently_used_window != menu_window && *presently_used_window != quit){

        SDL_Event event;
        SDL_WaitEvent(&event);

        switch (event.type){

            case SDL_QUIT:

                *presently_used_window = quit;

            break;

            case SDL_MOUSEBUTTONDOWN:

                if(event.button.button == SDL_BUTTON_LEFT){

                    reset(playboard, player_1_steps);
                    *presently_used_window = menu_window;
                }

            break;
        }
    }
}

// kirajzolja a babuk szamat, illetve az ezzel aranyos teglalapokat
void draw_state(SDL_Renderer *renderer, short (*playboard)[9]){

    int red_count = 0;
    int blue_count = 0;

    for(int i = 0; i < 17; i++)
        for(int j = 0; j < 9; j++){

            if(playboard[i][j] == 3)
                red_count++;

            if(playboard[i][j] == 2)
                blue_count++;
        }

    boxRGBA(renderer, 862 - 3 * red_count, 632, 862, 667, 219, 7, 0, 255);
    boxRGBA(renderer, 862 - 3 * blue_count, 670, 862, 705, 40, 0, 163, 255);

    if(red_count == blue_count){

        boxRGBA(renderer, 862 - 3 * red_count, 632, 862, 667, 255, 255, 255, 255);
        boxRGBA(renderer, 862 - 3 * blue_count, 670, 862, 705, 255, 255, 255, 255);
    }

    SDL_RenderPresent(renderer);
}

void draw_state_end(SDL_Renderer *renderer, short (*playboard)[9]){

    int red_count = 0;
    int blue_count = 0;

    for(int i = 0; i < 17; i++)
        for(int j = 0; j < 9; j++){

            if(playboard[i][j] == 3)
                red_count++;

            if(playboard[i][j] == 2)
                blue_count++;
        }

    boxRGBA(renderer, 88, 595 - 7.72 * red_count, 101, 595, 219, 7, 0, 255);
    boxRGBA(renderer, 760, 595 - 7.72 * blue_count, 747, 595, 40, 0, 163, 255);

    if(red_count == blue_count){

        boxRGBA(renderer, 862 - 3 * red_count, 632, 862, 667, 255, 255, 255, 255);
        boxRGBA(renderer, 862 - 3 * blue_count, 670, 862, 705, 255, 255, 255, 255);
    }

    SDL_RenderPresent(renderer);
}

// kirajzolja a babuk jelenlegi helyzetet a tablara
void draw_entities(SDL_Renderer *renderer, short (*playboard)[9], textures *used_pictures){


    for(int i = 0; i < 17; i++){
        for(int j = 0; j < 9; j++){

            // kekek kirajzolasa
            if(playboard[i][j] == 2){

                SDL_Rect src = { 0, 0, 55, 55};
                SDL_Rect dest = { 55 + j * 90, 23 + i * 39, 55, 55};
                SDL_RenderCopy(renderer, used_pictures -> enemies_picture, &src, &dest);
            }

            // pirosak kirajzolasa
            if(playboard[i][j] == 3){

                SDL_Rect src = { 55, 0, 110, 55};
                SDL_Rect dest = { 55 + j * 90, 23 + i * 39, 55, 55};
                SDL_RenderCopy(renderer, used_pictures -> enemies_picture, &src, &dest);
            }

            // lyukak kirajzolasa
            if(playboard[i][j] == -1){

                SDL_Rect src = { 0, 0, 102, 59};
                SDL_Rect dest = { 31 + j * 90.2, 23 + i * 38.7, 102, 59};
                SDL_RenderCopy(renderer, used_pictures -> hole_picture, &src, &dest);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

// az editorban valtogathato gombok kijeloleset rajzolja
void editor_button_animation(SDL_Renderer *renderer, entity placing){

    if(placing == blue)
        rectangleRGBA(renderer, 692, 52, 732, 81, 255, 0, 0, 255);

    if(placing == red)
        rectangleRGBA(renderer, 752, 52, 792, 81, 255, 0, 0, 255);

    if(placing == hole)
        rectangleRGBA(renderer, 812, 52, 852, 81, 255, 0, 0, 255);
}


// a menuben valtogathato gombok kijeloleset rajzolja
void menu_button_animation(SDL_Renderer *renderer, player player_1, player player_2, AI_difficulty AI_1_diff,
                            AI_difficulty AI_2_diff){

    if(player_1 == human)
        rectangleRGBA(renderer, 62, 507, 93, 529, 255, 0, 0, 255);

    if(player_1 == AI && AI_1_diff == easy)
        rectangleRGBA(renderer, 62, 562, 93, 584, 255, 0, 0, 255);

    if(player_1 == AI && AI_1_diff == medium)
        rectangleRGBA(renderer, 62, 617, 93, 639, 255, 0, 0, 255);

    if(player_1 == AI && AI_1_diff == hard)
        rectangleRGBA(renderer, 62, 672, 93, 694, 255, 0, 0, 255);

    if(player_2 == human)
        rectangleRGBA(renderer, 674, 507, 705, 529, 255, 0, 0, 255);

    if(player_2 == AI && AI_2_diff == easy)
        rectangleRGBA(renderer, 674, 562, 705, 584, 255, 0, 0, 255);

    if(player_2 == AI && AI_2_diff == medium)
        rectangleRGBA(renderer, 674, 617, 705, 639, 255, 0, 0, 255);

    if(player_2 == AI && AI_2_diff == hard)
        rectangleRGBA(renderer, 674, 672, 705, 694, 255, 0, 0, 255);

    SDL_RenderPresent(renderer);
}

// SDL letrehozasa
void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow(felirat, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);

    *pwindow = window;
    *prenderer = renderer;
}
