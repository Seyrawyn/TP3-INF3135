// General constants
#define SCREEN_WIDTH  (0.5 * 2048)
#define SCREEN_HEIGHT (0.5 * 1535)

// Menu constants
#define BACKGROUND_FILENAME "../assets/Space_Background.png"
#define BACKGROUND_X 0
#define BACKGROUND_Y 0

#define TITLE_FILENAME "../assets/title-small.png"
#define TITLE_WIDTH 588
#define TITLE_X (0.5 * (SCREEN_WIDTH - TITLE_WIDTH))
#define TITLE_Y (0.05 * SCREEN_HEIGHT)

#define PLAY_FILENAME "../assets/play-small.png"
#define PLAY_WIDTH 122
#define PLAY_X (0.25 * SCREEN_WIDTH - 0.5 * PLAY_WIDTH)
#define PLAY_Y (0.45 * SCREEN_HEIGHT)

#define QUIT_FILENAME "../assets/quit-small.png"
#define QUIT_WIDTH 160
#define QUIT_X (0.75 * SCREEN_WIDTH - 0.5 * QUIT_WIDTH)
#define QUIT_Y (0.45 * SCREEN_HEIGHT)

#define DIFFICULTY_FILENAME "../assets/difficulty-small.png"
#define DIFFICULTY_WIDTH 325
#define DIFFICULTY_X (0.5 * SCREEN_WIDTH - 0.5 * DIFFICULTY_WIDTH)
#define DIFFICULTY_Y (0.8 * SCREEN_HEIGHT)

#define DIFFICLUTY_EASY_FILENAME "../assets/easy-small.png"
#define DIFFICLUTY_MEDIUM_FILENAME "../assets/medium-small.png"
#define DIFFICLUTY_HARD_FILENAME "../assets/hard-small.png"


#define DIFFICULTY_EASY_X (0.5 * SCREEN_WIDTH - 0.5 * DIFFICULTY_WIDTH)
#define DIFFICULTY_MEDIUM_X (0.6 * SCREEN_WIDTH - 0.5 * DIFFICULTY_WIDTH)
#define DIFFICULTY_HARD_X (0.73 * SCREEN_WIDTH - 0.5 * DIFFICULTY_WIDTH)

#define DIFFICULTY_EASY_Y (0.75 * SCREEN_HEIGHT)
#define DIFFICULTY_MEDIUM_Y (0.75 * SCREEN_HEIGHT)
#define DIFFICULTY_HARD_Y (0.75 * SCREEN_HEIGHT)


// adjust the y-coordinates as needed to get the desired spacing




// Music constants
#define MUSIC_COUNT_TRACKS 7
#define MENU_MUSIC_FILENAMES "../assets_soundtrack/Skyline.mp3"
#define GAME_OVER_MUSIC_FILENAMES "../assets_soundtrack/Rick_Astley_-_Never_Gonna_Give_You_Up_Official_Music_Video.mp3"
extern const char* music_Selector[MUSIC_COUNT_TRACKS];





// Sound constants
#define SOUND_GAMEOVER_FILENAMES "../assets_soundtrack/mixkit-arcade-video-game-explosion-2810.wav"


// Setting constants
# define MAX_VOLUME 10
# define MIN_VOLUME 0



// Constante pour en jeu
#define PLAYER_SIZE 30 // La taille en pixels du joueur (carré)
#define RADIUS 70  // Vous pouvez ajuster cette valeur en fonction de la distance souhaitée

#define BACKGROUND_COLOR_R 0
#define BACKGROUND_COLOR_G 0
#define BACKGROUND_COLOR_B 0

#define WALL_DISTANCE_CENTRE 500.0f
#define INNER_CIRCLE_RADIUS 50
#define FPS 60