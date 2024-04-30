#ifndef __GAME
#include <stdbool.h>
#define __GAME

bool touch_sensor(void);
bool photo_sensor(void);
bool button_sensor(void);
bool microphone_sensor(void);
void play_game(void);
extern int score;
extern int lives;

#endif /* __GAME */


/*
    all senser functions
        return bool
    playgame
        create task - random
        call updateScreen
        update score, lives, time


*/