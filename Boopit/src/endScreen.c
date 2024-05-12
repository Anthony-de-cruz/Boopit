#include <stdbool.h>
#include <string.h>

#include "display.h"
#include "userData.h"

extern GLCD_FONT GLCD_Font_6x8;
extern GLCD_FONT GLCD_Font_16x24;

static Button replay_button = {(int)(SCREEN_WIDTH * 0.25) - (150 / 2),
                               (int)(SCREEN_HEIGHT * 0.75) - (50 / 2),
                               150,
                               50,
                               "Go again",
                               &GLCD_Font_16x24,
                               0,
                               0};

static Button main_menu_button = {(int)(SCREEN_WIDTH * 0.75) - (150 / 2),
                                  (int)(SCREEN_HEIGHT * 0.75) - (50 / 2),
                                  150,
                                  50,
                                  "Main Menu",
                                  &GLCD_Font_16x24,
                                  150,
                                  0};

static void handle_input(TOUCH_STATE *tsc_state, UserData *userData,
                         bool *inEndScreen) {

    Touch_GetState(tsc_state);
    if (!tsc_state->pressed) {
        return;
    }

    if (check_button_press(&replay_button, tsc_state)) {
        *inEndScreen = false;
    } else if (check_button_press(&main_menu_button, tsc_state)) {
    }
}

static void draw_end_screen(void) {

    char *title = "Game Over!";
    int title_size = strlen(title) * 16;

    GLCD_SetFont(&GLCD_Font_16x24);
    GLCD_DrawString((int)(SCREEN_WIDTH / 2) - (title_size / 2), 50, title);

    draw_button(&replay_button);
    draw_button(&main_menu_button);

    debug_print();
};

void end_screen(UserData *userData) {

    bool inEndScreen = true;

    GLCD_ClearScreen();
    debug_clear_all();

    while (inEndScreen) {

        draw_end_screen();
    }
};
