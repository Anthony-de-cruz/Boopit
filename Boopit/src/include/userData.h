#ifndef __USERDATA
#define __USERDATA

/** @file */

/**
 * @brief Represents the number of difficulties to choose from.
 */
typedef enum Difficulty { EASY, MEDIUM, HARD, DIFFICULTY_COUNT } Difficulty;

/**
 * @brief An array of strings associated with their corrosponding difficulties.
 */
static char *DIFFICULTY_NAMES[] = {"Easy  ", "Medium", "Hard  ",
                                   "Invalid Difficulty"};

/**
 * @brief Represents the next scene for the game to switch to. Used for the
 * game's control flow between menus.
 */
typedef enum NextScene { MAIN_MENU, GAME, END } NextScene;

/**
 * @brief Represents the data relevant to the user and their experience that
 * needs to be carted around the different game scenes.
 */
typedef struct UserData {
        Difficulty difficulty;
        int lives;
        int baseTime;
        int score;
        NextScene nextScene;
} UserData;

/**
 * @brief Assigns the lives and baseTime to the user data struct according to
 * it's difficulty.
 *
 * @param userData
 */
void handle_difficulty(UserData *userData);

#endif /* __USERDATA */
