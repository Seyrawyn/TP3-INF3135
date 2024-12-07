
# ifndef MUSIC_H
# define MUSIC_H

# include "sdl2.h"
# include "constants.h"



struct music {
    Mix_Music *menu_music;        // The music for the menu
    Mix_Music **music_tracks;     // The music tracks
    Mix_Music *game_over_music;   // The music for the game over screen
    int num_tracks;               // The number of music tracks
    int current_track_index;      // The index of the current track
};

struct sound {
    Mix_Chunk *menu_sound;       // The sound for the menu
    Mix_Chunk *sound_GameOver;   // The sound for the game over screen
};

// --------- //
// Functions //
// --------- //

// Initialize the music

/**
 * The function initializes and returns a struct music object that contains menu music, game music, and music tracks loaded using SDL_mixer library.
 * 
 * @return - A pointer to a new music struct, NULL if there was an error
*/
struct music *music_initialize();

/**
 * This function that initializes a struct called sound and the function allocates memory for this struct.
 * 
 * @return - A pointer to a new sound struct, NULL if there was an error
*/
struct sound *sound_initialize();

/**
 * The function loads music tracks from the filenames array and returns an array of Mix_Music pointers.
 * 
 * @param filenames - An array of filenames
 * @param num_tracks - The number of tracks
 * @return - An array of Mix_Music pointers, NULL if there was an error
*/
Mix_Music **load_music_tracks(const char *filenames[], int num_tracks);


/**
 * The play_random_music() function plays a random music track from the list of available tracks. 
 * It takes a pointer to a struct music as its argument, which contains an array of 
 * Mix_Music pointers to music tracks.
 * 
 * @param music - A pointer to a music struct
*/
void play_random_music(struct music *music);

/**
 * The change_music_track function is used to change the current playing track of the music. 
 * This function halts the currently playing music track and then selects 
 * a new track randomly to play using the play_random_music function.
*/
void change_music_track(struct music *music);

/**
 * This function stops the currently playing music.
 * 
 * @param music - A pointer to a music struct
*/
void stop_music(void);

/**
 * This function is responsible for playing the menu music track.
 * 
 * @param music - A pointer to a music struct
*/
void play_menu_music(struct music *music);

/**
 * The play_gameover_music function is used to play the game over music track.
 * 
 * @param music - A pointer to a music struct
*/
void play_gameover_music(struct music *music);

/**
 * This function is called every frame of the game loop to update the music being played.
 * 
 * @param music - A pointer to a music struct
*/
void music_update(struct music *music);

/**
 * unction is used to check if the current playing music has ended. It checks the status of the music 
 * playback using the Mix_PlayingMusic() function from the SDL_mixer library.
 * 
 * @param music - A pointer to a music struct
*/
void if_music_end(struct music *music);


//void set_music_volume(struct music *music, int volume);


/**
 * The play_menu_sound function is used to play the menu sound effect.
 * 
 * @param sound - A pointer to a sound struct
*/
void play_menu_sound(struct sound *sound);

/**
 * The play_setting_sound function is used to play the game over sound effect.
 * 
 * @param sound - A pointer to a sound struct to be freed
*/
void play_gameover_sound(struct sound *sound);

/**
 * This function frees the memory used by the given `struct music` and its associated `Mix_Music` pointers. 
 * 
 * @param music - A pointer to a music struct
*/
void free_Music (struct music *music);


/**
 * This function  frees the memory allocated to the struct and the chunks of sound loaded in it using the SDL_mixer library.
 * 
 * @param sound - A pointer to a sound struct to be freed
*/
void free_Sound (struct sound *sound);


# endif // MUSIC_H