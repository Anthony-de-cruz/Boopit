#include "RTE_Components.h"
#include CMSIS_device_header
#include "rtx_os.h"

#include <stdbool.h>

#include "display.h"
#include "endScreen.h"
#include "game.h"
#include "mainMenu.h"
#include "sensor.h"
#include "userData.h"

// HAL_GetTick replacement
// from https://developer.arm.com/documentation/ka002485/latest/
extern osRtxInfo_t osRtxInfo;
uint32_t HAL_GetTick(void) { return ((uint32_t)osRtxInfo.kernel.tick); }

int main(void) {
    bool running = true;

    Difficulty difficulty = MEDIUM;
    int lives = 0;
    int baseTime = 0;
    int score = 0;
    NextScene nextScene = MAIN_MENU;
    UserData userData = {difficulty, lives, baseTime, score, nextScene};

    init_display();
    SensorInit();

    while (running) {
        switch (userData.nextScene) {
        case MAIN_MENU:
            main_menu(&userData);
            break;
        case GAME:
            play_game(&userData);
            break;
        case END:
            end_screen(&userData);
            break;
        }
    }
}
