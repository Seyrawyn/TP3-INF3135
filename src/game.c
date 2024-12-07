//
// Created by Jean-Christophe Clouatre on 2023-04-04.
//

# include "game.h"
#include<unistd.h>


/*
 * Section des rendus
 */


/**
 * This function background_render is responsible for rendering the background of the game. 
 * It takes a SDL_Renderer pointer as an argument, which is used to render the background.
 * 
 * @param renderer - The renderer used to render the background
*/
void background_render(SDL_Renderer *renderer) {
    int centerX = SCREEN_WIDTH / 2;
    int centerY = SCREEN_HEIGHT / 2;
    int radius = (int) sqrt(pow(SCREEN_WIDTH / 2, 2) + pow(SCREEN_HEIGHT / 2, 2));
    int start_angle = 0;
    int end_angle = 60;

    for (int i = 0; i < 6; i++) {
        Uint32 color = (i % 2 == 0) ? 0xFFFFFFFF : 0xFFCCCCCC;
        filledPieColor(renderer, centerX, centerY, radius, start_angle, end_angle, color);
        start_angle += 60;
        end_angle += 60;
    }
}

/**
 * This function render_elapsed_time is responsible for rendering the elapsed time of the game.
 * It takes a SDL_Renderer pointer, a Uint32 elapsed_time and a TTF_Font pointer as arguments.
 * 
 * @param renderer - The renderer used to render the elapsed time
 * @param elapsed_time - The elapsed time of the game
 * @param font - The font used to render the elapsed time
*/
void render_elapsed_time(SDL_Renderer *renderer, Uint32 elapsed_time, TTF_Font *font) {
    char time_text[32];
    Uint32 seconds = elapsed_time / 1000;
    Uint32 minutes = seconds / 60;
    seconds = seconds % 60;

    snprintf(time_text, sizeof(time_text), "%02u:%02u", minutes, seconds);

    SDL_Color text_color = {255, 0, 255, 255};
    SDL_Surface *text_surface = TTF_RenderText_Solid(font, time_text, text_color);

    if (text_surface == NULL) {
        printf("Failed to render text: %s\n", TTF_GetError());
        return;
    } else {
        SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

        SDL_Rect dest_rect;
        dest_rect.x = SCREEN_WIDTH - text_surface->w - 10;
        dest_rect.y = 10;
        dest_rect.w = text_surface->w;
        dest_rect.h = text_surface->h;

        SDL_RenderCopy(renderer, text_texture, NULL, &dest_rect);

        SDL_DestroyTexture(text_texture);
        SDL_FreeSurface(text_surface);
    }
}

/**
 * This function is used to render the player on the game screen using the provided SDL renderer. 
 * It calculates the position of the player based on its angle and distance from the center 
 * of the screen, and then draws a triangular shape.
 * 
 * @param renderer - The renderer used to render the player
 * @param player - a pointer to a player struct that contains information about the player, 
 * such as its position, angle, and size.
*/
void player_render(SDL_Renderer *renderer, struct player *player) {
    int centerX = SCREEN_WIDTH / 2;
    int centerY = SCREEN_HEIGHT / 2;
    float radian_angle = player->angle * M_PI / 180.0f;
    int player_x = centerX + player->distance * cos(radian_angle);
    int player_y = centerY + player->distance * sin(radian_angle);

    Sint16 vx[3] = {
            player_x + player->size / 2 * cos(radian_angle),
            player_x + player->size / 2 * cos(radian_angle + 2 * M_PI / 3),
            player_x + player->size / 2 * cos(radian_angle - 2 * M_PI / 3)
    };
    Sint16 vy[3] = {
            player_y + player->size / 2 * sin(radian_angle),
            player_y + player->size / 2 * sin(radian_angle + 2 * M_PI / 3),
            player_y + player->size / 2 * sin(radian_angle - 2 * M_PI / 3)
    };

    filledPolygonColor(renderer, vx, vy, 3, 0xFFFF0000);
}


/**
 * This function is used to render the foreground of the game screen using the provided SDL renderer.
 * It draws a circle in the center of the screen.
 * 
 * @param renderer - The renderer used to render the foreground
*/
void foreground(SDL_Renderer *renderer) {
    int centerX = SCREEN_WIDTH / 2;
    int centerY = SCREEN_HEIGHT / 2;

    filledCircleColor(renderer, centerX, centerY, INNER_CIRCLE_RADIUS, 0xFF444444);
}


/**
 * The wall_render function renders the walls of the game onto the screen. 
 * The function takes a pointer to the game struct as an argument, 
 * which contains the renderer and the linked list of walls.
 * 
 * @param game - The game struct containing the renderer and the linked list of walls
*/
void wall_render(struct game *game){
    int centerX = SCREEN_WIDTH / 2;
    int centerY = SCREEN_HEIGHT / 2;
    int start_angle[6] = {0, 60, 120, 180, 240, 300};
    int end_angle[6] = {60, 120, 180, 240, 300, 360};
    struct wall *wall = game->wall_last;
    Uint32 color_wall = 0xFF0000FF;

    while (wall != NULL) {
        Uint32 color = (wall->zone % 2 == 0) ? 0xFFFFFFFF : 0xFFCCCCCC;
        filledPieColor(game->renderer, centerX, centerY, wall->distance + 10, start_angle[wall->zone], end_angle[wall->zone], color_wall);
        filledPieColor(game->renderer, centerX, centerY, wall->distance, start_angle[wall->zone], end_angle[wall->zone], color);
        wall = wall->previous;
    }
}

void game_render(struct game *game) {
    SDL_SetRenderDrawColor(game->renderer, BACKGROUND_COLOR_R, BACKGROUND_COLOR_G, BACKGROUND_COLOR_B, 255);
    SDL_RenderClear(game->renderer);

    background_render(game->renderer);
    wall_render(game);
    render_elapsed_time(game->renderer, game->time->timer, game->time->font);
    foreground(game->renderer);
    player_render(game->renderer, game->player);

    SDL_RenderPresent(game->renderer);
}


/*
 * Section des initialisations
 */



/**
 * The function wall_spawn_recurence returns the time in milliseconds between two wall spawns.
 * The time is calculated based on the difficulty level.
 * 
 * @param difficulty The difficulty level of the game.
 * 
*/
Uint32 wall_spawn_recurence(int difficulty) {
    if (difficulty == 0) {
        return 4000;
    } else if (difficulty == 1) {
        return 6500;
    } else {
        return 3000;
    }
}


/**
 * This function calculates and returns the speed of the walls based on the given difficulty level.
 * 
 * - For difficulty level 0, the speed is set to a constant value of 0.5f.
 * - For difficulty level 1, the speed is set to a random value between 0.5f and 1.0f.
 * - For difficulty level 2, the speed is set to a random value between 0.5f and 1.0f.
 * 
 * @param difficulty The difficulty level of the game.
*/
float wall_speed(int difficulty) {
    if (difficulty == 0) {
        return 0.5f;
    } else if (difficulty == 1) {
        float result = ((float)(random() % 5)) / 10;
        if (result == 0) {
            result = 0.5f;
        }
        return result;
    } else {
        return ((float)((random() %5) + 5)) / 10;
    }
}

/**
 * The function wall_initialise creates and initializes a new wall object with the specified difficulty level.
 *  It allocates memory for the wall using the malloc function and sets all of its attributes to their initial values.
 *  The wall_speed function is called to determine the speed of the wall based on the difficulty level.
 * 
 * @param difficulty  - an integer representing the difficulty level of the game.
 * @return wall       - a pointer to the newly created wall object.
*/
struct wall *wall_initialise(int difficulty) {
    struct wall *wall = malloc(sizeof(struct wall));

    memset(wall, 0, sizeof(struct wall));

    wall->distance = WALL_DISTANCE_CENTRE;
    wall->zone = random() % 6;
    wall->speed = wall_speed(difficulty);


    return wall;
}


/**
 * 
*/
struct player *player_initialise() {
    struct player *player = malloc(sizeof(struct player));
    memset(player, 0, sizeof(struct player));

    player->size = PLAYER_SIZE;
    player->distance = RADIUS;

    return player;
}

/**
 * This function is responsible for initializing the player struct by allocating memory 
 * for it and setting default values for its members.
 * 
 * @return player - a pointer to the newly created player object.
*/
struct time *timer_initialise() {
    struct time *time = malloc(sizeof(struct time));
    memset(time, 0, sizeof(struct time));

    time->timer_begin = SDL_GetTicks();
    time->font = TTF_OpenFont("../assets/BungeeSpice-Regular.ttf", 30);

    if (time->font == NULL) {
        printf("Failed to load font: %s\n", TTF_GetError());
        return NULL;
    }
    return time;
}


/**
 * This function initializes a new game instance with the given difficulty level, 
 * and allocates memory for all the game objects (such as player and walls) using malloc(). 
 * It then sets the game's renderer and event pointers to the given values, and initializes 
 * the game's time, player, and walls using their respective initialization functions.
 * 
 * @param renderer   - a pointer to the SDL_Renderer object used to render the game.
 * @param event      - a pointer to the SDL_Event object used to handle user input.
 * @param difficulty - an integer representing the difficulty level of the game.
 * @return game      - a pointer to the newly created game object.
*/
struct game *game_initialise(SDL_Renderer *renderer, SDL_Event *event, int difficulty) {
    struct game *game = malloc(sizeof(struct game));

    memset(game, 0, sizeof(struct game));
    game->renderer = renderer;
    game->event = event;
    game->difficulty = difficulty;
    game->time = timer_initialise();
    if (game->time == NULL) {
        return NULL;
    }
    game->player = player_initialise();
    game->wall_first = wall_initialise(difficulty);
    game->wall_first->next = wall_initialise(difficulty);
    game->wall_first->next->previous = game->wall_first;
    game->wall_last = game->wall_first->next;

    game->temps_next_apperence = wall_spawn_recurence(difficulty);

    return game;
}


/*
 * Section des mises à jour
 */


/**
 * handles input from the user during the game loop and updates the game state accordingly. Specifically,
 *  it checks if a key has been pressed and responds accordingly.
 * 
 * @param game  - a pointer to a game struct representing the current game state.
 * @param music - a pointer to a music struct representing the current music state.
 * 
*/
void game_handle_input(struct game *game,struct music *music) {
    if (game->event->type == SDL_KEYDOWN) {
        switch (game->event->key.keysym.sym) {
            case SDLK_LEFT:
                game->player->angle += 5.0f;
                if (game->player->angle > 360) {
                    game->player->angle -= 360;
                }
                break;
            case SDLK_RIGHT:
                game->player->angle -= 5.0f;
                if (game->player->angle < 0) {
                    game->player->angle += 360;
                }
                break;
            case SDLK_SPACE:
                change_music_track(music);
                break;
        }
    }
}

/**
 * This function creates and adds new wall objects to the game by appending them to the end of the linked list of wall objects.
 * 
 * @param game - a pointer to the game struct that contains information about the game.
 * @param amount - an integer representing the number of walls to be added to the game.
*/
void wall_writting(struct game *game, int amount) {
    struct wall *wall = game->wall_last;

    for (int i = 0; i < amount; ++i) {
        wall->next = wall_initialise(game->difficulty);
        wall->next->previous = wall;
        wall = wall->next;
        game->wall_last = wall;
    }
}

/**
 * This function is responsible for determining the number of walls that will appear on the screen 
 * based on the time elapsed since the last wall appeared.
 * 
 * @param game - a pointer to the game struct that contains information about the game.
*/
void wall_apperence_number(struct game *game) {
    if (game->next_apperence < 15000) {
        wall_writting(game, 2);
    } else if (game->next_apperence < 30000) {
        wall_writting(game, 3);
    } else if (game->next_apperence < 45000) {
        wall_writting(game, 4);
    } else {
        wall_writting(game, 5);
    }
}

/**
 * This function is responsible for removing walls that have passed the player and are no longer visible on the screen.
 * 
 * @param game - a pointer to the game struct that contains information about the game.
*/
void clear_dead_wall(struct game *game) {
    struct wall *wall = game->wall_first;
    while (1) {
        if (wall->distance <= INNER_CIRCLE_RADIUS - 10) {
            wall->next->previous = NULL;
            game->wall_first = wall->next;
            free(wall);
            wall = game->wall_first;
        } else {
            break;
        }
    }
}

/**
 * This function is responsible for updating the game state. Specifically, it updates the game's timer,
 * checks for user input, updates the position of the walls, and checks if new walls should be added to the game.
 * 
 * @param game  - a pointer to a game struct representing the current game state.
*/
void game_update(struct game *game, struct music *music){
    struct wall *wall = game->wall_first;
    while (SDL_PollEvent(game->event)) {
        game_handle_input(game, music);
    }
    while (wall != NULL) {
        wall->distance -= wall->speed;
        wall = wall->next;
    }
    if (game->next_apperence < game->time->timer) {
        wall_apperence_number(game);
        game->next_apperence += game->temps_next_apperence;
    }
    clear_dead_wall(game);


    game->time->timer = SDL_GetTicks() - game->time->timer_begin;
}

//TODO
/**
 * This function frees all the dynamically allocated memory used in the game, including the game struct itself.
 * 
 * @param game  - a pointer to a game struct representing the current game state.
*/
void clear_game(struct game *game) {
    TTF_CloseFont(game->time->font);
    free(game->time);
    free(game->player);

    struct wall *wall = game->wall_first;
    while (wall->next != NULL) {
        wall->next->previous = NULL;
        game->wall_first = wall->next;
        free(wall);
        wall = game->wall_first;
    }
    free(game->wall_first);

    free(game);
}


/**
 * Methode qui trie une liste doublement chainer.
 *
 * P.S. Cette methode a été conçus avec l'aide de ChatGPT4. Puis simplifier pour qu'elle prenne moins de ligne
 *
 * @param head Pointeur vers la tete de la liste chainer a trie
 */
void insertionSortWalls(struct wall** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }
    struct wall* sorted = NULL;
    struct wall* unsorted = *head;
    while (unsorted != NULL) {
        struct wall* current = unsorted;
        unsorted = unsorted->next;
        if (sorted == NULL || current->distance < sorted->distance) {
            current->next = sorted;
            if (sorted != NULL) {
                sorted->previous = current;
            }
            sorted = current;
            sorted->previous = NULL;
        } else {
            struct wall* temp = sorted;
            while (temp->next != NULL && current->distance > temp->next->distance) {
                temp = temp->next;
            }
            current->next = temp->next;
            if (temp->next != NULL) {
                temp->next->previous = current;
            }
            temp->next = current;
            current->previous = temp;
        }
    }
    *head = sorted;
}

/**
 * The tri_wall function is responsible for sorting the walls in the game according to their distance from the player, 
 * and updating the game structure to reflect the new order of walls.
 * 
 * @param game - a pointer to the game struct that contains information about the game.
*/
void tri_wall(struct game *game) {
    insertionSortWalls(&game->wall_first);
    struct wall *wall = game->wall_first;
    while (1) {
        if (wall->next == NULL) {
            game->wall_last = wall;
            break;
        }
        wall = wall->next;
    }
}

/**
 * This function is responsible for checking if the player has collided with a wall.
 * 
 * @param player - a pointer to the player struct that contains information about the player.
 * @param wall - a pointer to the wall struct that contains information about the wall.
*/
int check_collision(struct player *player, struct wall *wall) {
    struct wall *wall_current = wall;
    float start_angle[6] = {0, 60, 120, 180, 240, 300};
    float end_angle[6] = {60, 120, 180, 240, 300, 360};
    float player_size = (float)sqrt(pow(player->size / 2, 2) + pow(player->size, 2));

    do {
        if (wall_current->distance > player->distance + player->size) {
            break;
        }
        if (start_angle[wall_current->zone] <= player->angle && player->angle <= end_angle[wall_current->zone]) {
            if (player->distance <= wall_current->distance && player->distance + player_size >= wall_current->distance + 10) {
                return 1;
            }
        }

        wall_current = wall_current->next;
    } while (wall_current->next != NULL);
    return 0;
}

/**
 * This function is the main loop of the game. It initializes the game, plays music, updates the game state, 
 * renders the game, checks for collisions and waits for a specific amount of time after the game is over.
 * 
 * @param renderer - a pointer to the renderer struct that contains information about the renderer.
 * @param event - a pointer to the event struct that contains information about the event.
 * @param difficulty - an integer representing the difficulty of the game.
 * @param music - a pointer to the music struct that contains information about the music.
*/
void game_main(SDL_Renderer *renderer, SDL_Event *event, int difficulty,struct music *music,struct sound *sound) {
    struct game *game = game_initialise(renderer, event, difficulty);

    if (game == NULL) {

        return;
    }

    Uint32 frame_delay = 1000/FPS;
    play_random_music(music);

    while ((game->rencontre) == 0) {
        Uint32 frame_begin = SDL_GetTicks();
        game_update(game, music);
        tri_wall(game);
        game_render(game);
        game->rencontre = check_collision(game->player, game->wall_first);

        Uint32 frame_end = SDL_GetTicks();
        Uint32 frame_time = frame_end - frame_begin;
        if (frame_time < frame_delay) {
            SDL_Delay(frame_delay - frame_time);
        }
        music_update(music);
    }
    Uint32 game_over_time = SDL_GetTicks();
    Uint32 elapsed_time = 0;

    stop_music();
    play_gameover_sound(sound);
    while (elapsed_time <  5000) {
        SDL_Delay(5);
        elapsed_time = SDL_GetTicks() - game_over_time;
    }

    // loop until the desired time has elapsed
    Uint32 start_time = SDL_GetTicks();
    play_gameover_music(music);
    while (SDL_GetTicks() - start_time < 10 * 1000) {
    // do nothing, just wait for time to elapse
    SDL_Delay(10);  // optional: give the CPU a break to avoid busy-waiting
}
    stop_music();

    clear_game(game);
    play_menu_music(music);
}