#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_gpio.h"
#include "Board_LED.h"
#include "Board_Touch.h"

#include "game.h"
#include "display.h"
#include "sensor.h"
#include "globals.h"

#define wait_delay HAL_Delay

extern GLCD_FONT GLCD_Font_6x8;
extern GLCD_FONT GLCD_Font_16x24;

extern ADC_HandleTypeDef hadcPhoto;
extern ADC_HandleTypeDef hadcJoyY;

int score = 0;
int lives = 3;

void draw_game_screen(int timeRemaining, int task) {
    
    char timeRemainingBuffer[256];
    char taskBuffer[256];
    
    GLCD_SetFont(&GLCD_Font_16x24);
    GLCD_DrawString(150, 50, "BOOPIT!");
    
    sprintf(timeRemainingBuffer, "Remaining time: %i  ", (int)timeRemaining/1000);
    GLCD_DrawString(100, 80, timeRemainingBuffer);
    
    sprintf(taskBuffer, "Task: %s   ", TASK_NAMES[task]);
    GLCD_DrawString(100, 200, taskBuffer);
    
    debug_print();
}

void play_game(void){
    int startTime = 0, timeCurrent = 0, timeLimit = 0;
    int endTime;
    Task task = TOUCH;
    
    TOUCH_STATE tsc_state;

    bool taskCompleted = false;

    //Game settings
    srand(HAL_GetTick());
    task = (Task) rand() % 5;
    sprintf(debug_buffers[3], "Random num: %i", task);
    //task = 3; 
    timeLimit = 2000; // in ms
    startTime = HAL_GetTick();
    endTime = startTime + timeLimit;
    
    while(timeCurrent < endTime){
        
        timeCurrent = HAL_GetTick();
        
        //Touch_GetState(&tsc_state);
        
        switch (task) {
            case TOUCH:
                taskCompleted = touch_sensor_pressed();
                break;
            case PHOTO:
                taskCompleted = photo_sensor_pressed();
                break;
            case BUTTON:
                taskCompleted = button_sensor_pressed();
                break;
            case JOYSTICK:
                taskCompleted = joystick_sensor_pressed();
                break;
            case DISPLAY:
                //taskCompleted = tsc_state.pressed;
                break;
        }
    
        //check completed
        if(taskCompleted){
            LED_On(0u);
            score++;
            return;
            
        }
        else{
            LED_Off(0U);
        }

        sprintf(debug_buffers[0], "System Time: %ims", timeCurrent);
        sprintf(debug_buffers[2], "Lives: %i", lives);
        
        draw_game_screen(endTime - timeCurrent,  task);
    }

    lives--;
}
