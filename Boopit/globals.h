#ifndef __GLOBALS
#include <stdbool.h>
#define __GLOBALS

typedef enum Difficulty {
    EASY,
    MEDIUM,
    HARD
} Difficulty;

extern int score;
extern int lives;
extern Difficulty difficulty;

#endif /* __GLOBALS */
