#ifndef EMBEDDEDCWGAMECODE_GAME_H
#include <stdbool.h>
#define EMBEDDEDCWGAMECODE_GAME_H

void playGame();
void endGame();
void touchSensor(); // works with button too
void buttonSensor();
void photoresistorSensor();
void microphoneSensor();
void MX_ADC_Init(void);
void MX_GPIO_Init(void);
int main(void);

#endif // EMBEDDEDCWGAMECODE_GAME_H
