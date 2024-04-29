#ifndef EMBEDDEDCWGAMECODE_GAME_H
#include <stdbool.h>
#define EMBEDDEDCWGAMECODE_GAME_H

void playGame(void);
void *touchSensor(void *args); // works with button too
bool buttonSensor();
bool photoresistorSensor();
bool microphoneSensor();
void MX_ADC_Init(void);
void MX_GPIO_Init(void);
int main(void);

#endif // EMBEDDEDCWGAMECODE_GAME_H
