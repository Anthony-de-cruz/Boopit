#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "stm32f7xx_hal.h"
#include "GLCD_Config.h"
#include "Board_GLCD.h"
#include "Board_Touch.h"

#include "sensor.h"
#include "display.h"
#include "globals.h"
#include "mainMenu.h"
#include "game.h"
#include "endScreen.h"


int main(void){
    bool running = true;

    init_display();
    SensorInit();
    
    while(running){
        main_menu();
        play_game();
        end_screen();
    }
}
