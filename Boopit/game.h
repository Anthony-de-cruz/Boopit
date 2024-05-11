#ifndef __GAME
#define __GAME

typedef enum Task {
    TOUCH,
    PHOTO,
    BUTTON,
    JOYSTICK,
    DISPLAY
} Task;

static char *TASK_NAMES[] = {"Touch it!",
                             "Hide it!",
                             "Press it!",
                             "Spin it!",
                             "Boop it!"};

void play_game(void);

#endif /* __GAME */
