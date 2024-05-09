#ifndef __GAME
#define __GAME

enum Task {
    TOUCH,
    PHOTO,
    BUTTON,
    JOYSTICK
};

static char *TASK_NAMES[] = {"Touch it!",
                             "Hide it!",
                             "Press it!",
                             "Spin it!"};

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
