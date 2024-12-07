# include "sdl2.h"
# include "constants.h"
# include "music.h"
# include <stdio.h>

const char * music_Selector [MUSIC_COUNT_TRACKS] = {"../assets_soundtrack/About_that_time_.mp3",
                                                    "../assets_soundtrack/BITchintendo.mp3",
                                                    "../assets_soundtrack/Overture.mp3",
                                                    "../assets_soundtrack/Ending.mp3",
                                                    "../assets_soundtrack/Danimal_Cannon_Zef_-_Corrupted.mp3",
                                                    "../assets_soundtrack/Dont_Go_Outside.mp3",
                                                    "../assets_soundtrack/courtesy.mp3"};


/**
 * The function initializes and returns a struct music object that contains menu music, game music, and music tracks loaded using SDL_mixer library.
 * 
 * @return - A pointer to a new music struct, NULL if there was an error
*/
struct music *music_initialize() {
    struct music *music = malloc(sizeof(struct music));
    if (music == NULL) {
        return NULL;
    }
    music->menu_music = Mix_LoadMUS(MENU_MUSIC_FILENAMES);
    if (music->menu_music == NULL) {
        fprintf(stderr, "Failed to load music! SDL_mixer Error %s\n", Mix_GetError());
        return NULL;
    }
    music->game_over_music = Mix_LoadMUS(GAME_OVER_MUSIC_FILENAMES);
    if (music->game_over_music == NULL) {
        fprintf(stderr, "Failed to load music! SDL_mixer Error %s\n", Mix_GetError());
        return NULL;
    }
    music->music_tracks = load_music_tracks(music_Selector, MUSIC_COUNT_TRACKS);

    if (music->music_tracks == NULL) {
        printf("null");
    }
    return music;
}

/**
 * This function that initializes a struct called sound and the function allocates memory for this struct.
 * 
 * @return - A pointer to a new sound struct, NULL if there was an error
*/
struct sound *sound_initialize() {
    struct sound *sound = malloc(sizeof(struct sound));
    if (sound == NULL) {
        return NULL;
    }
    sound->sound_GameOver = Mix_LoadWAV(SOUND_GAMEOVER_FILENAMES);
    if (sound->sound_GameOver == NULL) {
        fprintf(stderr, "Failed to load sound! SDL_mixer Error %s\n", Mix_GetError());
        return NULL;
    }
    
    return sound;
}


/**
 * The play_random_music() function plays a random music track from the list of available tracks. 
 * It takes a pointer to a struct music as its argument, which contains an array of 
 * Mix_Music pointers to music tracks.
 * 
 * @param music - A pointer to a music struct
*/
void play_random_music(struct music *music) {
    int index = rand() % MUSIC_COUNT_TRACKS;

    Mix_Music * track = music->music_tracks[index];
    if(track == NULL) {
        fprintf(stderr, "Failed to load music track %s! SDL_mixer Error %s\n", music_Selector[index], Mix_GetError());
        return;
    }

    Mix_PlayMusic(track, -1);

    music->current_track_index = index;
}

/**
 * The change_music_track function is used to change the current playing track of the music. 
 * This function halts the currently playing music track and then selects 
 * a new track randomly to play using the play_random_music function.
*/
void change_music_track(struct music *music) {
    Mix_HaltMusic();

    play_random_music(music);
}

/**
 * The play_menu_music function is used to play the menu music track.
 * 
 * @param music - A pointer to a music struct
*/
void play_menu_music(struct music *music) {
    Mix_PlayMusic(music->menu_music, -1);
}


/**
 * The play_gameover_music function is used to play the game over music track.
 * 
 * @param music - A pointer to a music struct
*/
void play_gameover_music(struct music *music) {
    Mix_PlayMusic(music->game_over_music, -1);
}
/**
 * The play_game_music function is used to play the game music track.
 * 
 * @param music - A pointer to a music struct
*/
void stop_music(void) {
    Mix_HaltMusic();
}

/**
 * This function is called every frame of the game loop to update the music being played.
 * 
 * @param music - A pointer to a music struct
*/
void music_update(struct music *music) {
    if_music_end(music);
}

/**
 * The if_music_end function is used to check if the current music track has ended.
 * If the current music track has ended, then the function calls the play_random_music function to play a new track.
 * 
 * @param music - A pointer to a music struct
*/
void if_music_end(struct music *music) {
    if (Mix_PlayingMusic() == 0) {
        play_random_music(music);
    }
}

/**
 * The load_music_tracks function is used to load all the music tracks into an array of Mix_Music pointers.
 * 
 * @param filenames - An array of strings that contain the filenames of the music tracks
 * @param num_tracks - The number of music tracks
 * @return - An array of Mix_Music pointers, NULL if there was an error
*/
Mix_Music **load_music_tracks(const char *filenames[], int num_tracks) {
    Mix_Music **tracks = malloc(sizeof(Mix_Music*) * num_tracks);
    if (!tracks) {
        fprintf(stderr, "Failed to allocate memory for music tracks!\n");
        return NULL;
    }
    for (int i = 0; i < num_tracks; i++) {
        Mix_Music *track = Mix_LoadMUS(filenames[i]);
        if (!track) {
            fprintf(stderr, "Failed to load music track %s! SDL_mixer Error %s\n", filenames[i], Mix_GetError());
            return NULL;
        }
        tracks[i] = track;
    }

    return tracks;

}

/**
 * The play_menu_sound function is used to play the menu sound effect.
 * 
 * @param sound - A pointer to a sound struct
*/
void play_menu_sound (struct sound *sound) {
    Mix_PlayChannel(-1, sound->menu_sound, 0);
}

/**
 * The play_gameover_sound function is used to play the gameover sound effect.
 * 
 * @param sound - A pointer to a sound struct
*/
void play_gameover_sound(struct sound *sound) {
    Mix_PlayChannel(-1, sound->sound_GameOver, 0);
}


/**
 * This function  frees the memory allocated to the struct and the chunks of sound loaded in it using the SDL_mixer library.
 * 
 * @param sound - A pointer to a sound struct to be freed
*/
void free_Sound (struct sound *sound) {
    if (sound != NULL) {
    Mix_FreeChunk(sound->sound_GameOver);
    }
    free(sound);
}

/**
 * This function frees the memory used by the given `struct music` and its associated `Mix_Music` pointers. 
 * 
 * @param music - A pointer to a music struct
*/
void free_Music (struct music *music) {
    if (music != NULL) {
        Mix_FreeMusic(music->menu_music);
        Mix_FreeMusic(music->game_over_music);
        for (int i = 0; i < MUSIC_COUNT_TRACKS; i++) {
            Mix_FreeMusic(music->music_tracks[i]);
        }
        free(music->music_tracks);
    }
    free(music);
}
