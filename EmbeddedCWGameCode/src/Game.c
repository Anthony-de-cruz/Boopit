#include "Game.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <time.h>
#include <unistd.h>

int passedTask, timedOut;

void playGame() {

    pthread_t taskThread, timerThread;
    int score, lives, r;
    score = 0;
    lives = 3;

    printf("startint\n");
    r = rand() % 4;

    while (1) {
        passedTask = 0;
        timedOut = 0;
        printf("swtichting\n");

        switch (r) {
        case (0):
            pthread_create(&taskThread, NULL, touchSensor, NULL);
            break;
        case (1):
            pthread_create(&taskThread, NULL, buttonSensor, NULL);
            break;
        case (2):
            pthread_create(&taskThread, NULL, photoresistorSensor, NULL);
            break;
        case (3):

            pthread_create(&taskThread, NULL, microphoneSensor, NULL);
            break;
        }
        pthread_create(&timerThread, NULL, timer, NULL);
        printf("switched\n");

        while (1) {
            if (passedTask > 0) {
                printf("touch\n");
                pthread_cancel(timerThread);
                score++;
                break;
            }
            if (timedOut > 0) {
                pthread_cancel(taskThread);
                lives--;
                if (lives == 0) {
                    endGame(score);
                    exit(1);
                }
                printf("time\n");
                break;
            }
        }
    }
}

void *touchSensor(void *args) {
    int answer = 0;
    while (answer != 4) {

        printf("Enter");
        scanf("%d", &answer);
    }
    passedTask = 1;
    return NULL;
}

void *buttonSensor(void *args) {
    int answer = 0;
    while (answer != 4) {

        printf("Enter");
        scanf("%d", &answer);
    }

    passedTask = 1;
    return NULL;
};
void *photoresistorSensor(void *args) {
    int answer = 0;
    while (answer != 4) {

        printf("Enter");
        scanf("%d", &answer);
    }

    passedTask = 1;
    return NULL;
};
void *microphoneSensor(void *args) {
    int answer = 0;
    while (answer != 4) {

        printf("Enter");
        scanf("%d", &answer);
    }

    passedTask = 1;
    return NULL;
};
void MX_ADC_Init(void);
void MX_GPIO_Init(void);

void *timer(void *args) {
    sleep(3);
    timedOut = 1;
    return NULL;
}

void endGame(int score) { printf("%d\n", score); }

int main() {
    playGame();
    //
    return 0;
}
