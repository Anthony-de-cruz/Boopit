#ifndef __GAME
#include <stdbool.h>
#define __GAME

bool touch_sensor(void);
bool photo_sensor(void);
bool button_sensor(void);
bool Joystick_sensor(void);
void play_game(void);
extern int score;
extern int lives;

void MX_ADC_Init_Photo(void);
void MX_ADC_Init_JoyX(void);
void MX_ADC_Init_JoyY(void);
void MX_GPIO_Init_Photo(void);
void MX_GPIO_Init_JoyX(void);
void MX_GPIO_Init_JoyY(void);


#endif /* __GAME */


/*
    all senser functions
        return bool
    playgame
        create task - random
        call updateScreen
        update score, lives, time


*/
