#ifndef __SENSOR
#include <stdbool.h>
//#include "stm32f7xx_hal.h"
//#include "stm32f7xx_hal_gpio.h"
#define __SENSOR

//extern ADC_HandleTypeDef hadcPhoto;
//extern ADC_HandleTypeDef hadcJoyY;

bool touch_sensor(void);
bool photo_sensor(void);
bool button_sensor(void);
bool Joystick_sensor(void);


void MX_ADC_Init_Photo(void);
void MX_ADC_Init_JoyY(void);
void MX_GPIO_Init_Photo(void);
void MX_GPIO_Init_JoyY(void);
void SensorInit(void);


#endif /* __SENSOR */
