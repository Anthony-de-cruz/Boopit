#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "display.h"
#include "mainMenu.h"
#include "stm32f7xx_hal.h"
#include "userData.h"

extern GLCD_FONT GLCD_Font_6x8;
extern GLCD_FONT GLCD_Font_16x24;

Button play_button = {(int)(SCREEN_WIDTH * 0.15) - (100 / 2),
                      (int)(SCREEN_HEIGHT * 0.50) - (50 / 2),
                      100,
                      50,
                      "Play",
                      &GLCD_Font_16x24,
                      0,
                      0};

Button difficulty_button = {(int)(SCREEN_WIDTH * 0.15) - (100 / 2),
                            (int)(SCREEN_HEIGHT * 0.50) - (50 / 2) + 70,
                            280,
                            50,
                            "Change Difficulty",
                            &GLCD_Font_16x24,
                            150,
                            0};

void handle_difficulty(UserData *userData) {

    switch (userData->difficulty) {
    case EASY:
        userData->lives = 5;
        userData->baseTime = 3000;
        break;
    case MEDIUM:
        userData->lives = 3;
        userData->baseTime = 2000;
        break;
    case HARD:
        userData->lives = 2;
        userData->baseTime = 1500;
        break;
    default:
        exit(EXIT_FAILURE);
        break;
    }
}

void handle_input(TOUCH_STATE *tsc_state, UserData *userData, bool *inMenu) {

    Touch_GetState(tsc_state);
    if (!tsc_state->pressed) {
        return;
    }

    if (check_button_press(&play_button, tsc_state)) {
        handle_difficulty(userData);
        userData->score = 0;
        *inMenu = false;
    } else if (check_button_press(&difficulty_button, tsc_state)) {
        if (userData->difficulty < DIFFICULTY_COUNT - 1) {
            userData->difficulty++;
        } else {
            userData->difficulty = 0;
        }
    }
}

void draw_main_menu(Difficulty *difficulty) {

    char *title = "BOOPIT!";
    int title_size = strlen(title) * 16;

    GLCD_SetFont(&GLCD_Font_16x24);
    GLCD_DrawString((int)(SCREEN_WIDTH / 2) - (title_size / 2), 50, title);

    GLCD_DrawString((int)(SCREEN_WIDTH / 2) - (title_size / 2), 100,
                    DIFFICULTY_NAMES[*difficulty]);

    draw_button(&play_button);
    draw_button(&difficulty_button);

    debug_print();
};

void main_menu(UserData *userData) {
    TOUCH_STATE tsc_state;

    bool inMenu = true;

    GLCD_ClearScreen();
    debug_clear_all();

    while (inMenu) {

        handle_input(&tsc_state, userData, &inMenu);

        sprintf(debug_buffers[0], "System Time: %ims   ", HAL_GetTick());
        sprintf(debug_buffers[1], "Touch: %i @ X:%i,Y:%i    ",
                tsc_state.pressed, tsc_state.x, tsc_state.y);
        sprintf(debug_buffers[2], "Difficulty: %i   ", userData->difficulty);

        draw_main_menu(&userData->difficulty);
    }
    GLCD_ClearScreen();
};
