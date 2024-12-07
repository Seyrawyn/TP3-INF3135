// Created by Jean-Christophe Clouatre on 2023-04-04.


#ifndef INF3135_HIV2023_TP3_GAME_H
#define INF3135_HIV2023_TP3_GAME_H

#include "sdl2.h"
#include "constants.h"
#include "music.h"



struct time {
    TTF_Font *font;
    Uint32 timer;
    Uint32 timer_begin;
};

struct player {
    float angle;
    int distance;
    int size;
};


struct wall {
    struct wall *next;
    struct wall *previous;
    float distance;
    int zone;
    float speed;
};

struct game {
    struct time *time;
    struct player *player;
    struct wall *wall_first;
    struct wall *wall_last;
    SDL_Renderer *renderer;
    SDL_Event *event;
    int rencontre;
    int difficulty;
    Uint32 next_apperence;
    Uint32 temps_next_apperence;
};

/**
 * This function is the main loop of the game. It initializes the game, plays music, updates the game state, 
 * renders the game, checks for collisions and waits for a specific amount of time after the game is over.
 * 
 * @param renderer - a pointer to the renderer struct that contains information about the renderer.
 * @param event - a pointer to the event struct that contains information about the event.
 * @param difficulty - an integer representing the difficulty of the game.
 * @param music - a pointer to the music struct that contains information about the music.
*/
void game_main(SDL_Renderer *renderer, SDL_Event *event, int difficulty, struct music *track, struct sound *sound);

#endif //INF3135_HIV2023_TP3_GAME_H
