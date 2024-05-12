#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "stm32f7xx_hal.h"

#include "display.h"
#include "mainMenu.h"

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


void draw_main_menu() {

    char *title = "BOOPIT!";
    int title_size = strlen(title) * 16;

    GLCD_SetFont(&GLCD_Font_16x24);
    GLCD_DrawString((int)(480 / 2) - (title_size / 2), 50, title);

    draw_button(&play_button);
    draw_button(&difficulty_button);
    draw_button(&quit_button);
};

void main_menu(UserData *userData) {
    int presses = 0;
    TOUCH_STATE tsc_state;

    bool inMenu = true;

    GLCD_ClearScreen();

    while (inMenu) {

        Touch_GetState(&tsc_state);
        if (tsc_state.pressed) {
            presses++;
            if (check_button_press(&play_button, &tsc_state)) {
                userData->lives = 3;
                inMenu = false;
                continue;
            } else if (check_button_press(&quit_button, &tsc_state)) {
                exit(0);
            } else if (check_button_press(&difficulty_button, &tsc_state)) {
            }
        }

        draw_main_menu();
    }
    GLCD_ClearScreen();
};
