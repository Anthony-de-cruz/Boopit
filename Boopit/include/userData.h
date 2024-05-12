#ifndef __USERDATA
#define __USERDATA

typedef enum Difficulty { EASY, MEDIUM, HARD, DIFFICULTY_COUNT } Difficulty;

static char *DIFFICULTY_NAMES[] = {"Easy  ", "Medium", "Hard  ",
                                   "Invalid Difficulty"};

typedef struct UserData {
        Difficulty difficulty;
        int lives;
        int baseTime;
        int score;
} UserData;

#endif /* __USERDATA */
