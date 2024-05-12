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

    int lives = 0;
    int score = 0;
    Difficulty difficulty = MEDIUM;

    UserData userData = {difficulty, lives, score};

    init_display();
    SensorInit();

    while (running) {
        main_menu(&userData);
        while (userData.lives >= 0) {
            play_game(&userData);
        }
        end_screen(&userData);
    }
}
