#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Board_LED.h"
#include "Board_Touch.h"
#include "stm32f7xx_hal.h"

#include "display.h"
#include "game.h"
#include "sensor.h"

extern GLCD_FONT GLCD_Font_6x8;
extern GLCD_FONT GLCD_Font_16x24;

extern ADC_HandleTypeDef hadcPhoto;
extern ADC_HandleTypeDef hadcJoyY;

static int last_pressed;

static void draw_game_screen(int timeRemaining, int task, int score,
                             int lives) {

    char timeRemainingBuffer[256];
    char taskBuffer[256];
    char scoreBuffer[256];
    char livesBuffer[256];

    GLCD_SetFont(&GLCD_Font_16x24);
    GLCD_DrawString(150, 50, "BOOPIT!");

    sprintf(timeRemainingBuffer, "Remaining time: %.1f  ",
            (float)timeRemaining / 1000);
    GLCD_DrawString(100, 80, timeRemainingBuffer);

    sprintf(taskBuffer, "Task: %s   ", TASK_NAMES[task]);
    GLCD_DrawString(100, 200, taskBuffer);

    sprintf(scoreBuffer, "Score: %i   ", score);
    GLCD_DrawString(100, 150, scoreBuffer);

    sprintf(livesBuffer, "Lives: %i   ", lives);
    GLCD_DrawString(200, 150, livesBuffer);

    debug_print();
}

void play_game(UserData *userData) {
    int startTime = 0, timeCurrent = 0, timeLimit = 0;
    int endTime;
    Task task = TOUCH;

    TOUCH_STATE tsc_state;

    bool taskCompleted = false;

    // Game settings
    srand(HAL_GetTick());
    task = (Task)rand() % 5;
    timeLimit = userData->baseTime;
    startTime = HAL_GetTick();
    endTime = startTime + timeLimit;

    int input_delay = 100;

    while (timeCurrent < endTime) {

        timeCurrent = HAL_GetTick();

        Touch_GetState(&tsc_state);

        if (last_pressed + input_delay < timeCurrent) {
            last_pressed = timeCurrent;

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
                taskCompleted = tsc_state.pressed;
                break;
            }
        }

        // check completed
        if (taskCompleted) {
            LED_On(0u);
            userData->score++;
            return;

        } else {
            LED_Off(0U);
        }

        sprintf(debug_buffers[0], "System Time: %ims", timeCurrent);
        sprintf(debug_buffers[1], "Touch: %i @ X:%i,Y:%i   ", tsc_state.pressed,
                tsc_state.x, tsc_state.y);
        sprintf(debug_buffers[2], "Lives: %i", userData->lives);
        sprintf(debug_buffers[3], "Task: %i", task);
        sprintf(debug_buffers[4], "Score: %i ", userData->score);

        draw_game_screen(endTime - timeCurrent, task, userData->score,
                         userData->lives);
    }

    userData->lives--;

    if (userData->lives < 0) {
        userData->nextScene = END;
    }
}
