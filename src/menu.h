#ifndef MENU_H
#define MENU_H

#include "sdl2.h"
#include "constants.h"

// --------------- //
// Data structures //
// --------------- //

enum menu_state {
    MENU_PLAY_FOCUS,             // Play choice has focus
    MENU_QUIT_FOCUS,             // Quit choice has focus
    MENU_DIFFICULTY_FOCUS,       // Difficulty choice has focus
    MENU_EASY_FOCUS,             // Easy choice has focus
    MENU_MEDIUM_FOCUS,           // Medium choice has focus
    MENU_HARD_FOCUS,             // Hard choice has focus
    MENU_PLAY,                   // Play has been chosen
    MENU_QUIT                    // Play has been chosen
};

enum difficulty {
    EASY,
    MEDIUM,
    HARD
};

struct menu {
    enum menu_state state;          // The choice of the user
    enum menu_state stade_diff;     // The difficulty
    int difficulty_chosen;          // The difficulty has been chosen
    struct spritesheet *background; // The menu background
    struct spritesheet *title;      // The title sprite
    struct spritesheet *play;       // The play sprite
    struct spritesheet *quit;       // The quit sprite
    struct spritesheet *difficulty; // The dificulty sprite
    struct spritesheet *easy;       // The dificulty sprite
    struct spritesheet *medium;     // The dificulty sprite
    struct spritesheet *hard;       // The dificulty sprite
    SDL_Renderer *renderer;         // The renderer
};

// --------- //
// Functions //
// --------- //

/**
 * Creates a new menu.
 *
 * @param renderer  The renderer
 * @return          A pointer to the menu, NULL if there was an error
 */
struct menu *menu_initialize(SDL_Renderer *renderer);

/**
 * Start running the menu.
 *
 * @param menu  The menu to show
 */
void menu_run(struct menu *menu);

/**
 * Delete the menu.
 *
 * @param menu  The menu to delete
 */
void menu_delete(struct menu *menu);

#endif
