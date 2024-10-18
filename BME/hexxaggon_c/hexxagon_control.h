#ifndef HEXXAGON_CONTROL_H_INCLUDED
#define HEXXAGON_CONTROL_H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// tarolja a hasznalando kepeket
typedef struct textures{

    SDL_Texture *game_background;
    SDL_Texture *enemies_picture;
    SDL_Texture *hole_picture;
    SDL_Texture *menu_background;
    SDL_Texture *editor_background;
    SDL_Texture *selected_picture;
    SDL_Texture *selected_distant_picture;
    SDL_Texture *red_win_background;
    SDL_Texture *blue_win_background;
    SDL_Texture *draw_game_background;
}textures;

// tarolja a kattintas indexeit
typedef struct location{

    int x;
    int y;
}location;

typedef struct list_of_steps{

    location where;
    location from_where;
    int score;
    struct list_of_steps *next;
}list_of_steps;

// tarolja a AI szamitasainak adatait
typedef struct step_and_score{

    location location;
    int score;
}step_and_score;

// tarolja a gep nehezsegi szintjet
typedef enum AI_difficulty{

    easy,
    medium,
    hard
}AI_difficulty;

// formatum amely a jatekos tipusat mutatja
typedef enum player{

    human,
    AI
}player;

// formatum mely az editorban hasznalt eszkozt mutatja
typedef enum entity{

    blue,
    red,
    hole,
    emptyness
}entity;

// formatum amely a programban futtatott reszt mutatja
typedef enum window_type{

    menu_window,
    editor_window,
    game_window,
    quit
}window_type;

void delay(unsigned int mseconds);

location click_index(int click_x, int click_y);

void board_copy(short (*board_to)[9], short (*board_from)[9]);

void reset(short (*playboard)[9], bool *player_1_steps);

int distance(int ax, int ay, int bx, int by);

int counter(short (*board)[9]);

bool test_for_entities(short (*board)[9]);

bool test_for_same_step(list_of_steps *first, location from_where, location where);

bool list_search_for_same_step(list_of_steps *first, location s_where, location s_from_where);

void list_search_for_best_steps(list_of_steps *first, list_of_steps **best_steps, int actual_entity, bool wrong);

int list_lenght(list_of_steps *first);

list_of_steps *choose_from_list(list_of_steps *first, int serial_number);

void free_list(list_of_steps *first);

int difficulty_to_deepness(bool player_1_steps, AI_difficulty AI_1_diff, AI_difficulty AI_2_diff);

void print_list(list_of_steps *first);

void nullify_list(list_of_steps **first);

void step(short (*playboard)[9],location *step_locations_close, location *step_locations_far,location from_where,
           location where, int actual_entity, bool *player_1_steps);

bool test_for_step_validity(short (*playboard)[9], location *step_locations, location where);

void real_counter(short (*board)[9], int *blue, int *red);

void Menu(SDL_Renderer *renderer, textures *used_pictures, player *player_1, player *player_2,
           AI_difficulty *AI_1_diff, AI_difficulty *AI_2_diff, window_type *presently_used_window);

void Editor(SDL_Renderer *renderer, textures *used_pictures, short (*playboard)[9],
             window_type *presently_used_window, bool *player_1_steps);

void Game(SDL_Renderer *renderer, short (*playboard)[9], bool *player_1_steps, window_type *presently_used_window,
           textures *used_pictures, player player_1, player player_2, AI_difficulty AI_1_diff, AI_difficulty AI_2_diff);

void conquer(short (*playboard)[9], location where, int actual_entity);

int test_for_any_step(short (*playboard)[9], int index_x, int index_y);

bool test_and_save_steps(short (*board)[9], int x, int y, location *step_locations);

void start_finder(short (*AI_board)[9], location *starting_points, int actual_entity);

void AI_calculates_random_step(short (*playboard)[9], location *from_where, location *step, int actual_entitiy);

int AI_step_and_conquer_without_change(short (*AI_board)[9], location from_where, location step, int actual_entity);

void AI_step_and_conquer(short (*board)[9], location where, location from_where, int actual_entity);

list_of_steps *list_add_new(list_of_steps *first, location or_where, location or_from_where, int or_score);

void AI_calculates_all_steps(short (*playboard)[9], int actual_entity, list_of_steps **all_steps);

list_of_steps *AI_calculates_best_step(short (*playboard)[9], int actual_entity, list_of_steps **all_steps,
                              list_of_steps **best_steps);

void AI_makes_a_step(short (*playboard)[9], int actual_entity, bool *player_1_steps, AI_difficulty AI_1_diff,
                     AI_difficulty AI_2_diff);

int test_for_win(short (*playboard)[9]);

void test_for_end(SDL_Renderer *renderer, short (*playboard)[9], textures used_pictures,
                  window_type *presently_used_window, bool *player_1_steps, bool *ended);

void AI_can_step(short (*playboard)[9], bool *AI_steps, int actual_entity, bool *player_1_steps, bool *stepped,
                  AI_difficulty AI_1_diff, AI_difficulty AI_2_diff, player player_1, player player_2);

void editor_controller(SDL_Renderer *renderer, short (*playboard)[9], window_type *presently_used_window,
                        entity *placing, bool *changed, bool *player_1_steps);

void menu_controller(window_type *presently_used_window, player *player_1, player *player_2, bool *changed,
                      AI_difficulty *AI_1_diff, AI_difficulty *AI_2_diff);

#endif // HEXXAGON_CONTROL_H_INCLUDED
