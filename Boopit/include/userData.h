#ifndef __USERDATA
#define __USERDATA

typedef enum Difficulty { EASY, MEDIUM, HARD, DIFFICULTY_COUNT } Difficulty;

static char *DIFFICULTY_NAMES[] = {"Easy  ", "Medium", "Hard  ",
                                   "Invalid Difficulty"};

typedef enum NextScene { MAIN_MENU, GAME, END } NextScene;

typedef struct UserData {
        Difficulty difficulty;
        int lives;
        int baseTime;
        int score;
        NextScene nextScene;
} UserData;

void handle_difficulty(UserData *userData);

#endif /* __USERDATA */
