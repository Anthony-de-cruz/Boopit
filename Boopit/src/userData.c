#include "userData.h"

void handle_difficulty(UserData *userData) {

    switch (userData->difficulty) {
    case EASY:
        userData->lives = 5;
        userData->baseTime = 3000;
        break;
    case MEDIUM:
        userData->lives = 3;
        userData->baseTime = 2000;
        break;
    case HARD:
        userData->lives = 2;
        userData->baseTime = 1500;
        break;
    default:
        break;
    }
}