#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "display.h"
#include "mainMenu.h"
#include "stm32f7xx_hal.h"
#include "userData.h"

extern GLCD_FONT GLCD_Font_6x8;
extern GLCD_FONT GLCD_Font_16x24;

Button play_button = {
    (int)(480 * 0.15) - (100 / 2), 80, 100, 50, "Play", &GLCD_Font_16x24, 0};

Button quit_button = {
    (int)(480 * 0.15) - (100 / 2), 140, 100, 50, "Quit", &GLCD_Font_16x24, 0};

Button difficulty_button = {(int)(480 * 0.15) - (100 / 2),
                            200,
                            280,
                            50,
                            "Change Difficulty",
                            &GLCD_Font_16x24,
                            0};

void handle_input(TOUCH_STATE *tsc_state, UserData *userData, bool *inMenu) {

    Touch_GetState(tsc_state);
    if (tsc_state->pressed) {
        if (check_button_press(&play_button, tsc_state)) {
            userData->lives = 3;
            userData->difficulty = MEDIUM;
            *inMenu = false;
        } else if (check_button_press(&quit_button, tsc_state)) {
            exit(0);
        } else if (check_button_press(&difficulty_button, tsc_state)) {
        }
    }
}

void draw_main_menu() {

    char *title = "BOOPIT!";
    int title_size = strlen(title) * 16;

    GLCD_SetFont(&GLCD_Font_16x24);
    GLCD_DrawString((int)(480 / 2) - (title_size / 2), 50, title);

    draw_button(&play_button);
    draw_button(&difficulty_button);
    draw_button(&quit_button);

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

        draw_main_menu();
    }
    GLCD_ClearScreen();
};
