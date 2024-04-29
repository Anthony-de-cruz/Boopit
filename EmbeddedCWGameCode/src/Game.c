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
    int score, r;
    score = 0;

    printf("startint");
    r = rand() % 4;

    while (1) {
        passedTask = 0;
        timedOut = 0;
        printf("swtichting");

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
        printf("switched");

        while (1) {
            if (passedTask > 0) {
                printf("touch");
                pthread_cancel(timerThread);
                break;
            }
            if (timedOut > 0) {
                pthread_cancel(taskThread);
                printf("time");
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
    sleep(1);
    passedTask = 1;
    return NULL;
};
void *photoresistorSensor(void *args) {

    sleep(1);
    passedTask = 1;
    return NULL;
};
void *microphoneSensor(void *args) {

    sleep(1);
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

int main() {
    printf("plauign");
    playGame();
    //
    return 0;
}
