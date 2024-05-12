#include <stdbool.h>
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

    draw_button(&play_button);
    draw_button(&difficulty_button);
    draw_button(&quit_button);
};

void main_menu(UserData *userData) {

    char *title = "BOOPIT!";
    int title_size = strlen(title) * 16;

    bool running = true;

    while (running) {

        draw_main_menu();
    }
};
