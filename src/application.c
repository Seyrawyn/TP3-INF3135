#include "application.h"
#include "sdl2.h"


#include <stdio.h>
#include <pthread.h>
#include <time.h>

/**
 * This function initializes the SDL library and creates an application window with a renderer to display graphics. 
 * It also loads audio, initializes the menu, and sets the initial state of the application to the menu.
 * 
 * @return - A pointer to a struct application that contains information about the application's window, 
 * renderer, menu, audio, and state. NULL if there was an error.
 * 
*/
struct application *application_initialize() {
    struct application *application = NULL;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL failed to initialize: %s\n", SDL_GetError());
        return NULL;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return NULL;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        fprintf(stderr, "Warning: Linear texture filtering not enabled!");
    }
    application = malloc(sizeof(struct application));
    application->window = SDL_CreateWindow("Maze", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                           SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (application->window == NULL) {
        fprintf(stderr, "Window could not be created: %s\n", SDL_GetError());
        return NULL;
    }
    application->renderer = SDL_CreateRenderer(application->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (application->renderer == NULL) {
        fprintf(stderr, "Renderer could not be created: %s\n", SDL_GetError());
        return NULL;
    }
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        fprintf(stderr, "SDL_image failed to initialize: %s\n", IMG_GetError());
        return NULL;
    }
    application->menu = menu_initialize(application->renderer);
    if (application->menu == NULL) {
        fprintf(stderr, "Failed to initialize menu: %s\n", IMG_GetError());
        return NULL;
    }
    if (TTF_Init() == -1) {
        printf("Erreur lors de l'initialisation de SDL_ttf: %s\n", TTF_GetError());
        return NULL;
    }
    application->track = music_initialize();
    application->sound = sound_initialize();
    //application->sound = sound_initialize();





    play_menu_music(application->track);
    application->state = APPLICATION_STATE_MENU;
    return application;
}


/**
 * This function is responsible for running the game application. It runs a while loop that continues as long as the game application 
 * state is not APPLICATION_STATE_QUIT. The game application state is updated by other parts of the program, 
 * such as the menu and the game itself. Depending on the state, the function calls different parts of the program.
 * 
 * @param application  a pointer to an application structure that contains information about the game application.
 * 
 * 
*/
void application_run(struct application *application) {
    SDL_Event event;

    while (application->state != APPLICATION_STATE_QUIT) {
        switch (application->state) {
            case APPLICATION_STATE_MENU:
                menu_run(application->menu);
                if (application->menu->state == MENU_QUIT) {
                    application->state = APPLICATION_STATE_QUIT;
                } else if (application->menu->state == MENU_PLAY) {
                    application->state = APPLICATION_STATE_PLAY;
                }
                break;
            case APPLICATION_STATE_PLAY:
                game_main(application->renderer, &event, application->menu->difficulty_chosen, application->track, application->sound);
                application->state = APPLICATION_STATE_MENU;
                application->menu->state = MENU_PLAY_FOCUS;
                break;
            case APPLICATION_STATE_SETTINGS:
                //TODO
                break;
            case APPLICATION_STATE_QUIT:
                //TODO
                break;
        }
    }
}


/**
 * This function frees the memory allocated to the application and shuts down the SDL library.
 * 
 * @param application  a pointer to an application structure that contains information about the game application.
*/
void application_shut_down(struct application *application) {
    SDL_DestroyRenderer(application->renderer);
    SDL_DestroyWindow(application->window);
    menu_delete(application->menu);
    free_Music(application->track);
    free_Sound(application->sound);
    free(application);
    IMG_Quit();
    TTF_Quit();
    Mix_CloseAudio();
    SDL_Quit();
}
