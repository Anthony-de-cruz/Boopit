#ifndef EMBEDDEDCWGAMECODE_GAME_H
#include <stdbool.h>
#define EMBEDDEDCWGAMECODE_GAME_H

void playGame();
void endGame(int score);
void *timer(void *args);
void *touchSensor(void *args); // works with button too
void *buttonSensor(void *args);
void *photoresistorSensor(void *args);
void *microphoneSensor(void *args);
void MX_ADC_Init(void);
void MX_GPIO_Init(void);
int main(void);

#endif // EMBEDDEDCWGAMECODE_GAME_H
