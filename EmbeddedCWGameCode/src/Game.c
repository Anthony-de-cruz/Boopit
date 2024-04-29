#include "Game.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int score, lives, timeLimit;

void playGame() {

    int r;
    score = 0;
    lives = 3;
    // timer increments in 0.5ms - 14000 * 0.0005 = 7s;
    timeLimit = 2000;

    printf("startint\n");
    // r = rand() % 4;
    r = 0;

    while (1) {
        if (lives < 1) {
            endGame();
            exit(1);
        }

        switch (r) {
        case (0):
            touchSensor();
            break;
        case (1):
            buttonSensor();
            break;
        case (2):
            photoresistorSensor();
            break;
        case (3):
            microphoneSensor();
            break;
        }
    }
}

void touchSensor() {
    int timer = 0;
    int answer = 0;

    while (timer < timeLimit) {
        printf("OUT\n");
        if (answer == 4) {
            score++;
        }
        timer += 1;
        usleep(500);
    }
    lives--;
}

void buttonSensor() {
    int answer = 0;
    while (answer != 4) {

        printf("Enter");
        scanf("%d", &answer);
    }
};
void photoresistorSensor() {
    int answer = 0;
    while (answer != 4) {

        printf("Enter");
        scanf("%d", &answer);
    }
};
void microphoneSensor() {
    int answer = 0;
    while (answer != 4) {

        printf("Enter");
        scanf("%d", &answer);
    }
};
void MX_ADC_Init(void);
void MX_GPIO_Init(void);

void endGame(int score) { printf("%d\n", score); }

int main() {
    playGame();
    //
    return 0;
}
