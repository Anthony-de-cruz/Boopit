#ifndef __GAME
#include "userData.h"
#define __GAME

/** @file */

/**
 * @brief Represents the different tasks the user can do.
 */
typedef enum Task { TOUCH, PHOTO, BUTTON, JOYSTICK, DISPLAY } Task;

/**
 * @brief Array of strings that represent their corrosponding tasks.
 */
static char *TASK_NAMES[] = {"Touch it!", "Hide it!", "Press it!", "Spin it!",
                      "Boop it!"};

/**
 * @brief Run the game task.
 *
 * @param userData A pointer to the game data to be manipulated by the game
 */
void play_game(UserData *userData);

#endif /* __GAME */
