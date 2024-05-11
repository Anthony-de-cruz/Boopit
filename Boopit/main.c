#include "RTE_Components.h"
#include CMSIS_device_header

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

