#include "menu.h"
#include "spritesheet.h"
#include "sdl2.h"

#include <stdbool.h>

/**
 * Creates a new menu
 * 
 * @param renderer  The renderer to use
 * @return  A pointer to a new menu, NULL if there was an error
*/
struct menu *menu_initialize(SDL_Renderer *renderer)
{
    struct menu *menu;
    menu = malloc(sizeof(struct menu));
    menu->renderer = renderer;
    menu->state = MENU_PLAY_FOCUS;
    menu->background = spritesheet_create(BACKGROUND_FILENAME, 1, 1, 1, renderer);
    menu->title = spritesheet_create(TITLE_FILENAME, 1, 1, 1, renderer);
    menu->play = spritesheet_create(PLAY_FILENAME, 1, 1, 1, renderer);
    menu->quit = spritesheet_create(QUIT_FILENAME, 1, 1, 1, renderer);
    menu->difficulty = spritesheet_create(DIFFICULTY_FILENAME, 1, 1, 1, renderer);
    menu->easy = spritesheet_create(DIFFICLUTY_EASY_FILENAME, 1, 1, 1, renderer);
    menu->medium = spritesheet_create(DIFFICLUTY_MEDIUM_FILENAME, 1, 1, 1, renderer);
    menu->hard = spritesheet_create(DIFFICLUTY_HARD_FILENAME, 1, 1, 1, renderer);
    menu->difficulty_chosen = MEDIUM;
    menu->stade_diff = MENU_MEDIUM_FOCUS;
    return menu;
}

/**
 * Choses the alpha value for the given menu item
 * 
 * @param chosen  Whether the alpha value is selected
*/
int menu_alpha(bool chosen)
{
    return chosen ? 255 : 64;
}

/**
 * Renders the menu
 *
 * @param menu  The menu to render
*/
void menu_run(struct menu *menu) {
    SDL_Event event;
    while (menu->state != MENU_PLAY && menu->state != MENU_QUIT) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                menu->state = MENU_QUIT;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        if (menu->state == MENU_DIFFICULTY_FOCUS) {
                            if (menu->stade_diff == MENU_EASY_FOCUS) {
                                menu->stade_diff = MENU_HARD_FOCUS;
                            } else if (menu->stade_diff == MENU_MEDIUM_FOCUS) {
                                menu->stade_diff = MENU_EASY_FOCUS;
                            } else if (menu->stade_diff == MENU_HARD_FOCUS) {
                                menu->stade_diff = MENU_MEDIUM_FOCUS;
                            }
                        } else {
                            menu->state = menu->state == MENU_PLAY_FOCUS ? MENU_QUIT_FOCUS : MENU_PLAY_FOCUS;
                        }
                        break;
                    case SDLK_RIGHT:
                        if (menu->state == MENU_DIFFICULTY_FOCUS) {
                            if (menu->stade_diff == MENU_EASY_FOCUS) {
                                menu->stade_diff = MENU_MEDIUM_FOCUS;
                            } else if (menu->stade_diff == MENU_MEDIUM_FOCUS) {
                                menu->stade_diff = MENU_HARD_FOCUS;
                            } else if (menu->stade_diff == MENU_HARD_FOCUS) {
                                menu->stade_diff = MENU_EASY_FOCUS;
                            }
                        } else {
                            menu->state = menu->state == MENU_PLAY_FOCUS ? MENU_QUIT_FOCUS : MENU_PLAY_FOCUS;
                        }
                        break;
                    case SDLK_DOWN:
                        menu->state = menu->state == MENU_DIFFICULTY_FOCUS ? MENU_PLAY_FOCUS : MENU_DIFFICULTY_FOCUS;
                        break;
                    case SDLK_UP:
                        menu->state = menu->state == MENU_DIFFICULTY_FOCUS ? MENU_PLAY_FOCUS : MENU_DIFFICULTY_FOCUS;
                        break;
                    case SDLK_RETURN:
                        if (menu->state == MENU_PLAY_FOCUS) {
                            menu->state = MENU_PLAY;
                        } else if (menu->state == MENU_QUIT_FOCUS) {
                            menu->state = MENU_QUIT;
                        } else if (menu->state == MENU_DIFFICULTY_FOCUS) {
                            if (menu->stade_diff == MENU_EASY_FOCUS) {
                                menu->difficulty_chosen = EASY;
                                menu->state = MENU_PLAY_FOCUS;
                            } else if (menu->stade_diff == MENU_MEDIUM_FOCUS) {
                                menu->difficulty_chosen = MEDIUM;
                                menu->state = MENU_PLAY_FOCUS;
                            } else if (menu->stade_diff == MENU_HARD_FOCUS) {
                                menu->difficulty_chosen = HARD;
                                menu->state = MENU_PLAY_FOCUS;
                            }
                        }
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(menu->renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(menu->renderer);
        spritesheet_render(menu->background, BACKGROUND_X, BACKGROUND_Y, 255, 0);
        spritesheet_render(menu->title, TITLE_X, TITLE_Y, 255, 0);
        spritesheet_render(menu->difficulty, DIFFICULTY_X, DIFFICULTY_Y, 255, 0);
        if (menu->state == MENU_DIFFICULTY_FOCUS) {
            spritesheet_render(menu->easy, DIFFICULTY_EASY_X, DIFFICULTY_EASY_Y, menu_alpha(menu->stade_diff == MENU_EASY_FOCUS), 0);
            spritesheet_render(menu->medium, DIFFICULTY_MEDIUM_X, DIFFICULTY_MEDIUM_Y, menu_alpha(menu->stade_diff == MENU_MEDIUM_FOCUS), 0);
            spritesheet_render(menu->hard, DIFFICULTY_HARD_X, DIFFICULTY_HARD_Y, menu_alpha(menu->stade_diff == MENU_HARD_FOCUS), 0);
        } else {
            spritesheet_render(menu->easy, DIFFICULTY_EASY_X, DIFFICULTY_EASY_Y, menu_alpha(menu->state == MENU_EASY_FOCUS), 0);
            spritesheet_render(menu->medium, DIFFICULTY_MEDIUM_X, DIFFICULTY_MEDIUM_Y, menu_alpha(menu->state == MENU_MEDIUM_FOCUS), 0);
            spritesheet_render(menu->hard, DIFFICULTY_HARD_X, DIFFICULTY_HARD_Y, menu_alpha(menu->state == MENU_HARD_FOCUS), 0);
        }
        spritesheet_render(menu->play, PLAY_X, PLAY_Y, menu_alpha(menu->state == MENU_PLAY_FOCUS), 0);
        spritesheet_render(menu->quit, QUIT_X, QUIT_Y, menu_alpha(menu->state == MENU_QUIT_FOCUS), 0);
        SDL_RenderPresent(menu->renderer);
    }
}

/**
 * Deletes a menu
 * 
 * @param menu  The menu to delete
*/
void menu_delete(struct menu *menu)
{
    if (menu != NULL)
    {
        spritesheet_delete(menu->background);
        spritesheet_delete(menu->title);
        spritesheet_delete(menu->play);
        spritesheet_delete(menu->quit);
        spritesheet_delete(menu->difficulty);
        spritesheet_delete(menu->easy);
        spritesheet_delete(menu->medium);
        spritesheet_delete(menu->hard);

        free(menu);
    }
}
