#ifndef __USERDATA
#define __USERDATA

typedef enum Difficulty { EASY, MEDIUM, HARD } Difficulty;

typedef struct UserData {
    Difficulty difficulty;
    int lives;
    int score;
} UserData;


#endif /* __USERDATA */
