#ifndef __SENSOR
#include <stdbool.h>
//#include "stm32f7xx_hal.h"
//#include "stm32f7xx_hal_gpio.h"
#define __SENSOR

//extern ADC_HandleTypeDef hadcPhoto;
//extern ADC_HandleTypeDef hadcJoyY;

bool touch_sensor_pressed(void);
bool photo_sensor_pressed(void);
bool button_sensor_pressed(void);
bool joystick_sensor_pressed(void);

void MX_ADC_Init_Photo(void);
void MX_ADC_Init_JoyY(void);
void MX_GPIO_Init_Photo(void);
void MX_GPIO_Init_JoyY(void);
void SensorInit(void);


#endif /* __SENSOR */
