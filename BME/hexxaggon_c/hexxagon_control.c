
#include "hexxagon_control.h"
#include "hexxagon_graphics.h"

// kesleltetes fuggveny
void delay(unsigned int mseconds){

    clock_t goal = mseconds + clock();
    while (goal > clock());
}

// meghatarozza a jatekteren a kattintas adattablaban helyet
location click_index(int click_x, int click_y){

    location click_location;
    int x = click_x;
    int xx = 35;
    int oszlop = - 1;


    while(x > xx){
        xx += 90;
        oszlop += 1;
    }

    int y = click_y;
    int yy = 30;
    int sor = - 1;

    while(y > yy){
        yy += 39;
        sor += 1;
    }

    click_location.x = oszlop;
    click_location.y = sor;

    return click_location;
}

void board_copy(short (*board_to)[9], short (*board_from)[9]){

    for(int i = 0; i < 17; i++)
        for(int j = 0; j < 9; j++)
            board_to[i][j] = board_from[i][j];
}

// visszaallitja a tablat az eredeti allapotaba
void reset(short (*playboard)[9], bool *player_1_steps){

    // 1 -> empty mezo   3 -> red   2 -> blue   0 -> semmi   -1 -> hole
    short reset[17][9] = { {0, 0, 0, 0, 2, 0, 0, 0, 0},
                            {0, 0, 0, 1, 0, 1, 0, 0, 0},
                            {0, 0, 1, 0, 1, 0, 1, 0, 0},
                            {0, 1, 0, 1, 0, 1, 0, 1, 0},
                            {3, 0, 1, 0, 1, 0, 1, 0, 3},
                            {0, 1, 0, 1, 0, 1, 0, 1, 0},
                            {1, 0, 1, 0, 1, 0, 1, 0, 1},
                            {0, 1, 0, 1, 0, 1, 0, 1, 0},
                            {1, 0, 1, 0, 1, 0, 1, 0, 1},
                            {0, 1, 0, 1, 0, 1, 0, 1, 0},
                            {1, 0, 1, 0, 1, 0, 1, 0, 1},
                            {0, 1, 0, 1, 0, 1, 0, 1, 0},
                            {2, 0, 1, 0, 1, 0, 1, 0, 2},
                            {0, 1, 0, 1, 0, 1, 0, 1, 0},
                            {0, 0, 1, 0, 1, 0, 1, 0, 0},
                            {0, 0, 0, 1, 0, 1, 0, 0, 0},
                            {0, 0, 0, 0, 3, 0, 0, 0, 0}
    };

    board_copy(playboard, reset);

    *player_1_steps = true;
}

// Jatek fuggvenyei
// kiszamolja ket kapott pont tavolsagat a rendszerben, de ha tobb, mint 2 akkor 3-at ad
int distance(int ax, int ay, int bx, int by){

    int line_distance;

    if(ax > by)
        line_distance = ax - by;

    else
        line_distance = by - ax;

    if(line_distance > 4)
        return 3;

    int column_distance;

    if(ay > bx)
        column_distance = ay - bx;

    else
        column_distance = bx - ay;

    if(column_distance > 2)
        return 3;

    if(column_distance == 2 && line_distance == 0)
        return 2;

    if(column_distance == 1 && line_distance == 1)
        return 1;

    if(column_distance == 0 && line_distance == 2)
        return 1;

    if(column_distance == 2 && line_distance == 2)
        return 2;

    return (column_distance + line_distance) / 2;
}

// kiszamolja az aktualis a gepnek
int counter(short (*board)[9]){

    int state = 0;

    for(int i = 0; i < 17; i++){

        for(int j = 0; j < 9; j++){

            if(board[i][j] == 2)
                state -= 1;

            if(board[i][j] == 3)
                state += 1;
        }
    }

    return state;
}

bool test_for_entities(short (*board)[9]){

    bool red_exists = false;
    bool blue_exists = false;

    for(int i = 0; i < 17; i++)
        for(int j = 0; j < 9; j++){

            if(board[i][j] == 2)
                blue_exists = true;

            if(board[i][j] == 3)
                red_exists = true;
        }

    return red_exists && blue_exists;
}

bool test_for_same_step(list_of_steps *first, location from_where, location where){

    for(list_of_steps *iter = first; iter != NULL; iter = iter->next)
        if(iter->where.x == where.x && iter->where.y == where.y && iter->from_where.x == from_where.x && iter->from_where.y == from_where.y)
            return true;

    return false;
}

bool list_search_for_same_step(list_of_steps *first, location s_where, location s_from_where){

    if(first == NULL)
        return false;

    for(list_of_steps *iter = first; iter != NULL; iter = iter -> next)
        if(iter -> where.x == s_where.x && iter -> where.y == s_where.y &&
           iter -> from_where.x == s_from_where.x && iter -> from_where.y == s_from_where.y)
            return true;

    return false;
}

void list_search_for_best_steps(list_of_steps *first, list_of_steps **best_steps, int actual_entity, bool wrong){

    int best_score = first -> score;

    if(!wrong){

        if(actual_entity == 3){

            for(list_of_steps *iter = first; iter != NULL; iter = iter -> next)
                if(iter -> score > best_score)
                    best_score = iter -> score;

            for(list_of_steps *iter = first; iter != NULL; iter = iter -> next)
                if(iter -> score == best_score)
                    *best_steps = list_add_new(*best_steps, iter -> where, iter -> from_where, iter -> score);
        }

        if(actual_entity == 2){

            for(list_of_steps *iter = first; iter != NULL; iter = iter -> next)
                if(iter -> score < best_score)
                    best_score = iter -> score;

            for(list_of_steps *iter = first; iter != NULL; iter = iter -> next)
                if(iter -> score == best_score)
                    *best_steps = list_add_new(*best_steps, iter -> where, iter -> from_where, iter -> score);
        }
    }

    else{

        int almost = first -> score;

        if(actual_entity == 3){

            for(list_of_steps *iter = first; iter != NULL; iter = iter -> next)
                if(iter -> score > best_score)
                    best_score = iter -> score;

            for(list_of_steps *iter = first; iter != NULL; iter = iter -> next)
                if(iter -> score > almost && iter -> score != best_score)
                    almost = iter -> score;

            for(list_of_steps *iter = first; iter != NULL; iter = iter -> next)
                if(iter -> score == almost)
                    *best_steps = list_add_new(*best_steps, iter -> where, iter -> from_where, iter -> score);
        }

        if(actual_entity == 2){

            for(list_of_steps *iter = first; iter != NULL; iter = iter -> next)
                if(iter -> score < best_score)
                    best_score = iter -> score;

            for(list_of_steps *iter = first; iter != NULL; iter = iter -> next)
                if(iter -> score < almost && iter -> score != best_score)
                    almost = iter -> score;

            for(list_of_steps *iter = first; iter != NULL; iter = iter -> next)
                if(iter -> score == almost)
                    *best_steps = list_add_new(*best_steps, iter -> where, iter -> from_where, iter -> score);
        }
    }
}

int list_lenght(list_of_steps *first){

    int lenght = 0;
    for(list_of_steps *iter = first; iter != NULL; iter = iter -> next)
        lenght += 1;

    return lenght;
}

list_of_steps *choose_from_list(list_of_steps *first, int serial_number){

    int serial = 0;
    for(list_of_steps *iter = first; iter != NULL; iter = iter -> next){

        if(serial == serial_number)
            return iter;

        serial += 1;
    }

    return NULL;
}

void free_list(list_of_steps *first){

    while(first != NULL){

        list_of_steps * iter = first;
        first = first -> next;
        free(iter);
    }
}

int difficulty_to_deepness(bool player_1_steps, AI_difficulty AI_1_diff, AI_difficulty AI_2_diff){

    if((player_1_steps && AI_1_diff == easy) || (!player_1_steps && AI_2_diff == easy))
        return 1;

    if((player_1_steps && AI_1_diff == medium) || (!player_1_steps && AI_2_diff == medium))
        return 2;

    if((player_1_steps && AI_1_diff == hard) || (!player_1_steps && AI_2_diff == hard))
        return 3;

    return 3;
}

void print_list(list_of_steps *first){

    system("cls");

    int i = 1;

    for(list_of_steps *iter = first; iter != NULL; iter = iter -> next){

        printf("%d. From: x = %d y = %d\n", i++, iter -> from_where.x, iter -> from_where.y);
        printf("    To: x = %d y = %d\n", iter -> where.x, iter -> where.y);
        printf("    Score = %d\n\n", iter -> score);
    }
}

void nullify_list(list_of_steps **first){

    list_of_steps *second = *first;

    free_list(second);

    *first = NULL;
}

// a babut az egerrel megadott helyre mozgatja, figyeli a lepesfajtat
void step(short (*playboard)[9],location *step_locations_close, location *step_locations_far,location from_where,
           location where, int actual_entity, bool *player_1_steps){

    for(int i = 0; i < 6; i++){

        if(step_locations_close[i].x == - 1 || step_locations_close[i].y == - 1)
            break;

        if(where.y == step_locations_close[i].x && where.x == step_locations_close[i].y)
            playboard[where.y][where.x] = actual_entity;
    }

    for(int j = 0; j < 12; j++){

        if(step_locations_far[j].x == - 1 || step_locations_far[j].y == - 1)
            break;

        if(where.y == step_locations_far[j].x && where.x == step_locations_far[j].y){

            playboard[where.y][where.x] = actual_entity;
            playboard[from_where.y][from_where.x] = 1;
        }
    }

    for(int k = 0; k < 6; k++){

        step_locations_close[k].x = - 1;
        step_locations_close[k].y = - 1;
    }

    for(int l = 0; l < 12; l++){

        step_locations_far[l].x = - 1;
        step_locations_far[l].y = - 1;
    }

    *player_1_steps = !*player_1_steps;
}

// megadja, hogy a vegrehajtani kivant step helyes-e
bool test_for_step_validity(short (*playboard)[9], location *step_locations, location where){

    for(int i = 0; i < 18; i++){

        if(step_locations[i].y == where.x && step_locations[i].x == where.y)
            return true;
    }
    return false;
}

void real_counter(short (*board)[9], int *blue, int *red){

    for(int i = 0; i < 17; i++){

        for(int j = 0; j < 9; j++){

            if(board[i][j] == 2)
                blue += 1;

            if(board[i][j] == 3)
                red += 1;
        }
    }
}

// Main fuggvenyei
// a menu_window fofuggvenye
void Menu(SDL_Renderer *renderer, textures *used_pictures, player *player_1, player *player_2,
           AI_difficulty *AI_1_diff, AI_difficulty *AI_2_diff, window_type *presently_used_window){

    // menu_background frissitese
    bool changed = true;

    while(*presently_used_window == menu_window && changed){

        draw_background(renderer, used_pictures -> menu_background);

        menu_button_animation(renderer, *player_1, *player_2, *AI_1_diff, *AI_2_diff);

        changed = false;

        menu_controller(presently_used_window, player_1, player_2, &changed, AI_1_diff, AI_2_diff);
    }
}

// az editornak a fofouggvenye
void Editor(SDL_Renderer *renderer, textures *used_pictures, short (*playboard)[9],
             window_type *presently_used_window, bool *player_1_steps){

    bool changed = true;
    entity placing;

    // palya frissitese
    while(*presently_used_window != quit && *presently_used_window == editor_window){

        if(changed){

            draw_background(renderer, used_pictures -> editor_background);

            editor_button_animation(renderer, placing);

            draw_entities(renderer, playboard, used_pictures);

            changed = false;
        }

        // egermozdulatok figyelese
        editor_controller(renderer, playboard, presently_used_window, &placing, &changed, player_1_steps);
    }
}

// game_window fofuggvenye
void Game(SDL_Renderer *renderer, short (*playboard)[9], bool *player_1_steps, window_type *presently_used_window,
           textures *used_pictures, player player_1, player player_2, AI_difficulty AI_1_diff, AI_difficulty AI_2_diff){

    bool wait_for_step = false;
    bool stepped = true;
    bool selected = false;
    bool ended = false;
    bool AI_steps;
    int actual_entity = 3;
    location selected_location;
    location step_location;
    location from_where;
    location step_locations[18];
    location step_locations_close[6];
    location step_locations_far[12];

    if(player_1 == AI && *player_1_steps)
        AI_steps = true;

    else if(player_2 == AI && !*player_1_steps)
        AI_steps = false;

    if(player_1 == human && player_2 == human)
        AI_steps = false;

    if(player_1 == human)
        AI_steps = false;

    while(*presently_used_window != quit && *presently_used_window == game_window && !ended){

        //jatekter kirajzolasa es frissitese
        if(stepped || selected){

            draw_background(renderer, used_pictures -> game_background);

            draw_state(renderer, playboard);

            if(selected){

                draw_selection(renderer, playboard, used_pictures -> selected_picture, selected_location);

                draw_step(renderer, used_pictures, step_locations, step_locations_close, step_locations_far, selected_location);

                selected = false;
            }

            draw_entities(renderer, playboard, used_pictures);

            stepped = false;

        }

        ended = !test_for_entities(playboard);

        test_for_end(renderer, playboard, *used_pictures, presently_used_window, player_1_steps, &ended);

        if(AI_steps && !ended)
            AI_can_step(playboard, &AI_steps, actual_entity, player_1_steps, &stepped, AI_1_diff, AI_2_diff, player_1, player_2);

        else{

            SDL_Event event;
            SDL_WaitEvent(&event);

            selected_location = click_index(event.button.x, event.button.y);

            step_location = click_index(event.button.x, event.button.y);

            // kattintasok kezelese
            switch (event.type){

                // kilepes
                case SDL_QUIT:

                    *presently_used_window = quit;

                break;


                case SDL_MOUSEBUTTONDOWN:

                    // menu_window gomb lenyomasa -> menu_window
                    if(event.button.button == SDL_BUTTON_LEFT && event.button.x > 59
                        && event.button.x < 167 && event.button.y > 649 && event.button.y < 689) {

                        *presently_used_window = menu_window;
                    }

                    if(*player_1_steps)
                        actual_entity = 3;

                    else
                        actual_entity = 2;

                    if(!wait_for_step){

                        if(!wait_for_step && event.button.button == SDL_BUTTON_LEFT &&
                            test_and_save_steps(playboard, selected_location.y, selected_location.x, step_locations) &&
                            playboard[selected_location.y][selected_location.x] == actual_entity){

                            from_where = click_index(event.button.x, event.button.y);

                            selected = true;
                            wait_for_step = true;
                        }
                    }

                    else{

                        if(event.button.button == SDL_BUTTON_LEFT &&
                            test_for_step_validity(playboard, step_locations, step_location) &&
                            wait_for_step){

                            step(playboard, step_locations_close, step_locations_far, from_where, step_location, actual_entity, player_1_steps);

                            conquer(playboard, step_location, actual_entity);

                            wait_for_step = false;
                            stepped = true;

                            if(player_1 == AI || player_2 == AI)
                                AI_steps = true;
                        }

                        else{

                            wait_for_step = false;
                            stepped = false;

                            draw_background(renderer, used_pictures -> game_background);

                            draw_state(renderer, playboard);

                            draw_entities(renderer, playboard, used_pictures);
                        }
                    }

                    break;
            }
        }
    }
}


// elfoglalja a babuval szomszedos ellenseges babukat
void conquer(short (*playboard)[9], location where, int actual_entity){

    if(actual_entity == 3)
        for(int i = 0; i < 17; i++)
            for(int j = 0; j < 9; j++)
                if(playboard[i][j] == 2 && distance(i, j, where.x, where.y) == 1)
                    playboard[i][j] = actual_entity;

    if(actual_entity == 2)
        for(int i = 0; i < 17; i++)
            for(int j = 0; j < 9; j++)
                if(playboard[i][j] == 3 && distance(i, j, where.x, where.y) == 1)
                    playboard[i][j] = actual_entity;
}

// ellenorzi, hogy can_step barmelyik entity, 1 -> igen, 2 -> nem
int test_for_any_step(short (*playboard)[9], int index_x, int index_y){

    for(int i = 0; i < 17; i++)
        for(int j = 0; j < 9; j++)
            if(distance(index_x, index_y, j, i) <= 2 && playboard[i][j] == 1)
                return 1;

    return 0;
}

// megmondja, hogy a selected_location entity can_step-e, es elmenti a lehetseges lepesek helyeit
bool test_and_save_steps(short (*board)[9], int x, int y, location *step_locations){

    for(int i = 0; i < 18; i++){

        step_locations[i].x = - 1;
        step_locations[i].y = - 1;
    }

    bool can_step = false;
    int z = 0;
    for(int i = 0; i < 17; i++){
        for(int j = 0; j < 9; j++){
            if(distance(x, y, j, i) <= 2 && board[i][j] == 1 && (board[x][y] == 2 || board[x][y] == 3)){
                step_locations[z].x = i;
                step_locations[z].y = j;
                z++;
                can_step = true;

            }
        }
    }
    return can_step;
}

// megkeresi a gep szamara a kiindulo pontokat
void start_finder(short (*AI_board)[9], location *starting_points, int actual_entity){

    int i_start = 0;

    for(int i = 0; i < 58; i++){

        starting_points[i].x = - 1;
        starting_points[i].y = - 1;
    }

    for(int i = 0; i < 17; i++)
        for(int j = 0; j < 9; j++)

            if(AI_board[i][j] == actual_entity && test_for_any_step(AI_board, i, j) == 1){

                starting_points[i_start].x = i;
                starting_points[i_start].y = j;
                i_start += 1;
            }
}

// gep kiszamol egy random lepest
void AI_calculates_random_step(short (*playboard)[9], location *from_where, location *step, int actual_entitiy){

    short AI_board[17][9];

    board_copy(AI_board, playboard);

    location starting_points[58];
    location AI_step_locations[18];

    start_finder(AI_board, starting_points, actual_entitiy);

    int random_point;

    for(int i = 0; i < 58; i++)
        if(starting_points[i].x != - 1)
            random_point = i;

    if(random_point != 0)
        random_point = rand() % random_point;

    *from_where = starting_points[random_point];

    bool can_step = test_and_save_steps(AI_board, from_where -> x, from_where -> y, AI_step_locations);

    for(int i = 0; i < 18; i++)
        if(AI_step_locations[i].x != - 1)
            random_point = i;

    if(random_point != 0)
        random_point = rand() % random_point;

    *step = AI_step_locations[random_point];

    if(!can_step)
        return;
}

// a gep szamol a sajat tablajan
int AI_step_and_conquer_without_change(short (*AI_board)[9], location from_where, location step, int actual_entity){

    short board[17][9];

    board_copy(board, AI_board);

    if(distance(from_where.y, from_where.x, step.x, step.y) < 2 &&
        (from_where.y - step.y < 2 && from_where.y - step.y > - 2))
            board[step.x][step.y] = actual_entity;

    else{

        if((from_where.x - step.x <= 2 && from_where.x - step.x >= - 2) &&
            (from_where.y - step.y == 0))
            board[step.x][step.y] = actual_entity;

        else{

            board[step.x][step.y] = actual_entity;
            board[from_where.x][from_where.y] = 1;
        }
    }

    int temp = step.x;
    step.x = step.y;
    step.y = temp;

    conquer(board, step, actual_entity);

    return counter(board);
}

void AI_step_and_conquer(short (*board)[9], location where, location from_where, int actual_entity){

    location step = where;

    if(distance(from_where.y, from_where.x, step.x, step.y) < 2 &&
        (from_where.y - step.y < 2 && from_where.y - step.y > - 2))
            board[step.x][step.y] = actual_entity;

    else{

        if((from_where.x - step.x <= 2 && from_where.x - step.x >= - 2) &&
            (from_where.y - step.y == 0))
            board[step.x][step.y] = actual_entity;

        else{

            board[step.x][step.y] = actual_entity;
            board[from_where.x][from_where.y] = 1;
        }
    }

    int temp = step.x;
    step.x = step.y;
    step.y = temp;

    conquer(board, step, actual_entity);
}

list_of_steps *list_add_new(list_of_steps *first, location or_where, location or_from_where, int or_score){

    if(first == NULL){

        list_of_steps *new_member = (list_of_steps*) malloc(sizeof(list_of_steps));
        new_member -> from_where = or_from_where;
        new_member -> where = or_where;
        new_member -> score = or_score;
        new_member -> next = NULL;

        return new_member;
    }

    else{

        if(test_for_same_step(first, or_from_where, or_where))
            return first;

        list_of_steps *iter;

        for(iter = first; iter -> next != NULL; iter = iter -> next);

        list_of_steps *new_member = (list_of_steps *) malloc(sizeof(list_of_steps));

        new_member -> from_where = or_from_where;
        new_member -> where = or_where;
        new_member -> score = or_score;
        new_member -> next = NULL;

        iter -> next = new_member;

        return first;
    }
}

void AI_calculates_all_steps(short (*playboard)[9], int actual_entity, list_of_steps **all_steps){

    location steps[18];
    location from_where[58];

    short AI_board[17][9];

    board_copy(AI_board, playboard);

    start_finder(AI_board, from_where, actual_entity);

    for(int i = 0; i < 58; i++){

        if(from_where[i].x == - 1)
            break;

         test_and_save_steps(AI_board, from_where[i].x, from_where[i].y, steps);

        for(int j = 0; j < 18; j++){

            if(steps[j].x == - 1)
                break;

            int score = AI_step_and_conquer_without_change(AI_board, from_where[i], steps[j], actual_entity);

            *all_steps = list_add_new(*all_steps, steps[j], from_where[i], score);
        }
    }


}

list_of_steps *AI_calculates_best_step(short (*playboard)[9], int actual_entity, list_of_steps **all_steps,
                              list_of_steps **best_steps){

    AI_calculates_all_steps(playboard, actual_entity, all_steps);

    list_search_for_best_steps(*all_steps, best_steps, actual_entity, false);

    int best_steps_count = list_lenght(*best_steps);

    int random_step = rand() % best_steps_count;

    return choose_from_list(*best_steps, random_step);;
}

// a gep lep egyet es foglal a megadott koordinatak alapjan
void AI_makes_a_step(short (*playboard)[9], int actual_entity, bool *player_1_steps, AI_difficulty AI_1_diff,
                     AI_difficulty AI_2_diff){

    list_of_steps *all_steps = NULL;
    list_of_steps *best_steps = NULL;
    list_of_steps *enemy_counter_steps = NULL;
    list_of_steps *best_enemy_counter_steps = NULL;
    list_of_steps *d_2_steps = NULL;
    list_of_steps *d_2_best_steps = NULL;
    int attack_entity = actual_entity;
    bool end = false;

    short AI_board[17][9];

    int deepness = difficulty_to_deepness(*player_1_steps, AI_1_diff, AI_2_diff);

    bool ready = false;

    int score_after_enemy_counter;

    board_copy(AI_board, playboard);

    list_of_steps *chosen_step = AI_calculates_best_step(AI_board, attack_entity, &all_steps, &best_steps);

    if(deepness == 1){

        if(rand() % 10 < 6)
            AI_calculates_random_step(AI_board, &chosen_step -> from_where, &chosen_step -> where, actual_entity);

        ready = true;
        AI_step_and_conquer(AI_board, chosen_step -> where, chosen_step -> from_where, attack_entity);
        chosen_step = NULL;
    }

    chosen_step = NULL;

    if((deepness == 3 || deepness == 2) && !ready){

        for(list_of_steps *iter = all_steps; iter != NULL; iter = iter -> next){

            AI_step_and_conquer(AI_board, iter -> where, iter -> from_where, attack_entity);

            if(attack_entity == 2)
                attack_entity = 3;

            else
                attack_entity = 2;

            if(!test_for_entities(AI_board) || test_for_win(AI_board) != 1){

                end = true;
                break;
            }

            chosen_step = AI_calculates_best_step(AI_board, attack_entity, &enemy_counter_steps, &best_enemy_counter_steps);

            AI_step_and_conquer(AI_board, chosen_step -> where, chosen_step -> from_where, attack_entity);

            nullify_list(&enemy_counter_steps);
            nullify_list(&best_enemy_counter_steps);

            score_after_enemy_counter = counter(AI_board);

            d_2_steps = list_add_new(d_2_steps, iter -> where, iter -> from_where, score_after_enemy_counter);

            if(attack_entity == 2)
                attack_entity = 3;

            else
                attack_entity = 2;

            chosen_step = NULL;

            board_copy(AI_board, playboard);
        }

        if(!end){

            list_search_for_best_steps(d_2_steps, &d_2_best_steps, attack_entity, false);

            if(deepness == 2){

                if(rand() % 10 < 9){

                    list_search_for_best_steps(d_2_steps, &d_2_best_steps, attack_entity, true);
                }
            }

            int best_steps_count = list_lenght(d_2_best_steps);

            int random_step = rand() % best_steps_count;

            chosen_step = choose_from_list(d_2_best_steps, random_step);

            AI_step_and_conquer(AI_board, chosen_step -> where, chosen_step -> from_where, attack_entity);

            ready = true;

            chosen_step = NULL;
        }
    }

    if(end){

        attack_entity = actual_entity;

        int best_steps_count = list_lenght(best_steps);

        int random_step = rand() % best_steps_count;

        chosen_step = choose_from_list(best_steps, random_step);

        AI_step_and_conquer(AI_board, chosen_step -> where, chosen_step -> from_where, attack_entity);
    }

    board_copy(playboard, AI_board);

    *player_1_steps = !*player_1_steps;

    free_list(all_steps);
    free_list(best_steps);
    free_list(d_2_steps);
    free_list(d_2_best_steps);
    free_list(enemy_counter_steps);
    free_list(best_enemy_counter_steps);
}

// ellenorzi, hogy test_for_win-e valamelyik player 0 - ended, 1 - nincs ended, 2 - blue test_for_win, 3 - red test_for_win, 4 - dontetlen
int test_for_win(short (*playboard)[9]){

    int state = 0;
    bool blue_can, red_can = false;

    for(int i = 0; i < 17; i++)
        for(int j = 0; j < 9; j++){

            if(playboard[i][j] == 2){

                if(test_for_any_step(playboard, i, j) == 1)
                    blue_can = true;

                else
                    state = test_for_any_step(playboard, i, j);
            }

            else if(playboard[i][j] == 3){

                if(test_for_any_step(playboard, i, j) == 1)
                    red_can = true;

                else
                    state = test_for_any_step(playboard, i, j);
            }
        }

    if(blue_can && red_can)
        return 1;

    if(state == 0){

        state = counter(playboard);

        if(state > 0)
            return 3;

        if(state < 0)
            return 2;

        if(state == 0)
            return 4;
    }

    return state;
}

void test_for_end(SDL_Renderer *renderer, short (*playboard)[9], textures used_pictures,
                  window_type *presently_used_window, bool *player_1_steps, bool *ended){

    int winner_player;

    int win_type = test_for_win(playboard);

    if(win_type == 3)
        for(int i = 0; i < 17; i++)
            for(int j = 0; j < 9; j++)
                if(playboard[i][j] == 1)
                    playboard[i][j] = 3;


    if(win_type == 2)
        for(int i = 0; i < 17; i++)
            for(int j = 0; j < 9; j++)
                if(playboard[i][j] == 1)
                    playboard[i][j] = 2;

    if(win_type != 1)
        *ended = true;

    if(win_type == 2)
        winner_player = 2;

    else if(win_type == 3)
        winner_player = 3;

    else if(win_type == 4)
        winner_player = 4;

    if(*ended)
        draw_winner_background(renderer, playboard, &used_pictures, presently_used_window, player_1_steps,
                               winner_player);
}

void AI_can_step(short (*playboard)[9], bool *AI_steps, int actual_entity, bool *player_1_steps, bool *stepped,
                  AI_difficulty AI_1_diff, AI_difficulty AI_2_diff, player player_1, player player_2){

    if(*player_1_steps)
        actual_entity = 3;

    else
        actual_entity = 2;

    delay(500);

    AI_makes_a_step(playboard, actual_entity, player_1_steps, AI_1_diff, AI_2_diff);

    if(player_1 == AI && player_2 == AI)
        *AI_steps = true;

    else
        *AI_steps = false;

    *stepped = true;
}

// Editor fuggvenyei
// a kattintasokat vezerli az editorban
void editor_controller(SDL_Renderer *renderer, short (*playboard)[9], window_type *presently_used_window,
                        entity *placing, bool *changed, bool *player_1_steps){

    while(*presently_used_window != quit && *presently_used_window == editor_window && !*changed){

        location click_location;

        SDL_Event event;
        SDL_WaitEvent(&event);
        switch (event.type){

        // kilepes
        case SDL_QUIT:

            *presently_used_window = quit;

            break;

        case SDL_MOUSEBUTTONDOWN:

            // click_location megahatarozasa
            click_location = click_index(event.button.x, event.button.y);

            // menu_window gomb lenyomasa -> menu_window
            if (event.button.button == SDL_BUTTON_LEFT && event.button.x > 59
                && event.button.x < 167 && event.button.y > 649 && event.button.y < 689)
                *presently_used_window = menu_window;

            // reset
            if(event.button.button == SDL_BUTTON_LEFT && event.button.x > 761
                    && event.button.x < 869 && event.button.y > 95 && event.button.y < 135){

                reset(playboard, player_1_steps);
                *changed = true;
            }

            // blue gombja -> keket akaarunk rakni
            if(event.button.button == SDL_BUTTON_LEFT && event.button.x > 691
                    && event.button.x < 731 && event.button.y > 52 && event.button.y < 81){

                *placing = blue;
                *changed = true;
            }

            // red gombja -> pirosat akaarunk rakni
            if(event.button.button == SDL_BUTTON_LEFT && event.button.x > 751
                    && event.button.x < 791 && event.button.y > 52 && event.button.y < 81){

                *placing = red;
                *changed = true;
            }

            // hole gombja -> lyukakat akaarunk rakni
            if(event.button.button == SDL_BUTTON_LEFT && event.button.x > 811
                    && event.button.x < 851 && event.button.y > 52 && event.button.y < 81){

                *placing = hole;
                *changed = true;
            }

            // blue szerkesztese
            if((event.button.button == SDL_BUTTON_LEFT && *placing == blue) || (event.button.button == SDL_BUTTON_RIGHT && *placing == blue)){

                click_location = click_index(event.button.x, event.button.y);

                if(playboard[click_location.y][click_location.x] != 0 && playboard[click_location.y][click_location.x] != -1
                    && playboard[click_location.y][click_location.x] != 3 && event.button.button == SDL_BUTTON_LEFT)
                    playboard[click_location.y][click_location.x] = 2;

                if(playboard[click_location.y][click_location.x] == 2 && event.button.button == SDL_BUTTON_RIGHT)
                    playboard[click_location.y][click_location.x] = 1;

                *changed = true;

            }

            // red szerkesztese
            if((event.button.button == SDL_BUTTON_LEFT && *placing == red) || (event.button.button == SDL_BUTTON_RIGHT && *placing == red)){

                click_location = click_index(event.button.x, event.button.y);

                if(playboard[click_location.y][click_location.x] != 0 && playboard[click_location.y][click_location.x] != -1
                    && playboard[click_location.y][click_location.x] != 2 && event.button.button == SDL_BUTTON_LEFT)
                    playboard[click_location.y][click_location.x] = 3;

                if(playboard[click_location.y][click_location.x] == 3 && event.button.button == SDL_BUTTON_RIGHT)
                    playboard[click_location.y][click_location.x] = 1;

                *changed = true;

            }

            // hole szerkesztese
            if((event.button.button == SDL_BUTTON_LEFT && *placing == hole) || (event.button.button == SDL_BUTTON_RIGHT && *placing == hole)){

                click_location = click_index(event.button.x, event.button.y);

                if(playboard[click_location.y][click_location.x] == - 1 && event.button.button == SDL_BUTTON_LEFT)
                    playboard[click_location.y][click_location.x] = 1;

                if(playboard[click_location.y][click_location.x] == 1 && event.button.button == SDL_BUTTON_RIGHT)
                    playboard[click_location.y][click_location.x] = - 1;

                *changed = true;

            }
        }
    }
}

// Menu fuggvenyei
// a kattintasokat vezerli a menuben
void menu_controller(window_type *presently_used_window, player *player_1, player *player_2, bool *changed,
                      AI_difficulty *AI_1_diff, AI_difficulty *AI_2_diff){

    while (*presently_used_window != quit && *presently_used_window == menu_window && !*changed){

            SDL_Event event;
            SDL_WaitEvent(&event);

            // kattintasok kezelese
            switch (event.type){

                // kilepes
                case SDL_QUIT:

                    *presently_used_window = quit;

                break;

                // egergomb lenyomasa
                case SDL_MOUSEBUTTONDOWN:

                    // game_window gomb -> game_window inditasa
                    if (event.button.button == SDL_BUTTON_LEFT && event.button.x > 289
                        && event.button.x < 591 && event.button.y > 499 && event.button.y < 541) {

                        *presently_used_window = game_window;
                    }

                    // editor gomb -> editor inditasa
                    if (event.button.button == SDL_BUTTON_LEFT && event.button.x > 289
                        && event.button.x < 591 && event.button.y > 554 && event.button.y < 596) {

                        *presently_used_window = editor_window;
                    }

                    // kilepes gomb -> kilepes
                    if (event.button.button == SDL_BUTTON_LEFT && event.button.x > 289
                        && event.button.x < 591 && event.button.y > 609 && event.button.y < 651) {

                        *presently_used_window = quit;
                    }

                    // player_1 human
                    if (event.button.button == SDL_BUTTON_LEFT && event.button.x > 53
                        && event.button.x < 215 && event.button.y > 498 && event.button.y < 538) {

                        *player_1 = human;
                        *changed = true;
                    }

                    // player_1 AI
                    if (event.button.button == SDL_BUTTON_LEFT && event.button.x > 53
                        && event.button.x < 215 && event.button.y > 553 && event.button.y < 593) {

                        *player_1 = AI;
                        *AI_1_diff = easy;
                        *changed = true;
                    }

                    // player_1 AI
                    if (event.button.button == SDL_BUTTON_LEFT && event.button.x > 53
                        && event.button.x < 215 && event.button.y > 608 && event.button.y < 648) {

                        *player_1 = AI;
                        *AI_1_diff = medium;
                        *changed = true;
                    }

                    // player_1 AI
                    if (event.button.button == SDL_BUTTON_LEFT && event.button.x > 53
                        && event.button.x < 215 && event.button.y > 663 && event.button.y < 703) {

                        *player_1 = AI;
                        *AI_1_diff = hard;
                        *changed = true;
                    }

                    // player_2 human
                    if (event.button.button == SDL_BUTTON_LEFT && event.button.x > 665
                        && event.button.x < 827 && event.button.y > 498 && event.button.y < 538) {

                        *player_2 = human;
                        *changed = true;
                    }

                    // player_2 AI
                    if (event.button.button == SDL_BUTTON_LEFT && event.button.x > 665
                        && event.button.x < 827 && event.button.y > 553 && event.button.y < 593) {

                        *player_2 = AI;
                        *AI_2_diff = easy;
                        *changed = true;
                    }

                    // player_2 AI
                    if (event.button.button == SDL_BUTTON_LEFT && event.button.x > 665
                        && event.button.x < 827 && event.button.y > 608 && event.button.y < 648) {

                        *player_2 = AI;
                        *AI_2_diff = medium;
                        *changed = true;
                    }

                    // player_2 AI
                    if (event.button.button == SDL_BUTTON_LEFT && event.button.x > 665
                        && event.button.x < 827 && event.button.y > 663 && event.button.y < 703) {

                        *player_2 = AI;
                        *AI_2_diff = hard;
                        *changed = true;
                    }

                    break;

            }
        }
}
