#ifndef EMBEDDEDCWGAMECODE_GAME_H
#define EMBEDDEDCWGAMECODE_GAME_H

void playGame(void);
void BoopIt(void);
void CoverIt(void);
void PushIt(void);
void BlowIt(void);
void touchSensor(void); // works with button too
void photoresistorSensor(void);
void MX_ADC_Init(void);
void MX_GPIO_Init(void);

#endif // EMBEDDEDCWGAMECODE_GAME_H
