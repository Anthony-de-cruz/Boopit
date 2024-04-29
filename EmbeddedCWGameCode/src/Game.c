#include "Game.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct taskResult {
    int result;
};

void playGame(void) {
    int score = 0;
    clock_t startTime;
    int r = rand();

    srand(time(NULL)); // Initialization, should only be called once.

    startTime = clock();

    void *args;

    struct taskResult *param = (struct taskResult *)args;
    int input;
    int res = param->result;

    printf("%d\n", res);
    pthread_t taskThread;
    pthread_create(&taskThread, NULL, touchSensor, NULL);
    pthread_join(taskThread, NULL);

    printf("%d\n", res);
}

void *touchSensor(void *args) {
    struct taskResult *param = (struct taskResult *)args;
    int input;
    int res = param->result;
    printf("enter: ");
    scanf("%d", &input);
    if (input == 4) {
        res = 1;
    }
    res = 0;
    return NULL;
}

bool buttonSensor();
bool photoresistorSensor();
bool microphoneSensor();
void MX_ADC_Init(void);
void MX_GPIO_Init(void);

int main() {
    struct taskResult *result = malloc(sizeof(struct taskResult));

    result->result = 0;
    // playGame();
    //
    return 0;
}
